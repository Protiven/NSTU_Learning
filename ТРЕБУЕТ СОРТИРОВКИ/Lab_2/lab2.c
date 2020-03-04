#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
// символ разделитель директорий
 #ifdef WIN32
 const char dir_delim = '\\'; // для Windows
 #else
 const char dir_delim = '/'; // для *nix
 #endif


// функция считает количество поддиректорий, в папке, указанной ее параметром 
int count_subdir(char* dname) {
    DIR* dir; // дескриптор директории
    struct dirent* entry; // элемент каталога(файл/папка)
    struct stat st; // атрибуты элемента
 
    char *cur_ent; // полное имя текущей записи (/папка/до/элемента/имя)
    int   count = 0; // счетчик поддиректорий
    cur_ent = calloc(1024, sizeof(*cur_ent)); // выделяем память для имени
    dir = opendir(dname); // получаем дескриптор директории
    if (dir) // если удалось открыть
	{ 
        // получаем следующий элемент
		while(entry = readdir(dir)) {
		// пропускаем записи "." и ".."
			if(strcmp(entry->d_name, ".") == 0) continue;
			if(strcmp(entry->d_name, "..") == 0) continue;
			// получаем полное имя пекущей записи
			strcpy(cur_ent, dname);
			strcat(cur_ent, entry->d_name);
			// получаем атрибуты текущей записи
			stat(cur_ent, &st);
			if(S_ISDIR(st.st_mode)) 
			{ // если текущая запись - папка
				++count; // увеличим счетчик
		    }
		}
		closedir(dir); // закрываем дескриптор
    }
    else // выводим ошибку
        perror(dname);
    free(cur_ent); // освободить память
    return count;
}
 
int main(int argc, char** argv)
{
    struct dirent* entry; // текущая запись
    struct stat st; // атрибуты
    char *cur_dir, // текущая директория
         *cur_ent, // имя текущей записи
         *last;    // указатель на последний символ
    // выделяем память
    cur_dir = calloc(1024, sizeof(*cur_dir));
    cur_ent = calloc(1024, sizeof(*cur_ent));
    // копируем имя исполняемого файла
    strcpy(cur_dir, argv[0]);
    last = cur_dir + strlen(cur_dir); // получаем указатель на '\0' в cur_dir
    // затираем символы до разделителя
    while(last > cur_dir) {
        if(*last == dir_delim) break;
        *last = '\0';
        --last;
    }
    // получаем дескриптор
    DIR* dir = opendir(cur_dir);
    if (dir) {
        // получаем записи
        while(entry = readdir(dir)) {
            // пропускаем записи "." и ".."
            if(strcmp(entry->d_name, ".") == 0) continue;
            if(strcmp(entry->d_name, "..") == 0) continue;
            // получаем полное имя пекущей записи
            strcpy(cur_ent, cur_dir);
            strcat(cur_ent, entry->d_name);
            // получаем атрибуты текущей записи
            stat(cur_ent, &st);
 
            // добавляем разделитель к имени, если его там нет
            last = cur_ent + strlen(cur_ent) - 1;
            if(*last != dir_delim) {
                *(last + 1) = dir_delim;
                *(last + 2) = '\0';
            }
            if(S_ISDIR(st.st_mode)) { // если директория
                if(count_subdir(cur_ent)==0) // и нет поддиректорий
                    puts(cur_ent); // выводим имя
            }
        }
        closedir(dir); // закрываем дескриптор
    }
    else // выводим ошибку
        perror(cur_dir);
    // освободить память
    free(cur_dir);
    free(cur_ent);
    return 0;
}



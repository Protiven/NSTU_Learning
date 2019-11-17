<?php
	//`title`, `announce`,`full_text`, `addr_im`,

	 // Проверяем, загрузил ли пользователь файл
	$index = $var_id;
	
	if(!empty($_FILES))
	{

		$file_name = 'images/'. $index .'.jpg';
		
		if(file_exists($file_name))
			unlink($file_name);
		

		$destiation_dir = $file_name; // Директория для размещения файла
		move_uploaded_file($_FILES['image_n']['tmp_name'], $destiation_dir ); // Перемещаем файл в желаемую директорию
	}

	var_dump($var_id);
	
	if(!empty($_GET['title_n']) && !empty($_GET['not_full_n']) && !empty($_GET['full_n']))
	{
		$title_n = $_GET['title_n'];
		$n_full = $_GET['not_full_n'];
		$full = $_GET['full_n'];

		$mysqli->query("UPDATE `data_news` SET `announce` = '$n_full', `title` = '$title_n', `full_text` = '$full'  WHERE `data_news`.`id` = '$index'");
	}
?>
<script type="text/javascript">	
	alert("Все окей!");
</script>

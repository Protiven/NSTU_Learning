<?php
	//`title`, `announce`,`full_text`, `addr_im`,

	 // Проверяем, загрузил ли пользователь файл
	var_dump($_POST);
	
	if(!empty($_FILES))
	{
		$index = $_GET['id'];
		$file_name = 'images/'. $index .'.jpg';
		
		if(file_exists($file_name))
			unlink($file_name);
		

		$destiation_dir = $file_name; // Директория для размещения файла
		move_uploaded_file($_FILES['image_n']['tmp_name'], $destiation_dir ); // Перемещаем файл в желаемую директорию
	}

	
	if(!empty($_POST['title_n']) && !empty($_POST['not_full_n']) && !empty($_POST['full_n']))
	{
		$title_n = $_POST['title_n'];
		$n_full = $_POST['not_full_n'];
		$full = $_POST['full_n'];

		$mysqli->query("UPDATE `data_news` SET `announce` = '$n_full', `title` = '$title_n', `full_text` = '$full'  WHERE `data_news`.`id` = $index");
	}
?>
<script type="text/javascript">
	alert("Все окей!");
</script>

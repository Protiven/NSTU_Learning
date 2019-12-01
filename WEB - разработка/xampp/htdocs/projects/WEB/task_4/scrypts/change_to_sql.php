<?php
	//`title`, `announce`,`full_text`, `addr_im`,
	 // Проверяем, загрузил ли пользователь файл
	$index = $_POST['id'];
	$mysqli = new mysqli('localhost', 'root', '', 'news_base');
	
	if(!empty($_FILES))
	{

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

		if(!$stmt = $mysqli->prepare("UPDATE `data_news` SET `announce` = (?), `title` = (?), `full_text` = (?)  WHERE `data_news`.`id` = (?)"))
			echo "Не удалось подготовить запрос: (" . $mysqli->errno . ") " . $mysqli->error;
		else
		{
			if(!$stmt->bind_param("sssi", $n_full, $title_n, $full, $index))
				echo "Не удалось привязать параметры: (" . $stmt->errno . ") " . $stmt->error;
			else
			{
				if (!$stmt->execute())
					echo "Не удалось выполнить запрос: (" . $stmt->errno . ") " . $stmt->error;
			}
		}
	}
?>
<script type="text/javascript">	
	alert("Все окей!");
</script>
<?php
	header('Location: /projects/WEB/task_2/');
	exit;
?>

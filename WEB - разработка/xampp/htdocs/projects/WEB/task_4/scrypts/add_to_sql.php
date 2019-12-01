<?php
	$mysqli = new mysqli('localhost', 'root', '', 'news_base');
if (!$mysqli)
{
?>
<script type="text/javascript">
	alert("Все плохо!");
</script>
<?php
}
else
{
	$result = $mysqli->query('SELECT `id` FROM `data_news` ORDER BY ID DESC LIMIT 1' );
	$row = $result->fetch_assoc();

	if(isset($_FILES) && $_FILES['image_n']['error'] == 0)
	{ // Проверяем, загрузил ли пользователь файл
	$index = $row['id'] + 1;
	$destiation_dir = 'images/'. $index .'.jpg'; // Директория для размещения файла
	move_uploaded_file($_FILES['image_n']['tmp_name'], $destiation_dir ); // Перемещаем файл в желаемую директорию

	$title_n = $_POST['title_n'];
	$n_full = $_POST['not_full_n'];
	$full = $_POST['full_n'];
	$d = date("Y-m-d");
	$t = date("h:i:s");


	$addr = 'images/'.$index.'.jpg';

	if(!$stmt = $mysqli->prepare("INSERT INTO `data_news` (`id`, `title`, `announce`, `date`, `time`, `full_text`, `addr_im`, `tags`) VALUES (NULL, (?), (?), (?), (?), (?), (?), '');"))
		echo "Не удалось подготовить запрос: (" . $mysqli->errno . ") " . $mysqli->error;
	else
	{
		if(!$stmt->bind_param("ssddss", $title_n, $n_full, $d, $t, $full, $addr))
			echo "Не удалось привязать параметры: (" . $stmt->errno . ") " . $stmt->error;
		else
		{
			if (!$stmt->execute())
				echo "Не удалось выполнить запрос: (" . $stmt->errno . ") " . $stmt->error;
		}
	}

	// '$title_n', '$n_full', '$d', '$t', '$full', '$addr'
?>
<script type="text/javascript">
alert("Все окей!");
</script>
<?php
}
	else
	{
?>
<script type="text/javascript">
	alert("Все плохо!");
</script>
<?php
	}
	header('Location: /projects/WEB/task_2/');
	exit;
}
?>
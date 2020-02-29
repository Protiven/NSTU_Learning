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

	$mysqli->query("INSERT INTO `data_news` (`id`, `title`, `announce`, `date`, `time`, `full_text`, `addr_im`, `tags`) VALUES (NULL, '$title_n', '$n_full', '$d', '$t', '$full', '$addr', '');");
	$mysqli->close();
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
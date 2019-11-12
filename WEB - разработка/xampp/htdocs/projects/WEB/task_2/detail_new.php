<?php
	include("templates/header.php");
	include("templates/side_bar_menu.php");

	if (!$mysqli)
	{
	echo "Не удалось подключиться к MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
	}
	else
	{
		if(!empty($_GET['id']))
		{	
			$var = (int) $_GET['id'];
			$result = $mysqli->query("SELECT `date`,`time`,`title`, `addr_im`, `full_text` FROM `data_news` WHERE `id` = '$var'" );

			if($result!=false)
			{
			$row = $result->fetch_assoc();

?>

<div class="block_content">
	<div class="News" style="display: table-cell">
		<h3><?=$row['title']?></h3>
		<div class="N_img add_set_new" ><img style="width:100%;" src="<?=$row['addr_im']?>" ></img></div>
		<span>
			<?=$row['full_text']?>
		</span>
		<div class="date"><?=$row['date']?> <?=$row['time']?></div>
	</div>
</div>

<?php

			}
			else
			{
				echo "ОШИБКА!";
			}
		}
}
include("templates/footer.php");
?>
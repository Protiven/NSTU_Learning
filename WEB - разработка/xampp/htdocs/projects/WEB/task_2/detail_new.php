<?php
	include("templates/header.php");
	include("templates/side_bar_menu.php");
	$row1=$_GET['id'];
	
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
		<div class="N_img add_set_new" ><img class="Image_news" style="width:100%;" src="<?=$row['addr_im']?>" ></img></div>
		<span>
			<?=$row['full_text']?>
		</span>
		<?php if(isset($_SESSION['logged_user']) && isset($_SESSION['FLAG_ADM']) && $_SESSION['FLAG_ADM'] == true){?>
		<a class="text_href" style="font-family: Arial; font-weight: 500" href="change_new.php?id=<?=$row1?>"> (Изменить публикацию)</a>
		<?php }?>
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
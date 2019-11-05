<div class="block_content">

<?php
	$mysqli = new mysqli('localhost', 'root', '', 'news_base');
	

	
	if (!$mysqli) 
	{
		echo "Не удалось подключиться к MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
	}
	else
	{
		echo "connected successfully!";
	}
	$result = $mysqli->query('SELECT `id`,`date`,`title`, `time`, `text` FROM `data_news` ORDER BY `date` LIMIT 10' );

	
    while ($row = $result->fetch_assoc()) 
	{
       
?>


	<div class="News">
		<h3><?=$row["title"]?></h3>
		<img class="N_img" src="<?=row["adrr_im!!!!!!!!!!!!!"]?>" ></img>
		<span>	
		<?=row["text!!!!!!!!"]?>
		<a class="text_href" href="new_4.html">Подробнее</a>
		</span>
		<div style="text-align:right; width:100%; font-family: Snell Roundhand, cursive;"><?=row["date!!!"]?> <?=row["time!!!!!"]?></div>
	</div>

<?php
	}
?>

</div>
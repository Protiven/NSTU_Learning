<div class="block_content">

<?php
	$mysqli = new mysqli('localhost', 'root', '', 'news_base');	
	if (!$mysqli) 
	{
		echo "Не удалось подключиться к MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
	}
	else
	{
		$result = $mysqli->query('SELECT `announce`,`date`,`time`,`title`, `addr_im`, `id` FROM `data_news` ORDER BY `date` LIMIT 10' );

		
		while ($row = $result->fetch_assoc()) 
		{    
?>

<div class="News" style="display: block;">
	<h3><?=$row["title"]?></h3>
	<div  class="N_img"><img style="width: 100%" src="<?=$row["addr_im"]?>" ></img></div>
	<span>	
	<?=$row["announce"]?>
	<a class="text_href" href="detail_new.php?id=<?=$row["id"]?>">Подробнее</a>
	</span>
	<div style="text-align:right; width:100%; font-family: Snell Roundhand, cursive;"><?=$row["date"]?> <?=$row["time"]?></div>
</div>

<?php
		}
	}
?>
</div>
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
	$result = $mysqli->query('SELECT `id`,`date`,`title` FROM `data_news` ORDER BY `date` LIMIT 10' );

	
    while ($row = $result->fetch_assoc()) 
	{
       
?>


<div class="News">
	<h3><?=$row["title"]?></h3>
	<img class="N_img" src="images/4.jpg" ></img>
	<span>	
	В Альметьевске (Республика Татарстан) уволилась учительница, которую обвинили в том, что она заклеивала первоклассникам рты скотчем за разговоры на уроке. Об этом сообщили в управлении образования Альметьевского района, передает РИА Новости...
	<a class="text_href" href="new_4.html">Подробнее</a>
	</span>
	<div style="	text-align:right;
	width:100%;
	font-family: Snell Roundhand, cursive;">30-05-18</div>
</div>

<?php
	
	
	}
?>
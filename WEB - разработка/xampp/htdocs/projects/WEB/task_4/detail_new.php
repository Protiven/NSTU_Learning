<?php

	include("templates/header.php");
	
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
				<!-- Single Featured Post -->
				<div class="single-blog-post featured-post single-post">
					<div class="post-thumb">
						<a href="#"><img src="<?=$row['addr_im']?>" alt=""></a>
					</div>
					<div class="post-data">
						<a href="#" class="post-title">
							<h6><?=$row['title']?></h6>
						</a>
						<div class="post-meta">
							<p><?=$row['full_text']?></p>
							<div class="newspaper-post-like d-flex align-items-center justify-content-between">
							</div>
						</div>
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
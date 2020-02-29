
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
							<?php
								if(isset($_SESSION['FLAG_ADM']))
								{
									if($_SESSION['FLAG_ADM'] == true)
									{
							?>
							
								<nav aria-label="Page navigation example">
									<ul class="nav">
										<li class="nav-item"><a class="nav-link" style="color: black;" href="change_new.php?id=<?=$row["id"]?>">Изменить новость</a></li>
										<li class="nav-item"><a class="nav-link" style="color: black;" href="">Удалить новость</a></li>
									</ul>
								</nav>
							<?php
									}
								}
							?>
							<div class="newspaper-post-like d-flex align-items-center justify-content-between">
							</div>
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
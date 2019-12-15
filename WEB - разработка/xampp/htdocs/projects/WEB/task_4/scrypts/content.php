<div class="block_content">
	
<?php
	$mysqli = new mysqli('localhost', 'root', '', 'news_base');	
	if (!$mysqli) 
	{
		echo "Не удалось подключиться к MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
	}
	else
	{
		$result = $mysqli->query('SELECT `announce`,`date`,`time`,`title`, `addr_im`, `id` FROM `data_news` ORDER BY `date` DESC LIMIT 10' );

		
		while ($row = $result->fetch_assoc()) 
		{    
?>
			<!-- Single Featured Post         ЭТО есть НОВОСТЬ-->
			<div class="single-blog-post featured-post mb-30">
				<div class="post-thumb">
					<a href="#"><img src="<?=$row['addr_im']?>" alt=""></a>
				</div>
				<div class="post-data">
					<a href="detail_new.php?id=<?=$row["id"]?>" class="post-title">
						<h6><?=$row['title']?></h6>
					</a>
					<div class="post-meta">
						<p class="post-author">By <a href="#">Admin</a></p>
						<p class="post-excerp"> <?=$row['announce']?>
					</div>
				</div>
			</div>
<?php
		}
	}
?>
</div>

</div>
<nav aria-label="Page navigation example">
	<ul class="pagination mt-50">
		<li class="page-item active"><a class="page-link" href="#">1</a></li>
		<li class="page-item"><a class="page-link" href="#">2</a></li>
		<li class="page-item"><a class="page-link" href="#">3</a></li>
		<li class="page-item"><a class="page-link" href="#">4</a></li>
		<li class="page-item"><a class="page-link" href="#">5</a></li>
		<li class="page-item"><a class="page-link" href="#">...</a></li>
		<li class="page-item"><a class="page-link" href="#">10</a></li>
	</ul>
</nav>
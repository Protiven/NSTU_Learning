<?php
	session_start();
	global $mysqli;
	$mysqli = new mysqli('localhost', 'root', '', 'news_base');

	if(isset($_GET['exit']))
	{
		if($_GET['exit'] == 1)
		{
			unset($_SESSION['logged_user']);
			unset($_SESSION['FLAG_ADM']);
			$_GET['exit'] = 0;
		}
	}
?>

<html>
<head>
	<meta charset = "UTF-8"/>
	<title>Новости</title>
	<link rel="shortcut icon" href="icon.png" type="image/x-icon">
	<link href="style/style.css" rel="stylesheet" type="text/css"/>
	<script src="js/jquery-3.4.1.min.js"></script>
	<script src="js/jquery-3.4.1.min.js">
		$('.Image_news').on('click', function()
		{
			if($(this).css('width', '200%'))
		});
		
		$('.Image_news').off('click', function()
		{
			$(this).css('width', '100%');
		});
	</script>
</head>
<body>

	<div class="Label"><P class="blocktext">Новости</P></div>
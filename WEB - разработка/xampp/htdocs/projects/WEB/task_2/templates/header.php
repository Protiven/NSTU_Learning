<?php
	session_start();
	global $mysqli;
	$mysqli = new mysqli('localhost', 'root', '', 'news_base');

	if(isset($_GET['exit']))
	{
		if($_GET['exit'] == 1)
		{
			session_destroy();
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
</head>
<body>
	<div class="Label"><P class="blocktext">Новости</P></div>
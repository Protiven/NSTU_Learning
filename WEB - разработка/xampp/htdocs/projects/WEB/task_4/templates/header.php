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
	<link rel="stylesheet" type="text/css" href="style/bootstrap.css" />
	<link rel="stylesheet" type="text/css" href="style/bootstrap-grid.css" />
	<link rel="stylesheet" type="text/css" href="style/bootstrap-reboot.css" />
	<script src="js/jquery-3.4.1.min.js"></script>
</head>
<body>

	<div class="row border-d" style="margin: 0; z-index: 100;"><h1 class="display-4" style="margin:10px;">Новости</h1></div>
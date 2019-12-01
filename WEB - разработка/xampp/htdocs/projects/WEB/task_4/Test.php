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
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/3.3.7/css/bootstrap.min.css" />
	
    <script src="js/jquery-3.4.1.min.js"></script>
</head>
<body>
  
  
    <style>
        @media only screen and (min-width: 768px) {
        .dropdown:hover .dropdown-menu {
        display: block;
        }
        }
    </style>
    <script>
        $('.dropdown-toggle').click(function(e) {
        if ($(document).width() > 768) {
        e.preventDefault();
        var url = $(this).attr('href'); 
        if (url !== '#') { 
        window.location.href = url;
        }
        }
        });
    </script>



    <nav class="navbar navbar-default">
        <div class="container-fluid">
            <div class="navbar-header">
                <!--<button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
                <span class="sr-only">Toggle navigation</span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                </button>
                <a class="navbar-brand" href="#">BootstrapTema</a>-->
            </div>
            <div id="navbar" class="navbar-collapse collapse">
                <ul class="nav navbar-nav">
                    <li class="active"><a href="#">Home</a></li>
                    <li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">Dropdown <span class="caret"></span></a>
                <ul class="dropdown-menu">
                    <li><a href="#">Action</a></li>
                    <li><a href="#">Another action</a></li>
                    <li><a href="#">Something else here</a></li>
                    <li role="separator" class="divider"></li>
                    <li><a href="#">Separated link</a></li>
                    <li><a href="#">One more separated link</a></li>
                </ul>
                </li>
                </ul>
            </div>
        </div>
    </nav>
</body>
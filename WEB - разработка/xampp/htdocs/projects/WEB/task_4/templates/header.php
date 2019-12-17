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
            header('Location: /projects/WEB/task_4/');
		}
	}
	$errors = "";
	global $add_v;
	$add_v = "";
	if(!empty($_POST['login']) && !empty($_POST['password']))
	{
		$var = md5($_POST['password']);
		$var1 = $_POST['login'];
		$result = $mysqli->query("SELECT * FROM `pers_info` WHERE `login` = '$var1' && `pass` = '$var'");
		$res = $result->fetch_assoc();
		if($res)
		{
			$res1 = $res;
			$var2 = $res1['stat_admin'];
			if($var2 == 1)
			{
				$_SESSION['FLAG_ADM'] = TRUE;
			}
			else
			{
				$_SESSION['FLAG_ADM'] = false;
			}
			$_SESSION['logged_user'] = $res1;
		}
		else
		{
			$errors = "Неправильно введён логин или пароль!";
			if(!empty($_POST['login']))
				$add_v = $_POST['login'];
		}
		
		unset($_POST['login']);
		unset($_POST['password']);
	}
	else
	{
		if(!empty($_POST['login']) && empty($_POST['password']))
		{
			$errors = "Введите пароль!";
			$add_v = $_POST['login'];
		}
		elseif(!empty($_POST['password']) && empty($_POST['login']))
		{
			$errors = "Введите логин!";
			unset($_POST['password']);
		}
	}
?>


<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="description" content="">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <!-- The above 4 meta tags *must* come first in the head; any other head content must come *after* these tags -->

    <!-- Title -->
    <title>The News Paper - News &amp; Lifestyle Magazine Template</title>

    <!-- Favicon -->
    <link rel="icon" href="img/core-img/favicon.ico">

    <!-- Core Stylesheet -->
    <link rel="stylesheet" href="style.css">

</head>

<body>
    <!-- ##### Header Area Start ##### -->
    <header class="header-area">

        <!-- Top Header Area -->
        <div class="top-header-area">
            <div class="container">
                <div class="row">
                    <div class="col-12">
                        <div class="top-header-content d-flex align-items-center justify-content-between">
                            <!-- Logo -->
                            <div class="logo">
                                <a href="index.php"><img src="img/core-img/logo.png" alt=""></a>
                            </div>

                            <!-- Login Search Area -->
                            <div class="login-search-area d-flex align-items-center">
                                <!-- Login -->
                             
                                <?php	if(!isset($_SESSION['logged_user']))
		                        {	?>	                             
                                <div class="login d-flex">
                                    <a class="login_act" href="login.php">Login</a>
                                    <a href="#">Register</a>
                                </div>
                                <?php } 
                                else
                                {
                                    $res1 = $_SESSION['logged_user'];
                                    ?>
                                <div class="login d-flex">
                                    <a href="#">Hello, <?=$res1['l_name']?> <?=$res1['f_name']?></a>
                                <?php	
                                    if(isset($_SESSION['FLAG_ADM']))
                                    {
                                        if( $_SESSION['FLAG_ADM'] == true)
                                        {?>
                                                <a href="add_news.php">Опубликовать новость</a>
                                <?php	}
                                    }?>
                                    
                                    <a href="?exit=1">Exit</a>
                                </div>
                                <?php
                                }
                                ?>
                                <!-- Search Form -->
                                <div class="search-form">
                                    <form action="#" method="post">
                                        <input type="search" name="search" class="form-control" placeholder="Search">
                                        <button type="submit"><i class="fa fa-search" aria-hidden="true"></i></button>
                                    </form>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </header>
    <!-- ##### Header Area End ##### -->

    <!-- ##### Blog Area Start ##### -->
    <div class="blog-area section-padding-80" style="padding-top: 30px;">
        <div class="container">
            <div class="row">
                <div class="col-12 col-lg-8">
                    <div class="blog-posts-area">

<?php
	session_start();
	$res1;
	if(isset($_POST['login']) && isset($_POST['password']))
	{
		$var = md5($_POST['password']);
		$var1 = $_POST['login'];
		$result = $mysqli->query("SELECT * FROM `pers_info` WHERE `login` = '$var1' && `pass` = '$var'");
		if($result)
		{
			$auth_flag = true;
			$res1 = $result->fetch_assoc();
			$var2 = $res1['stat_admin'];
			if($var2 == 1)
			{
				$_SESSION['FLAG_ADM'] = TRUE;
			}
			$_SESSION['logged_user'] = $res1;
		}
	}
	if(isset($_GET['exit']))
	{
		if($_GET['exit'] == 1)
		{
			session_destroy();
			$_GET['exit'] = 0;
		}
	}
?>


<div class="sidebar_menu">
	<div class="link_menu">				
		<ul>
			<a href="index.php">Главная страница</a>
			<li><a href="">Спорт</a></li>
			<li><a href="">Политика</a></li>
			<li><a href="">Экономика</a></li>
			<li><a href="">Шоу-бизнес</a></li>
			<li><a href="">Культура</a></li>
			<li><a href="">Наука и техника</a></li>
			<li><a href="">Россия</a></li>
		</ul>
	</div>
<?php	if(!isset($_SESSION['logged_user']))
		{	?>
			<div class="login_menu">
				<fieldset>
					<form method="post" action = "">
						<p>
							<label>Введите логин:</label><br/>
							<input type="text" name="login" size="17" maxlength="30"/>
						</p>
						<p>
							<label>Введите пароль:</label><br/>
							<input type="password" name="password" size="17" maxlength="30"/>
						</p>
						<input type="submit" value="Подтвердить">
						<p style="text-decoration: underline;">
							<a href="">Регистрация</a>
						</p>
					</form>
				</fieldset>
			</div>
<?php	}else
		{
		$res1 = $_SESSION['logged_user'];	
			?>
		<div style="padding-left: 15px; font-size: 17px; font-family: cursive;">
			<p>Здравствуйте, <?=$res1['l_name']?> <?=$res1['f_name']?>!</p>
		</div>
		<div style="padding-left: 15px; font-size: 17px; font-family: cursive;">
			<p><a href="?exit=1">Выйти из профиля!</a></p>
		</div>
<?php	
		}
		if(isset($_SESSION['FLAG_ADM']))
		{
			if( $_SESSION['FLAG_ADM'] == true)
			{?>
				<div style="padding-left: 15px; font-size: 17px; font-family: cursive;">
					<a href="add_news.php">Опубликовать новость!!!</a>
				</div>
<?php		}
		}?>
	<div class="search_block">
		<fieldset>
			<legend>Поиск новостей</legend>
			<form method="post" action="">
					<p>
					<label>По названию:</label><br/>
					<input type="text" name="news" size="17" maxlength="40"/><br/></p>
					<p><input type="submit" value="Подтвердить"></p>
					<p>
					<label>По дате:</label>
					<input type="date" name="news" size="17" maxlength="17"/></p>
					<p><input type="submit" value="Подтвердить"></p>
			</form>
		</fieldset>
	</div>
</div>
		
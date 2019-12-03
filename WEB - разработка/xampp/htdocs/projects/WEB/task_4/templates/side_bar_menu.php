<?php
	$auth_flag = false;
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
			$auth_flag = true;
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
<div class="row">
	<div class="col border-r">
		<div class="Sidebar_sets">
			<nav class="sidebar-sticky bg-dark navbar-dark " style="padding: 7px;">
				<div class="navbar-brand">Меню</div>		
				<ul class="navbar-nav ">
					<a class="navbar-brand" href="index.php">Главная страница</a>
					<li class="nav-item"><a class="nav-link" href="">Спорт</a></li>
					<li class="nav-item"><a class="nav-link" href="">Политика</a></li>
					<li class="nav-item"><a class="nav-link" href="">Экономика</a></li>
					<li class="nav-item"><a class="nav-link" href="">Шоу-бизнес</a></li>
					<li class="nav-item"><a class="nav-link" href="">Культура</a></li>
					<li class="nav-item"><a class="nav-link" href="">Наука и техника</a></li>
					<li class="nav-item"><a class="nav-link" href="">Россия</a></li>
				</ul>
			</nav>
		<?php	if(!isset($_SESSION['logged_user']))
				{	?>	
					<div class="Sidebar_sets"><?=$errors?></div>
					<div class="Sidebar_sets">
						<fieldset>
							<form method="post" action = "">
								<p>
									<label>Введите логин:</label><br/>
									<input type="text" name="login" value="<?=$add_v?>" size="17" maxlength="30"/>
								</p>
								<p>
									<label>Введите пароль:</label><br/>
									<input type="password" name="password" value="" size="17" maxlength="30"/>
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
			<div class="Sidebar_sets">
				<p>Здравствуйте, <?=$res1['l_name']?> <?=$res1['f_name']?>!</p>
			<?php	
				if(isset($_SESSION['FLAG_ADM']))
				{
					if( $_SESSION['FLAG_ADM'] == true)
					{?>
							<a href="add_news.php">Опубликовать новость</a>
	<?php			}
				}?>
				<p><a href="?exit=1">Выйти из профиля</a></p>
			</div>
	<?php   }
		if(isset($errors))
			unset($errors);
		unset($_POST);
		?>
			<div class="Sidebar_sets">
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
	</div>
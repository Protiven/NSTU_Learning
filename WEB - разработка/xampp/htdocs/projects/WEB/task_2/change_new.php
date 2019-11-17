<?php
	include("templates/header.php");
	include("templates/side_bar_menu.php");
	include("templates/footer.php");

	global $var_id;
	if(!empty($_GET['id']))
		$var_id = $_GET['id'];
	$result = $mysqli->query("SELECT * FROM `data_news` WHERE `id` = '$var_id'" );
	//`id`, `title`, `announce`, `date`, `time`, `full_text`, `addr_im`, `tags`
	
	$res = $result->fetch_assoc();
	$var_title= $res['title'];
	$var_announce= $res['announce'];
	$var_full_text= $res['full_text'];
	$var_addr_im= $res['addr_im'];
	
?>

<div class="block_content" style="padding-left: 20px; width: 70%; padding-right: 20px; padding-top: 7%">
	<fieldset>
		<legend class="add_news">Изменить новость</legend>
		<form method="GET" action="change_new.php?id=<?=$var_id?>" enctype="multipart/form-data">
		<p>
			<label>Название новости:</label><br/>
			<input type="text" name="title_n" value="<?=$var_title?>" size="30"/>
		</p>
		<p>
			<label>Анонс новости:</label><br/>
			<input type="text" name="not_full_n" value="<?=$var_announce?>" size="100"/>
		</p>
		<p>
			<label>Текст новости:</label><br/>
			<input type="text" name="full_n" value="<?=$var_full_text?>" size="100"/>
		</p>
		<p>
			<label>Картинка:</label><br/>
			<input type="file" name="image_n" value="<?=$var_addr_im?>" size="100"/>
		</p>
			<input type="submit" value="Подтвердить">
		</form>
	</fieldset>
<?php
if(!empty($_GET['title_n']))
{ 

	include("scrypts/change_to_sql.php");
}
?>
</div>
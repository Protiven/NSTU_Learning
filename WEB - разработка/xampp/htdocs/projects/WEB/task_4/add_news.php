<?php
	include("templates/header.php");
	include("templates/side_bar_menu.php");
?>

<div class="" style="padding-left: 20px; width: 70%; padding-right: 20px;">
	<fieldset>
	<legend class="">Добавить новость</legend>
		<form method="post" action = "scrypts/add_to_sql.php" enctype="multipart/form-data">
		<p>
			<label>Введите название новости:</label><br/>
			<input type="text" name="title_n" size="30"/>
		</p>
		<p>
			<label>Введите анонс новости:</label><br/>
			<input type="text" name="not_full_n" size="100"/>
		</p>
		<p>
			<label>Введите текст новости:</label><br/>
			<input type="text" name="full_n" size="100"/>
		</p>
		<p>
			<label>Загрузите картинку:</label><br/>
			<input type="file" name="image_n" size="100"/>
		</p>
			<input type="submit" value="Подтвердить">
		</form>
	</fieldset>
</div>
<?php
	include("templates/footer.php");
?>
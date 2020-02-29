<?php
	include("templates/header.php");
?>
   <fieldset>
        <form method="post" action = "index.php">
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
            </p>
        </form>
    </fieldset>
   </div>
<?php
    include("templates/footer.php");
?>

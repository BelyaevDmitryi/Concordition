<!DOCTYPE html>
<script src="calendar/datepicker.js" type="text/javascript" charset="UTF-8" language="javascript"></script>
<script src="/flash-point/datepicker.js" type="text/javascript"><!--mce:0--></script>
<link rel="stylesheet" type="text/css" href="calendar/datepicker.css" />
<?php include("includes/header.php");?>
<h1>Заявка на аренду автомобиля</h1>
<form method="POST" id="feedback-form" action="zayavka.php">
<p><label for="uname">Как к Вам обращаться<br>
<input type="text" name="nameFF" required placeholder="Фамилия имя отчество" x-autocompletetype="name"></label></p>
<p><label for="E-mail">Email для связи<br>
<input type="email" name="contactFF" required placeholder="Адрес электронной почты" x-autocompletetype="email"></label></p>
<p><label for="hour">Время<br>
<input type="time" name="hourFF" required placeholder="Укажите время" x-autocompletetype="hour"></label></p>
<p><label>Выберите дату<br>
<input name="data">
<input type="button" style="background: url('calendar/datepicker.jpg') no-repeat; width: 30px; border: 0px;" onclick="displayDatePicker('data', false, 'dmy', '.');"></label></p>
<input type="submit" value="отправить">
</form>
<?php include("includes/footer.php");?>
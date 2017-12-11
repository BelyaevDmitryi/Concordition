<?php
if (isset ($_POST['contactFF'])) {
  mail ("belyaev.dmitryi.info@mail.ru",
        "заполнена контактная форма с ".$_SERVER['HTTP_REFERER'],
        "Имя: ".$_POST['nameFF']."\nEmail: ".$_POST['contactFF']."\nВремя: ".$_POST['hourFF']."\nДата: ".$_POST['data']);
  echo ('<p style="color: green">Ваше сообщение получено, спасибо!</p>');
}
?>

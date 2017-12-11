<?php
require "Slim/Slim.php";
require "/Slim/Middleware.php";
require "/Slim/Http/Request.php";
require "/Slim/Http/Response.php";
require "/Slim/Middleware/ContentTypes.php";
require "/Slim/Middleware/Flash.php";
require "/Slim/Middleware/MethodOverride.php";
require "/Slim/Middleware/PrettyExceptions.php";
require "/Slim/Exception/Pass.php";
require "/Slim/Exception/Stop.php";
require "/Slim/View.php";
require "/Slim/Route.php";

\Slim\Slim::registerAutoloader();

$app = new \Slim\Slim(array(
	'debug' => true,
	'mode' => 'development',
	'HOST' => 'localhost',
	'USER' => 'root',
	'PASSWORD' => '0000',
	'DBname' => 'avtorental'
));

$app->database = new mysqli(
$app->config('HOST'),
$app->config('USER'),
$app->config('PASSWORD'),
$app->config('DBname')
);
/*if ($app->database->connect_errno){
	echo " MySQL: (" Не удалось подключиться к . $app->database->connect_errno . ") " . $app->database->connect_error;
	die();
}*/

$app->database->query("SET NAMES 'utf8'");
$app->database->query("SET CHARACTER SET 'utf8'");
$app->database->query("SET SESSION collation_connection='utf8_general_ci'");

$app->get('/hello', function (){
	echo 'world';
});

function BDConnection(){
	return new PDO('mysql:dbhost=localhost;dbname=avtorental','root','0000');
}

$app->get('/database(/:param)', function ($param='full_name') use($app){
	if($param=='password')
	{
		echo "Show passwords disabled!";
		exit(0);
	}
	else
	{
		$db = BDConnection();
		$request = $db->query("SELECT * FROM client");
		foreach($request as $result){
			echo $result[$param].'<br>';
		}
	}
});
/*
$app->get('/car', function() use($app){
	$db = BDConnection();
	$request = $db->query("SELECT Number FROM avto");
	if($request->num_rows>0){
		$result = $db->query("SELECT * FROM avto");
		foreach($request as $result){
			echo $result['Number'].'<br>';
		}
	}
	else
	{
		$mes = array('mes'=>'Ops!');
		echo $mes;
	}
	}
});
*/


/*
$app->get('/adduser', function() use ($app){
// the following statement invokes and displays the hello.php View
//
$app->render('register.php');
});
*/

/*$app->post('/user/:login/:pass', function($login,$pass) use ($app){
$User = $login;//$app->request->get('login');
$Pass = $pass;//$app->request->get('pass');
$res=$app->database->query("SELECT `email` FROM `client` WHERE`login`= '$User' AND `password`= '$Pass'");
if($res->num_rows>0){
	$id = (null !== $app->request->post('id'))?$app->request->post('id'):'';
	$full_name = (null !== $app->request->post('full_name'))?$app->request->post('full_name'):'';
	$email = (null !== $app->request->post('email'))?$app->request->post('email'):'';
	$username = (null !== $app->request->post('username'))?$app->request->post('username'):'';
	$password = (null !== $app->request->post('password'))?$app->request->post('password'):'';
	$app->database->query("INSERT INTO `usertbl`( `id`, `full_name`,
	`email`, `username`, `password`) VALUES('$id','$full_name','$email','$username','$password')");
	$app->render('register.php', array('id' => $id,'full_name' => $full_name,
	'email' => $email,'username' => $username));
}
});
*/

$app->run();
?>
<?php 
header('Content-type: application/json');
$dest=$_GET['url'];
echo file_get_contents('http://api.bit.ly/v3/shorten?login=grabbit&apiKey=R_3ec7e2bdc7065f1a5847789192659d72&format=json&longUrl='.$dest);
?>
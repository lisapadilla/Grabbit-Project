<?php 
header('Content-type: application/json');
$dest=$_GET['url'];
echo file_get_contents('http://api.bit.ly/v3/shorten?format=json&longUrl='.$dest);
?>
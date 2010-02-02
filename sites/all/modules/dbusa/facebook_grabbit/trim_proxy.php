<?php 
header('Content-type: application/json');
$dest=$_GET['url'];
echo file_get_contents('http://api.tr.im/api/trim_url.json?url='.$dest);
?>
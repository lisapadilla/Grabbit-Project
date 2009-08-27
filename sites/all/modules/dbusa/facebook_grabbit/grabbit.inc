<?php 

function grabbit_facebook_account($account){

	require_once("facebook/facebook.php");
	require_once("facebook/facebook_desktop.php");
	include("facebook/config.php");
	
	global $user;
	
	$fuser = facebook_grabbit_get_fid($user->uid);
	
	if ($fuser){
		$suser=$fuser->fid;
		$session_key=$fuser->kid;
		
		$facebook = new FacebookDesktop($api_key, $secret);
		
		$facebook->set_user($suser, $session_key);
		$user_details = $facebook->api_client->users_getInfo($suser, 'last_name, first_name, pic_square '); 
		
		print_r($user_details);

		$output = '<div class="facebook-details">You have a facebook account with grabbit:
		            <div class="facebook-details-name">'.$user_details[0]['first_name'].' '.$user_details[0]['last_name'].'</div>
		            <div class="facebook-details-pic"><img src="'.$user_details[0]['pic_square'].'" /></div>
		           </div>';
		
	}else{
		
		$output = '<div class="facebook-details">You dont have a facebook account with grabbit
		              '.l('<img src="'.base_path().drupal_get_path('module', 'facebook_grabbit').'/facebook/connect.gif">','http://apps.facebook.com/onixmedia/?duid='.$user->uid,array('html'=>TRUE,'attributes'=>array('target'=>'blank'))).'          
		            </div>';
		
	}
	
	return $output;
}
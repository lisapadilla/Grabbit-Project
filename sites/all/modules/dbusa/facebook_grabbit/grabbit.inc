<?php 

function grabbit_facebook_account($account){

	require_once("facebook/facebook.php");
	require_once("facebook/facebook_desktop.php");
	include("facebook/config.php");
	

	drupal_add_js(drupal_get_path('module', 'grabbit_panels').'/jquery.alerts.js', $type = 'module');
	drupal_add_css(drupal_get_path('module', 'grabbit_panels').'/jquery.alerts.css', $type = 'module');
	drupal_add_js(drupal_get_path('module', 'facebook_grabbit').'/delete-engine.js', $type = 'module');		
	global $user;
	
	$fuser = facebook_grabbit_get_fid($user->uid);
	
	if ($fuser){
		$suser=$fuser->fid;
		$session_key=$fuser->kid;
		
		$facebook = new FacebookDesktop($api_key, $secret);
		$facebook->set_user($suser, $session_key);
		
		try{
		  
		  $user_details = $facebook->api_client->users_getInfo($suser, 'last_name, first_name, pic_square ');
		
		  if(is_array($user_details[0])):
		  $output='<div id="fb_story_000000000" class="facebook-post clearfix even" style="display: block;">
			<div class="facebook-post-header">
			  <a class="facebook-story-pic" href="#"><span class="facebook-user-pic"><img width="48" src="'.$user_details[0]['pic_square'].'" alt="'.$user_details[0]['first_name'].' '.$user_details[0]['last_name'].'" class="facebook-image-s" target="_blank"/></span></a>
			  <a class="facebook-story-name" href="#"><span class="facebook-user-name">'.$user_details[0]['first_name'].' '.$user_details[0]['last_name'].'</span></a>
			<div class="facebook-post-body">
			  <div class="facebook-post-inside-body">You have a facebook account with grabbit</div>
			  
			</div>
			<div class="views-field-action-link-requestee" id="removing-fb"><a href="#">Remove facebook account from grabbit</a></div>
			</div>
			</div>';
			endif;
			
		}catch(FacebookRestClientException $e){
			
			$output='<div id="fb_story_000000000" class="facebook-post clearfix even" style="display: block;">
				<div class="facebook-post-header">
				  
				<div class="facebook-post-body">
				  <div class="facebook-post-inside-body">There was a problem with your current facebook account. Please try to '.l('re-install','http://apps.facebook.com/onixmedia/?duid='.$user->uid,array('html'=>TRUE,'attributes'=>array('target'=>'blank'))).' it (remember that you first need to delete the application from your facebook account.)</div>
				</div>
				</div>
				</div>';
			
		}
	}else{
		
		$output = '<div class="facebook-details">You dont have a facebook account with grabbit
		              '.l('<img src="'.base_path().drupal_get_path('module', 'facebook_grabbit').'/facebook/connect.gif">','http://apps.facebook.com/onixmedia/?duid='.$user->uid,array('html'=>TRUE,'attributes'=>array('target'=>'blank'))).'          
		            </div>
					';
		
	}
	
	return $output;
}
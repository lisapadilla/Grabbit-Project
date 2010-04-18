<?php
// $Id: template.php,v 1.17.2.1 2009/02/13 06:47:44 johnalbin Exp $

/**
 * @file
 * Contains theme override functions and preprocess functions for the theme.
 *
 * ABOUT THE TEMPLATE.PHP FILE
 *
 *   The template.php file is one of the most useful files when creating or
 *   modifying Drupal themes. You can add new regions for block content, modify
 *   or override Drupal's theme functions, intercept or make additional
 *   variables available to your theme, and create custom PHP logic. For more
 *   information, please visit the Theme Developer's Guide on Drupal.org:
 *   http://drupal.org/theme-guide
 *
 * OVERRIDING THEME FUNCTIONS
 *
 *   The Drupal theme system uses special theme functions to generate HTML
 *   output automatically. Often we wish to customize this HTML output. To do
 *   this, we have to override the theme function. You have to first find the
 *   theme function that generates the output, and then "catch" it and modify it
 *   here. The easiest way to do it is to copy the original function in its
 *   entirety and paste it here, changing the prefix from theme_ to grabbit_.
 *   For example:
 *
 *     original: theme_breadcrumb()
 *     theme override: grabbit_breadcrumb()
 *
 *   where grabbit is the name of your sub-theme. For example, the
 *   zen_classic theme would define a zen_classic_breadcrumb() function.
 *
 *   If you would like to override any of the theme functions used in Zen core,
 *   you should first look at how Zen core implements those functions:
 *     theme_breadcrumbs()      in zen/template.php
 *     theme_menu_item_link()   in zen/template.php
 *     theme_menu_local_tasks() in zen/template.php
 *
 *   For more information, please visit the Theme Developer's Guide on
 *   Drupal.org: http://drupal.org/node/173880
 *
 * CREATE OR MODIFY VARIABLES FOR YOUR THEME
 *
 *   Each tpl.php template file has several variables which hold various pieces
 *   of content. You can modify those variables (or add new ones) before they
 *   are used in the template files by using preprocess functions.
 *
 *   This makes THEME_preprocess_HOOK() functions the most powerful functions
 *   available to themers.
 *
 *   It works by having one preprocess function for each template file or its
 *   derivatives (called template suggestions). For example:
 *     THEME_preprocess_page    alters the variables for page.tpl.php
 *     THEME_preprocess_node    alters the variables for node.tpl.php or
 *                              for node-forum.tpl.php
 *     THEME_preprocess_comment alters the variables for comment.tpl.php
 *     THEME_preprocess_block   alters the variables for block.tpl.php
 *
 *   For more information on preprocess functions and template suggestions,
 *   please visit the Theme Developer's Guide on Drupal.org:
 *   http://drupal.org/node/223440
 *   and http://drupal.org/node/190815#template-suggestions
 */


/*
 * Add any conditional stylesheets you will need for this sub-theme.
 *
 * To add stylesheets that ALWAYS need to be included, you should add them to
 * your .info file instead. Only use this section if you are including
 * stylesheets based on certain conditions.
 */
/* -- Delete this line if you want to use and modify this code
// Example: optionally add a fixed width CSS file.
if (theme_get_setting('grabbit_fixed')) {
  drupal_add_css(path_to_theme() . '/layout-fixed.css', 'theme', 'all');
}
// */

drupal_add_js( path_to_theme().'/js/tooltip.js' );
drupal_add_js( path_to_theme().'/js/engine.js' );

/**
 * Implementation of HOOK_theme().
 */
function grabbit_theme(&$existing, $type, $theme, $path) {
  $hooks = zen_theme($existing, $type, $theme, $path);
  // Add your theme hooks like this:
  /*
  $hooks['hook_name_here'] = array( // Details go here );
  */
  // @TODO: Needs detailed comments. Patches welcome!
  return $hooks;
}

/**
 * Override or insert variables into all templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered (name of the .tpl.php file.)
 */
/* -- Delete this line if you want to use this function
function grabbit_preprocess(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert variables into the page templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("page" in this case.)
 */
function grabbit_preprocess_page(&$vars, $hook) {
  
    global $user;

    if(arg(0)=='user' && $user->uid==0){
	  drupal_set_title('Login');
	  $vars['head_title']='Login | Grabbit';
	  $vars['title']='Login';
    }
    if(arg(0)=='activity'){
	  drupal_set_title($user->name);
	  $vars['head_title']=$user->name.' | Grabbit';
	  $vars['title']=$user->name;
    }

    if(arg(1)=='me' && arg(2)!='myfriends'){
	  $vars['head_title']='Settings | Grabbit';
	  $vars['title']='Settings';
    }

	if( (arg(0)=='user' && arg(1)!=$user->uid && !arg(2)) ||(arg(0)=='user' && arg(1)=='me' && !arg(2))){
		$vars['body_classes'] .=' profile-display';
	}
	if(arg(0)=='search'){
	  	$pos = strpos($vars['content'],'blue smurf');

		if($pos === false) {
		 // string needle NOT found in haystack
		}
		else {
		  $vars['content']='	<h1 class="title">Search your Stream</h1><div class="panels-controllers"><div class="panels-pager" id="panels-pager"><a href="#" title="Search Results">Search Results</a></div></div><div class="messages-status-updates">Your search for <strong>'.arg(2).'</strong> did not match any results, please try again</div>';
		}
	}
	
}
// */

/**
 * Override or insert variables into the node templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("node" in this case.)
 */

function grabbit_preprocess_node(&$vars, $hook) {
  if(arg(0)=='stream'){
    $vars['links_stream'] = flag_create_link('bookmarks', $vars['nid']);	
    $vars['comment_link'] = l("Comment","node/".$vars['nid'],array('query'=>'#comments'));
  }

  if($vars['node']->type=='media'){
	
	 	global $user;
		//controles
		if($user->uid>0){
			drupal_add_js(drupal_get_path('module', 'grabbit_landing').'/resource_engine.js', $type = 'module');
			drupal_add_js(drupal_get_path('module', 'facebook_grabbit').'/facebook_grabbit.js', $type = 'module');
			if($vars['node']->field_networks[0]['value']){
				$networks=unserialize($vars['node']->field_networks[0]['value']);
				$network_id=array_shift($networks);
			}else{
				$network_id=$vars['node']->nid;
			}
			$controles='<div id="tags-show-'.$vars['node']->nid.'"></div>  
			<div class="links_stream_media" id="article-news">
				<a href="JavaScript:void(0);" title="delete" class="trash-item" item_id="'.$vars['node']->nid.'">TR</a>
				  <a href="'.curPageURL().'" title="retweet" class="grabb-that">RT</a>
				  <a href="javascript:void(0);" title="comment" class="comment-news comment-special">Post a comment</a>
				  <a href="javascript:void(0);" title="add/edit tags" class="bring-tags iconchange" node="'.$vars['node']->nid.'"></a>
				   <span class="url-deal iconchange"><a href="#" title="check deals" node="'.$vars['node']->nid.'" >Deal</a></span>
			      <span class="flag-wrapper flag-bookmarks">'.flag_create_link('bookmarks', $vars['node']->nid).'	</span>
			  </div>';

		}
		// end controles
        $vars['controles']= $controles;
	
		$profile = content_profile_load('profile', $vars['node']->uid);
		if($profile->field_profile_picture[0]['filepath']){
		  $pic=theme('imagecache', 'friend_thumbnail', $profile->field_profile_picture[0]['filepath'], 'Friend');
		}else{
		  $pic=theme('imagecache', 'friend_thumbnail', 'sites/all/themes/grabbit/images/default/default_profile.jpg');
		}
		$vars['file_uploader']='<div class="uploader"><span class="pic-uploader">'.$pic.'</span><span class="body-uploader">'.$vars['body'].'<span class="submitted">on '.format_date($vars['node']->created).'</span></span></div>';
    $error="Oops! we could not find the file, check the URL and try again!";
	if ($vars['node']->field_media[0]['value']){
		
			$unserialize=unserialize($vars['node']->field_media[0]['value']);
			if($unserialize){
				$node_media=node_load($unserialize['file']);
				$file_fid=$node_media->field_media[0]['value'];	
			}else{
				if(!$file_fid=facebook_grabbit_get_post_from_file($vars['node']->nid)){
				    $file_fid= $vars['node']->field_media[0]['value'];
			    }else{
				    drupal_goto('node/'.$file_fid);
			    }
			}
			
		
		$result = db_query('SELECT * FROM {files} WHERE fid = %d', $file_fid);
		if (db_affected_rows($result)){
			$file=db_fetch_object($result);
			$ext = substr($file->filename, strrpos($file->filename, '.') + 1);
			switch($ext){
				case "mov":
				case "mp3":
				case "flv":
				  $output = swf($file->filepath, array('params' => array('width' => '430', 'height'=>'400')));
				break;
				case "doc":
				case "rtf":
				case "txt":
				case "csv":
				case "ppt":
				case "xls":
				case "pdf":
				  $output = '<div class="download-wrapper"><div class="filetype"><img src="'.base_path().path_to_theme().'/images/logos/'.$ext.'.gif"/></div><div class="download-file-type">Download: '.l($file->filename,$file->filepath).'</div></div>';
				break;
				default:
				  $output = theme('imagecache', 'image_uploads', $file->filepath, 'Grabbit Image', '');
				break;
			}
			
			
			$vars['file_media']= $output;
		}else{
			$error;
		}

	}
  }

  if($vars['node']->type=='news'){
	global $user;
	drupal_add_js(path_to_theme().'/js/article_engine.js', $type = 'theme');
	//controles
	if($user->uid>0){
		
		$controles='
		<div id="tags-show-'.$vars['node']->nid.'"></div>
		    <div class="links_stream" id="article-news">
		  
		    <a href="JavaScript:void(0);" class="trash-item" item_id="'.$vars['node']->nid.'">TR</a>
		    <a href="'.curPageURL().'" class="grabb-that">RT</a>
		    <a href="javascript:void(0)" class="comment-news">Comment</a>
		    <a href="javascript:void(0);" title="add/edit tags" class="bring-tags iconchange" node="'.$vars['node']->nid.'"></a>
			<span class="url-deal iconchange"><a href="#" title="check deals" node="'.$vars['node']->nid.'" >Deal</a></span>
		    <span class="flag-wrapper flag-bookmarks">'.flag_create_link('bookmarks', $vars['node']->nid).'	</span>
		  </div>';
		
	}
	// end controles
	
	$title ='<div class="titles"><h2>'.$vars['node']->links['feedapi_feed']['title']."</h2>".$controles."<h1>".$vars['node']->title."</h1></div>";
    $vars['content']= $title.'<div class="news-body">'.$vars['content']."</div>"; 	
    
    unset($vars['submitted']);
    $feednid = array_shift($vars['node']->feedapi_node->feed_nids);
    $vars['links'] = '<div class="submitted">From '.
      l( $vars['node']->links['feedapi_feed']['title'], 'node/'. $feednid ). ' - '.$vars['date'].
      '</div>';
    $vars['links'] .= '<div class="original">&raquo; '.
      l( 'go to original article', 
        $vars['node']->feedapi_node->url, 
        array( 'attributes' => array('target' => '_blank'), 'absolute' => true ) ) 
      .'</div>';
  }
}
// */

/**
 * Override or insert variables into the comment templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("comment" in this case.)
 */

function grabbit_preprocess_comment(&$vars, $hook) {

  // Load user's profile picture for display
  $profile = content_profile_load('profile', $vars['comment']->uid);
  if ( $profile->field_profile_picture[0]['filepath'] )
  {
    $pic = theme('imagecache', 'friend_thumbnail', $profile->field_profile_picture[0]['filepath'], 'Friend');
  }
  else
  {
    $pic = theme('imagecache', 'friend_thumbnail', 'sites/all/themes/grabbit/images/default/default_profile.jpg');
  }
  $vars['profile_pic'] = $pic;
  
}
// */

/**
 * Override or insert variables into the block templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
/* -- Delete this line if you want to use this function
function grabbit_preprocess_block(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

function grabbit_preprocess_search_results(&$variables) {

 if(module_exists('facebook_grabbit') && module_exists('grabbit_panels') && module_exists('grabbit_uploads')){

	drupal_add_js(drupal_get_path('module', 'grabbit_panels').'/jquery.truncate-2.3.js', $type = 'module');
	drupal_add_js(drupal_get_path('module', 'grabbit_uploads').'/jquery.form.js', $type = 'module');
	drupal_add_js(drupal_get_path('module', 'grabbit_panels').'/engine.js', $type = 'module');
	drupal_add_js(drupal_get_path('module', 'grabbit_panels').'/jquery.alerts.js', $type = 'module');
	drupal_add_css(drupal_get_path('module', 'grabbit_panels').'/jquery.alerts.css', $type = 'module');
	drupal_add_js(drupal_get_path('module', 'facebook_grabbit').'/jquery_scroll.js', $type = 'module');
    drupal_add_js(drupal_get_path('module', 'facebook_grabbit').'/facebook_grabbit.js', $type = 'module');
    
    foreach($variables['results'] as $result){
	  $node=$result['node'];
	  if($node->type!='feed' && $node->type!='profile'){
	  $twitface[$node->created]=array('time'=>$node->created,
	                                       'value'=>$node);
	  }
    }
    if(arg(1)=='user'){
	    foreach($variables['results'] as $usuario){
	      $profiles[$usuario->title]=$usuario;	
	    }
	  	if(count($profiles)){
		  $resultados = grabbit_search_theme_users($profiles);
	    }else{
		  $resultados = '<div class="no-results">Your search did not match any results</div>';
	    }


		$output ='<div class="view view-friends view-id-friends view-display-id-page_1 view-dom-id-1">
		      <div class="view-content">';
		  
		  $output .= $resultados;
		
		$output .='</div>
		</div>';
	
    }else{
	  	if(count($twitface)){
		  $resultados = facebook_grabbit_theme_results($twitface);
	    }else{
		  $resultados = '<div class="no-results">Your search did not match any results</div>';
	    }

			$output .='<div class="panels-controllers">
			           <div id="panels-pager" class="panels-pager"><a class="activeSlide" title="Search Results" href="#">Search results</a></div>
			           <a href="JavaScript:void(0);" class="move-left"></a>
			           <a href="JavaScript:void(0);" class="move-right"></a>
			           </div><div class="panel-grabbit suser-panels">
			           <div class="panel-favorites">';
			$output .=$resultados;

			$output .='</div></div>';
	
    }
    $variables['search_results']=$output;
  }
}

function curPageURL() {
 $pageURL = 'http';
 if ($_SERVER["HTTPS"] == "on") {$pageURL .= "s";}
 $pageURL .= "://";
 $pageURL .= $_SERVER["SERVER_NAME"].$_SERVER["REQUEST_URI"];
 
 return $pageURL;
}
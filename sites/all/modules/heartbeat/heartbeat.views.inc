<?php

/**
 * Implementation of hook_views_plugins
 */
function heartbeat_views_plugins() {  
  return array(
    'module' => 'heartbeat', // This just tells our themes are elsewhere.
    'row' => array(
      'heartbeat' => array(
        'title' => t('Heartbeat'),
        'help' => t('Display the heartbeat messages in a heartbeat view.'),
        'handler' => 'views_plugin_row_heartbeat_view',
        'path' => drupal_get_path('module', 'heartbeat') . '/handlers', 
        'theme' => 'views_view_row_heartbeat', // views_view_row_node
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-heartbeat',
      ),
      /*
      'node_rss' => array(
        'title' => t('Heartbeat'),
        'help' => t('Display the heartbeat messages in standard heartbeat rss view.'),
        'handler' => 'views_plugin_row_heartbeat_rss',
        'path' => drupal_get_path('module', 'heartbeat') . '/handlers',
        'uses options' => TRUE,
        'type' => 'feed',
        'help topic' => 'style-heartbeat-rss',
      ),
	    'argument validator' => array(
	      'node' => array(
	        'title' => t('Node'),
	        'handler' => 'views_plugin_argument_validate_node',
	        'path' => drupal_get_path('module', 'views') . '/modules/node', // not necessary for most modules
	      ),
	    ),
	    'argument default' => array(
	      'node' => array(
	        'title' => t('Node ID from URL'),
	        'handler' => 'views_plugin_argument_default_node',
	        'path' => drupal_get_path('module', 'views') . '/modules/node', // not necessary for most modules
	        'parent' => 'fixed', // so that the parent class is included
	      ),      
	    ),*/
    ),
  );
}

* SNIPSET TO SHOW THE LIST OF INCOMING PENDING REQUeSTS

 <?
  // Creates the query
  $r=friendlist_api_db_statuses('select',     # Either 'select' or 'count'
                                $user->uid,   # The requester ID (viewer)
                                NULL,         # The requestee ID - NULL = ANY
                                1,            # The relation type
                                'TW_1_TO_2_P' # The status - pending
                               );

  // Cycle through the results
  while($row=db_fetch_object($r)){
    $user_object=user_load( array( 'uid' => $row->requestee_id) );

    $list[]=theme('username',$user_object);
  }

  // Display them
  $result .=  theme('item_list',
                $list,
                "Title",
                'ul',
                array( 'class' => 'pending' )
              );

?>

* SNIPSET TO BE USED IN THE "BLOCKS" SECTION OF DRUPAL, SO THAT
  ONLY FRIENDS CAN SEE A SPECIFIC BLOCK. TO BE PLACED IN THE BLOCK
  CONFIG PAGE, "Show block on specific pages: " AFTER PICKING
  "Show if the following PHP code returns TRUE (PHP-mode, experts only)"


<?php

  global $user;   

  // If a node is being watched...
  if(  arg(0) == 'node' &&
       is_numeric(arg(1)) &&
       ($n=node_load(arg(1))) &&
       ( $u=user_load( array('uid'=>$n->uid))) &&
       ($user->uid != $u->uid)
    ){
      // OK, at this point we are definitely watching a node. See what the status is.
      $status = friendlist_api_relation_status_get($user->uid, $u->uid, 1); # CHANGE "1" WITH THE RELATION TYPE ID!     
      
      return ($status == 'TW_BOTH'); # Or whatever Status you'd like to check!
   }
?>


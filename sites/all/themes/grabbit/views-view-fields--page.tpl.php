<?php
if(facebook_grabbit_get_fid($row->users_friendlist_relations_uid))
  $social_networks .='<span class="from-facebook"><img src="'.base_path().path_to_theme().'/images/various/facebook_ico_sml.gif" alt="Facebook Account" /></span>';

if(oauth_twitter_get_uid($row->users_friendlist_relations_uid))
  $social_networks .='<span class="from-twitter"> <img src="'.base_path().path_to_theme().'/images/various/twitter_ico_sml.gif" alt="Twitter Account" /></span>';

  if ($fields['field_profile_picture_fid']->content){
?>
<div class="views-row">
      
  <div class="views-field-field-profile-picture-fid">
    <span class="field-content"><?=$fields['field_profile_picture_fid']->content?></span>
  </div>
  
  <span class="views-field-name">
    <span class="field-content"><?=$fields['name']->content?></span>
  </span>
  
  <div class="views-field-last-update-time">
    <span class="field-content"><?=$fields['last_update_time']->content?></span>
  </div>
  
  <div class="views-field-action-link-requestee">
    <span class="field-content"><?=$fields['action_link_requestee']->content?></span>
  </div>

  <div class="views-field-action-socital-networks">
    <span class="field-content"><?=$social_networks?></span>
  </div>
</div>
<?php }else{ 
	print $content;
}
	?>
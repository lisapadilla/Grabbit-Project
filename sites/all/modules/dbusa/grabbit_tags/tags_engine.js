Drupal.behaviors.tagsEngine = function(){
  $('.bring-tags').live('click',function(i){
	var tag_node=$(this).attr('node');
	
	$.get(Drupal.settings.basePath+"tags/display",{nid:tag_node},function(data){
		if (data){
			alert(data);
		}else{
			alert('Oops, there was a problem connecting to the server. Please try again');
		}
	});
	
  });
}
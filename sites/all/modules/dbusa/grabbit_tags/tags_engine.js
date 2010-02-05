Drupal.behaviors.tagsEngine = function(){
  $('.bring-tags').live('click',function(i){
	var tag_node=$(this).attr('node');
	$(this).addClass('selected');
	$.get(Drupal.settings.basePath+"tags/display",{nid:tag_node},function(data){
		if (data){
			$('#tags-show-'+tag_node).html(data);
		}else{
			alert('Oops, there was a problem connecting to the server. Please try again');
		}
	});
	
  });

  $('.close-tags').live('click', function(i){
	i.preventDefault();
    $(this).parent().html('');
    $(this).removeClass('selected');	
  });

  $(document).keyup(function(e){
    if (e.keyCode == 27) { $('.close-tags').click(); }	
  });

  $('.tags-submit-profile').live('click',function(i){
	var tag_node=$(this).attr('node');

	$.get(Drupal.settings.basePath+"tags/profile/save",{nid:tag_node},function(data){
		if (data){
			$('#tags-show-'+tag_node).html('<span class="tags-success">The tags were added to your profile successfully.</span>');
			$(this).removeClass('selected');
		}else{
			alert('Oops, there was a problem connecting to the server. Please try again');
		}
	});

  });

}
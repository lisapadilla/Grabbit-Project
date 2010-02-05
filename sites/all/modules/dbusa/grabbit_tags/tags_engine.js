Drupal.behaviors.tagsEngine = function(){
  $('.bring-tags').live('click',function(i){
	var tag_node=$(this).attr('node');
	var selector = $(this);
	$.get(Drupal.settings.basePath+"tags/display",{nid:tag_node},function(data){
		if (data){
			var parent = $('#tags-show-'+tag_node).parents('.user-panel');
			alert(parent.html());
			$('#tags-show-'+tag_node, parent).html(data);
			selector.addClass('selected');
		}else{
			alert('Oops, there was a problem connecting to the server. Please try again');
		}
	});
	
  });

  $('.close-tags').live('click', function(i){
	i.preventDefault();
    var container = $(this).parents('.twitter-message-stream, .facebook-post, .node-stream-news');
    $('.bring-tags',container).removeClass('selected');
    $(this).parent().remove();	
  });

  $(document).keyup(function(e){
    if (e.keyCode == 27) { $('.close-tags').click(); }	
  });

  $('.tags-submit-profile').live('click',function(i){
	var tag_node=$(this).attr('node');

	$.get(Drupal.settings.basePath+"tags/profile/save",{nid:tag_node},function(data){
		if (data){
			var parent = $('#tags-show-'+tag_node).parents('.user-panel');
			$('#tags-show-'+tag_node, parent).html('<span class="tags-success">The tags were added to your profile successfully.</span>').fadeIn(function(){
			      setTimeout(function(){
			         $(".tags-success").fadeOut("fast");
			      }, 2000);
			});
			
			var container = $('#tags-show-'+tag_node).parents('.twitter-message-stream, .facebook-post, .node-stream-news');
			$('.bring-tags',container).removeClass('selected');
		}else{
			alert('Oops, there was a problem connecting to the server. Please try again');
		}
	});

  });

}
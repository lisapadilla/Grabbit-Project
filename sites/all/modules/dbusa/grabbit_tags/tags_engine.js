Drupal.behaviors.tagsEngine = function(){
  $('.bring-tags').live('click',function(i){
	var tag_node=$(this).attr('node');
	var selector = $(this);
	var parent = $(this).parents('.user-panel');
	
	$.get(Drupal.settings.basePath+"tags/display",{nid:tag_node},function(data){
		if (data){
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
    var parent = $(this).parents('.user-panel');
    var options = $(this).parent('.all-tags');

    if($('#add-tags',options).is(':checked')){
	  alert('add tags '+$('#add-tags',options).is(':checked'));
    }
    if($('#save-tags',options).is(':checked')){
	  alert('save tags'+ $('#save-tags',options).is(':checked'));
    }
/*
    $.get(Drupal.settings.basePath+"tags/save",{nid:tag_node,tags:tag_tags}, function(data){
	  	if (data){
		
 	    }else{
			alert('Oops, there was a problem connecting to the server. Please try again');
		}
    });

    $.get(Drupal.settings.basePath+"tags/profile/save",{nid:tag_node},function(data){
		if (data){

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
  */
  });

}
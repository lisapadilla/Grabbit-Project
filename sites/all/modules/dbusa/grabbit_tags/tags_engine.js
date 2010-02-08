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
    var messages = [];
    messages[0]='item';
  if($('#save-tags',options).is(':checked')){
	var tag_tags=($('#text-area-'+tag_node,options).val());
   	$.get(Drupal.settings.basePath+"tags/save",{nid:tag_node,tags:tag_tags}, function(data){
	  	if (data){
		  messages[0]='item';
 	    }else{
			alert('Oops, there was a problem connecting to the server. Please try again');
		}
    }); 
  }

  if($('#add-tags',options).is(':checked')){
    $.get(Drupal.settings.basePath+"tags/profile/save",{nid:tag_node},function(data){
		if (data){
		    messages[1]='profile';
		}else{
			alert('Oops, there was a problem connecting to the server. Please try again');
		}
	});	  
  }
alert(messages[0]);
  if(messages.length>0){
	    alert(messages.length);
    	$('#tags-show-'+tag_node, parent).html('<span class="tags-success">The tags were added to your '+messages.join(' and ')+' successfully.</span>').fadeIn(function(){
		    setTimeout(function(){
		      $(".tags-success").fadeOut("fast");
		    }, 2000);
		});
		var container = $('#tags-show-'+tag_node).parents('.twitter-message-stream, .facebook-post, .node-stream-news');
		$('.bring-tags',container).removeClass('selected');	
  }  

  });

}
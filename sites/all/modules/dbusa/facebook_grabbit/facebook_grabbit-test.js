function display_panel(panel,panel_element){

	// PANEL VARIABLES
	var stories_at_first_p1 = 4;
	var current_panel_1 = panel_element;
	var panel_id = panel;

	$("#"+panel_id+" .panel-wraper #"+current_panel_1.attr('id')+" .content-truncated").truncate( 135,{
	        trail: [ "...<a href='#' class='truncate_show'>more</a>", "<a href='#' class='truncate_hide'>less</a>" ]
	});
	current_panel_1.addClass('last');
	current_panel_1.show();
	
	for (var i = 1; i< stories_at_first_p1; i++){
		if(current_panel_1.next().attr('id')){
			current_panel_1.removeClass('last');
			current_panel_1 = current_panel_1.next()
			$("#"+panel_id+" .panel-wraper #"+current_panel_1.attr('id')+" .content-truncated").truncate( 135,{
			        trail: [ "...<a href='#' class='truncate_show'>more</a>", "<a href='#' class='truncate_hide'>less</a>" ]
			});
			current_panel_1.addClass('last');
			current_panel_1.show();	
		}
	}
	
	$('#'+panel_id).append('<div class="panel-controller"></a><a class="main-stream-next" href="javascript:void(0)">more</a></div>');

}

function display_items(panel){
	stories_per_slide_p1=4;
    panel_id=panel.attr('id');
    current_panel=$(".last",panel);

	if (current_panel.next().attr('class') != undefined){
		var scroll_to = current_panel.next();
		for (var i = 0; i< stories_per_slide_p1; i++){	
			if (current_panel.next().attr('class') != undefined){
				
				current_panel.removeClass('last');
				current_panel = current_panel.next();
		
				$("#"+panel_id+" .panel-wraper #"+current_panel.attr('id')+" .content-truncated").truncate( 135,{
				        trail: [ "...<a href='#' class='truncate_show'>more</a>", "<a href='#' class='truncate_hide'>less</a>" ]
				});
				current_panel.addClass('last');
				current_panel.show();
			}			
		}
		$(document).scrollTo(scroll_to,1000,{axis:'y'});
	}else{
		current_panel.parent().next().html('There\'s no more posts');
	}
}


$(document).ready(function() {

    panels_width=306;
    $(".panel-grabbit").each(function(elemento){
	    var panel_aid=$(this).attr('id');
		var current_panel_1 = $('#'+panel_aid+' .panel-wraper div:first');
		display_panel(panel_aid,current_panel_1);
		panels_width=panels_width+306;
    });

    $('.user-panels').width(panels_width);
	
	$('.main-stream-next').click(function(){
        panel=$(this).parents(".panel-grabbit");
        display_items(panel);
	});
	
	$(".facebook-makecomment-link").click(function () {
		var input1 = $(this).parent();
		var input = $("#myForm",input1).children("input").prev();
		$("#myForm",input1).slideToggle("medium",function(){
			input.focus();
		});
		
	});
	
	$('.comment-news').click(function(){
		var space = $(this).parents('.stream-item-element');
		var text_input = $('.form-text-content',space);
		text_input.attr('value','');
		text_input.focus();
		
		$('#myForm',space).slideToggle('medium',function(){
			text_input.focus();
		});
	});
	
	$('.news-comment-submit-button').click(function(){
		// Save comment
		
		var tag = $(this);
		var nid = $(this).attr('id');
		var tag_id = Math.round(Math.random()*1000);
		var comment = $(this).prev().attr('value');
		
		$.get(Drupal.settings.basePath+"news/comment",{nid:nid,comment:comment,tag_id:tag_id},function(data){
			if (data){
				tag.parent().parent().parent().prev().append(data);
				$('#tag_id').slideToggle('medium');
				tag.prev().attr('value','');
				$('#'+tag_id).slideToggle('medium');
			}else{
				// Handle this depending on the design
				tag.prev().attr('value','Error when connecting, try later.');
			}
		});
	});

	// When user submits a comment in facebook
	$(".facebook_comment_submit").click(function () {
		var tag = $(this);
		var post_id = $(this).attr("id");
		var comment = $(this).prev("input").attr("value");		
		
		$.get(Drupal.settings.basePath+"facebook/comment",{post_id:post_id,comment:comment,mode:"create"},function(data){
	      // Comment has succesfully added and the comment box is hidden again
				if (data){
								//Try grabbit/facebook/getuserinfo?params=first_name,last_name,sex
								//To know the order facebook returns values
								var params = "name,pic_square,profile_url";
								
								$.get(Drupal.settings.basePath+"facebook/getuserinfo",{params:params},function(data1){
									var params_values = data1.split(",");
									var name 				= params_values[0];
									var pic_square 	= params_values[2];
									var profile_url = params_values[3];								
									
									var d = new Date();
									var curr_date 		= d.getDate();
									var curr_day 			= d.getDay();
									var curr_month 		= d.getMonth();
									var curr_year 		= d.getFullYear();
									var curr_hour 		= d.getHours();
									var curr_minutes 	= d.getMinutes();													
								
									var date 		= curr_date+", "+curr_month+"/"+curr_day+"/"+curr_year+" - "+ curr_hour+":"+curr_minutes;
									var comment = tag.prev("input").attr("value");
									
									var new_content 	= '<div id="'+data+'" class="facebook-comments" style="display:none"><a target="_blank" title="'+name+'" class="facebook-story-pic" href="'+profile_url+'"><span class="facebook-user-pic"><img class="facebook-image-s" alt="'+name+'" src="'+pic_square+'" width="30"/></span></a>';
									    new_content  += '<span class="facebook-comment-timeline"><a target="_blank" title="'+name+'" class="facebook-comment-link" href="'+profile_url+'">'+name+'</a> commented on '+date+'</span>';
											new_content  += '<span class="facebook-comment-text">'+comment+'</span><br /><span><a id="facebook-comment-delete-'+data+'" class="facebook-comment-delete" href="javascript:void(0)">delete comment</a></span></div></div>';
									
									// Add the new comment								
									tag.closest("div").parent().prev().append(new_content);
									var id = data;
									
									// Add the new handler to jQuery using live() function
									$('#facebook-comment-delete-'+data).live('click',function(){
										var tag = $(this).parent().parent();
										var post_id = id;
										
										$.get(Drupal.settings.basePath+"facebook/comment",{post_id:post_id,mode:"delete"},function(data){
												// Comment has been deleted
												if (data){
													tag.slideUp('medium',function(){
														tag.remove();
													});		
												}else{
														// An error has occurred, catch it depending on the incoming design
												}
										});	
									});
									
									// Reset comment textbox
									tag.prev("input").attr("value","");
									tag.prev("input").focus();
									// Call a funcion to extend the stream and enable the new comment
									tag.closest("div").parent().prev().children("#"+data).slideToggle('medium');						
								});								
				}else{
								alert ("There was a connection problem. Try later");
				}
    });
	});
		
	$(".facebook-comment-delete").click(function () {
		var tag = $(this).parent().parent();
		var post_id = tag.attr("id");
		
		$.get(Drupal.settings.basePath+"facebook/comment",{post_id:post_id,mode:"delete"},function(data){
	      // Comment has been deleted
				if (data){
					tag.slideToggle('medium');																				
				}else{
						// An error has occurred, catch it depending on the incoming design
				}
    });
	});
	
	
	$(".twit-reply").click(function () {
	  var to = $(this).attr("id")+" "; 
	  
	  $("#edit-status").val(to);
	  var scroll = $("#edit-status");
	  $(document).scrollTo(scroll,100);
	  $("#edit-status").focus();
	});	
	
	
	$('.retweet').click(function (event){
	  var container = $(this).parents().filter('.twitter-message-stream');	
	  var message = $('.twitter-body-contains',container);
	  var to = $('.twit-reply',container).attr('id');
	  
	  $("#edit-status").val("RT "+to+" "+message.text());
	  var scroll = $("#edit-status");
	  $(document).scrollTo(scroll,100);
	  $("#edit-status").focus();
	});
	
	$(".grabb-that").click(function (ev) {
		ev.preventDefault();
		urlcomplete = $(this).attr('href');
		myurl = encodeURIComponent(urlcomplete);
		$.getJSON("http://json-tinyurl.appspot.com/?url=" + myurl + "&callback=?", 
	        function(data)
	        { 
				
				$("#edit-status").val(data.tinyurl+' ');
				var scroll = $("#edit-status");
				$(document).scrollTo(scroll,100);
				$("#edit-status").focus();
	        }
	    );
	 
	  
	});	
	
	$(".twitter_favorite, .twitter_favorite-remove").click(function () {
	  var id = $(this).attr("id"); //post_id
	  var tag = $(this);
	  
	  if (tag.text() == "Add to favorites"){
	    tag.text("Adding to favorites...");
	    $.get(Drupal.settings.basePath+"twitter/addfavorite",{id:id,mode:"create"},function(data){
	      //Successfully added to favorites
	      //Testing if it works
				if (data){
								tag.text("Remove from favorites");
								tag.attr("class","twitter_favorite-remove");
				}else{
								alert ("There was a connection problem. Try later");
				}
	    });
	  }
	  else{ //Remove from favorites
	  tag.text("Removing from favorites...");
	    $.get(Drupal.settings.basePath+"twitter/addfavorite",{id:id,mode:"destroy"},function(data){
	      //Successfully removed from favorites
	      //Testing if it works
				if (data){
								tag.text("Add to favorites");		
								tag.attr("class","twitter_favorite");
				}else{								
								alert ("There was a connection problem. Try later");
				}
	    });		    
	  }  		  
	});
});


Drupal.behaviors.charCountDown = function(context)
{
  var limit = 140;
  var form = $("#facebook-grabbit-update-form");
  
  $('#edit-status').keyup(function()
  {
    if(this.value.length >= limit) 
    {
      //handle the over the limit part here
      $(this).addClass('overlimit');
      $('input',form).attr('disabled', 'true');
      $('input',form).css('opacity', '0.5');      
    } 
    else 
    {
      $(this).removeClass('overlimit');
      $('input',form).removeAttr('disabled');
      $('input',form).css('opacity', '1');
    }
    $('#counter div').text(limit-this.value.length);
  });
}

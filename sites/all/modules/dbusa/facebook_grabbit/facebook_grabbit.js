$(document).ready(function() {

	$(document).scrollTo($(document).children(),0);
	
	// PANEL 1
	var stories_at_first_p1 = 4;
	var stories_per_slide_p1 = 4;
	var current_panel_1 = $('#panel-0 .panel-wraper div:first-child');
	current_panel_1.show();
	
	for (var i = 1; i< stories_at_first_p1; i++){
		current_panel_1 = current_panel_1.next();
		current_panel_1.show();
	}
	
	$('#panel-0').append('<div class="panel-controller"></a><a class="main-stream-next-p1" href="javascript:void(0)">more</a></div>');
	
	$('.main-stream-next-p1').click(function(){
		// Verify if it is the last one
		if (current_panel_1.next().attr('class') != undefined){
			var scroll_to = current_panel_1.next();
			for (var i = 0; i< stories_per_slide_p2; i++){	
				if (current_panel_1.next().attr('class') != undefined){
					current_panel_1 = current_panel_1.next();
					current_panel_1.show();
				}			
			}
			$(document).scrollTo(scroll_to,1000,{axis:'y'});
		}else{
			current_panel_1.parent().next().html('There\'s no more posts');
		}		
	});
	
	// PANEL 2
	var stories_at_first_p2 = 4;
	var stories_per_slide_p2 = 4;
	var current_panel_2 = $('#panel-1 .panel-wraper div:first-child');
	current_panel_2.show();
	
	for (var i = 1; i< stories_at_first_p2; i++){
		current_panel_2 = current_panel_2.next();		
		current_panel_2.show();
	}
	
	$('#panel-1').append('<div class="panel-controller"></a><a class="main-stream-next-p2" href="javascript:void(0)">more</a></div>');
	
	$('.main-stream-next-p2').click(function(){		
		//Verify if it is the last one
		if (current_panel_2.next().attr('class') != undefined){
			var scroll_to = current_panel_2.next();
			for (var i = 0; i< stories_per_slide_p2; i++){	
				if (current_panel_2.next().attr('class') != undefined){
					current_panel_2 = current_panel_2.next();
					current_panel_2.show();
				}			
			}
			$(document).scrollTo(scroll_to,1000,{axis:'y'});
		}else{
			current_panel_2.parent().next().html('There\'s no more posts');
		}
	});
	
	$(".facebook-makecomment-link").click(function () {
		var input1 = $(this).next("div");
		var input = $("#myForm",input1).children("input").prev();
		$("#myForm",input1).slideToggle("medium",function(){
			input.focus();
		});
		
	});
	
	$('.comment-news').click(function(){
		var text_input = $(this).parent().parent().next().next().children().children().children().prev();
		text_input.attr('value','');
		text_input.focus();
		
		$(this).parent().parent().next().next().children().children().slideToggle('medium',function(){
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
	  $("#edit-status").focus();
	  $("#edit-status").val(to);
	  $("#edit-status").focus();
	  
	});	
	
	$(".grabb-that").click(function () {
		requestShortURL('http://www.mycompany.com', function(shortened){
		    alert('new url: ' + shortened);
		});		
	  
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

function requestShortURL(longURL, success) {
    var API = 'http://reque.st/create.api.php?json&url=',
        URL = API + encodeURIComponent(longURL) + '&callback=?';
    console.log('tweet apit url: ' + URL);
    $.getJSON(URL, function(data){
        success && success(data.url);
    });
}

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
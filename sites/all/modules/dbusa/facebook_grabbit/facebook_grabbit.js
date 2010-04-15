function display_panel(panel,panel_element){

	// PANEL VARIABLES
	var stories_at_first_p1 = 8;
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
	
	$('#'+panel_id).append('<div class="panel-controller" id="onstream-controller"><a class="main-stream-next" href="javascript:void(0)">more</a></div>');

}
var panels_heights=new Array();
function display_items(panel){
	stories_per_slide_p1=4;
    panel_id=panel.attr('id');
    current_panel=$(".last",panel);
		$('.main-stream-next',panel).html('retrieving data...');
		pid=panel.attr('pid');
		pager=parseInt(panel.attr('pager'))+1;
		$.get(Drupal.settings.basePath+"panels/paginate",{pid:pid,page:pager},function(data){
				if (data){
		        panel.attr('pager',pager);		
				$("#"+panel_id+" .panel-wraper").append(data);
		        $('.main-stream-next',panel).html('more');
		        panel=$("#"+panel_id);
		        //display_items(panel);
		        fixtheheightMore(panel);
		        Drupal.behaviors.initThickbox(data);
		        Drupal.behaviors.tooltips(data);
			    Drupal.flagLink(data);																
				}else{
		        current_panel.parent().next().html('You have reached the end of your stream');
				}
        });

        $('.tooltip-deal').each(function(i){
			 var contents=$('.tooltip_deal',$(this)).html();

		     $(this).simpletip({
			   	fixed:true,
			    persistent:true,
			    focus:true,
			    position:[-355,0],
			    content: contents
		     });

		   });
		
	//}
}

function fixtheheight(isNext, zeroBasedSlideIndex, slideElement){
	var height = $("#"+slideElement.id).height()+200;
//	$(".suser-panels").height(height);
}

function fixtheheightMore(element){
	var height = $(".panel-wraper",element).height()+$(".panel-title",element).height()+$(".panel-controller",element).height()+200;
//	element.height(height);
//	$(".suser-panels").height(height);
	panels_heights[element.attr('id')]=height;
}
function fixtheheightAfter(currSlideElement, nextSlideElement, options, forwardFlag){
	if(panels_heights[nextSlideElement.id]){
		var height = panels_heights[nextSlideElement.id];
//		$("#"+nextSlideElement.id).height(height);
//		$(".suser-panels").height(height);
	}else{
	  	var height = $("#"+nextSlideElement.id).height()+200;
//		$(".suser-panels").height(height);	
	}

	//Initialize our user agent string to lower case.

	
}
function bringPanelsAjax(currentSlide,NextSlide){
	$('.suser-panels .user-panel').each(function(i){
		if(i==currentSlide && !$(this).attr('engaged') && i!=0){
			paid = $('.panel-content-ajax',$(this)).attr('paid');
			target=$('.panel-wraper',$(this));
			wraper=$(this);
			$('.panel-content-ajax',$(this)).mask("Loading content...");
			$.get(Drupal.settings.basePath+"panels/ajax",{pid:paid,publics:1},function(data){
				if (data){
					target.html(data);
					wraper.attr('engaged','true');
					Drupal.behaviors.initThickbox(data);
			        Drupal.behaviors.tooltips(data);
				    Drupal.flagLink(data);
				}else{
					// Handle this depending on the design
				}
			});
		}
	});
}

var deviceIphone = "iphone";
var deviceIpod = "ipod";
var deviceIpad = "ipad";
var uagent = navigator.userAgent.toLowerCase();
//**************************
// Detects if the current device is an iPhone.
function DetectIphone()
{
   if (uagent.search(deviceIphone) > -1)
      return true;
   else
      return false;
}

//**************************
// Detects if the current device is an iPod Touch.
function DetectIpod()
{
   if (uagent.search(deviceIpod) > -1)
      return true;
   else
      return false;
}

function DetectIpad(){
	if (uagent.search(deviceIpad) > -1)
	      return true;
	   else
	      return false;
}

//**************************
// Detects if the current device is an iPhone or iPod Touch.
function DetectIphoneOrIpod()
{
    if (DetectIphone())
       return true;
    else if (DetectIpod())
       return true;
    else if (DetectIpad())
       return true;
    else
       return false;
}

$(document).ready(function() {


   $(".suser-panels .user-panel").each(function(elemento,n){
 	    var panel_aid=$(this).attr('id');
		var current_panel_1 = $('#'+panel_aid+' .panel-wraper div:first');
		display_panel(panel_aid,current_panel_1);
    });

	$('.suser-panels').cycle({
	    next:    '.move-right',
	    prev:    '.move-left',
	    pager: '.panels-pager',
	    pagerClick: bringPanelsAjax,
	    timeout:  0,
	    after: fixtheheightAfter,
	    prevNextClick: fixtheheight
	});
	
	var height = $("#panel-0").height();
	$(".suser-panels").height(height);
	
	$('.main-stream-next').live("click", function(){
        panel=$(this).parents(".user-panel");
        display_items(panel);
        fixtheheightMore(panel);
	});
	
	$(".upload_button_expand_tags a").click(function(i){
		i.preventDefault;
		$(".panels-update-form_file").hide();
		$("#tags-control").slideToggle("fast");
	});
	
	$('#tags-on-post').keyup(function(e){
		$('#edit-tags').val($(this).val());
	});

	$(".section-resource .facebook-makecomment-link").click(function(e){
		var comment=$("#comment");
		if(comment){
			comment.focus();	
		}else{
			alert('Login or register to post a comment');
		}
		
	});
	
	$(".facebook-makecomment-link").live('click',function () {
		var input1 = $(this).parents('.facebook-post');
		var input = $("#myForm",input1).children("input").prev();
		$("#myForm",input1).slideToggle("medium",function(){
			input.focus();
			$(this).submit(function(i){
			  return false;	
			});
			$(this).keyup(function(e) {
		      if(e.keyCode == 13) {
			    $(".facebook_comment_submit",input1).click();
		      }
		    });
		});
		
	});
	
	$("#TB_closeWindowButton").live('click',function(){
		$(this).parent.tb_remove();
	});
	
	$('.comment-news').live('click',function(){
		var space = $(this).parents('.stream-item-element');
		var text_input = $('.form-text-content',space);
		text_input.attr('value','');
		text_input.focus();
		
		$('#myForm',space).slideToggle('medium',function(){
			text_input.focus();
			$(this).submit(function(i){
			  return false;	
			});
			$(this).keyup(function(e) {
		      if(e.keyCode == 13) {
			    e.preventDefault;
			    $(".news-comment-submit-button",space).click();
		      }
		    });
		});
	});
	
	$('.comment-special').live('click',function(){
		var comment=$("#edit-comment");
		if(comment){
			comment.focus();	
		}else{
			alert('Login or register to post a comment');
		}
	});
	
	$('.suser-panels').height($('.suser-panels').height());
	
	$('.news-comment-submit-button').live('click',function(){
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
			}
		});
	});

	// When user submits a comment in facebook
	$(".facebook_comment_submit").live('click',function () {
		var input1=$(this).parents('.facebook-post');
		$('.display-comments-buttons',input1).show();
		var tag = $(this);
		var post_id = $(this).attr("id");
		var comment = $(this).prev("input").attr("value");
		var nid=$(this).attr("nid");		
		
		$.get(Drupal.settings.basePath+"facebook/comment",{post_id:post_id,comment:comment,mode:"create",nid:nid},function(data){
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
									
									var new_content 	= '<div id="'+data+'" class="facebook-comments clearfix" style="display:none"><a target="_blank" title="'+name+'" class="facebook-image-comment" href="'+profile_url+'"><span class="facebook-user-pic"><img class="facebook-image-comm" alt="'+name+'" src="'+pic_square+'" width="30"/></span></a>';
									    new_content  += '<span class="facebook-comment-timeline"><a target="_blank" title="'+name+'" class="facebook-comment-link" href="'+profile_url+'">'+name+'</a></span>';
											new_content  += '<span class="facebook-comment-text">'+comment+'</span><span class="facebook-date">'+date+'</span><a id="facebook-comment-delete-'+data+'" class="facebook-comment-delete" href="javascript:void(0)">delete comment</a></span></div>';
									
									// Add the new comment								
									tag.closest("div").parent().prev().append(new_content);
									var id = data;
									
									// Add the new handler to jQuery using live() function
									$('#facebook-comment-delete-'+data).live('click',function(){
										var tag = $(this).parent();
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
	
	$(".facebook_comment_submit_landing").live('click',function () {
		var input1=$(this).parents('.facebook-post');
		$('.display-comments-buttons',input1).show();
		var tag = $(this);
		var post_id = $(this).attr("id");
		var comment = $("#comment").attr("value");
		var nid=$(this).attr("nid");		
		
		$.get(Drupal.settings.basePath+"facebook/comment",{post_id:post_id,comment:comment,mode:"create",nid:nid},function(data){
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
									var comment = $("#comment").attr("value");
									
									var new_content 	= '<div id="'+data+'" class="facebook-comments clearfix"><a target="_blank" title="'+name+'" class="facebook-image-comment" href="'+profile_url+'"><span class="facebook-user-pic"><img class="facebook-image-comm" alt="'+name+'" src="'+pic_square+'" width="30"/></span></a>';
									    new_content  += '<span class="facebook-comment-timeline"><a target="_blank" title="'+name+'" class="facebook-comment-link" href="'+profile_url+'">'+name+'</a></span>';
											new_content  += '<span class="facebook-comment-text">'+comment+'</span><span class="facebook-date">'+date+'</span><a id="facebook-comment-delete-'+data+'" class="facebook-comment-delete" href="javascript:void(0)">delete comment</a></span></div>';
									
									// Add the new comment								
									$('.display-comments-buttons').append(new_content);
									var id = data;
									
									// Add the new handler to jQuery using live() function
									$('#facebook-comment-delete-'+data).live('click',function(){
										var tag = $(this).parent();
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
									
									$("#comment").attr("value","");
									$("#comment").focus();
															
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
	
	$('.show-comment-link').live('click',function(i){
		i.preventDefault;
		var universe = $(this).parents('.facebook-post-header, .item-body, .twitter-message-stream');
		$('.display-comments-buttons',universe).slideToggle('medium');
		$(this).toggleClass('expanded');
	});
	
	$(".twit-reply").live('click',function () {
	  var to = $(this).attr("id")+" "; 
	  $("#edit-status").val(to);
	  var scroll = $("#edit-status");
	  $(document).scrollTo(scroll,100);
	  $("#edit-status").focus();
	});
		
	$('.retweet').live('click',function (event){
	  var container = $(this).parents().filter('.twitter-message-stream');	
	  var message = $('.twitter-body-contains',container);
	  var to = $('.twit-reply',container).attr('id');
	  $('#edit-RT').val(1);
	  
	  $("#edit-status").val("RT "+to+" "+message.text());
	  var scroll = $("#edit-status");
	  $(document).scrollTo(scroll,100);
	  $("#edit-status").focus();
	});
	
	$('.retweet-facebook').live('click',function (event){
	  var container = $(this).parents().filter('.facebook-post');	
	  var message = $('.retweet-hide',container);
	  var to = $('.facebook-story-name',container).attr('title');
	  $('#edit-RT').val(1);
	  
	  $("#edit-status").val("RT "+to+" "+message.text());
	  var scroll = $("#edit-status");
	  $(document).scrollTo(scroll,100);
	  $("#edit-status").focus();
	});
	
	$(".url-deal a").live('click',function (element){
		
		d_deal=$(this).attr('href');
		d_price=$(this).attr('price');
		$.get(Drupal.settings.basePath+"statistics/save/deal",{deal:d_deal,price:d_price},function(data){
	      
				if (data){
																						
				}else{
		
				}
        });
	});
	
	$(".grabb-that").live('click',function (ev) {
		ev.preventDefault();
		urlcomplete = $(this).attr('href');
		myurl = encodeURIComponent(urlcomplete);
		$.getJSON(Drupal.settings.basePath+"sites/all/modules/dbusa/facebook_grabbit/trim_proxy.php",{url:myurl}, 
	        function(data)
	        { 
				
				$("#edit-status").val(data.url+' ');
				var scroll = $("#edit-status");
				$(document).scrollTo(scroll,100);
				$("#edit-status").focus();
				$('#edit-RT').val(1);
				pageTracker._trackPageview(myurl);
	        }
	    );
	 
	  
	});	
	
	$(".friend-action").live('click',function (i) {
	
	  var tag = $(this);
	  var nid= $(this).attr("uid"); // user_id
	  if (tag.text() == "Add to favorites"){
	    tag.text("Adding to favorites...");
	    $.get(Drupal.settings.basePath+"favorites/save/facebook",{type:"friend",nid:nid},function(data){
	      //Successfully added to favorites
	      //Testing if it works
				if (data){
								tag.text("Remove from favorites");
								tag.attr("class","friend_favorite-remove friend-action");
				}else{
								alert ("There was a connection problem. Try later");
				}
	    });
	  }
	  else{ //Remove from favorites
	  tag.text("Removing from favorites...");
	    $.get(Drupal.settings.basePath+"favorites/remove/facebook",{type:"friend",nid:nid},function(data){
	      //Successfully removed from favorites
	      //Testing if it works
				if (data){
								tag.text("Add to favorites");		
								tag.attr("class","friend_favorite friend-action");
				}else{								
								alert ("There was a connection problem. Try later");
				}
	    });		    
	  }  		  
	});
	
	$(".trash-facebook").live('click',function () {
	  var id = $(this).attr("face_id"); //post_id
	  var trashElement = $(this);
	  $.get(Drupal.settings.basePath+"trash/save/facebook",{id:id,type:"item"},function(data){
	      //Successfully added to favorites
	      //Testing if it works
				if (data){
					trashContainer = trashElement.parents().filter('.facebook-post');
					trashContainer.slideToggle('fast');			
				}else{
								alert ("There was a connection problem. Try later");
				}
	    });
	  
	});
	
	$(".trash-twitter").live('click',function () {
	  var id = $(this).attr("tweet_id"); //post_id
	  var trashElement = $(this);
	
	  $.get(Drupal.settings.basePath+"trash/save/facebook",{id:id,type:"item"},function(data){
	      //Successfully added to favorites
	      //Testing if it works
				if (data){
								trashContainer = trashElement.parents().filter('.twitter-message-stream');
								trashContainer.slideToggle('fast');
				}else{
								alert ("There was a connection problem. Try later");
				}
	    });
	  
	});
	
	$(".trash-item").live('click',function () {
	  var id = $(this).attr("item_id"); //post_id
	  var trashElement = $(this);
	
	  $.get(Drupal.settings.basePath+"trash/save/facebook",{id:id,type:"item"},function(data){
	      //Successfully added to favorites
	      //Testing if it works
				if (data){
					trashContainer = trashElement.parents().filter('.stream-item-element');
					trashContainer.slideToggle('fast');
				}else{
								alert ("There was a connection problem. Try later");
				}
	    });
	  
	});
	
	$(".facebook_favorite, .facebook_favorite-remove").live('click',function () {
	  var id = $(this).attr("id"); //post_id
	  var tag = $(this);
	  var nid= $(this).attr("nid");
	 
	  if (tag.text() == "Add to favorites"){
	    tag.text("Adding to favorites...");
	    $.get(Drupal.settings.basePath+"favorites/save/facebook",{id:id,type:"facebook",nid:nid},function(data){
	      //Successfully added to favorites
	      //Testing if it works
				if (data){
								tag.text("Remove from favorites");
								tag.attr("class","facebook_favorite-remove");
				}else{
								alert ("There was a connection problem. Try later");
				}
	    });
	  }
	  else{ //Remove from favorites
	  tag.text("Removing from favorites...");
	    $.get(Drupal.settings.basePath+"favorites/remove/facebook",{id:id,type:"facebook",nid:nid},function(data){
	      //Successfully removed from favorites
	      //Testing if it works
				if (data){
								tag.text("Add to favorites");		
								tag.attr("class","facebook_favorite");
				}else{								
								alert ("There was a connection problem. Try later");
				}
	    });		    
	  }  		  
	});

   $('.tooltip-deal').each(function(i){
	 var contents=$('.tooltip_deal',$(this)).html();
	
     $(this).simpletip({
	   	fixed:true,
	    persistent:true,
	    focus:true,
	    position:[-355,0],
	    content: contents
     });

   });

});




/*!
 * jQuery Cycle Plugin (with Transition Definitions)
 * Examples and documentation at: http://jquery.malsup.com/cycle/
 * Copyright (c) 2007-2009 M. Alsup
 * Version: 2.71 (11-AUG-2009)
 * Dual licensed under the MIT and GPL licenses:
 * http://www.opensource.org/licenses/mit-license.php
 * http://www.gnu.org/licenses/gpl.html
 * Requires: jQuery v1.2.6 or later
 *
 * Originally based on the work of:
 *	1) Matt Oakes
 *	2) Torsten Baldes (http://medienfreunde.com/lab/innerfade/)
 *	3) Benjamin Sterling (http://www.benjaminsterling.com/experiments/jqShuffle/)
 */
;(function($) {

var ver = '2.71';

// if $.support is not defined (pre jQuery 1.3) add what I need
if ($.support == undefined) {
	$.support = {
		opacity: !($.browser.msie)
	};
}

function log() {
	if (window.console && window.console.log)
		window.console.log('[cycle] ' + Array.prototype.join.call(arguments,' '));
	//$('body').append('<div>'+Array.prototype.join.call(arguments,' ')+'</div>');
};

// the options arg can be...
//   a number  - indicates an immediate transition should occur to the given slide index
//   a string  - 'stop', 'pause', 'resume', or the name of a transition effect (ie, 'fade', 'zoom', etc)
//   an object - properties to control the slideshow
//
// the arg2 arg can be...
//   the name of an fx (only used in conjunction with a numeric value for 'options')
//   the value true (only used in conjunction with a options == 'resume') and indicates
//     that the resume should occur immediately (not wait for next timeout)

$.fn.cycle = function(options, arg2) {
	var o = { s: this.selector, c: this.context };

    // in 1.3+ we can fix mistakes with the ready state
	if (this.length === 0 && options != 'stop') {
        if (!$.isReady && o.s) {
            log('DOM not ready, queuing slideshow');
            $(function() {
                $(o.s,o.c).cycle(options,arg2);
            });
            return this;
        }
		// is your DOM ready?  http://docs.jquery.com/Tutorials:Introducing_$(document).ready()
		log('terminating; zero elements found by selector' + ($.isReady ? '' : ' (DOM not ready)'));
		return this;
	}

    // iterate the matched nodeset
	return this.each(function() {
        var opts = handleArguments(this, options, arg2);
        if (opts === false)
            return;

		// stop existing slideshow for this container (if there is one)
		if (this.cycleTimeout)
            clearTimeout(this.cycleTimeout);
		this.cycleTimeout = this.cyclePause = 0;

		var $cont = $(this);
		var $slides = opts.slideExpr ? $(opts.slideExpr, this) : $cont.children();
		var els = $slides.get();
		if (els.length < 2) {
			log('terminating; too few slides: ' + els.length);
			return;
		}

        var opts2 = buildOptions($cont, $slides, els, opts, o);
        if (opts2 === false)
            return;

        // if it's an auto slideshow, kick it off
		if (opts2.timeout || opts2.continuous)
			this.cycleTimeout = setTimeout(function(){go(els,opts2,0,!opts2.rev)},
				opts2.continuous ? 10 : opts2.timeout + (opts2.delay||0));
	});
};

// process the args that were passed to the plugin fn
function handleArguments(cont, options, arg2) {
	if (cont.cycleStop == undefined)
		cont.cycleStop = 0;
	if (options === undefined || options === null)
		options = {};
	if (options.constructor == String) {
		switch(options) {
		case 'stop':
			cont.cycleStop++; // callbacks look for change
			if (cont.cycleTimeout)
                clearTimeout(cont.cycleTimeout);
			cont.cycleTimeout = 0;
			$(cont).removeData('cycle.opts');
			return false;
		case 'pause':
			cont.cyclePause = 1;
			return false;
		case 'resume':
			cont.cyclePause = 0;
			if (arg2 === true) { // resume now!
				options = $(cont).data('cycle.opts');
				if (!options) {
					log('options not found, can not resume');
					return false;
				}
				if (cont.cycleTimeout) {
					clearTimeout(cont.cycleTimeout);
					cont.cycleTimeout = 0;
				}
				go(options.elements, options, 1, 1);
			}
			return false;
		case 'prev':
		case 'next':
			var opts = $(cont).data('cycle.opts');
			if (!opts) {
				log('options not found, "prev/next" ignored');
				return false;
			}
			$.fn.cycle[options](opts);
			return false;
		default:
			options = { fx: options };
		};
		return options;
	}
	else if (options.constructor == Number) {
		// go to the requested slide
		var num = options;
		options = $(cont).data('cycle.opts');
		if (!options) {
			log('options not found, can not advance slide');
			return false;
		}
		if (num < 0 || num >= options.elements.length) {
			log('invalid slide index: ' + num);
			return false;
		}
		options.nextSlide = num;
		if (cont.cycleTimeout) {
			clearTimeout(cont.cycleTimeout);
			cont.cycleTimeout = 0;
		}
        if (typeof arg2 == 'string')
            options.oneTimeFx = arg2;
		go(options.elements, options, 1, num >= options.currSlide);
		return false;
	}
    return options;
};

function removeFilter(el, opts) {
	if (!$.support.opacity && opts.cleartype && el.style.filter) {
		try { el.style.removeAttribute('filter'); }
		catch(smother) {} // handle old opera versions
	}
};

// one-time initialization
function buildOptions($cont, $slides, els, options, o) {
	// support metadata plugin (v1.0 and v2.0)
	var opts = $.extend({}, $.fn.cycle.defaults, options || {}, $.metadata ? $cont.metadata() : $.meta ? $cont.data() : {});
	if (opts.autostop)
		opts.countdown = opts.autostopCount || els.length;

    var cont = $cont[0];
	$cont.data('cycle.opts', opts);
	opts.$cont = $cont;
	opts.stopCount = cont.cycleStop;
	opts.elements = els;
	opts.before = opts.before ? [opts.before] : [];
	opts.after = opts.after ? [opts.after] : [];
	opts.after.unshift(function(){ opts.busy=0; });

    // push some after callbacks
	if (!$.support.opacity && opts.cleartype)
		opts.after.push(function() { removeFilter(this, opts); });
	if (opts.continuous)
		opts.after.push(function() { go(els,opts,0,!opts.rev); });

    saveOriginalOpts(opts);

	// clearType corrections
	if (!$.support.opacity && opts.cleartype && !opts.cleartypeNoBg)
		clearTypeFix($slides);

    // container requires non-static position so that slides can be position within
	if ($cont.css('position') == 'static')
		$cont.css('position', 'relative');
	if (opts.width)
		$cont.width(opts.width);
	if (opts.height && opts.height != 'auto')
		$cont.height(opts.height);

	if (opts.startingSlide)
        opts.startingSlide = parseInt(opts.startingSlide);

    // if random, mix up the slide array
	if (opts.random) {
		opts.randomMap = [];
		for (var i = 0; i < els.length; i++)
			opts.randomMap.push(i);
		opts.randomMap.sort(function(a,b) {return Math.random() - 0.5;});
		opts.randomIndex = 0;
		opts.startingSlide = opts.randomMap[0];
	}
	else if (opts.startingSlide >= els.length)
		opts.startingSlide = 0; // catch bogus input
	opts.currSlide = opts.startingSlide = opts.startingSlide || 0;
	var first = opts.startingSlide;

    // set position and zIndex on all the slides
	$slides.css({position: 'absolute', top:0, left:0}).hide().each(function(i) {
		var z = first ? i >= first ? els.length - (i-first) : first-i : els.length-i;
		$(this).css('z-index', z)
	});

    // make sure first slide is visible
	$(els[first]).css('opacity',1).show(); // opacity bit needed to handle restart use case
	removeFilter(els[first], opts);

    // stretch slides
	if (opts.fit && opts.width)
		$slides.width(opts.width);
	if (opts.fit && opts.height && opts.height != 'auto')
		$slides.height(opts.height);

    // stretch container
	var reshape = opts.containerResize && !$cont.innerHeight();
	if (reshape) { // do this only if container has no size http://tinyurl.com/da2oa9
		var maxw = 0, maxh = 0;
		for(var j=0; j < els.length; j++) {
			var $e = $(els[j]), e = $e[0], w = $e.outerWidth(), h = $e.outerHeight();
            if (!w) w = e.offsetWidth;
            if (!h) h = e.offsetHeight;
			maxw = w > maxw ? w : maxw;
			maxh = h > maxh ? h : maxh;
		}
        if (maxw > 0 && maxh > 0)
		    $cont.css({width:maxw+'px',height:maxh+'px'});
	}

	if (opts.pause)
		$cont.hover(function(){this.cyclePause++;},function(){this.cyclePause--;});

    if (supportMultiTransitions(opts) === false)
		return false;

	// run transition init fn
	if (!opts.multiFx) {
		var init = $.fn.cycle.transitions[opts.fx];
		if ($.isFunction(init))
			init($cont, $slides, opts);
		else if (opts.fx != 'custom' && !opts.multiFx) {
			log('unknown transition: ' + opts.fx,'; slideshow terminating');
			return false;
		}
	}

	// apparently a lot of people use image slideshows without height/width attributes on the images.
	// Cycle 2.50+ requires the sizing info for every slide; this block tries to deal with that.
	var requeue = false;
	options.requeueAttempts = options.requeueAttempts || 0;
	$slides.each(function() {
        // try to get height/width of each slide
		var $el = $(this);
	    this.cycleH = (opts.fit && opts.height) ? opts.height : $el.height();
		this.cycleW = (opts.fit && opts.width) ? opts.width : $el.width();

		if ( $el.is('img') ) {
			// sigh..  sniffing, hacking, shrugging...  this crappy hack tries to account for what browsers do when
			// an image is being downloaded and the markup did not include sizing info (height/width attributes);
			// there seems to be some "default" sizes used in this situation
			var loadingIE    = ($.browser.msie  && this.cycleW == 28 && this.cycleH == 30 && !this.complete);
			var loadingFF    = ($.browser.mozilla && this.cycleW == 34 && this.cycleH == 19 && !this.complete);
			var loadingOp    = ($.browser.opera && ((this.cycleW == 42 && this.cycleH == 19) || (this.cycleW == 37 && this.cycleH == 17)) && !this.complete);
			var loadingOther = (this.cycleH == 0 && this.cycleW == 0 && !this.complete);
			// don't requeue for images that are still loading but have a valid size
			if (loadingIE || loadingFF || loadingOp || loadingOther) {
				if (o.s && opts.requeueOnImageNotLoaded && ++options.requeueAttempts < 100) { // track retry count so we don't loop forever
					log(options.requeueAttempts,' - img slide not loaded, requeuing slideshow: ', this.src, this.cycleW, this.cycleH);
					setTimeout(function() {$(o.s,o.c).cycle(options)}, opts.requeueTimeout);
					requeue = true;
					return false; // break each loop
				}
				else {
					log('could not determine size of image: '+this.src, this.cycleW, this.cycleH);
				}
			}
		}
		return true;
	});

	if (requeue)
		return false;

	opts.cssBefore = opts.cssBefore || {};
	opts.animIn = opts.animIn || {};
	opts.animOut = opts.animOut || {};

	$slides.not(':eq('+first+')').css(opts.cssBefore);
	if (opts.cssFirst)
		$($slides[first]).css(opts.cssFirst);

	if (opts.timeout) {
		opts.timeout = parseInt(opts.timeout);
		// ensure that timeout and speed settings are sane
		if (opts.speed.constructor == String)
			opts.speed = $.fx.speeds[opts.speed] || parseInt(opts.speed);
		if (!opts.sync)
			opts.speed = opts.speed / 2;
		while((opts.timeout - opts.speed) < 250) // sanitize timeout
			opts.timeout += opts.speed;
	}
	if (opts.easing)
		opts.easeIn = opts.easeOut = opts.easing;
	if (!opts.speedIn)
		opts.speedIn = opts.speed;
	if (!opts.speedOut)
		opts.speedOut = opts.speed;

	opts.slideCount = els.length;
	opts.currSlide = opts.lastSlide = first;
	if (opts.random) {
		opts.nextSlide = opts.currSlide;
		if (++opts.randomIndex == els.length)
			opts.randomIndex = 0;
		opts.nextSlide = opts.randomMap[opts.randomIndex];
	}
	else
		opts.nextSlide = opts.startingSlide >= (els.length-1) ? 0 : opts.startingSlide+1;

	// fire artificial events
	var e0 = $slides[first];
	if (opts.before.length)
		opts.before[0].apply(e0, [e0, e0, opts, true]);
	if (opts.after.length > 1)
		opts.after[1].apply(e0, [e0, e0, opts, true]);

	if (opts.next)
		$(opts.next).bind(opts.prevNextEvent,function(){return advance(opts,opts.rev?-1:1)});
	if (opts.prev)
		$(opts.prev).bind(opts.prevNextEvent,function(){return advance(opts,opts.rev?1:-1)});
	if (opts.pager)
		buildPager(els,opts);

    exposeAddSlide(opts, els);

    return opts;
};

// save off original opts so we can restore after clearing state
function saveOriginalOpts(opts) {
    opts.original = { before: [], after: [] };
    opts.original.cssBefore = $.extend({}, opts.cssBefore);
    opts.original.cssAfter  = $.extend({}, opts.cssAfter);
    opts.original.animIn    = $.extend({}, opts.animIn);
    opts.original.animOut   = $.extend({}, opts.animOut);
	$.each(opts.before, function() { opts.original.before.push(this); });
	$.each(opts.after,  function() { opts.original.after.push(this); });
};

function supportMultiTransitions(opts) {
    var i, tx, txs = $.fn.cycle.transitions;
	// look for multiple effects
	if (opts.fx.indexOf(',') > 0) {
		opts.multiFx = true;
		opts.fxs = opts.fx.replace(/\s*/g,'').split(',');
		// discard any bogus effect names
		for (i=0; i < opts.fxs.length; i++) {
			var fx = opts.fxs[i];
			tx = txs[fx];
			if (!tx || !txs.hasOwnProperty(fx) || !$.isFunction(tx)) {
				log('discarding unknown transition: ',fx);
				opts.fxs.splice(i,1);
				i--;
			}
		}
		// if we have an empty list then we threw everything away!
		if (!opts.fxs.length) {
			log('No valid transitions named; slideshow terminating.');
			return false;
		}
	}
	else if (opts.fx == 'all') {  // auto-gen the list of transitions
		opts.multiFx = true;
		opts.fxs = [];
		for (p in txs) {
			tx = txs[p];
			if (txs.hasOwnProperty(p) && $.isFunction(tx))
				opts.fxs.push(p);
		}
	}
	if (opts.multiFx && opts.randomizeEffects) {
		// munge the fxs array to make effect selection random
		var r1 = Math.floor(Math.random() * 20) + 30;
		for (i = 0; i < r1; i++) {
			var r2 = Math.floor(Math.random() * opts.fxs.length);
			opts.fxs.push(opts.fxs.splice(r2,1)[0]);
		}
		log('randomized fx sequence: ',opts.fxs);
	}
	return true;
};

// provide a mechanism for adding slides after the slideshow has started
function exposeAddSlide(opts, els) {
	opts.addSlide = function(newSlide, prepend) {
		var $s = $(newSlide), s = $s[0];
		if (!opts.autostopCount)
			opts.countdown++;
		els[prepend?'unshift':'push'](s);
		if (opts.els)
			opts.els[prepend?'unshift':'push'](s); // shuffle needs this
		opts.slideCount = els.length;

		$s.css('position','absolute');
		$s[prepend?'prependTo':'appendTo'](opts.$cont);

		if (prepend) {
			opts.currSlide++;
			opts.nextSlide++;
		}

		if (!$.support.opacity && opts.cleartype && !opts.cleartypeNoBg)
			clearTypeFix($s);

		if (opts.fit && opts.width)
			$s.width(opts.width);
		if (opts.fit && opts.height && opts.height != 'auto')
			$slides.height(opts.height);
		s.cycleH = (opts.fit && opts.height) ? opts.height : $s.height();
		s.cycleW = (opts.fit && opts.width) ? opts.width : $s.width();

		$s.css(opts.cssBefore);

		if (opts.pager)
			$.fn.cycle.createPagerAnchor(els.length-1, s, $(opts.pager), els, opts);

		if ($.isFunction(opts.onAddSlide))
			opts.onAddSlide($s);
		else
			$s.hide(); // default behavior
	};
}

// reset internal state; we do this on every pass in order to support multiple effects
$.fn.cycle.resetState = function(opts, fx) {
    fx = fx || opts.fx;
	opts.before = []; opts.after = [];
	opts.cssBefore = $.extend({}, opts.original.cssBefore);
	opts.cssAfter  = $.extend({}, opts.original.cssAfter);
	opts.animIn    = $.extend({}, opts.original.animIn);
	opts.animOut   = $.extend({}, opts.original.animOut);
	opts.fxFn = null;
	$.each(opts.original.before, function() { opts.before.push(this); });
	$.each(opts.original.after,  function() { opts.after.push(this); });

	// re-init
	var init = $.fn.cycle.transitions[fx];
	if ($.isFunction(init))
		init(opts.$cont, $(opts.elements), opts);
};

// this is the main engine fn, it handles the timeouts, callbacks and slide index mgmt
function go(els, opts, manual, fwd) {
    // opts.busy is true if we're in the middle of an animation
	if (manual && opts.busy && opts.manualTrump) {
        // let manual transitions requests trump active ones
		$(els).stop(true,true);
		opts.busy = false;
	}
    // don't begin another timeout-based transition if there is one active
	if (opts.busy)
        return;

	var p = opts.$cont[0], curr = els[opts.currSlide], next = els[opts.nextSlide];

    // stop cycling if we have an outstanding stop request
	if (p.cycleStop != opts.stopCount || p.cycleTimeout === 0 && !manual)
		return;

    // check to see if we should stop cycling based on autostop options
	if (!manual && !p.cyclePause &&
		((opts.autostop && (--opts.countdown <= 0)) ||
		(opts.nowrap && !opts.random && opts.nextSlide < opts.currSlide))) {
		if (opts.end)
			opts.end(opts);
		return;
	}

    // if slideshow is paused, only transition on a manual trigger
	if (manual || !p.cyclePause) {
        var fx = opts.fx;
		// keep trying to get the slide size if we don't have it yet
		curr.cycleH = curr.cycleH || $(curr).height();
		curr.cycleW = curr.cycleW || $(curr).width();
		next.cycleH = next.cycleH || $(next).height();
		next.cycleW = next.cycleW || $(next).width();

		// support multiple transition types
		if (opts.multiFx) {
			if (opts.lastFx == undefined || ++opts.lastFx >= opts.fxs.length)
				opts.lastFx = 0;
			fx = opts.fxs[opts.lastFx];
			opts.currFx = fx;
		}

        // one-time fx overrides apply to:  $('div').cycle(3,'zoom');
        if (opts.oneTimeFx) {
            fx = opts.oneTimeFx;
            opts.oneTimeFx = null;
        }

        $.fn.cycle.resetState(opts, fx);

        // run the before callbacks
		if (opts.before.length)
			$.each(opts.before, function(i,o) {
				if (p.cycleStop != opts.stopCount) return;
				o.apply(next, [curr, next, opts, fwd]);
			});

        // stage the after callacks
		var after = function() {
			$.each(opts.after, function(i,o) {
				if (p.cycleStop != opts.stopCount) return;
				o.apply(next, [curr, next, opts, fwd]);
			});
		};

		if (opts.nextSlide != opts.currSlide) {
            // get ready to perform the transition
			opts.busy = 1;
			if (opts.fxFn) // fx function provided?
				opts.fxFn(curr, next, opts, after, fwd);
			else if ($.isFunction($.fn.cycle[opts.fx])) // fx plugin ?
				$.fn.cycle[opts.fx](curr, next, opts, after);
			else
				$.fn.cycle.custom(curr, next, opts, after, manual && opts.fastOnEvent);
		}

        // calculate the next slide
		opts.lastSlide = opts.currSlide;
		if (opts.random) {
			opts.currSlide = opts.nextSlide;
			if (++opts.randomIndex == els.length)
				opts.randomIndex = 0;
			opts.nextSlide = opts.randomMap[opts.randomIndex];
		}
		else { // sequence
			var roll = (opts.nextSlide + 1) == els.length;
			opts.nextSlide = roll ? 0 : opts.nextSlide+1;
			opts.currSlide = roll ? els.length-1 : opts.nextSlide-1;
		}

		if (opts.pager)
			$.fn.cycle.updateActivePagerLink(opts.pager, opts.currSlide);
	}

    // stage the next transtion
    var ms = 0;
	if (opts.timeout && !opts.continuous)
        ms = getTimeout(curr, next, opts, fwd);
    else if (opts.continuous && p.cyclePause) // continuous shows work off an after callback, not this timer logic
        ms = 10;
    if (ms > 0)
        p.cycleTimeout = setTimeout(function(){ go(els, opts, 0, !opts.rev) }, ms);
};

// invoked after transition
$.fn.cycle.updateActivePagerLink = function(pager, currSlide) {
	//$(pager).find('a').removeClass('activeSlide').filter('a').eq(currSlide).addClass('activeSlide');
	$('.activeSlide',pager).removeClass('activeSlide');
	$(pager).find('a').filter('a').eq(currSlide).addClass('activeSlide');
};

// calculate timeout value for current transition
function getTimeout(curr, next, opts, fwd) {
	if (opts.timeoutFn) {
        // call user provided calc fn
		var t = opts.timeoutFn(curr,next,opts,fwd);
		if (t !== false)
			return t;
	}
	return opts.timeout;
};

// expose next/prev function, caller must pass in state
$.fn.cycle.next = function(opts) { advance(opts, opts.rev?-1:1); };
$.fn.cycle.prev = function(opts) { advance(opts, opts.rev?1:-1);};

// advance slide forward or back
function advance(opts, val) {
    var els = opts.elements;
	var p = opts.$cont[0], timeout = p.cycleTimeout;
	if (timeout) {
		clearTimeout(timeout);
		p.cycleTimeout = 0;
	}
	if (opts.random && val < 0) {
		// move back to the previously display slide
		opts.randomIndex--;
		if (--opts.randomIndex == -2)
			opts.randomIndex = els.length-2;
		else if (opts.randomIndex == -1)
			opts.randomIndex = els.length-1;
		opts.nextSlide = opts.randomMap[opts.randomIndex];
	}
	else if (opts.random) {
		if (++opts.randomIndex == els.length)
			opts.randomIndex = 0;
		opts.nextSlide = opts.randomMap[opts.randomIndex];
	}
	else {
		opts.nextSlide = opts.currSlide + val;
		if (opts.nextSlide < 0) {
			if (opts.nowrap) return false;
			opts.nextSlide = els.length - 1;
		}
		else if (opts.nextSlide >= els.length) {
			if (opts.nowrap) return false;
			opts.nextSlide = 0;
		}
	}

	if ($.isFunction(opts.prevNextClick))
		opts.prevNextClick(val > 0, opts.nextSlide, els[opts.nextSlide]);
	go(els, opts, 1, val>=0);
	return false;
};

function buildPager(els, opts) {
	var $p = $(opts.pager);
	$.each(els, function(i,o) {
		$.fn.cycle.createPagerAnchor(i,o,$p,els,opts);
	});
   $.fn.cycle.updateActivePagerLink(opts.pager, opts.startingSlide);
};

$.fn.cycle.createPagerAnchor = function(i, el, $p, els, opts) {
	var a;
	var stitle = $('.title','#'+el.id);
	if ($.isFunction(opts.pagerAnchorBuilder))
		a = opts.pagerAnchorBuilder(i,el);
	else
		a = '<a href="#" title="'+stitle.html()+'">'+stitle.html()+' </a>';
		
	if (!a)
		return;
	var $a = $(a);
	// don't reparent if anchor is in the dom
	if ($a.parents('body').length === 0) {
		var arr = [];
		if ($p.length > 1) {
			$p.each(function() {
				var $clone = $a.clone(true);
				$(this).append($clone);
				arr.push($clone);
			});
			$a = $(arr);
		}
		else {
			$a.appendTo($p);
		}
	}

	$a.bind(opts.pagerEvent, function(e) {
		e.preventDefault();
		opts.nextSlide = i;
		var p = opts.$cont[0], timeout = p.cycleTimeout;
		if (timeout) {
			clearTimeout(timeout);
			p.cycleTimeout = 0;
		}
		if ($.isFunction(opts.pagerClick))
			opts.pagerClick(opts.nextSlide, els[opts.nextSlide]);
		go(els,opts,1,opts.currSlide < i); // trigger the trans
		return false;
	});
	
	if (opts.pagerEvent != 'click')
		$a.click(function(){return false;}); // supress click
	
	if (opts.pauseOnPagerHover)
		$a.hover(function() { opts.$cont[0].cyclePause++; }, function() { opts.$cont[0].cyclePause--; } );
};

// helper fn to calculate the number of slides between the current and the next
$.fn.cycle.hopsFromLast = function(opts, fwd) {
	var hops, l = opts.lastSlide, c = opts.currSlide;
	if (fwd)
		hops = c > l ? c - l : opts.slideCount - l;
	else
		hops = c < l ? l - c : l + opts.slideCount - c;
	return hops;
};

// fix clearType problems in ie6 by setting an explicit bg color
// (otherwise text slides look horrible during a fade transition)
function clearTypeFix($slides) {
	function hex(s) {
		s = parseInt(s).toString(16);
		return s.length < 2 ? '0'+s : s;
	};
	function getBg(e) {
		for ( ; e && e.nodeName.toLowerCase() != 'html'; e = e.parentNode) {
			var v = $.css(e,'background-color');
			if (v.indexOf('rgb') >= 0 ) {
				var rgb = v.match(/\d+/g);
				return '#'+ hex(rgb[0]) + hex(rgb[1]) + hex(rgb[2]);
			}
			if (v && v != 'transparent')
				return v;
		}
		return '#ffffff';
	};
	$slides.each(function() { $(this).css('background-color', getBg(this)); });
};

// reset common props before the next transition
$.fn.cycle.commonReset = function(curr,next,opts,w,h,rev) {
	$(opts.elements).not(curr).hide();
	opts.cssBefore.opacity = 1;
	opts.cssBefore.display = 'block';
	if (w !== false && next.cycleW > 0)
		opts.cssBefore.width = next.cycleW;
	if (h !== false && next.cycleH > 0)
		opts.cssBefore.height = next.cycleH;
	opts.cssAfter = opts.cssAfter || {};
	opts.cssAfter.display = 'none';
	$(curr).css('zIndex',opts.slideCount + (rev === true ? 1 : 0));
	$(next).css('zIndex',opts.slideCount + (rev === true ? 0 : 1));
};

// the actual fn for effecting a transition
$.fn.cycle.custom = function(curr, next, opts, cb, speedOverride) {
	var $l = $(curr), $n = $(next);
	var speedIn = opts.speedIn, speedOut = opts.speedOut, easeIn = opts.easeIn, easeOut = opts.easeOut;
	$n.css(opts.cssBefore);
	if (speedOverride) {
		if (typeof speedOverride == 'number')
			speedIn = speedOut = speedOverride;
		else
			speedIn = speedOut = 1;
		easeIn = easeOut = null;
	}
	var fn = function() {$n.animate(opts.animIn, speedIn, easeIn, cb)};
	$l.animate(opts.animOut, speedOut, easeOut, function() {
		if (opts.cssAfter) $l.css(opts.cssAfter);
		if (!opts.sync) fn();
	});
	if (opts.sync) fn();
};

// transition definitions - only fade is defined here, transition pack defines the rest
$.fn.cycle.transitions = {
	fade: function($cont, $slides, opts) {
		$slides.not(':eq('+opts.currSlide+')').css('opacity',0);
		opts.before.push(function(curr,next,opts) {
			$.fn.cycle.commonReset(curr,next,opts);
			opts.cssBefore.opacity = 0;
		});
		opts.animIn	   = { opacity: 1 };
		opts.animOut   = { opacity: 0 };
		opts.cssBefore = { top: 0, left: 0 };
	}
};

$.fn.cycle.ver = function() { return ver; };

// override these globally if you like (they are all optional)
$.fn.cycle.defaults = {
	fx:			  'fade', // name of transition effect (or comma separated names, ex: fade,scrollUp,shuffle)
	timeout:	   4000,  // milliseconds between slide transitions (0 to disable auto advance)
	timeoutFn:     null,  // callback for determining per-slide timeout value:  function(currSlideElement, nextSlideElement, options, forwardFlag)
	continuous:	   0,	  // true to start next transition immediately after current one completes
	speed:		   1000,  // speed of the transition (any valid fx speed value)
	speedIn:	   null,  // speed of the 'in' transition
	speedOut:	   null,  // speed of the 'out' transition
	next:		   null,  // selector for element to use as click trigger for next slide
	prev:		   null,  // selector for element to use as click trigger for previous slide
	prevNextClick: null,  // callback fn for prev/next clicks:	function(isNext, zeroBasedSlideIndex, slideElement)
	prevNextEvent:'click',// event which drives the manual transition to the previous or next slide
	pager:		   null,  // selector for element to use as pager container
	pagerClick:	   null,  // callback fn for pager clicks:	function(zeroBasedSlideIndex, slideElement)
	pagerEvent:	  'click', // name of event which drives the pager navigation
	pagerAnchorBuilder: null, // callback fn for building anchor links:  function(index, DOMelement)
	before:		   null,  // transition callback (scope set to element to be shown):     function(currSlideElement, nextSlideElement, options, forwardFlag)
	after:		   null,  // transition callback (scope set to element that was shown):  function(currSlideElement, nextSlideElement, options, forwardFlag)
	end:		   null,  // callback invoked when the slideshow terminates (use with autostop or nowrap options): function(options)
	easing:		   null,  // easing method for both in and out transitions
	easeIn:		   null,  // easing for "in" transition
	easeOut:	   null,  // easing for "out" transition
	shuffle:	   null,  // coords for shuffle animation, ex: { top:15, left: 200 }
	animIn:		   null,  // properties that define how the slide animates in
	animOut:	   null,  // properties that define how the slide animates out
	cssBefore:	   null,  // properties that define the initial state of the slide before transitioning in
	cssAfter:	   null,  // properties that defined the state of the slide after transitioning out
	fxFn:		   null,  // function used to control the transition: function(currSlideElement, nextSlideElement, options, afterCalback, forwardFlag)
	height:		  'auto', // container height
	startingSlide: 0,	  // zero-based index of the first slide to be displayed
	sync:		   1,	  // true if in/out transitions should occur simultaneously
	random:		   0,	  // true for random, false for sequence (not applicable to shuffle fx)
	fit:		   0,	  // force slides to fit container
	containerResize: 1,	  // resize container to fit largest slide
	pause:		   0,	  // true to enable "pause on hover"
	pauseOnPagerHover: 0, // true to pause when hovering over pager link
	autostop:	   0,	  // true to end slideshow after X transitions (where X == slide count)
	autostopCount: 0,	  // number of transitions (optionally used with autostop to define X)
	delay:		   0,	  // additional delay (in ms) for first transition (hint: can be negative)
	slideExpr:	   null,  // expression for selecting slides (if something other than all children is required)
	cleartype:	   !$.support.opacity,  // true if clearType corrections should be applied (for IE)
	cleartypeNoBg: false, // set to true to disable extra cleartype fixing (leave false to force background color setting on slides)
	nowrap:		   0,	  // true to prevent slideshow from wrapping
	fastOnEvent:   0,	  // force fast transitions when triggered manually (via pager or prev/next); value == time in ms
	randomizeEffects: 1,  // valid when multiple effects are used; true to make the effect sequence random
	rev:           0,     // causes animations to transition in reverse
	manualTrump:   true,  // causes manual transition to stop an active transition instead of being ignored
	requeueOnImageNotLoaded: true, // requeue the slideshow if any image slides are not yet loaded
	requeueTimeout: 250   // ms delay for requeue
};

})(jQuery);


/*!
 * jQuery Cycle Plugin Transition Definitions
 * This script is a plugin for the jQuery Cycle Plugin
 * Examples and documentation at: http://malsup.com/jquery/cycle/
 * Copyright (c) 2007-2008 M. Alsup
 * Version:	 2.52
 * Dual licensed under the MIT and GPL licenses:
 * http://www.opensource.org/licenses/mit-license.php
 * http://www.gnu.org/licenses/gpl.html
 */
(function($) {

//
// These functions define one-time slide initialization for the named
// transitions. To save file size feel free to remove any of these that you
// don't need.
//

// scrollUp/Down/Left/Right
$.fn.cycle.transitions.scrollUp = function($cont, $slides, opts) {
	$cont.css('overflow','hidden');
	opts.before.push($.fn.cycle.commonReset);
	var h = $cont.height();
	opts.cssBefore ={ top: h, left: 0 };
	opts.cssFirst = { top: 0 };
	opts.animIn	  = { top: 0 };
	opts.animOut  = { top: -h };
};
$.fn.cycle.transitions.scrollDown = function($cont, $slides, opts) {
	$cont.css('overflow','hidden');
	opts.before.push($.fn.cycle.commonReset);
	var h = $cont.height();
	opts.cssFirst = { top: 0 };
	opts.cssBefore= { top: -h, left: 0 };
	opts.animIn	  = { top: 0 };
	opts.animOut  = { top: h };
};
$.fn.cycle.transitions.scrollLeft = function($cont, $slides, opts) {
	$cont.css('overflow','hidden');
	opts.before.push($.fn.cycle.commonReset);
	var w = $cont.width();
	opts.cssFirst = { left: 0 };
	opts.cssBefore= { left: w, top: 0 };
	opts.animIn	  = { left: 0 };
	opts.animOut  = { left: 0-w };
};
$.fn.cycle.transitions.scrollRight = function($cont, $slides, opts) {
	$cont.css('overflow','hidden');
	opts.before.push($.fn.cycle.commonReset);
	var w = $cont.width();
	opts.cssFirst = { left: 0 };
	opts.cssBefore= { left: -w, top: 0 };
	opts.animIn	  = { left: 0 };
	opts.animOut  = { left: w };
	
};
$.fn.cycle.transitions.scrollHorz = function($cont, $slides, opts) {
	$cont.css('overflow','hidden').width();
	opts.before.push(function(curr, next, opts, fwd) {
		$.fn.cycle.commonReset(curr,next,opts);
		opts.cssBefore.left = fwd ? (next.cycleW-1) : (1-next.cycleW);
		opts.animOut.left = fwd ? -curr.cycleW : curr.cycleW;
	});
	opts.cssFirst = { left: 0 };
	opts.cssBefore= { top: 0 };
	opts.animIn   = { left: 0 };
	opts.animOut  = { top: 0 };
};
$.fn.cycle.transitions.scrollVert = function($cont, $slides, opts) {
	$cont.css('overflow','hidden');
	opts.before.push(function(curr, next, opts, fwd) {
		$.fn.cycle.commonReset(curr,next,opts);
		opts.cssBefore.top = fwd ? (1-next.cycleH) : (next.cycleH-1);
		opts.animOut.top = fwd ? curr.cycleH : -curr.cycleH;
	});
	opts.cssFirst = { top: 0 };
	opts.cssBefore= { left: 0 };
	opts.animIn   = { top: 0 };
	opts.animOut  = { left: 0 };
};

// slideX/slideY
$.fn.cycle.transitions.slideX = function($cont, $slides, opts) {
	opts.before.push(function(curr, next, opts) {
		$(opts.elements).not(curr).hide();
		$.fn.cycle.commonReset(curr,next,opts,false,true);
		opts.animIn.width = next.cycleW;
	});
	opts.cssBefore = { left: 0, top: 0, width: 0 };
	opts.animIn	 = { width: 'show' };
	opts.animOut = { width: 0 };
};
$.fn.cycle.transitions.slideY = function($cont, $slides, opts) {
	opts.before.push(function(curr, next, opts) {
		$(opts.elements).not(curr).hide();
		$.fn.cycle.commonReset(curr,next,opts,true,false);
		opts.animIn.height = next.cycleH;
	});
	opts.cssBefore = { left: 0, top: 0, height: 0 };
	opts.animIn	 = { height: 'show' };
	opts.animOut = { height: 0 };
};

// shuffle
$.fn.cycle.transitions.shuffle = function($cont, $slides, opts) {
	var i, w = $cont.css('overflow', 'visible').width();
	$slides.css({left: 0, top: 0});
	opts.before.push(function(curr,next,opts) {
		$.fn.cycle.commonReset(curr,next,opts,true,true,true);
	});
	opts.speed = opts.speed / 2; // shuffle has 2 transitions
	opts.random = 0;
	opts.shuffle = opts.shuffle || {left:-w, top:15};
	opts.els = [];
	for (i=0; i < $slides.length; i++)
		opts.els.push($slides[i]);

	for (i=0; i < opts.currSlide; i++)
		opts.els.push(opts.els.shift());

	// custom transition fn (hat tip to Benjamin Sterling for this bit of sweetness!)
	opts.fxFn = function(curr, next, opts, cb, fwd) {
		var $el = fwd ? $(curr) : $(next);
		$(next).css(opts.cssBefore);
		var count = opts.slideCount;
		$el.animate(opts.shuffle, opts.speedIn, opts.easeIn, function() {
			var hops = $.fn.cycle.hopsFromLast(opts, fwd);
			for (var k=0; k < hops; k++)
				fwd ? opts.els.push(opts.els.shift()) : opts.els.unshift(opts.els.pop());
			if (fwd) {
				for (var i=0, len=opts.els.length; i < len; i++)
					$(opts.els[i]).css('z-index', len-i+count);
			}
			else {
				var z = $(curr).css('z-index');
				$el.css('z-index', parseInt(z)+1+count);
			}
			$el.animate({left:0, top:0}, opts.speedOut, opts.easeOut, function() {
				$(fwd ? this : curr).hide();
				if (cb) cb();
			});
		});
	};
	opts.cssBefore = { display: 'block', opacity: 1, top: 0, left: 0 };
};

// turnUp/Down/Left/Right
$.fn.cycle.transitions.turnUp = function($cont, $slides, opts) {
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts,true,false);
		opts.cssBefore.top = next.cycleH;
		opts.animIn.height = next.cycleH;
	});
	opts.cssFirst  = { top: 0 };
	opts.cssBefore = { left: 0, height: 0 };
	opts.animIn	   = { top: 0 };
	opts.animOut   = { height: 0 };
};
$.fn.cycle.transitions.turnDown = function($cont, $slides, opts) {
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts,true,false);
		opts.animIn.height = next.cycleH;
		opts.animOut.top   = curr.cycleH;
	});
	opts.cssFirst  = { top: 0 };
	opts.cssBefore = { left: 0, top: 0, height: 0 };
	opts.animOut   = { height: 0 };
};
$.fn.cycle.transitions.turnLeft = function($cont, $slides, opts) {
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts,false,true);
		opts.cssBefore.left = next.cycleW;
		opts.animIn.width = next.cycleW;
	});
	opts.cssBefore = { top: 0, width: 0  };
	opts.animIn	   = { left: 0 };
	opts.animOut   = { width: 0 };
};
$.fn.cycle.transitions.turnRight = function($cont, $slides, opts) {
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts,false,true);
		opts.animIn.width = next.cycleW;
		opts.animOut.left = curr.cycleW;
	});
	opts.cssBefore = { top: 0, left: 0, width: 0 };
	opts.animIn	   = { left: 0 };
	opts.animOut   = { width: 0 };
};

// zoom
$.fn.cycle.transitions.zoom = function($cont, $slides, opts) {
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts,false,false,true);
		opts.cssBefore.top = next.cycleH/2;
		opts.cssBefore.left = next.cycleW/2;
		opts.animIn	   = { top: 0, left: 0, width: next.cycleW, height: next.cycleH };
		opts.animOut   = { width: 0, height: 0, top: curr.cycleH/2, left: curr.cycleW/2 };
	});
	opts.cssFirst = { top:0, left: 0 };
	opts.cssBefore = { width: 0, height: 0 };
};

// fadeZoom
$.fn.cycle.transitions.fadeZoom = function($cont, $slides, opts) {
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts,false,false);
		opts.cssBefore.left = next.cycleW/2;
		opts.cssBefore.top = next.cycleH/2;
		opts.animIn	= { top: 0, left: 0, width: next.cycleW, height: next.cycleH };
	});
	opts.cssBefore = { width: 0, height: 0 };
	opts.animOut  = { opacity: 0 };
};

// blindX
$.fn.cycle.transitions.blindX = function($cont, $slides, opts) {
	var w = $cont.css('overflow','hidden').width();
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts);
		opts.animIn.width = next.cycleW;
		opts.animOut.left   = curr.cycleW;
	});
	opts.cssBefore = { left: w, top: 0 };
	opts.animIn = { left: 0 };
	opts.animOut  = { left: w };
};
// blindY
$.fn.cycle.transitions.blindY = function($cont, $slides, opts) {
	var h = $cont.css('overflow','hidden').height();
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts);
		opts.animIn.height = next.cycleH;
		opts.animOut.top   = curr.cycleH;
	});
	opts.cssBefore = { top: h, left: 0 };
	opts.animIn = { top: 0 };
	opts.animOut  = { top: h };
};
// blindZ
$.fn.cycle.transitions.blindZ = function($cont, $slides, opts) {
	var h = $cont.css('overflow','hidden').height();
	var w = $cont.width();
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts);
		opts.animIn.height = next.cycleH;
		opts.animOut.top   = curr.cycleH;
	});
	opts.cssBefore = { top: h, left: w };
	opts.animIn = { top: 0, left: 0 };
	opts.animOut  = { top: h, left: w };
};

// growX - grow horizontally from centered 0 width
$.fn.cycle.transitions.growX = function($cont, $slides, opts) {
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts,false,true);
		opts.cssBefore.left = this.cycleW/2;
		opts.animIn = { left: 0, width: this.cycleW };
		opts.animOut = { left: 0 };
	});
	opts.cssBefore = { width: 0, top: 0 };
};
// growY - grow vertically from centered 0 height
$.fn.cycle.transitions.growY = function($cont, $slides, opts) {
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts,true,false);
		opts.cssBefore.top = this.cycleH/2;
		opts.animIn = { top: 0, height: this.cycleH };
		opts.animOut = { top: 0 };
	});
	opts.cssBefore = { height: 0, left: 0 };
};

// curtainX - squeeze in both edges horizontally
$.fn.cycle.transitions.curtainX = function($cont, $slides, opts) {
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts,false,true,true);
		opts.cssBefore.left = next.cycleW/2;
		opts.animIn = { left: 0, width: this.cycleW };
		opts.animOut = { left: curr.cycleW/2, width: 0 };
	});
	opts.cssBefore = { top: 0, width: 0 };
};
// curtainY - squeeze in both edges vertically
$.fn.cycle.transitions.curtainY = function($cont, $slides, opts) {
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts,true,false,true);
		opts.cssBefore.top = next.cycleH/2;
		opts.animIn = { top: 0, height: next.cycleH };
		opts.animOut = { top: curr.cycleH/2, height: 0 };
	});
	opts.cssBefore = { left: 0, height: 0 };
};

// cover - curr slide covered by next slide
$.fn.cycle.transitions.cover = function($cont, $slides, opts) {
	var d = opts.direction || 'left';
	var w = $cont.css('overflow','hidden').width();
	var h = $cont.height();
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts);
		if (d == 'right')
			opts.cssBefore.left = -w;
		else if (d == 'up')
			opts.cssBefore.top = h;
		else if (d == 'down')
			opts.cssBefore.top = -h;
		else
			opts.cssBefore.left = w;
	});
	opts.animIn = { left: 0, top: 0};
	opts.animOut = { opacity: 1 };
	opts.cssBefore = { top: 0, left: 0 };
};

// uncover - curr slide moves off next slide
$.fn.cycle.transitions.uncover = function($cont, $slides, opts) {
	var d = opts.direction || 'left';
	var w = $cont.css('overflow','hidden').width();
	var h = $cont.height();
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts,true,true,true);
		if (d == 'right')
			opts.animOut.left = w;
		else if (d == 'up')
			opts.animOut.top = -h;
		else if (d == 'down')
			opts.animOut.top = h;
		else
			opts.animOut.left = -w;
	});
	opts.animIn = { left: 0, top: 0 };
	opts.animOut = { opacity: 1 };
	opts.cssBefore = { top: 0, left: 0 };
};

// toss - move top slide and fade away
$.fn.cycle.transitions.toss = function($cont, $slides, opts) {
	var w = $cont.css('overflow','visible').width();
	var h = $cont.height();
	opts.before.push(function(curr, next, opts) {
		$.fn.cycle.commonReset(curr,next,opts,true,true,true);
		// provide default toss settings if animOut not provided
		if (!opts.animOut.left && !opts.animOut.top)
			opts.animOut = { left: w*2, top: -h/2, opacity: 0 };
		else
			opts.animOut.opacity = 0;
	});
	opts.cssBefore = { left: 0, top: 0 };
	opts.animIn = { left: 0 };
};

// wipe - clip animation
$.fn.cycle.transitions.wipe = function($cont, $slides, opts) {
	var w = $cont.css('overflow','hidden').width();
	var h = $cont.height();
	opts.cssBefore = opts.cssBefore || {};
	var clip;
	if (opts.clip) {
		if (/l2r/.test(opts.clip))
			clip = 'rect(0px 0px '+h+'px 0px)';
		else if (/r2l/.test(opts.clip))
			clip = 'rect(0px '+w+'px '+h+'px '+w+'px)';
		else if (/t2b/.test(opts.clip))
			clip = 'rect(0px '+w+'px 0px 0px)';
		else if (/b2t/.test(opts.clip))
			clip = 'rect('+h+'px '+w+'px '+h+'px 0px)';
		else if (/zoom/.test(opts.clip)) {
			var top = parseInt(h/2);
			var left = parseInt(w/2);
			clip = 'rect('+top+'px '+left+'px '+top+'px '+left+'px)';
		}
	}

	opts.cssBefore.clip = opts.cssBefore.clip || clip || 'rect(0px 0px 0px 0px)';

	var d = opts.cssBefore.clip.match(/(\d+)/g);
	var t = parseInt(d[0]), r = parseInt(d[1]), b = parseInt(d[2]), l = parseInt(d[3]);

	opts.before.push(function(curr, next, opts) {
		if (curr == next) return;
		var $curr = $(curr), $next = $(next);
		$.fn.cycle.commonReset(curr,next,opts,true,true,false);
    	opts.cssAfter.display = 'block';

		var step = 1, count = parseInt((opts.speedIn / 13)) - 1;
		(function f() {
			var tt = t ? t - parseInt(step * (t/count)) : 0;
			var ll = l ? l - parseInt(step * (l/count)) : 0;
			var bb = b < h ? b + parseInt(step * ((h-b)/count || 1)) : h;
			var rr = r < w ? r + parseInt(step * ((w-r)/count || 1)) : w;
			$next.css({ clip: 'rect('+tt+'px '+rr+'px '+bb+'px '+ll+'px)' });
			(step++ <= count) ? setTimeout(f, 13) : $curr.css('display', 'none');
		})();
	});
	opts.cssBefore = { display: 'block', opacity: 1, top: 0, left: 0 };
	opts.animIn	   = { left: 0 };
	opts.animOut   = { left: 0 };
};

})(jQuery);

/**
 * 
 * Find more about the scrolling function at
 * http://cubiq.org/scrolling-div-for-mobile-webkit-turns-3/16
 *
 * Copyright (c) 2009 Matteo Spinelli, http://cubiq.org/
 * Released under MIT license
 * http://cubiq.org/dropbox/mit-license.txt
 * 
 * Version 3.0beta4 - Last updated: 2010.04.02
 * 
 */

function iScroll (el, options) {
	this.element = typeof el == 'object' ? el : document.getElementById(el);
	this.wrapper = this.element.parentNode;

	this.wrapper.style.overflow = 'hidden';
	this.wrapper.style.position = 'relative';
	this.element.style.webkitTransitionProperty = '-webkit-transform';
	this.element.style.webkitTransitionTimingFunction = 'cubic-bezier(0,0,0.25,1)';
	this.element.style.webkitTransitionDuration = '0';
	this.element.style.webkitTransform = 'translate3d(0,0,0)';

	// Get options
	this.options = {
		bounce: true,
		hScrollBar: true,
		vScrollBar: true
	};
	
	if (typeof options == 'object') {
		for (var i in options) {
			this.options[i] = options[i];
		}
	}

	this.refresh();
	
	this.element.addEventListener('touchstart', this);
	this.element.addEventListener('touchmove', this);
	this.element.addEventListener('touchend', this);
	window.addEventListener('orientationchange', this);
}

iScroll.prototype = {
	_x: 0,
	_y: 0,

	handleEvent: function (e) {
		switch (e.type) {
			case 'touchstart': this.onTouchStart(e); break;
			case 'touchmove': this.onTouchMove(e); break;
			case 'touchend': this.onTouchEnd(e); break;
			case 'webkitTransitionEnd': this.onTransitionEnd(e); break;
			case 'orientationchange': this.refresh(); this.scrollTo(0,0,'0'); break;
		}
	},

	refresh: function () {
		this.element.style.webkitTransitionDuration = '0';
		this.scrollWidth = this.wrapper.clientWidth;
		this.scrollHeight = this.wrapper.clientHeight;
		this.maxScrollX = this.scrollWidth - this.element.offsetWidth;
		this.maxScrollY = this.scrollHeight - this.element.offsetHeight;
		this.scrollX = this.element.offsetWidth > this.scrollWidth ? true : false;
		this.scrollY = this.element.offsetHeight > this.scrollHeight ? true : false;

		// Update horizontal scrollbar
		if (this.options.hScrollBar && this.scrollX) {
			this.scrollBarX = new scrollbar('horizontal', this.wrapper);			
			this.scrollBarX.init(this.scrollWidth, this.element.offsetWidth);
		} else if (this.scrollBarX) {
			this.scrollBarX = this.scrollBarX.remove();
		}

		// Update vertical scrollbar
		if (this.options.vScrollBar && this.scrollY) {
			this.scrollBarY = new scrollbar('vertical', this.wrapper);			
			this.scrollBarY.init(this.scrollHeight, this.element.offsetHeight);
		} else if (this.scrollBarY) {
			this.scrollBarY = this.scrollBarY.remove();
		}
	},

	get x() {
		return this._x;
	},

	get y() {
		return this._y;
	},

	setPosition: function (x, y) { 
		this._x = x !== null ? x : this._x;
		this._y = y !== null ? y : this._y;

		this.element.style.webkitTransform = 'translate3d(' + this._x + 'px,' + this._y + 'px,0)';

		// Move the scrollbars
		if (this.scrollBarX) {
			this.scrollBarX.setPosition(this.scrollBarX.maxScroll / this.maxScrollX * this._x);
		}
		if (this.scrollBarY) {
			this.scrollBarY.setPosition(this.scrollBarY.maxScroll / this.maxScrollY * this._y);
		}
	},
		
	onTouchStart: function(e) {
	    if (e.targetTouches.length != 1) {
	        return false;
        }

		e.preventDefault();
		e.stopPropagation();
		
		this.element.style.webkitTransitionDuration = '0';
		
		if (this.scrollBarX) {
			this.scrollBarX.bar.style.webkitTransitionDuration = '0, 250ms';
		}
		if (this.scrollBarY) {
			this.scrollBarY.bar.style.webkitTransitionDuration = '0, 250ms';
		}

		// Check if elem is really where it should be
		var theTransform = new WebKitCSSMatrix(window.getComputedStyle(this.element).webkitTransform);
		if (theTransform.m41 != this.x || theTransform.m42 != this.y) {
			this.setPosition(theTransform.m41, theTransform.m42);
		}

		this.touchStartX = e.touches[0].pageX;
		this.scrollStartX = this.x;

		this.touchStartY = e.touches[0].pageY;
		this.scrollStartY = this.y;			

		this.scrollStartTime = e.timeStamp;
		this.moved = false;
	},
	
	onTouchMove: function(e) {
		if (e.targetTouches.length != 1) {
			return false;
		}

		var leftDelta = this.scrollX === true ? e.touches[0].pageX - this.touchStartX : 0;
		var topDelta = this.scrollY === true ? e.touches[0].pageY - this.touchStartY : 0;

		if (this.x > 0 || this.x < this.maxScrollX) { 
			leftDelta = Math.round(leftDelta / 4);		// Slow down if outside of the boundaries
		}

		if (this.y > 0 || this.y < this.maxScrollY) { 
			topDelta = Math.round(topDelta / 4);		// Slow down if outside of the boundaries
		}

		if (this.scrollBarX && !this.scrollBarX.visible) {
			this.scrollBarX.show();
		}
		if (this.scrollBarY && !this.scrollBarY.visible) {
			this.scrollBarY.show();
		}

		this.setPosition(this.x + leftDelta, this.y + topDelta);

		this.touchStartX = e.touches[0].pageX;
		this.touchStartY = e.touches[0].pageY;
		this.moved = true;

		// Prevent slingshot effect
		if( e.timeStamp-this.scrollStartTime > 250 ) {
			this.scrollStartX = this.x;
			this.scrollStartY = this.y;
			this.scrollStartTime = e.timeStamp;
		}
	},
	
	onTouchEnd: function(e) {
		if (e.targetTouches.length > 0) {
			return false;
		}

		if (!this.moved) {
			var theEvent = document.createEvent('MouseEvents');
			theEvent.initMouseEvent("click", true, true, document.defaultView, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, null);
			e.changedTouches[0].target.dispatchEvent(theEvent);		
			return false;
		}
		
		var time = e.timeStamp - this.scrollStartTime;

		var momentumX = this.scrollX === true
			? this.momentum(this.x - this.scrollStartX,
							time,
							-this.x + 50,
							this.x + this.element.offsetWidth - this.scrollWidth + 50)
			: { dist: 0, time: 0 };

		var momentumY = this.scrollY === true
			? this.momentum(this.y - this.scrollStartY,
							time,
							 -this.y + /*this.scrollHeight/3*/ 50,
							this.y + this.element.offsetHeight - this.scrollHeight + /*this.scrollHeight/3*/ 50)
			: { dist: 0, time: 0 };

		if (!momentumX.dist && !momentumY.dist) {
			this.onTransitionEnd();	// I know, I know... This is lame
			return false;
		}

		var newDuration = Math.max(momentumX.time, momentumY.time);
		var newPositionX = this.x + momentumX.dist;
		var newPositionY = this.y + momentumY.dist;

		this.element.addEventListener('webkitTransitionEnd', this);

		this.scrollTo(newPositionX, newPositionY, newDuration + 'ms');

		// Move the scrollbars
		if (this.scrollBarX) {
			this.scrollBarX.scrollTo(this.scrollBarX.maxScroll / this.maxScrollX * newPositionX, newDuration + 'ms');	
		}		
		if (this.scrollBarY) {
			this.scrollBarY.scrollTo(this.scrollBarY.maxScroll / this.maxScrollY * newPositionY, newDuration + 'ms');
		}
	},
	
	onTransitionEnd: function () {
		this.element.removeEventListener('webkitTransitionEnd', this);
		this.resetPosition();

		// Hide the scrollbars
		if (this.scrollBarX) {
			this.scrollBarX.hide();
		}
		if (this.scrollBarY) {
			this.scrollBarY.hide();
		}
	},

	resetPosition: function () {
		var resetX = resetY = null;
		if (this.x > 0 || this.x < this.maxScrollX) {
			resetX = this.x >= 0 ? 0 : this.maxScrollX;
		}

		if (this.y > 0 || this.y < this.maxScrollY) {
			resetY = this.y >= 0 ? 0 : this.maxScrollY;
		}

		if (resetX !== null || resetY !== null) {
			this.scrollTo(resetX, resetY, '500ms');

			if (this.scrollBarX) {
				this.scrollBarX.scrollTo(this.scrollBarX.maxScroll / this.maxScrollX * (resetX || this.x), '500ms');
			}			
			if (this.scrollBarY) {
				this.scrollBarY.scrollTo(this.scrollBarY.maxScroll / this.maxScrollY * (resetY || this.y), '500ms');
			}
		}
	},

	scrollTo: function (destX, destY, runtime) {
		this.element.style.webkitTransitionDuration = runtime || '400ms';
		this.setPosition(destX, destY);
	},

	momentum: function (dist, time, maxDist1, maxDist2) {
		friction = 0.1;
		deceleration = 1.5;

		var speed = Math.abs(dist) / time * 1000;
		var newDist = speed * speed / (20 * friction) / 1000;

		// Proportinally reduce speed if we are outside of the boundaries 
		if (dist > 0 && maxDist1 !== undefined && newDist > maxDist1) {
			speed = speed * maxDist1 / newDist;
			newDist = maxDist1;
		}
		if (dist < 0 && maxDist2 !== undefined && newDist > maxDist2) {
			speed = speed * maxDist2 / newDist;
			newDist = maxDist2;
		}
		
		newDist = newDist * (dist < 0 ? -1 : 1);
		
		var newTime = -speed / -deceleration;
		if (newTime < 1) {	// We can't go back in time
			newTime = 1;
		}

		return { dist: Math.round(newDist), time: Math.round(newTime) };
	}
};

var scrollbar = function (dir, wrapper) {
	this.dir = dir;
	this.bar = document.createElement('div');
	this.bar.className = 'scrollbar ' + dir;
	this.bar.style.webkitTransitionTimingFunction = 'cubic-bezier(0,0,0.25,1)';
	this.bar.style.webkitTransform = 'translate3d(0,0,0)';
	this.bar.style.webkitTransitionProperty = '-webkit-transform,opacity';
	this.bar.style.webkitTransitionDuration = '0,250ms';
	this.bar.style.pointerEvents = 'none';
	this.bar.style.opacity = '0';

	wrapper.appendChild(this.bar);
}

scrollbar.prototype = {
	size: 0,
	maxSize: 0,
	maxScroll: 0,
	visible: false,
	
	init: function (scroll, size) {
		var offset = this.dir == 'horizontal' ? this.bar.offsetWidth - this.bar.clientWidth : this.bar.offsetHeight - this.bar.clientHeight;
		this.maxSize = scroll - 8;		// 8 = distance from top + distance from bottom
		this.size = Math.round(this.maxSize * this.maxSize / size) + offset;
		this.maxScroll = this.maxSize - this.size;
		this.bar.style[this.dir == 'horizontal' ? 'width' : 'height'] = (this.size - offset) + 'px';
	},
	
	setPosition: function (pos) {
		if (pos < 0) {
			pos = 0;
		} else if (pos > this.maxScroll) {
			pos = this.maxScroll;
		}

		pos = this.dir == 'horizontal' ? 'translate3d(' + Math.round(pos) + 'px,0,0)' : 'translate3d(0,' + Math.round(pos) + 'px,0)';
		this.bar.style.webkitTransform = pos;
	},
	
	scrollTo: function (pos, runtime) {
		this.bar.style.webkitTransitionDuration = (runtime || '400ms') + ',250ms';
		this.setPosition(pos);
	},
	
	show: function () {
		this.visible = true;
		this.bar.style.opacity = '1';
	},

	hide: function () {
		this.visible = false;
		this.bar.style.opacity = '0';
	},
	
	remove: function () {
		this.bar.parentNode.removeChild(this.bar);
		return null;
	}
};


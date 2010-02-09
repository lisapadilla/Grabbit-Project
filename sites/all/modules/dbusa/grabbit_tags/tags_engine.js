Drupal.behaviors.tagsEngine = function(){
  $('.bring-tags').live('click',function(i){
	var tag_node=$(this).attr('node');
	var selector = $(this);
	var parent = $(this).parents('.user-panel');
	reset_buttons(tag_node);
	$.get(Drupal.settings.basePath+"tags/display",{nid:tag_node},function(data){
		if (data){
			$('#tags-show-'+tag_node, parent).hide();
			$('#tags-show-'+tag_node, parent).html(data);
			$('#tags-show-'+tag_node, parent).show(1000);
			selector.addClass('selected');
		}else{
			alert('Oops, there was a problem connecting to the server. Please try again');
		}
	});
	
  });

  $('.close-tags').live('click', function(i){
	i.preventDefault();
    var container = $(this).parents('.twitter-message-stream, .facebook-post, .node-stream-news');
    reset_buttons_container(container);
    $(this).parent().remove();	
  });

  $(document).keyup(function(e){
    if (e.keyCode == 27) { $('.close-tags').click(); }	
  });

  $('.tags-submit-profile').live('click',function(i){
	var tag_node=$(this).attr('node');
    var parent = $(this).parents('.user-panel');
    var options = $(this).parent('.all-tags');
    
  if($('#save-tags',options).is(':checked') && $('#add-tags',options).is(':checked')){
	$('#tags-show-'+tag_node, parent).mask("Loading...");
	var tag_tags=($('#text-area-'+tag_node,options).val());
   	$.get(Drupal.settings.basePath+"tags/save",{nid:tag_node,tags:tag_tags}, function(data){
	  	if (data){
		  	$.get(Drupal.settings.basePath+"tags/profile/save",{nid:tag_node},function(data){
				if (data){
				    $('#tags-show-'+tag_node, parent).html('<span class="tags-success">The tags were added to your item and profile successfully.</span>').fadeIn(function(){
					    setTimeout(function(){
					      $(".tags-success").fadeOut("fast");
					    }, 2000);
					});
					var container = $('#tags-show-'+tag_node).parents('.twitter-message-stream, .facebook-post, .node-stream-news');
					reset_buttons_container(container);
				}else{
					alert('Oops, there was a problem connecting to the server. Please try again');
				}
			});
 	    }else{
			alert('Oops, there was a problem connecting to the server. Please try again');
		}
    }); 
  }
  else if($('#save-tags',options).is(':checked') && !$('#add-tags',options).is(':checked')){
	$('#tags-show-'+tag_node, parent).mask("Loading...");
    var tag_tags=($('#text-area-'+tag_node,options).val());
   	$.get(Drupal.settings.basePath+"tags/save",{nid:tag_node,tags:tag_tags}, function(data){
	  	if (data){
		  	$('#tags-show-'+tag_node, parent).html('<span class="tags-success">The tags were added to your item successfully.</span>').fadeIn(function(){
			    setTimeout(function(){
			      $(".tags-success").fadeOut("fast");
			    }, 2000);
			});
			var container = $('#tags-show-'+tag_node).parents('.twitter-message-stream, .facebook-post, .node-stream-news');
			reset_buttons_container(container);
 	    }else{
			alert('Oops, there was a problem connecting to the server. Please try again');
		}
    });	  
  }else if(!$('#save-tags',options).is(':checked') && $('#add-tags',options).is(':checked')){
	$('#tags-show-'+tag_node, parent).mask("Loading...");
	var tag_tags=($('#text-area-'+tag_node,options).val());
	$.get(Drupal.settings.basePath+"tags/custom/profile/save",{nid:tag_node,tags:tag_tags},function(data){
		if (data){
	      	$('#tags-show-'+tag_node, parent).html('<span class="tags-success">The tags were added to your profile successfully.</span>').fadeIn(function(){
			    setTimeout(function(){
			      $(".tags-success").fadeOut("fast");
			    }, 2000);
			});
			var container = $('#tags-show-'+tag_node).parents('.twitter-message-stream, .facebook-post, .node-stream-news');
			reset_buttons_container(container);
	    }else{
		  alert('Oops, there was a problem connecting to the server. Please try again');
		}
	});
  }

  });

}

function reset_buttons(nodeid){
	var container = $('#tags-show-'+nodeid).parents('.twitter-message-stream, .facebook-post, .node-stream-news');
	$('.iconchange',container).each(function(i){
	  $(this).removeClass('selected');
	  $('a ', this).removeClass('selected');	
	});
}

function reset_buttons_container(container){
	$('.iconchange',container).each(function(i){
	  $(this).removeClass('selected');	
	  $('a ', this).removeClass('selected');	
	});
}

/**
 * Copyright (c) 2009 Sergiy Kovalchuk (serg472@gmail.com)
 * 
 * Dual licensed under the MIT (http://www.opensource.org/licenses/mit-license.php)
 * and GPL (http://www.opensource.org/licenses/gpl-license.php) licenses.
 *  
 * Following code is based on Element.mask() implementation from ExtJS framework (http://extjs.com/)
 *
 */
;(function($){
	
	/**
	 * Displays loading mask over selected element(s). Accepts both single and multiple selectors.
	 *
	 * @param label Text message that will be displayed on top of the mask besides a spinner (optional). 
	 * 				If not provided only mask will be displayed without a label or a spinner.  	
	 * @param delay Delay in milliseconds before element is masked (optional). If unmask() is called 
	 *              before the delay times out, no mask is displayed. This can be used to prevent unnecessary 
	 *              mask display for quick processes.   	
	 */
	$.fn.mask = function(label, delay){
		$(this).each(function() {
			if(delay !== undefined && delay > 0) {
		        var element = $(this);
		        element.data("_mask_timeout", setTimeout(function() { $.maskElement(element, label)}, delay));
			} else {
				$.maskElement($(this), label);
			}
		});
	};
	
	/**
	 * Removes mask from the element(s). Accepts both single and multiple selectors.
	 */
	$.fn.unmask = function(){
		$(this).each(function() {
			$.unmaskElement($(this));
		});
	};
	
	/**
	 * Checks if a single element is masked. Returns false if mask is delayed or not displayed. 
	 */
	$.fn.isMasked = function(){
		return this.hasClass("masked");
	};

	$.maskElement = function(element, label){
	
		//if this element has delayed mask scheduled then remove it and display the new one
		if (element.data("_mask_timeout") !== undefined) {
			clearTimeout(element.data("_mask_timeout"));
			element.removeData("_mask_timeout");
		}

		if(element.isMasked()) {
			$.unmaskElement(element);
		}
		
		if(element.css("position") == "static") {
			element.addClass("masked-relative");
		}
		
		element.addClass("masked");
		
		var maskDiv = $('<div class="loadmask"></div>');
		
		//auto height fix for IE
		if(navigator.userAgent.toLowerCase().indexOf("msie") > -1){
			maskDiv.height(element.height() + parseInt(element.css("padding-top")) + parseInt(element.css("padding-bottom")));
			maskDiv.width(element.width() + parseInt(element.css("padding-left")) + parseInt(element.css("padding-right")));
		}
		
		//fix for z-index bug with selects in IE6
		if(navigator.userAgent.toLowerCase().indexOf("msie 6") > -1){
			element.find("select").addClass("masked-hidden");
		}
		
		element.append(maskDiv);
		
		if(label !== undefined) {
			var maskMsgDiv = $('<div class="loadmask-msg" style="display:none;"></div>');
			maskMsgDiv.append('<div>' + label + '</div>');
			element.append(maskMsgDiv);
			
			//calculate center position
			maskMsgDiv.css("top", Math.round(element.height() / 2 - (maskMsgDiv.height() - parseInt(maskMsgDiv.css("padding-top")) - parseInt(maskMsgDiv.css("padding-bottom"))) / 2)+"px");
			maskMsgDiv.css("left", Math.round(element.width() / 2 - (maskMsgDiv.width() - parseInt(maskMsgDiv.css("padding-left")) - parseInt(maskMsgDiv.css("padding-right"))) / 2)+"px");
			
			maskMsgDiv.show();
		}
		
	};
	
	$.unmaskElement = function(element){
		//if this element has delayed mask scheduled then remove it
		if (element.data("_mask_timeout") !== undefined) {
			clearTimeout(element.data("_mask_timeout"));
			element.removeData("_mask_timeout");
		}
		
		element.find(".loadmask-msg,.loadmask").remove();
		element.removeClass("masked");
		element.removeClass("masked-relative");
		element.find("select").removeClass("masked-hidden");
	};
 
})(jQuery);
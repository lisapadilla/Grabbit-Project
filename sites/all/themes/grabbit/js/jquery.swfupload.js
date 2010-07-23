/*
 * SWFUpload jQuery Plugin v1.0.0
 *
 * Copyright (c) 2009 Adam Royle
 * Licensed under the MIT license.
 *
 */

(function($){
	
	var defaultHandlers = ['swfupload_loaded_handler','file_queued_handler','file_queue_error_handler','file_dialog_start_handler','file_dialog_complete_handler','upload_start_handler','upload_progress_handler','upload_error_handler','upload_success_handler','upload_complete_handler','queue_complete_handler'];
	var additionalHandlers = [];
	
	$.fn.swfupload = function(){
		var args = $.makeArray(arguments);
		return this.each(function(){
			var swfu;
			if (args.length == 1 && typeof(args[0]) == 'object') {
				swfu = $(this).data('__swfu');
				if (!swfu) {
					var settings = args[0];
					var $magicUploadControl = $(this);
					var handlers = [];
					$.merge(handlers, defaultHandlers);
					$.merge(handlers, additionalHandlers);
					$.each(handlers, function(i, v){
						var eventName = v.replace(/_handler$/, '').replace(/_([a-z])/g, function(){ return arguments[1].toUpperCase(); });
						settings[v] = function() {
							var event = $.Event(eventName);
							$magicUploadControl.trigger(event, $.makeArray(arguments));
							return !event.isDefaultPrevented();
						};
					});
					$(this).data('__swfu', new SWFUpload(settings));
				}
			} else if (args.length > 0 && typeof(args[0]) == 'string') {
				var methodName = args.shift();
				swfu = $(this).data('__swfu');
				if (swfu && swfu[methodName]) {
					swfu[methodName].apply(swfu, args);
				}
			}
		});
	};
	
	$.swfupload = {
		additionalHandlers: function() {
			if (arguments.length === 0) {
				return additionalHandlers.slice();
			} else {
				$(arguments).each(function(i, v){
					$.merge(additionalHandlers, $.makeArray(v));
				});
			}
		},
		defaultHandlers: function() {
			return defaultHandlers.slice();
		},
		getInstance: function(el) {
			return $(el).data('__swfu');
		}
	};
	
})(jQuery);

function file_to_tinymce(urlcomplete){
        
		myurl = encodeURIComponent(urlcomplete);
		$.getJSON(Drupal.settings.basePath+"sites/all/modules/dbusa/facebook_grabbit/trim_proxy.php",{url:myurl}, 
	        function(data)
	        { 
				var current = $("#edit-status").val();
				var lastPos = current.length-1;
				var lastCode = current.charCodeAt(lastPos);
				if(lastCode==31){
				  $("#edit-status").val($("#edit-status").val()+data.data.url+' ');	
				}else{
					$("#edit-status").val($("#edit-status").val()+' '+data.data.url+' ');
				}
				
				var scroll = $("#edit-status");
				$("#edit-status").focus();
				$("#edit-media-link").val(data.url);
	        }
	    );
}

Drupal.behaviors.charCountDown = function(context)
{
  var limit = 140;
  var form = $("#facebook-grabbit-update-form");
  var flag = 0;
  
  $('#edit-status').keyup(function()
  {
    if(this.value.length >= limit) 
    {
      //handle the over the limit part here
      $(this).addClass('overlimit');
      $('#article-indicator').show();
      if($('#edit-status').css('height')=='55px'){
	    //$('#edit-status-wrapper').fadeOut(400, function(){
		  	$('#edit-status-wrapper').css({'background':'transparent url('+Drupal.settings.basePath+'sites/all/themes/grabbit/images/bg_textarea_big.gif) no-repeat scroll 0 0',
		                                      'height':'97px'});
		      $('.panels-update-wraper .form-submit').css('top','110px');
		      $('#counter').css('top','112px');
		      $('#counter').css('left','650px');
		      $('#counter').css('color','#FF6600');
		      
		      $('#edit-status').css('height','85px');
		      $('#facebook-grabbit-update-form').css('height','110px');
		//      $('#edit-status-wrapper').fadeIn(200);
	  //  });
      }
    } 
    else 
    {
      $(this).removeClass('overlimit');
      $('#article-indicator').hide();
      if($('#edit-status').css('height')=='85px'){
	//    $('#edit-status-wrapper').fadeOut(400, function(i){
			$('#edit-status-wrapper').css({'background':'transparent url('+Drupal.settings.basePath+'sites/all/themes/grabbit/images/bg_textarea.gif) no-repeat scroll 0 0',
		                                      'height':'73px'});
		      $('.panels-update-wraper .form-submit').css('top','88px');
		      $('#counter').css('top','59px');
		      $('#counter').css('left','705px');
		      $('#counter').css('color','#B3B3B3');
		      $('#edit-status').css('height','55px');
		      $('#facebook-grabbit-update-form').css('height','90px');
		  //    $('#edit-status-wrapper').fadeIn(200);
		  
	    //});
      }
    }
    $('#counter div').text(limit-this.value.length);
  });
}

Drupal.behaviors.frontpage = function(){
	
 $('#swfupload-control').swfupload({  
         upload_url: Drupal.settings.basePath+"yfrog/upload",  
         file_post_name: 'files',  
         file_size_limit : "1024",  
         file_types : "*.jpeg;*.bmp;*.jpg;*.png;*.gif;*.mov;*.flv;*.mp3;*.pdf;*.doc;*.rtf;*.txt;*.csv;*.ppt;*.xls",  
         file_types_description : "Image files",  
         file_upload_limit : 10,  
         flash_url : Drupal.settings.basePath+"sites/all/themes/grabbit/js/swfupload/swfupload.swf",  
         button_image_url : Drupal.settings.basePath+'sites/all/themes/grabbit/js/swfupload/wdp_buttons_upload_114x299.png',  
         button_width : 79,  
         button_height : 22,  
         button_placeholder : $('#button')[0],  
         debug: false
     })
         .bind('fileQueued', function(event, file){  
             var listitem='<li id="'+file.id+'" >'+  
                 'File: <em>'+file.name+'</em> ('+Math.round(file.size/1024)+' KB) <span class="progressvalue" ></span>'+  
                 '<div class="progressbar" ><div class="progress" ></div></div>'+  
                 '<p class="status" >Pending</p>'+  
                 '<span class="cancel" >&nbsp;</span>'+  
                 '</li>';  
             $('#log').append(listitem);  
             $('li#'+file.id+' .cancel').bind('click', function(){ //Remove from queue on cancel click  
                 var swfu = $.swfupload.getInstance('#swfupload-control');  
                 swfu.cancelUpload(file.id);  
                 $('li#'+file.id).slideUp('fast');  
             });  
             // start the upload since it's queued  
             $(this).swfupload('startUpload'); 
         }) 
         .bind('fileQueueError', function(event, file, errorCode, message){ 
             alert('Oop! Size of the file '+file.name+' is greater than the limit!'); 
         }) 
         .bind('fileDialogComplete', function(event, numFilesSelected, numFilesQueued){ 
              
         }) 
         .bind('uploadStart', function(event, file){ 
             $('#log li#'+file.id).find('p.status').text('Uploading...'); 
             $('#log li#'+file.id).find('span.progressvalue').text('0%'); 
             $('#log li#'+file.id).find('span.cancel').hide(); 
         }) 
         .bind('uploadProgress', function(event, file, bytesLoaded){ 
             //Show Progress 
             var percentage=Math.round((bytesLoaded/file.size)*100); 
             $('#log li#'+file.id).find('div.progress').css('width', percentage+'%'); 
             $('#log li#'+file.id).find('span.progressvalue').text(percentage+'%'); 
         }) 
         .bind('uploadSuccess', function(event, file, serverData){ 
             var item=$('#log li#'+file.id);  
             item.find('div.progress').css('width', '100%'); 
             item.find('span.progressvalue').text('100%');
             if(serverData!=0){
	           	var pathtofile="http://"+document.domain+Drupal.settings.basePath+"node/"+serverData; 
	             item.addClass('success').find('p.status').html('Done!!! | '+pathtofile);
	             encoded=decodeURIComponent(pathtofile);            
	             file_to_tinymce(encoded);
	             $("#log li").hide(); 
	             $(".panels-update-form_file").slideToggle("fast");
	             $("#edit-media").val(serverData);
             }else{
	           alert("Oops! there was a problem uploading your file, please try again!");
	           $("#log li").hide();
             }
             
         }) 
         .bind('uploadComplete', function(event, file){ 
             // upload has completed, try the next one in the queue 
             $(this).swfupload('startUpload');  
         })

      $(".upload_button_expand a").click(function(element){
	     $("#tags-control").hide();
	     $(".panels-update-form_file").slideToggle("fast");
	     return false;
       });

     	$('#collapse-custom').click(function(){
			               $('#collapsable-custom-form').slideToggle();
			               $(this).toggleClass('expanded');
			               return false; 
			             });
			
		$('#edit-onlysite').click(function(){
			
		  if($('#edit-onlysite').attr('checked')){
			$('#edit-onlystream').attr('checked',false);
			$('#edit-details-facebook').attr('checked',false);
			$('#edit-details-twitter').attr('checked',false);
			$('#edit-details-gmail').attr('checked',false);
			$('#edit-details-imap').attr('checked',false);
			$('#edit-details-RSS').attr('checked',false);
			$('#edit-users').attr('checked',false);
		  }
		});
		
		$('#edit-users').click(function(){
			
		  if($('#edit-users').attr('checked')){
			$('#edit-onlystream').attr('checked',false);
			$('#edit-details-facebook').attr('checked',false);
			$('#edit-details-twitter').attr('checked',false);
			$('#edit-details-gmail').attr('checked',false);
			$('#edit-details-imap').attr('checked',false);
			$('#edit-details-RSS').attr('checked',false);
			$('#edit-onlysite').attr('checked',false);
		  }
		});
		
		$('#edit-onlystream').click(function(){
			$('#edit-onlysite').attr('checked',false);
		});
		
		$('#edit-details-facebook').click(function(){
			$('#edit-onlysite').attr('checked',false);
		});
		
		$('#edit-details-twitter').click(function(){
			$('#edit-onlysite').attr('checked',false);
		});
		
		$('#edit-details-gmail').click(function(){
			$('#edit-onlysite').attr('checked',false);
		});
		
		$('#edit-details-imap').click(function(){
			$('#edit-onlysite').attr('checked',false);
		});
		
		$('#edit-details-RSS').click(function(){
			$('#edit-onlysite').attr('checked',false);
		});
		$('#block-friend_search-3 #edit-name').val('username');
		$('#block-friend_search-3 #edit-pass').val('password');
		$('#block-friend_search-3 #edit-name').click(function(){
			if($(this).val()=='username'){
				$(this).val('');
			}
		});
		
		$('#block-friend_search-3 #edit-pass').click(function(){
			$(this).val('');
			
		});
		
}
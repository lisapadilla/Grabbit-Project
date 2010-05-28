Drupal.behaviors.grabbitPanelsAdjust = function (context) {

//JQuery alerts to delete panels (with confirmation) - grabbit streams.
  $('.panel-closer').click(function(elem){
	var panel=$(this).attr('panelid');
	jConfirm("Do you really want to delete this panel? This action cannot be undone.", 'Delete Panel',function(confirm){
	if(confirm==false){
	  return 0;	// return empty to avoit panel deletion 
	}
	
	$.get(Drupal.settings.basePath+"panels/delete",{panel:panel},function(data){
		if (data){
		  $('.move-left').click();
		  $('#panel-'+panel).remove();
		  $('.panels-pager').empty();
		  $('.suser-panels').cycle('stop');
		  ct = $('.suser-panels').children().size();
				
		  if (ct>1){
		    $('.suser-panels').cycle({
			  fx:      'scrollHorz',
			  next:    '.move-right',
		      prev:    '.move-left',
			  pager: '.panels-pager',
			  timeout:  0,
		      prevNextClick: fixtheheight
		    });	
		  }else{
			$('.suser-panels div').show();
			$('.panel-closer').hide();
		  }
		}else{
		  alert("Oops! There was a connection problem. Try later later");
		}
     });
	
    });
  });

  //Only for favs
  $('.page-favorites-display .user-display-div').hide();
  var basichtml= '<div class="ladronde" style="margin-top: -7px; margin-left: 355px;"><a href="#" id="only-stories" style="padding-top: 0px; font-weight: bold; color: rgb(185, 193, 199);">show stories</a><a href="#" id="only-users" style="color: rgb(185, 193, 199); padding-top: 0px;">show friends</a></div>';
  $('.page-favorites-display .panels-pager').html(basichtml);
  
   $('#only-stories').click(function(i){
	i.preventDefault();
	$('#only-users').css('font-weight','normal');
	$(this).css('font-weight','bold');
    $('.page-favorites-display .user-display-div').hide();
    $('.page-favorites-display .stream-node, .node-stream-news').show('slow');	
   });

  
   $('#only-users').click(function(i){
	i.preventDefault();
	$('#only-stories').css('font-weight','normal');
	$(this).css('font-weight','bold');
    $('.page-favorites-display .stream-node').hide();
    $('.page-favorites-display .user-display-div, .node-stream-news').show('slow');	
   });

};
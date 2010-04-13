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


};
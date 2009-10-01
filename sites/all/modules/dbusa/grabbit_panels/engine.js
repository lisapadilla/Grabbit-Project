Drupal.behaviors.grabbitPanelsAdjust = function (context) {

  $('.panel-closer').click(function(elem){
	var panel=$(this).attr('panelid');
	jConfirm("Do you really want to delete this panel? This action cannot be undone.", 'Delete Panel',function(confirm){
	  if(confirm==false){
	    return 0;	
	  }
	
	    $.get(Drupal.settings.basePath+"panels/delete",{panel:panel},function(data){
			if (data){
				$('.move-left').click();
			  	$('#panel-'+panel).remove();
				$('.panels-pager').empty();
				$('.user-panels').cycle('stop');
				ct = $('.user-panels').children().size();
				
				if (ct>1){
					$('.user-panels').cycle({
					    fx:      'scrollHorz',
					    next:    '.move-right',
					    prev:    '.move-left',
					    pager: '.panels-pager',
					    timeout:  0,
					    prevNextClick: fixtheheight
					});	
				}else{
					$('.user-panels div').show();
					$('.panel-closer').hide();
				}
			}else{
				alert("Oops! There was a connection problem. Try later later");
			}
        });
	
    });
  });

};
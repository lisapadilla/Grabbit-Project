Drupal.behaviors.grabbitPanelsAdjust = function (context) {

  $('.panel-closer').click(function(elem){
	var panel=$(this).attr('panelid');
	
	$.get(Drupal.settings.basePath+"panels/delete",{panel:panel},function(data){
			if (data){
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

};
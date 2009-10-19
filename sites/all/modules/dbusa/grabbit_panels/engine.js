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

	var options = { 
	        success:       showResponse,
	        url:           Drupal.settings.basePath+"yfrog/upload",
	    }; 
		$('#yfrog-form').submit(function() { 
		        // inside event callbacks 'this' is the DOM element so we first 
		        // wrap it in a jQuery object and then invoke ajaxSubmit 
		        $(this).ajaxSubmit(options); 

		        // !!! Important !!! 
		        // always return false to prevent standard browser submit and page navigation 
		        return false; 
		    });
};

function showResponse(responseText, statusText)  { 
 // var url = responseText.attr("mediaurl");
  alert(responseText); 
}
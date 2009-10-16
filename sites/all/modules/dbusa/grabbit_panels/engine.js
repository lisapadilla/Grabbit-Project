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
	        url:           "http://yfrog.com/api/upload",
	        beforeSubmit:  showRequest,
	        target: "#block-views-friends-block_1"  
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
  alert("noproblem"); 
}
function showRequest(formData, jqForm, options) { 
    // formData is an array; here we use $.param to convert it to a string to display it 
    // but the form plugin does this for you automatically when it submits the data 
    var queryString = $.param(formData); 
 
    // jqForm is a jQuery object encapsulating the form element.  To access the 
    // DOM element for the form do this: 
    // var formElement = jqForm[0]; 
 
    alert('About to submit: \n\n' + queryString); 
 
    // here we could return false to prevent the form from being submitted; 
    // returning anything other than false will allow the form submit to continue 
    return true; 
}
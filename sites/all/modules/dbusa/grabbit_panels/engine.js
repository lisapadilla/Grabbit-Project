Drupal.behaviors.grabbitPanelsBehavior = function (context) {
  $('.panel-closer').click(function(element){
	 var panel=$(this).attr('panelid');
	alert(panel);
	 $.get(Drupal.settings.basePath+"panels/delete",{panel:panel},function(data){
				if (data){
					$('#panel-'+panel).slideToggle('slow');
				}else{
					alert("Oops! The server is not responding, please try again");
				}
	    });
	
  });
};
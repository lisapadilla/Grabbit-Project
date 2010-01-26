Drupal.behaviors.grabbitDeleteFacebook = function (context) {

//JQuery alerts to delete panels (with confirmation) - grabbit streams.
  $('.views-field-action-link-requestee a').click(function(elem){
	jConfirm("Do you really want to remove your facebook account on grabbit? This action cannot be undone.", 'Remove account',function(confirm){
	if(confirm==false){
	  return 0;	// return empty to avoit panel deletion 
	}
	$('.views-field-action-link-requestee').html('Removing... this may take several minutes, please wait...');
	$.get(Drupal.settings.basePath+"panels/delete",{panel:panel},function(data){
		if (data){
			$('.views-field-action-link-requestee').html('Your facebook account has been removed');
		}else{
			$('.views-field-action-link-requestee').html('There was a problem connecting to the server, please try again latter');
		}
     });
	
    });
  });


};
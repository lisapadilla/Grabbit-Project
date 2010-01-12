Drupal.behaviors.editables = function(){
	
	$(".edit-me-place").click(function (){
		$("#bio-no-edit").slideToggle();
		$("#user-profile-form").slideToggle();
		return false;
	});
	
	$("#bio-cancel").click(function (){
		$("#bio-no-edit").slideToggle();
		$("#user-profile-form").slideToggle();
		return false;
	});
	
}
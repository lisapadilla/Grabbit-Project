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
	
	$(".edit-user-tags").click(function (){
		$("#tags-info").slideToggle();
		$("#user-tags-form").slideToggle();
		return false;
	});
	
	$("#tags-cancel").click(function (){
		$("#tags-info").slideToggle();
		$("#user-tags-form").slideToggle();
		return false;
	});
	
}
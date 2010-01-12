Drupal.behaviors.editables = function(){
	
	$(".edit-me-place").click(function (){
		$(".user-profile-form").show();
		return false;
	});
	
}
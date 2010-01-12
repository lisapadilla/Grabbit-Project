Drupal.behaviors.editables = function(){
	
	$(".other-info .bio").editable({type:"textarea"});
	$(".other-info .city").editable();
	$(".other-info .state").editable();
	$(".other-info .country").editable();
	$(".other-info .websites").editable();
	
	$(".edit-me-place").click(function (){
		
		$(".other-info .city").click();
		$(".other-info .state").click();
		$(".other-info .country").click();
		$(".other-info .websites").click();
		return false;
	});
	
}
Drupal.behaviors.editables = function(){
	
	$(".other-info .bio").editable({type:"textarea"});
	$(".other-info .city").editable({type:"textfield"});
	$(".other-info .state").editable({type:"textfield"});
	$(".other-info .country").editable({type:"textfield"});
	$(".other-info .websites").editable({type:"textfield"});
	
	$(".edit-me-place").click(function (){
		
		$(".other-info .city").click();
		$(".other-info .state").click();
		$(".other-info .country").click();
		$(".other-info .websites").click();
		return false;
	});
	
}
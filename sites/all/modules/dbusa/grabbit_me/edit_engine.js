Drupal.behaviors.editables = function(){
	
	$(".other-info .bio").editable({type:"textarea"});
	$(".other-info .city").editable({submitBy:'none'});
	$(".other-info .state").editable({submitBy:'none'});
	$(".other-info .country").editable({submitBy:'none'});
	$(".other-info .websites").editable({submitBy:'none'});
	
	$(".edit-me-place").click(function (){
		
		$(".other-info .city").click();
		$(".other-info .state").click();
		$(".other-info .country").click();
		$(".other-info .websites").click();
		return false;
	});
	
}
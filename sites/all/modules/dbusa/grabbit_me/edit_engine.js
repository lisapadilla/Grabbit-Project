Drupal.behaviors.editables = function(){
	
	$(".bio").editable({type:"textarea"});
	
	$(".edit-me-place").click(function (){
		$(".bio").click();
	});
	
}
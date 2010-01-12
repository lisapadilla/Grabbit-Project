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
	
	$("#bio-submit").click(function (){
		
		webs=$("#webs").value();
		country=$("#country").value();
		state=$("#state").value();
		city=$("#city").value();
		bio=$("#bio").html();
		
		$.get(Drupal.settings.basePath+"ajax/save/bio",{bio:bio,city:city,state:state,country:country,web:webs},function(data){
			if (data){
				alert(data);
			}
		});
		
		return false;
	});
	
	$("#edit-user-tags").click(function (){
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
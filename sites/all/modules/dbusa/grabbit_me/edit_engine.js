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
		
		webs=$("#webs").val();
		country=$("#country").val();
		state=$("#state").val();
		city=$("#city").val();
		bio=$("#bio").val();
		$.get(Drupal.settings.basePath+"ajax/save/bio",{bio:bio,city:city,state:state,country:country,web:webs},function(data){
			if (data){
				alert(data);
				$(".other-info .websites").html(webs);
				$(".other-info .country").html(country);
				$(".other-info .state").html(state);
				$(".other-info .city").html(city);
				$(".other-info .bio").html(bio);
				$("#bio-no-edit").slideToggle();
				$("#user-profile-form").slideToggle();
			}else{
				alert("Problem connecting with the server, please try to update your settings latter.");
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
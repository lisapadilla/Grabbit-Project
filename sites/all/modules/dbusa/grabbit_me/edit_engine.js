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
		name=$("#name").val();
		$.get(Drupal.settings.basePath+"ajax/save/bio",{name:name,bio:bio,city:city,state:state,country:country,web:webs},function(data){
			if (data){
				
				$(".other-info .websites").html(webs);
				$(".other-info .country").html(country);
				$(".other-info .state").html(state);
				$(".other-info .city").html(city);
				$(".other-info .bio").html(bio);
				$(".other-info .display").html("<strong>"+name+"</strong>");
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
	
	$("#tags-submit").click(function (){
		
		feeds=$("#feeds").val();
		hobbies=$("#hobbies").val();
		topics=$("#topics").val();
		interests=$("#interests").val();
		
		$.get(Drupal.settings.basePath+"ajax/save/tags",{feeds:feeds,hobbies:hobbies,topics:topics,interests:interests},function(data){
			if (data){
				alert(data);
				$("#feeds").html(feeds);
				$("#hobbies").html(hobbies);
				$("#topics").html(topics);
				$("#interests").html(interests);
				
				$("#tags-info").slideToggle();
				$("#user-tags-form").slideToggle();
				
			}else{
				alert("Problem connecting with the server, please try to update your settings latter.");
			}
		});
		
		return false;
	});
	
}
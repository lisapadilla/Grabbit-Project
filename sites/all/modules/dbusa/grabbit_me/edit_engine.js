Drupal.behaviors.editables = function(){
	
	$(".edit-me-place").click(function (){
		$("#bio-no-edit").slideToggle("fast");
		$("#user-profile-form").slideToggle("fast");
		return false;
	});
	
	$("#bio-cancel").click(function (){
		$("#bio-no-edit").slideToggle("fast");
		$("#user-profile-form").slideToggle("fast");
		return false;
	});
	
	$("#bio-submit").click(function (){
		
		webs=$("#webs").val();
		country=$("#country").val();
		state=$("#state").val();
		city=$("#city").val();
		bio=$("#bio").val();
		name=$("#name").val();
		$('#user-profile-form').mask("Saving...");
		$.get(Drupal.settings.basePath+"ajax/save/bio",{name:name,bio:bio,city:city,state:state,country:country,web:webs},function(data){
			if (data){
				
				$(".other-info .websites").html(webs);
				$(".other-info .country").html(country);
				$(".other-info .state").html(state);
				$(".other-info .city").html(city);
				$(".other-info .bio").html(bio);
				$(".other-info .display").html("<strong>"+name+"</strong>");
				$("#bio-no-edit").slideToggle("fast");
				$("#user-profile-form").slideToggle("fast");
				$('#user-profile-form').unmask();
			}else{
				alert("Problem connecting with the server, please try to update your settings latter.");
			}
		});
		
		return false;
	});
	
	$("#edit-user-tags").click(function (){
		$("#tags-info").slideToggle("fast");
		$("#user-tags-form").slideToggle("fast");
		return false;
	});
	
	$("#tags-cancel").click(function (){
		$("#tags-info").slideToggle("fast");
		$("#user-tags-form").slideToggle("fast");
		return false;
	});
	
	$("#tags-submit").click(function (){
		
		feeds=$("#feeds").val();
		hobbies=$("#hobbies").val();
		topics=$("#topics").val();
		interests=$("#interests").val();
		$('#user-tags-form').mask("Saving...");
		$.get(Drupal.settings.basePath+"ajax/save/tags",{feeds:feeds,hobbies:hobbies,topics:topics,interests:interests},function(data){
			if (data){
				$("#tags-info .feeds-keywords").html("<h3>Feeds keywords: </h3>"+feeds);
				$("#tags-info .hobbies").html("<h3>Hobbies: </h3>"+hobbies);
				$("#tags-info .topics").html("<h3>Topics: </h3>"+topics); 
				$("#tags-info .interests").html("<h3>Interests: </h3>"+interests);
				
				$("#tags-info").slideToggle("fast");
				$("#user-tags-form").slideToggle("fast");
		        $('#user-tags-form').unmask();		
			}else{
				alert("Problem connecting with the server, please try to update your settings latter.");
			}
		});
		
		return false;
	});
	
	  
     var btnUpload=$('#upload');  
     var status=$('#status');  
     new AjaxUpload(btnUpload, {  
         action: Drupal.settings.basePath+'ajax/upload/file',  
         //Name of the file input box  
         name: 'uploadfile',  
         onSubmit: function(file, ext){  
             if (! (ext && /^(jpg|png|jpeg|gif)$/.test(ext))){  
                   // check for valid file extension  
                 status.text('Only JPG, PNG or GIF files are allowed');  
                 return false;  
             }  
             status.text('Uploading...');  
         },  
         onComplete: function(file, response){  
             //On completion clear the status  
             status.text('');  
             //Add uploaded file to list  
             if(response){
                 $('.image').html(response);  
                 $("#bio-no-edit").slideToggle("fast");
				 $("#user-profile-form").slideToggle("fast");
             } else{  
                 //$('<li></li>').appendTo('#files').text(response).addClass('error');
                 alert("There was a problem connecting with the server, try again latter");  
             }  
         }  
     });

     $('#me-more').click(function(i){
	   var page = $(this).attr('page');
	   var pid  = $(this).attr('pid');
	   var link = $(this);
	   $.get(Drupal.settings.basePath+"me/pagination",{page:page,pid:pid},function(data){
			if (data){
				$(data).insertBefore(link);
				link.attr('page',page+1);
			}else{
				alert("Problem connecting with the server, please try again latter.");
			}
		});   
     });

}
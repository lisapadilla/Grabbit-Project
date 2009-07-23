$(document).ready(function() {
	$(".facebook-makecomment-link").click(function () {
	  $(this).next("div").slideToggle("slow"); 
	});
	
	$(".twit-reply").click(function () {
	  var to = $(this).attr("id"); 
	  $("#edit-status").val(to);
	  $("#edit-status").focus();
	});		
	
	$(".twitter_favorite").click(function () {
	  var id = $(this).attr("id");
	  var tag = $(this);
	  
	  if (tag.text() == "Add to favorites"){
	    tag.text("Adding to favorites...");
	    $.get(Drupal.settings.basePath+"twitter/addfavorite",{id:id,mode:"create"},function(data){
	      //Successfully added to favorites
	      //Testing if it works
	      tag.text("Remove from favorites");		      
	    });
	  }
	  else{ //Remove from favorites
	  tag.text("Removing from favorites...");
	    $.get(Drupal.settings.basePath+"twitter/addfavorite",{id:id,mode:"destroy"},function(data){
	      //Successfully removed from favorites
	      //Testing if it works
	      tag.text("Add to favorites");		      
	    });		    
	  }
	  		  
	});		
	
	});
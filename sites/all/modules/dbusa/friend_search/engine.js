$(document).ready(function() {
	
	$(".friend-action").live('click',function (i) {
	
	  var tag = $(this);
	  var nid= $(this).attr("uid"); // user_id
	  if (tag.text() == "Add to favorites"){
	    tag.text("Adding to favorites...");
	    $.get(Drupal.settings.basePath+"favorites/save/facebook",{type:"friend",nid:nid},function(data){
	      //Successfully added to favorites
	      //Testing if it works
				if (data){
								tag.text("Remove from favorites");
								tag.attr("class","friend_favorite-remove friend-action");
				}else{
								alert ("There was a connection problem. Try later");
				}
	    });
	  }
	  else{ //Remove from favorites
	  tag.text("Removing from favorites...");
	    $.get(Drupal.settings.basePath+"favorites/remove/facebook",{type:"friend",nid:nid},function(data){
	      //Successfully removed from favorites
	      //Testing if it works
				if (data){
								tag.text("Add to favorites");		
								tag.attr("class","friend_favorite");
				}else{								
								alert ("There was a connection problem. Try later");
				}
	    });		    
	  }  		  
	});
	
});
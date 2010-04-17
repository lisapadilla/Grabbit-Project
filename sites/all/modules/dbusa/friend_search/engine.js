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
								tag.attr("class","friend_favorite friend-action");
				}else{								
								alert ("There was a connection problem. Try later");
				}
	    });		    
	  }  		  
	});
	
	$('.grabbit-container .all-friends-button').click(function(i){
		$('.grabbit-container .views-row').show();
		$(this).addClass('selected');
		$('.g-friends-button').removeClass('selected');
		i.preventDefault();
		
	});
	
	$('.grabbit-container .g-friends-button').click(function(i){
		$('.grabbit-container .views-row').hide();
		$('.grabbit-container .grabbit-fr').show('slow');
		$(this).addClass('selected');
		$('.all-friends-button').removeClass('selected');
		i.preventDefault();
	});
	
	$('.facebook-container .all-friends-button').click(function(i){
		$('.facebook-container .views-row').show();
		i.preventDefault();
		$(this).addClass('selected');
		$('.g-friends-button').removeClass('selected');
	});
	
	$('.facebook-container .g-friends-button').click(function(i){
		$('.facebook-container .views-row').hide();
		$('.facebook-container .joined-grabbit').show('slow');
		i.preventDefault();
		$(this).addClass('selected');
		$('.all-friends-button').removeClass('selected');
	});
	
	$('.twitter-container .all-friends-button').click(function(i){
		$('.twitter-container .views-row').show();
		i.preventDefault();
		$(this).addClass('selected');
		$('.g-friends-button').removeClass('selected');
		
	});
	
	$('.twitter-container .g-friends-button').click(function(i){
		$('.twitter-container .views-row').hide();
		$('.twitter-container .joined-grabbit').show('slow');
		i.preventDefault();
		$(this).addClass('selected');
		$('.all-friends-button').removeClass('selected');
		
	});
	
	
});
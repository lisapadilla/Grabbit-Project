Drupal.behaviors.article = function(){

  $(".grabb-that").click(function(ev){
		ev.preventDefault();
		urlcomplete = window.location;
		myurl = encodeURIComponent(urlcomplete);
		$.getJSON("http://api.tr.im/api/trim_url.json?url=" + myurl, 
	        function(data)
	        { 
				alert(data);
				$("#edit-status").val(data.url+' ');
				$("#edit-status").focus();
				$('#edit-RT').val(1);
				pageTracker._trackPageview(myurl);
	        }
	    );
  });

  $(".comment-news").click(function(eve){
	var comment=$("#edit-comment");
	if(comment){
		comment.focus();	
	}else{
		alert('Login or register to post a comment');
	}
  });

  	$(".trash-item").live('click',function () {
	  var id = $(this).attr("item_id"); //post_id
	  var trashElement = $(this);
	
	  $.get(Drupal.settings.basePath+"trash/save/facebook",{id:id,type:"item"},function(data){
	      //Successfully added to favorites
	      //Testing if it works
				if (data){
					alert ("Item trashed");
				}else{
					alert ("There was a connection problem. Try later");
				}
	    });
	  
	});

}
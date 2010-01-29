Drupal.behaviors.article = function(){

  $(".grabb-that").click(function(ev){
		ev.preventDefault();
		urlcomplete = window.location;
		myurl = encodeURIComponent(urlcomplete);
		$.getJSON("http://json-tinyurl.appspot.com/?url=" + myurl + "&callback=?", 
	        function(data)
	        { 
				
				$("#edit-status").val(data.tinyurl+' ');
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

}
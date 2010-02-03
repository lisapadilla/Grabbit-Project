Drupal.behaviors.article = function(){

  $(".grabb-that").click(function(ev){
		ev.preventDefault();
		urlcomplete = window.location;
		myurl = encodeURIComponent(urlcomplete);
	    $.getJSON(Drupal.settings.basePath+"sites/all/modules/dbusa/facebook_grabbit/trim_proxy.php",{url:myurl},function(data){
					if (data){
						$("#edit-status").val(data.url+' ');
						$("#edit-status").focus();
						$('#edit-RT').val(1);
						pageTracker._trackPageview(myurl);
					}else{
						alert ("There was a connection problem. Try later");
					}
		    });
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

Drupal.behaviors.imageResizer = function()
{
  $('#content-area .news-body img').each(function(i){
    if ( $(this).width() > 532 )
    {
      $(this).width(532);
    }
    else if ( $(this).width() > 266 )
    {
      $(this).width(266);
    }
  });
}
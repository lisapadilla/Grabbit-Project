Drupal.behaviors.article = function(){

  $("#article-news .trash-item").click(function(ev){
	alert("hola");
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

}
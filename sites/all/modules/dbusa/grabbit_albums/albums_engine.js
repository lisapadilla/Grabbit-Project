Drupal.behaviors.albums = function(){
  $("#scroll-album").scrollable({size:1,clickable:false});

  $("#album-type").change(function(e){
    var val=$(this).val();
	
	var url=Drupal.settings.new_url+val;
	
	top.location = url;
	
  });

}
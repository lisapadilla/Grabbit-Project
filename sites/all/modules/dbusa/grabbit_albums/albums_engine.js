Drupal.behaviors.albums = function(){
  $("#scroll-album").scrollable({size:1,clickable:false});

  alert(Drupal.settings.new_val);

  $("#album-type").change(function(e){
    var val=$(this).val();
	top.location = val;
	
  });

}
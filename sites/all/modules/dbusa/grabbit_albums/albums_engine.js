Drupal.behaviors.albums = function(){
  $("#scroll-album").scrollable({size:1,clickable:false});

  $("#album-type").val(Drupal.settings.grabbit_1);

  $('.title').html(Drupal.settings.grabbit_2+"'s "+Drupal.settings.grabbit_1);

  $("#album-type").change(function(e){
    var val=$(this).val();
	top.location = val;
  });

}
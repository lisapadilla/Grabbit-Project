Drupal.behaviors.grabbitSearchEngine = function (context) {
  var count=0;
  var basic=0;
  $('.stream-node').each(function(i){
	count++;
	if(count<=10){
		basic++;
	}else{
		$(this).hide();
	}
  });

  $('a.grabbit-results').html('Results: '+basic+' of '+count);

  if(count > basic){
	$('#content-area').append('<span style="position: absolute;"><a href="#">MORE</a></span>');
}

};
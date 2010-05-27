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
	$('#content-area').append('<span style="position: relative; margin-left: 280px; color: rgb(153, 153, 153); font-size: 14px; text-decoration: none;"><a href="#" style="position: relative; margin-left: 280px; color: rgb(153, 153, 153); font-size: 14px; text-decoration: none;">MORE</a></span>');
}

};
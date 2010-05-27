Drupal.behaviors.grabbitSearchEngine = function (context) {
  var count=0;
  var basic=0;
  $('.twitter-message-stream').each(function(i){
	count++;
	if(count<=10){
		continue;
		basic++;
	}else{
		i.hide();
	}
  });

  $('a.grabbit-results').html('Results: '+basic+' of '+count);

};
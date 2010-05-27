Drupal.behaviors.grabbitSearchEngine = function (context) {
  var count=0;
  var basic=0;
  $('.panel-favorites div').each(function(i){
	count++;
	if(count<=10){
		basic++;
	}else{
		$(this).hide();
	}
  });

  $('a.grabbit-results').html('Results: '+basic+' of '+count);

};
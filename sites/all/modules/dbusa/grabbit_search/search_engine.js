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
	$('#content-area').append('<span style="position: relative; margin-left: 280px; color: rgb(153, 153, 153); font-size: 14px; text-decoration: none;"><a href="#" id="moremore" style="position: relative; color: rgb(153, 153, 153); font-size: 14px; text-decoration: none;">more</a></span>');
  }
  
  $('#moremore').click(function(i){
	i.preventDefault();
	var hidden=0;
	$('.stream-node:hidden').each(function(i){
		hidden++;
		if(hidden<=10){
			$(this).show();
		}
	  });
	
	basic = basic+hidden;
    $('a.grabbit-results').html('Results: '+basic+' of '+count);
    var visibles=0;
   	$('.stream-node:visible').each(function(i){
		visibles++;
	});
	
    $('.suser-panels').height(visibles*76);	
  });
};
Drupal.behaviors.resource = function()
{
  var uname = Drupal.settings.user_name;
  var type  = Drupal.settings.user_type;
  if(uname){
	$('h1.title').html(uname + "&#8217;s "+type);	
  }
  
  $('.facebook-attachment img').each(function(){
    if ( $(this).width() > 596 )
    {
      $(this).width(596);
    }
  });

  var item=$('#content');
  calculateDeals(item);

}
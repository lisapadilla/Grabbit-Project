Drupal.behaviors.resource = function()
{
  var uname = Drupal.settings.user_name;
  if(uname){
	$('h1.title').html(uname + "&#8217;s Facebook");	
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
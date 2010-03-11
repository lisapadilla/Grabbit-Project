Drupal.behaviors.resource = function()
{
  $('.facebook-attachment img').each(function(){
    if ( $(this).width() > 596 )
    {
      $(this).width(596);
    }
  });
}
Drupal.behaviors.tooltips = function()
{
  $('#article-news').addClass('tooltipwraper');
  $(".tooltipwraper a[title]").tooltip('#tooltip'); 
}
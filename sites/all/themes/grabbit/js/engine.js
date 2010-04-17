Drupal.behaviors.tooltips = function()
{
  $('#article-news').addClass('tooltipwraper');
  $(".tooltipwraper a[title]").tooltip('#tooltip'); 

  $("#edit-taxonomy-tags-3").removeClass('form-autocomplete');
}
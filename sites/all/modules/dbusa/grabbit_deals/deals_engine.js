Drupal.behaviors.deals = function()
{
  // calculate deals on visible stream nodes
  streamVisibles('#panel-0', '.stream-node', calculateDeals, 1500);
  
  // deals box behaviors
  $('.url-deal a').live('click', function(i){
    i.preventDefault();
    var nid = $(this).attr('node');
    var anch = $(this);
    var parent = $(this).parents('.user-panel'); // reducir el universo a solo el panel que estoy viendo
    
    $.get(Drupal.settings.basePath+"deals/display",{nid:nid},function(data){
       if (data)
       {
           $('#tags-show-'+nid, parent).html(data);
           anch.toggleClass('selected');
       }
    });
  });
  
  $('.deals-display .close').live('click', function(i){
    i.preventDefault();
    $(this).parent().remove();
  });
  
  $(document).keyup(function(e){
    if (e.keyCode == 27) { $('.deals-display .close').click(); }	
  });
}

function calculateDeals( item )
{
  var nid = $('.url-deal a', item).attr('node');
  
  $.get(Drupal.settings.basePath+"deals/calculate",{nid:nid},function(data){
     if (data)
     {
        $('.url-deal', item).show('slow');
     }
  });
}
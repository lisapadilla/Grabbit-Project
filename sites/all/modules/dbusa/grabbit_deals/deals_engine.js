Drupal.behaviors.deals = function()
{
  // calculate deals on visible stream nodes
  $('.user-panel').each(function(i){
	streamVisibles('#'+$(this).attr('id'), '.stream-node', calculateDeals, 1500);
  });
  
  // deals box behaviors
  $('.url-deal a').live('click', function(i){
	$('.bring-tags').removeClass('selected');
    i.preventDefault();
    if ( $(this).hasClass('selected') )
    {
      $('.deals-display .close').click();
    }
    else
    { 
      var nid = $(this).attr('node');
      var anch = $(this);
      var parent = $(this).parents('.user-panel, #content-area'); // reducir el universo a solo el panel que estoy viendo
      reset_buttons(nid);
      $.get(Drupal.settings.basePath+"deals/display",{nid:nid},function(data){
         if (data)
         {
           $('.album-control').hide();
  	       $('#tags-show-'+nid, parent).hide();
             $('#tags-show-'+nid, parent).html(data);
             $('#tags-show-'+nid, parent).show(600);
             anch.toggleClass('selected');
         }
      });  
    }
    
  });
  
  $('.deals-display .close').live('click', function(i){
    i.preventDefault();
    var container = $(this).parents('.twitter-message-stream, .facebook-post, .node-stream-news');
    reset_buttons_container(container);
    $('.album-control').show();
    $('.url-deal a').removeClass('selected');
    $(this).parent().hide(500, function(i){
	  $(i).parent().remove();
	});
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
        $('.url-deal a', item).toggleClass('available');
     }
  });
}
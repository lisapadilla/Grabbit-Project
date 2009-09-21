$(document).ready(function() {
	
  $(".deal-url").click(function (element){
	
	d_deal=$(this).attr('href');
	d_price=parseFloat($('.field-field-price .field-item').html());
	$.get(Drupal.settings.basePath+"statistics/save/deal",{deal:d_deal,price:d_price},function(data){
      
			if (data){									
			}else{
	
			}
    });
  });
});
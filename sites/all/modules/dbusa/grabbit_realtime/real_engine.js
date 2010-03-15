Drupal.behaviors.realtime = function(){
	
	setInterval("execute_realtime()", 3000);
	
}

function execute_realtime(){
	
	$(".suser-panels .user-panel").each(function(){
		var first = $(".panel-wraper div:first",$(this));
		var second = $(".panel-wraper",$(this));
		pid=$(this).attr('pid');
		if(!first.attr('paid')){ // es un panel sin procesar
		  $.get(Drupal.settings.basePath+"execute/realtime",{pannel:pid,last_nid:first.attr('id')},function(data){
			if (data){
				second.prepend(
					$(data).hide().fadeIn(3000)
				);
				Drupal.behaviors.initThickbox(data);
		        Drupal.behaviors.tooltips(data);
			    Drupal.flagLink(data);
				
				$('a,area,input', data).filter('.thickbox:not(.initThickbox-processed)').addClass('initThickbox-processed').click(function() {
			      var t = this.title || this.name || null;
			      var a = this.href || this.alt;
			      var g = this.rel || false;
			      tb_show(t,a,g);
			      this.blur();
			      return false;
			    });
				
			}
		  });
		}
			
	});
		
}

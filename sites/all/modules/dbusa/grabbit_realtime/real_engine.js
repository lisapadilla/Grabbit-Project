Drupal.behaviors.realtime = function(){
	
	setInterval("execute_realtime()", 60000);
	//setInterval("execute_realtime()", 300000);
	
}

function execute_realtime(){
	
	$(".suser-panels .user-panel").each(function(){
		var first = $(".panel-wraper div:first",$(this));
		var second = $(".panel-wraper",$(this));
		pid=$(this).attr('pid');
	  	$.get(Drupal.settings.basePath+"execute/realtime",{pannel:pid,last_nid:first.attr('id')},function(data){
			if (data){
				second.prepend(
					$(data).hide().fadeIn('slow')
				);
			}
		});
			
	});
		
}

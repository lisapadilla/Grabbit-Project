Drupal.behaviors.realtime = function(){
	
	setInterval("execute_realtime()", 60000);
	//setInterval("execute_realtime()", 300000);
	
}

function execute_realtime(){
	
	$(".user-panel").each(function(){
		first = $(".panel-wraper div:first",$(this));
	  	$.get(Drupal.settings.basePath+"execute/realtime",{pannel:$(this).attr('pid'),last_nid:first.attr('id')},function(data){
			if (data){
				$(this).prepend(data);
			}
		});
			
	});
		
}

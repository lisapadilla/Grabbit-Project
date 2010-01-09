Drupal.behaviors.realtime = function(){
	
	setInterval("execute_realtime()", 60000);
	//setInterval("execute_realtime()", 300000);
	
}

function execute_realtime(){
	
	$(".user-panel").each(function(){
	  	$.get(Drupal.settings.basePath+"execute/realtime",{pannel:$(this).attr('pid')},function(data){
			if (data){
				alert (data);
			}
		});
			
	});
		
}

Drupal.behaviors.realtime = function(){
	
	setInterval("execute_realtime()", 3000);
	//setInterval("execute_realtime()", 300000);
	
}

function execute_realtime(){
	
	$(".user-panel").each(function(i){
	  	$.get(Drupal.settings.basePath+"execute/realtime",{user:"uid",pannel:$(i).attr('pid')},function(data){
			if (data){
				alert (data);
			}
		});	
	});
		
}

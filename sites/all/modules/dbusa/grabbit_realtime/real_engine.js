Drupal.behaviors.realtime = function(){
	
	setInterval("execute_realtime()", 3000);
	//setInterval("execute_realtime()", 300000);
	
}

function execute_realtime(){
	
	$(".user-panel").each(obj,function(){
	  	$.get(Drupal.settings.basePath+"execute/realtime",{user:"uid",pannel:this},function(data){
			if (data){
				alert (data);
			}
		});	
	});
		
}

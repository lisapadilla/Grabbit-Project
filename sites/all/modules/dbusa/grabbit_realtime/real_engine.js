Drupal.behaviors.realtime = function(){
	
	setInterval("execute_realtime()", 15000);
	//setInterval("execute_realtime()", 300000);
	
}

function execute_realtime(){
	
	$(".user-panel").each(function(){
		alert($(this).attr('pid'));
	  	$.get(Drupal.settings.basePath+"execute/realtime",{user:"uid",pannel:i},function(data){
			if (data){
				alert (data);
			}
		});	
	});
		
}

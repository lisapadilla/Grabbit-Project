Drupal.behaviors.realtime = function(){
	
	setInterval("execute_realtime()", 60000);
	//setInterval("execute_realtime()", 300000);
	
}

function execute_realtime(){
	
	$(".user-panel").each(function(){
	  /*	$.get(Drupal.settings.basePath+"execute/realtime",{pannel:$(this).attr('pid'),last_nid:last_nid},function(data){
			if (data){
				alert (data);
			}
		});*/
		first = $(".panel-wraper div:first",$(this));
		alert(first.attr('id'));
			
	});
		
}

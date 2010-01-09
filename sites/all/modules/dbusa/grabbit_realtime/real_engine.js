Drupal.behaviors.realtime = function(){
	
	setInterval("execute_realtime()", 300000);
	
}

function execute_realtime(){
	
		$.get(Drupal.settings.basePath+"execute/realtime",{user:"uid",pannel:"elpanel"},function(data){
	      
			if (data){
				alert (data);
			}else{
				alert ("There was a problem connecting with the realtime");
			}
		});
		
}

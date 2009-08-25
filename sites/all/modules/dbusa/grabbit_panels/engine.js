$(document).ready(function() {
	
	
	$(".node-stream-news .content-truncated").truncate( 120,{
	        chars: /\s/,
	        trail: [ "...<a href='#' class='truncate_show'>more</a>", "<a href='#' class='truncate_hide'>less</a>" ]
	   });
	
	$(".node-stream-blogs .content-truncated, .node-stream-deal .content-truncated").truncate( 120,{
	        chars: /\s/,
	        trail: [ "...<a href='#' class='truncate_show'>more</a>", "<a href='#' class='truncate_hide'>less</a>" ]
	   });
	
	$(".facebook-post .content-truncated").truncate( 120,{
	        chars: /\s/,
	        trail: [ "...<a href='#' class='truncate_show'>more</a>", "<a href='#' class='truncate_hide'>less</a>" ]
	   });
	
	$(".twitter-message-stream .twitter-body-contains").truncate( 120,{
	        chars: /\s/,
	        trail: [ "...<a href='#' class='truncate_show'>more</a>", "<a href='#' class='truncate_hide'>less</a>" ]
	   });
	
	
});
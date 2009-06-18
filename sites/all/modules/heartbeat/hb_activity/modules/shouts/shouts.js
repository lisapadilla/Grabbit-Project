/**
* Submit the request to clear the shout
*/
function clearShout() {

  $.ajax({
   type: "POST",
   dataType: 'json',
   url: Drupal.settings.basePath + "/shout/clear",
   success: function(response){

   	 if (typeof(msg) == 'string') {
       response = Drupal.parseJson(response);
     }

     $('#shout-wrapper').html(response.data);
     
   }
   
 });
	
}
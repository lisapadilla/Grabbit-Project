// $Id: gridselect.js,v 1.2 2009/08/28 23:40:15 hadsie Exp $

Drupal.behaviors.gridselect = function (context) {
  $('#multi-grid-selector', context).show();
}
  
Drupal.behaviors.clickItem = function (context) {
  $('#multi-grid-selector #items li.item', context).click(function() {
      if ($(this).hasClass("disabled")) {
	return false;
      }
      
      var key_id = $(this).attr('id');
      var key = key_id.substring(4); // drop the key-

      var item = $('a', this);

      var curval = $(Drupal.settings.gridselect.gridselect_id).val();
      curval = curval ? curval : [];
      var newval = [];

      if ($(item).hasClass('selected')) {
	// Deselect
	$(item).removeClass('selected');
	$('#multi-grid-selector #selected-items #' + key_id).remove();

	// Remove the selected item from the form values
	for ($i = 0; $i < curval.length; $i++) {
	  if (curval[$i] == key) {
	    continue;
	  }
	  newval.push(curval[$i]);
	}
      }
      else {
	// Select
	$(item).addClass('selected');
	item_html = '<li class="item" id="sidebar-' + key_id + '">' + $(this).html() + '</li>';
	$('#multi-grid-selector #selected-items').append(item_html);

	// Update the form with the latest value
	curval.push(key);
	newval = curval;
      }

      $(Drupal.settings.gridselect.gridselect_id).val(newval);

      return false;
    });
}

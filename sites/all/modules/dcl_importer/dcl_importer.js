// $Id: dcl_importer.js,v 1.1.2.1 2009/08/21 03:16:31 hadsie Exp $

Drupal.behaviors.dclTableSelect = function (context) {
  $('table.new_dcl_contacts:has(th.select-all):not(.tableSelect-processed)', context).each(Drupal.tableSelect);
  if (Drupal.settings.dcl_importer.select_all) {
    $('th.select-all input.form-checkbox:checkbox', context).click();
    $('table.new_dcl_contacts tbody tr', context).addClass('selected');
  }

};

Drupal.behaviors.dclEnterSubmit = function (context) {
  $("#dcl-import-form-wrapper #edit-password", context).keypress(function (e){
      if (e.keyCode == 13) {
	// If any autocomplete fields are open, don't submit so the enter key
	// can be used to select an option.
	if ($("#autocomplete").length == 0) {
	  $("#dcl-import-form-wrapper #edit-submit").click();
	}
	return false;
      }
  });
};

var cck_field_privacy = {
  init: function() {
    if (typeof(Drupal) == 'undefined' || typeof(Drupal.settings) == 'undefined') return; // abort

    for (field_name in Drupal.settings.cck_field_privacy.default_value) {
      $('#'+ field_name +'link').bind('click', cck_field_privacy.click); // bind padlock elements
    }
  },

  click: function() {
    var field_name = $(this).attr('id').substr(0, $(this).attr('id').length-4),
        field_state = Drupal.settings.cck_field_privacy.default_value[field_name];

    // display prompt
    var prompt = $.prompt(
      // @TODO: Output the list of privacy options in Drupal.settings.
      // @TODO: Make Buddies conditional based on module_exists('buddylist').
      //        then remove as a dependency.
      // @TODO: Provide all available relationships when module_exists('user_relationships').
      '<p><strong>Privacy Settings</strong></p>'+
      '<form>'+
      '  <div><label><input type="radio" value="e" name="privacy" /> Everyone</label></div>'+
      '  <div><label><input type="radio" value="b" name="privacy" /> Buddies</label></div>'+
      '  <div><label><input type="radio" value="n" name="privacy" /> Nobody</label></div>'+
      '</form>', {

      overlayspeed: 'fast',
      promptspeed: 'fast',
      show: 'slideDown',
      loaded: (function(field_name) { return function() {
        $("input[@type='radio']", this).each(function() {
          // set default radio checked on load
          var e = $(this);
          e.attr('checked', field_state == e.val()? 'checked' : '');
        }).change((function(field_name) { return function() {
          // save changes
          var radio = $(this),
              form = radio.parents('form'),
              prompt = form.parents('div.jqicontainer');

          Drupal.settings.cck_field_privacy.default_value[field_name] = radio.val(); // remember setting
          $('#jqibuttonOk', prompt).trigger('click'); // automatically close prompt
          $.post( // save changes
            Drupal.settings.cck_field_privacy.action, {
            user: Drupal.settings.cck_field_privacy.uid,
            field: field_name,
            type: Drupal.settings.cck_field_privacy.content_type,
            setting: radio.val()
          });
        };})(field_name))
      };})(field_name)
    });
  return false;
  }
};

$(cck_field_privacy.init); // onload
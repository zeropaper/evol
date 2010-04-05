Drupal.behaviors.nszFieldset = function(context) {
  // Fieldset
  $('div.fieldset:not(.admin-processed)').each(function () {
    var $fieldset = $(this);
    $fieldset.addClass('admin-processed');
    if ($fieldset.is('.collapsible')) {
      if ($('.error', $fieldset).length > 0) {
        $fieldset.removeClass('collapsed');
      }
      if ($fieldset.is('.collapsed')) {
        $fieldset.children('.fieldset-content').hide();
      }
      $fieldset.children('.fieldset-title').click(function () {
        var $title = $(this);
        if ($fieldset.is('.collapsed')) {
          $title.next('.fieldset-content').slideDown('fast');
          $fieldset.removeClass('collapsed');
        }
        else {
          $title.next('.fieldset-content').slideUp('fast');
          $fieldset.addClass('collapsed');
        }
        return false;
      });
    }
  });
};

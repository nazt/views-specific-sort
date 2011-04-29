<?php
// $Id$
/* vim: set expandtab tabstop=2 shiftwidth=2 softtabstop=2: */
/**
 * @author     Niels Hackius <niels.hackius@tu-harburg.de>
 * @copyright  2007, Technische Universität Hamburg-Harburg: Institut für Logistik und Unternehmensführung
 * @license    http://www.opensource.org/licenses/gpl-2.0.php  The GNU General Public License (GPL) Version 2, June 1991
 * @since	   14.10.2008
 *
 */
/**
 * Handle a specific sort
 *
 *
 * SELECT col1, col2, col3
* FROM table1
* WHERE col1 IN ('z', 'x', 'y')
* ORDER BY find_in_set(col1, 'z,x,y');
*
*OR:
*	mysql> SELECT FIND_IN_SET('b','a,b,c,d');
*        -> 2

 */

class views_handler_sort_specific extends views_handler_sort{
  function query() {
    $this->ensure_my_table();
    $field = "node.nid";
    $arg = $this->query->where[0]['args'];
    $nids = array();
    foreach($arg as $value) {
      if(is_numeric($value)) {
        $nids[] = $value;
      }
    }
    if(count($nids) > 0) {
      $nids = implode(',', $nids);
      $fieldformula = "FIND_IN_SET(" . $field . ", '" . $nids . "') ";
      $fieldformula .= $this->options['order'];
      $this->query->add_orderby(NULL, NULL , NULL, $fieldformula);
    }
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['findinset'] = array(
      '#type' => 'textfield',
      '#title' => t('You can specify a sort order here(Optional)'),
      '#description' => t('Seperate by comma: e.g. a,b,d,c'),
      '#default_value' => $this->options['findinset'],
    );
  }

  function admin_summary() {
    switch ($this->options['order']) {
      case 'ASC':
      case 'asc':
      default:
        $type = t('asc');
      	break;
      case 'DESC';
      case 'desc';
        $type = t('desc');
      break;
    }
    return '<span class="views-ascending"><span>' . $type . ' '. t('for') . ' Node.nid</span></span>';
  }
}
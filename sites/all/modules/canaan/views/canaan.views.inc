<?php
function canaan_views_query_alter(&$view, &$query) {
  //krumo($query);
  //krumo($view);
  if ($view->name == 'index' && $view->current_display == "page_1") {
    $nids = array();

    //nodos slideshow
    $query_nids = db_select('node', 'n');
    $query_nids->join('field_data_field_slideshow', 'fs', 'n.nid = fs.entity_id');
    $query_nids->condition('fs.field_slideshow_value', 1)
      ->condition('n.status', 1)
      ->orderBy('n.created', 'DESC')
      ->fields('n', array('nid'))
      ->range(0, 5);
    $resultado = $query_nids->execute();
    $count = $resultado->rowCount();

    if ($count > 0) {
      foreach ($resultado as $row) {
        $nids[] = $row->nid;
      }
    }
    //nodos mision diáspora
    $query_nids = db_select('node', 'n');
    $query_nids->join('field_data_field_tipo_noticia', 'ftn', 'n.nid = ftn.entity_id');
    $query_nids->condition('ftn.field_tipo_noticia_tid', 3)
      ->condition('n.status', 1)
      ->orderBy('n.created', 'DESC')
      ->fields('n', array('nid'))
      ->range(0, 1);
    $resultado = $query_nids->execute();
    $count = $resultado->rowCount();

    if ($count > 0) {
      foreach ($resultado as $row) {
        $nids[] = $row->nid;
      }
    }

    //nodos eventos
    $query_nids = db_select('node', 'n');
    $query_nids->join('field_data_field_tipo_noticia', 'ftn', 'n.nid = ftn.entity_id');
    $query_nids->condition('ftn.field_tipo_noticia_tid', 5)
      ->condition('n.status', 1)
      ->orderBy('n.created', 'DESC')
      ->fields('n', array('nid'))
      ->range(0, 1);
    $resultado = $query_nids->execute();
    $count = $resultado->rowCount();

    if ($count > 0) {
      foreach ($resultado as $row) {
        $nids[] = $row->nid;
      }
    }


    if (!empty($nids)) {
      $query->add_where(2, 'node.nid', $nids, 'NOT IN');
    }
  }
}


function canaan_views_pre_render(&$view) {
  if ($view->name == 'radio' && $view->current_display == "radio_page") {
    $my_field = $view->field['my_field'];
    unset($view->field['my_field']);
    $view->field = array_merge(array('my_field' => $my_field), $view->field);
  }
}

// Add 'Custom text' field
function canaan_views_pre_view(&$view, &$display_id, &$args) {
  if ($view->name == 'radio' && $view->current_display == "radio_page") {

    $view->add_item($view->current_display, 'field', 'views', 'nothing', array(
      'label' => NULL,
      'alter' => array('text' => 'My field text'),
      'element_class' => 'my-field',
      'element_default_classes' => 0,
    ), 'my_field');
  }
}

?>
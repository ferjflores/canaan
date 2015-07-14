<?php
function canaan_views_query_alter(&$view, &$query) {
  //krumo($query);
  //krumo($view);
  if ($view->name == 'index' && $view->current_display == "page_1") {
    $nids = array();

    //nodos radio
    $query_nids = db_select('node', 'n');
    $query_nids->join('field_data_field_tipo_noticia', 'ftn', 'n.nid = ftn.entity_id');
    $query_nids->condition('ftn.field_tipo_noticia_tid', 4)
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
  if ($view->name == 'index' && $view->current_display == "slideshow") {
    $nids = array();
    //nodos radio
    $query_nids = db_select('node', 'n');
    $query_nids->join('field_data_field_tipo_noticia', 'ftn', 'n.nid = ftn.entity_id');
    $query_nids->condition('ftn.field_tipo_noticia_tid', 4)
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

    //nodos evento
    $query_nids = db_select('node', 'n');
    $query_nids->join('field_data_field_tipo_noticia', 'ftn', 'n.nid = ftn.entity_id');
    $query_nids->join('field_data_field_slideshow', 'fs', 'n.nid = fs.entity_id');
    $query_nids->condition('ftn.field_tipo_noticia_tid', 5)
      ->condition('fs.field_slideshow_value', 1)
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
      $query->add_where(2, 'node.nid', $nids, 'IN');
    }
  }
}


/*function canaan_views_pre_render(&$view) {
  if ($view->name == 'radio' && $view->current_display == "radio_page") {

    //ordenar campos
    $titulo = $view->field['titulo'];
    $fecha = $view->field['fecha'];
    unset($view->field['titulo'], $view->field['fecha']);
    $view->field = array_merge(array('fecha' => $fecha, 'titulo' => $titulo), $view->field);

    //asignar valores a los campos reordenados
    $nid = $view->result[0]->file_usage_id;
    $node = node_load($nid);


    $link = l($node->title, 'node/'.$nid);
    $titulo = theme('html_tag', array(
      'element' => array(
        '#tag' => 'h2',
        '#value' => $link,
      ),
    ));
    $view->field['titulo']->options['alter']['text'] =  $titulo;

    $fecha = theme('html_tag', array(
      'element' => array(
        '#tag' => 'div',
        '#value' => date('l, j \d\e F \d\e Y', $node->created),
      ),
    ));
    $view->field['fecha']->options['alter']['text'] =  $fecha;
  }
}

// Add 'Custom text' field
function canaan_views_pre_view(&$view, &$display_id, &$args) {
  if ($view->name == 'radio' && $view->current_display == "radio_page") {

    $view->add_item($view->current_display, 'field', 'views', 'nothing', array(
      'label' => NULL,
      'alter' => array('text' => 'titulo'),
      'element_class' => 'titulo',
      'element_default_classes' => 0,
    ), 'titulo');

    $view->add_item($view->current_display, 'field', 'views', 'nothing', array(
      'label' => NULL,
      'alter' => array('text' => 'fecha'),
      'element_class' => 'fecha',
      'element_default_classes' => 0,
    ), 'fecha');
  }
}
*/
?>
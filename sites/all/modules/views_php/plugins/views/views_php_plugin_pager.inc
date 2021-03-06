<?php

/**
 * A (fake) pager plugin that wraps around the actual pager.
 *
 * @ingroup views_pager_plugins
 */
class views_php_plugin_pager extends views_php_plugin_wrapper  {

  /**
   * Perform any needed actions just prior to the query executing.
   */
  public function pre_execute($query) {
    $this->wrapped->pre_execute($query);

    foreach (array(/*'argument',*/ 'field', 'filter', 'sort', /*'relationship'*/) as $type) {
      foreach ($this->wrapped->view->$type as $id => $handler) {
        if (is_callable(array($handler, 'php_pre_execute'))) {
          $handler->php_pre_execute();
        }
      }
    }

    $this->wrapped->view->query->set_limit(0);
    $this->wrapped->view->query->set_offset(0);
  }

  /**
   * Perform any needed actions just after the query executing.
   */
  public function post_execute(&$result) {
    foreach (array(/*'argument',*/ 'field', 'filter', 'sort', /*'relationship'*/) as $type) {
      foreach ($this->wrapped->view->$type as $id => $handler) {
        if (is_callable(array($handler, 'php_post_execute'))) {
          $handler->php_post_execute();
        }
      }
    }
    $this->wrapped->post_execute($result);
  }

  public function pre_render() {
    foreach (array(/*'argument',*/ 'field', 'filter', 'sort', /*'relationship'*/) as $type) {
      foreach ($this->wrapped->view->$type as $id => $handler) {
        if (is_callable(array($handler, 'php_pre_render'))) {
          $handler->php_pre_render();
        }
      }
    }
    $this->update_wrapped_pager();
    $this->php_unwrap();
  }

  protected function update_wrapped_pager() {
     if (!isset($this->wrapped->total_items)) {
       $this->wrapped->total_items = count($this->wrapped->view->result);
     }
     $this->wrapped->update_page_info();    $this->wrapped->update_page_info();

    $item_per_page = $this->wrapped->get_items_per_page();
    if ($item_per_page > 0) {
      $offset = $this->wrapped->get_current_page() * $item_per_page + $this->wrapped->get_offset();
      if (!isset($this->wrapped->view->result)) {
        $this->wrapped->view->result = array_slice($this->wrapped->view->result, $offset, $item_per_page);
      }
    }
  }

  /**
   * Execute the count query, which will be done just prior to the query
   * itself being executed.
   */
  function execute_count_query(&$count_query) {
    $this->wrapped->execute_count_query($count_query);
  }
}

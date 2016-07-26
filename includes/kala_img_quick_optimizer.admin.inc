<?php

/**
 * @file
 * Kala IMG Quick Optimizer Admin Settings file.
 */

/**
 * Missing Module Message Fixer Form.
 */
function kala_img_quick_optimizer_form() {

  $query = db_query("SELECT uri FROM {file_managed} WHERE type = 'image' ORDER BY filesize DESC");
  $count = $query->rowCount();

  $form['files'] = array(
    '#type' => 'fieldset',
    '#title' => t('Resave all Images so ImageMagick can do its thing.'),
  );

  $desc = t("!count managed files to process", array('!count' => $count));

  $form['files']['count'] = array(
    '#type' => 'item',
    '#markup' => '<center><h2>' . $desc . '</h2></center>',
  );

  $form['#submit'][] = 'kala_img_quick_optimizer_form_submit';

  return system_settings_form($form);
}


/**
 * Submit handler for kala img optimizer form.
 */
function kala_img_quick_optimizer_form_submit($form, &$form_state) {

  $query = db_query("SELECT uri FROM {file_managed} WHERE type = 'image' ORDER BY filesize DESC");

  foreach ($query->fetchAll() as $record) {
    $operations[] = array('kala_img_quick_optimizer_batch_files', array($record->uri));
  }

  // Set Batch fun stuff.
  $batch = array(
    'title' => t('Assimilating...'),
    'operations' => $operations,
    'finished' => 'kala_img_quick_optimizer_batch_files_finished',
    'file' => 'includes/kala_img_quick_optimizer.batch.inc',
  );

  // Engage.
  batch_set($batch);
}

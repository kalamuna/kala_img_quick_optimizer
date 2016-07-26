<?php

/**
 * @file
 * Kala IMG Quick Optimizer Batch file.
 */

/**
 * Batch function for resaving the images.
 */
function kala_img_quick_optimizer_batch_files($uri, &$context) {

  // Update our progress information.
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
  }
  $context['sandbox']['progress']++;

  // Load the image.
  $image = image_load($uri);

  // Now resave it if it exists,
  if ($image) {
    image_save($image);
    $context['results'][] = $image;
  }

  // Message of winning.
  $context['message'] = t('Now assimilating %m', array('%m' => $uri));
}


/**
 * Batch finished function.
 */
function kala_img_quick_optimizer_batch_files_finished($success, $results, $operations) {
  // go through success and grab what we need.
  $items = array();

  if ($success) {
    $message = format_plural(count($results), 'One file assimilated.', '@count files assimilated.');
  }
  else {
    $message = t('Assimilation was futile!');
  }

  drupal_set_message($message);

  drupal_goto('admin/config/system/kala-img-quick-optimizer');
}

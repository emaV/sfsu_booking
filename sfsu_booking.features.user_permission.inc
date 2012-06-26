<?php
/**
 * @file
 * sfsu_booking.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sfsu_booking_user_default_permissions() {
  $permissions = array();

  // Exported permission: create appointment content.
  $permissions['create appointment content'] = array(
    'name' => 'create appointment content',
    'roles' => array(
      0 => 'host',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own appointment content.
  $permissions['delete own appointment content'] = array(
    'name' => 'delete own appointment content',
    'roles' => array(
      0 => 'host',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own appointment content.
  $permissions['edit own appointment content'] = array(
    'name' => 'edit own appointment content',
    'roles' => array(
      0 => 'host',
    ),
    'module' => 'node',
  );

  return $permissions;
}

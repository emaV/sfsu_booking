<?php
/**
 * @file
 * sfsu_booking.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sfsu_booking_taxonomy_default_vocabularies() {
  return array(
    'booking_status' => array(
      'name' => 'Booking Status',
      'machine_name' => 'booking_status',
      'description' => 'Booking Status',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}

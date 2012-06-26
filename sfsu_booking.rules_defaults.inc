<?php
/**
 * @file
 * sfsu_booking.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function sfsu_booking_default_rules_configuration() {
  $items = array();
  $items['rules_remove_all_comments'] = entity_import('rules_config', '{ "rules_remove_all_comments" : {
      "LABEL" : "Remove all comments",
      "PLUGIN" : "rule set",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "node" : { "label" : "Node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : { "entity_fetched" : { "entity_comment" : "Fetched comment" } },
            "DO" : [
              { "entity_query" : {
                  "USING" : { "type" : "comment", "property" : "node", "value" : [ "node" ] },
                  "PROVIDE" : { "entity_fetched" : { "entity_comment" : "Fetched comment" } }
                }
              },
              { "LOOP" : {
                  "USING" : { "list" : [ "entity-comment" ] },
                  "ITEM" : { "list_item_comment" : "Current list item comment" },
                  "DO" : [
                    { "entity_delete" : { "data" : [ "list-item-comment" ] } },
                    { "drupal_message" : { "message" : "Comment [list-item-comment:cid] removed." } }
                  ]
                }
              }
            ],
            "LABEL" : "Remove all comments (rule)"
          }
        }
      ]
    }
  }');
  $items['rules_slot_duplicate'] = entity_import('rules_config', '{ "rules_slot_duplicate" : {
      "LABEL" : "Slot Duplicate",
      "PLUGIN" : "rule set",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "node" : { "label" : "Node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : {
              "entity_created" : { "entity_node_created" : "Created node" },
              "variable_added" : { "variable_time" : "Time variable" }
            },
            "IF" : [
              { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_time" } },
              { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_user_host" } }
            ],
            "DO" : [
              { "entity_create" : {
                  "USING" : {
                    "type" : "node",
                    "param_type" : "appointment",
                    "param_title" : "[node:title]",
                    "param_author" : [ "site:current-user" ]
                  },
                  "PROVIDE" : { "entity_created" : { "entity_node_created" : "Created node" } }
                }
              },
              { "variable_add" : {
                  "USING" : {
                    "type" : "date",
                    "value" : { "select" : "node:field-time", "date_offset" : { "value" : 604800 } }
                  },
                  "PROVIDE" : { "variable_added" : { "variable_time" : "Time variable" } }
                }
              },
              { "data_set" : {
                  "data" : [ "entity-node-created:field-time" ],
                  "value" : [ "node:field-time" ]
                }
              },
              { "data_set" : {
                  "data" : [ "entity-node-created:field-user-host" ],
                  "value" : [ "node:field-user-host" ]
                }
              }
            ],
            "LABEL" : "Slot Duplicate (rule)"
          }
        }
      ]
    }
  }');
  $items['rules_slot_reserve'] = entity_import('rules_config', '{ "rules_slot_reserve" : {
      "LABEL" : "Slot Reserve",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "comment" ],
      "ON" : [ "comment_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "comment:node" ],
            "type" : { "value" : { "appointment" : "appointment" } }
          }
        },
        { "entity_has_field" : { "entity" : [ "comment:node" ], "field" : "field_booking_status" } }
      ],
      "DO" : [
        { "entity_query" : {
            "USING" : {
              "type" : "taxonomy_term",
              "property" : "name",
              "value" : "Booked",
              "limit" : [ "" ]
            },
            "PROVIDE" : { "entity_fetched" : { "entity_term_booked" : "Fetched Term \\u0022Booked\\u0022" } }
          }
        },
        { "entity_fetch" : {
            "USING" : { "type" : "node", "id" : [ "comment:node:nid" ] },
            "PROVIDE" : { "entity_fetched" : { "entity_node" : "Fetched node" } }
          }
        },
        { "data_set" : {
            "data" : [ "comment:node:field-user-guest" ],
            "value" : [ "comment:author" ]
          }
        },
        { "data_set" : { "data" : [ "comment:node:comment" ], "value" : "0" } },
        { "data_set" : {
            "data" : [ "comment:node:field-booking-status" ],
            "value" : [ "entity-term-booked:0" ]
          }
        },
        { "drupal_message" : { "message" : "[entity-node:title] reserved!" } }
      ]
    }
  }');
  $items['rules_slot_reset'] = entity_import('rules_config', '{ "rules_slot_reset" : {
      "LABEL" : "Slot Reset",
      "PLUGIN" : "rule set",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "node" : { "label" : "Node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : { "entity_fetched" : {
                "entity_term_available" : "Fetched Term",
                "entity_anonymous" : "Fetched Anonymous"
              }
            },
            "IF" : [
              { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_booking_status" } },
              { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_user_guest" } }
            ],
            "DO" : [
              { "entity_query" : {
                  "USING" : { "type" : "taxonomy_term", "property" : "name", "value" : "Available" },
                  "PROVIDE" : { "entity_fetched" : { "entity_term_available" : "Fetched Term" } }
                }
              },
              { "entity_fetch" : {
                  "USING" : { "type" : "user", "id" : "0" },
                  "PROVIDE" : { "entity_fetched" : { "entity_anonymous" : "Fetched Anonymous" } }
                }
              },
              { "data_set" : {
                  "data" : [ "node:field-booking-status" ],
                  "value" : [ "entity-term-available:0" ]
                }
              },
              { "data_set" : { "data" : [ "node:field-user-guest" ], "value" : [ "entity-anonymous" ] } },
              { "data_set" : { "data" : [ "node:comment" ], "value" : "2" } },
              { "component_rules_remove_all_comments" : { "node" : [ "node" ] } }
            ],
            "LABEL" : "Slot Reset (rule)"
          }
        }
      ]
    }
  }');
  return $items;
}

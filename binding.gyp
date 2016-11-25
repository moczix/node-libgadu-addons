{
  "targets": [
    {
      "target_name": "<(module_name)",
      "sources": [ "src/<(module_name).cc" ],
      "dependencies": [
        "deps/gadu.gyp:gadu"
      ]
    },
    {
      "target_name": "action_after_build",
      "type": "none",
      "dependencies": [ "<(module_name)" ],
      "copies": [
        {
          "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
          "destination": "<(module_path)/"
        },
      ],
      'conditions': [
          ['OS == "win"', {
             "copies": [
               {
                "files": [ "<(PRODUCT_DIR)/mylib<(SHARED_LIB_SUFFIX)" ],
                "destination": "<(module_path)/"
               }
             ]
          }, {
             "copies": [
               {
                "files": [ "<(PRODUCT_DIR)/mylib<(SHARED_LIB_SUFFIX)" ],
                "destination": "<(module_path)/lib.target/"
               }
             ]
          }
          ]
      ]
    }
  ]
}

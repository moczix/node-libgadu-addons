{
    "targets": [
        {
            "target_name": "gadu",
            "product_name": "gadu",
            "type": "shared_library",
            "sources": [
                "./../src/session.cc"
            ],
            "include_dirs": [
                "include",
				"<!(node -e \"require('nan')\")"
            ],
            'direct_dependent_settings': {
              'include_dirs': [ 'include/' ],
            },
            'xcode_settings': {
              'DYLIB_INSTALL_NAME_BASE': '@loader_path/lib.target/'
            }
        }
    ]
}
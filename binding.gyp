{
  "targets": [
    {
      "target_name": "gadu",
      "sources": [ "src/gadu.cc", "src/session.cc"],
	  "libraries": [ "/home/moczniak/my_native_libs/libgadu/lib/libgadu.so" ],
		"include_dirs" : [
			"<!(node -e \"require('nan')\")"
		]
    }
  ]
}
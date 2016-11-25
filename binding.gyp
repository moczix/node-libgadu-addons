{
  "targets": [
    {
      "target_name": "gadu",
      "sources": [ "src/gadu.cc", "src/session.cc"],
	  "libraries": [ "-L/home/moczniak/my_native_libs/libgadu/lib", "-lgadu" ],
		"include_dirs" : [
			"<!(node -e \"require('nan')\")"
		]
    }
  ]
}



{
  "targets": [
    {
      "target_name": "gadu",
      "sources": [ "src/gadu.cc", "src/session.cc"],
	  "libraries": [ "-L/var/www/mygadu2/gadu/src/libgadu/lib", "-lgadu" ],
		"include_dirs" : [
			"<!(node -e \"require('nan')\")"
		]
    }
  ]
}



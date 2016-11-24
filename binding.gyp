{
  "targets": [
    {
      "target_name": "gadu",
      "sources": [ "src/gadu.cc", "src/session.cc"],
	  "libraries": [ "/usr/local/lib/libgadu.a" ],
		"include_dirs" : [
			"<!(node -e \"require('nan')\")"
		]
    }
  ]
}
{
  "targets": [
    {
      "target_name": "gadu",
      "sources": [ "src/gadu.cc", "src/session.cc"],
	  "libraries": [ "-lgadu" ],
		"include_dirs" : [
			"<!(node -e \"require('nan')\")"
		]
    }
  ]
}
cmd_Makefile := cd ..; /root/.nvm/versions/node/v7.1.0/lib/node_modules/node-gyp/gyp/gyp_main.py -fmake --ignore-environment "--toplevel-dir=." -I/var/www/mygadu2/gadu/build/config.gypi -I/root/.nvm/versions/node/v7.1.0/lib/node_modules/node-gyp/addon.gypi -I/root/.node-gyp/7.1.0/include/node/common.gypi "--depth=." "-Goutput_dir=." "--generator-output=build" "-Dlibrary=shared_library" "-Dvisibility=default" "-Dnode_root_dir=/root/.node-gyp/7.1.0" "-Dnode_gyp_dir=/root/.nvm/versions/node/v7.1.0/lib/node_modules/node-gyp" "-Dnode_lib_file=node.lib" "-Dmodule_root_dir=/var/www/mygadu2/gadu" binding.gyp

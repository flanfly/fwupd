if gusb.found()
cargs = ['-DG_LOG_DOMAIN="FuPluginJabra"']

install_data(['jabra.quirk'],
  install_dir: join_paths(datadir, 'fwupd', 'quirks.d')
)

shared_module('fu_plugin_jabra',
  fu_hash,
  sources : [
    'fu-plugin-jabra.c',
    'fu-jabra-device.c',
  ],
  include_directories : [
    root_incdir,
    fwupd_incdir,
    fwupdplugin_incdir,
  ],
  install : true,
  install_dir: plugin_dir,
  link_with : [
    fwupd,
    fwupdplugin,
  ],
  c_args : cargs,
  dependencies : [
    plugin_deps,
  ],
)
endif

if gusb.found()
cargs = ['-DG_LOG_DOMAIN="FuPluginSystem76Launch"']

install_data(['system76-launch.quirk'],
  install_dir: join_paths(datadir, 'fwupd', 'quirks.d')
)

shared_module('fu_plugin_system76_launch',
  fu_hash,
  sources : [
    'fu-plugin-system76-launch.c',
    'fu-system76-launch-device.c',
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

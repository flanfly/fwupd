if gusb.found()
cargs = ['-DG_LOG_DOMAIN="FuPluginNovatek"']

install_data([
  'hailuck.quirk',
  ],
  install_dir: join_paths(datadir, 'fwupd', 'quirks.d')
)

shared_module('fu_plugin_hailuck',
  fu_hash,
  sources : [
    'fu-hailuck-common.c',
    'fu-hailuck-bl-device.c',
    'fu-hailuck-kbd-device.c',
    'fu-hailuck-kbd-firmware.c',  # fuzzing
    'fu-hailuck-tp-device.c',
    'fu-plugin-hailuck.c',
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

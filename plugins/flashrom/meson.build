if get_option('plugin_flashrom').enabled() or \
   (get_option('plugin_flashrom').auto() and libflashrom.found())
cargs = ['-DG_LOG_DOMAIN="FuPluginFlashrom"']

install_data(['flashrom.quirk'],
  install_dir: join_paths(get_option('datadir'), 'fwupd', 'quirks.d')
)

shared_module('fu_plugin_flashrom',
  fu_hash,
  sources : [
    'fu-flashrom-device.c',
    'fu-plugin-flashrom.c',
    'fu-flashrom-cmos.c',
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
  c_args : [
    cargs,
    '-DLOCALSTATEDIR="' + localstatedir + '"',
  ],
  dependencies : [
    plugin_deps,
    libflashrom,
  ],
)
endif

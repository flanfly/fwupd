package main

/*
#cgo LDFLAGS: -Lbuild/libfwupd -Lbuild/libfwupdplugin -L/usr/lib/x86_64-linux-gnu/ -Lbuild/subprojects/gusb/gusb -Lbuild/subprojects/json-glib/json-glib -Lbuild/subprojects/libxmlb/src -Wl,-Bstatic -lfwupdplugin -lfwupd -lgio-2.0 -lgobject-2.0 -lffi -lgmodule-2.0 -lglib-2.0 -lgusb -ljson-glib-1.0 -lpcre -lmount -lxmlb -lusb-1.0 -larchive -llzma -lresolv -lselinux -lblkid -lnettle -lacl -lxml2 -lbz2 -llz4 -lzstd -licuuc -licudata -lstdc++ -luuid -Wl,-Bdynamic -pthread -lm -lz -ldl -ludev
#cgo CFLAGS: -Ilibfwupd -Ibuild -Ilibfwupdplugin -Isubprojects/libxmlb/src -Ibuild/subprojects/libxmlb/src -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -pthread -I/usr/lib/x86_64-linux-gnu/glib-2.0/include

#include <stdio.h>
#include <fwupd.h>
#include <fwupdplugin.h>
#include <libfwupdplugin/fu-version.h>
#include <libfwupdplugin/fu-plugin-private.h>
#include <libfwupdplugin/fu-context-private.h>
//#include "src/fu-

typedef void (*FuPluginInitVfuncsFunc)(FuPluginVfuncs *vfuncs);
gboolean fu_plugin_open(FuPlugin *self, const gchar *filename, GError **error);

FuContext* ctx = NULL;

void callback(FuPlugin *plugin, FuDevice *device, gpointer user_data) {
  printf("%s (%p) added\n",fu_device_get_name(device),device);
  printf("%s added\n",fu_device_get_id(device));
}

const char* doit(const char* path) {
  if (ctx == NULL) {
    ctx = fu_context_new();
  }
  FuPlugin* plugin = fu_plugin_new(ctx);
  g_signal_connect(FU_PLUGIN(plugin),
                   "device-added",
                   G_CALLBACK(callback),
                   NULL);

  gboolean ret = fu_plugin_open(plugin, path, NULL);
  fu_plugin_runner_init(plugin);

  g_autoptr(FuProgress) progress = fu_progress_new(G_STRLOC);
  g_autoptr(GError) error_local = NULL;
  if(!fu_plugin_runner_startup(plugin, &error_local)) {
    g_prefix_error(&error_local,"startup()");
  } else {
    if(!fu_plugin_runner_coldplug(plugin, &error_local)) {
      g_prefix_error(&error_local,"coldplug()");
    }
  }

  return fu_plugin_get_name(plugin);
}
*/
import "C"
import (
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
	fmt.Println("fwupd version", C.GoString(C.fwupd_version_string()))
	fmt.Println("fwupdplugin version", C.GoString(C.fu_version_string()))

	dir, err := ioutil.ReadDir("/fwupd/build/plugins")
	if err != nil {
		panic("readdir" + err.Error())
	}

	for _, fi := range dir {
		if !fi.IsDir() {
			continue
		}
		fname := fmt.Sprint("/fwupd/build/plugins/", fi.Name(), "/libfu_plugin_", fi.Name(), ".so")
		_, err = os.Stat(fname)
		if err != nil {
			continue
		}
		fmt.Println("name", C.GoString(C.doit(C.CString(fname))))
	}
}

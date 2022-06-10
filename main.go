package main

// #cgo LDFLAGS: -Lbuild/libfwupd -Lbuild/libfwupdplugin -L/home/seu/.local/lib -Wl,-Bstatic -lfwupdplugin -lfwupd -lgio-2.0 -lgobject-2.0 -lffi -lgmodule-2.0 -lglib-2.0 -lpcre -lmount -lblkid -lxmlb -Wl,-Bdynamic -ljson-glib-1.0 -lgusb -lusb-1.0 -larchive -llzma -pthread -lm -lz
// #cgo CFLAGS: -Ilibfwupd -Ibuild -Ilibfwupdplugin -I/home/seu/.local/include/libxmlb-2 -I/home/seu/.local/include -I/home/seu/.local/include/glib-2.0 -I/home/seu/.local/lib/glib-2.0/include -pthread -I/home/seu/.local/include/libmount -I/home/seu/.local/include/blkid
// #include <fwupd.h>
// #include <fwupdplugin.h>
// #include <libfwupdplugin/fu-version.h>
// #include <libfwupdplugin/fu-plugin-private.h>
// #include <libfwupdplugin/fu-context-private.h>
/*
typedef void (*FuPluginInitVfuncsFunc)(FuPluginVfuncs *vfuncs);
gboolean fu_plugin_open(FuPlugin *self, const gchar *filename, GError **error);

const char* doit(const char* path) {
  FuContext* ctx = fu_context_new();
  FuPlugin* plugin = fu_plugin_new(ctx);
  gboolean ret = fu_plugin_open(plugin, path, NULL);
  return fu_plugin_get_name(plugin);
}
*/
import "C"
import (
	"fmt"
)

func main() {
	fmt.Println("fwupd version", C.GoString(C.fwupd_version_string()))
	fmt.Println("fwupdplugin version", C.GoString(C.fu_version_string()))
	fmt.Println("amt name", C.GoString(C.doit(C.CString("/home/seu/src/fwupd/build/plugins/amt/libfu_plugin_amt.so"))))
}

package main
// #cgo LDFLAGS: -L/root/.local/lib -L/root/.local/lib/x86_64-linux-gnu/ -Wl,-Bstatic -lfwupdembed -lfwupdplugin -lfwupd -ljcat -lgcab-1.0 -lgio-2.0 -lgobject-2.0 -lffi -lgmodule-2.0 -lglib-2.0 -lgusb -ljson-glib-1.0 -lgnutls -lnettle -ltasn1 -lgmp -lpcre -lmount -lxmlb -lusb-1.0 -lgnutls -larchive -lresolv -lselinux -lblkid -lnettle -lhogweed -lgmp -lnettle -lunistring -lacl -lxml2 -lbz2 -llz4 -llzma -lzstd -licuuc -licudata -lstdc++ -luuid -Wl,-Bdynamic -pthread -lm -lz -ldl -ludev -llzma
// #cgo CFLAGS: -Ilibfwupd -Ibuild -Ilibfwupdplugin -Isubprojects/libxmlb/src -Ibuild/subprojects/libxmlb/src -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -pthread -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
// void fu_embed_go(void);
import "C"

func main() {
  C.fu_embed_go()
}

package main

// #cgo LDFLAGS: -Lbuild/src -lfwupdembed
// void fu_embed_go(void);
import "C"

func main() {
  C.fu_embed_go()
}

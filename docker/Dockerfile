FROM debian:oldstable AS build

RUN apt-get update && \
    apt-get install -y git build-essential ninja-build python3 python3-pip pkg-config libglib2.0-dev libarchive-dev liblzma-dev gnutls-dev gnutls-bin libudev-dev libusb-1.0-0-dev libprotobuf-c-dev protobuf-c-compiler libpci-dev libftdi1-dev gcab gettext wget libacl1-dev libbz2-dev libzstd-dev liblz4-dev libxml2-dev libselinux-dev && \
    pip3 install --user meson

RUN git clone https://github.com/fwupd/fwupd && cd fwupd && git checkout 1.8.1

WORKDIR fwupd

RUN PATH="/root/.local/bin:$PATH" meson build \
      --default-library=static \
      --strip \
      -Dlibexecdir=/usr/lib/ \
      -Dprefix=/usr/ \
      -Ddocs=none \
      -Dconsolekit=disabled \
      -Dpolkit=disabled \
      -Dsystemd=disabled \
      -Dgudev=disabled \
      -Dgnutls=disabled \
      -Dcurl=disabled \
      -Dudevdir=disabled \
      -Dintrospection=disabled \
      -Dlibxmlb:introspection=false \
      -Dlibxmlb:gtkdoc=false \
      -Dlibjcat:gtkdoc=false \
      -Dlibjcat:introspection=false \
      -Dlibjcat:gpg=false \
      -Dlibjcat:pkcs7=false \
      -Dlibjcat:vapi=false \
      -Dlibjcat:cli=false \
      -Dgcab:docs=false \
      -Dgcab:introspection=false \
      -Dgcab:vapi=false \
      -Dgusb:docs=false \
      -Dgusb:introspection=false \
      -Dgusb:vapi=false

RUN ninja -C build

RUN cd /root && wget https://go.dev/dl/go1.18.3.linux-amd64.tar.gz && \
    tar xvf go1.18.3*

COPY main.go .
RUN PATH="/root/go/bin:$PATH" go build main.go
RUN ./main

FROM scratch AS export
COPY --from=build /fwupd/main /

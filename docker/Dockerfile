FROM debian:oldstable AS build

RUN apt-get update && \
    apt-get install -y git build-essential ninja-build pkg-config libglib2.0-dev libarchive-dev liblzma-dev libudev-dev libusb-1.0-0-dev libprotobuf-c-dev protobuf-c-compiler libpci-dev libftdi1-dev gettext wget libacl1-dev libbz2-dev libzstd-dev liblz4-dev libxml2-dev libselinux-dev libssl-dev libreadline-dev libncurses-dev libunistring-dev libz-dev libtool autopoint gtk-doc-tools gperf libgmp-dev libev-dev libtasn1-dev libtasn1-bin bison

# setup python 3.8
RUN git clone https://github.com/yyuu/pyenv /root/.pyenv
ENV HOME  /root
ENV PYENV_ROOT $HOME/.pyenv
ENV PATH $PYENV_ROOT/shims:$PYENV_ROOT/bin:$PATH
RUN pyenv install 3.8.13
RUN pyenv global 3.8.13
RUN pyenv rehash
RUN pip install --user meson xml-python
# contrib/generate-gresource-xml.py hardcodes /usr/bin/python3
RUN ln -sf $PYENV_ROOT/shims/python3 /usr/bin/python3

# local prefix
ENV PKG_CONFIG_PATH /root/.local/lib/pkgconfig 
ENV PATH /root/.local/bin:$PATH
ENV LD_LIBRARY_PATH /root/.local/lib/x86_64-linux-gnu:/root/.local/lib 

# static gcab
RUN git clone https://gitlab.gnome.org/GNOME/gcab.git && cd gcab && git checkout b55268ac1020cd6c033acb52f2e6ae984bf5c9fd

WORKDIR gcab

RUN sed -i.bak 's/shared_library/library/' libgcab/meson.build
RUN  meson build \
      --default-library=static \
      --strip \
      -Dprefix=/root/.local \
      -Ddocs=false \
      -Dintrospection=false \
      -Dvapi=false \
      -Ddocs=false \
      -Dintrospection=false \
      -Dvapi=false
RUN ninja -C build install

# nettle
RUN wget https://ftp.gnu.org/gnu/nettle/nettle-3.6.tar.gz -O /root/nettle.tgz && tar xvf /root/nettle.tgz

WORKDIR nettle-3.6

RUN ./configure \
  --prefix=/root/.local \
  --with-gmp
RUN make install

# stripped down gnutls
RUN git clone https://github.com/gnutls/gnutls.git /root/gnutls && cd /root/gnutls && git checkout 3.7.6

WORKDIR /root/gnutls

RUN ./bootstrap
RUN ./configure \
  --prefix=/root/.local \
  --enable-static \
  --without-p11-kit \
  --without-tpm \
  --without-tpm2 \
  --disable-doc
RUN make install

RUN git clone https://github.com/flanfly/fwupd /root/fwupd && cd /root/fwupd && git checkout mistress

WORKDIR /root/fwupd

RUN meson build \
      --default-library=static \
      --strip \
      -Dprefix=/root/.local \
      -Ddocs=none \
      -Dconsolekit=disabled \
      -Dpolkit=disabled \
      -Dsystemd=disabled \
      -Dgudev=disabled \
      -Dgnutls=disabled \
      -Dcurl=disabled \
      -Dudevdir=disabled \
      -Dintrospection=disabled \
      -Dgresource_quirks=enabled \
      -Dlibxmlb:introspection=false \
      -Dlibxmlb:gtkdoc=false \
      -Dlibjcat:gtkdoc=false \
      -Djson-glib:gtk_doc=disabled \
      -Djson-glib:introspection=disabled \
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

RUN ninja -C build install
RUN cp build/src/libfwupdembed.a /usr/lib

RUN cd /root && wget https://go.dev/dl/go1.18.3.linux-amd64.tar.gz && \
    tar xvf go1.18.3*
ENV PATH /root/go/bin:$PATH

COPY docker/embed.go .
RUN go build  embed.go
RUN ./embed

FROM scratch AS export
COPY --from=build /root/fwupd/embed /

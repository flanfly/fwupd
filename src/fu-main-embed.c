
#define G_LOG_DOMAIN "FuMainEmbed"

#include <stdio.h>
#include "config.h"

#include <fwupdplugin.h>
#ifdef HAVE_GIO_UNIX
#include <gio/gunixfdlist.h>
#endif
#include <glib/gstdio.h>
#ifdef HAVE_POLKIT
#include <polkit/polkit.h>
#endif
#include <jcat.h>

#include "fwupd-device-private.h"
#include "fwupd-enums-private.h"
#include "fwupd-plugin-private.h"
#include "fwupd-release-private.h"
#include "fwupd-remote-private.h"
#include "fwupd-request-private.h"
#include "fwupd-security-attr-private.h"

#include "fu-daemon.h"
#include "fu-device-private.h"
#include "fu-engine.h"
#include "fu-release.h"
#include "fu-security-attrs-private.h"

#ifdef HAVE_POLKIT
#ifndef HAVE_POLKIT_0_114
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
G_DEFINE_AUTOPTR_CLEANUP_FUNC(PolkitAuthorizationResult, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(PolkitSubject, g_object_unref)
#pragma clang diagnostic pop
#endif /* HAVE_POLKIT_0_114 */
#endif /* HAVE_POLKIT */

static void
fu_embed_engine_changed_cb(FuEngine *engine, void *self)
{
  printf("fu_embed_engine_changed_cb()\n");
}

static void
fu_embed_engine_device_added_cb(FuEngine *engine, FuDevice *device, void *self)
{
  printf("fu_embed_engine_device_added_cb()\n");
  printf("device: %s\n", fu_device_get_name(device));
}

static void
fu_embed_engine_device_removed_cb(FuEngine *engine, FuDevice *device, void *self)
{
  printf("fu_embed_engine_device_removed_cb()\n");
}

static void
fu_embed_engine_device_changed_cb(FuEngine *engine, FuDevice *device, void *self)
{
  printf("fu_embed_engine_device_changed_cb()\n");
}

static void
fu_embed_engine_device_request_cb(FuEngine *engine, FwupdRequest *request, void *self)
{
  printf("fu_embed_engine_device_request_cb()\n");
}

static void
fu_embed_engine_status_changed_cb(FuEngine *engine, FwupdStatus status,  void *self)
{
  printf("fu_embed_engine_status_changed_cb()\n");
}

void fu_embed_go(void) {
	g_autoptr(GError) error = NULL;
	g_autoptr(FuProgress) progress = fu_progress_new(G_STRLOC);

	fu_progress_set_id(progress, G_STRLOC);
	fu_progress_set_profile(progress, g_getenv("FWUPD_VERBOSE") != NULL);
	fu_progress_add_step(progress, FWUPD_STATUS_LOADING, 99, "load-engine");
	fu_progress_add_step(progress, FWUPD_STATUS_LOADING, 1, "load-introspection");
#ifdef HAVE_POLKIT
	fu_progress_add_step(progress, FWUPD_STATUS_LOADING, 1, "load-authority");
#endif
	fu_progress_add_step(progress, FWUPD_STATUS_LOADING, 1, "own-name");


	/* load engine */
  FuEngine *engine = fu_engine_new();
	g_signal_connect(FU_ENGINE(engine),
			 "changed",
			 G_CALLBACK(fu_embed_engine_changed_cb),
       NULL);
	g_signal_connect(FU_ENGINE(engine),
			 "device-added",
			 G_CALLBACK(fu_embed_engine_device_added_cb),
       NULL);
	g_signal_connect(FU_ENGINE(engine),
			 "device-removed",
			 G_CALLBACK(fu_embed_engine_device_removed_cb),
       NULL);
	g_signal_connect(FU_ENGINE(engine),
			 "device-changed",
			 G_CALLBACK(fu_embed_engine_device_changed_cb),
       NULL);
	g_signal_connect(FU_ENGINE(engine),
			 "device-request",
			 G_CALLBACK(fu_embed_engine_device_request_cb),
       NULL);
	g_signal_connect(FU_ENGINE(engine),
			 "status-changed",
			 G_CALLBACK(fu_embed_engine_status_changed_cb),
       NULL);
	if (!fu_engine_load(engine,
			    FU_ENGINE_LOAD_FLAG_COLDPLUG | FU_ENGINE_LOAD_FLAG_HWINFO |
				FU_ENGINE_LOAD_FLAG_REMOTES,
			    fu_progress_get_child(progress),
			    &error)) {
		g_prefix_error(&error, "failed to load engine: ");
	}

  if (error) {
    printf("err: %s\n", error->message);
  }
}

/*
 * Copyright (C) 2018 Richard Hughes <richard@hughsie.com>
 * Copyright (C) 2019 Aleksander Morgado <aleksander@aleksander.es>
 *
 * SPDX-License-Identifier: LGPL-2.1+
 */

#ifndef __FU_MM_DEVICE_H
#define __FU_MM_DEVICE_H

#include <fwupdplugin.h>

#include <libmm-glib.h>

#define FU_TYPE_MM_DEVICE (fu_mm_device_get_type())
G_DECLARE_FINAL_TYPE(FuMmDevice, fu_mm_device, FU, MM_DEVICE, FuDevice)

FuMmDevice *
fu_mm_device_new(FuContext *ctx, MMManager *manager, MMObject *omodem);
FuUsbDevice *
fu_mm_device_get_usb_device(FuMmDevice *self);
void
fu_mm_device_set_usb_device(FuMmDevice *self, FuUsbDevice *usb_device);
const gchar *
fu_mm_device_get_inhibition_uid(FuMmDevice *device);
const gchar *
fu_mm_device_get_detach_fastboot_at(FuMmDevice *device);
gint
fu_mm_device_get_port_at_ifnum(FuMmDevice *device);
gint
fu_mm_device_get_port_qmi_ifnum(FuMmDevice *device);
gint
fu_mm_device_get_port_mbim_ifnum(FuMmDevice *device);
MMModemFirmwareUpdateMethod
fu_mm_device_get_update_methods(FuMmDevice *device);

/* support for udev-based devices */
typedef struct {
	gchar *inhibited_uid;
	gchar *physical_id;
	gchar *vendor;
	gchar *name;
	gchar *version;
	GPtrArray *guids;
	MMModemFirmwareUpdateMethod update_methods;
	gchar *detach_fastboot_at;
	gint port_at_ifnum;
	gint port_qmi_ifnum;
	gint port_mbim_ifnum;
} FuPluginMmInhibitedDeviceInfo;

FuPluginMmInhibitedDeviceInfo *
fu_plugin_mm_inhibited_device_info_new(FuMmDevice *device);
void
fu_plugin_mm_inhibited_device_info_free(FuPluginMmInhibitedDeviceInfo *info);
G_DEFINE_AUTOPTR_CLEANUP_FUNC(FuPluginMmInhibitedDeviceInfo,
			      fu_plugin_mm_inhibited_device_info_free);

FuMmDevice *
fu_mm_device_udev_new(FuContext *ctx, MMManager *manager, FuPluginMmInhibitedDeviceInfo *info);
void
fu_mm_device_udev_add_port(FuMmDevice *device,
			   const gchar *subsystem,
			   const gchar *path,
			   gint ifnum);

#endif /* __FU_MM_DEVICE_H */

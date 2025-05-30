/*
 * Copyright (C) 2021 Gaël PORTAY <gael.portay@collabora.com>
 *
 * SPDX-License-Identifier: LGPL-2.1+
 */

#pragma once

typedef struct {
	guint8 reg;
	guint8 expected_val;
} FuGenesysWaitFlashRegisterHelper;

typedef struct __attribute__((packed)) {
	guint8 tool_string_version; /* 0xff = not supported */

	/* byte arrays are ASCII encoded and not NUL terminated */
	guint8 mask_project_code[4];
	guint8 mask_project_hardware[1]; /* 0=a, 1=b... */
	guint8 mask_project_firmware[2]; /* 01,02,03... */
	guint8 mask_project_ic_type[6];	 /* 352310=GL3523-10 (ASCII string) */

	guint8 running_project_code[4];
	guint8 running_project_hardware[1];
	guint8 running_project_firmware[2];
	guint8 running_project_ic_type[6];

	guint8 firmware_version[4]; /* MMmm=MM.mm (ASCII string) */
} FuGenesysStaticToolString;

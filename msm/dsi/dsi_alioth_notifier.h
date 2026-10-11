/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _DSI_ALIOTH_NOTIFIER_H_
#define _DSI_ALIOTH_NOTIFIER_H_

#include <linux/string.h>
#include "dsi_display.h"
#if IS_ENABLED(CONFIG_XIAOMI_DRM_NOTIFIER)
#include <drm/drm_notifier_mi.h>
#endif

/* Preserve the donor touch/fingerprint blank-event ordering. */
static inline void dsi_alioth_notify(struct dsi_display *display,
		unsigned long event, int power_mode)
{
#if IS_ENABLED(CONFIG_XIAOMI_DRM_NOTIFIER)
	struct mi_drm_notifier data = {
		.id = MSM_DRM_PRIMARY_DISPLAY,
		.data = &power_mode,
	};

	if (display && display->display_type &&
	    !strcmp(display->display_type, "primary"))
		mi_drm_notifier_call_chain(event, &data);
#endif
}

#if !IS_ENABLED(CONFIG_XIAOMI_DRM_NOTIFIER)
#define MI_DRM_EVENT_BLANK 0x01
#define MI_DRM_EARLY_EVENT_BLANK 0x02
#define MI_DRM_PRE_EVENT_BLANK 0x03
#endif
#endif

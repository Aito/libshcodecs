#ifndef __LOCK_VPU_H__
#define __LOCK_VPU_H__

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_UIOMUX

#include <uiomux/uiomux.h>

#define LOCK_VPU(ux) uiomux_lock (ux, UIOMUX_SH_VPU);
#define UNLOCK_VPU(ux) uiomux_unlock (ux, UIOMUX_SH_VPU);

#else

#include "m4driverif.h"

#define LOCK_VPU(ux) pthread_mutex_lock(&vpu_mutex);
#define UNLOCK_VPU(ux) pthread_mutex_unlock(&vpu_mutex);

#endif

#endif /* __LOCK_VPU_H__ */

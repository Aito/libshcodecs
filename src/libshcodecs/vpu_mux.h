#ifndef __VPU_MUX_H__
#define __VPU_MUX_H__

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_UIOMUX

#include <uiomux/uiomux.h>

extern UIOMux * global_uiomux;

#define VPU_LOCK(ux) uiomux_lock (ux, UIOMUX_SH_VPU); global_uiomux = ux;
#define VPU_UNLOCK(ux) uiomux_unlock (ux, UIOMUX_SH_VPU);

#define VPU_MALLOC(ux,size,align) uiomux_malloc (ux, UIOMUX_SH_VPU, size, align)
#define VPU_FREE(ux,address,size) uiomux_free (ux, UIOMUX_SH_VPU, address, size)

#else

#include "m4driverif.h"

#define VPU_LOCK(ux) pthread_mutex_lock(&vpu_mutex);
#define VPU_UNLOCK(ux) pthread_mutex_unlock(&vpu_mutex);

#define VPU_MALLOC(ux,size,align) m4iph_sdr_malloc(size, align)
#define VPU_FREE(ux,address,size) m4iph_sdr_free(address, size)

#endif

#endif /* __VPU_MUX_H__ */

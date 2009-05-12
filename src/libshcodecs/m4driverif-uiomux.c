/*
 * libshcodecs: A library for controlling SH-Mobile hardware codecs
 * Copyright (C) 2009 Renesas Technology Corp.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA  02110-1301 USA
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sh7722_vpu.h>
#include <m4iph_vpu4.h>
#include <avcbd.h>
#include "avcbd_optionaldata.h"
#include "avcbd_inner_typedef.h"

#include <uiomux/uiomux.h>

static int sleep_time;

int avcbd_idr_adjust(void *context);

/*
 * A globally managed UIOMux * handle.
 * This must only be modified within VPU_LOCK()
 */
UIOMux * global_uiomux = NULL;

/* User defined functions as specified by the Encoder/Decoder middleware
 * documents.
 */
void m4iph_sleep_time_init(void)
{
	sleep_time = 0;
}

unsigned long m4iph_sleep_time_get(void)
{
	return sleep_time;
}

void m4iph_start(void)
{
}

long m4iph_sleep(void)
{
	struct timeval tv, tv1;
	struct timezone tz;
	long tm;

	gettimeofday(&tv, &tz);

        uiomux_sleep (global_uiomux, UIOMUX_SH_VPU);
	m4iph_vpu4_int_handler();

	gettimeofday(&tv1, &tz);
	tm = (tv1.tv_usec - tv.tv_usec) / 1000;
	if (tm < 0) {
		tm = 1000 - (tv.tv_usec - tv1.tv_usec) / 1000;
	}
	sleep_time += tm;
	/* avcbd_idr_adjust(global_context); */
	return 0;
}

void m4iph_restart(void)
{
	/* Do nothing for Linux */
#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);
#endif
}

int m4iph_vpu_open(void)
{
        /* We call uiomux_open() already from the initialization */
#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);
#endif
	return 0;
}

void m4iph_vpu_close(void)
{
#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);
#endif
}

unsigned long m4iph_reg_table_read(unsigned long *addr,
				   unsigned long *data, long nr_longs)
{
	unsigned long *reg_base;
	int k;

#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);
#endif

        uiomux_get_mmio (global_uiomux, UIOMUX_SH_VPU, NULL, NULL, (void *)&reg_base);
	reg_base += ((unsigned long) addr - VP4_CTRL) / 4;

	for (k = 0; k < nr_longs; k++)
		data[k] = reg_base[k];

#if DEBUG
	for (offset = 0; offset < nr_longs; offset++)
		fprintf(stderr, "%s: addr = %p, data = %08lx\n", __FUNCTION__,
		       addr++, *data++);
#endif
	return nr_longs;
}

void m4iph_reg_table_write(unsigned long *addr, unsigned long *data,
			   long nr_longs)
{
	unsigned long *reg_base;
	int k;

#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);
#endif

        uiomux_get_mmio (global_uiomux, UIOMUX_SH_VPU, NULL, NULL, (void *)&reg_base);
	reg_base += ((unsigned long) addr - VP4_CTRL) / 4;

	for (k = 0; k < nr_longs; k++)
		reg_base[k] = data[k];

#if DEBUG
	for (offset = 0; offset < nr_longs; offset++) {
		fprintf(stderr, "%s: addr = %p, data = %08lx\n", __FUNCTION__, addr,
		       *data);
		addr++;
		data++;
	}
#endif
}

int m4iph_sdr_open(void)
{
#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);
#endif
	return 0;
}

void m4iph_sdr_close(void)
{
#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);
#endif
}

void *m4iph_map_sdr_mem(void *address, int size)
{
        unsigned long mem_base;
        void * iomem;

#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);
#endif
	uiomux_get_mem (global_uiomux, UIOMUX_SH_VPU, &mem_base, NULL, &iomem);
	return iomem + ((unsigned long) address - mem_base);
}

int m4iph_unmap_sdr_mem(void *address, int size)
{
#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);
#endif
	return 0;
}

int m4iph_sync_sdr_mem(void *address, int size)
{
#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);
#endif
	return 0;
}

unsigned long m4iph_sdr_read(unsigned char *address, unsigned char *buffer,
			     unsigned long count)
{
	unsigned char *buf;
	unsigned long addr;
        unsigned long mem_base, mem_size;
	int roundoff;
	int pagesize = getpagesize();

#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);
#endif

	uiomux_get_mem (global_uiomux, UIOMUX_SH_VPU, &mem_base, &mem_size, NULL);

	if ((unsigned long) address + count >= (mem_base+mem_size)
	    || (unsigned long) address < mem_base) {
		fprintf(stderr, "%s: Invalid read from SDR memory. ",
			__FUNCTION__);
		fprintf(stderr, "address = %p, count = %ld\n", address,
			count);
		return 0;
	}
	addr = (unsigned long) address & ~(pagesize - 1);
	roundoff = (unsigned long) address - addr;
	buf =
	    (unsigned char *) m4iph_map_sdr_mem((void *) addr,
						count + roundoff);
	if (buf == NULL) {
		fprintf(stderr, "%s: Aborting since mmap() failed.\n",
		       __FUNCTION__);
		fprintf(stderr, "%s: address = %p, buffer = %p, count = %ld\n",
		       __FUNCTION__, address, buffer, count);
		abort();
	}
	memcpy(buffer, buf + roundoff, count);
	m4iph_unmap_sdr_mem(buf, count + roundoff);
	return count;
}

/* Same arg order as memcpy; does alignment on dest */
void m4iph_sdr_write(unsigned char *address, unsigned char *buffer,
		     unsigned long count)
{
	unsigned char *buf;
	unsigned long addr;
        unsigned long mem_base, mem_size;
	int roundoff;
	int pagesize = getpagesize();

#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);
#endif

	uiomux_get_mem (global_uiomux, UIOMUX_SH_VPU, &mem_base, &mem_size, NULL);

	if ((unsigned long) address + count >= (mem_base+mem_size)
	    || (unsigned long) address < mem_base) {
		fprintf(stderr, "%s: Invalid write to SDR memory. ",
			__FUNCTION__);
		fprintf(stderr, "address = %p, count = %ld\n", address,
			count);
		return;
	}
	addr = (unsigned long) address & ~(pagesize - 1);
	roundoff = (unsigned long) address - addr;
	buf =
	    (unsigned char *) m4iph_map_sdr_mem((void *) addr,
						count + roundoff);
	if (buf == NULL) {
		fprintf(stderr, "%s: Aborting since mmap() failed.\n",
		       __FUNCTION__);
		fprintf(stderr, "%s: address = %p, buffer = %p, count = %ld\n",
		       __FUNCTION__, address, buffer, count);
		abort();
	}
	memcpy(buf + roundoff, buffer, count);
	m4iph_unmap_sdr_mem(buf, count + roundoff);
}

void m4iph_sdr_memset(unsigned long *address, unsigned long data,
		      unsigned long count)
{
	unsigned char *buf;
	unsigned long addr;
	int roundoff;
	int pagesize = getpagesize();

#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);
#endif

	addr = (unsigned long) address & ~(pagesize - 1);
	roundoff = (unsigned long) address - addr;
	buf =
	    (unsigned char *) m4iph_map_sdr_mem((void *) addr,
						count + roundoff);
	if (buf == NULL) {
		fprintf(stderr, "%s: Aborting since mmap() failed.\n",
		       __FUNCTION__);
		fprintf(stderr, "%s: address = %p, data = %08lx, count = %ld\n",
		       __FUNCTION__, address, data, count);
		abort();
	}
	memset(buf, data, count);
	m4iph_unmap_sdr_mem(buf, count + roundoff);
}

/* Allocate sdr memory */
void *m4iph_sdr_malloc(unsigned long count, int align)
{
	unsigned long ret;
	int size;

#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);

        fprintf (stderr, "%s: global_uiomux %x\n", global_uiomux);
#endif

        return uiomux_malloc (global_uiomux, UIOMUX_SH_VPU, count, align);
}

void m4iph_sdr_free(void *address, unsigned long count)
{
#ifdef DEBUG
        fprintf (stderr, "%s: IN\n", __func__);
#endif

        uiomux_free (global_uiomux, UIOMUX_SH_VPU, address, count);
}

#if 0
float logf(float x)
{
	return (float) log((double) x);
}

float ceilf(float x)
{
	return (float) ceil((double) x);
}
#endif

void m4iph_avcbd_perror(char *msg, int error)
{
	fprintf(stderr, "%s: ", msg);
	switch (error) {
	case AVCBD_PARAM_ERROR:
		fprintf(stderr, "Parameter Error\n");
		break;
	case AVCBD_PIC_TIMEOUT:
		fprintf(stderr, "Timeout\n");
		break;
	case AVCBD_PIC_ABORT:
		fprintf(stderr, "Abort\n");
		break;
	case AVCBD_PIC_EOS:
		fprintf(stderr, "End of Stream\n");
		break;
	case AVCBD_PIC_LARGE:
		fprintf(stderr, "Picture too large\n");
		break;
	case AVCBD_PIC_FEWERMB:
		fprintf(stderr, "AVCBD_PIC_FEWERMB Error\n");
		break;
	case AVCBD_PIC_FMTERROR:
		fprintf(stderr, "Format Error\n");
		break;
	case AVCBD_PIC_ERROR:
		fprintf(stderr, "Picture Error\n");
		break;
	case AVCBD_MB_OVERRUN:
		fprintf(stderr, "Overrun Error\n");
		break;
	case AVCBD_ILLEGAL_DATA:
		fprintf(stderr, "Illegal Data\n");
		break;
	case AVCBD_ILLEGAL_CODE:
		fprintf(stderr, "Illegal Code\n");
		break;
	case AVCBD_ILLEGAL_MTYPE:
		fprintf(stderr, "Illegal Mtype\n");
		break;
	case AVCBD_BUFFER_OVERRUN:
		fprintf(stderr, "Buffer Overrun\n");
		break;
	case AVCBD_PIC_EXCESS_FRAME:
		fprintf(stderr, "Excess Frames\n");
		break;
	case AVCBD_PIC_EXCESS_PPS:
		fprintf(stderr, "Excess PPS\n");
		break;
	case AVCBD_TEMPORARY_BUFFER_SHORT_ERROR:
		fprintf(stderr, "Temporary buffer too short\n");
		break;
	case AVCBD_VPU_ERROR:
		fprintf(stderr, "General VPU Error\n");
		break;
	default:
		fprintf(stderr, "Unknown error %d\n", error);
	}
}

void m4iph_avcbe_perror(char *msg, int error)
{
	fprintf(stderr, "%s: %d\n", msg, error);
}

void avcbd_get_time_code(long h, long m, long s)
{
}

int vpu4_clock_on(void)
{
	return 0;
}

int vpu4_clock_off(void)
{
	return 0;
}

int avcbd_idr_adjust(void *context)
{
	TAVCBD_VARIABLES *var;

	if ((!context) || ((int) context & 3)) {
		return AVCBD_PARAM_ERROR;
	}
	var = (TAVCBD_VARIABLES *) context;
	if (var->id != 1)
		return 0;
	if (var->seq_param->nal_unit_type == 5) {
		var->poc_info.prev_frame_num = 0;
	}
	return 0;
}

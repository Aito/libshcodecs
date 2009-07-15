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

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <setjmp.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include <shcodecs/shcodecs_encoder.h>

#include "avcbencsmp.h"		/* User Application Sample Header */

#include "ControlFileUtil.h"

#define MAX_ENCODERS 8

int open_input_image_file(APPLI_INFO *);
int load_1frame_from_image_file(SHCodecs_Encoder * encoder, APPLI_INFO * appli_info);

int open_output_file(APPLI_INFO *);
int select_inputfile_set_param(SHCodecs_Encoder * encoder, APPLI_INFO * appli_info);

static void usage (const char * progname)
{
        printf ("Usage: %s <control file>\n", progname);
        printf ("Encode a video file using the SH-Mobile VPU\n");
        printf ("\nPlease report bugs to <linux-sh@vger.kernel.org>\n");
}

struct shenc {
        APPLI_INFO ainfo; /* Application Data */
        SHCodecs_Encoder *encoder; /* Encoder */
	long stream_type;
};

static pthread_t childs[MAX_ENCODERS];
static struct shenc * shencs[MAX_ENCODERS];

/* SHCodecs_Encoder_Input callback for acquiring an image from the input file */
static int get_input(SHCodecs_Encoder * encoder, void *user_data)
{
	struct shenc * shenc = (struct shenc *)user_data;
	return load_1frame_from_image_file(shenc->encoder, &shenc->ainfo);
}

/* SHCodecs_Encoder_Output callback for writing encoded data to the output file */
static int write_output(SHCodecs_Encoder * encoder,
			unsigned char *data, int length, void *user_data)
{
	struct shenc * shenc = (struct shenc *)user_data;
	return fwrite(data, 1, length, shenc->ainfo.output_file_fp);
}

void sig_handler(int sig)
{
#ifdef DEBUG
        fprintf (stderr, "Got signal %d\n", sig);
#endif

        /* Send ourselves the signal: see http://www.cons.org/cracauer/sigint.html */
	signal(sig, SIG_DFL);
	kill(getpid(), sig);
}

static int setup_file (char * filename, int i)
{
	struct shenc * shenc;
	int return_code;

        shenc = malloc (sizeof(*shenc));
        if (shenc == NULL) return -1;

	shencs[i] = shenc;

        memset (shenc, 0, sizeof(*shenc));

	strcpy(shenc->ainfo.ctrl_file_name_buf, filename);
	return_code = GetFromCtrlFTop((const char *)shenc->ainfo.ctrl_file_name_buf,
				      &shenc->ainfo, &shenc->stream_type);
	if (return_code < 0) {
		perror("Error opening control file");
		return (-1);
	}

	/* Input path */
	snprintf(shenc->ainfo.input_file_name_buf, 256, "%s/%s",
		 shenc->ainfo.buf_input_yuv_file_with_path,
		 shenc->ainfo.buf_input_yuv_file);
	fprintf(stderr, "Input file: %s\n", shenc->ainfo.input_file_name_buf);

	/* Output path */
        if (!strcmp (shenc->ainfo.buf_output_stream_file, "-")) {
                snprintf (shenc->ainfo.output_file_name_buf, 256, "-");
        } else {
	        snprintf(shenc->ainfo.output_file_name_buf, 256, "%s/%s",
	        	 shenc->ainfo.buf_output_directry,
	        	 shenc->ainfo.buf_output_stream_file);
        }
	fprintf(stderr, "Output file: %s\n", shenc->ainfo.output_file_name_buf);

        shenc->ainfo.ceu = NULL;

	shenc->encoder = shcodecs_encoder_init(shenc->ainfo.xpic, shenc->ainfo.ypic, shenc->stream_type);

	shcodecs_encoder_set_input_callback(shenc->encoder, get_input, shenc);
	shcodecs_encoder_set_output_callback(shenc->encoder, write_output, shenc);

	/* open input YUV data file */
	return_code = open_input_image_file(&shenc->ainfo);
	if (return_code != 0) {	/* error */
		perror("Error opening input file");
		return (-6);
	}

	/* open output file */
	return_code = open_output_file(&shenc->ainfo);
	if (return_code != 0) {	/* error */
		perror("Error opening output file");
		return (-6);
	}

	/* set parameters for use in encoding */
	return_code = select_inputfile_set_param(shenc->encoder, &shenc->ainfo);
	if (return_code == -1) {	/* error */
		fprintf (stderr, "select_inputfile_set_param ERROR! \n");
		return (-3);
	}

	return 0;
}

static void encode_shenc (struct shenc * shenc)
{
	int encode_return_code;

	encode_return_code = shcodecs_encoder_run(shenc->encoder);

	if (encode_return_code < 0) {
		fprintf(stderr, "Error encoding, error code=%d\n",
			encode_return_code);
	} else {
		fprintf(stderr, "Encode Success\n");
	}

        if (shenc->encoder != NULL)
                shcodecs_encoder_close(shenc->encoder);

	pthread_exit (NULL);

	return;
}

int main(int argc, char *argv[])
{
	int i;

	if (argc < 2 || !strncmp (argv[1], "-h", 2) || !strncmp (argv[1], "--help", 6)) {
		usage (argv[0]);
		return -1;
        }

	memset (childs, 0, sizeof(childs));
	memset (shencs, 0, sizeof(shencs));

        signal (SIGINT, sig_handler);
        signal (SIGPIPE, sig_handler);

	for (i=0; i < argc-1; i++) {
	       if (setup_file (argv[i+1], i) != 0)
		       shencs[i] = NULL;
	}

	for (i=0; i < argc-1; i++) {
		if (shencs[i])
	                pthread_create (&childs[i], NULL, encode_shenc, shencs[i]);
	}

	for (i=0; i < argc-1; i++) {
		char * ret;

		fprintf (stderr, "Waiting on child %d...\n", i);

	        if (shencs[i] && childs[i])
			pthread_join (childs[i], &ret);
	}

        return 0;
}

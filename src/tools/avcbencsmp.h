/*****************************************************************************
*                                                                            *
*  SuperH MEPG-4 Video Encode Library                                        *
*    (Application Sample source for VPU4)                                    *
*                                                                            *
*    Copyright (C) Renesas Technology Corp., 2005. All rights reserved.      *
*                                                                            *
*    Version@2.0 : avcbencsmp.h (for MPEG-4 and H.264)						 *
*				2005/07/27 14:50 Renesas Technology Corp.   *
*                                                                            *
*****************************************************************************/

#ifndef	AVCBENCSMP_H
#define	AVCBENCSMP_H

#include "capture.h"
//#include "encoder_private.h"

//#define MAX_D1

#define CAPTURE_VGA 1

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MAX_D1
/*----------------------------------------------------------*/
/*       Image width x Image height x 1.5                   */
/*----------------------------------------------------------*/
#define WIDTH_HEIGHT_1_5	622080	/* 622080=720 x 576 x 1.5(D1 Size) */
#define MAX_FRAME 2
/*----------------------------------------------------------*/
/*       Other work-field area size                         */
/*----------------------------------------------------------*/
#define MY_WORK_AREA_SIZE	1024*512

/*----------------------------------------------------------*/
/*       Stream-output buffer size for 1 frame              */
/*----------------------------------------------------------*/
#define MY_STREAM_BUFF_SIZE	1024*256     /* byte unit */	/* this value must be multiple of 32 */

#elif defined(CAPTURE_VGA)
/*----------------------------------------------------------*/
/*       Image width x Image height x 1.5                   */
/*----------------------------------------------------------*/
#define WIDTH_HEIGHT_1_5	460800	/* 460800=640 x 480 x 1.5(VGA Size) */
#define MAX_FRAME 2
/*----------------------------------------------------------*/
/*       Other work-field area size                         */
/*----------------------------------------------------------*/
#define MY_WORK_AREA_SIZE	(101376*4) /*76800 One stream */	/* QVGA */

/*----------------------------------------------------------*/
/*       Stream-output buffer size for 1 frame              */
/*----------------------------------------------------------*/
#define MY_STREAM_BUFF_SIZE	(400000)     /* byte unit */	/* this value must be multiple of 32 */

#else				/* Not D1, or CAPTURE_VGA */
/*----------------------------------------------------------*/
/*       Image width x Image height x 1.5                   */
/*----------------------------------------------------------*/
#define WIDTH_HEIGHT_1_5	152064	/* 115200=320 x 240 x 1.5(QVGA Size) */
#define MAX_FRAME 4
/*----------------------------------------------------------*/
/*       Other work-field area size                         */
/*----------------------------------------------------------*/
#define MY_WORK_AREA_SIZE	101376 /*76800 One stream */	/* QVGA */

/*----------------------------------------------------------*/
/*       Stream-output buffer size for 1 frame              */
/*----------------------------------------------------------*/
#define MY_STREAM_BUFF_SIZE	160000     /* byte unit */	/* this value must be multiple of 32 */
#endif

/*----------------------------------------------------------*/
/*       Output buffer size for EOS                         */
/*----------------------------------------------------------*/
#define MY_END_CODE_BUFF_SIZE 32	/* byte unit */

/*----------------------------------------------------------*/
/*       SPS-stream-output buffer size                      */
/*----------------------------------------------------------*/
#define MY_SPS_STREAM_BUFF_SIZE 256 /* byte unit */	/* this value must be multiple of 32 */

/*----------------------------------------------------------*/
/*       PPS-stream-output buffer size                      */
/*----------------------------------------------------------*/
#define MY_PPS_STREAM_BUFF_SIZE 256 /* byte unit */	/* this value must be multiple of 32 */

/*----------------------------------------------------------*/
/*       SEI-stream-output buffer size                      */
/*----------------------------------------------------------*/
	/*#define MY_SEI_STREAM_BUFF_SIZE       175000 *//* Level 1 */
	/*#define MY_SEI_STREAM_BUFF_SIZE       2000000 *//* Level 2 */
	/*#define MY_SEI_STREAM_BUFF_SIZE       10000000 *//* Level 3 */
#define MY_SEI_STREAM_BUFF_SIZE	100000

/*----------------------------------------------------------*/
/*    Filler-data-stream-output buffer size                 */
/*----------------------------------------------------------*/
#define MY_FILLER_DATA_BUFF_SIZE 256

/*----------------------------------------------------------*/
/* Buffer size which is used if the avcbe_encode_picture function returns on each 1-slice */
/*----------------------------------------------------------*/
#define MY_DUMMY_NAL_BUFF_SIZE (1024*256)

/*----------------------------------------------------------*/
/*    Input YUV-data buffer size			                */
/*----------------------------------------------------------*/
//#define MY_INPUT_YUV_DATA_BUFF_SIZE (WIDTH_HEIGHT_1_5 *10)

// ORIG #define  OUTPUT_BUF_SIZE (50*1024)
#define  OUTPUT_BUF_SIZE (256*1024)
//#define  OUTPUT_BUF_SIZE (256*1024*4)

/*----- structures -----*/

#if 0
	typedef struct {	/* add at Version2 */
		/* Table to set encoding parameter (for H.264 bitstream) */
		avcbe_vui_main_param vui_main_param;	/* the parameter of the avcbe_set_VUI_parameters function */

		char out_buffering_period_SEI;	/* whether output buffering_period SEI message (1:output, 2:NOT outputj */
		char out_pic_timing_SEI;	/* whether output picture_timing SEI message (1:output, 2:NOT outputj */
		char out_pan_scan_rect_SEI;	/* whether output filler_payload SEI message (1:output, 2:NOT outputj */
		char out_filler_payload_SEI;	/* whether output picture_timing SEI message (1:output, 2:NOT outputj */
		char out_recovery_point_SEI;	/* whether output recovery_point SEI message (1:output, 2:NOT outputj */
		char out_dec_ref_pic_marking_repetition_SEI;	/* whether output dec_ref_pic_marking_repetition SEI message (1:output, 2:NOT outputj */

		avcbe_sei_buffering_period_param sei_buffering_period_param;	/* the parameter of the avcbe_put_SEI_parameters function (1) */
		avcbe_sei_pic_timing_param sei_pic_timing_param;	/* the parameter of the avcbe_put_SEI_parameters function (2) */
		avcbe_sei_pan_scan_rect_param sei_pan_scan_rect_param;	/* the parameter of the avcbe_put_SEI_parameters function (3) */
		avcbe_sei_filler_payload_param sei_filler_payload_param;	/* the parameter of the avcbe_put_SEI_parameters function (4) */
		avcbe_sei_recovery_point_param sei_recovery_point_param;	/* the parameter of the avcbe_put_SEI_parameters function (5) */
	} OTHER_API_ENC_PARAM;
#endif



/*************** michioka ******************/
#if 1
	typedef struct {	/* add at Version2 */
		/* Table to set encoding parameter (for H.264 bitstream) */
		avcbe_vui_main_param vui_main_param;	/* the parameter of the avcbe_set_VUI_parameters function */

		char out_buffering_period_SEI;	/* whether output buffering_period SEI message (1:output, 2:NOT outputj */
		char out_pic_timing_SEI;	/* whether output picture_timing SEI message (1:output, 2:NOT outputj */
		char out_pan_scan_rect_SEI;	/* whether output filler_payload SEI message (1:output, 2:NOT outputj */
		char out_filler_payload_SEI;	/* whether output picture_timing SEI message (1:output, 2:NOT outputj */
		char out_recovery_point_SEI;	/* whether output recovery_point SEI message (1:output, 2:NOT outputj */
		char out_dec_ref_pic_marking_repetition_SEI;	/* whether output dec_ref_pic_marking_repetition SEI message (1:output, 2:NOT outputj */

		avcbe_sei_buffering_period_param sei_buffering_period_param;	/* the parameter of the avcbe_put_SEI_parameters function (1) */
		avcbe_sei_pic_timing_param sei_pic_timing_param;	/* the parameter of the avcbe_put_SEI_parameters function (2) */
		avcbe_sei_pan_scan_rect_param sei_pan_scan_rect_param;	/* the parameter of the avcbe_put_SEI_parameters function (3) */
		avcbe_sei_filler_payload_param sei_filler_payload_param;	/* the parameter of the avcbe_put_SEI_parameters function (4) */
		avcbe_sei_recovery_point_param sei_recovery_point_param;	/* the parameter of the avcbe_put_SEI_parameters function (5) */
	} OTHER_API_ENC_PARAM;

/* ���󥳡��ɼ¹Ծ��ι�¤�� */
	typedef struct {

		long frame_number_to_encode;	/* ���󥳡��ɤ���ե졼��� */

		long output_filler_enable;	/* CPB�Хåե��Υ����С��ե�����Filler���������뤫�ɤ��� *//* 050519 */
		char calc_PSNR_flag;	/* PSNR�򻻽Ф��뤫 AVCBE_ON(1)/AVCBE_OFF(0) */
		char yuv_CbCr_format;	/* YUV�ǡ�����ʽ��Ϥ��������ǥ����ɥե������ˤ�Cb,Cr�ǡ������¤ӽ��1:Cb����Cr������2:Cb0,Cr0,Cb1,Cr1,...��3:Cb��1�饤��ʬ,Cr��1�饤��ʬ,...�� *//* 050520 */

		char buf_input_yuv_file_with_path[256 + 8];	/* ����YUV�ե�����̾�ʥѥ��դ��� *//* 041201 */
		char buf_input_yuv_file[64 + 8];	/* ����YUV�ե�����̾�ʥѥ��ʤ��� */

		char buf_output_directry[256 + 8];	/* ������Υǥ��쥯�ȥ� *//* 041201 */
		char buf_output_stream_file[64 + 8];	/* ���ϥ��ȥ꡼��ե�����̾�ʥѥ��ʤ��� */
		unsigned char ref_frame_num;	/* ���ȥե졼�����1 or 2) (H.264�Τߡ� */
		long xpic;
		long ypic;
	} ENC_EXEC_INFO;	// MICHIOKA(2006-11-6)
#endif

	typedef struct {

		/* Table to store an encoding result (MPEG-4 bitstream) */

		/* Size of encoding result (byte unit) */

		/* Input imformation in encoding */

		/* The number of frames to encode. */
		long frame_number_to_encode;

#ifdef USE_PSNR
		/* PSNR�򻻽Ф��뤫��1:ON/0:OFF�� */
		long calc_PSNR_flag;
#endif				/* USE_PSNR */

		/* Input YUV file name and it's file pointer */
		char input_file_name_buf[256];	/* for stream-1 */
		FILE *input_yuv_fp;	/* for stream-1 */
		long yuv_CbCr_format;	/* YUV�ǡ�����ʽ��Ϥ��������ǥ����ɥե�������
					   ��Cb,Cr�ǡ������¤ӽ��1:Cb����Cr������2:Cb0,Cr0,Cb1,Cr1,...��
					   3:Cb��1�饤��ʬ,Cr��1�饤��ʬ,...�� */

		char output_file_name_buf[256];	/* ����m4v�ե�����̾ */
		char ctrl_file_name_buf[256];	/* ����YUV�ե�����̾ */

		/* encoding parameters */
		avcbe_encoding_property param;	/* for stream-1 */

		avcbe_other_options_h264 other_options_h264;	/* parameters to control details */

#if 1
		ENC_EXEC_INFO enc_exec_info;	/* FILE_USE����Ϥ��� *//* 050121 */

		long frame_no_increment;	/* Increment value of Frame number to be encoded for 
						   m4vse_encode_picture function */
		long b_vop_num;	/* The number of B-VOP to insert */

		/* Output imformation in encoding */

		unsigned long mb_num_of_picture;	/* total number of mb in picture */
		unsigned long slice_mb_counter;	/* counter of mb_num_of_picture */
		long SPS_PPS_header_bytes;	/* bytes of SPS and PPS */

		long return_code;	/* return_value of current frame or NAL *//* 041123 */

		long output_filler_enable;	/* enable flag to put Filler Data for CPB Buffer Over *//* 050519 */
#endif

		long error_return_function;	/* ID of the API function when error ocuured *//* add at Version2 */
		long error_return_code;	/* return_value of the API function when error ocuured *//* add at Version2 */
		long output_filler_data;	/* for FillerData(CPB  Buffer) *//* add at Version2 */
		FILE *output_file_fp;	/* for output stream-2 */

		sh_ceu *ceu;

	} APPLI_INFO;



/*-------------- proto-type declaration ----------------------------*/
/*--- the functions in avcbencsmp_common.c ---*/
	int avcbe_enc(long stream_type);
	int encode_1file(APPLI_INFO * appli_info, long stream_type);
	void set_VPU4_param(M4IPH_VPU4_INIT_OPTION * vpu4_param);
	void cat_output_stream(APPLI_INFO * appli_info,
			       avcbe_stream_info * context,
			       char *frame_stream_address,
			       long frame_stream_size);
	void DisplayMessage(char *message_text, int line_feed_flag);

/*--- the functions in avcbeinputuser.c ---*/
	int open_input_image_file(APPLI_INFO * appli_info);
// ORIG int load_1frame_from_image_file(APPLI_INFO *appli_info, avcbe_stream_info *context, unsigned long *addr_y, unsigned long *addr_c);
	int load_1frame_from_image_file(APPLI_INFO * appli_info,
					unsigned long *addr_y,
					unsigned long *addr_c);

#define ALIGN(a, w) (void *)(((unsigned long)(a) + (w) - 1) & ~((w) - 1))

#ifdef __cplusplus
}
#endif
#endif				/* AVCBENCSMP */

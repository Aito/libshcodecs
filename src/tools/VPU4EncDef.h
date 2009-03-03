/*****************************************************************************
*                                                                            *
*  SuperH MEPG-4 Video Encode Library                                        *
*                                                                            *
*    Copyright (C) Renesas Technology Corp., 2004-2005. All rights reserved. *
*                                                                            *
*    Version��1.0 :   VPU4EncDef.h                                           *
*                                 2005/06/01 18:00  Renesas Technology Corp. *
*                                                                            *
*****************************************************************************/

/*--------------------------------------------------------------------------*/
/*  1.000  2004.08.02  start codes (TOOL�ѤΥإå�)                         */
/*--------------------------------------------------------------------------*/

#ifndef	VPU4ENCDEF_H
#define	VPU4ENCDEF_H

/*----- structures -----*/

/* VPU4�ǥ��󥳡����ߥɥ��API�ؿ���avcbe_init_encode()������ˤ����ꤹ�륨�󥳡��ɾ��ι�¤�� */
typedef struct {
	unsigned char ref_frame_num;	/* ���ȥե졼�����1 or 2) (H.264�Τߡ� */

	long weightdQ_enable;
	TAVCBE_WEIGHTEDQ_CENTER weightedQ_info_center;	/* API�ؿ�avcbe_set_weightedQ()���Ϥ�����ι�¤��(1) */
	TAVCBE_WEIGHTEDQ_RECT weightedQ_info_rect;	/* API�ؿ�avcbe_set_weightedQ()���Ϥ�����ι�¤��(2) */
	TAVCBE_WEIGHTEDQ_USER weightedQ_info_user;	/* API�ؿ�avcbe_set_weightedQ()���Ϥ�����ι�¤��(3) */
	char weightedQ_table_filepath[256];	/* �Ť��դ��ơ��֥�ե�����Υѥ�̾ */

	avcbe_vui_main_param vui_main_param;	/* API�ؿ�avcbe_set_VUI_parameters()���Ϥ�����ι�¤�� (H.264�Τߡ� */

	char out_buffering_period_SEI;	/* SEI��å������ν��Ϥ�̵ͭ��1:���Ϥ���� */
	char out_pic_timing_SEI;
	char out_pan_scan_rect_SEI;
	char out_filler_payload_SEI;
	char out_recovery_point_SEI;
	char out_dec_ref_pic_marking_repetition_SEI;

	avcbe_sei_buffering_period_param sei_buffering_period_param;	/* API�ؿ�avcbe_put_SEI_parameters()���Ϥ�����ι�¤��(1) (H.264�Τߡ� */
	avcbe_sei_pic_timing_param sei_pic_timing_param;	/* API�ؿ�avcbe_put_SEI_parameters()���Ϥ�����ι�¤��(2) (H.264�Τߡ� */
	avcbe_sei_pan_scan_rect_param sei_pan_scan_rect_param;	/* API�ؿ�avcbe_put_SEI_parameters()���Ϥ�����ι�¤��(3) (H.264�Τߡ� */
	avcbe_sei_filler_payload_param sei_filler_payload_param;	/* API�ؿ�avcbe_put_SEI_parameters()���Ϥ�����ι�¤��(4) (H.264�Τߡ� */
	avcbe_sei_recovery_point_param sei_recovery_point_param;	/* API�ؿ�avcbe_put_SEI_parameters()���Ϥ�����ι�¤��(5) (H.264�Τߡ� */

	long use_I_PCM_flag;	/*I_PCM����Ϥ��뤫�ɤ�����041109 */

} OTHER_API_ENC_PARAM;

#if 0
/* ���󥳡��ɼ¹Ծ��ι�¤�� */
typedef struct {

	long frame_number_to_encode;	/* ���󥳡��ɤ���ե졼��� */

	long output_filler_enable;	/* CPB�Хåե��Υ����С��ե�����Filler���������뤫�ɤ��� *//* 050519 */
	char yuv_CbCr_format;	/* YUV�ǡ�����ʽ��Ϥ��������ǥ����ɥե������ˤ�Cb,Cr�ǡ������¤ӽ��1:Cb����Cr������2:Cb0,Cr0,Cb1,Cr1,...��3:Cb��1�饤��ʬ,Cr��1�饤��ʬ,...�� *//* 050520 */

	char buf_input_yuv_file_with_path[256 + 8];	/* ����YUV�ե�����̾�ʥѥ��դ��� *//* 041201 */
	char buf_input_yuv_file[64 + 8];	/* ����YUV�ե�����̾�ʥѥ��ʤ��� */

	char buf_output_directry[256 + 8];	/* ������Υǥ��쥯�ȥ� *//* 041201 */
	char buf_output_stream_file[64 + 8];	/* ���ϥ��ȥ꡼��ե�����̾�ʥѥ��ʤ��� */
	unsigned char ref_frame_num;	/* ���ȥե졼�����1 or 2) (H.264�Τߡ� */
	long xpic;
	long ypic;
} ENC_EXEC_INFO;
#endif

#endif				/* VPU4ENCDEF_H */

/*****************************************************************************
*                                                                            *
*  SuperH MEPG-4 Video Encode Library                                        *
*                                                                            *
*    Copyright (C) Renesas Technology Corp., 2004-2006. All rights reserved. *
*                                                                            *
*    Version��2.1 :   avcbe_inner.h                                          *
*                                 2006/03/07 22:33  Renesas Technology Corp. *
*                                                                            *
*****************************************************************************/


/*--------------------------------------------------------------------------*/
/*  1.000  2004.05.17  start codes                                          */
/*--------------------------------------------------------------------------*/


#ifndef	AVCBE_INNER_H
#define	AVCBE_INNER_H

#ifdef __cplusplus
extern "C" {
#endif

// michioka
//#include <stdio.h>
//#include <setjmp.h> /* 050523 */
//#include "avcbe.h"
//#include "m4iph_vpu4.h"

#define AVCBE_INTRA_OFFSET_NUM		52	/* ����ȥ饪�ե��åȤθĿ� */

/* avcbe_output_byte�ؿ��ν��ϥ�����(H.264 only) */
#define AVCBE_PUT_HEADER	0	/* 060125 */
#define AVCBE_PUT_END_CODE	1
#define AVCBE_PUT_OTHERS	2

/* avcbe_add_trailing_bits�ؿ��ν��ϥ�����(H.264 only) */
#define AVCBE_NOT_TRB	0	/* 060127 */
#define AVCBE_ADD_TRB	1	/* 060127 */

/*----- avcbe_rate_control_info_t��¤�� -----*/
	typedef struct {/*--- VPU4�ǥ��󥳡����Υ졼�ȥ���ȥ���ξ��� ---*/
		char quant_init_i;	/* I-VOP��Q����� */
		char quant_init_p;	/* P-VOP��Q����� */
		char quant_init_b;	/* B-VOP��Q����� */
		char use_dquant;	/* DQUANT�λ��ѥե饰 */
		char clip_dquant;	/* DQUANT����ΤȤ��˥���åפ����ϰ�(MPEG-4�ΤȤ��ϻ��Ѥ��ʤ�) */
		char gvop_m;	/* GVOP M��(1:Low Delay(B-VOP�ʤ�), 0:Low Delay�Ǥʤ�(B-VOP����))����������VPU4�ǥ��󥳡�����H.264���ȥ꡼��ǤϾ��=1 */
		char coef_cut_enable;	/* ��������̤ˤ��,Q�Υ��ꥢ������(H.264�ξ��Ͼ��0�����¤��ʤ���) */
		char quality_mode;	/* �̻Ҳ��¹ԥ⡼�ɡ�H.264�ξ��Ͼ��0�ʻ��Ѥ��ʤ���) */

		char quant_min;	/* Q�μ�ꤦ��Ǿ��� */
		char quant_max;	/* Q�μ�ꤦ������� */
		char vop_min_stuffing;	/* VOP�κ�������̤ˤʤ�褦�����åե��󥰤�ͤ�뤫��0:�ͤ�ʤ���1:�ͤ�롢��������H.264�ξ��Ͼ��0�ʻ��Ѥ��ʤ���) */
		char coef_enc_area;	/* MB���̻Ҳ��¹ԥ��ꥢ(H.264�ξ��Ͼ��0�ʻ��Ѥ��ʤ���) */
		char first_p_pic_out;	/* P�ԥ��������Ϥ�������0: �ޤ�P�ԥ��������Ϥ��Ƥ��ʤ���1: P�ԥ��������ϺѤߡ� */
		char ratecontrol_skip_enable;	/* �ե졼�ॹ���åפ�Ԥ����ݤ� */
		char dummy_3;	/* 4�Х��ȶ����ˤ��뤿��Υ��ߡ� */

		long cur_quant;	/* ����Υե졼���Q�͡ʼ�ꤦ���ͤ�char���Ǥ��ब������Ψ��long���ˤ���� */
		float cur_f_quant;	/* ����Υե졼���Q�͡ʼ�ꤦ���ͤ�char���Ǥ��ब������Ψ��long���ˤ���� *//* 041213 */
		long prev_quant;	/* ľ���Υե졼���Q�� */

		long Ni;	/* Nbr I-VOP remaining in GOV */
		long Np;	/* Nbr P-VOP remaining in GOV */
		long Nb;	/* Nbr B-VOP remaining in GOV */

		long d0i;	/* I-VOP virtual vuffer occupancy */
		long d0p;	/* P-VOP virtual vuffer occupancy */
		long d0b;	/* B-VOP virtual vuffer occupancy */

		unsigned long cpb_buf_size;	/* cpb ����Хåե������� *//* Rename vbv -> cpb 040729 Y.Funabashi */
		long cpb_buf_remain;	/* cpb �Хåե����� *//* Rename vbv -> cpb 040729 Y.Funabashi  */

		long vbv_buf_size;
		long vbv_buf_remain;

		long T_tm5;	/* mb_target_bits�Ȥ������ꤹ���� */
		long T_min;	/* vop_min_bits�Ȥ������ꤹ����(H.264�ξ��Ͼ��0�ʻ��Ѥ��ʤ���) */
		long T_max;	/* mb_max_bits�Ȥ������ꤹ���� */
		long r_tm5;	/* reaction_param�Ȥ������ꤹ���� */
		long d_tm5;	/* virtual_buf_size�Ȥ������ꤹ���� */

		long R_tm5;	/* remaining bits for GOV */

		float Xi;	/* I-VOP complexity *//* �ϡ��ɥ����ब�����������󥳡�������long���ʤΤǡ�float���Ȥɤ��餬�褤����Ƥ���뤳�� */
		float Xp;	/* P-VOP complexity */
		float Xb;	/* B-VOP complexity */

		unsigned long avcbe_target_Ipic_frame_bits;	/* ��ɸ��I�ԥ����������ƥӥå��� 040726 Add Y.Funabashi  */
		unsigned long avcbe_target_Ppic_frame_bits;	/* ��ɸ��P�ԥ����������ƥӥå��� 040726 Add Y.Funabashi  */
		unsigned long avcbe_cumurative_bits_rc_unit;	/* ���ӤΥԥ����������ƥӥå�������(RC���) 040726 Add Y.Funabashi  */
		unsigned long avcbe_cumurative_target_bits_rc_unit;	/* ��ɸ�Υԥ����������ƥӥå�������(RC���) 040726 Add Y.Funabashi  */
		unsigned long avcbe_rate_ctrl_type;	/* Q�ͥ���ȥ��륢�르�ꥺ���TM5�ˤ��뤫ForDSC�ˤ��뤫�����ե饰�� 041208 Add Y.Funabashi  *//* 041213 */
		unsigned long avcbe_cpb_start_size;	/* Q�ͥ���ȥ��륢�르�ꥺ���TM5�ˤ��뤫ForDSC�ˤ��뤫�����ե饰�� 041208 Add Y.Funabashi  *//* 041213 */

#ifdef SH
		unsigned long long avcbe_cumurative_bits;	/* ���ӤΥԥ����������ƥӥå������� 040726 Add Y.Funabashi  */
		unsigned long long avcbe_cumurative_target_bits;	/* ��ɸ�Υԥ����������ƥӥå������� 040726 Add Y.Funabashi  */
#else
		unsigned _int64 avcbe_cumurative_bits;	/* ���ӤΥԥ����������ƥӥå������� 040726 Add Y.Funabashi  *//* VC++�Ǥϡ�64bit Integer��_int64��������� 041020 */
		unsigned _int64 avcbe_cumurative_target_bits;	/* ��ɸ�Υԥ����������ƥӥå������� 040726 Add Y.Funabashi  *//* 041020 */
#endif

		unsigned long avcbe_activity_sum_pic;	/* �����ƥ��ӥƥ��ι���͡�1�ե졼��ʬ�� *//* 050422 */
		unsigned long avcbe_activity_sum_slice;	/* �����ƥ��ӥƥ��ι���͡�1���饤��ʬ�� *//* 050422 */
		unsigned long avcbe_activity_sum_mb;	/* �����ƥ��ӥƥ��ι���͡�1�ե졼��ʬ�ˤ�ޥ���֥�å����ǳ�ä�1/2������ *//* 050422 */

	} avcbe_rate_control_info_t;

/*----- avcbe nal unit info��¤�� -----*/
	typedef struct {
/*	long	avcbe_forbidden_zero_bit; */
		long avcbe_nal_ref_idc;
		long avcbe_nal_unit_type;
	} AVCBE_NAL_UNIT_INFO;

/*----- avcbe sequence parameter set info��¤�� -----*/
	typedef struct {
		long avcbe_profile_idc;
		long avcbe_constraint_set0_flag;	/* 041102 */
		long avcbe_constraint_set1_flag;	/* 041102 */
		long avcbe_constraint_set2_flag;	/* 041102 */
		long avcbe_level_idc;
		long avcbe_seq_param_set_ID;
		long avcbe_log2_max_frame_num_minus4;
		long avcbe_pic_order_cnt_type;
		long avcbe_log2_max_pic_order_cnt_lsb_minus4;
		long avcbe_delta_pic_order_always_zero_flag;
		long avcbe_offset_for_non_ref_pic;
		long avcbe_offset_for_top_to_bottom_field;
		long avcbe_num_ref_frames_in_pic_order_cnt_cycle;
		long avcbe_offset_for_ref_frame[256];
		long avcbe_num_ref_frames;
		long avcbe_gaps_in_frame_num_value_allowed_flag;
		long avcbe_pic_width_in_mbs_minus1;
		long avcbe_pic_height_in_map_units_minus1;
		long avcbe_frame_mbs_only_flag;
		long avcbe_mb_adaptive_frame_field_flag;
		long avcbe_direct_8x8_inference_flag;
		long avcbe_frame_cropping_flag;
		long avcbe_frame_crop_left_offset;
		long avcbe_frame_crop_right_offset;
		long avcbe_frame_crop_top_offset;
		long avcbe_frame_crop_bottom_offset;
		long avcbe_vui_parameters_present_flag;
		long avcbe_SPS_header_bits;	/* SPS�Υӥåȿ�(RateControl�ǻ���) */
	} AVCBE_SPS_INFO;

/*----- avcbe picture parameter set info��¤�� -----*/
	typedef struct {
		long avcbe_pic_parameter_set_ID;
		long avcbe_seq_param_set_ID;
		long avcbe_entropy_coding_mode_flag;
		long avcbe_pic_order_present_flag;
		long avcbe_num_slice_groups_minus1;
		long avcbe_num_ref_idx_l0_active_minus1;
		long avcbe_num_ref_idx_l1_active_minus1;
		long avcbe_weighted_pred_flag;
		long avcbe_weighted_bipred_idc;
		long avcbe_pic_init_qp_minus26;
		long avcbe_pic_init_qs_minus26;
		long avcbe_chroma_qp_index_offset;
		long avcbe_deblocking_filter_control_present_flag;	/* 041106 ̾���ѹ� */
		long avcbe_constrained_intra_pred_flag;
		long avcbe_redundant_pic_cnt_present_flag;
		long avcbe_PPS_header_bits;	/* PPS�Υӥåȿ�(RateControl�ǻ���) */
	} AVCBE_PPS_INFO;

	/*----- avcbe_slice_info��¤�� -----*//* �����Ȥ��ֹ���ѹ����ʤ�����!! */
	typedef struct {
		long avcbe_first_mb_in_slice;	/* (1) *//* M4IPH_VPU4_ENC��¤�ΤΥ��Фˤ��ͤ��Ϥ�(m4iph_avc_first_mb_in_slice) */
		long avcbe_slice_type;	/* (2) */
		long avcbe_pic_parameter_set_id;	/* (3) */
		long avcbe_frame_num;	/* (4) */
		long avcbe_prev_frame_num;	/* (5) *//* SEI�ǻ��Ȥ��뤿��˥Хå����åפ��� *//* 041214 */

		long avcbe_idr_pic_id;	/* (5) */
		long avcbe_pic_order_cnt_lsb;	/* (6) */
		long avcbe_delta_pic_order_cnt[2];	/* (7) */

		long avcbe_num_ref_idx_active_override_flag;	/* (8) */
		long avcbe_slice_qp_delta;	/* (9) */
		long avcbe_disable_deblocking_filter_idc;	/* (10) */
		long avcbe_slice_alpha_c0_offset_div2;	/* (11) *//* M4IPH_VPU4_ENC��¤�ΤΥ��Фˤ��ͤ��Ϥ�(m4iph_avc_alpha_offset) */
		long avcbe_slice_beta_offset_div2;	/* (12) *//* M4IPH_VPU4_ENC��¤�ΤΥ��Фˤ��ͤ��Ϥ�(m4iph_avc_beta_offset) */
		long avcbe_ref_pic_list_reordering_flag_l0;	/* (13) */
		long avcbe_reordering_of_pic_nums_idc;	/* (14) *//* 041106 */
		long avcbe_abs_diff_pic_num_minus1;	/* (15) *//* 041106 */
		long avcbe_no_output_od_prior_pics_flag;	/* (16) */
		long avcbe_long_term_reference_flag;	/* (17) */
		long avcbe_adaptive_ref_pic_making_mode_flag;	/* (18) */

		long avcbe_vop_type;	/* (19) *//* 1���avcbe_encode_picture()�Ǥ�ȯ���ӥå��� */
		long avcbe_deblock_disable;	/* (20) *//* M4IPH_VPU4_ENC��¤�ΤΥ��Фˤ��ͤ��Ϥ�(m4iph_avc_deblock_disable) */
		long avcbe_vop_quant;	/* (21) *//* M4IPH_VPU4_ENC��¤�ΤΥ��Фˤ��ͤ��Ϥ�(m4iph_vop_quant) */
		long avcbe_slice_next_quant;	/* (22) *//* 041118 */

		long avcbe_use_multi_reference;	/* (23) */
		long *avcbe_stream_out;	/* (24) *//* ���ȥ꡼��Хåե�(���饤���إå����ϻ��˻���) */
		long avcbe_slice_header_total_bits;	/* (25) *//* ���饤���إå��Υȡ�����ӥåȿ� */
		long avcbe_slice_total_bits_for_frame;	/* (26) *//* NALñ�̥��󥳡��ɤǤ�����ȯ���ӥå���(1�ե졼��ʬ) *//* 041118 */
		long avcbe_outputed_continue_bits;	/* (27) *//* continue�ؿ��ǽ��Ϥ����ӥåȿ���� *//* 050707 */
		long avcbe_last_slice_data_continue_bits;	/* (28) *//* continue�⡼�ɻ������饤���ν����Υǡ����Υӥåȿ� *//* 050707 */
		long avcbe_used_continue_in_slice;	/* (29) *//* continue�⡼�ɻ���1���饤������ǥ���ƥ��˥塼�������ɤ���(1��Ǥ⥳��ƥ��˥塼�������ϡ֣��פˤ���) *//* 050708 */

	} AVCBE_SLICE_INFO;

	/* avcbe.h�����ư����������ʳ����˸����ʤ������ *//* 050218 */

/* API�ؿ�avcbe_set_weightedQ()���Ϥ�����ι�¤��(3)avcbe_weightedQ_mode = AVCBE_WEIGHTEDQ_BY_USER�ΤȤ��˻��Ѥ��� */
	typedef struct {
		long avcbe_weight_type;	/* (1) */
		long avcbe_mode_for_bit1;	/* (2) */
		long avcbe_mode_for_bit2;	/* (3) */
		long avcbe_mode_for_bit3;	/* (4) */
		long avcbe_Qweight_for_bit1;	/* (5) */
		long avcbe_Qweight_for_bit2;	/* (6) */
		long avcbe_Qweight_for_bit3;	/* (7) */
		char *avcbe_MB_table;	/* (8) */
		unsigned long avcbe_num_of_MB_table;	/* (9) */
	} TAVCBE_WEIGHTEDQ_USER;

#if 0				/* 050526 */
/* API�ؿ�avcbe_set_VUI_parameters()���Ϥ������������ư�����ѥѥ�᡼���Τߡ�(H.264 only) */
	typedef struct {
		long avcbe_bit_rate_scale;	/* (1)        *//* �����Ǽ�ư���ꤹ����ͤ��ѹ� *//* 050524 */
		long avcbe_cpb_size_scale;	/* (2)        *//* �����Ǽ�ư���ꤹ����ͤ��ѹ� *//* 050524 */
	} avcbe_inner_vui_hrd_param;
#endif

/* API�ؿ�avcbe_set_SEI_parameters()���Ϥ�����ι�¤��(6)DEC_REF_PIC_MARKING_REPETITION�� (H.264 only) */
	typedef struct {
		unsigned long avcbe_original_idr_flag;	/* (1) */
		unsigned long avcbe_original_frame_num;	/* (2) */
		unsigned long avcbe_original_field_pic_flag;	/* (3) */
		unsigned long avcbe_original_bottom_field_flag;	/* (4) */

		unsigned long avcbe_use_output_of_prior_pics_long_term_reference;	/* (5) */
		unsigned long avcbe_no_output_of_prior_pics_flag;	/* (6) */
		unsigned long avcbe_adaptive_ref_pic_making_mode_flag;	/* (7) *//* 041122 */
		unsigned long avcbe_long_term_reference_flag;	/* (8) */
	} avcbe_sei_dec_ref_pic_marking_repetition_param;

/* Work area information */
	typedef struct {
		jmp_buf jmpbuf;	/* for setjmp, longjmp�� */
		jmp_buf jmpbuf2;	/* for setjmp, longjmp�� *//* �֤���=-4�ǻ��� *//* 050523 */
		unsigned char *work_area_top;	/* ���ץꥱ������󤫤��Ϥ��줿������ꥢ����Ƭ���ɥ쥹 */
		unsigned long alloc_work_area_size;	/* ������ꥢ�λ��Ѳ�ǽ�������ʥХ��ȿ��� */
		unsigned long used_work_area_size;	/* �嵭�Τ������ɤ��ޤǻ��Ѥ������ΥХ��ȿ� */
		unsigned long used_work_area_size_previous;	/* �������˥������Ȥ����Ȥ��˻��Ѥ��Ƥ����Х��ȿ� */
	} AVCBE_WORK_AREA_INFO_t;

	/* avcbe.h�����ư�������ޤǡʳ����˸����ʤ������ *//* 050218 */


/*----- avcbe_H264_stream_info_t��¤�� -----*/

	typedef struct AVCBE_H264_STREAM_INFO {
					/*--- ���󥳡�����������H.264���ȥ꡼�ऴ�Ȥξ��� ---*/

		/*      unsigned long avcbe_stream_ID; *//* ���Υ��ȥ꡼��μ����ֹ��0, 1, 2, ������, ���ȥ꡼�����1�� */
		unsigned long avcbe_stream_type;	/* ���Υ��ȥ꡼��Υ����ס�AVCBE_MPEG4, AVCBE_H263, AVCBE_H264�� */

		/* ���ȥ꡼�ऴ�ȤΥ�����󥰥������󥹥����å��� */
		long avcbe_stream_check_flg;

		AVCBE_WORK_AREA_INFO_t avcbe_work_area_info_for_stream;	/* ���Υ��ȥ꡼��Υ���ΰ�ξ��� */

		unsigned char *avcbe_stream_buff;	/* avcbe_encode_picture()���Ϥ��줿���ȥ꡼����ϥХåե�����Ƭ���ɥ쥹 */
		unsigned long avcbe_stream_buff_size;	/* Ʊ���ȥ꡼����ϥХåե��Υ�������ñ�̡��Х��ȡ� */
		unsigned long avcbe_used_stream_buff_size_bits;	/* ���ȥ꡼����ϥХåե��λ�����(���եȤǽ��Ϥ���ʬ�Τ�)�ʥХ��ȡ� */
		long avcbe_stream_output_flag;	/* =0�����-1���Хåե�����������­���� */

/*--- �����ޤǤϡ�MPEG-4�Ѥι�¤��m4vse_MPEG4_stream_info_t��Ʊ���������ˤ��Ƥ���ΤǤ�����ʤ����� ---*/

		long avcbe_output_type;	/* avcbe_encode_picture�ؿ��ΰ���output_type���� *//* 050105 */
		/* AU delimiter�� *//* 041115 */
		unsigned char *avcbe_AUD_stream_buff;	/* avcbe_encode_picture()���Ϥ��줿AUD�ѥ��ȥ꡼����ϥХåե�����Ƭ���ɥ쥹 */
		unsigned long avcbe_AUD_stream_buff_size;	/* Ʊ���ȥ꡼����ϥХåե��Υ�������ñ�̡��Х��ȡ� */

		/* SEI�� *//* 041210 */
		unsigned char *avcbe_SEI_stream_buff;	/* SEI�ѥ��ȥ꡼����ϥХåե�����Ƭ���ɥ쥹 */
		unsigned long avcbe_SEI_stream_buff_size;	/* Ʊ���ȥ꡼����ϥХåե��Υ�������ñ�̡��Х��ȡ� */

	/*--- �����ޤǤϡ�MPEG-4,H.263�Ѥι�¤��m4vse_MPEG4_stream_info_t��Ʊ���������ˤ��Ƥ��� ---*/
		/* ����¾�Υ��ȥ꡼�ऴ�ȤΥ����Х��ѿ� */
		char avcbe_EndEncoding;
		char avcbe_start_flag;	/* avcbe_encode_picture()�������뤵�줿�Ȥ���0:�����ܰʹߤΥե졼�ࡢ1:��Ƭ�Υե졼�ࡢ2:�����ܰʹߤΥե졼��Ǻƽ�������� */
		char avcbe_prev_start_flag;	/* avcbe_start_flag�ΥХå����å��� *//* 041224 */
		char avcbe_vpu_continue_flag;	/* =1:continue������=0:continue���Ƥʤ� *//* 050203 */

		/* API�ؿ�avcbe_init_encode()�ǻ��ꤵ�줿���󥳡��ɥѥ�᡼�� */
		avcbe_encoding_property avcbe_encode_option;
		avcbe_other_options_h264 avcbe_encode_other_opt_h264;

		/* ��������ΰ�ξ���ʥ�����ǥ����ɲ����ν����衢���ȥե졼��� */
		unsigned char avcbe_ldec_index;	/* ������ǥ����ɲ����ν�����(��������ΰ�Υ���ǥå����ֹ�:0 to N-1) �ե졼�����2�ʾ� */
		unsigned char avcbe_ref1_index;	/* ���ȥե졼��(��������ΰ�Υ���ǥå����ֹ�:0 to N-1) */
		unsigned char avcbe_ref2_index;	/* �ޥ����ե���󥹤ΤȤ�������Ū��ref1������β�������ΰ���λ��Ȳ������ֹ�:0 to N-1) */


		long avcbe_num_of_mb;	/* ���������ȹ⤵�����ޤ�ޥ���֥�å���(((��+15)/16)x16)x(((�⤵+15)/16)x16) */
		long avcbe_num_of_mb_4x;	/* 4���ܿ��ˤ����ޥ���֥�å��� *//* 041027 */

		long avcbe_vop_bits;	/* �ե졼��ñ�̤Υӥå�ȯ���� */
		long avcbe_out_stream_bits;	/* �ӥå�ȯ���̤��߷� */

		TAVCBE_FMEM avcbe_captbuf[1];	/* ����ץ�������ΰ� */

		unsigned char avcbe_nrefframe;	/* ���ȥե졼���(VPU4�ǥ��󥳡����Ǥ�1 or 2) */

		unsigned char avcbe_nldecfmem;	/* ��������ΰ�Υե졼��� */
		TAVCBE_FMEM *avcbe_ldecbuf;	/* ��������ΰ�Υ��ɥ쥹�ơ��֥�ʥե졼�����2�ʾ�Ǿ�¤ʤ��Ȥ��롣������255�ޤǡ� */

		unsigned char avcbe_npfiltfmem;	/* �ݥ��ȥե��륿�����ΰ�Υե졼��� */
		TAVCBE_FMEM avcbe_pfiltfbuf[1];	/* �ݥ��ȥե��륿�����ΰ� */

		/* 0x03�������������Ѥ�temp�Хåե� *//* 041128 */
		/* avcbe_output_byte()�ǽ��Ϥ��Ƥ�������4byteñ�̤��������Ƥ����Τǡ�����ñ�̤�٤���0x000000�����ɤ����Ϥ����
		   ��礬���ä��Τǰ���temp�Хåե��˥إå����򤹤٤�ί��Ƥ���0x03�����������ߤˤ��� */
		char avcbe_temp_stream_buff_1[500];	/* 256->300->500byte *//* 060213 *//* 060307 */
		char avcbe_temp_stream_buff_2[500];	/* 256->300->500byte *//* 060213 *//* 060307 */

		long avcbe_h264_profile;
		long avcbe_h264_level;

		long avcbe_set_intra;

		/*      long avcbe_quant_mod_ratio; *//* 100%���� *//* ���Ѥ��ʤ��ΤǺ�� 050518 */

		long avcbe_frm_interval;	/* ��¤��avcbe_frame_stat�Υ��ФΤ���ɬ�פʤ�� 040909 */
		avcbe_slice_stat avcbe_last_slice_stat;

		/* �إå������� *//* 060127 */
		avcbe_SPS_header_info_stat avcbe_last_SPS_header_info;
		avcbe_PPS_header_info_stat avcbe_last_PPS_header_info;
		avcbe_slice_header_info_stat avcbe_last_slice_header_info;

		/* �ӥåȥ졼�ȴƻ��� */
		long avcbe_bitrate_watch_index;	/* �Ǹ�˽����������ڤ�Υ���ǥå����ֹ� */
		long avcbe_bitrate_remainder_size;	/* ���ڤꤴ�ȤΥӥåȥ������λĤ����� */


		/* ���ȥ꡼����ϥХåե���­��ȯ�������Ȥ��˸ƤӽФ��٤��桼�������ؿ� */
		 avcbe_buf_continue_userproc_ptr
		    avcbe_buf_continue_userproc;
		long avcbe_slice_header_output_bits;	/* ���ȥ꡼����ϥХåե��˥��եȤǽ��Ϥ����������ʥӥå�ñ�̡˥��ȥ꡼����ϥХåե���­�ΤȤ��˻��Ѥ��� *//* 050628 */

		/* VPU4�ɥ饤�����˥��󥳡��ɥѥ�᡼�����Ϥ����� */
		M4IPH_VPU4_ENC avcbe_vpu4_enc_info;

		/* VPU4�ɥ饤�������饨�󥳡��ɷ�̤������뤿�� */
		M4IPH_VPU4_ENC_RES avcbe_vpu4_enc_res;

		/* NAL Unit Syntax�Ѥι�¤�� */
		AVCBE_NAL_UNIT_INFO avcbe_nal_info;

		/* Sequence Parameter Set�Ѥι�¤�� */
		AVCBE_SPS_INFO avcbe_SPS_info;

		/* Picture Parameter Set�Ѥι�¤�� */
		AVCBE_PPS_INFO avcbe_PPS_info;

		/* ���饤���إå��Ѥι�¤�� */
		AVCBE_SLICE_INFO avcbe_slice_header_info;

		/* VUI�ѥ�᡼���Ѥι�¤�� */
		avcbe_vui_main_param *avcbe_vui_info;	/* ���󥳡��ɥѥ�᡼��avcbe_use_vui_parameters��ON�ʤ�С�����ΰ���˳�����Ƥ� */
		long avcbe_non_vcl_bits;	/* nal_hrd_present_flag=ON�ξ��Υإå���ʬ�����(Ratecontrol��cpb_buf_remain���������) *//* 050526 */


#if 0				/* 050526 */
		avcbe_inner_vui_hrd_param inner_vui_hrd_param;	/* 050524 */
#endif

		long *avcbe_mb_table;	/* B-VOP�ΤȤ��˥Υåȥ����ǥåȾ�����ݻ����뤿��Υơ��֥롢���ǿ��ϥޥ���֥�å��� */


		/* ���ȥ꡼�ॿ���פ�H.264�ΤȤ����ѤΤ�� */
		long avcbe_encoded_mb_num;	/* ���饤����ʬ�䤹��Ȥ������ĤΥޥ���֥�å����������줿�� */

		long avcbe_insert_emulation_prevention_flag;	/* 0x03�����ɡ�emulation_prevention�ˤ��������뤫�ݤ��ʥǥե���Ȥ���������� *//* 060124 */
		unsigned char avcbe_primary_pic_type;	/* AU Delimiter��primary_pic_type�ν��ϻ��� *//* 060124 */
		unsigned char avcbe_use_I_PCM;	/* I-PCM�����ѡ�avcbe_set_use_I_PCM�ؿ��ǥ��åȤ���� *//* 060124 */
		unsigned char avcbe_slice_next_Q;	/* nextQ��ON/OFF(���饤��ʬ����˻���) *//* 060124 */
		long avcbe_use_intra_offset;	/* ����ȥ饪�ե��å��� *//* =1:����ȥ饪�ե��åȤ򱣤�API�ؿ�avcbe_set_intra_offset�����ꤹ�롣=0:����ȥ饪�ե��åȤ���ꤷ�ʤ��ʥǥե���ȡ� *//* 060124 */


		char avcbe_use_multi_ref;	/* �ޥ����ե���󥹤��ݤ��ζ��� */
		/* 050408       char avcbe_put_three_byte;      *//* prevention_emulation_three_byte���������뤫�ʥǥե�����ͤ�AVCBE_ON=����� */

		/* �졼�ȥ���ȥ����Ϣ */
		char avcbe_pic_type;	/* ����Υե졼��Υԥ�����μ����AVCBE_IDR_PIC/AVCBE_I_PIC/AVCBE_P_PIC�� */
		char avcbe_prev_pic_type;	/* ľ���˥��󥳡��ɤ����ե졼��Υԥ�����μ���ʥե졼�ॹ���åפ����ե졼��Ͻ����� */
		char avcbe_I_vop_skip_value;	/* I-VOP�򥹥��åפ������1�򥻥å� *//* �����Х��ѿ����ä��������ȥ꡼�ऴ�Ȥ˻������� *//* 050425 */
		char avcbe_prev_I_pic_flag;	/* ���ȥ꡼�ऴ�Ȥ˻�������褦���ѹ� 050425 */
		char avcbe_prev_I_quant_value;	/* ���ȥ꡼�ऴ�Ȥ˻�������褦���ѹ� 050425 */
		char avcbe_ncram_weightq_flag;	/* ���ȥ꡼�ऴ�Ȥ˻�������褦���ѹ� 050425 */
		char avcbe_wq_read_flag;	/* avcbe_g_nc_ram_end������ե饰 050518 */
		char avcbe_wq_write_flag;	/* avcbe_g_median_filter_end������ե饰 050518 */

		long avcbe_x_mb_size;	/* �������Υޥ���֥�å��� *//* 050518 */
		long avcbe_y_mb_size;	/* �������Υޥ���֥�å��� *//* 050518 */

		long avcbe_I_pic_count;	/* ����Ū���������뤿��Ρ�I�ԥ������IDR�ԥ������ޤ�ˤΥ����� */
		long avcbe_frm_rate_count;	/* 1�ü����˥ӥåȥ졼�����椹�뤿��Υե졼��������󥿡���P-Pic�⡼�ɤ����ѡ� */
		float avcbe_skip_counter;	/* Ϣ³�����åץ����� */
		float avcbe_skip_limit;	/* Ϣ³�����å׺����� */

		long avcbe_I_quant_offset_minus_range_flag;	/* ���ȥ꡼�ऴ�Ȥ˻������� 050425 */
		long avcbe_prev_remain_buff;	/* ���ȥ꡼�ऴ�Ȥ˻������� 050425 */
		float avcbe_f_cpb_offset;	/* ���󥳡��ɥѥ�᡼��avcbe_ratecontrol_cpb_offset(long��)���ͤ�1/10�����ͤ������ 050520 */
		float avcbe_f_cpb_offset_rate;	/* cpb buffer ���Ф���cpb_lower���ϰϤ�cpb_min���ϰϤ���Ψ *//* ���󥳡��ɥѥ�᡼��avcbe_ratecontrol_cpb_offset_rate(long��)���ͤ�1/10�����ͤ������ 050520 */
		/*      float avcbe_cpb_stack_rate; *//* cpb buffer �˳��ϻ���������Ƥ������ *//* avcbe_g_cpb_offset���ͤϥ��󥳡��ɥѥ�᡼���ǻ��ꤹ��褦���ѹ������Τ����� 050520 */

		long avcbe_remain_sum;	/* ���ȥ꡼�ऴ�Ȥ˻������� 050427 */
		long avcbe_cpb_buff_per_frm_over_cnt;	/* ���ȥ꡼�ऴ�Ȥ˻������� 050427 */

		long avcbe_1_thr;	/* ���ȥ꡼�ऴ�Ȥ˻������� 050425 */
		long avcbe_2_thr;	/* ���ȥ꡼�ऴ�Ȥ˻������� 050425 */
		long avcbe_3_thr;	/* ���ȥ꡼�ऴ�Ȥ˻������� 050425 */
		long avcbe_4_thr;	/* ���ȥ꡼�ऴ�Ȥ˻������� 050425 */
		long avcbe_5_thr;	/* ���ȥ꡼�ऴ�Ȥ˻������� 050425 */

		long avcbe_quant_max_thr1;	/* ���ȥ꡼�ऴ�Ȥ˻������� 050425 */
		long avcbe_quant_max_thr2;	/* ���ȥ꡼�ऴ�Ȥ˻������� 050425 */
		long avcbe_quant_max_thr3;	/* ���ȥ꡼�ऴ�Ȥ˻������� 050425 */
		long avcbe_quant_max_thr4;	/* ���ȥ꡼�ऴ�Ȥ˻������� 050425 */

		avcbe_rate_control_info_t avcbe_rate_con;	/* �������åȥӥå��̤�Q�ͤ򻻽Ф��뤿��ξ��� */

		/* ����Ū��INTRA�ޥ���֥�å���ե�å����Ϣ */
		long avcbe_intraRefreshMBnum;	/* �ե졼�ऴ�Ȥ˥�ե�å��夹��ޥ���֥�å��� */
		long avcbe_cyclicIntraCounter;	/* ����Ū�˥�ե�å��夹�뤿��Υ����� */

		long avcbe_frm;	/* ���󥨥󥳡��ɤ���ե졼��Υե졼���ֹ�ʻ��֡� */
		long avcbe_prev_frm;	/* ľ���˥��󥳡��ɤ����ե졼��Υե졼���ֹ�ʻ��֡� */

		long avcbe_skip_frame_flag;	/* 0: ����Υե졼��ϥ����åפ��ʤ���1: �����åפ��� */

		long avcbe_qsum;	/* �ե졼��ñ�̤�Q�ι��(rate_control�ǻ�����) */

		/* �̻Ҳ������νŤ��դ���Ϣ */
		char *avcbe_weightedQ_table1;	/* �ޥ���֥�å����Ȥ��̻Ҳ������νŤ��դ�����ꤷ���ơ��֥�����ǿ��ϡ��ޥ���֥�å����� */
		char *avcbe_weightedQ_table2;	/* Ʊ�ơ��֥�2��avcbe_weightedQ_mode=AVCBE_WEIGHTEDQ_AUTO�ΤȤ���median fileter�򤫤����Ť��ͤ������� *//* 050518 */

		/* 2�ѥ������Ϣ *//* 041026 ưŪ�˳��ݤ���褦���ѹ� */
		TAVCBE_WORKAREA avcbe_mb_sads_work_buf;	/* �ޥ���֥�å����Ȥ�SAD�ͳ�Ǽ�� */
		short *avcbe_mb_sads_buf;	/* �ޥ���֥�å����Ȥ�SAD�ͥ��ԡ�������ǿ��ϡ֥ޥ���֥�å���/2�ס� */
		short *avcbe_mb_sads_buf_lowpath;	/* �ޥ���֥�å����Ȥ�SAD�ͥ��ԡ�������ǿ��ϡ֥ޥ���֥�å���/2�ס� */
		char *avcbe_mb_quant;	/* �ޥ���֥�å����Ȥ�Q�͡����ǿ��ϥޥ���֥�å���) */

		/* �����Ǽ�ưŪ�˼��Хå����å� *//* 041027 */
		struct AVCBE_H264_STREAM_INFO *avcbe_backup_H264_stream_info;	/* ��¤��avcbe_H264_stream_info_t���������� */

		avcbe_sei_dec_ref_pic_marking_repetition_param dec_ref_pic_marking_repet_param;	/* 050426 */

		/* ������ǽ�Υ���ȥ饪�ե��å��� *//* 041101 */
		long avcbe_intra_offset_set_flag;	/* =1:����ȥ饪�ե��å��ͤΥơ��֥���ͤ����ꤵ�줿 */
		long *avcbe_intra_offset_table;	/* ����ȥ饪�ե��å��ͤΥơ��֥�ʱ���API�ؿ�avcbe_set_intra_offset()�����ꤹ��� */

		/* ������ǽ��MB�ǥХå������� */
		long avcbe_mb_debug_enable;	/* �ǥХå������ON/OFF *//* 060112 */
		long avcbe_mb_debug_addr;	/* �ǥХå�����ν�����Υ��ɥ쥹 *//* 060112 */

	} avcbe_H264_stream_info_t;



#ifdef __cplusplus
}
#endif
#endif				/* ABCBE_INNER_H */

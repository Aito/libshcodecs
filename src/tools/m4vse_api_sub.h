/*****************************************************************************
*                                                                            *
*  SuperH MEPG-4 Video Encode Library                                        *
*                                                                            *
*    Copyright (C) Renesas Technology Corp., 2005. All rights reserved.      *
*                                                                            *
*    Version��1.0 :   m4vse_api_sub.h                                        *
*                                 2005/02/02 19:30  Renesas Technology Corp. *
*                                                                            *
*****************************************************************************/

/*--------------------------------------------------------------------------*/
/*  1.000  2004.06.22  start codes (VPU4�Ǥǿ�������)                       */
/*--------------------------------------------------------------------------*/

#ifndef	M4VSE_API_SUB_H
#define	M4VSE_API_SUB_H

			/*#include "avcbe.h" *//* 050119 */
			   /*#include "mpeg4venc.h"*//* 050119 */
			      /*#include "m4vse_inner.h" *//* ����ѥ��뤬�̤�ʤ��Τǻ��Ȥ��ʤ� */
					    /*#include "m4iph_vpu4.h"*//* 040714�ɲ� *//* 050119 */

	/* ���Ѵؿ�m4vse_get_address_of_stream()�ΰ���address_type�˻��ꤹ����� */
enum { M4VSE_ADDRESS_WORK_AREA_INFO = 0,
	M4VSE_ADDRESS_ENCODE_BASIC_OPT_MPEG4,
	M4VSE_ADDRESS_ENCODE_OTHER_OPT_MPEG4,
	M4VSE_ADDRESS_VPU4_ENC_INFO,
	M4VSE_ADDRESS_VPU4_ENC_RES,
	M4VSE_ADDRESS_WEIGHTEDQ_TABLE,
	M4VSE_ADDRESS_BUF_CONTINUE_USERPROC,
	M4VSE_ADDRESS_STREAM_BUFF,
	M4VSE_ADDRESS_DUMMY
};

	/* ���Ѵؿ�m4vse_get_value_of_stream()�ΰ���value_type�˻��ꤹ����� */
enum { M4VSE_VALUE_NUM_OF_MB = 0,
	M4VSE_VALUE_USED_WORK_AREA_SIZE,
	M4VSE_VALUE_SIZEOF_MPEG4_STREAM_INFO,
	M4VSE_VALUE_USED_STREAM_BUFF_SIZE,
	M4VSE_VALUE_VPU_CONTINUE_FLAG,
	M4VSE_VALUE_DUMMY
};

	/* ���Ѵؿ�m4vse_set_address_of_stream()�ΰ���address_type�˻��ꤹ����� */
enum { M4VSE_SET_ADDRESS_STREAM_BUFF = 0,
	M4VSE_SET_ADDRESS_DUMMY
};

	/* ���Ѵؿ�m4vse_set_value_of_stream()�ΰ���value_type�˻��ꤹ����� */
enum { M4VSE_SET_VALUE_USED_STREAM_BUFF_SIZE = 0,
	M4VSE_SET_VALUE_STREAM_BUFF_SIZE,
	M4VSE_SET_VALUE_VPU_CONTINUE_FLAG,
	M4VSE_SET_VALUE_DUMMY
};


#ifdef __cplusplus
extern "C" {
#endif

	void m4vse_set_current_stream_info(void
					   *cur_stream_info_mpeg4_h263);

	void *m4vse_get_address_of_stream(void *cur_stream_info_mpeg4_h263, long address_type);	/* ���ȥ꡼��ñ�̤ξ���ʹ�¤��m4vse_MPEG4_stream_info_t�ˤΥ��ФΥ��ɥ쥹���֤����Ѵؿ� */

	long m4vse_get_value_of_stream(void *cur_stream_info_mpeg4_h263, long value_type);	/* ���ȥ꡼��ñ�̤ξ���ʹ�¤��m4vse_MPEG4_stream_info_t�ˤΥ��Ф��ͤ��֤����Ѵؿ� */

	void m4vse_set_address_of_stream(void *cur_stream_info_mpeg4_h263, long address_type, void *new_address);	/* ���ȥ꡼��ñ�̤ξ���ʹ�¤��m4vse_MPEG4_stream_info_t�ˤΥ��ФΥ��ɥ쥹�����ꤹ�����Ѵؿ� */

	void m4vse_set_value_of_stream(void *cur_stream_info_mpeg4_h263, long value_type, long new_value);	/* ���ȥ꡼��ñ�̤ξ���ʹ�¤��m4vse_MPEG4_stream_info_t�ˤΥ��Ф��ͤ����ꤹ�����Ѵؿ� */

#ifdef __cplusplus
}
#endif
#endif				/* M4VSE_API_SUB_H */

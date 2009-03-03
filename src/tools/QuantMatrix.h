/*****************************************************************************
*                                                                            *
*  SuperH MEPG-4 Video Encode Library Sample Source                          *
*                                                                            *
*    Copyright (C) Renesas Technology Corp., 2005. All rights reserved.      *
*                                                                            *
*    Version��1.0 :   QuantMatrix.h                                          *
*                                 2005/08/05 08:40  Renesas Technology Corp. *
*                                                                            *
*****************************************************************************/

/*--------------------------------------------------------------------------*/
/*  1.000  2005.07.29  start codes (����ץ륽�����Υإå�)                  */
/*--------------------------------------------------------------------------*/

#ifndef	QUANT_MATRIX_H
#define	QUANT_MATRIX_H

#include "avcbe.h"

#define QMAT_MPEG_TYPE_DEFAULT_INTRA	1	/* MPEG-4�ε��ʽ�˺ܤäƤ��롢quant_type=1(MPEG������)�Υǥե���Ȥ��̻Ҳ�����(Intra��) */
#define QMAT_MPEG_TYPE_DEFAULT_NONINTRA	101	/* ƱNon-Intra(Inter)�� */

#define QMAT_MPEG_TYPE_ANIME1_INTRA		2	/* �������ͰƤ�����MPEG-4�ǤΥ��˥�������̻Ҳ����󤽤�1(Intra��) */
#define QMAT_MPEG_TYPE_ANIME1_NONINTRA	102	/* ƱNon-Intra(Inter)�� */

#define QMAT_MPEG_TYPE_ANIME2_INTRA		3	/* �������ͰƤ�����MPEG-4�ǤΥ��˥�������̻Ҳ����󤽤�2(Intra��) */
#define QMAT_MPEG_TYPE_ANIME2_NONINTRA	103	/* ƱNon-Intra(Inter)�� */

#define QMAT_MPEG_TYPE_SPECIAL_INTRA	4	/* �������ͰƤ�����MPEG-4�ǤΥӥå�ȯ���̤򸺤餹������̻Ҳ�����(Intra��) */
#define QMAT_MPEG_TYPE_SPECIAL_NONINTRA	104	/* ƱNon-Intra(Inter)�� */

/*----- structures -----*/

#ifdef __cplusplus
extern "C" {
#endif

/*----- prototype -----*/
	int SetQuantMatrix(avcbe_stream_info * context,
			   int qmattype_for_Intra,
			   int qmattype_for_NonIntra);

#ifdef __cplusplus
}
#endif
#endif				/* QUANT_MATRIX_H */

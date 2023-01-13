/****************************************************************************************************************************************** 
* �ļ�����: SWM241_timr.c
* ����˵��:	SWM241��Ƭ���ļ�����/��ʱ������������
* ����֧��:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* ע������:
* �汾����:	V1.0.0		2016��1��30��
* ������¼: 
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION 
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE 
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT 
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology 
*******************************************************************************************************************************************/
#include "SWM241.h"
#include "SWM241_timr.h"


/****************************************************************************************************************************************** 
* ��������: TIMR_Init()
* ����˵��:	TIMR��ʱ��/��������ʼ��
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������Чֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
*			uint32_t mode			TIMR_MODE_TIMER ��ʱ��ģʽ    TIMR_MODE_COUNTER ������ģʽ
*			uint32_t clkdiv			��ʱ/����ʱ�ӷ�Ƶ��ȡֵ1--256
*			uint32_t period			��ʱ/��������
*			uint32_t int_en			�ж�ʹ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_Init(TIMR_TypeDef * TIMRx, uint32_t mode, uint32_t clkdiv, uint32_t period, uint32_t int_en)
{
	SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_TIMR_Pos);
	
	TIMR_Stop(TIMRx);	//һЩ�ؼ��Ĵ���ֻ���ڶ�ʱ��ֹͣʱ����
	
	TIMRx->CR &= ~TIMR_CR_CLKSRC_Msk;
	TIMRx->CR |= mode << TIMR_CR_CLKSRC_Pos;
	
	TIMRx->PSC = clkdiv-1;
	TIMRx->LOAD = period;
	
	TIMRx->IF = (1 << TIMR_IF_TO_Pos);		//����жϱ�־
	if(int_en) TIMRx->IE |=  (1 << TIMR_IE_TO_Pos);
	else	   TIMRx->IE &= ~(1 << TIMR_IE_TO_Pos);
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		if(int_en) NVIC_EnableIRQ(TIMR0_IRQn);
		break;
	
	case ((uint32_t)TIMR1):
		if(int_en) NVIC_EnableIRQ(TIMR1_IRQn);
		break;
	
	case ((uint32_t)TIMR2):
		if(int_en) NVIC_EnableIRQ(TIMR2_IRQn);
		break;
	
	case ((uint32_t)TIMR3):
		if(int_en) NVIC_EnableIRQ(TIMR3_IRQn);
		break;
	
	case ((uint32_t)TIMR4):
		if(int_en) NVIC_EnableIRQ(TIMR4_IRQn);
		break;
	
	case ((uint32_t)TIMR5):
		if(int_en) NVIC_EnableIRQ(TIMR5_GPIOC3_IRQn);
		break;
	
	case ((uint32_t)TIMR6):
		if(int_en) NVIC_EnableIRQ(TIMR6_GPIOC1_IRQn);
		break;
	
	case ((uint32_t)TIMR7):
		if(int_en) NVIC_EnableIRQ(TIMR7_XTALSTOP_GPIOD12_IRQn);
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_Start()
* ����˵��:	������ʱ�����ӳ�ʼֵ��ʼ��ʱ/����
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_Start(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->EN |= (1 << TIMRG_EN_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->EN |= (1 << TIMRG_EN_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->EN |= (1 << TIMRG_EN_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->EN |= (1 << TIMRG_EN_TIMR3_Pos);
		break;
	
	case ((uint32_t)TIMR4):
		TIMRG->EN |= (1 << TIMRG_EN_TIMR4_Pos);
		break;
	
	case ((uint32_t)TIMR5):
		TIMRG->EN |= (1 << TIMRG_EN_TIMR5_Pos);
		break;
	
	case ((uint32_t)TIMR6):
		TIMRG->EN |= (1 << TIMRG_EN_TIMR6_Pos);
		break;
	
	case ((uint32_t)TIMR7):
		TIMRG->EN |= (1 << TIMRG_EN_TIMR7_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_Stop()
* ����˵��:	ֹͣ��ʱ��
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_Stop(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->EN &= ~(1 << TIMRG_EN_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->EN &= ~(1 << TIMRG_EN_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->EN &= ~(1 << TIMRG_EN_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->EN &= ~(1 << TIMRG_EN_TIMR3_Pos);
		break;
	
	case ((uint32_t)TIMR4):
		TIMRG->EN &= ~(1 << TIMRG_EN_TIMR4_Pos);
		break;
	
	case ((uint32_t)TIMR5):
		TIMRG->EN &= ~(1 << TIMRG_EN_TIMR5_Pos);
		break;
	
	case ((uint32_t)TIMR6):
		TIMRG->EN &= ~(1 << TIMRG_EN_TIMR6_Pos);
		break;
	
	case ((uint32_t)TIMR7):
		TIMRG->EN &= ~(1 << TIMRG_EN_TIMR7_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_Halt()
* ����˵��:	��ͣ��ʱ��������ֵ���ֲ���
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_Halt(TIMR_TypeDef * TIMRx)
{
	TIMRx->HALT = 1;
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_Resume()
* ����˵��:	�ָ���ʱ��������ͣ����������
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_Resume(TIMR_TypeDef * TIMRx)
{
	TIMRx->HALT = 0;
}

/****************************************************************************************************************************************** 
* ��������: TIMR_SetPeriod()
* ����˵��:	���ö�ʱ/��������
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
*			uint32_t period			��ʱ/��������
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_SetPeriod(TIMR_TypeDef * TIMRx, uint32_t period)
{
	TIMRx->LOAD = period;
}

/****************************************************************************************************************************************** 
* ��������: TIMR_GetPeriod()
* ����˵��:	��ȡ��ʱ/��������
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: uint32_t				��ǰ��ʱ/��������
* ע������: ��
******************************************************************************************************************************************/
uint32_t TIMR_GetPeriod(TIMR_TypeDef * TIMRx)
{
	return TIMRx->LOAD; 
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_GetCurValue()
* ����˵��:	��ȡ��ǰ����ֵ
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: uint32_t				��ǰ����ֵ
* ע������: ��
******************************************************************************************************************************************/
uint32_t TIMR_GetCurValue(TIMR_TypeDef * TIMRx)
{
	return TIMRx->VALUE >> 8;
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_INTEn()
* ����˵��:	ʹ���ж�
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_INTEn(TIMR_TypeDef * TIMRx)
{
	TIMRx->IE |= (1 << TIMR_IE_TO_Pos);
}

/****************************************************************************************************************************************** 
* ��������: TIMR_INTDis()
* ����˵��:	�����ж�
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_INTDis(TIMR_TypeDef * TIMRx)
{
	TIMRx->IE &= ~(1 << TIMR_IE_TO_Pos);
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_INTClr()
* ����˵��:	����жϱ�־
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_INTClr(TIMR_TypeDef * TIMRx)
{
	TIMRx->IF = (1 << TIMR_IF_TO_Pos);
}

/****************************************************************************************************************************************** 
* ��������: TIMR_INTStat()
* ����˵��:	��ȡ�ж�״̬
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: uint32_t 				0 TIMRxδ�����ж�    1 TIMRx�������ж�
* ע������: ��
******************************************************************************************************************************************/
uint32_t TIMR_INTStat(TIMR_TypeDef * TIMRx)
{
	return (TIMRx->IF >> TIMR_IF_TO_Pos) & 1;
}

/****************************************************************************************************************************************** 
* ��������: TIMR_OC_Init()
* ����˵��:	����ȽϹ��ܳ�ʼ��
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
*			uint16_t match			����������ֵ�ݼ���matchʱ���������ƽ��ת
*			uint32_t match_int_en	����������ֵ�ݼ���matchʱ�Ƿ�����ж�
*			uint32_t init_lvl		��ʼ�����ƽ
* ��    ��: ��
* ע������: ʹ��Output Compare����ʱTIMRxֻ��16λ
******************************************************************************************************************************************/
void TIMR_OC_Init(TIMR_TypeDef * TIMRx, uint16_t match, uint32_t match_int_en, uint32_t init_lvl)
{
	TIMRx->OCMAT = match;
	if(init_lvl) TIMRx->OCCR |=  (1 << TIMR_OCCR_INITLVL_Pos);
	else         TIMRx->OCCR &= ~(1 << TIMR_OCCR_INITLVL_Pos);
	
	TIMRx->IF = (1 << TIMR_IF_OC0_Pos);		//����жϱ�־
	if(match_int_en) TIMRx->IE |=  (1 << TIMR_IE_OC0_Pos);
	else             TIMRx->IE &= ~(1 << TIMR_IE_OC0_Pos);
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		if(match_int_en) NVIC_EnableIRQ(TIMR0_IRQn);
		break;
	
	case ((uint32_t)TIMR1):
		if(match_int_en) NVIC_EnableIRQ(TIMR1_IRQn);
		break;
	
	case ((uint32_t)TIMR2):
		if(match_int_en) NVIC_EnableIRQ(TIMR2_IRQn);
		break;
	
	case ((uint32_t)TIMR3):
		if(match_int_en) NVIC_EnableIRQ(TIMR3_IRQn);
		break;
	
	case ((uint32_t)TIMR4):
		if(match_int_en) NVIC_EnableIRQ(TIMR4_IRQn);
		break;
	
	case ((uint32_t)TIMR5):
		if(match_int_en) NVIC_EnableIRQ(TIMR5_GPIOC3_IRQn);
		break;
	
	case ((uint32_t)TIMR6):
		if(match_int_en) NVIC_EnableIRQ(TIMR6_GPIOC1_IRQn);
		break;
	
	case ((uint32_t)TIMR7):
		if(match_int_en) NVIC_EnableIRQ(TIMR7_XTALSTOP_GPIOD12_IRQn);
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_OC_OutputEn()
* ����˵��:	ʹ������ȽϹ��ܵĲ������
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_OC_OutputEn(TIMR_TypeDef * TIMRx)
{
	TIMRx->OCCR &= ~(TIMR_OCCR_FORCEEN_Pos);
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_OC_OutputDis()
* ����˵��:	��ֹ����ȽϹ��ܵĲ����������������ȽϹ������ű���level��ƽ
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
*			uint32_t level			��ֹ������κ��������ϱ��ֵĵ�ƽ
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_OC_OutputDis(TIMR_TypeDef * TIMRx, uint32_t level)
{
	if(level) TIMRx->OCCR |=  (1 << TIMR_OCCR_FORCELVL_Pos);
	else      TIMRx->OCCR &= ~(1 << TIMR_OCCR_FORCELVL_Pos);
	
	TIMRx->OCCR |= (TIMR_OCCR_FORCEEN_Pos);
}

/****************************************************************************************************************************************** 
* ��������: TIMR_OC_SetMatch()
* ����˵��:	��������ȽϹ��ܵıȽ�ֵ
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
*			uint16_t match			����ȽϹ��ܵıȽ�ֵ
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_OC_SetMatch(TIMR_TypeDef * TIMRx, uint16_t match)
{
	TIMRx->OCMAT = match;
}

/****************************************************************************************************************************************** 
* ��������: TIMR_OC_GetMatch()
* ����˵��:	��ȡ����ȽϹ��ܵıȽ�ֵ
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: uint16_t				����ȽϹ��ܵıȽ�ֵ
* ע������: ��
******************************************************************************************************************************************/
uint16_t TIMR_OC_GetMatch(TIMR_TypeDef * TIMRx)
{
	return TIMRx->OCMAT;
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_OC_INTEn()
* ����˵��:	ʹ������Ƚ��ж�
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_OC_INTEn(TIMR_TypeDef * TIMRx)
{
	TIMRx->IE |= (1 << TIMR_IE_OC0_Pos);
}

/****************************************************************************************************************************************** 
* ��������: TIMR_OC_INTDis()
* ����˵��:	��������Ƚ��ж�
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_OC_INTDis(TIMR_TypeDef * TIMRx)
{
	TIMRx->IE &= ~(1 << TIMR_IE_OC0_Pos);
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_OC_INTClr()
* ����˵��:	�������Ƚ��жϱ�־
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_OC_INTClr(TIMR_TypeDef * TIMRx)
{
	TIMRx->IF = (1 << TIMR_IF_OC0_Pos);
}

/****************************************************************************************************************************************** 
* ��������: TIMR_OC_INTStat()
* ����˵��:	��ȡ����Ƚ��ж�״̬
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: uint32_t 				0 ����Ƚ�matchδ����   1 ����Ƚ�match����
* ע������: ��
******************************************************************************************************************************************/
uint32_t TIMR_OC_INTStat(TIMR_TypeDef * TIMRx)
{
	return (TIMRx->IF >> TIMR_IF_OC0_Pos) & 1;
}

/****************************************************************************************************************************************** 
* ��������: TIMR_IC_Init()
* ����˵��:	���벶���ܳ�ʼ��
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
*			uint32_t start_edge		���������ı��أ�TIMR_ICEDGE_BOTH��TIMR_ICEDGE_RISE��TIMR_ICEDGE_FALL
*			uint32_t captureH_int_en	�����ߵ�ƽ��������ж�ʹ��
*			uint32_t captureL_int_en	�����͵�ƽ��������ж�ʹ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_IC_Init(TIMR_TypeDef * TIMRx, uint32_t start_edge, uint32_t captureH_int_en, uint32_t captureL_int_en)
{
	TIMRx->CR &= ~TIMR_CR_ICEDGE_Msk;
	TIMRx->CR |= (start_edge << TIMR_CR_ICEDGE_Pos);
	
	TIMRx->IF = (TIMR_IF_ICR_Msk | TIMR_IF_ICF_Msk);
	if(captureH_int_en) TIMRx->IE |=  (1 << TIMR_IE_ICF_Pos);
	else                TIMRx->IE &= ~(1 << TIMR_IE_ICF_Pos);
	if(captureL_int_en) TIMRx->IE |=  (1 << TIMR_IE_ICR_Pos);
	else                TIMRx->IE &= ~(1 << TIMR_IE_ICR_Pos);
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		if(captureH_int_en | captureL_int_en) NVIC_EnableIRQ(TIMR0_IRQn);
		break;
	
	case ((uint32_t)TIMR1):
		if(captureH_int_en | captureL_int_en) NVIC_EnableIRQ(TIMR1_IRQn);
		break;
	
	case ((uint32_t)TIMR2):
		if(captureH_int_en | captureL_int_en) NVIC_EnableIRQ(TIMR2_IRQn);
		break;
	
	case ((uint32_t)TIMR3):
		if(captureH_int_en | captureL_int_en) NVIC_EnableIRQ(TIMR3_IRQn);
		break;
	
	case ((uint32_t)TIMR4):
		if(captureH_int_en | captureL_int_en) NVIC_EnableIRQ(TIMR4_IRQn);
		break;
	
	case ((uint32_t)TIMR5):
		if(captureH_int_en | captureL_int_en) NVIC_EnableIRQ(TIMR5_GPIOC3_IRQn);
		break;
	
	case ((uint32_t)TIMR6):
		if(captureH_int_en | captureL_int_en) NVIC_EnableIRQ(TIMR6_GPIOC1_IRQn);
		break;
	
	case ((uint32_t)TIMR7):
		if(captureH_int_en | captureL_int_en) NVIC_EnableIRQ(TIMR7_XTALSTOP_GPIOD12_IRQn);
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������: TIMR_IC_GetCaptureH()
* ����˵��:	��ȡ�ߵ�ƽ���Ȳ������
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: uint32_t				�ߵ�ƽ���Ȳ������
* ע������: ��
******************************************************************************************************************************************/
uint32_t TIMR_IC_GetCaptureH(TIMR_TypeDef * TIMRx)
{
	return TIMRx->ICHIGH;
}

/****************************************************************************************************************************************** 
* ��������: TIMR_IC_GetCaptureL()
* ����˵��:	��ȡ�͵�ƽ���Ȳ������
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: uint32_t				�͵�ƽ���Ȳ������
* ע������: ��
******************************************************************************************************************************************/
uint32_t TIMR_IC_GetCaptureL(TIMR_TypeDef * TIMRx)
{
	return TIMRx->ICLOW;
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_IC_CaptureH_INTEn()
* ����˵��:	ʹ�����벶��ߵ�ƽ���Ȳ�������ж�
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_IC_CaptureH_INTEn(TIMR_TypeDef * TIMRx)
{
	TIMRx->IE |= (1 << TIMR_IE_ICF_Pos);
}

/****************************************************************************************************************************************** 
* ��������: TIMR_IC_CaptureH_INTDis()
* ����˵��:	�������벶��ߵ�ƽ���Ȳ�������ж�
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_IC_CaptureH_INTDis(TIMR_TypeDef * TIMRx)
{
	TIMRx->IE &= ~(1 << TIMR_IE_ICF_Pos);
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_IC_CaptureH_INTClr()
* ����˵��:	������벶��ߵ�ƽ���Ȳ�������жϱ�־
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_IC_CaptureH_INTClr(TIMR_TypeDef * TIMRx)
{
	TIMRx->IF = (0x01 << TIMR_IF_ICF_Pos);
}

/****************************************************************************************************************************************** 
* ��������: TIMR_IC_CaptureH_INTStat()
* ����˵��:	��ȡ���벶��ߵ�ƽ���Ȳ�������ж�״̬
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: uint32_t 				0 �ߵ�ƽ���Ȳ���δ���    1 �ߵ�ƽ���Ȳ������
* ע������: ��
******************************************************************************************************************************************/
uint32_t TIMR_IC_CaptureH_INTStat(TIMR_TypeDef * TIMRx)
{
	return (TIMRx->IF >> TIMR_IF_ICF_Pos) & 1;
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_IC_CaptureL_INTEn()
* ����˵��:	ʹ�����벶��͵�ƽ���Ȳ�������ж�
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_IC_CaptureL_INTEn(TIMR_TypeDef * TIMRx)
{
	TIMRx->IE |= (1 << TIMR_IE_ICR_Pos);
}

/****************************************************************************************************************************************** 
* ��������: TIMR_IC_CaptureL_INTDis()
* ����˵��:	�������벶��͵�ƽ���Ȳ�������ж�
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_IC_CaptureL_INTDis(TIMR_TypeDef * TIMRx)
{
	TIMRx->IE &= ~(1 << TIMR_IE_ICR_Pos);
}

/****************************************************************************************************************************************** 
* ��������:	TIMR_IC_CaptureL_INTClr()
* ����˵��:	������벶��͵�ƽ���Ȳ�������жϱ�־
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMR_IC_CaptureL_INTClr(TIMR_TypeDef * TIMRx)
{
	TIMRx->IF = (1 << TIMR_IF_ICR_Pos);
}

/****************************************************************************************************************************************** 
* ��������: TIMR_IC_CaptureL_INTStat()
* ����˵��:	��ȡ���벶��͵�ƽ���Ȳ�������ж�״̬
* ��    ��: TIMR_TypeDef * TIMRx	ָ��Ҫ�����õĶ�ʱ������ȡֵ����TIMR0��TIMR1��TIMR2��TIMR3��TIMR4��TIMR5��TIMR6��TIMR7
* ��    ��: uint32_t 				0 �͵�ƽ���Ȳ���δ���    1 �͵�ƽ���Ȳ������
* ע������: ��
******************************************************************************************************************************************/
uint32_t TIMR_IC_CaptureL_INTStat(TIMR_TypeDef * TIMRx)
{
	return (TIMRx->IF >> TIMR_IF_ICR_Pos) & 1;
}
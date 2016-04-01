
// SendOrder.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


#include <fstream>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <math.h>

#define DISP_VERBOSE			1
#define FCN_LOG					0

#define MAX_CODE_N				200
#define ORD_Q_SIZE				(1 << 12)

#define REFRESH_INTERVAL_SEC	10
#define TR_RATE_CAP				5
#define BLOCK_WAIT_MS			30
#define OVERFLOW_WAIT_MS		200
#define ORD_TIMEOUT_MS			5000

#define TCP_PASSWORD			"sendorder"
#define TCP_BACKLOG_SIZE		8
#define TCP_BUF_SIZE			(1 << 16)


#include "KHOpenAPICtrl.h"

#define OP_ERR_NONE				0			//"����ó��"
#define OP_ERR_LOGIN			-100			//"�����������ȯ�� �����Ͽ����ϴ�. ����� �ٽ� �����Ͽ� �ֽʽÿ�."
#define OP_ERR_CONNECT			-101			//"���� ���� ����"
#define OP_ERR_VERSION			-102			//"����ó���� �����Ͽ����ϴ�."

#define OP_ERR_SISE_OVERFLOW	-200			//"�ü���ȸ ������"
#define OP_ERR_RQ_STRUCT_FAIL	-201		//"REQUEST_INPUT_st Failed"
#define OP_ERR_RQ_STRING_FAIL	-202			//"��û ���� �ۼ� ����"
#define OP_ERR_NO_DATA			-203			//"�����Ͱ� �������� �ʽ��ϴ�."
#define OP_ERR_OVER_MAX_DATA	-204			//"�ѹ��� ��ȸ ������ ���񰳼��� �ִ� 100���� �Դϴ�."

#define OP_ERR_ORD_WRONG_INPUT	-300			//"�Է°� ����"
#define OP_ERR_ORD_WRONG_ACCNO	-301			//"���º�й�ȣ�� �Է��Ͻʽÿ�."
#define OP_ERR_OTHER_ACC_USE	-302			//"Ÿ�ΰ��´� ����� �� �����ϴ�."
#define OP_ERR_MIS_2BILL_EXC	-303			//"�ֹ������� 20����� �ʰ��մϴ�."
#define OP_ERR_MIS_5BILL_EXC	-304			//"�ֹ������� 50����� �ʰ��մϴ�."
#define OP_ERR_MIS_1PER_EXC		-305			//"�ֹ������� �ѹ����ּ��� 1%�� �ʰ��մϴ�."
#define OP_ERR_MIS_3PER_EXC		-306			//"�ֹ������� �ѹ����ּ��� 3%�� �ʰ��� �� �����ϴ�."
#define OP_ERR_SEND_FAIL		-307			//"�ֹ����۽���"
#define OP_ERR_ORD_OVERFLOW		-308			//"�ֹ����� ������"

#define OP_FID_�����ڵ�			9001		// A###### (A ���� �� ����Ұ�)
#define OP_FID_�ֹ����ɼ���		933			// �������� - �Ǹ��ֹ��߼���
#define OP_FID_�ֹ�����			913			// ����, ü��, Ȯ��
#define OP_FID_�ֹ�����			905			// +�ż� �ż���� +�ż����� -�ŵ� �ŵ���� -�ŵ�����
#define OP_FID_�ֹ���ȣ			9203		// %07d
#define OP_FID_�ֹ�����			901
#define OP_FID_��ü�����		902			
#define OP_FID_���ֹ���ȣ		904			// %07d
#define OP_FID_����ü�ᰡ		914			// �ݵ�� �ֹ����ݰ� ������ ������ ����
#define OP_FID_����ü�ᷮ		915			// �ֹ��� ���� ü�ᷮ�� �ƴ� �̺�Ʈ ��ü�� ü�ᷮ


// CSendOrderApp:
// See SendOrder.cpp for the implementation of this class
//

class CSendOrderApp : public CWinApp
{
public:
	CSendOrderApp();
	CKHOpenAPI m_cKHOpenAPI;
	CString m_sAppPath;

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSendOrderApp theApp;
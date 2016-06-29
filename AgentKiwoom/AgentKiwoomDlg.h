
// AgentKiwoomDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "sibyl/util/Config.h"
#include "sibyl/server/Kiwoom/Kiwoom.h"
#include "sibyl/server/NetServer.h"

// CAgentKiwoomDlg ��ȭ ����
class CAgentKiwoomDlg : public CDialogEx
{
// �����Դϴ�.
public:
    CAgentKiwoomDlg(CWnd* pParent = NULL);    // ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AGENTKIWOOM_DIALOG };
#endif

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// my stuff
private:
    static CAgentKiwoomDlg *this_;
    static sibyl::CSTR& TimeStr();
    void UpdateWindowTitle();
    void Launch();
    
    sibyl::Config config;
    sibyl::Kiwoom kiwoom;
    sibyl::KiwoomServer server;

// �����Դϴ�.
protected:
    HICON m_hIcon;

    // ������ �޽��� �� �Լ�
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    DECLARE_EVENTSINK_MAP()
    void OnEventConnect(long nErrCode);
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnBnClickedButtonExit();
    CButton m_bnRun;
    afx_msg void OnBnClickedButtonRun();
    void OnReceiveTrData(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
    void OnReceiveRealData(LPCTSTR sRealKey, LPCTSTR sRealType, LPCTSTR sRealData);
    void OnReceiveMsg(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg);
    void OnReceiveChejanData(LPCTSTR sGubun, long nItemCnt, LPCTSTR sFIdList);
};

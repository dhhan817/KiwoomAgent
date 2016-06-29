
// AgentKiwoom.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "AgentKiwoom.h"
#include "AgentKiwoomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAgentKiwoomApp

BEGIN_MESSAGE_MAP(CAgentKiwoomApp, CWinApp)
    ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAgentKiwoomApp ����

CAgentKiwoomApp::CAgentKiwoomApp()
{
    // TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
    // InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CAgentKiwoomApp ��ü�Դϴ�.

CAgentKiwoomApp theApp;


// CAgentKiwoomApp �ʱ�ȭ

BOOL CAgentKiwoomApp::InitInstance()
{
    CWinApp::InitInstance();


    AfxEnableControlContainer();

    // ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
    // �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
    CShellManager *pShellManager = new CShellManager;

    // MFC ��Ʈ���� �׸��� ����ϱ� ���� "Windows ����" ���־� ������ Ȱ��ȭ
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

    // ǥ�� �ʱ�ȭ
    // �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
    // �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
    // ��ƾ�� �����ؾ� �մϴ�.
    // �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
    // TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
    // ������ �������� �����ؾ� �մϴ�.
    SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

    ///////////////////////////////////////////////////////////// custom start
    // Save app's path
    TCHAR path_c_str[MAX_PATH];
    GetModuleFileName(AfxGetInstanceHandle(), path_c_str, MAX_PATH);
    path = path_c_str;
    path.resize(path.find_last_of('\\'));
    
    // Redirect cout & cerr to files
    rdCout.Redirect(std::cout, path + "\\main.log");
    rdCerr.Redirect(std::cerr, path + "\\msg.log");
    ///////////////////////////////////////////////////////////// custom end

    CAgentKiwoomDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
        // TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
        //  �ڵ带 ��ġ�մϴ�.
    }
    else if (nResponse == IDCANCEL)
    {
        // TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
        //  �ڵ带 ��ġ�մϴ�.
    }
    else if (nResponse == -1)
    {
        TRACE(traceAppMsg, 0, "���: ��ȭ ���ڸ� ������ �������Ƿ� ���� ���α׷��� ����ġ �ʰ� ����˴ϴ�.\n");
        TRACE(traceAppMsg, 0, "���: ��ȭ ���ڿ��� MFC ��Ʈ���� ����ϴ� ��� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS�� ������ �� �����ϴ�.\n");
    }

    // ������ ���� �� �����ڸ� �����մϴ�.
    if (pShellManager != NULL)
    {
        delete pShellManager;
    }

    // ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
    // ��ȯ�մϴ�.
    return FALSE;
}


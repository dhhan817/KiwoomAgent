/*
   Copyright 2016 Hosang Yoon

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

// KiwoomAgent.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "KiwoomAgent.h"
#include "KiwoomAgentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKiwoomAgentApp

BEGIN_MESSAGE_MAP(CKiwoomAgentApp, CWinApp)
    ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CKiwoomAgentApp ����

CKiwoomAgentApp::CKiwoomAgentApp()
{
    // TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
    // InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CKiwoomAgentApp ��ü�Դϴ�.

CKiwoomAgentApp theApp;


// CKiwoomAgentApp �ʱ�ȭ

BOOL CKiwoomAgentApp::InitInstance()
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

    CKiwoomAgentDlg dlg;
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


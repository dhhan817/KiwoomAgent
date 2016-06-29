
// AgentKiwoom.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
    #error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"        // �� ��ȣ�Դϴ�.

#include <string>
#include "sibyl/util/OstreamRedirector.h"

// CAgentKiwoomApp:
// �� Ŭ������ ������ ���ؼ��� AgentKiwoom.cpp�� �����Ͻʽÿ�.
//

class CAgentKiwoomApp : public CWinApp
{
public:
    CAgentKiwoomApp();
    std::string name;
    std::string path;

// �������Դϴ�.
public:
    virtual BOOL InitInstance();

// �����Դϴ�.
private:
    sibyl::OstreamRedirector rdCout, rdCerr;

public:
    DECLARE_MESSAGE_MAP()
};

extern CAgentKiwoomApp theApp;
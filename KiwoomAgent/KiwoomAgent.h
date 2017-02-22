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

// KiwoomAgent.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
    #error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"        // �� ��ȣ�Դϴ�.

#include <string>
#include "sibyl/util/OstreamRedirector.h"

// CKiwoomAgentApp:
// �� Ŭ������ ������ ���ؼ��� KiwoomAgent.cpp�� �����Ͻʽÿ�.
//

class CKiwoomAgentApp : public CWinApp
{
public:
    CKiwoomAgentApp();
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

extern CKiwoomAgentApp theApp;

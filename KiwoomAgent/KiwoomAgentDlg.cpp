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

// KiwoomAgentDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "KiwoomAgent.h"
#include "KiwoomAgentDlg.h"
#include "afxdialogex.h"

#include "OpenAPI_wrap.h"
#include "sibyl/util/Clock.h"
#include "sibyl/util/DispPrefix.h"

#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace sibyl;

// CKiwoomAgentDlg ��ȭ ����

// static
CKiwoomAgentDlg* CKiwoomAgentDlg::this_ = nullptr;

CKiwoomAgentDlg::CKiwoomAgentDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_AGENTKIWOOM_DIALOG, pParent),
      server(&kiwoom)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // Only one instance allowed
    verify(this_ == nullptr);
    this_ = this;

    // Function pointer initializations
    dispPrefix.SetFunc(TimeStr);
    OpenAPI_wrap_initialize_maps();
    KiwoomAPI::SetWrapperFuncs( &SetInputValue,
                                &GetRepeatCnt,
                                &CommRqData,
                                &GetCommData,
                                &SendOrder,
                                &SetRealReg,
                                &GetCommRealData,
                                &GetChejanData );
}

void CKiwoomAgentDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_KHOPENAPICTRL1, openAPI);
    DDX_Control(pDX, IDC_BUTTON_RUN, m_bnRun);
}

// General member functions

// static
CSTR& CKiwoomAgentDlg::TimeStr() // "local_wall_clock/orderbook_time "
{
    static STR str;

    str = Clock::ms_to_HHMMSS(sibyl::clock.Now(), true);

    const auto &kiwoom = static_cast<CKiwoomAgentDlg*>(this_)->kiwoom;
    str += '/' + Clock::ms_to_HHMMSS((kiwoom.GetOrderBookTime() - kiwoom.GetTimeOffset()) * 1000, true);
    
    str += ' ';

    return str;
}

// runs in a separate thread
void CKiwoomAgentDlg::UpdateWindowTitle()
{
    while (true)
    {
        SetWindowText(TimeStr().c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

// runs in a separate thread
void CKiwoomAgentDlg::Launch()
{
    m_bnRun.EnableWindow(false);
    if (true == kiwoom.Launch())
        server.StartMainLoop();
    else
    {
        std::cerr << dispPrefix << "Launch: [Fail] Initialization failed" << std::endl;
        m_bnRun.EnableWindow(true);
    }
}

BEGIN_MESSAGE_MAP(CKiwoomAgentDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_EXIT, &CKiwoomAgentDlg::OnBnClickedButtonExit)
    ON_BN_CLICKED(IDC_BUTTON_RUN, &CKiwoomAgentDlg::OnBnClickedButtonRun)
END_MESSAGE_MAP()

// CKiwoomAgentDlg �޽��� ó����

void CKiwoomAgentDlg::OnOK()
{
    // Disable <enter> to close
    // CDialogEx::OnOK();
}

void CKiwoomAgentDlg::OnCancel()
{
    // Disable <escape> to close
    // CDialogEx::OnCancel();
}

BOOL CKiwoomAgentDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
    //  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
    SetIcon(m_hIcon, TRUE);            // ū �������� �����մϴ�.
    SetIcon(m_hIcon, FALSE);        // ���� �������� �����մϴ�.

    // TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
    
    // Set display options
    kiwoom.SetVerbose(true);
    server.SetVerbose(true);

    // Check config file validity
    verify(true == config.SetFile(theApp.path + "\\config.config", Config::Mode::read_write));

    // Configure sibyl::Kiwoom; read code list from SaveData's config.ini
    kiwoom.SetStateFile(theApp.path + "\\state.log");
    STR pathParent = theApp.path;
    pathParent.resize(pathParent.find_last_of('\\'));
    kiwoom.ReadConfigFiles(theApp.path + "\\config.config");//, pathParent + "\\SaveData\\config.ini");

    // Read last position from config.config
    auto &ssPos = config.Get("POS");
    RECT rect;
    ssPos >> rect.left >> rect.top;
    if (ssPos.fail() == false)
        SetWindowPos(nullptr, rect.left, rect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    // Read TCP port from config.config
    auto &ssPort = config.Get("PORT");
    std::string port;
    ssPort >> port;
    verify(ssPort.fail() == false && port.empty() == false);
    
    // Launch TCP server (autoStart = false)
    std::thread tServer(&KiwoomServer::Launch, &server, port, false, true);
    tServer.detach();
    
    // Launch title updater
    std::thread tTitleUpdater(&CKiwoomAgentDlg::UpdateWindowTitle, this);
    tTitleUpdater.detach();

    // Open login window
    if (openAPI.CommConnect() < 0)
    {
        std::cerr << dispPrefix << "OpenAPI: Login failed" << std::endl;
    }

    return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CKiwoomAgentDlg::OnBnClickedButtonRun()
{
    std::thread tLaunch(&CKiwoomAgentDlg::Launch, this);
    tLaunch.detach();
}

void CKiwoomAgentDlg::OnBnClickedButtonExit()
{
    // Save window position
    RECT rect;
    GetWindowRect(&rect);
    std::string str = std::to_string(rect.left) + ' ' + std::to_string(rect.top);
    config.Set("POS", str);

    //// Proper way to exit
    //if (openAPI.GetConnectState() == 1)
    //{
    //    std::cerr << TimeStr(this) << "Terminating OpenAPI communiation" << std::endl;
    //    openAPI.CommTerminate();
    //}
    //EndDialog(0);

    // Avoid API errors
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
    abort();
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CKiwoomAgentDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // �������� �׸��ϴ�.
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CKiwoomAgentDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CKiwoomAgentDlg, CDialogEx)
    ON_EVENT(CKiwoomAgentDlg, IDC_KHOPENAPICTRL1, 5, CKiwoomAgentDlg::OnEventConnect, VTS_I4)
    ON_EVENT(CKiwoomAgentDlg, IDC_KHOPENAPICTRL1, 1, CKiwoomAgentDlg::OnReceiveTrData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
    ON_EVENT(CKiwoomAgentDlg, IDC_KHOPENAPICTRL1, 2, CKiwoomAgentDlg::OnReceiveRealData, VTS_BSTR VTS_BSTR VTS_BSTR)
    ON_EVENT(CKiwoomAgentDlg, IDC_KHOPENAPICTRL1, 4, CKiwoomAgentDlg::OnReceiveChejanData, VTS_BSTR VTS_I4 VTS_BSTR)
    ON_EVENT(CKiwoomAgentDlg, IDC_KHOPENAPICTRL1, 3, CKiwoomAgentDlg::OnReceiveMsg, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
END_EVENTSINK_MAP()

void CKiwoomAgentDlg::OnEventConnect(long nErrCode)
{
    if (nErrCode == 0)
    {
        if ("1" == openAPI.KOA_Functions("GetServerGubun", ""))
            std::cerr << dispPrefix << "OpenAPI: Login successful (test server)" << std::endl;
        else
            std::cerr << dispPrefix << "OpenAPI: Login successful" << std::endl;

        std::string accNo = openAPI.GetLoginInfo("ACCNO");
        if (accNo.back() == ';') accNo.pop_back();
        auto pos = accNo.find_first_of(';');
        if (pos != std::string::npos)
        {
            std::cerr << dispPrefix << "OpenAPI: Account list: " << accNo << std::endl;
            accNo.resize(pos);
        }
        // align
            std::cerr << dispPrefix << "OpenAPI: Using account " << accNo << std::endl;
        
        // Set account number to be used in various TR's
        TR::SetAccNo(accNo);

        // Account password input window
        openAPI.KOA_Functions("ShowAccountWindow", "");
        
        m_bnRun.EnableWindow(true);
    }
    else
    {
        std::cerr << dispPrefix << "OpenAPI: Error " << nErrCode << std::endl;
    }
}

void CKiwoomAgentDlg::OnReceiveTrData(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
    // debug_msg("[TR] Received " + STR(sRQName) + " " + STR(sTrCode) + " " + STR(sPrevNext));
    TR::Receive(sRQName, sTrCode, (sPrevNext == STR("2") ? TR::State::carry : TR::State::normal));
        // Note: sPrevNext == "" may also arrive, and std::stol("") hangs
}

void CKiwoomAgentDlg::OnReceiveRealData(LPCTSTR sRealKey, LPCTSTR sRealType, LPCTSTR sRealData)
{
    switch (Map_sRealType(sRealType))
    {
        case MarketEventType::trade : // debug_msg("[RealTr ] " << fmt_code(sRealKey));
                                      kiwoom.ReceiveMarketTr (sRealKey);
                                      break;
        case MarketEventType::table : // debug_msg("[RealTb ] " << fmt_code(sRealKey));
                                      kiwoom.ReceiveMarketTb (sRealKey);
                                      break;
        case MarketEventType::NAV   : // debug_msg("[RealNAV] " << fmt_code(sRealKey));
                                      kiwoom.ReceiveMarketNAV(sRealKey);
                                      break;
        case MarketEventType::index : // debug_msg("[Index  ] " << fmt_code(sRealKey));
                                      kiwoom.ReceiveIndex    (sRealKey);
                                      break;
    }
}

void CKiwoomAgentDlg::OnReceiveChejanData(LPCTSTR sGubun, long nItemCnt, LPCTSTR sFIdList)
{
    // debug_msg("[Chejan]");

    if (strlen(sGubun) == 0) return;

    switch (std::stol(sGubun))
    {
        case static_cast<long>(BookEventType::ord) : // debug_msg("[OrdEvent] Received");
                                                     kiwoom.ReceiveOrdEvent();
                                                     break;
        case static_cast<long>(BookEventType::cnt) : // debug_msg("[CntEvent] Received");
                                                     kiwoom.ReceiveCntEvent();
                                                     break;
    }
}

void CKiwoomAgentDlg::OnReceiveMsg(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
    CSTR &str = Map_sMsg(sMsg);
    if (str.empty() == false)
        std::cerr << dispPrefix << str << std::endl;
}

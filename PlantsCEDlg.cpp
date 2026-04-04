
// PlantsCEDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "PlantsCE.h"
#include "PlantsCEDlg.h"
#include "afxdialogex.h"
#include "atlimage.h"
#include <TlHelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPlantsCEDlg 对话框

CPlantsCEDlg::CPlantsCEDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLANTSCE_DIALOG, pParent)
	, m_hProcess(NULL)
	, m_dwProcessId(0)
	, m_bAttached(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	// 初始化阳光地址结构
	m_sunlightAddr.baseAddress = SUNLIGHT_BASE_ADDR;
	m_sunlightAddr.offset1 = OFFSET1;
	m_sunlightAddr.offset2 = OFFSET2;
	m_sunlightAddr.finalAddress = 0;
}

CPlantsCEDlg::~CPlantsCEDlg()
{
	if (m_hProcess)
	{
		CloseHandle(m_hProcess);
		m_hProcess = NULL;
	}
}

void CPlantsCEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PictureShow, m_PictureShow);
	DDX_Control(pDX, IDC_SunBaseValue, m_editSunBaseValue);
	DDX_Control(pDX, IDC_AttachProcess, m_btnAttachProcess);
	DDX_Control(pDX, IDC_ReadSunValue, m_btnReadSunlight);
	DDX_Control(pDX, IDC_ModifySunValue, m_btnModifySunlight);
	DDX_Control(pDX, IDC_ListLog, m_listLog);
    DDX_Control(pDX, IDC_SunInitBigValue, m_checkSunInitBigValue);
    DDX_Control(pDX, IDC_NoCDPlant, m_checkNoPlantCD);
    DDX_Control(pDX, IDC_AutoSunProduce, m_checkAutoFastSun);
    DDX_Control(pDX, IDC_AutoCollectSun, m_checkAutoCollectSun);
    DDX_Control(pDX, IDC_FastShoot, m_checkFastShoot);
    DDX_Control(pDX, IDC_SelectProcess, m_btnSelectProcess);
    DDX_Control(pDX, IDC_SlotSel1, m_comboSlot1);
    DDX_Control(pDX, IDC_SlotSel2, m_comboSlot2);
    DDX_Control(pDX, IDC_SlotSel3, m_comboSlot3);
    DDX_Control(pDX, IDC_SlotSel4, m_comboSlot4);
    DDX_Control(pDX, IDC_SlotSel5, m_comboSlot5);
    DDX_Control(pDX, IDC_SlotSel6, m_comboSlot6);
    DDX_Control(pDX, IDC_SlotSel7, m_comboSlot7);
    DDX_Control(pDX, IDC_SlotSel8, m_comboSlot8);
    DDX_Control(pDX, IDC_SlotSel9, m_comboSlot9);
    DDX_Control(pDX, IDC_SlotSel10, m_comboSlot10);
    DDX_Control(pDX, IDC_FullScreenExplosion, m_checkFullScreenExplode);
    DDX_Control(pDX, IDC_ZombiesALLGo, m_checkZombiesAllOut);
    DDX_Control(pDX, IDC_PotatoMineNoCD, m_checkPotatoMineNoCD);
    DDX_Control(pDX, IDC_EatZombiesNoCD, m_checkChomperNoCD);
    DDX_Control(pDX, IDC_PlantInfiniteHP, m_checkPlantInfiniteHP);
    DDX_Control(pDX, IDC_MushroomFrozen, m_checkIceMushroomFreeze);
    
}

BEGIN_MESSAGE_MAP(CPlantsCEDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNSelPicture, &CPlantsCEDlg::OnBnClickedBtnselpicture)
	ON_BN_CLICKED(IDC_AttachProcess, &CPlantsCEDlg::OnBnClickedAttachprocess)
    ON_BN_CLICKED(IDC_ReadSunValue, &CPlantsCEDlg::OnBnClickedReadSunValue)
    ON_BN_CLICKED(IDC_ModifySunValue, &CPlantsCEDlg::OnBnClickedModifySunValue)
    ON_BN_CLICKED(IDC_SmallSunAdd1000, &CPlantsCEDlg::OnBnClickedSmallsunadd1000)
    ON_BN_CLICKED(IDC_BigSunAdd2000, &CPlantsCEDlg::OnBnClickedBigsunadd2000)
    ON_BN_CLICKED(IDC_SunInitBigValue, &CPlantsCEDlg::OnBnClickedSuninitbigvalue)
    ON_BN_CLICKED(IDC_NoCDPlant, &CPlantsCEDlg::OnBnClickedNocdplant)
    ON_BN_CLICKED(IDC_AutoSunProduce, &CPlantsCEDlg::OnBnClickedAutosunproduce)
    ON_BN_CLICKED(IDC_AutoCollectSun, &CPlantsCEDlg::OnBnClickedAutocollectsun)
    ON_BN_CLICKED(IDC_FastShoot, &CPlantsCEDlg::OnBnClickedFastshoot)
    ON_BN_CLICKED(IDC_SelectProcess, &CPlantsCEDlg::OnBnClickedSelectprocess)
    ON_CBN_SELCHANGE(IDC_SlotSel1, &CPlantsCEDlg::OnCbnSelchangeSlotsel1)
    ON_CBN_SELCHANGE(IDC_SlotSel2, &CPlantsCEDlg::OnCbnSelchangeSlotsel2)
    ON_CBN_SELCHANGE(IDC_SlotSel3, &CPlantsCEDlg::OnCbnSelchangeSlotsel3)
    ON_CBN_SELCHANGE(IDC_SlotSel4, &CPlantsCEDlg::OnCbnSelchangeSlotsel4)
    ON_CBN_SELCHANGE(IDC_SlotSel5, &CPlantsCEDlg::OnCbnSelchangeSlotsel5)
    ON_CBN_SELCHANGE(IDC_SlotSel6, &CPlantsCEDlg::OnCbnSelchangeSlotsel6)
    ON_CBN_SELCHANGE(IDC_SlotSel7, &CPlantsCEDlg::OnCbnSelchangeSlotsel7)
    ON_CBN_SELCHANGE(IDC_SlotSel8, &CPlantsCEDlg::OnCbnSelchangeSlotsel8)
    ON_CBN_SELCHANGE(IDC_SlotSel9, &CPlantsCEDlg::OnCbnSelchangeSlotsel9)
    ON_CBN_SELCHANGE(IDC_SlotSel10, &CPlantsCEDlg::OnCbnSelchangeSlotsel10)
    ON_BN_CLICKED(IDC_FullScreenExplosion, &CPlantsCEDlg::OnBnClickedFullscreenexplosion)
    ON_BN_CLICKED(IDC_ZombiesALLGo, &CPlantsCEDlg::OnBnClickedZombiesallgo)
    ON_BN_CLICKED(IDC_PotatoMineNoCD, &CPlantsCEDlg::OnBnClickedPotatominenocd)
    ON_BN_CLICKED(IDC_EatZombiesNoCD, &CPlantsCEDlg::OnBnClickedEatzombiesnocd)
    ON_BN_CLICKED(IDC_PlantInfiniteHP, &CPlantsCEDlg::OnBnClickedPlantinfinitehp)
    ON_BN_CLICKED(IDC_MushroomFrozen, &CPlantsCEDlg::OnBnClickedMushroomfrozen)
END_MESSAGE_MAP()


// CPlantsCEDlg 消息处理程序

BOOL CPlantsCEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    // 获取INI文件路径（程序所在目录）
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(NULL, szPath, MAX_PATH);
    CString strExePath = szPath;
    int nPos = strExePath.ReverseFind('\\');
    if (nPos != -1)
    {
        m_strIniPath = strExePath.Left(nPos + 1) + INI_FILENAME;
    }
    else
    {
        m_strIniPath = INI_FILENAME;
    }

    // 初始化卡槽当前值数组
    for (int i = 1; i <= 10; i++)
    {
        m_arrSlotCurrentValue[i] = 0xFFFFFFFF;  // 初始化为无效值
    }

    // 初始化植物名称
    InitPlantNames();

    // 初始化10个卡槽下拉框
    InitSlotComboBox(m_comboSlot1, 1);
    InitSlotComboBox(m_comboSlot2, 2);
    InitSlotComboBox(m_comboSlot3, 3);
    InitSlotComboBox(m_comboSlot4, 4);
    InitSlotComboBox(m_comboSlot5, 5);
    InitSlotComboBox(m_comboSlot6, 6);
    InitSlotComboBox(m_comboSlot7, 7);
    InitSlotComboBox(m_comboSlot8, 8);
    InitSlotComboBox(m_comboSlot9, 9);
    InitSlotComboBox(m_comboSlot10, 10);

    // 禁用控件，等待附加进程
    m_comboSlot1.EnableWindow(FALSE);
    m_comboSlot2.EnableWindow(FALSE);
    m_comboSlot3.EnableWindow(FALSE);
    m_comboSlot4.EnableWindow(FALSE);
    m_comboSlot5.EnableWindow(FALSE);
    m_comboSlot6.EnableWindow(FALSE);
    m_comboSlot7.EnableWindow(FALSE);
    m_comboSlot8.EnableWindow(FALSE);
    m_comboSlot9.EnableWindow(FALSE);
    m_comboSlot10.EnableWindow(FALSE);

    // 设置卡槽地址常量
    m_dwSlotBaseAddress = SLOT_BASE_ADDR;
    m_dwSlotOffset1 = SLOT_OFFSET1;
    m_dwSlotOffset2 = SLOT_OFFSET2;

    // 初始化 CheckBox
    m_checkSunInitBigValue.SetCheck(BST_UNCHECKED);
    m_bSunInitBigValueEnabled = FALSE;
    m_pAllocatedMemory = NULL;
    m_dwTargetAddress = 0;

    // 初始化无CD CheckBox
    m_checkNoPlantCD.SetCheck(BST_UNCHECKED);
    m_bNoPlantCDEnabled = FALSE;
    m_dwNoPlantCDAddress = 0;

    // 初始化自动快速生产阳光 CheckBox
    m_checkAutoFastSun.SetCheck(BST_UNCHECKED);
    m_bAutoFastSunEnabled = FALSE;
    m_dwAutoFastSunAddress = 0;
    m_dwAutoFastSunAllocated = 0;
    m_bAutoFastSunMemoryAllocated = FALSE;

    // 自动收集阳光 CheckBox
    m_checkAutoCollectSun.SetCheck(BST_UNCHECKED);
    m_bAutoCollectSunEnabled = FALSE;
    m_dwAutoCollectSunAddress = 0;
    m_dwAutoCollectSunAllocated = 0;
    m_bAutoCollectSunMemoryAllocated = FALSE;

    // 快速发射 CheckBox
    m_checkFastShoot.SetCheck(BST_UNCHECKED);
    m_bFastShootEnabled = FALSE;
    m_dwFastShootAddress = 0;
    m_dwFastShootAllocated = 0;
    m_bFastShootMemoryAllocated = FALSE;

	// 初始化控件状态
	m_btnReadSunlight.EnableWindow(FALSE);
	m_btnModifySunlight.EnableWindow(FALSE);
	m_editSunBaseValue.EnableWindow(FALSE);

    // 初始化全屏爆炸复选框
    m_checkFullScreenExplode.SetCheck(BST_UNCHECKED);
    m_bFullScreenExplodeEnabled = FALSE;

    // 初始化爆炸地址
    m_dwExplode1Address = 0;
    m_dwExplode2Address = 0;
    m_dwExplode3Address = 0;

    // 初始化分配的内存地址
    m_dwExplode1Allocated = 0;
    m_dwExplode2Allocated = 0;
    m_dwExplode3Allocated = 0;

    // 初始化内存分配标志
    m_bExplode1MemoryAllocated = FALSE;
    m_bExplode2MemoryAllocated = FALSE;
    m_bExplode3MemoryAllocated = FALSE;

    // 初始化僵尸全部出动复选框
    m_checkZombiesAllOut.SetCheck(BST_UNCHECKED);
    m_bZombiesAllOutEnabled = FALSE;
    m_dwZombiesAllOutAddress = 0;
    m_dwZombiesAllOutAllocated = 0;
    m_bZombiesAllOutMemoryAllocated = FALSE;

    // 初始化土豆地雷无CD复选框
    m_checkPotatoMineNoCD.SetCheck(BST_UNCHECKED);
    m_bPotatoMineNoCDEnabled = FALSE;
    m_dwPotatoMineNoCDAddress = 0;
    m_dwPotatoMineNoCDAllocated = 0;
    m_bPotatoMineNoCDMemoryAllocated = FALSE;

    // 初始化食人花无CD复选框
    m_checkChomperNoCD.SetCheck(BST_UNCHECKED);
    m_bChomperNoCDEnabled = FALSE;
    m_dwChomperNoCDAddress = 0;
    m_dwChomperNoCDAllocated = 0;
    m_bChomperNoCDMemoryAllocated = FALSE;

    // 初始化植物无限血复选框
    m_checkPlantInfiniteHP.SetCheck(BST_UNCHECKED);
    m_bPlantInfiniteHPEnabled = FALSE;
    m_dwPlantInfiniteHPAddress = 0;
    m_dwPlantInfiniteHPAllocated = 0;
    m_bPlantInfiniteHPMemoryAllocated = FALSE;

    // 初始化寒冰菇一直冰冻复选框
    m_checkIceMushroomFreeze.SetCheck(BST_UNCHECKED);
    m_bIceMushroomFreezeEnabled = FALSE;
    m_dwIceMushroomFreezeAddress = 0;
    m_dwIceMushroomFreezeAllocated = 0;
    m_bIceMushroomFreezeMemoryAllocated = FALSE;

	AddLog(_T("植物大战僵尸阳光修改器启动"));
    AddLog(_T("配置文件路径: %s"), m_strIniPath);
    AddLog(_T("默认进程: %s"), m_strProcessName);
    AddLog(_T("可以点击【选择进程】按钮选择其他进程"));
	AddLog(_T("阳光基址: 0x%08X"), SUNLIGHT_BASE_ADDR);
	AddLog(_T("偏移链: 0x%X -> 0x%X"), OFFSET1, OFFSET2);
    AddLog(_T("卡槽功能已加载"));
    AddLog(_T("卡槽基址: 0x%08X"), SLOT_BASE_ADDR);
    AddLog(_T("卡槽偏移链: [0x%08X]+0x%X -> +0x%X -> +0x%X+(n-1)*0x%X"),
        SLOT_BASE_ADDR, SLOT_OFFSET1, SLOT_OFFSET2, SLOT_OFFSET3_BASE, SLOT_OFFSET_STEP);
    AddLog(_T("全屏爆炸功能已加载"));
    AddLog(_T("全屏爆炸1地址偏移: 0x%X"), EXPLODE1_OFFSET);
    AddLog(_T("全屏爆炸2地址偏移: 0x%X"), EXPLODE2_OFFSET);
    AddLog(_T("全屏爆炸3地址偏移: 0x%X"), EXPLODE3_OFFSET);
    AddLog(_T("僵尸全部出动功能已加载"));
    AddLog(_T("僵尸全部出动地址偏移: 0x%X"), ZOMBIES_ALL_OUT_OFFSET);
    AddLog(_T("土豆地雷无CD功能已加载"));
    AddLog(_T("土豆地雷无CD地址偏移: 0x%X"), POTATO_MINE_NO_CD_OFFSET);
    AddLog(_T("食人花无CD功能已加载"));
    AddLog(_T("食人花无CD地址偏移: 0x%X"), CHOMPER_NO_CD_OFFSET);
    AddLog(_T("植物无限血功能已加载"));
    AddLog(_T("植物无限血地址偏移: 0x%X"), PLANT_INFINITE_HP_OFFSET);
    AddLog(_T("寒冰菇一直冰冻功能已加载"));
    AddLog(_T("寒冰菇一直冰冻地址偏移: 0x%X"), ICE_MUSHROOM_FREEZE_OFFSET);
    AddLog(_T("请点击【附加进程】按钮开始"));

    // 加载配置文件
    LoadConfigFromIni();

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPlantsCEDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPlantsCEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPlantsCEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPlantsCEDlg::ShowBackgroundPicture(CString m_JpgPathName)
{
	CRect rect;
	CRect rectImage;
	CImage image;
	image.Load(m_JpgPathName);
	int cx = image.GetWidth();
	int cy = image.GetHeight();
	m_PictureShow.GetClientRect(&rect);
	CDC* pDC = m_PictureShow.GetDC();
	SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);
	if ((cx < rect.Width()) || (cy < rect.Height()))
	{
		rectImage = CRect(rect.TopLeft(), CSize(cx, cy));
		image.StretchBlt(pDC->m_hDC, rectImage, SRCCOPY);
	}
	else
	{
		float xScale = (float)rect.Width() / (float)cx;
		float yScale = (float)rect.Height() / (float)cy;
		float ScaleIndex = (xScale >= yScale, xScale, yScale);
		rectImage = CRect(rect.TopLeft(), CSize((int)cx * ScaleIndex, (int)cy * ScaleIndex));
		image.StretchBlt(pDC->m_hDC, rect, SRCCOPY); //将图片画到Picture控件表示的矩形区域
	}
}


void CPlantsCEDlg::OnBnClickedBtnselpicture()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_JpgPathName;
	CFileDialog Filejpg(TRUE, _T(".jpg"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||"), this);
	if (Filejpg.DoModal() == IDOK)
	{
		m_JpgPathName = Filejpg.GetPathName();
		UpdateData(FALSE);
		ShowBackgroundPicture(m_JpgPathName);
	}
}

// 保存配置到INI文件
void CPlantsCEDlg::SaveConfigToIni()
{
    CString strValue;

    // 保存阳光初始值10000功能
    int nSunInitBigValue = m_checkSunInitBigValue.GetCheck();
    strValue.Format(_T("%d"), nSunInitBigValue);
    WritePrivateProfileString(INI_SECTION, _T("SunInitBigValue"), strValue, m_strIniPath);

    // 保存种植植物无CD功能
    int nNoPlantCD = m_checkNoPlantCD.GetCheck();
    strValue.Format(_T("%d"), nNoPlantCD);
    WritePrivateProfileString(INI_SECTION, _T("NoPlantCD"), strValue, m_strIniPath);

    // 保存自动快速生产阳光功能
    int nAutoFastSun = m_checkAutoFastSun.GetCheck();
    strValue.Format(_T("%d"), nAutoFastSun);
    WritePrivateProfileString(INI_SECTION, _T("AutoFastSun"), strValue, m_strIniPath);

    // 保存自动收集阳光功能
    int nAutoCollectSun = m_checkAutoCollectSun.GetCheck();
    strValue.Format(_T("%d"), nAutoCollectSun);
    WritePrivateProfileString(INI_SECTION, _T("AutoCollectSun"), strValue, m_strIniPath);

    // 保存快速发射功能
    int nFastShoot = m_checkFastShoot.GetCheck();
    strValue.Format(_T("%d"), nFastShoot);
    WritePrivateProfileString(INI_SECTION, _T("FastShoot"), strValue, m_strIniPath);

    // 保存全屏爆炸功能
    int nFullScreenExplode = m_checkFullScreenExplode.GetCheck();
    strValue.Format(_T("%d"), nFullScreenExplode);
    WritePrivateProfileString(INI_SECTION, _T("FullScreenExplode"), strValue, m_strIniPath);

    // 保存僵尸全部出动功能
    int nZombiesAllOut = m_checkZombiesAllOut.GetCheck();
    strValue.Format(_T("%d"), nZombiesAllOut);
    WritePrivateProfileString(INI_SECTION, _T("ZombiesAllOut"), strValue, m_strIniPath);

    // 保存土豆地雷无CD功能
    int nPotatoMineNoCD = m_checkPotatoMineNoCD.GetCheck();
    strValue.Format(_T("%d"), nPotatoMineNoCD);
    WritePrivateProfileString(INI_SECTION, _T("ZombiesAllOut"), strValue, m_strIniPath);

    // 保存食人花无CD功能
    int nChomperNoCD = m_checkChomperNoCD.GetCheck();
    strValue.Format(_T("%d"), nChomperNoCD);
    WritePrivateProfileString(INI_SECTION, _T("ChomperNoCD"), strValue, m_strIniPath);

    // 保存植物无限血
    int nPlantInfiniteHP = m_checkPlantInfiniteHP.GetCheck();
    strValue.Format(_T("%d"), nPlantInfiniteHP);
    WritePrivateProfileString(INI_SECTION, _T("PlantInfiniteHP"), strValue, m_strIniPath);

    // 保存寒冰菇一直冰冻功能
    int nIceMushroomFreeze = m_checkIceMushroomFreeze.GetCheck();
    strValue.Format(_T("%d"), nIceMushroomFreeze);
    WritePrivateProfileString(INI_SECTION, _T("IceMushroomFreeze"), strValue, m_strIniPath);

    // 保存进程名称
    WritePrivateProfileString(INI_SECTION, _T("ProcessName"), m_strProcessName, m_strIniPath);

    AddLog(_T("[配置] 配置已保存到: %s"), m_strIniPath);
}

// 从INI文件加载配置
void CPlantsCEDlg::LoadConfigFromIni()
{
    // 检查配置文件是否存在
    if (GetFileAttributes(m_strIniPath) == INVALID_FILE_ATTRIBUTES)
    {
        AddLog(_T("[配置] 配置文件不存在，使用默认设置"));
        return;
    }

    AddLog(_T("[配置] 正在加载配置文件: %s"), m_strIniPath);

    // 加载阳光初始值10000功能
    int nSunInitBigValue = GetPrivateProfileInt(INI_SECTION, _T("SunInitBigValue"), 0, m_strIniPath);
    m_checkSunInitBigValue.SetCheck(nSunInitBigValue);

    // 加载种植植物无CD功能
    int nNoPlantCD = GetPrivateProfileInt(INI_SECTION, _T("NoPlantCD"), 0, m_strIniPath);
    m_checkNoPlantCD.SetCheck(nNoPlantCD);

    // 加载自动快速生产阳光功能
    int nAutoFastSun = GetPrivateProfileInt(INI_SECTION, _T("AutoFastSun"), 0, m_strIniPath);
    m_checkAutoFastSun.SetCheck(nAutoFastSun);

    // 加载自动收集阳光功能
    int nAutoCollectSun = GetPrivateProfileInt(INI_SECTION, _T("AutoCollectSun"), 0, m_strIniPath);
    m_checkAutoCollectSun.SetCheck(nAutoCollectSun);

    // 加载快速发射功能
    int nFastShoot = GetPrivateProfileInt(INI_SECTION, _T("FastShoot"), 0, m_strIniPath);
    m_checkFastShoot.SetCheck(nFastShoot);

    // 加载全屏爆炸功能
    int nFullScreenExplode = GetPrivateProfileInt(INI_SECTION, _T("FullScreenExplode"), 0, m_strIniPath);
    m_checkFullScreenExplode.SetCheck(nFullScreenExplode);

    // 加载僵尸全部出动功能
    int nZombiesAllOut = GetPrivateProfileInt(INI_SECTION, _T("ZombiesAllOut"), 0, m_strIniPath);
    m_checkZombiesAllOut.SetCheck(nZombiesAllOut);

    // 加载土豆地雷无CD功能
    int nPotatoMineNoCD = GetPrivateProfileInt(INI_SECTION, _T("PotatoMineNoCD"), 0, m_strIniPath);
    m_checkPotatoMineNoCD.SetCheck(nPotatoMineNoCD);

    // 加载食人花无CD功能
    int nChomperNoCD = GetPrivateProfileInt(INI_SECTION, _T("ChomperNoCD"), 0, m_strIniPath);
    m_checkChomperNoCD.SetCheck(nChomperNoCD);

    // 加载植物无限血功能
    int nPlantInfiniteHP = GetPrivateProfileInt(INI_SECTION, _T("PlantInfiniteHP"), 0, m_strIniPath);
    m_checkPlantInfiniteHP.SetCheck(nPlantInfiniteHP);

    // 加载寒冰菇一直冰冻功能
    int nIceMushroomFreeze = GetPrivateProfileInt(INI_SECTION, _T("IceMushroomFreeze"), 0, m_strIniPath);
    m_checkIceMushroomFreeze.SetCheck(nIceMushroomFreeze);

    // 加载进程名称
    TCHAR szProcessName[MAX_PATH] = { 0 };
    GetPrivateProfileString(INI_SECTION, _T("ProcessName"), TARGET_PROCESS_NAME,
        szProcessName, MAX_PATH, m_strIniPath);
    m_strProcessName = szProcessName;

    // 更新选择进程按钮文字
    CString strBtnText;
    strBtnText.Format(_T("选择进程 [%s]"), m_strProcessName);
    m_btnSelectProcess.SetWindowText(strBtnText);

    AddLog(_T("[配置] 加载完成"));
    AddLog(_T("  阳光初始值10000: %s"), nSunInitBigValue ? _T("启用") : _T("禁用"));
    AddLog(_T("  种植植物无CD: %s"), nNoPlantCD ? _T("启用") : _T("禁用"));
    AddLog(_T("  自动快速生产阳光: %s"), nAutoFastSun ? _T("启用") : _T("禁用"));
    AddLog(_T("  自动收集阳光: %s"), nAutoCollectSun ? _T("启用") : _T("禁用"));
    AddLog(_T("  快速发射: %s"), nFastShoot ? _T("启用") : _T("禁用"));
    AddLog(_T("  全屏爆炸: %s"), nFullScreenExplode ? _T("启用") : _T("禁用"));
    AddLog(_T("  僵尸全部出动: %s"), nZombiesAllOut ? _T("启用") : _T("禁用"));
    AddLog(_T("  土豆地雷无CD: %s"), nPotatoMineNoCD ? _T("启用") : _T("禁用"));
    AddLog(_T("  食人花无CD: %s"), nChomperNoCD ? _T("启用") : _T("禁用"));
    AddLog(_T("  植物无限血: %s"), nPlantInfiniteHP ? _T("启用") : _T("禁用"));
    AddLog(_T("  寒冰菇一直冰冻: %s"), nIceMushroomFreeze ? _T("启用") : _T("禁用"));
    AddLog(_T("  进程名称: %s"), m_strProcessName);
}

// 根据配置应用所有修改功能（附加进程后调用）
void CPlantsCEDlg::ApplyAllCheatsFromConfig()
{
    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("[配置] 未附加进程，无法应用修改功能"));
        return;
    }

    AddLog(_T("[配置] 正在应用保存的修改功能..."));

    // 应用阳光初始值10000功能
    if (m_checkSunInitBigValue.GetCheck() == BST_CHECKED && !m_bSunInitBigValueEnabled)
    {
        AddLog(_T("[配置] 启用阳光初始值10000"));
        EnableSunInitBigValue();
    }

    // 应用种植植物无CD功能
    if (m_checkNoPlantCD.GetCheck() == BST_CHECKED && !m_bNoPlantCDEnabled)
    {
        AddLog(_T("[配置] 启用种植植物无CD"));
        EnableNoPlantCD();
    }

    // 应用自动快速生产阳光功能
    if (m_checkAutoFastSun.GetCheck() == BST_CHECKED && !m_bAutoFastSunEnabled)
    {
        AddLog(_T("[配置] 启用自动快速生产阳光"));
        EnableAutoFastSun();
    }

    // 应用自动收集阳光功能
    if (m_checkAutoCollectSun.GetCheck() == BST_CHECKED && !m_bAutoCollectSunEnabled)
    {
        AddLog(_T("[配置] 启用自动收集阳光"));
        EnableAutoCollectSun();
    }

    // 应用快速发射功能
    if (m_checkFastShoot.GetCheck() == BST_CHECKED && !m_bFastShootEnabled)
    {
        AddLog(_T("[配置] 启用快速发射"));
        EnableFastShoot();
    }

    // 应用全屏爆炸功能
    if (m_checkFullScreenExplode.GetCheck() == BST_CHECKED && !m_bFullScreenExplodeEnabled)
    {
        AddLog(_T("[配置] 启用全屏爆炸"));
        EnableFullScreenExplode();
    }

    // 应用僵尸全部出动功能
    if (m_checkZombiesAllOut.GetCheck() == BST_CHECKED && !m_bZombiesAllOutEnabled)
    {
        AddLog(_T("[配置] 启用僵尸全部出动"));
        EnableZombiesAllOut();
    }

    // 应用土豆地雷无CD功能
    if (m_checkPotatoMineNoCD.GetCheck() == BST_CHECKED && !m_bPotatoMineNoCDEnabled)
    {
        AddLog(_T("[配置] 启用土豆地雷无CD"));
        EnablePotatoMineNoCD();
    }

    // 应用食人花无CD功能
    if (m_checkChomperNoCD.GetCheck() == BST_CHECKED && !m_bChomperNoCDEnabled)
    {
        AddLog(_T("[配置] 启用食人花无CD"));
        EnableChomperNoCD();
    }

    // 应用植物无限血功能
    if (m_checkPlantInfiniteHP.GetCheck() == BST_CHECKED && !m_bPlantInfiniteHPEnabled)
    {
        AddLog(_T("[配置] 启用植物无限血"));
        EnablePlantInfiniteHP();
    }

    // 应用寒冰菇一直冰冻功能
    if (m_checkIceMushroomFreeze.GetCheck() == BST_CHECKED && !m_bIceMushroomFreezeEnabled)
    {
        AddLog(_T("[配置] 启用寒冰菇一直冰冻"));
        EnableIceMushroomFreeze();
    }

    AddLog(_T("[配置] 应用完成"));
}


// 查找进程ID
BOOL CPlantsCEDlg::FindProcessId(LPCTSTR szProcessName, DWORD& dwProcessId)
{
    AddLog(_T("[查找进程] 正在查找: %s"), szProcessName);

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        AddLog(_T("[查找进程] 创建进程快照失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    BOOL bFound = FALSE;
    if (Process32First(hSnapshot, &pe))
    {
        do
        {
            if (_tcsicmp(pe.szExeFile, szProcessName) == 0)
            {
                dwProcessId = pe.th32ProcessID;
                bFound = TRUE;
                AddLog(_T("[查找进程] 找到进程: %s (PID: %d)"), pe.szExeFile, dwProcessId);
                break;
            }
        } while (Process32Next(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);

    if (!bFound)
    {
        AddLog(_T("[查找进程] 未找到进程: %s"), szProcessName);

        // 列出所有运行中的进程，帮助用户排查
        AddLog(_T("[查找进程] 当前运行的进程列表:"));
        hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot != INVALID_HANDLE_VALUE)
        {
            pe.dwSize = sizeof(PROCESSENTRY32);
            if (Process32First(hSnapshot, &pe))
            {
                int nCount = 0;
                do
                {
                    if (nCount < 20)  // 只显示前20个
                    {
                        AddLog(_T("[查找进程]   %s (PID: %d)"), pe.szExeFile, pe.th32ProcessID);
                    }
                    nCount++;
                } while (Process32Next(hSnapshot, &pe));
                if (nCount > 20)
                {
                    AddLog(_T("[查找进程]   ... 还有 %d 个进程"), nCount - 20);
                }
            }
            CloseHandle(hSnapshot);
        }
    }

    return bFound;
}

// 添加日志
void CPlantsCEDlg::AddLog(LPCTSTR szFormat, ...)
{
    CString strLog;
    va_list args;
    va_start(args, szFormat);
    strLog.FormatV(szFormat, args);
    va_end(args);

    CTime time = CTime::GetCurrentTime();
    CString strTime = time.Format(_T("[%H:%M:%S] "));

    m_listLog.AddString(strTime + strLog);

    int nCount = m_listLog.GetCount();
    if (nCount > 0)
        m_listLog.SetCurSel(nCount - 1);
}

// 读取指针链：[[baseAddress] + offset1] + offset2
DWORD_PTR CPlantsCEDlg::ReadPointerChain(DWORD_PTR baseAddress, DWORD_PTR offset1, DWORD_PTR offset2)
{
    if (!m_hProcess)
        return 0;

    DWORD_PTR ptr1 = 0;
    SIZE_T bytesRead = 0;

    // 第一次读取：基址 -> 指针1
    if (!ReadProcessMemory(m_hProcess, (LPCVOID)baseAddress, &ptr1, sizeof(DWORD_PTR), &bytesRead))
    {
        AddLog(_T("读取基址失败，错误码: %d"), GetLastError());
        return 0;
    }

    if (bytesRead != sizeof(DWORD_PTR))
    {
        AddLog(_T("读取基址数据不完整"));
        return 0;
    }

    AddLog(_T("读取基址[0x%08X] -> 指针1: 0x%08X"), baseAddress, ptr1);

    // 第一次偏移计算
    DWORD_PTR addr1 = ptr1 + offset1;
    DWORD_PTR ptr2 = 0;

    // 第二次读取：指针1+偏移1 -> 指针2
    if (!ReadProcessMemory(m_hProcess, (LPCVOID)addr1, &ptr2, sizeof(DWORD_PTR), &bytesRead))
    {
        AddLog(_T("读取第一层偏移失败，错误码: %d"), GetLastError());
        return 0;
    }

    if (bytesRead != sizeof(DWORD_PTR))
    {
        AddLog(_T("读取第一层偏移数据不完整"));
        return 0;
    }

    AddLog(_T("读取地址[0x%08X] -> 指针2: 0x%08X"), addr1, ptr2);

    // 第二次偏移计算，得到最终阳光地址
    DWORD_PTR finalAddr = ptr2 + offset2;

    AddLog(_T("最终阳光地址: 0x%08X"), finalAddr);

    return finalAddr;
}

// 读取阳光值
DWORD CPlantsCEDlg::ReadSunlightValue()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("错误: 未附加进程"));
        return 0;
    }

    // 获取最终阳光地址
    m_sunlightAddr.finalAddress = ReadPointerChain(
        m_sunlightAddr.baseAddress,
        m_sunlightAddr.offset1,
        m_sunlightAddr.offset2
    );

    if (m_sunlightAddr.finalAddress == 0)
    {
        AddLog(_T("无法获取阳光地址"));
        return 0;
    }

    // 读取阳光值
    DWORD dwSunlight = 0;
    SIZE_T bytesRead = 0;

    if (ReadProcessMemory(m_hProcess, (LPCVOID)m_sunlightAddr.finalAddress,
        &dwSunlight, sizeof(DWORD), &bytesRead))
    {
        if (bytesRead == sizeof(DWORD))
        {
            AddLog(_T("当前阳光值: %d"), dwSunlight);
            return dwSunlight;
        }
    }

    AddLog(_T("读取阳光值失败，错误码: %d"), GetLastError());
    return 0;
}

// 写入阳光值
BOOL CPlantsCEDlg::WriteSunlightValue(DWORD dwNewValue)
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("错误: 未附加进程"));
        return FALSE;
    }

    if (m_sunlightAddr.finalAddress == 0)
    {
        AddLog(_T("错误: 未获取阳光地址，请先读取阳光值"));
        return FALSE;
    }

    // 修改内存保护属性
    DWORD dwOldProtect = 0;
    if (!VirtualProtectEx(m_hProcess, (LPVOID)m_sunlightAddr.finalAddress,
        sizeof(DWORD), PAGE_EXECUTE_READWRITE, &dwOldProtect))
    {
        AddLog(_T("修改内存保护失败，错误码: %d"), GetLastError());
        // 继续尝试写入
    }

    // 写入新值
    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_sunlightAddr.finalAddress,
        &dwNewValue, sizeof(DWORD), &bytesWritten);

    // 恢复内存保护属性
    VirtualProtectEx(m_hProcess, (LPVOID)m_sunlightAddr.finalAddress,
        sizeof(DWORD), dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == sizeof(DWORD))
    {
        AddLog(_T("成功修改阳光值: %d -> %d"),
            ReadSunlightValue() - dwNewValue + dwNewValue, dwNewValue);

        // 验证修改
        DWORD dwVerify = ReadSunlightValue();
        if (dwVerify == dwNewValue)
        {
            AddLog(_T("验证成功: 阳光值已更新为 %d"), dwVerify);
            return TRUE;
        }
        else
        {
            AddLog(_T("警告: 验证失败，当前值为 %d"), dwVerify);
            return FALSE;
        }
    }
    else
    {
        AddLog(_T("写入失败，错误码: %d"), GetLastError());
        return FALSE;
    }
}

// 附加进程
BOOL CPlantsCEDlg::AttachToProcess()
{
    if (m_strProcessName.IsEmpty())
    {
        AddLog(_T("[附加进程] 错误: 请先选择进程"));
        MessageBox(_T("请先点击【选择进程】按钮选择游戏进程！"),
            _T("错误"), MB_OK | MB_ICONERROR);
        return FALSE;
    }

    if (!FindProcessId(m_strProcessName, m_dwProcessId))
    {
        AddLog(_T("[附加进程] 错误: 未找到进程 %s"), m_strProcessName);
        AddLog(_T("[附加进程] 请确保游戏已经运行，并且进程名称正确"));

        CString strMsg;
        strMsg.Format(_T("未找到进程: %s\n\n请确保:\n1. 游戏已经运行\n2. 进程名称正确\n3. 以管理员权限运行此程序"),
            m_strProcessName);
        MessageBox(strMsg, _T("错误"), MB_OK | MB_ICONERROR);
        return FALSE;
    }

    AddLog(_T("[附加进程] 找到进程: %s (PID: %d, 0x%08X)"),
        m_strProcessName, m_dwProcessId, m_dwProcessId);

    // 尝试打开进程
    m_hProcess = OpenProcess(
        PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION |
        PROCESS_QUERY_INFORMATION | PROCESS_SET_INFORMATION,
        FALSE,
        m_dwProcessId
    );

    if (!m_hProcess)
    {
        DWORD dwError = GetLastError();
        AddLog(_T("[附加进程] 打开进程失败，错误码: %d"), dwError);

        if (dwError == 5)
        {
            AddLog(_T("[附加进程] 权限不足，请以管理员权限运行"));
            MessageBox(_T("无法打开进程！\n\n请以管理员身份运行此程序。"),
                _T("错误"), MB_OK | MB_ICONERROR);
        }
        return FALSE;
    }

    m_bAttached = TRUE;
    AddLog(_T("[附加进程] 成功附加进程 %s"), m_strProcessName);
    AddLog(_T("[附加进程] 进程句柄: 0x%08X"), (DWORD_PTR)m_hProcess);

    return TRUE;
}

// 分离进程
void CPlantsCEDlg::DetachFromProcess()
{
    // 禁用所有功能
    if (m_bSunInitBigValueEnabled)
    {
        DisableSunInitBigValue();
    }

    if (m_bNoPlantCDEnabled)
    {
        DisableNoPlantCD();
    }

    if (m_bAutoFastSunEnabled)
    {
        DisableAutoFastSun();
    }

    if (m_bAutoCollectSunEnabled)
    {
        DisableAutoCollectSun();
    }

    if (m_bFastShootEnabled)
    {
        DisableFastShoot();
    }

    if (m_bFullScreenExplodeEnabled)
    {
        DisableFullScreenExplode();
    }

    if (m_bZombiesAllOutEnabled)
    {
        DisableZombiesAllOut();
    }
    // 保存配置（保存复选框状态）
    SaveConfigToIni();

    if (m_hProcess)
    {
        CloseHandle(m_hProcess);
        m_hProcess = NULL;
    }
    m_bAttached = FALSE;
    m_dwProcessId = 0;
    m_sunlightAddr.finalAddress = 0;

    // 重置地址
    m_dwNoPlantCDAddress = 0;
    m_dwAutoFastSunAddress = 0;
    m_dwAutoCollectSunAddress = 0;
    m_dwFastShootAddress = 0;

    // 恢复按钮文字
    m_btnAttachProcess.SetWindowText(_T("附加进程"));

    // 禁用功能按钮
    m_btnReadSunlight.EnableWindow(FALSE);
    m_btnModifySunlight.EnableWindow(FALSE);
    m_editSunBaseValue.EnableWindow(FALSE);
    m_checkSunInitBigValue.EnableWindow(FALSE);
    m_checkNoPlantCD.EnableWindow(FALSE);
    m_checkAutoFastSun.EnableWindow(FALSE);
    m_checkAutoCollectSun.EnableWindow(FALSE);
    m_checkFastShoot.EnableWindow(FALSE);
    m_checkZombiesAllOut.EnableWindow(FALSE);
    m_checkFullScreenExplode.EnableWindow(FALSE);
    m_checkPotatoMineNoCD.EnableWindow(FALSE);
    m_checkChomperNoCD.EnableWindow(FALSE);
    m_checkPlantInfiniteHP.EnableWindow(FALSE);
    m_checkIceMushroomFreeze.EnableWindow(FALSE);

    // 禁用卡槽控件
    m_comboSlot1.EnableWindow(FALSE);
    m_comboSlot2.EnableWindow(FALSE);
    m_comboSlot3.EnableWindow(FALSE);
    m_comboSlot4.EnableWindow(FALSE);
    m_comboSlot5.EnableWindow(FALSE);
    m_comboSlot6.EnableWindow(FALSE);
    m_comboSlot7.EnableWindow(FALSE);
    m_comboSlot8.EnableWindow(FALSE);
    m_comboSlot9.EnableWindow(FALSE);
    m_comboSlot10.EnableWindow(FALSE);

    AddLog(_T("已分离进程"));
}


void CPlantsCEDlg::OnBnClickedAttachprocess()
{
    // TODO: 在此添加控件通知处理程序代码
    if (m_bAttached)
    {
        DetachFromProcess();
        return;
    }

    if (AttachToProcess())
    {
        m_btnAttachProcess.SetWindowText(_T("分离进程"));

        // 启用功能按钮
        m_btnReadSunlight.EnableWindow(TRUE);
        m_btnModifySunlight.EnableWindow(TRUE);
        m_editSunBaseValue.EnableWindow(TRUE);
        m_checkSunInitBigValue.EnableWindow(TRUE);
        m_checkNoPlantCD.EnableWindow(TRUE);
        m_checkAutoFastSun.EnableWindow(TRUE);
        m_checkAutoCollectSun.EnableWindow(TRUE);
        m_checkFastShoot.EnableWindow(TRUE);
        m_checkFullScreenExplode.EnableWindow(TRUE);
        m_checkPotatoMineNoCD.EnableWindow(TRUE);
        m_checkChomperNoCD.EnableWindow(TRUE);
        m_checkPlantInfiniteHP.EnableWindow(TRUE);
        m_checkIceMushroomFreeze.EnableWindow(TRUE);

        // 启用卡槽控件
        m_comboSlot1.EnableWindow(TRUE);
        m_comboSlot2.EnableWindow(TRUE);
        m_comboSlot3.EnableWindow(TRUE);
        m_comboSlot4.EnableWindow(TRUE);
        m_comboSlot5.EnableWindow(TRUE);
        m_comboSlot6.EnableWindow(TRUE);
        m_comboSlot7.EnableWindow(TRUE);
        m_comboSlot8.EnableWindow(TRUE);
        m_comboSlot9.EnableWindow(TRUE);
        m_comboSlot10.EnableWindow(TRUE);
        m_checkZombiesAllOut.EnableWindow(TRUE);

        // 应用保存的配置
        ApplyAllCheatsFromConfig();

        // 获取模块基址并显示初始值功能地址
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
        {
            m_dwTargetAddress = dwModuleBase + TARGET_INIT_VALUE_OFFSET;
            AddLog(_T("[初始值10000] 目标地址: 0x%08X"), m_dwTargetAddress);

            // 无CD功能地址
            m_dwNoPlantCDAddress = dwModuleBase + NO_PLANT_CD_OFFSET;
            AddLog(_T("[无CD功能] 目标地址: 0x%08X"), m_dwNoPlantCDAddress);
        }

        // 自动读取一次阳光值
        OnBnClickedReadSunValue();
    }
}

void CPlantsCEDlg::OnBnClickedReadSunValue()
{
    // TODO: 在此添加控件通知处理程序代码
    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("错误: 请先附加进程"));
        return;
    }

    AddLog(_T("开始读取阳光值..."));

    DWORD dwSunlight = ReadSunlightValue();

    if (dwSunlight > 0 || dwSunlight == 0)  // 允许读取到0
    {
        CString strValue;
        strValue.Format(_T("%d"), dwSunlight);
        m_editSunBaseValue.SetWindowText(strValue);

        CString strStatus;
        strStatus.Format(_T("阳光: %d"), dwSunlight);
    }
    else
    {
        AddLog(_T("读取失败，请检查游戏是否运行正常"));
    }
}


void CPlantsCEDlg::OnBnClickedModifySunValue()
{
    // TODO: 在此添加控件通知处理程序代码
    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("错误: 请先附加进程"));
        return;
    }

    CString strValue;
    m_editSunBaseValue.GetWindowText(strValue);

    if (strValue.IsEmpty())
    {
        AddLog(_T("错误: 请输入要修改的阳光值"));
        return;
    }

    DWORD dwNewValue = _ttoi(strValue);

    if (dwNewValue > 999999)
    {
        AddLog(_T("警告: 阳光值过大 (%d)，可能影响游戏体验"), dwNewValue);
    }

    AddLog(_T("准备修改阳光值为: %d"), dwNewValue);

    if (WriteSunlightValue(dwNewValue))
    {

        // 刷新显示
        DWORD dwCurrent = ReadSunlightValue();
        CString strCurrent;
        strCurrent.Format(_T("%d"), dwCurrent);
        m_editSunBaseValue.SetWindowText(strCurrent);
    }
    else
    {

    }
}


// 获取模块基址
DWORD_PTR CPlantsCEDlg::GetModuleBaseAddress()
{
    if (!m_hProcess || !m_bAttached)
        return 0;

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, m_dwProcessId);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    MODULEENTRY32 moduleEntry;
    moduleEntry.dwSize = sizeof(MODULEENTRY32);

    DWORD_PTR dwModuleBase = 0;
    if (Module32First(hSnapshot, &moduleEntry))
    {
        do
        {
            if (_tcsicmp(moduleEntry.szModule, TARGET_PROCESS_NAME) == 0)
            {
                dwModuleBase = (DWORD_PTR)moduleEntry.modBaseAddr;
                break;
            }
        } while (Module32Next(hSnapshot, &moduleEntry));
    }

    CloseHandle(hSnapshot);
    return dwModuleBase;
}

// 启用初始值10000功能
void CPlantsCEDlg::EnableSunInitBigValue()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[初始值10000] 错误: 未附加进程"));
        return;
    }

    if (m_bSunInitBigValueEnabled)
    {
        AddLog(_T("[初始值10000] 已经启用"));
        return;
    }

    AddLog(_T("[初始值10000] 正在启用..."));

    // 获取模块基址
    if (m_dwTargetAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
        {
            m_dwTargetAddress = dwModuleBase + TARGET_INIT_VALUE_OFFSET;
            AddLog(_T("[初始值10000] 目标地址: 0x%08X"), m_dwTargetAddress);
        }
        else
        {
            AddLog(_T("[初始值10000] 无法获取模块基址"));
            return;
        }
    }

    // 使用Cheat Engine脚本中的字节码
    // [ENABLE] 部分的字节码: C7 85 60 55 00 00 10 27 00 00
    BYTE enableBytes[] = { 0xC7, 0x85, 0x60, 0x55, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00 };

    // 修改内存保护属性
    DWORD dwOldProtect = 0;
    if (!VirtualProtectEx(m_hProcess, (LPVOID)m_dwTargetAddress, 10,
        PAGE_READWRITE, &dwOldProtect))
    {
        AddLog(_T("[初始值10000] 修改内存保护失败，错误码: %d"), GetLastError());
        return;
    }

    // 直接写入字节码
    SIZE_T bytesWritten = 0;
    if (WriteProcessMemory(m_hProcess, (LPVOID)m_dwTargetAddress, enableBytes, 10, &bytesWritten))
    {
        AddLog(_T("[初始值10000] 成功启用！初始阳光变为10000"));
        m_bSunInitBigValueEnabled = TRUE;
    }
    else
    {
        AddLog(_T("[初始值10000] 修改失败，错误码: %d"), GetLastError());
    }

    // 恢复内存保护属性
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwTargetAddress, 10, dwOldProtect, &dwOldProtect);
}

// 禁用初始值10000功能
void CPlantsCEDlg::DisableSunInitBigValue()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[初始值10000] 错误: 未附加进程"));
        return;
    }

    if (!m_bSunInitBigValueEnabled)
    {
        AddLog(_T("[初始值10000] 已经禁用"));
        return;
    }

    AddLog(_T("[初始值10000] 正在禁用，恢复默认50阳光..."));

    // 获取模块基址
    if (m_dwTargetAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
        {
            m_dwTargetAddress = dwModuleBase + TARGET_INIT_VALUE_OFFSET;
        }
        else
        {
            AddLog(_T("[初始值10000] 无法获取模块基址"));
            return;
        }
    }

    // 使用Cheat Engine脚本中的原始字节码
    // [DISABLE] 部分的字节码: C7 85 60 55 00 00 32 00 00 00
    BYTE disableBytes[] = { 0xC7, 0x85, 0x60, 0x55, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00 };

    // 修改内存保护属性
    DWORD dwOldProtect = 0;
    if (!VirtualProtectEx(m_hProcess, (LPVOID)m_dwTargetAddress, 10,
        PAGE_READWRITE, &dwOldProtect))
    {
        AddLog(_T("[初始值10000] 修改内存保护失败，错误码: %d"), GetLastError());
        return;
    }

    // 恢复原始字节码
    SIZE_T bytesWritten = 0;
    if (WriteProcessMemory(m_hProcess, (LPVOID)m_dwTargetAddress, disableBytes, 10, &bytesWritten))
    {
        AddLog(_T("[初始值10000] 成功禁用！已恢复默认50阳光"));
        m_bSunInitBigValueEnabled = FALSE;
    }
    else
    {
        AddLog(_T("[初始值10000] 恢复失败，错误码: %d"), GetLastError());
    }

    // 恢复内存保护属性
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwTargetAddress, 10, dwOldProtect, &dwOldProtect);
}


void CPlantsCEDlg::OnBnClickedSmallsunadd1000()
{
    // TODO: 在此添加控件通知处理程序代码
}


void CPlantsCEDlg::OnBnClickedBigsunadd2000()
{
    // TODO: 在此添加控件通知处理程序代码
}


void CPlantsCEDlg::OnBnClickedSuninitbigvalue()
{
    // TODO: 在此添加控件通知处理程序代码
    int nCheck = m_checkSunInitBigValue.GetCheck();

    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("[初始值10000] 错误: 请先附加进程"));
        // 恢复之前的选中状态
        m_checkSunInitBigValue.SetCheck(m_bSunInitBigValueEnabled ? BST_CHECKED : BST_UNCHECKED);
        return;
    }

    if (nCheck == BST_CHECKED)  // 启用
    {
        EnableSunInitBigValue();
    }
    else  // 禁用
    {
        DisableSunInitBigValue();
    }
    // 保存配置
    SaveConfigToIni();
}


// 启用无CD功能
void CPlantsCEDlg::EnableNoPlantCD()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[无CD功能] 错误: 未附加进程"));
        return;
    }

    if (m_bNoPlantCDEnabled)
    {
        AddLog(_T("[无CD功能] 已经启用"));
        return;
    }

    AddLog(_T("[无CD功能] 正在启用种植无CD..."));

    // 获取模块基址和完整地址
    if (m_dwNoPlantCDAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
        {
            m_dwNoPlantCDAddress = dwModuleBase + NO_PLANT_CD_OFFSET;
            AddLog(_T("[无CD功能] 目标地址: 0x%08X"), m_dwNoPlantCDAddress);
        }
        else
        {
            AddLog(_T("[无CD功能] 无法获取模块基址"));
            return;
        }
    }

    // 读取当前字节码
    BYTE currentBytes[9] = { 0 };  // 原始指令9字节
    SIZE_T bytesRead = 0;
    if (ReadProcessMemory(m_hProcess, (LPCVOID)m_dwNoPlantCDAddress, currentBytes, 9, &bytesRead))
    {
        AddLog(_T("[无CD功能] 当前字节码: %02X %02X %02X %02X %02X %02X %02X %02X %02X"),
            currentBytes[0], currentBytes[1], currentBytes[2], currentBytes[3], currentBytes[4],
            currentBytes[5], currentBytes[6], currentBytes[7], currentBytes[8]);
    }

    // 修改内存保护属性
    DWORD dwOldProtect = 0;
    if (!VirtualProtectEx(m_hProcess, (LPVOID)m_dwNoPlantCDAddress, 9,
        PAGE_EXECUTE_READWRITE, &dwOldProtect))
    {
        AddLog(_T("[无CD功能] 修改内存保护失败，错误码: %d"), GetLastError());
        return;
    }

    // 根据Cheat Engine脚本，启用时需要替换的字节码
    // 原始: 7E 14 C7 47 24 00 00 00 00 (jle + nop + mov)
    // 修改为: 90 C7 47 24 00 00 00 00 90 (nop + mov + nop)
    // 实际上我们只需要将条件跳转改为无条件执行

    // 方法1: 直接修改为 nop + mov [edi+24],0 + nop
    BYTE enableBytes[] = {
        0x90,                               // nop (替换 jle)
        0xC7, 0x47, 0x24, 0x00, 0x00, 0x00, 0x00,  // mov [edi+24],00000000
        0x90                                // nop (填充)
    };

    // 写入修改后的字节码
    SIZE_T bytesWritten = 0;
    if (WriteProcessMemory(m_hProcess, (LPVOID)m_dwNoPlantCDAddress, enableBytes, 9, &bytesWritten))
    {
        AddLog(_T("[无CD功能] 成功启用！种植植物将无冷却时间"));
        AddLog(_T("[无CD功能] 修改字节码: %02X %02X %02X %02X %02X %02X %02X %02X %02X"),
            enableBytes[0], enableBytes[1], enableBytes[2], enableBytes[3], enableBytes[4],
            enableBytes[5], enableBytes[6], enableBytes[7], enableBytes[8]);
        m_bNoPlantCDEnabled = TRUE;

        // 验证修改
        BYTE verifyBytes[9] = { 0 };
        if (ReadProcessMemory(m_hProcess, (LPCVOID)m_dwNoPlantCDAddress, verifyBytes, 9, &bytesRead))
        {
            if (memcmp(enableBytes, verifyBytes, 9) == 0)
            {
                AddLog(_T("[无CD功能] 验证成功，内存修改正确"));
            }
            else
            {
                AddLog(_T("[无CD功能] 验证失败，请检查"));
            }
        }
    }
    else
    {
        AddLog(_T("[无CD功能] 修改失败，错误码: %d"), GetLastError());
    }

    // 恢复内存保护属性
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwNoPlantCDAddress, 9, dwOldProtect, &dwOldProtect);
}

// 禁用无CD功能（恢复原始代码）
void CPlantsCEDlg::DisableNoPlantCD()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[无CD功能] 错误: 未附加进程"));
        return;
    }

    if (!m_bNoPlantCDEnabled)
    {
        AddLog(_T("[无CD功能] 已经禁用"));
        return;
    }

    AddLog(_T("[无CD功能] 正在禁用，恢复正常CD..."));

    // 获取模块基址
    if (m_dwNoPlantCDAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
        {
            m_dwNoPlantCDAddress = dwModuleBase + NO_PLANT_CD_OFFSET;
        }
        else
        {
            AddLog(_T("[无CD功能] 无法获取模块基址"));
            return;
        }
    }

    // 原始字节码: 7E 14 C7 47 24 00 00 00 00
    // jle + mov [edi+24],00000000
    BYTE originalBytes[] = {
        0x7E, 0x14,                      // jle PlantsVsZombies_后台.exe+872AC
        0xC7, 0x47, 0x24, 0x00, 0x00, 0x00, 0x00  // mov [edi+24],00000000
    };

    // 修改内存保护属性
    DWORD dwOldProtect = 0;
    if (!VirtualProtectEx(m_hProcess, (LPVOID)m_dwNoPlantCDAddress, 9,
        PAGE_EXECUTE_READWRITE, &dwOldProtect))
    {
        AddLog(_T("[无CD功能] 修改内存保护失败，错误码: %d"), GetLastError());
        return;
    }

    // 恢复原始字节码
    SIZE_T bytesWritten = 0;
    if (WriteProcessMemory(m_hProcess, (LPVOID)m_dwNoPlantCDAddress, originalBytes, 9, &bytesWritten))
    {
        AddLog(_T("[无CD功能] 成功禁用！已恢复正常冷却时间"));
        AddLog(_T("[无CD功能] 恢复字节码: %02X %02X %02X %02X %02X %02X %02X %02X %02X"),
            originalBytes[0], originalBytes[1], originalBytes[2], originalBytes[3], originalBytes[4],
            originalBytes[5], originalBytes[6], originalBytes[7], originalBytes[8]);
        m_bNoPlantCDEnabled = FALSE;

        // 验证恢复
        BYTE verifyBytes[9] = { 0 };
        SIZE_T bytesRead = 0;
        if (ReadProcessMemory(m_hProcess, (LPCVOID)m_dwNoPlantCDAddress, verifyBytes, 9, &bytesRead))
        {
            if (memcmp(originalBytes, verifyBytes, 9) == 0)
            {
                AddLog(_T("[无CD功能] 验证成功，内存恢复正确"));
            }
            else
            {
                AddLog(_T("[无CD功能] 验证失败，请检查"));
            }
        }
    }
    else
    {
        AddLog(_T("[无CD功能] 恢复失败，错误码: %d"), GetLastError());
    }

    // 恢复内存保护属性
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwNoPlantCDAddress, 9, dwOldProtect, &dwOldProtect);
}

void CPlantsCEDlg::OnBnClickedNocdplant()
{
    // TODO: 在此添加控件通知处理程序代码
    int nCheck = m_checkNoPlantCD.GetCheck();

    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("[无CD功能] 错误: 请先附加进程"));
        // 恢复之前的选中状态
        m_checkNoPlantCD.SetCheck(m_bNoPlantCDEnabled ? BST_CHECKED : BST_UNCHECKED);
        return;
    }

    if (nCheck == BST_CHECKED)  // 启用
    {
        EnableNoPlantCD();
    }
    else  // 禁用
    {
        DisableNoPlantCD();
    }
}


// PlantsCEDlg.cpp - 自动快速生产阳光功能部分

// ==================== 自动快速生产阳光功能 ====================

// 原始字节码 (mov [edi+58], eax; mov eax, [edi])
const BYTE AUTO_FAST_SUN_ORIGINAL_BYTES[] = { 0x89, 0x47, 0x58, 0x8B, 0x07 };

// 自定义代码 (与CE实际运行一致)
// mov [edi+58], 64
// mov eax, [edi]
// jmp returnhere
const BYTE AUTO_FAST_SUN_NEW_CODE[] = {
    0xC7, 0x47, 0x58, 0x64, 0x00, 0x00, 0x00,  // mov [edi+58], 00000064
    0x8B, 0x07,                                 // mov eax, [edi]
    0xE9                                        // jmp (偏移量需要计算)
};

// 分配内存
BOOL CPlantsCEDlg::AllocateMemoryForAutoFastSun()
{
    if (m_bAutoFastSunMemoryAllocated && m_dwAutoFastSunAllocated)
    {
        return TRUE;
    }

    AddLog(_T("[自动快速阳光] 正在分配内存..."));

    m_dwAutoFastSunAllocated = (DWORD_PTR)VirtualAllocEx(
        m_hProcess,
        NULL,
        2048,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE
    );

    if (!m_dwAutoFastSunAllocated)
    {
        AddLog(_T("[自动快速阳光] 分配内存失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    AddLog(_T("[自动快速阳光] 内存分配成功: 0x%08X"), m_dwAutoFastSunAllocated);
    m_bAutoFastSunMemoryAllocated = TRUE;
    return TRUE;
}

// 写入自定义代码
BOOL CPlantsCEDlg::WriteCustomCodeForAutoFastSun()
{
    if (!m_bAutoFastSunMemoryAllocated)
        return FALSE;

    // 计算返回地址：原地址 + 5 (JMP指令长度)
    DWORD_PTR returnAddress = m_dwAutoFastSunAddress + 5;

    // 计算JMP偏移：JMP指令位置到返回地址的偏移
    // JMP指令位置 = 分配地址 + (自定义代码大小 - 1)
    DWORD_PTR jmpPosition = m_dwAutoFastSunAllocated + (sizeof(AUTO_FAST_SUN_NEW_CODE) - 1);
    DWORD jmpOffset = (DWORD)(returnAddress - jmpPosition - 5);

    // 计算完整代码大小
    const size_t codeSize = sizeof(AUTO_FAST_SUN_NEW_CODE) + 4;

    BYTE* fullCode = new BYTE[codeSize];
    memcpy(fullCode, AUTO_FAST_SUN_NEW_CODE, sizeof(AUTO_FAST_SUN_NEW_CODE));

    // 设置JMP偏移
    size_t jmpPos = sizeof(AUTO_FAST_SUN_NEW_CODE) - 1;
    fullCode[jmpPos] = 0xE9;
    fullCode[sizeof(AUTO_FAST_SUN_NEW_CODE)] = (BYTE)(jmpOffset & 0xFF);
    fullCode[sizeof(AUTO_FAST_SUN_NEW_CODE) + 1] = (BYTE)((jmpOffset >> 8) & 0xFF);
    fullCode[sizeof(AUTO_FAST_SUN_NEW_CODE) + 2] = (BYTE)((jmpOffset >> 16) & 0xFF);
    fullCode[sizeof(AUTO_FAST_SUN_NEW_CODE) + 3] = (BYTE)((jmpOffset >> 24) & 0xFF);

    AddLog(_T("[自动快速阳光] 分配地址: 0x%08X"), m_dwAutoFastSunAllocated);
    AddLog(_T("[自动快速阳光] 目标地址: 0x%08X"), m_dwAutoFastSunAddress);
    AddLog(_T("[自动快速阳光] 返回地址: 0x%08X (原地址+5)"), returnAddress);
    AddLog(_T("[自动快速阳光] JMP位置: 0x%08X"), jmpPosition);
    AddLog(_T("[自动快速阳光] JMP偏移: 0x%08X"), jmpOffset);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwAutoFastSunAllocated,
        fullCode, codeSize, &bytesWritten);

    if (bResult && bytesWritten == codeSize)
    {
        CString strCode;
        for (size_t i = 0; i < codeSize; i++)
        {
            strCode.AppendFormat(_T("%02X "), fullCode[i]);
        }
        AddLog(_T("[自动快速阳光] 写入代码: %s"), strCode);
        AddLog(_T("[自动快速阳光] 自定义代码写入成功"));
    }
    else
    {
        AddLog(_T("[自动快速阳光] 写入失败，错误码: %d"), GetLastError());
    }

    delete[] fullCode;
    return (bResult && bytesWritten == codeSize);
}

// 安装Hook
BOOL CPlantsCEDlg::InstallHookForAutoFastSun()
{
    AddLog(_T("[自动快速阳光] 正在安装Hook..."));

    // 计算JMP偏移：从目标地址跳转到分配的内存
    DWORD jmpOffset = (DWORD)(m_dwAutoFastSunAllocated - (m_dwAutoFastSunAddress + 5));

    BYTE jmpInstruction[5] = { 0xE9 };
    jmpInstruction[1] = (BYTE)(jmpOffset & 0xFF);
    jmpInstruction[2] = (BYTE)((jmpOffset >> 8) & 0xFF);
    jmpInstruction[3] = (BYTE)((jmpOffset >> 16) & 0xFF);
    jmpInstruction[4] = (BYTE)((jmpOffset >> 24) & 0xFF);

    AddLog(_T("[自动快速阳光] JMP从 0x%08X 到 0x%08X"),
        m_dwAutoFastSunAddress, m_dwAutoFastSunAllocated);
    AddLog(_T("[自动快速阳光] JMP偏移: 0x%08X"), jmpOffset);
    AddLog(_T("[自动快速阳光] JMP指令: %02X %02X %02X %02X %02X"),
        jmpInstruction[0], jmpInstruction[1], jmpInstruction[2],
        jmpInstruction[3], jmpInstruction[4]);

    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwAutoFastSunAddress, 5,
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwAutoFastSunAddress,
        jmpInstruction, 5, &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwAutoFastSunAddress, 5, dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == 5)
    {
        AddLog(_T("[自动快速阳光] Hook安装成功！"));
        return TRUE;
    }
    else
    {
        AddLog(_T("[自动快速阳光] Hook安装失败，错误码: %d"), GetLastError());
        return FALSE;
    }
}

// 释放内存
void CPlantsCEDlg::FreeAutoFastSunMemory()
{
    if (m_bAutoFastSunMemoryAllocated && m_dwAutoFastSunAllocated)
    {
        VirtualFreeEx(m_hProcess, (LPVOID)m_dwAutoFastSunAllocated, 0, MEM_RELEASE);
        AddLog(_T("[自动快速阳光] 内存已释放"));
        m_bAutoFastSunMemoryAllocated = FALSE;
        m_dwAutoFastSunAllocated = 0;
    }
}

// 启用自动快速生产阳光
void CPlantsCEDlg::EnableAutoFastSun()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[自动快速阳光] 错误: 未附加进程"));
        return;
    }

    if (m_bAutoFastSunEnabled)
    {
        AddLog(_T("[自动快速阳光] 已经启用"));
        return;
    }

    AddLog(_T("[自动快速阳光] 正在启用..."));

    // 获取目标地址
    if (m_dwAutoFastSunAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
        {
            m_dwAutoFastSunAddress = dwModuleBase + AUTO_FAST_SUN_OFFSET;
            AddLog(_T("[自动快速阳光] 目标地址: 0x%08X"), m_dwAutoFastSunAddress);
        }
        else
        {
            AddLog(_T("[自动快速阳光] 无法获取模块基址"));
            return;
        }
    }

    // 读取当前字节码
    BYTE currentBytes[5] = { 0 };
    SIZE_T bytesRead = 0;
    if (ReadProcessMemory(m_hProcess, (LPCVOID)m_dwAutoFastSunAddress, currentBytes, 5, &bytesRead))
    {
        AddLog(_T("[自动快速阳光] 当前字节码: %02X %02X %02X %02X %02X"),
            currentBytes[0], currentBytes[1], currentBytes[2], currentBytes[3], currentBytes[4]);
    }

    // 1. 分配内存
    if (!AllocateMemoryForAutoFastSun())
        return;

    // 2. 写入自定义代码
    if (!WriteCustomCodeForAutoFastSun())
    {
        FreeAutoFastSunMemory();
        return;
    }

    // 3. 安装Hook
    if (!InstallHookForAutoFastSun())
    {
        FreeAutoFastSunMemory();
        return;
    }

    m_bAutoFastSunEnabled = TRUE;
    AddLog(_T("[自动快速阳光] 成功启用！获取阳光时自动变为100"));
}

// 禁用自动快速生产阳光
void CPlantsCEDlg::DisableAutoFastSun()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[自动快速阳光] 错误: 未附加进程"));
        return;
    }

    if (!m_bAutoFastSunEnabled)
    {
        AddLog(_T("[自动快速阳光] 已经禁用"));
        return;
    }

    AddLog(_T("[自动快速阳光] 正在禁用..."));

    if (m_dwAutoFastSunAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
            m_dwAutoFastSunAddress = dwModuleBase + AUTO_FAST_SUN_OFFSET;
    }

    // 恢复原始字节码
    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwAutoFastSunAddress, sizeof(AUTO_FAST_SUN_ORIGINAL_BYTES),
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwAutoFastSunAddress,
        AUTO_FAST_SUN_ORIGINAL_BYTES, sizeof(AUTO_FAST_SUN_ORIGINAL_BYTES), &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwAutoFastSunAddress, sizeof(AUTO_FAST_SUN_ORIGINAL_BYTES),
        dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == sizeof(AUTO_FAST_SUN_ORIGINAL_BYTES))
    {
        AddLog(_T("[自动快速阳光] 成功禁用！已恢复正常阳光获取"));
        m_bAutoFastSunEnabled = FALSE;
        FreeAutoFastSunMemory();
    }
    else
    {
        AddLog(_T("[自动快速阳光] 恢复失败，错误码: %d"), GetLastError());
    }
}
void CPlantsCEDlg::OnBnClickedAutosunproduce()
{
    // TODO: 在此添加控件通知处理程序代码
    int nCheck = m_checkAutoFastSun.GetCheck();

    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("[自动快速阳光] 错误: 请先附加进程"));
        // 恢复之前的选中状态
        m_checkAutoFastSun.SetCheck(m_bAutoFastSunEnabled ? BST_CHECKED : BST_UNCHECKED);
        return;
    }

    if (nCheck == BST_CHECKED)  // 启用
    {
        EnableAutoFastSun();
    }
    else  // 禁用
    {
        DisableAutoFastSun();
    }

    // 保存配置
    SaveConfigToIni();
}

// PlantsCEDlg.cpp - 添加自动收集阳光功能

// ==================== 自动收集阳光功能 ====================

// 原始字节码 (jne PlantsVsZombies_后台.exe+31599; push ebx; call PlantsVsZombies_后台.exe+30AC0)
// 对应汇编: 75 08 53 E8 29 F5 FF FF
const BYTE AUTO_COLLECT_SUN_ORIGINAL_BYTES[] = {
    0x75, 0x08,                         // jne PlantsVsZombies_后台.exe+31599
    0x53,                               // push ebx
    0xE8, 0x29, 0xF5, 0xFF, 0xFF        // call PlantsVsZombies_后台.exe+30AC0
};

// 自定义代码 (直接跳转到收集阳光的代码，跳过判断)
// jmp PlantsVsZombies_后台.exe+31599
// push ebx
// call PlantsVsZombies_后台.exe+30AC0
const BYTE AUTO_COLLECT_SUN_NEW_CODE[] = {
    0xE9,                               // jmp (偏移量需要计算)
    0x53,                               // push ebx
    0xE8, 0x29, 0xF5, 0xFF, 0xFF        // call PlantsVsZombies_后台.exe+30AC0
};

// 分配内存
BOOL CPlantsCEDlg::AllocateMemoryForAutoCollectSun()
{
    if (m_bAutoCollectSunMemoryAllocated && m_dwAutoCollectSunAllocated)
    {
        return TRUE;
    }

    AddLog(_T("[自动收集阳光] 正在分配内存..."));

    m_dwAutoCollectSunAllocated = (DWORD_PTR)VirtualAllocEx(
        m_hProcess,
        NULL,
        2048,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE
    );

    if (!m_dwAutoCollectSunAllocated)
    {
        AddLog(_T("[自动收集阳光] 分配内存失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    AddLog(_T("[自动收集阳光] 内存分配成功: 0x%08X"), m_dwAutoCollectSunAllocated);
    m_bAutoCollectSunMemoryAllocated = TRUE;
    return TRUE;
}

// 写入自定义代码
BOOL CPlantsCEDlg::WriteCustomCodeForAutoCollectSun()
{
    if (!m_bAutoCollectSunMemoryAllocated)
        return FALSE;

    // 计算JMP偏移：从自定义代码的JMP位置跳转到目标地址
    // 目标地址 = 原地址 + 0x31599? 实际上应该跳转到 PlantsVsZombies_后台.exe+31599
    // 但为了简化，我们直接计算跳转到原地址+0xA (因为原始代码有jne指令)
    DWORD_PTR jumpTarget = m_dwAutoCollectSunAddress + 0xA;  // +0xA 是 jne跳转的目标

    // JMP指令位置 = 分配地址
    DWORD jmpOffset = (DWORD)(jumpTarget - (m_dwAutoCollectSunAllocated + 5));

    // 计算完整代码大小
    const size_t codeSize = sizeof(AUTO_COLLECT_SUN_NEW_CODE) + 4;  // +4 是JMP偏移量

    BYTE* fullCode = new BYTE[codeSize];

    // 复制NEW_CODE的内容
    memcpy(fullCode, AUTO_COLLECT_SUN_NEW_CODE, sizeof(AUTO_COLLECT_SUN_NEW_CODE));

    // 设置JMP偏移
    fullCode[0] = 0xE9;  // JMP指令
    fullCode[1] = (BYTE)(jmpOffset & 0xFF);
    fullCode[2] = (BYTE)((jmpOffset >> 8) & 0xFF);
    fullCode[3] = (BYTE)((jmpOffset >> 16) & 0xFF);
    fullCode[4] = (BYTE)((jmpOffset >> 24) & 0xFF);

    // 复制剩余的代码（push ebx; call ...）
    memcpy(fullCode + 5, AUTO_COLLECT_SUN_NEW_CODE + 1, sizeof(AUTO_COLLECT_SUN_NEW_CODE) - 1);

    AddLog(_T("[自动收集阳光] 分配地址: 0x%08X"), m_dwAutoCollectSunAllocated);
    AddLog(_T("[自动收集阳光] 目标地址: 0x%08X"), m_dwAutoCollectSunAddress);
    AddLog(_T("[自动收集阳光] 跳转目标: 0x%08X"), jumpTarget);
    AddLog(_T("[自动收集阳光] JMP偏移: 0x%08X"), jmpOffset);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwAutoCollectSunAllocated,
        fullCode, codeSize, &bytesWritten);

    if (bResult && bytesWritten == codeSize)
    {
        CString strCode;
        for (size_t i = 0; i < codeSize; i++)
        {
            strCode.AppendFormat(_T("%02X "), fullCode[i]);
        }
        AddLog(_T("[自动收集阳光] 写入代码: %s"), strCode);
        AddLog(_T("[自动收集阳光] 自定义代码写入成功"));
    }
    else
    {
        AddLog(_T("[自动收集阳光] 写入失败，错误码: %d"), GetLastError());
    }

    delete[] fullCode;
    return (bResult && bytesWritten == codeSize);
}

// 安装Hook
BOOL CPlantsCEDlg::InstallHookForAutoCollectSun()
{
    AddLog(_T("[自动收集阳光] 正在安装Hook..."));

    // 计算JMP偏移：从目标地址跳转到分配的内存
    DWORD jmpOffset = (DWORD)(m_dwAutoCollectSunAllocated - (m_dwAutoCollectSunAddress + 5));

    BYTE jmpInstruction[5] = { 0xE9 };
    jmpInstruction[1] = (BYTE)(jmpOffset & 0xFF);
    jmpInstruction[2] = (BYTE)((jmpOffset >> 8) & 0xFF);
    jmpInstruction[3] = (BYTE)((jmpOffset >> 16) & 0xFF);
    jmpInstruction[4] = (BYTE)((jmpOffset >> 24) & 0xFF);

    AddLog(_T("[自动收集阳光] JMP从 0x%08X 到 0x%08X"),
        m_dwAutoCollectSunAddress, m_dwAutoCollectSunAllocated);
    AddLog(_T("[自动收集阳光] JMP偏移: 0x%08X"), jmpOffset);
    AddLog(_T("[自动收集阳光] JMP指令: %02X %02X %02X %02X %02X"),
        jmpInstruction[0], jmpInstruction[1], jmpInstruction[2],
        jmpInstruction[3], jmpInstruction[4]);

    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwAutoCollectSunAddress, 5,
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwAutoCollectSunAddress,
        jmpInstruction, 5, &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwAutoCollectSunAddress, 5, dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == 5)
    {
        AddLog(_T("[自动收集阳光] Hook安装成功！"));
        return TRUE;
    }
    else
    {
        AddLog(_T("[自动收集阳光] Hook安装失败，错误码: %d"), GetLastError());
        return FALSE;
    }
}

// 释放内存
void CPlantsCEDlg::FreeAutoCollectSunMemory()
{
    if (m_bAutoCollectSunMemoryAllocated && m_dwAutoCollectSunAllocated)
    {
        VirtualFreeEx(m_hProcess, (LPVOID)m_dwAutoCollectSunAllocated, 0, MEM_RELEASE);
        AddLog(_T("[自动收集阳光] 内存已释放"));
        m_bAutoCollectSunMemoryAllocated = FALSE;
        m_dwAutoCollectSunAllocated = 0;
    }
}

// 启用自动收集阳光
void CPlantsCEDlg::EnableAutoCollectSun()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[自动收集阳光] 错误: 未附加进程"));
        return;
    }

    if (m_bAutoCollectSunEnabled)
    {
        AddLog(_T("[自动收集阳光] 已经启用"));
        return;
    }

    AddLog(_T("[自动收集阳光] 正在启用..."));

    // 获取目标地址
    if (m_dwAutoCollectSunAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
        {
            m_dwAutoCollectSunAddress = dwModuleBase + AUTO_COLLECT_SUN_OFFSET;
            AddLog(_T("[自动收集阳光] 目标地址: 0x%08X"), m_dwAutoCollectSunAddress);
        }
        else
        {
            AddLog(_T("[自动收集阳光] 无法获取模块基址"));
            return;
        }
    }

    // 读取当前字节码
    BYTE currentBytes[8] = { 0 };
    SIZE_T bytesRead = 0;
    if (ReadProcessMemory(m_hProcess, (LPCVOID)m_dwAutoCollectSunAddress, currentBytes, 8, &bytesRead))
    {
        AddLog(_T("[自动收集阳光] 当前字节码: %02X %02X %02X %02X %02X %02X %02X %02X"),
            currentBytes[0], currentBytes[1], currentBytes[2], currentBytes[3],
            currentBytes[4], currentBytes[5], currentBytes[6], currentBytes[7]);
    }

    // 1. 分配内存
    if (!AllocateMemoryForAutoCollectSun())
        return;

    // 2. 写入自定义代码
    if (!WriteCustomCodeForAutoCollectSun())
    {
        FreeAutoCollectSunMemory();
        return;
    }

    // 3. 安装Hook
    if (!InstallHookForAutoCollectSun())
    {
        FreeAutoCollectSunMemory();
        return;
    }

    m_bAutoCollectSunEnabled = TRUE;
    AddLog(_T("[自动收集阳光] 成功启用！阳光将自动快速收集"));
}

// 禁用自动收集阳光
void CPlantsCEDlg::DisableAutoCollectSun()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[自动收集阳光] 错误: 未附加进程"));
        return;
    }

    if (!m_bAutoCollectSunEnabled)
    {
        AddLog(_T("[自动收集阳光] 已经禁用"));
        return;
    }

    AddLog(_T("[自动收集阳光] 正在禁用..."));

    if (m_dwAutoCollectSunAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
            m_dwAutoCollectSunAddress = dwModuleBase + AUTO_COLLECT_SUN_OFFSET;
    }

    // 恢复原始字节码
    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwAutoCollectSunAddress, sizeof(AUTO_COLLECT_SUN_ORIGINAL_BYTES),
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwAutoCollectSunAddress,
        AUTO_COLLECT_SUN_ORIGINAL_BYTES, sizeof(AUTO_COLLECT_SUN_ORIGINAL_BYTES), &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwAutoCollectSunAddress, sizeof(AUTO_COLLECT_SUN_ORIGINAL_BYTES),
        dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == sizeof(AUTO_COLLECT_SUN_ORIGINAL_BYTES))
    {
        AddLog(_T("[自动收集阳光] 成功禁用！恢复正常收集"));
        m_bAutoCollectSunEnabled = FALSE;
        FreeAutoCollectSunMemory();
    }
    else
    {
        AddLog(_T("[自动收集阳光] 恢复失败，错误码: %d"), GetLastError());
    }
}

void CPlantsCEDlg::OnBnClickedAutocollectsun()
{
    // TODO: 在此添加控件通知处理程序代码
    int nCheck = m_checkAutoCollectSun.GetCheck();

    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("[自动收集阳光] 错误: 请先附加进程"));
        m_checkAutoCollectSun.SetCheck(m_bAutoCollectSunEnabled ? BST_CHECKED : BST_UNCHECKED);
        return;
    }

    if (nCheck == BST_CHECKED)
    {
        EnableAutoCollectSun();
    }
    else
    {
        DisableAutoCollectSun();
    }

    // 保存配置
    SaveConfigToIni();
}


// PlantsCEDlg.cpp - 添加快速发射功能

// ==================== 快速发射功能 ====================

// 原始字节码 (jne PlantsVsZombies_后台.exe+64934)
// 对应汇编: 0F 85 98 FE FF FF
const BYTE FAST_SHOOT_ORIGINAL_BYTES[] = {
    0x0F, 0x85, 0x98, 0xFE, 0xFF, 0xFF  // jne PlantsVsZombies_后台.exe+64934
};

// 自定义代码 (NOP掉条件跳转，实现快速发射)
// nop (6个nop，因为原始指令是6字节)
const BYTE FAST_SHOOT_NEW_CODE[] = {
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90  // 6个nop
};

// 分配内存
BOOL CPlantsCEDlg::AllocateMemoryForFastShoot()
{
    if (m_bFastShootMemoryAllocated && m_dwFastShootAllocated)
    {
        return TRUE;
    }

    AddLog(_T("[快速发射] 正在分配内存..."));

    m_dwFastShootAllocated = (DWORD_PTR)VirtualAllocEx(
        m_hProcess,
        NULL,
        2048,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE
    );

    if (!m_dwFastShootAllocated)
    {
        AddLog(_T("[快速发射] 分配内存失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    AddLog(_T("[快速发射] 内存分配成功: 0x%08X"), m_dwFastShootAllocated);
    m_bFastShootMemoryAllocated = TRUE;
    return TRUE;
}

// 写入自定义代码
BOOL CPlantsCEDlg::WriteCustomCodeForFastShoot()
{
    if (!m_bFastShootMemoryAllocated)
        return FALSE;

    // 计算返回地址的JMP偏移
    // 新代码执行完后需要跳回原地址+6 (JMP指令占用5字节，但原始指令6字节，所以返回地址是原地址+6)
    DWORD_PTR returnAddress = m_dwFastShootAddress + 6;

    // 计算JMP偏移：从自定义代码的JMP指令位置跳转到返回地址
    DWORD_PTR jmpPosition = m_dwFastShootAllocated + sizeof(FAST_SHOOT_NEW_CODE);
    DWORD jmpOffset = (DWORD)(returnAddress - (jmpPosition + 5));

    // 计算完整代码大小：自定义代码 + JMP指令(5字节)
    const size_t codeSize = sizeof(FAST_SHOOT_NEW_CODE) + 5;

    BYTE* fullCode = new BYTE[codeSize];

    // 复制NOP代码
    memcpy(fullCode, FAST_SHOOT_NEW_CODE, sizeof(FAST_SHOOT_NEW_CODE));

    // 添加JMP指令跳回原程序
    fullCode[sizeof(FAST_SHOOT_NEW_CODE)] = 0xE9;  // JMP指令
    fullCode[sizeof(FAST_SHOOT_NEW_CODE) + 1] = (BYTE)(jmpOffset & 0xFF);
    fullCode[sizeof(FAST_SHOOT_NEW_CODE) + 2] = (BYTE)((jmpOffset >> 8) & 0xFF);
    fullCode[sizeof(FAST_SHOOT_NEW_CODE) + 3] = (BYTE)((jmpOffset >> 16) & 0xFF);
    fullCode[sizeof(FAST_SHOOT_NEW_CODE) + 4] = (BYTE)((jmpOffset >> 24) & 0xFF);

    AddLog(_T("[快速发射] 分配地址: 0x%08X"), m_dwFastShootAllocated);
    AddLog(_T("[快速发射] 目标地址: 0x%08X"), m_dwFastShootAddress);
    AddLog(_T("[快速发射] 返回地址: 0x%08X (原地址+6)"), returnAddress);
    AddLog(_T("[快速发射] JMP位置: 0x%08X"), jmpPosition);
    AddLog(_T("[快速发射] JMP偏移: 0x%08X"), jmpOffset);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwFastShootAllocated,
        fullCode, codeSize, &bytesWritten);

    if (bResult && bytesWritten == codeSize)
    {
        CString strCode;
        for (size_t i = 0; i < codeSize; i++)
        {
            strCode.AppendFormat(_T("%02X "), fullCode[i]);
        }
        AddLog(_T("[快速发射] 写入代码: %s"), strCode);
        AddLog(_T("[快速发射] 自定义代码写入成功"));
    }
    else
    {
        AddLog(_T("[快速发射] 写入失败，错误码: %d"), GetLastError());
    }

    delete[] fullCode;
    return (bResult && bytesWritten == codeSize);
}

// 安装Hook
BOOL CPlantsCEDlg::InstallHookForFastShoot()
{
    AddLog(_T("[快速发射] 正在安装Hook..."));

    // 计算JMP偏移：从目标地址跳转到分配的内存
    DWORD jmpOffset = (DWORD)(m_dwFastShootAllocated - (m_dwFastShootAddress + 5));

    BYTE jmpInstruction[5] = { 0xE9 };
    jmpInstruction[1] = (BYTE)(jmpOffset & 0xFF);
    jmpInstruction[2] = (BYTE)((jmpOffset >> 8) & 0xFF);
    jmpInstruction[3] = (BYTE)((jmpOffset >> 16) & 0xFF);
    jmpInstruction[4] = (BYTE)((jmpOffset >> 24) & 0xFF);

    AddLog(_T("[快速发射] JMP从 0x%08X 到 0x%08X"),
        m_dwFastShootAddress, m_dwFastShootAllocated);
    AddLog(_T("[快速发射] JMP偏移: 0x%08X"), jmpOffset);
    AddLog(_T("[快速发射] JMP指令: %02X %02X %02X %02X %02X"),
        jmpInstruction[0], jmpInstruction[1], jmpInstruction[2],
        jmpInstruction[3], jmpInstruction[4]);

    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwFastShootAddress, 5,
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwFastShootAddress,
        jmpInstruction, 5, &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwFastShootAddress, 5, dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == 5)
    {
        AddLog(_T("[快速发射] Hook安装成功！"));
        return TRUE;
    }
    else
    {
        AddLog(_T("[快速发射] Hook安装失败，错误码: %d"), GetLastError());
        return FALSE;
    }
}

// 释放内存
void CPlantsCEDlg::FreeFastShootMemory()
{
    if (m_bFastShootMemoryAllocated && m_dwFastShootAllocated)
    {
        VirtualFreeEx(m_hProcess, (LPVOID)m_dwFastShootAllocated, 0, MEM_RELEASE);
        AddLog(_T("[快速发射] 内存已释放"));
        m_bFastShootMemoryAllocated = FALSE;
        m_dwFastShootAllocated = 0;
    }
}

// 启用快速发射功能
void CPlantsCEDlg::EnableFastShoot()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[快速发射] 错误: 未附加进程"));
        return;
    }

    if (m_bFastShootEnabled)
    {
        AddLog(_T("[快速发射] 已经启用"));
        return;
    }

    AddLog(_T("[快速发射] 正在启用..."));

    // 获取目标地址
    if (m_dwFastShootAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
        {
            m_dwFastShootAddress = dwModuleBase + FAST_SHOOT_OFFSET;
            AddLog(_T("[快速发射] 目标地址: 0x%08X"), m_dwFastShootAddress);
        }
        else
        {
            AddLog(_T("[快速发射] 无法获取模块基址"));
            return;
        }
    }

    // 读取当前字节码
    BYTE currentBytes[6] = { 0 };
    SIZE_T bytesRead = 0;
    if (ReadProcessMemory(m_hProcess, (LPCVOID)m_dwFastShootAddress, currentBytes, 6, &bytesRead))
    {
        AddLog(_T("[快速发射] 当前字节码: %02X %02X %02X %02X %02X %02X"),
            currentBytes[0], currentBytes[1], currentBytes[2],
            currentBytes[3], currentBytes[4], currentBytes[5]);
    }

    // 1. 分配内存
    if (!AllocateMemoryForFastShoot())
        return;

    // 2. 写入自定义代码
    if (!WriteCustomCodeForFastShoot())
    {
        FreeFastShootMemory();
        return;
    }

    // 3. 安装Hook
    if (!InstallHookForFastShoot())
    {
        FreeFastShootMemory();
        return;
    }

    m_bFastShootEnabled = TRUE;
    AddLog(_T("[快速发射] 成功启用！植物发射速度大幅提升"));
}

// 禁用快速发射功能
void CPlantsCEDlg::DisableFastShoot()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[快速发射] 错误: 未附加进程"));
        return;
    }

    if (!m_bFastShootEnabled)
    {
        AddLog(_T("[快速发射] 已经禁用"));
        return;
    }

    AddLog(_T("[快速发射] 正在禁用..."));

    if (m_dwFastShootAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
            m_dwFastShootAddress = dwModuleBase + FAST_SHOOT_OFFSET;
    }

    // 恢复原始字节码
    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwFastShootAddress, sizeof(FAST_SHOOT_ORIGINAL_BYTES),
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwFastShootAddress,
        FAST_SHOOT_ORIGINAL_BYTES, sizeof(FAST_SHOOT_ORIGINAL_BYTES), &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwFastShootAddress, sizeof(FAST_SHOOT_ORIGINAL_BYTES),
        dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == sizeof(FAST_SHOOT_ORIGINAL_BYTES))
    {
        AddLog(_T("[快速发射] 成功禁用！已恢复正常发射速度"));
        m_bFastShootEnabled = FALSE;
        FreeFastShootMemory();
    }
    else
    {
        AddLog(_T("[快速发射] 恢复失败，错误码: %d"), GetLastError());
    }
}

void CPlantsCEDlg::OnBnClickedFastshoot()
{
    // TODO: 在此添加控件通知处理程序代码
    int nCheck = m_checkFastShoot.GetCheck();

    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("[快速发射] 错误: 请先附加进程"));
        m_checkFastShoot.SetCheck(m_bFastShootEnabled ? BST_CHECKED : BST_UNCHECKED);
        return;
    }

    if (nCheck == BST_CHECKED)
    {
        EnableFastShoot();
    }
    else
    {
        DisableFastShoot();
    }

    // 保存配置
    SaveConfigToIni();
}


void CPlantsCEDlg::OnBnClickedSelectprocess()
{
    // TODO: 在此添加控件通知处理程序代码
    // 如果已经附加进程，先分离
    if (m_bAttached)
    {
        AddLog(_T("[选择进程] 请先分离当前进程"));
        MessageBox(_T("请先点击【附加进程】按钮分离当前进程！"),
            _T("提示"), MB_OK | MB_ICONINFORMATION);
        return;
    }

    // 打开文件选择对话框
    CFileDialog fileDlg(
        TRUE,                           // TRUE = 打开文件对话框
        _T("exe"),                      // 默认扩展名
        NULL,                           // 默认文件名
        OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,  // 标志
        _T("可执行文件 (*.exe)|*.exe|所有文件 (*.*)|*.*||"),  // 文件过滤器
        this
    );

    // 设置初始目录为当前目录
    fileDlg.m_ofn.lpstrInitialDir = _T(".\\");

    if (fileDlg.DoModal() == IDOK)
    {
        CString strFilePath = fileDlg.GetPathName();
        CString strFileName = fileDlg.GetFileName();

        AddLog(_T("[选择进程] 选择的文件: %s"), strFileName);
        AddLog(_T("[选择进程] 完整路径: %s"), strFilePath);

        // 只保存文件名（不含路径）
        m_strProcessName = strFileName;

        AddLog(_T("[选择进程] 当前目标进程: %s"), m_strProcessName);

        // 重置地址
        m_dwNoPlantCDAddress = 0;
        m_dwAutoFastSunAddress = 0;
        m_dwAutoCollectSunAddress = 0;
        m_dwFastShootAddress = 0;

        // 更新按钮文字显示当前进程
        CString strBtnText;
        strBtnText.Format(_T("[%s]"), m_strProcessName);
        m_btnSelectProcess.SetWindowText(strBtnText);

        // 保存配置
        SaveConfigToIni();
    }
}

// 初始化植物名称
void CPlantsCEDlg::InitPlantNames()
{
    const TCHAR* plantNames[] = {
        _T("豌豆射手"), _T("向日葵"), _T("樱桃炸弹"), _T("坚果墙"),
        _T("土豆地雷"), _T("寒冰射手"), _T("大嘴花"), _T("双发射手"),
        _T("小喷菇"), _T("阳光菇"), _T("大喷菇"), _T("墓碑吞噬者"),
        _T("魅惑菇"), _T("胆小菇"), _T("寒冰菇"), _T("毁灭菇"),
        _T("睡莲"), _T("窝瓜"), _T("三线射手"), _T("缠绕水草"),
        _T("火爆辣椒"), _T("地刺"), _T("火炬树桩"), _T("高坚果"),
        _T("海蘑菇"), _T("路灯花"), _T("仙人掌"), _T("三叶草"),
        _T("分裂豆"), _T("杨桃"), _T("南瓜头"), _T("磁力菇"),
        _T("卷心菜投手"), _T("花盆"), _T("玉米加农炮"), _T("咖啡豆"),
        _T("大蒜"), _T("叶子保护伞"), _T("金盏花"), _T("西瓜投手"),
        _T("机枪射手"), _T("双子向日葵"), _T("忧郁蘑菇"), _T("香蒲"),
        _T("冰瓜投手"), _T("吸金磁"), _T("地刺王"), _T("玉米投手")
    };

    for (int i = 0; i < 48; i++)
    {
        // 使用两位数格式，确保排序正确（00,01,02...47）
        m_arrPlantNames[i].Format(_T("%02d-%s"), i, plantNames[i]);
    }
}

// 初始化单个卡槽下拉框
void CPlantsCEDlg::InitSlotComboBox(CComboBox& combo, int nSlot)
{
    // 确保不使用排序
    combo.ModifyStyle(CBS_SORT, 0);

    // 按顺序添加植物名称
    for (int i = 0; i < 48; i++)
    {
        combo.AddString(m_arrPlantNames[i]);
    }
    combo.SetCurSel(0);

    UNREFERENCED_PARAMETER(nSlot);
}

// 获取指定卡槽地址
DWORD_PTR CPlantsCEDlg::GetSlotAddress(int nSlot)
{
    if (nSlot < 1 || nSlot > 10)
    {
        return 0;
    }

    if (!m_hProcess || !m_bAttached)
    {
        return 0;
    }

    // 读取第一级指针 (基址)
    DWORD_PTR ptr1 = 0;
    SIZE_T bytesRead = 0;

    if (!ReadProcessMemory(m_hProcess, (LPCVOID)m_dwSlotBaseAddress, &ptr1, sizeof(DWORD_PTR), &bytesRead))
    {
        AddLog(_T("[卡槽] 读取基址失败，错误码: %d"), GetLastError());
        return 0;
    }

    AddLog(_T("[卡槽] 基址[0x%08X] -> 指针1: 0x%08X"), m_dwSlotBaseAddress, ptr1);

    // 第一级偏移 768
    DWORD_PTR addr1 = ptr1 + m_dwSlotOffset1;
    AddLog(_T("[卡槽] 地址1: 0x%08X + 0x%X = 0x%08X"), ptr1, m_dwSlotOffset1, addr1);

    // 读取第二级指针
    DWORD_PTR ptr2 = 0;
    if (!ReadProcessMemory(m_hProcess, (LPCVOID)addr1, &ptr2, sizeof(DWORD_PTR), &bytesRead))
    {
        AddLog(_T("[卡槽] 读取第二级指针失败，错误码: %d"), GetLastError());
        return 0;
    }

    AddLog(_T("[卡槽] 地址1[0x%08X] -> 指针2: 0x%08X"), addr1, ptr2);

    // 第二级偏移 144
    DWORD_PTR addr2 = ptr2 + m_dwSlotOffset2;
    AddLog(_T("[卡槽] 地址2: 0x%08X + 0x%X = 0x%08X"), ptr2, m_dwSlotOffset2, addr2);

    // 读取第三级指针 (注意：这里需要再读一次指针)
    DWORD_PTR ptr3 = 0;
    if (!ReadProcessMemory(m_hProcess, (LPCVOID)addr2, &ptr3, sizeof(DWORD_PTR), &bytesRead))
    {
        AddLog(_T("[卡槽] 读取第三级指针失败，错误码: %d"), GetLastError());
        return 0;
    }

    AddLog(_T("[卡槽] 地址2[0x%08X] -> 指针3: 0x%08X"), addr2, ptr3);

    // 计算第三级偏移 (卡槽专用) 5C + (n-1)*50
    DWORD_PTR offset3 = SLOT_OFFSET3_BASE + (nSlot - 1) * SLOT_OFFSET_STEP;
    DWORD_PTR finalAddr = ptr3 + offset3;

    AddLog(_T("[卡槽%d] 最终地址: 0x%08X + 0x%X = 0x%08X"),
        nSlot, ptr3, offset3, finalAddr);

    return finalAddr;
}

// 读取卡槽值
DWORD CPlantsCEDlg::ReadSlotValue(int nSlot)
{
    DWORD_PTR dwAddress = GetSlotAddress(nSlot);
    if (dwAddress == 0)
    {
        return 0;
    }

    DWORD dwValue = 0;
    SIZE_T bytesRead = 0;

    if (ReadProcessMemory(m_hProcess, (LPCVOID)dwAddress, &dwValue, sizeof(DWORD), &bytesRead))
    {
        if (bytesRead == sizeof(DWORD))
        {
            return dwValue;
        }
    }

    return 0;
}

// 写入卡槽值
BOOL CPlantsCEDlg::WriteSlotValue(int nSlot, DWORD dwValue)
{
    DWORD_PTR dwAddress = GetSlotAddress(nSlot);
    if (dwAddress == 0)
    {
        AddLog(_T("[卡槽%d] 无法获取地址"), nSlot);
        return FALSE;
    }

    // 修改内存保护属性
    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)dwAddress, sizeof(DWORD),
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    // 写入新值
    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)dwAddress, &dwValue, sizeof(DWORD), &bytesWritten);

    // 恢复内存保护属性
    VirtualProtectEx(m_hProcess, (LPVOID)dwAddress, sizeof(DWORD), dwOldProtect, &dwOldProtect);

    return (bResult && bytesWritten == sizeof(DWORD));
}

// 加载卡槽值到下拉框
void CPlantsCEDlg::LoadSlotValue(int nSlot)
{
    if (!m_bAttached || !m_hProcess)
    {
        return;
    }

    DWORD dwValue = ReadSlotValue(nSlot);

    // 保存当前值
    m_arrSlotCurrentValue[nSlot] = dwValue;

    // 更新下拉框选中项
    CComboBox* pCombo = NULL;
    switch (nSlot)
    {
    case 1: pCombo = &m_comboSlot1; break;
    case 2: pCombo = &m_comboSlot2; break;
    case 3: pCombo = &m_comboSlot3; break;
    case 4: pCombo = &m_comboSlot4; break;
    case 5: pCombo = &m_comboSlot5; break;
    case 6: pCombo = &m_comboSlot6; break;
    case 7: pCombo = &m_comboSlot7; break;
    case 8: pCombo = &m_comboSlot8; break;
    case 9: pCombo = &m_comboSlot9; break;
    case 10: pCombo = &m_comboSlot10; break;
    default: return;
    }

    if (dwValue >= 0 && dwValue <= 47)
    {
        pCombo->SetCurSel((int)dwValue);
        AddLog(_T("[卡槽%d] 当前植物: %s"), nSlot, m_arrPlantNames[dwValue]);
    }
    else
    {
        pCombo->SetCurSel(-1);
        AddLog(_T("[卡槽%d] 当前值: %d (未知)"), nSlot, dwValue);
    }
}

// 卡槽选择变化处理
void CPlantsCEDlg::OnSlotSelChange(int nSlot)
{
    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("[卡槽%d] 错误: 请先附加进程"), nSlot);

        // 恢复之前的选择
        CComboBox* pCombo = NULL;
        switch (nSlot)
        {
        case 1: pCombo = &m_comboSlot1; break;
        case 2: pCombo = &m_comboSlot2; break;
        case 3: pCombo = &m_comboSlot3; break;
        case 4: pCombo = &m_comboSlot4; break;
        case 5: pCombo = &m_comboSlot5; break;
        case 6: pCombo = &m_comboSlot6; break;
        case 7: pCombo = &m_comboSlot7; break;
        case 8: pCombo = &m_comboSlot8; break;
        case 9: pCombo = &m_comboSlot9; break;
        case 10: pCombo = &m_comboSlot10; break;
        default: return;
        }

        if (m_arrSlotCurrentValue[nSlot] <= 47)
        {
            pCombo->SetCurSel((int)m_arrSlotCurrentValue[nSlot]);
        }
        return;
    }

    CComboBox* pCombo = NULL;
    switch (nSlot)
    {
    case 1: pCombo = &m_comboSlot1; break;
    case 2: pCombo = &m_comboSlot2; break;
    case 3: pCombo = &m_comboSlot3; break;
    case 4: pCombo = &m_comboSlot4; break;
    case 5: pCombo = &m_comboSlot5; break;
    case 6: pCombo = &m_comboSlot6; break;
    case 7: pCombo = &m_comboSlot7; break;
    case 8: pCombo = &m_comboSlot8; break;
    case 9: pCombo = &m_comboSlot9; break;
    case 10: pCombo = &m_comboSlot10; break;
    default: return;
    }

    int nSel = pCombo->GetCurSel();
    if (nSel == CB_ERR)
    {
        return;
    }

    // 检查是否与当前值相同
    if ((DWORD)nSel == m_arrSlotCurrentValue[nSlot])
    {
        // 相同，不写入
        AddLog(_T("[卡槽%d] 未修改 (当前已是 %s)"), nSlot, m_arrPlantNames[nSel]);
        return;
    }

    // 不同，写入新值
    AddLog(_T("[卡槽%d] 修改: %s -> %s"),
        nSlot,
        (m_arrSlotCurrentValue[nSlot] <= 47) ? m_arrPlantNames[m_arrSlotCurrentValue[nSlot]] : _T("未知"),
        m_arrPlantNames[nSel]);

    if (WriteSlotValue(nSlot, (DWORD)nSel))
    {
        m_arrSlotCurrentValue[nSlot] = (DWORD)nSel;
        AddLog(_T("[卡槽%d] 修改成功！"), nSlot);
    }
    else
    {
        AddLog(_T("[卡槽%d] 修改失败！"), nSlot);
        // 恢复之前的选择
        if (m_arrSlotCurrentValue[nSlot] <= 47)
        {
            pCombo->SetCurSel((int)m_arrSlotCurrentValue[nSlot]);
        }
    }
}

// 加载所有卡槽值
void CPlantsCEDlg::LoadAllSlots()
{
    if (!m_bAttached || !m_hProcess)
    {
        return;
    }

    AddLog(_T("[卡槽] 正在加载所有卡槽值..."));

    for (int i = 1; i <= 10; i++)
    {
        LoadSlotValue(i);
    }

    AddLog(_T("[卡槽] 加载完成"));
}

void CPlantsCEDlg::OnCbnSelchangeSlotsel1()
{
    // TODO: 在此添加控件通知处理程序代码
    OnSlotSelChange(1);
}


void CPlantsCEDlg::OnCbnSelchangeSlotsel2()
{
    // TODO: 在此添加控件通知处理程序代码
    OnSlotSelChange(2);
}


void CPlantsCEDlg::OnCbnSelchangeSlotsel3()
{
    // TODO: 在此添加控件通知处理程序代码
    OnSlotSelChange(3);
}


void CPlantsCEDlg::OnCbnSelchangeSlotsel4()
{
    // TODO: 在此添加控件通知处理程序代码
    OnSlotSelChange(4);
}


void CPlantsCEDlg::OnCbnSelchangeSlotsel5()
{
    // TODO: 在此添加控件通知处理程序代码
    OnSlotSelChange(5);
}


void CPlantsCEDlg::OnCbnSelchangeSlotsel6()
{
    // TODO: 在此添加控件通知处理程序代码
    OnSlotSelChange(6);
}


void CPlantsCEDlg::OnCbnSelchangeSlotsel7()
{
    // TODO: 在此添加控件通知处理程序代码
    OnSlotSelChange(7);
}


void CPlantsCEDlg::OnCbnSelchangeSlotsel8()
{
    // TODO: 在此添加控件通知处理程序代码
    OnSlotSelChange(8);
}


void CPlantsCEDlg::OnCbnSelchangeSlotsel9()
{
    // TODO: 在此添加控件通知处理程序代码
    OnSlotSelChange(9);
}


void CPlantsCEDlg::OnCbnSelchangeSlotsel10()
{
    // TODO: 在此添加控件通知处理程序代码
    OnSlotSelChange(10);
}


// 原始字节码
// 爆炸1原始: 7F 3E F7 D9 3B C1 (jg + neg + cmp)
const BYTE EXPLODE1_ORIGINAL_BYTES[] = { 0x7F, 0x3E, 0xF7, 0xD9, 0x3B, 0xC1 };

// 爆炸2原始: 7C 38 8B 4D 18 (jl + mov)
const BYTE EXPLODE2_ORIGINAL_BYTES[] = { 0x7C, 0x38, 0x8B, 0x4D, 0x18 };

// 爆炸3原始: 74 1E 80 7D 20 00 (je + cmp)
const BYTE EXPLODE3_ORIGINAL_BYTES[] = { 0x74, 0x1E, 0x80, 0x7D, 0x20, 0x00 };

// 自定义代码
// 爆炸1自定义: nop; neg ecx; cmp eax,ecx
const BYTE EXPLODE1_NEW_CODE[] = {
    0x90,                               // nop
    0xF7, 0xD9,                         // neg ecx
    0x3B, 0xC1,                         // cmp eax, ecx
    0xE9                                // jmp
};

// 爆炸2自定义: nop; mov ecx,[ebp+18]
const BYTE EXPLODE2_NEW_CODE[] = {
    0x90,                               // nop
    0x8B, 0x4D, 0x18,                   // mov ecx, [ebp+18]
    0xE9                                // jmp
};

// 爆炸3自定义: nop; cmp byte ptr [ebp+20],00
const BYTE EXPLODE3_NEW_CODE[] = {
    0x90,                               // nop
    0x80, 0x7D, 0x20, 0x00,             // cmp byte ptr [ebp+20], 00
    0xE9                                // jmp
};

// ==================== 全屏爆炸1 ====================

BOOL CPlantsCEDlg::AllocateMemoryForExplode1()
{
    if (m_bExplode1MemoryAllocated && m_dwExplode1Allocated)
    {
        return TRUE;
    }

    m_dwExplode1Allocated = (DWORD_PTR)VirtualAllocEx(
        m_hProcess, NULL, 2048, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if (!m_dwExplode1Allocated)
    {
        AddLog(_T("[全屏爆炸1] 分配内存失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    AddLog(_T("[全屏爆炸1] 内存分配成功: 0x%08X"), m_dwExplode1Allocated);
    m_bExplode1MemoryAllocated = TRUE;
    return TRUE;
}

BOOL CPlantsCEDlg::WriteCustomCodeForExplode1()
{
    if (!m_bExplode1MemoryAllocated) return FALSE;

    // 计算返回地址
    DWORD_PTR returnAddress = m_dwExplode1Address + 6;  // 原指令6字节
    DWORD_PTR jmpPosition = m_dwExplode1Allocated + sizeof(EXPLODE1_NEW_CODE);
    DWORD jmpOffset = (DWORD)(returnAddress - (jmpPosition + 5));

    const size_t codeSize = sizeof(EXPLODE1_NEW_CODE) + 4;
    BYTE* fullCode = new BYTE[codeSize];

    memcpy(fullCode, EXPLODE1_NEW_CODE, sizeof(EXPLODE1_NEW_CODE));

    size_t jmpPos = sizeof(EXPLODE1_NEW_CODE) - 1;
    fullCode[jmpPos] = 0xE9;
    fullCode[sizeof(EXPLODE1_NEW_CODE)] = (BYTE)(jmpOffset & 0xFF);
    fullCode[sizeof(EXPLODE1_NEW_CODE) + 1] = (BYTE)((jmpOffset >> 8) & 0xFF);
    fullCode[sizeof(EXPLODE1_NEW_CODE) + 2] = (BYTE)((jmpOffset >> 16) & 0xFF);
    fullCode[sizeof(EXPLODE1_NEW_CODE) + 3] = (BYTE)((jmpOffset >> 24) & 0xFF);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwExplode1Allocated,
        fullCode, codeSize, &bytesWritten);

    delete[] fullCode;

    if (bResult && bytesWritten == codeSize)
    {
        AddLog(_T("[全屏爆炸1] 自定义代码写入成功"));
        return TRUE;
    }
    return FALSE;
}

BOOL CPlantsCEDlg::InstallHookForExplode1()
{
    DWORD jmpOffset = (DWORD)(m_dwExplode1Allocated - (m_dwExplode1Address + 5));
    BYTE jmpInstruction[6] = { 0xE9 };
    jmpInstruction[1] = (BYTE)(jmpOffset & 0xFF);
    jmpInstruction[2] = (BYTE)((jmpOffset >> 8) & 0xFF);
    jmpInstruction[3] = (BYTE)((jmpOffset >> 16) & 0xFF);
    jmpInstruction[4] = (BYTE)((jmpOffset >> 24) & 0xFF);

    jmpInstruction[5] = 0x90;
    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwExplode1Address, 6,
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwExplode1Address,
        jmpInstruction, 6, &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwExplode1Address, 5, dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == 6)
    {
        AddLog(_T("[全屏爆炸1] Hook安装成功"));
        return TRUE;
    }
    return FALSE;
}

BOOL CPlantsCEDlg::EnableExplode1()
{
    if (m_dwExplode1Address == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
        {
            m_dwExplode1Address = dwModuleBase + EXPLODE1_OFFSET;
        }
        else return FALSE;
    }

    if (!AllocateMemoryForExplode1()) return FALSE;
    if (!WriteCustomCodeForExplode1()) { FreeExplodeMemory(); return FALSE; }
    if (!InstallHookForExplode1()) { FreeExplodeMemory(); return FALSE; }

    return TRUE;
}

BOOL CPlantsCEDlg::DisableExplode1()
{
    if (m_dwExplode1Address == 0) return FALSE;

    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwExplode1Address, sizeof(EXPLODE1_ORIGINAL_BYTES),
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwExplode1Address,
        EXPLODE1_ORIGINAL_BYTES, sizeof(EXPLODE1_ORIGINAL_BYTES), &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwExplode1Address, sizeof(EXPLODE1_ORIGINAL_BYTES),
        dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == sizeof(EXPLODE1_ORIGINAL_BYTES))
    {
        AddLog(_T("[全屏爆炸1] 恢复成功"));
        return TRUE;
    }
    return FALSE;
}

// ==================== 全屏爆炸2 ====================

BOOL CPlantsCEDlg::AllocateMemoryForExplode2()
{
    if (m_bExplode2MemoryAllocated && m_dwExplode2Allocated) return TRUE;

    m_dwExplode2Allocated = (DWORD_PTR)VirtualAllocEx(
        m_hProcess, NULL, 2048, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if (!m_dwExplode2Allocated)
    {
        AddLog(_T("[全屏爆炸2] 分配内存失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    AddLog(_T("[全屏爆炸2] 内存分配成功: 0x%08X"), m_dwExplode2Allocated);
    m_bExplode2MemoryAllocated = TRUE;
    return TRUE;
}

BOOL CPlantsCEDlg::WriteCustomCodeForExplode2()
{
    if (!m_bExplode2MemoryAllocated) return FALSE;

    DWORD_PTR returnAddress = m_dwExplode2Address + 5;  // 原指令5字节
    DWORD_PTR jmpPosition = m_dwExplode2Allocated + sizeof(EXPLODE2_NEW_CODE);
    DWORD jmpOffset = (DWORD)(returnAddress - (jmpPosition + 4));

    const size_t codeSize = sizeof(EXPLODE2_NEW_CODE) + 4;
    BYTE* fullCode = new BYTE[codeSize];

    memcpy(fullCode, EXPLODE2_NEW_CODE, sizeof(EXPLODE2_NEW_CODE));

    size_t jmpPos = sizeof(EXPLODE2_NEW_CODE) - 1;
    fullCode[jmpPos] = 0xE9;
    fullCode[sizeof(EXPLODE2_NEW_CODE)] = (BYTE)(jmpOffset & 0xFF);
    fullCode[sizeof(EXPLODE2_NEW_CODE) + 1] = (BYTE)((jmpOffset >> 8) & 0xFF);
    fullCode[sizeof(EXPLODE2_NEW_CODE) + 2] = (BYTE)((jmpOffset >> 16) & 0xFF);
    fullCode[sizeof(EXPLODE2_NEW_CODE) + 3] = (BYTE)((jmpOffset >> 24) & 0xFF);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwExplode2Allocated,
        fullCode, codeSize, &bytesWritten);

    delete[] fullCode;
    return (bResult && bytesWritten == codeSize);
}

BOOL CPlantsCEDlg::InstallHookForExplode2()
{
    DWORD jmpOffset = (DWORD)(m_dwExplode2Allocated - (m_dwExplode2Address + 5));
    BYTE jmpInstruction[5] = { 0xE9 };
    jmpInstruction[1] = (BYTE)(jmpOffset & 0xFF);
    jmpInstruction[2] = (BYTE)((jmpOffset >> 8) & 0xFF);
    jmpInstruction[3] = (BYTE)((jmpOffset >> 16) & 0xFF);
    jmpInstruction[4] = (BYTE)((jmpOffset >> 24) & 0xFF);

    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwExplode2Address, 5,
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwExplode2Address,
        jmpInstruction, 5, &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwExplode2Address, 5, dwOldProtect, &dwOldProtect);

    return (bResult && bytesWritten == 5);
}

BOOL CPlantsCEDlg::EnableExplode2()
{
    if (m_dwExplode2Address == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase) m_dwExplode2Address = dwModuleBase + EXPLODE2_OFFSET;
        else return FALSE;
    }

    if (!AllocateMemoryForExplode2()) return FALSE;
    if (!WriteCustomCodeForExplode2()) { FreeExplodeMemory(); return FALSE; }
    if (!InstallHookForExplode2()) { FreeExplodeMemory(); return FALSE; }

    AddLog(_T("[全屏爆炸2] 启用成功"));
    return TRUE;
}

BOOL CPlantsCEDlg::DisableExplode2()
{
    if (m_dwExplode2Address == 0) return FALSE;

    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwExplode2Address, sizeof(EXPLODE2_ORIGINAL_BYTES),
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwExplode2Address,
        EXPLODE2_ORIGINAL_BYTES, sizeof(EXPLODE2_ORIGINAL_BYTES), &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwExplode2Address, sizeof(EXPLODE2_ORIGINAL_BYTES),
        dwOldProtect, &dwOldProtect);

    return (bResult && bytesWritten == sizeof(EXPLODE2_ORIGINAL_BYTES));
}

// ==================== 全屏爆炸3 ====================

BOOL CPlantsCEDlg::AllocateMemoryForExplode3()
{
    if (m_bExplode3MemoryAllocated && m_dwExplode3Allocated) return TRUE;

    m_dwExplode3Allocated = (DWORD_PTR)VirtualAllocEx(
        m_hProcess, NULL, 2048, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if (!m_dwExplode3Allocated)
    {
        AddLog(_T("[全屏爆炸3] 分配内存失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    AddLog(_T("[全屏爆炸3] 内存分配成功: 0x%08X"), m_dwExplode3Allocated);
    m_bExplode3MemoryAllocated = TRUE;
    return TRUE;
}

BOOL CPlantsCEDlg::WriteCustomCodeForExplode3()
{
    if (!m_bExplode3MemoryAllocated) return FALSE;

    DWORD_PTR returnAddress = m_dwExplode3Address + 6;  // 原指令6字节
    DWORD_PTR jmpPosition = m_dwExplode3Allocated + sizeof(EXPLODE3_NEW_CODE);
    DWORD jmpOffset = (DWORD)(returnAddress - (jmpPosition + 5));

    const size_t codeSize = sizeof(EXPLODE3_NEW_CODE) + 4;
    BYTE* fullCode = new BYTE[codeSize];

    memcpy(fullCode, EXPLODE3_NEW_CODE, sizeof(EXPLODE3_NEW_CODE));

    size_t jmpPos = sizeof(EXPLODE3_NEW_CODE) - 1;
    fullCode[jmpPos] = 0xE9;
    fullCode[sizeof(EXPLODE3_NEW_CODE)] = (BYTE)(jmpOffset & 0xFF);
    fullCode[sizeof(EXPLODE3_NEW_CODE) + 1] = (BYTE)((jmpOffset >> 8) & 0xFF);
    fullCode[sizeof(EXPLODE3_NEW_CODE) + 2] = (BYTE)((jmpOffset >> 16) & 0xFF);
    fullCode[sizeof(EXPLODE3_NEW_CODE) + 3] = (BYTE)((jmpOffset >> 24) & 0xFF);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwExplode3Allocated,
        fullCode, codeSize, &bytesWritten);

    delete[] fullCode;
    return (bResult && bytesWritten == codeSize);
}

BOOL CPlantsCEDlg::InstallHookForExplode3()
{
    DWORD jmpOffset = (DWORD)(m_dwExplode3Allocated - (m_dwExplode3Address + 5));
    BYTE jmpInstruction[6] = { 0xE9 };
    jmpInstruction[1] = (BYTE)(jmpOffset & 0xFF);
    jmpInstruction[2] = (BYTE)((jmpOffset >> 8) & 0xFF);
    jmpInstruction[3] = (BYTE)((jmpOffset >> 16) & 0xFF);
    jmpInstruction[4] = (BYTE)((jmpOffset >> 24) & 0xFF);
    jmpInstruction[5] = 0x90;

    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwExplode3Address, 6,
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwExplode3Address,
        jmpInstruction, 6, &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwExplode3Address, 5, dwOldProtect, &dwOldProtect);

    return (bResult && bytesWritten == 6);
}

BOOL CPlantsCEDlg::EnableExplode3()
{
    if (m_dwExplode3Address == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase) m_dwExplode3Address = dwModuleBase + EXPLODE3_OFFSET;
        else return FALSE;
    }

    if (!AllocateMemoryForExplode3()) return FALSE;
    if (!WriteCustomCodeForExplode3()) { FreeExplodeMemory(); return FALSE; }
    if (!InstallHookForExplode3()) { FreeExplodeMemory(); return FALSE; }

    AddLog(_T("[全屏爆炸3] 启用成功"));
    return TRUE;
}

BOOL CPlantsCEDlg::DisableExplode3()
{
    if (m_dwExplode3Address == 0) return FALSE;

    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwExplode3Address, sizeof(EXPLODE3_ORIGINAL_BYTES),
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwExplode3Address,
        EXPLODE3_ORIGINAL_BYTES, sizeof(EXPLODE3_ORIGINAL_BYTES), &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwExplode3Address, sizeof(EXPLODE3_ORIGINAL_BYTES),
        dwOldProtect, &dwOldProtect);

    return (bResult && bytesWritten == sizeof(EXPLODE3_ORIGINAL_BYTES));
}

// 释放所有内存
void CPlantsCEDlg::FreeExplodeMemory()
{
    if (m_bExplode1MemoryAllocated && m_dwExplode1Allocated)
    {
        VirtualFreeEx(m_hProcess, (LPVOID)m_dwExplode1Allocated, 0, MEM_RELEASE);
        m_bExplode1MemoryAllocated = FALSE;
        m_dwExplode1Allocated = 0;
    }
    if (m_bExplode2MemoryAllocated && m_dwExplode2Allocated)
    {
        VirtualFreeEx(m_hProcess, (LPVOID)m_dwExplode2Allocated, 0, MEM_RELEASE);
        m_bExplode2MemoryAllocated = FALSE;
        m_dwExplode2Allocated = 0;
    }
    if (m_bExplode3MemoryAllocated && m_dwExplode3Allocated)
    {
        VirtualFreeEx(m_hProcess, (LPVOID)m_dwExplode3Allocated, 0, MEM_RELEASE);
        m_bExplode3MemoryAllocated = FALSE;
        m_dwExplode3Allocated = 0;
    }
}

// 启用全屏爆炸（三处全部启用）
void CPlantsCEDlg::EnableFullScreenExplode()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[全屏爆炸] 错误: 未附加进程"));
        return;
    }

    if (m_bFullScreenExplodeEnabled)
    {
        AddLog(_T("[全屏爆炸] 已经启用"));
        return;
    }

    AddLog(_T("[全屏爆炸] 正在启用（三处代码注入）..."));

    BOOL bSuccess1 = EnableExplode1();
    BOOL bSuccess2 = EnableExplode2();
    BOOL bSuccess3 = EnableExplode3();

    if (bSuccess1 && bSuccess2 && bSuccess3)
    {
        m_bFullScreenExplodeEnabled = TRUE;
        AddLog(_T("[全屏爆炸] 成功启用！场上僵尸将会被消灭"));
    }
    else
    {
        AddLog(_T("[全屏爆炸] 启用失败，正在回滚..."));
        DisableExplode1();
        DisableExplode2();
        DisableExplode3();
        FreeExplodeMemory();
    }
}

// 禁用全屏爆炸（三处全部禁用）
void CPlantsCEDlg::DisableFullScreenExplode()
{
    if (!m_bFullScreenExplodeEnabled)
    {
        AddLog(_T("[全屏爆炸] 已经禁用"));
        return;
    }

    AddLog(_T("[全屏爆炸] 正在禁用..."));

    DisableExplode1();
    DisableExplode2();
    DisableExplode3();
    FreeExplodeMemory();

    m_bFullScreenExplodeEnabled = FALSE;
    AddLog(_T("[全屏爆炸] 已禁用"));
}

void CPlantsCEDlg::OnBnClickedFullscreenexplosion()
{
    // TODO: 在此添加控件通知处理程序代码
    int nCheck = m_checkFullScreenExplode.GetCheck();

    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("[全屏爆炸] 错误: 请先附加进程"));
        m_checkFullScreenExplode.SetCheck(m_bFullScreenExplodeEnabled ? BST_CHECKED : BST_UNCHECKED);
        return;
    }

    if (nCheck == BST_CHECKED)
    {
        EnableFullScreenExplode();
    }
    else
    {
        DisableFullScreenExplode();
    }

    // 保存配置
    SaveConfigToIni();
}

// 原始字节码: add dword ptr [edi+0000559C],-01
const BYTE ZOMBIES_ALL_OUT_ORIGINAL_BYTES[] = {
    0x83, 0x87, 0x9C, 0x55, 0x00, 0x00, 0xFF
};

// 自定义代码: mov [edi+0000559C], 0
const BYTE ZOMBIES_ALL_OUT_NEW_CODE[] = {
    0xC7, 0x87, 0x9C, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // mov [edi+0000559C], 00000000
    0xE9                                                           // jmp
};

// ==================== 僵尸全部出动功能 ====================

// 分配内存
BOOL CPlantsCEDlg::AllocateMemoryForZombiesAllOut()
{
    if (m_bZombiesAllOutMemoryAllocated && m_dwZombiesAllOutAllocated)
    {
        return TRUE;
    }

    AddLog(_T("[僵尸全部出动] 正在分配内存..."));

    m_dwZombiesAllOutAllocated = (DWORD_PTR)VirtualAllocEx(
        m_hProcess,
        NULL,
        2048,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE
    );

    if (!m_dwZombiesAllOutAllocated)
    {
        AddLog(_T("[僵尸全部出动] 分配内存失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    AddLog(_T("[僵尸全部出动] 内存分配成功: 0x%08X"), m_dwZombiesAllOutAllocated);
    m_bZombiesAllOutMemoryAllocated = TRUE;
    return TRUE;
}

// 写入自定义代码
BOOL CPlantsCEDlg::WriteCustomCodeForZombiesAllOut()
{
    if (!m_bZombiesAllOutMemoryAllocated)
        return FALSE;

    // 计算返回地址：原地址 + 7 (原始指令7字节)
    DWORD_PTR returnAddress = m_dwZombiesAllOutAddress + 7;

    // 计算JMP偏移
    DWORD_PTR jmpPosition = m_dwZombiesAllOutAllocated + sizeof(ZOMBIES_ALL_OUT_NEW_CODE);
    DWORD jmpOffset = (DWORD)(returnAddress - (jmpPosition + 4));

    const size_t codeSize = sizeof(ZOMBIES_ALL_OUT_NEW_CODE) + 4;
    BYTE* fullCode = new BYTE[codeSize];

    memcpy(fullCode, ZOMBIES_ALL_OUT_NEW_CODE, sizeof(ZOMBIES_ALL_OUT_NEW_CODE));

    // 设置JMP偏移
    size_t jmpPos = sizeof(ZOMBIES_ALL_OUT_NEW_CODE) - 1;
    fullCode[jmpPos] = 0xE9;
    fullCode[sizeof(ZOMBIES_ALL_OUT_NEW_CODE)] = (BYTE)(jmpOffset & 0xFF);
    fullCode[sizeof(ZOMBIES_ALL_OUT_NEW_CODE) + 1] = (BYTE)((jmpOffset >> 8) & 0xFF);
    fullCode[sizeof(ZOMBIES_ALL_OUT_NEW_CODE) + 2] = (BYTE)((jmpOffset >> 16) & 0xFF);
    fullCode[sizeof(ZOMBIES_ALL_OUT_NEW_CODE) + 3] = (BYTE)((jmpOffset >> 24) & 0xFF);

    AddLog(_T("[僵尸全部出动] 分配地址: 0x%08X"), m_dwZombiesAllOutAllocated);
    AddLog(_T("[僵尸全部出动] 目标地址: 0x%08X"), m_dwZombiesAllOutAddress);
    AddLog(_T("[僵尸全部出动] 返回地址: 0x%08X"), returnAddress);
    AddLog(_T("[僵尸全部出动] JMP偏移: 0x%08X"), jmpOffset);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwZombiesAllOutAllocated,
        fullCode, codeSize, &bytesWritten);

    if (bResult && bytesWritten == codeSize)
    {
        CString strCode;
        for (size_t i = 0; i < codeSize; i++)
        {
            strCode.AppendFormat(_T("%02X "), fullCode[i]);
        }
        AddLog(_T("[僵尸全部出动] 写入代码: %s"), strCode);
        AddLog(_T("[僵尸全部出动] 自定义代码写入成功"));
    }
    else
    {
        AddLog(_T("[僵尸全部出动] 写入失败，错误码: %d"), GetLastError());
    }

    delete[] fullCode;
    return (bResult && bytesWritten == codeSize);
}

// 安装Hook
BOOL CPlantsCEDlg::InstallHookForZombiesAllOut()
{
    AddLog(_T("[僵尸全部出动] 正在安装Hook..."));

    // 计算JMP偏移：从目标地址跳转到分配的内存
    DWORD jmpOffset = (DWORD)(m_dwZombiesAllOutAllocated - (m_dwZombiesAllOutAddress + 5));

    BYTE jmpInstruction[5] = { 0xE9 };
    jmpInstruction[1] = (BYTE)(jmpOffset & 0xFF);
    jmpInstruction[2] = (BYTE)((jmpOffset >> 8) & 0xFF);
    jmpInstruction[3] = (BYTE)((jmpOffset >> 16) & 0xFF);
    jmpInstruction[4] = (BYTE)((jmpOffset >> 24) & 0xFF);

    AddLog(_T("[僵尸全部出动] JMP从 0x%08X 到 0x%08X"),
        m_dwZombiesAllOutAddress, m_dwZombiesAllOutAllocated);
    AddLog(_T("[僵尸全部出动] JMP偏移: 0x%08X"), jmpOffset);
    AddLog(_T("[僵尸全部出动] JMP指令: %02X %02X %02X %02X %02X"),
        jmpInstruction[0], jmpInstruction[1], jmpInstruction[2],
        jmpInstruction[3], jmpInstruction[4]);

    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwZombiesAllOutAddress, 5,
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwZombiesAllOutAddress,
        jmpInstruction, 5, &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwZombiesAllOutAddress, 5, dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == 5)
    {
        AddLog(_T("[僵尸全部出动] Hook安装成功！"));
        return TRUE;
    }
    else
    {
        AddLog(_T("[僵尸全部出动] Hook安装失败，错误码: %d"), GetLastError());
        return FALSE;
    }
}

// 释放内存
void CPlantsCEDlg::FreeZombiesAllOutMemory()
{
    if (m_bZombiesAllOutMemoryAllocated && m_dwZombiesAllOutAllocated)
    {
        VirtualFreeEx(m_hProcess, (LPVOID)m_dwZombiesAllOutAllocated, 0, MEM_RELEASE);
        AddLog(_T("[僵尸全部出动] 内存已释放"));
        m_bZombiesAllOutMemoryAllocated = FALSE;
        m_dwZombiesAllOutAllocated = 0;
    }
}

// 启用僵尸全部出动
void CPlantsCEDlg::EnableZombiesAllOut()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[僵尸全部出动] 错误: 未附加进程"));
        return;
    }

    if (m_bZombiesAllOutEnabled)
    {
        AddLog(_T("[僵尸全部出动] 已经启用"));
        return;
    }

    AddLog(_T("[僵尸全部出动] 正在启用..."));

    // 获取目标地址
    if (m_dwZombiesAllOutAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
        {
            m_dwZombiesAllOutAddress = dwModuleBase + ZOMBIES_ALL_OUT_OFFSET;
            AddLog(_T("[僵尸全部出动] 目标地址: 0x%08X"), m_dwZombiesAllOutAddress);
        }
        else
        {
            AddLog(_T("[僵尸全部出动] 无法获取模块基址"));
            return;
        }
    }

    // 读取当前字节码
    BYTE currentBytes[7] = { 0 };
    SIZE_T bytesRead = 0;
    if (ReadProcessMemory(m_hProcess, (LPCVOID)m_dwZombiesAllOutAddress, currentBytes, 7, &bytesRead))
    {
        AddLog(_T("[僵尸全部出动] 当前字节码: %02X %02X %02X %02X %02X %02X %02X"),
            currentBytes[0], currentBytes[1], currentBytes[2], currentBytes[3],
            currentBytes[4], currentBytes[5], currentBytes[6]);
    }

    // 1. 分配内存
    if (!AllocateMemoryForZombiesAllOut())
        return;

    // 2. 写入自定义代码
    if (!WriteCustomCodeForZombiesAllOut())
    {
        FreeZombiesAllOutMemory();
        return;
    }

    // 3. 安装Hook
    if (!InstallHookForZombiesAllOut())
    {
        FreeZombiesAllOutMemory();
        return;
    }

    m_bZombiesAllOutEnabled = TRUE;
    AddLog(_T("[僵尸全部出动] 成功启用！僵尸将全部出动"));
}

// 禁用僵尸全部出动
void CPlantsCEDlg::DisableZombiesAllOut()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[僵尸全部出动] 错误: 未附加进程"));
        return;
    }

    if (!m_bZombiesAllOutEnabled)
    {
        AddLog(_T("[僵尸全部出动] 已经禁用"));
        return;
    }

    AddLog(_T("[僵尸全部出动] 正在禁用..."));

    if (m_dwZombiesAllOutAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
            m_dwZombiesAllOutAddress = dwModuleBase + ZOMBIES_ALL_OUT_OFFSET;
    }

    // 恢复原始字节码
    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwZombiesAllOutAddress, sizeof(ZOMBIES_ALL_OUT_ORIGINAL_BYTES),
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwZombiesAllOutAddress,
        ZOMBIES_ALL_OUT_ORIGINAL_BYTES, sizeof(ZOMBIES_ALL_OUT_ORIGINAL_BYTES), &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwZombiesAllOutAddress, sizeof(ZOMBIES_ALL_OUT_ORIGINAL_BYTES),
        dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == sizeof(ZOMBIES_ALL_OUT_ORIGINAL_BYTES))
    {
        AddLog(_T("[僵尸全部出动] 成功禁用！已恢复正常"));
        m_bZombiesAllOutEnabled = FALSE;
        FreeZombiesAllOutMemory();
    }
    else
    {
        AddLog(_T("[僵尸全部出动] 恢复失败，错误码: %d"), GetLastError());
    }
}

void CPlantsCEDlg::OnBnClickedZombiesallgo()
{
    // TODO: 在此添加控件通知处理程序代码
    int nCheck = m_checkZombiesAllOut.GetCheck();

    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("[僵尸全部出动] 错误: 请先附加进程"));
        m_checkZombiesAllOut.SetCheck(m_bZombiesAllOutEnabled ? BST_CHECKED : BST_UNCHECKED);
        return;
    }

    if (nCheck == BST_CHECKED)
    {
        EnableZombiesAllOut();
    }
    else
    {
        DisableZombiesAllOut();
    }

    // 保存配置
    SaveConfigToIni();
}

// 原始字节码: jne PlantsVsZombies_后台.exe+60053
const BYTE POTATO_MINE_NO_CD_ORIGINAL_BYTES[] = {
    0x0F, 0x85, 0xFA, 0x01, 0x00, 0x00  // jne +0x1FA
};

// 自定义代码: nop (6个nop，因为原始指令6字节)
const BYTE POTATO_MINE_NO_CD_NEW_CODE[] = {
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90,  // 6个nop
    0xE9                                   // jmp
};

// ==================== 土豆地雷无CD功能 ====================

// 分配内存
BOOL CPlantsCEDlg::AllocateMemoryForPotatoMineNoCD()
{
    if (m_bPotatoMineNoCDMemoryAllocated && m_dwPotatoMineNoCDAllocated)
    {
        return TRUE;
    }

    AddLog(_T("[土豆地雷无CD] 正在分配内存..."));

    m_dwPotatoMineNoCDAllocated = (DWORD_PTR)VirtualAllocEx(
        m_hProcess,
        NULL,
        2048,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE
    );

    if (!m_dwPotatoMineNoCDAllocated)
    {
        AddLog(_T("[土豆地雷无CD] 分配内存失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    AddLog(_T("[土豆地雷无CD] 内存分配成功: 0x%08X"), m_dwPotatoMineNoCDAllocated);
    m_bPotatoMineNoCDMemoryAllocated = TRUE;
    return TRUE;
}

// 写入自定义代码
BOOL CPlantsCEDlg::WriteCustomCodeForPotatoMineNoCD()
{
    if (!m_bPotatoMineNoCDMemoryAllocated)
        return FALSE;

    // 计算返回地址：原地址 + 6 (原始指令6字节)
    DWORD_PTR returnAddress = m_dwPotatoMineNoCDAddress + 6;

    // 计算JMP偏移
    DWORD_PTR jmpPosition = m_dwPotatoMineNoCDAllocated + sizeof(POTATO_MINE_NO_CD_NEW_CODE);
    DWORD jmpOffset = (DWORD)(returnAddress - (jmpPosition + 4));

    const size_t codeSize = sizeof(POTATO_MINE_NO_CD_NEW_CODE) + 4;
    BYTE* fullCode = new BYTE[codeSize];

    memcpy(fullCode, POTATO_MINE_NO_CD_NEW_CODE, sizeof(POTATO_MINE_NO_CD_NEW_CODE));

    // 设置JMP偏移
    size_t jmpPos = sizeof(POTATO_MINE_NO_CD_NEW_CODE) - 1;
    fullCode[jmpPos] = 0xE9;
    fullCode[sizeof(POTATO_MINE_NO_CD_NEW_CODE)] = (BYTE)(jmpOffset & 0xFF);
    fullCode[sizeof(POTATO_MINE_NO_CD_NEW_CODE) + 1] = (BYTE)((jmpOffset >> 8) & 0xFF);
    fullCode[sizeof(POTATO_MINE_NO_CD_NEW_CODE) + 2] = (BYTE)((jmpOffset >> 16) & 0xFF);
    fullCode[sizeof(POTATO_MINE_NO_CD_NEW_CODE) + 3] = (BYTE)((jmpOffset >> 24) & 0xFF);

    AddLog(_T("[土豆地雷无CD] 分配地址: 0x%08X"), m_dwPotatoMineNoCDAllocated);
    AddLog(_T("[土豆地雷无CD] 目标地址: 0x%08X"), m_dwPotatoMineNoCDAddress);
    AddLog(_T("[土豆地雷无CD] 返回地址: 0x%08X"), returnAddress);
    AddLog(_T("[土豆地雷无CD] JMP偏移: 0x%08X"), jmpOffset);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwPotatoMineNoCDAllocated,
        fullCode, codeSize, &bytesWritten);

    if (bResult && bytesWritten == codeSize)
    {
        CString strCode;
        for (size_t i = 0; i < codeSize; i++)
        {
            strCode.AppendFormat(_T("%02X "), fullCode[i]);
        }
        AddLog(_T("[土豆地雷无CD] 写入代码: %s"), strCode);
        AddLog(_T("[土豆地雷无CD] 自定义代码写入成功"));
    }
    else
    {
        AddLog(_T("[土豆地雷无CD] 写入失败，错误码: %d"), GetLastError());
    }

    delete[] fullCode;
    return (bResult && bytesWritten == codeSize);
}

// 安装Hook
BOOL CPlantsCEDlg::InstallHookForPotatoMineNoCD()
{
    AddLog(_T("[土豆地雷无CD] 正在安装Hook..."));

    // 计算JMP偏移：从目标地址跳转到分配的内存
    DWORD jmpOffset = (DWORD)(m_dwPotatoMineNoCDAllocated - (m_dwPotatoMineNoCDAddress + 5));

    BYTE jmpInstruction[6] = { 0xE9 };
    jmpInstruction[1] = (BYTE)(jmpOffset & 0xFF);
    jmpInstruction[2] = (BYTE)((jmpOffset >> 8) & 0xFF);
    jmpInstruction[3] = (BYTE)((jmpOffset >> 16) & 0xFF);
    jmpInstruction[4] = (BYTE)((jmpOffset >> 24) & 0xFF);
    jmpInstruction[5] = 0x90;

    AddLog(_T("[土豆地雷无CD] JMP从 0x%08X 到 0x%08X"),
        m_dwPotatoMineNoCDAddress, m_dwPotatoMineNoCDAllocated);
    AddLog(_T("[土豆地雷无CD] JMP偏移: 0x%08X"), jmpOffset);
    AddLog(_T("[土豆地雷无CD] JMP指令: %02X %02X %02X %02X %02X"),
        jmpInstruction[0], jmpInstruction[1], jmpInstruction[2],
        jmpInstruction[3], jmpInstruction[4]);

    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwPotatoMineNoCDAddress, 6,
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwPotatoMineNoCDAddress,
        jmpInstruction, 6, &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwPotatoMineNoCDAddress, 6, dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == 6)
    {
        AddLog(_T("[土豆地雷无CD] Hook安装成功！"));
        return TRUE;
    }
    else
    {
        AddLog(_T("[土豆地雷无CD] Hook安装失败，错误码: %d"), GetLastError());
        return FALSE;
    }
}

// 释放内存
void CPlantsCEDlg::FreePotatoMineNoCDMemory()
{
    if (m_bPotatoMineNoCDMemoryAllocated && m_dwPotatoMineNoCDAllocated)
    {
        VirtualFreeEx(m_hProcess, (LPVOID)m_dwPotatoMineNoCDAllocated, 0, MEM_RELEASE);
        AddLog(_T("[土豆地雷无CD] 内存已释放"));
        m_bPotatoMineNoCDMemoryAllocated = FALSE;
        m_dwPotatoMineNoCDAllocated = 0;
    }
}

// 启用土豆地雷无CD
void CPlantsCEDlg::EnablePotatoMineNoCD()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[土豆地雷无CD] 错误: 未附加进程"));
        return;
    }

    if (m_bPotatoMineNoCDEnabled)
    {
        AddLog(_T("[土豆地雷无CD] 已经启用"));
        return;
    }

    AddLog(_T("[土豆地雷无CD] 正在启用..."));

    // 获取目标地址
    if (m_dwPotatoMineNoCDAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
        {
            m_dwPotatoMineNoCDAddress = dwModuleBase + POTATO_MINE_NO_CD_OFFSET;
            AddLog(_T("[土豆地雷无CD] 目标地址: 0x%08X"), m_dwPotatoMineNoCDAddress);
        }
        else
        {
            AddLog(_T("[土豆地雷无CD] 无法获取模块基址"));
            return;
        }
    }

    // 读取当前字节码
    BYTE currentBytes[6] = { 0 };
    SIZE_T bytesRead = 0;
    if (ReadProcessMemory(m_hProcess, (LPCVOID)m_dwPotatoMineNoCDAddress, currentBytes, 6, &bytesRead))
    {
        AddLog(_T("[土豆地雷无CD] 当前字节码: %02X %02X %02X %02X %02X %02X"),
            currentBytes[0], currentBytes[1], currentBytes[2],
            currentBytes[3], currentBytes[4], currentBytes[5]);
    }

    // 1. 分配内存
    if (!AllocateMemoryForPotatoMineNoCD())
        return;

    // 2. 写入自定义代码
    if (!WriteCustomCodeForPotatoMineNoCD())
    {
        FreePotatoMineNoCDMemory();
        return;
    }

    // 3. 安装Hook
    if (!InstallHookForPotatoMineNoCD())
    {
        FreePotatoMineNoCDMemory();
        return;
    }

    m_bPotatoMineNoCDEnabled = TRUE;
    AddLog(_T("[土豆地雷无CD] 成功启用！土豆地雷可以连续种植"));
}

// 禁用土豆地雷无CD
void CPlantsCEDlg::DisablePotatoMineNoCD()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[土豆地雷无CD] 错误: 未附加进程"));
        return;
    }

    if (!m_bPotatoMineNoCDEnabled)
    {
        AddLog(_T("[土豆地雷无CD] 已经禁用"));
        return;
    }

    AddLog(_T("[土豆地雷无CD] 正在禁用..."));

    if (m_dwPotatoMineNoCDAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
            m_dwPotatoMineNoCDAddress = dwModuleBase + POTATO_MINE_NO_CD_OFFSET;
    }

    // 恢复原始字节码
    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwPotatoMineNoCDAddress, sizeof(POTATO_MINE_NO_CD_ORIGINAL_BYTES),
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwPotatoMineNoCDAddress,
        POTATO_MINE_NO_CD_ORIGINAL_BYTES, sizeof(POTATO_MINE_NO_CD_ORIGINAL_BYTES), &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwPotatoMineNoCDAddress, sizeof(POTATO_MINE_NO_CD_ORIGINAL_BYTES),
        dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == sizeof(POTATO_MINE_NO_CD_ORIGINAL_BYTES))
    {
        AddLog(_T("[土豆地雷无CD] 成功禁用！已恢复正常CD"));
        m_bPotatoMineNoCDEnabled = FALSE;
        FreePotatoMineNoCDMemory();
    }
    else
    {
        AddLog(_T("[土豆地雷无CD] 恢复失败，错误码: %d"), GetLastError());
    }
}


void CPlantsCEDlg::OnBnClickedPotatominenocd()
{
    // TODO: 在此添加控件通知处理程序代码
    int nCheck = m_checkPotatoMineNoCD.GetCheck();

    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("[土豆地雷无CD] 错误: 请先附加进程"));
        m_checkPotatoMineNoCD.SetCheck(m_bPotatoMineNoCDEnabled ? BST_CHECKED : BST_UNCHECKED);
        return;
    }

    if (nCheck == BST_CHECKED)
    {
        EnablePotatoMineNoCD();
    }
    else
    {
        DisablePotatoMineNoCD();
    }

    // 保存配置
    SaveConfigToIni();
}

// 原始字节码: jne PlantsVsZombies_后台.exe+615C6; push 14; push esi (5字节)
const BYTE CHOMPER_NO_CD_ORIGINAL_BYTES[] = {
    0x75, 0x5F,        // jne +0x5F
    0x6A, 0x14,        // push 0x14
    0x56               // push esi
};

// 自定义代码: nop; push 14; push esi (5字节)
const BYTE CHOMPER_NO_CD_NEW_CODE[] = {
    0x90,              // nop (替换jne)
    0x6A, 0x14,        // push 0x14
    0x56,              // push esi
    0xE9               // jmp
};

// ==================== 食人花无CD功能 ====================

// 分配内存
BOOL CPlantsCEDlg::AllocateMemoryForChomperNoCD()
{
    if (m_bChomperNoCDMemoryAllocated && m_dwChomperNoCDAllocated)
    {
        return TRUE;
    }

    AddLog(_T("[食人花无CD] 正在分配内存..."));

    m_dwChomperNoCDAllocated = (DWORD_PTR)VirtualAllocEx(
        m_hProcess,
        NULL,
        2048,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE
    );

    if (!m_dwChomperNoCDAllocated)
    {
        AddLog(_T("[食人花无CD] 分配内存失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    AddLog(_T("[食人花无CD] 内存分配成功: 0x%08X"), m_dwChomperNoCDAllocated);
    m_bChomperNoCDMemoryAllocated = TRUE;
    return TRUE;
}

// 写入自定义代码
BOOL CPlantsCEDlg::WriteCustomCodeForChomperNoCD()
{
    if (!m_bChomperNoCDMemoryAllocated)
        return FALSE;

    // 计算返回地址：原地址 + 5 (原始指令5字节)
    DWORD_PTR returnAddress = m_dwChomperNoCDAddress + 5;

    // 计算JMP位置和偏移
    DWORD_PTR jmpPosition = m_dwChomperNoCDAllocated + sizeof(CHOMPER_NO_CD_NEW_CODE);
    // 偏移计算：JMP指令后跟4字节偏移
    DWORD jmpOffset = (DWORD)(returnAddress - (jmpPosition + 4));

    const size_t codeSize = sizeof(CHOMPER_NO_CD_NEW_CODE) + 4;
    BYTE* fullCode = new BYTE[codeSize];

    memcpy(fullCode, CHOMPER_NO_CD_NEW_CODE, sizeof(CHOMPER_NO_CD_NEW_CODE));

    // 设置JMP偏移
    size_t jmpPos = sizeof(CHOMPER_NO_CD_NEW_CODE) - 1;
    fullCode[jmpPos] = 0xE9;
    fullCode[sizeof(CHOMPER_NO_CD_NEW_CODE)] = (BYTE)(jmpOffset & 0xFF);
    fullCode[sizeof(CHOMPER_NO_CD_NEW_CODE) + 1] = (BYTE)((jmpOffset >> 8) & 0xFF);
    fullCode[sizeof(CHOMPER_NO_CD_NEW_CODE) + 2] = (BYTE)((jmpOffset >> 16) & 0xFF);
    fullCode[sizeof(CHOMPER_NO_CD_NEW_CODE) + 3] = (BYTE)((jmpOffset >> 24) & 0xFF);

    AddLog(_T("[食人花无CD] 分配地址: 0x%08X"), m_dwChomperNoCDAllocated);
    AddLog(_T("[食人花无CD] 目标地址: 0x%08X"), m_dwChomperNoCDAddress);
    AddLog(_T("[食人花无CD] 返回地址: 0x%08X"), returnAddress);
    AddLog(_T("[食人花无CD] JMP位置: 0x%08X"), jmpPosition);
    AddLog(_T("[食人花无CD] JMP偏移: 0x%08X"), jmpOffset);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwChomperNoCDAllocated,
        fullCode, codeSize, &bytesWritten);

    if (bResult && bytesWritten == codeSize)
    {
        CString strCode;
        for (size_t i = 0; i < codeSize; i++)
        {
            strCode.AppendFormat(_T("%02X "), fullCode[i]);
        }
        AddLog(_T("[食人花无CD] 写入代码: %s"), strCode);
        AddLog(_T("[食人花无CD] 自定义代码写入成功"));
    }
    else
    {
        AddLog(_T("[食人花无CD] 写入失败，错误码: %d"), GetLastError());
    }

    delete[] fullCode;
    return (bResult && bytesWritten == codeSize);
}

// 安装Hook
BOOL CPlantsCEDlg::InstallHookForChomperNoCD()
{
    AddLog(_T("[食人花无CD] 正在安装Hook..."));

    // 原始指令5字节，JMP指令5字节，长度正好对齐，不需要NOP填充
    DWORD jmpOffset = (DWORD)(m_dwChomperNoCDAllocated - (m_dwChomperNoCDAddress + 5));

    // 5字节JMP指令
    BYTE jmpInstruction[5] = { 0xE9 };
    jmpInstruction[1] = (BYTE)(jmpOffset & 0xFF);
    jmpInstruction[2] = (BYTE)((jmpOffset >> 8) & 0xFF);
    jmpInstruction[3] = (BYTE)((jmpOffset >> 16) & 0xFF);
    jmpInstruction[4] = (BYTE)((jmpOffset >> 24) & 0xFF);

    AddLog(_T("[食人花无CD] JMP从 0x%08X 到 0x%08X"),
        m_dwChomperNoCDAddress, m_dwChomperNoCDAllocated);
    AddLog(_T("[食人花无CD] JMP偏移: 0x%08X"), jmpOffset);
    AddLog(_T("[食人花无CD] JMP指令: %02X %02X %02X %02X %02X"),
        jmpInstruction[0], jmpInstruction[1], jmpInstruction[2],
        jmpInstruction[3], jmpInstruction[4]);

    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwChomperNoCDAddress, 5,
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwChomperNoCDAddress,
        jmpInstruction, 5, &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwChomperNoCDAddress, 5, dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == 5)
    {
        AddLog(_T("[食人花无CD] Hook安装成功！"));
        return TRUE;
    }
    else
    {
        AddLog(_T("[食人花无CD] Hook安装失败，错误码: %d"), GetLastError());
        return FALSE;
    }
}

// 释放内存
void CPlantsCEDlg::FreeChomperNoCDMemory()
{
    if (m_bChomperNoCDMemoryAllocated && m_dwChomperNoCDAllocated)
    {
        VirtualFreeEx(m_hProcess, (LPVOID)m_dwChomperNoCDAllocated, 0, MEM_RELEASE);
        AddLog(_T("[食人花无CD] 内存已释放"));
        m_bChomperNoCDMemoryAllocated = FALSE;
        m_dwChomperNoCDAllocated = 0;
    }
}

// 启用食人花无CD
void CPlantsCEDlg::EnableChomperNoCD()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[食人花无CD] 错误: 未附加进程"));
        return;
    }

    if (m_bChomperNoCDEnabled)
    {
        AddLog(_T("[食人花无CD] 已经启用"));
        return;
    }

    AddLog(_T("[食人花无CD] 正在启用..."));

    // 获取目标地址
    if (m_dwChomperNoCDAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
        {
            m_dwChomperNoCDAddress = dwModuleBase + CHOMPER_NO_CD_OFFSET;
            AddLog(_T("[食人花无CD] 目标地址: 0x%08X"), m_dwChomperNoCDAddress);
        }
        else
        {
            AddLog(_T("[食人花无CD] 无法获取模块基址"));
            return;
        }
    }

    // 读取当前字节码
    BYTE currentBytes[5] = { 0 };
    SIZE_T bytesRead = 0;
    if (ReadProcessMemory(m_hProcess, (LPCVOID)m_dwChomperNoCDAddress, currentBytes, 5, &bytesRead))
    {
        AddLog(_T("[食人花无CD] 当前字节码: %02X %02X %02X %02X %02X"),
            currentBytes[0], currentBytes[1], currentBytes[2],
            currentBytes[3], currentBytes[4]);
    }

    // 1. 分配内存
    if (!AllocateMemoryForChomperNoCD())
        return;

    // 2. 写入自定义代码
    if (!WriteCustomCodeForChomperNoCD())
    {
        FreeChomperNoCDMemory();
        return;
    }

    // 3. 安装Hook
    if (!InstallHookForChomperNoCD())
    {
        FreeChomperNoCDMemory();
        return;
    }

    m_bChomperNoCDEnabled = TRUE;
    AddLog(_T("[食人花无CD] 成功启用！食人花可以连续吞噬僵尸"));
}

// 禁用食人花无CD
void CPlantsCEDlg::DisableChomperNoCD()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[食人花无CD] 错误: 未附加进程"));
        return;
    }

    if (!m_bChomperNoCDEnabled)
    {
        AddLog(_T("[食人花无CD] 已经禁用"));
        return;
    }

    AddLog(_T("[食人花无CD] 正在禁用..."));

    if (m_dwChomperNoCDAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
            m_dwChomperNoCDAddress = dwModuleBase + CHOMPER_NO_CD_OFFSET;
    }

    // 恢复原始字节码 (5字节)
    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwChomperNoCDAddress, sizeof(CHOMPER_NO_CD_ORIGINAL_BYTES),
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwChomperNoCDAddress,
        CHOMPER_NO_CD_ORIGINAL_BYTES, sizeof(CHOMPER_NO_CD_ORIGINAL_BYTES), &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwChomperNoCDAddress, sizeof(CHOMPER_NO_CD_ORIGINAL_BYTES),
        dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == sizeof(CHOMPER_NO_CD_ORIGINAL_BYTES))
    {
        AddLog(_T("[食人花无CD] 成功禁用！已恢复正常CD"));
        m_bChomperNoCDEnabled = FALSE;
        FreeChomperNoCDMemory();
    }
    else
    {
        AddLog(_T("[食人花无CD] 恢复失败，错误码: %d"), GetLastError());
    }
}

void CPlantsCEDlg::OnBnClickedEatzombiesnocd()
{
    // TODO: 在此添加控件通知处理程序代码
    int nCheck = m_checkChomperNoCD.GetCheck();

    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("[食人花无CD] 错误: 请先附加进程"));
        m_checkChomperNoCD.SetCheck(m_bChomperNoCDEnabled ? BST_CHECKED : BST_UNCHECKED);
        return;
    }

    if (nCheck == BST_CHECKED)
    {
        EnableChomperNoCD();
    }
    else
    {
        DisableChomperNoCD();
    }

    // 保存配置
    SaveConfigToIni();
}

// 原始字节码: add dword ptr [esi+40],-04; mov ecx,[esi+40] (7字节)
const BYTE PLANT_INFINITE_HP_ORIGINAL_BYTES[] = {
    0x83, 0x46, 0x40, 0xFC,  // add dword ptr [esi+40], -04
    0x8B, 0x4E, 0x40         // mov ecx, [esi+40]
};

// 自定义代码: add dword ptr [esi+40],0; mov ecx,[esi+40] (7字节)
// 将减血改为加0，实现无限血
const BYTE PLANT_INFINITE_HP_NEW_CODE[] = {
    0x83, 0x46, 0x40, 0x00,  // add dword ptr [esi+40], 0 (不减血)
    0x8B, 0x4E, 0x40,        // mov ecx, [esi+40]
    0xE9                     // jmp
};

// ==================== 植物无限血功能 ====================

// 分配内存
BOOL CPlantsCEDlg::AllocateMemoryForPlantInfiniteHP()
{
    if (m_bPlantInfiniteHPMemoryAllocated && m_dwPlantInfiniteHPAllocated)
    {
        return TRUE;
    }

    AddLog(_T("[植物无限血] 正在分配内存..."));

    m_dwPlantInfiniteHPAllocated = (DWORD_PTR)VirtualAllocEx(
        m_hProcess,
        NULL,
        2048,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE
    );

    if (!m_dwPlantInfiniteHPAllocated)
    {
        AddLog(_T("[植物无限血] 分配内存失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    AddLog(_T("[植物无限血] 内存分配成功: 0x%08X"), m_dwPlantInfiniteHPAllocated);
    m_bPlantInfiniteHPMemoryAllocated = TRUE;
    return TRUE;
}

// 写入自定义代码
BOOL CPlantsCEDlg::WriteCustomCodeForPlantInfiniteHP()
{
    if (!m_bPlantInfiniteHPMemoryAllocated)
        return FALSE;

    // 计算返回地址：原地址 + 7 (原始指令7字节)
    DWORD_PTR returnAddress = m_dwPlantInfiniteHPAddress + 7;

    // 计算JMP位置和偏移
    DWORD_PTR jmpPosition = m_dwPlantInfiniteHPAllocated + sizeof(PLANT_INFINITE_HP_NEW_CODE);
    // 偏移计算：JMP指令后跟4字节偏移
    DWORD jmpOffset = (DWORD)(returnAddress - (jmpPosition + 4));

    const size_t codeSize = sizeof(PLANT_INFINITE_HP_NEW_CODE) + 4;
    BYTE* fullCode = new BYTE[codeSize];

    memcpy(fullCode, PLANT_INFINITE_HP_NEW_CODE, sizeof(PLANT_INFINITE_HP_NEW_CODE));

    // 设置JMP偏移
    size_t jmpPos = sizeof(PLANT_INFINITE_HP_NEW_CODE) - 1;
    fullCode[jmpPos] = 0xE9;
    fullCode[sizeof(PLANT_INFINITE_HP_NEW_CODE)] = (BYTE)(jmpOffset & 0xFF);
    fullCode[sizeof(PLANT_INFINITE_HP_NEW_CODE) + 1] = (BYTE)((jmpOffset >> 8) & 0xFF);
    fullCode[sizeof(PLANT_INFINITE_HP_NEW_CODE) + 2] = (BYTE)((jmpOffset >> 16) & 0xFF);
    fullCode[sizeof(PLANT_INFINITE_HP_NEW_CODE) + 3] = (BYTE)((jmpOffset >> 24) & 0xFF);

    AddLog(_T("[植物无限血] 分配地址: 0x%08X"), m_dwPlantInfiniteHPAllocated);
    AddLog(_T("[植物无限血] 目标地址: 0x%08X"), m_dwPlantInfiniteHPAddress);
    AddLog(_T("[植物无限血] 返回地址: 0x%08X"), returnAddress);
    AddLog(_T("[植物无限血] JMP位置: 0x%08X"), jmpPosition);
    AddLog(_T("[植物无限血] JMP偏移: 0x%08X"), jmpOffset);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwPlantInfiniteHPAllocated,
        fullCode, codeSize, &bytesWritten);

    if (bResult && bytesWritten == codeSize)
    {
        CString strCode;
        for (size_t i = 0; i < codeSize; i++)
        {
            strCode.AppendFormat(_T("%02X "), fullCode[i]);
        }
        AddLog(_T("[植物无限血] 写入代码: %s"), strCode);
        AddLog(_T("[植物无限血] 自定义代码写入成功"));
    }
    else
    {
        AddLog(_T("[植物无限血] 写入失败，错误码: %d"), GetLastError());
    }

    delete[] fullCode;
    return (bResult && bytesWritten == codeSize);
}

// 安装Hook
BOOL CPlantsCEDlg::InstallHookForPlantInfiniteHP()
{
    AddLog(_T("[植物无限血] 正在安装Hook..."));

    // 原始指令7字节，JMP指令5字节，需要2个NOP填充保持7字节
    DWORD jmpOffset = (DWORD)(m_dwPlantInfiniteHPAllocated - (m_dwPlantInfiniteHPAddress + 5));

    // 7字节指令: JMP(5字节) + NOP(2字节)
    BYTE jmpInstruction[7] = { 0xE9 };
    jmpInstruction[1] = (BYTE)(jmpOffset & 0xFF);
    jmpInstruction[2] = (BYTE)((jmpOffset >> 8) & 0xFF);
    jmpInstruction[3] = (BYTE)((jmpOffset >> 16) & 0xFF);
    jmpInstruction[4] = (BYTE)((jmpOffset >> 24) & 0xFF);
    jmpInstruction[5] = 0x90;  // NOP填充
    jmpInstruction[6] = 0x90;  // NOP填充

    AddLog(_T("[植物无限血] JMP从 0x%08X 到 0x%08X"),
        m_dwPlantInfiniteHPAddress, m_dwPlantInfiniteHPAllocated);
    AddLog(_T("[植物无限血] JMP偏移: 0x%08X"), jmpOffset);
    AddLog(_T("[植物无限血] JMP指令: %02X %02X %02X %02X %02X %02X %02X"),
        jmpInstruction[0], jmpInstruction[1], jmpInstruction[2],
        jmpInstruction[3], jmpInstruction[4], jmpInstruction[5], jmpInstruction[6]);

    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwPlantInfiniteHPAddress, 7,
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwPlantInfiniteHPAddress,
        jmpInstruction, 7, &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwPlantInfiniteHPAddress, 7, dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == 7)
    {
        AddLog(_T("[植物无限血] Hook安装成功！"));
        return TRUE;
    }
    else
    {
        AddLog(_T("[植物无限血] Hook安装失败，错误码: %d"), GetLastError());
        return FALSE;
    }
}

// 释放内存
void CPlantsCEDlg::FreePlantInfiniteHPMemory()
{
    if (m_bPlantInfiniteHPMemoryAllocated && m_dwPlantInfiniteHPAllocated)
    {
        VirtualFreeEx(m_hProcess, (LPVOID)m_dwPlantInfiniteHPAllocated, 0, MEM_RELEASE);
        AddLog(_T("[植物无限血] 内存已释放"));
        m_bPlantInfiniteHPMemoryAllocated = FALSE;
        m_dwPlantInfiniteHPAllocated = 0;
    }
}

// 启用植物无限血
void CPlantsCEDlg::EnablePlantInfiniteHP()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[植物无限血] 错误: 未附加进程"));
        return;
    }

    if (m_bPlantInfiniteHPEnabled)
    {
        AddLog(_T("[植物无限血] 已经启用"));
        return;
    }

    AddLog(_T("[植物无限血] 正在启用..."));

    // 获取目标地址
    if (m_dwPlantInfiniteHPAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
        {
            m_dwPlantInfiniteHPAddress = dwModuleBase + PLANT_INFINITE_HP_OFFSET;
            AddLog(_T("[植物无限血] 目标地址: 0x%08X"), m_dwPlantInfiniteHPAddress);
        }
        else
        {
            AddLog(_T("[植物无限血] 无法获取模块基址"));
            return;
        }
    }

    // 读取当前字节码
    BYTE currentBytes[7] = { 0 };
    SIZE_T bytesRead = 0;
    if (ReadProcessMemory(m_hProcess, (LPCVOID)m_dwPlantInfiniteHPAddress, currentBytes, 7, &bytesRead))
    {
        AddLog(_T("[植物无限血] 当前字节码: %02X %02X %02X %02X %02X %02X %02X"),
            currentBytes[0], currentBytes[1], currentBytes[2], currentBytes[3],
            currentBytes[4], currentBytes[5], currentBytes[6]);
    }

    // 1. 分配内存
    if (!AllocateMemoryForPlantInfiniteHP())
        return;

    // 2. 写入自定义代码
    if (!WriteCustomCodeForPlantInfiniteHP())
    {
        FreePlantInfiniteHPMemory();
        return;
    }

    // 3. 安装Hook
    if (!InstallHookForPlantInfiniteHP())
    {
        FreePlantInfiniteHPMemory();
        return;
    }

    m_bPlantInfiniteHPEnabled = TRUE;
    AddLog(_T("[植物无限血] 成功启用！植物将不会死亡"));
}

// 禁用植物无限血
void CPlantsCEDlg::DisablePlantInfiniteHP()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[植物无限血] 错误: 未附加进程"));
        return;
    }

    if (!m_bPlantInfiniteHPEnabled)
    {
        AddLog(_T("[植物无限血] 已经禁用"));
        return;
    }

    AddLog(_T("[植物无限血] 正在禁用..."));

    if (m_dwPlantInfiniteHPAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
            m_dwPlantInfiniteHPAddress = dwModuleBase + PLANT_INFINITE_HP_OFFSET;
    }

    // 恢复原始字节码 (7字节)
    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwPlantInfiniteHPAddress, sizeof(PLANT_INFINITE_HP_ORIGINAL_BYTES),
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwPlantInfiniteHPAddress,
        PLANT_INFINITE_HP_ORIGINAL_BYTES, sizeof(PLANT_INFINITE_HP_ORIGINAL_BYTES), &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwPlantInfiniteHPAddress, sizeof(PLANT_INFINITE_HP_ORIGINAL_BYTES),
        dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == sizeof(PLANT_INFINITE_HP_ORIGINAL_BYTES))
    {
        AddLog(_T("[植物无限血] 成功禁用！植物会正常受伤死亡"));
        m_bPlantInfiniteHPEnabled = FALSE;
        FreePlantInfiniteHPMemory();
    }
    else
    {
        AddLog(_T("[植物无限血] 恢复失败，错误码: %d"), GetLastError());
    }
}

void CPlantsCEDlg::OnBnClickedPlantinfinitehp()
{
    // TODO: 在此添加控件通知处理程序代码
    int nCheck = m_checkPlantInfiniteHP.GetCheck();

    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("[植物无限血] 错误: 请先附加进程"));
        m_checkPlantInfiniteHP.SetCheck(m_bPlantInfiniteHPEnabled ? BST_CHECKED : BST_UNCHECKED);
        return;
    }

    if (nCheck == BST_CHECKED)
    {
        EnablePlantInfiniteHP();
    }
    else
    {
        DisablePlantInfiniteHP();
    }

    // 保存配置
    SaveConfigToIni();
}

// 原始字节码: add eax,-01; mov [edi+000000B4],eax (9字节)
const BYTE ICE_MUSHROOM_FREEZE_ORIGINAL_BYTES[] = {
    0x83, 0xC0, 0xFF,                    // add eax, -01
    0x89, 0x87, 0xB4, 0x00, 0x00, 0x00   // mov [edi+000000B4], eax
};

// 自定义代码: nop; mov [edi+000000B4],eax (9字节)
// 将减1操作替换为nop，保持eax不变，实现一直冰冻
const BYTE ICE_MUSHROOM_FREEZE_NEW_CODE[] = {
    0x90,                                // nop (替换 add eax,-01)
    0x90,                                // nop (额外填充，因为add是3字节)
    0x90,                                // nop
    0x89, 0x87, 0xB4, 0x00, 0x00, 0x00,  // mov [edi+000000B4], eax
    0xE9                                 // jmp
};

// ==================== 寒冰菇一直冰冻功能 ====================

// 分配内存
BOOL CPlantsCEDlg::AllocateMemoryForIceMushroomFreeze()
{
    if (m_bIceMushroomFreezeMemoryAllocated && m_dwIceMushroomFreezeAllocated)
    {
        return TRUE;
    }

    AddLog(_T("[寒冰菇冰冻] 正在分配内存..."));

    m_dwIceMushroomFreezeAllocated = (DWORD_PTR)VirtualAllocEx(
        m_hProcess,
        NULL,
        2048,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE
    );

    if (!m_dwIceMushroomFreezeAllocated)
    {
        AddLog(_T("[寒冰菇冰冻] 分配内存失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    AddLog(_T("[寒冰菇冰冻] 内存分配成功: 0x%08X"), m_dwIceMushroomFreezeAllocated);
    m_bIceMushroomFreezeMemoryAllocated = TRUE;
    return TRUE;
}

// 写入自定义代码
BOOL CPlantsCEDlg::WriteCustomCodeForIceMushroomFreeze()
{
    if (!m_bIceMushroomFreezeMemoryAllocated)
        return FALSE;

    // 计算返回地址：原地址 + 9 (原始指令9字节)
    DWORD_PTR returnAddress = m_dwIceMushroomFreezeAddress + 9;

    // 计算JMP位置和偏移
    DWORD_PTR jmpPosition = m_dwIceMushroomFreezeAllocated + sizeof(ICE_MUSHROOM_FREEZE_NEW_CODE);
    // 偏移计算：JMP指令后跟4字节偏移
    DWORD jmpOffset = (DWORD)(returnAddress - (jmpPosition + 4));

    const size_t codeSize = sizeof(ICE_MUSHROOM_FREEZE_NEW_CODE) + 4;
    BYTE* fullCode = new BYTE[codeSize];

    memcpy(fullCode, ICE_MUSHROOM_FREEZE_NEW_CODE, sizeof(ICE_MUSHROOM_FREEZE_NEW_CODE));

    // 设置JMP偏移
    size_t jmpPos = sizeof(ICE_MUSHROOM_FREEZE_NEW_CODE) - 1;
    fullCode[jmpPos] = 0xE9;
    fullCode[sizeof(ICE_MUSHROOM_FREEZE_NEW_CODE)] = (BYTE)(jmpOffset & 0xFF);
    fullCode[sizeof(ICE_MUSHROOM_FREEZE_NEW_CODE) + 1] = (BYTE)((jmpOffset >> 8) & 0xFF);
    fullCode[sizeof(ICE_MUSHROOM_FREEZE_NEW_CODE) + 2] = (BYTE)((jmpOffset >> 16) & 0xFF);
    fullCode[sizeof(ICE_MUSHROOM_FREEZE_NEW_CODE) + 3] = (BYTE)((jmpOffset >> 24) & 0xFF);

    AddLog(_T("[寒冰菇冰冻] 分配地址: 0x%08X"), m_dwIceMushroomFreezeAllocated);
    AddLog(_T("[寒冰菇冰冻] 目标地址: 0x%08X"), m_dwIceMushroomFreezeAddress);
    AddLog(_T("[寒冰菇冰冻] 返回地址: 0x%08X"), returnAddress);
    AddLog(_T("[寒冰菇冰冻] JMP位置: 0x%08X"), jmpPosition);
    AddLog(_T("[寒冰菇冰冻] JMP偏移: 0x%08X"), jmpOffset);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwIceMushroomFreezeAllocated,
        fullCode, codeSize, &bytesWritten);

    if (bResult && bytesWritten == codeSize)
    {
        CString strCode;
        for (size_t i = 0; i < codeSize; i++)
        {
            strCode.AppendFormat(_T("%02X "), fullCode[i]);
        }
        AddLog(_T("[寒冰菇冰冻] 写入代码: %s"), strCode);
        AddLog(_T("[寒冰菇冰冻] 自定义代码写入成功"));
    }
    else
    {
        AddLog(_T("[寒冰菇冰冻] 写入失败，错误码: %d"), GetLastError());
    }

    delete[] fullCode;
    return (bResult && bytesWritten == codeSize);
}

// 安装Hook
BOOL CPlantsCEDlg::InstallHookForIceMushroomFreeze()
{
    AddLog(_T("[寒冰菇冰冻] 正在安装Hook..."));

    // 原始指令9字节，JMP指令5字节，需要4个NOP填充保持9字节
    DWORD jmpOffset = (DWORD)(m_dwIceMushroomFreezeAllocated - (m_dwIceMushroomFreezeAddress + 5));

    // 9字节指令: JMP(5字节) + NOP(4字节)
    BYTE jmpInstruction[9] = { 0xE9 };
    jmpInstruction[1] = (BYTE)(jmpOffset & 0xFF);
    jmpInstruction[2] = (BYTE)((jmpOffset >> 8) & 0xFF);
    jmpInstruction[3] = (BYTE)((jmpOffset >> 16) & 0xFF);
    jmpInstruction[4] = (BYTE)((jmpOffset >> 24) & 0xFF);
    jmpInstruction[5] = 0x90;  // NOP填充
    jmpInstruction[6] = 0x90;  // NOP填充
    jmpInstruction[7] = 0x90;  // NOP填充
    jmpInstruction[8] = 0x90;  // NOP填充

    AddLog(_T("[寒冰菇冰冻] JMP从 0x%08X 到 0x%08X"),
        m_dwIceMushroomFreezeAddress, m_dwIceMushroomFreezeAllocated);
    AddLog(_T("[寒冰菇冰冻] JMP偏移: 0x%08X"), jmpOffset);
    AddLog(_T("[寒冰菇冰冻] JMP指令: %02X %02X %02X %02X %02X %02X %02X %02X %02X"),
        jmpInstruction[0], jmpInstruction[1], jmpInstruction[2],
        jmpInstruction[3], jmpInstruction[4], jmpInstruction[5],
        jmpInstruction[6], jmpInstruction[7], jmpInstruction[8]);

    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwIceMushroomFreezeAddress, 9,
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwIceMushroomFreezeAddress,
        jmpInstruction, 9, &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwIceMushroomFreezeAddress, 9, dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == 9)
    {
        AddLog(_T("[寒冰菇冰冻] Hook安装成功！"));
        return TRUE;
    }
    else
    {
        AddLog(_T("[寒冰菇冰冻] Hook安装失败，错误码: %d"), GetLastError());
        return FALSE;
    }
}

// 释放内存
void CPlantsCEDlg::FreeIceMushroomFreezeMemory()
{
    if (m_bIceMushroomFreezeMemoryAllocated && m_dwIceMushroomFreezeAllocated)
    {
        VirtualFreeEx(m_hProcess, (LPVOID)m_dwIceMushroomFreezeAllocated, 0, MEM_RELEASE);
        AddLog(_T("[寒冰菇冰冻] 内存已释放"));
        m_bIceMushroomFreezeMemoryAllocated = FALSE;
        m_dwIceMushroomFreezeAllocated = 0;
    }
}

// 启用寒冰菇一直冰冻
void CPlantsCEDlg::EnableIceMushroomFreeze()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[寒冰菇冰冻] 错误: 未附加进程"));
        return;
    }

    if (m_bIceMushroomFreezeEnabled)
    {
        AddLog(_T("[寒冰菇冰冻] 已经启用"));
        return;
    }

    AddLog(_T("[寒冰菇冰冻] 正在启用..."));

    // 获取目标地址
    if (m_dwIceMushroomFreezeAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
        {
            m_dwIceMushroomFreezeAddress = dwModuleBase + ICE_MUSHROOM_FREEZE_OFFSET;
            AddLog(_T("[寒冰菇冰冻] 目标地址: 0x%08X"), m_dwIceMushroomFreezeAddress);
        }
        else
        {
            AddLog(_T("[寒冰菇冰冻] 无法获取模块基址"));
            return;
        }
    }

    // 读取当前字节码
    BYTE currentBytes[9] = { 0 };
    SIZE_T bytesRead = 0;
    if (ReadProcessMemory(m_hProcess, (LPCVOID)m_dwIceMushroomFreezeAddress, currentBytes, 9, &bytesRead))
    {
        AddLog(_T("[寒冰菇冰冻] 当前字节码: %02X %02X %02X %02X %02X %02X %02X %02X %02X"),
            currentBytes[0], currentBytes[1], currentBytes[2], currentBytes[3],
            currentBytes[4], currentBytes[5], currentBytes[6], currentBytes[7], currentBytes[8]);
    }

    // 1. 分配内存
    if (!AllocateMemoryForIceMushroomFreeze())
        return;

    // 2. 写入自定义代码
    if (!WriteCustomCodeForIceMushroomFreeze())
    {
        FreeIceMushroomFreezeMemory();
        return;
    }

    // 3. 安装Hook
    if (!InstallHookForIceMushroomFreeze())
    {
        FreeIceMushroomFreezeMemory();
        return;
    }

    m_bIceMushroomFreezeEnabled = TRUE;
    AddLog(_T("[寒冰菇冰冻] 成功启用！寒冰菇效果将一直持续"));
}

// 禁用寒冰菇一直冰冻
void CPlantsCEDlg::DisableIceMushroomFreeze()
{
    if (!m_hProcess || !m_bAttached)
    {
        AddLog(_T("[寒冰菇冰冻] 错误: 未附加进程"));
        return;
    }

    if (!m_bIceMushroomFreezeEnabled)
    {
        AddLog(_T("[寒冰菇冰冻] 已经禁用"));
        return;
    }

    AddLog(_T("[寒冰菇冰冻] 正在禁用..."));

    if (m_dwIceMushroomFreezeAddress == 0)
    {
        DWORD_PTR dwModuleBase = GetModuleBaseAddress();
        if (dwModuleBase)
            m_dwIceMushroomFreezeAddress = dwModuleBase + ICE_MUSHROOM_FREEZE_OFFSET;
    }

    // 恢复原始字节码 (9字节)
    DWORD dwOldProtect = 0;
    VirtualProtectEx(m_hProcess, (LPVOID)m_dwIceMushroomFreezeAddress, sizeof(ICE_MUSHROOM_FREEZE_ORIGINAL_BYTES),
        PAGE_EXECUTE_READWRITE, &dwOldProtect);

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)m_dwIceMushroomFreezeAddress,
        ICE_MUSHROOM_FREEZE_ORIGINAL_BYTES, sizeof(ICE_MUSHROOM_FREEZE_ORIGINAL_BYTES), &bytesWritten);

    VirtualProtectEx(m_hProcess, (LPVOID)m_dwIceMushroomFreezeAddress, sizeof(ICE_MUSHROOM_FREEZE_ORIGINAL_BYTES),
        dwOldProtect, &dwOldProtect);

    if (bResult && bytesWritten == sizeof(ICE_MUSHROOM_FREEZE_ORIGINAL_BYTES))
    {
        AddLog(_T("[寒冰菇冰冻] 成功禁用！寒冰菇效果将正常衰减"));
        m_bIceMushroomFreezeEnabled = FALSE;
        FreeIceMushroomFreezeMemory();
    }
    else
    {
        AddLog(_T("[寒冰菇冰冻] 恢复失败，错误码: %d"), GetLastError());
    }
}

void CPlantsCEDlg::OnBnClickedMushroomfrozen()
{
    // TODO: 在此添加控件通知处理程序代码
    int nCheck = m_checkIceMushroomFreeze.GetCheck();

    if (!m_bAttached || !m_hProcess)
    {
        AddLog(_T("[寒冰菇冰冻] 错误: 请先附加进程"));
        m_checkIceMushroomFreeze.SetCheck(m_bIceMushroomFreezeEnabled ? BST_CHECKED : BST_UNCHECKED);
        return;
    }

    if (nCheck == BST_CHECKED)
    {
        EnableIceMushroomFreeze();
    }
    else
    {
        DisableIceMushroomFreeze();
    }

    // 保存配置
    SaveConfigToIni();
}

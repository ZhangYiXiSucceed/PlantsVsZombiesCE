
// PlantsCEDlg.h: 头文件
//

#pragma once
#include "afxwin.h"

// 在类定义末尾添加常量
#define INI_FILENAME _T("PlantsCE.ini")
#define INI_SECTION _T("CheatSettings")
// 进程名称
#define TARGET_PROCESS_NAME _T("PlantsVsZombies_后台.exe")
// 阳光基址
#define SUNLIGHT_BASE_ADDR 0x6A9F38
// 偏移量
#define OFFSET1 0x768
#define OFFSET2 0x5560
// 阳光初始化偏移
#define TARGET_INIT_VALUE_OFFSET 0xB095  // 偏移地址
// 阳光地址结构
struct SunlightAddress {
	DWORD_PTR baseAddress;      // 基址 0x6A9F38
	DWORD_PTR offset1;           // 第一层偏移 0x768
	DWORD_PTR offset2;           // 第二层偏移 0x5560
	DWORD_PTR finalAddress;      // 最终地址
};
#define NO_PLANT_CD_OFFSET 0x87296     // 无CD功能偏移地址
#define AUTO_FAST_SUN_OFFSET 0x5FA98     // 自动快速生产阳光功能偏移地址
#define AUTO_COLLECT_SUN_OFFSET 0x3158F   // 自动收集阳光功能偏移地址
#define FAST_SHOOT_OFFSET 0x64A96        // 快速发射功能偏移地址

#define SLOT_BASE_ADDR 0x6A9EC0          // 卡槽基址
#define SLOT_OFFSET1 0x768               // 第一级偏移
#define SLOT_OFFSET2 0x144               // 第二级偏移
#define SLOT_OFFSET3_BASE 0x5C           // 第三级偏移基数
#define SLOT_OFFSET_STEP 0x50            // 每个卡槽间隔

#define EXPLODE1_OFFSET 0x1D8FF          // 全屏爆炸1偏移地址
#define EXPLODE2_OFFSET 0x1D905          // 全屏爆炸2偏移地址
#define EXPLODE3_OFFSET 0x1D91F          // 全屏爆炸3偏移地址

#define ZOMBIES_ALL_OUT_OFFSET 0x13E45    // 僵尸全部出动偏移地址
#define POTATO_MINE_NO_CD_OFFSET 0x5FE53  // 土豆地雷无CD偏移地址
#define CHOMPER_NO_CD_OFFSET 0x61565      // 食人花无CD偏移地址

#define PLANT_INFINITE_HP_OFFSET 0x12FCF0  // 植物无限血偏移地址
#define ICE_MUSHROOM_FREEZE_OFFSET 0x12B41F  // 寒冰菇一直冰冻偏移地址
#define REPEAT_PLANT_OFFSET 0xFE2F       // 重复种植偏移地址
#define SUN_MAX_VALUE_OFFSET 0x30A1D     // 阳光最大值偏移地址

// CPlantsCEDlg 对话框
class CPlantsCEDlg : public CDialogEx
{
// 构造
public:
	CPlantsCEDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CPlantsCEDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLANTSCE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	HANDLE m_hProcess;           // 进程句柄
	DWORD m_dwProcessId;         // 进程ID
	BOOL m_bAttached;             // 是否已附加进程
	SunlightAddress m_sunlightAddr;  // 阳光地址结构
	
	CString m_strIniPath;                // INI配置文件路径

	// 控件变量
	CEdit m_editSunBaseValue;     // 阳光值显示编辑框
	CButton m_btnAttachProcess;   // 附加进程按钮
	CButton m_btnReadSunlight;    // 读取阳光按钮
	CButton m_btnModifySunlight;  // 修改阳光按钮
	CStatic m_staticStatus;       // 状态显示
	CListBox m_listLog;           // 日志列表

	CButton m_checkSunInitBigValue;      // 初始值10000功能复选框
	BOOL m_bSunInitBigValueEnabled;      // 功能开关状态
	DWORD_PTR m_dwTargetAddress;         // 目标地址 PlantsVsZombies_后台.exe+B095
	LPVOID m_pAllocatedMemory;           // 分配的内存地址

	CButton m_checkNoPlantCD;          // 无CD功能复选框
	BOOL m_bNoPlantCDEnabled;          // 无CD功能开关状态
	DWORD_PTR m_dwNoPlantCDAddress;    // 目标地址 PlantsVsZombies_后台.exe+87296


	CButton m_checkAutoFastSun;          // 自动快速生产阳光复选框
	BOOL m_bAutoFastSunEnabled;          // 功能开关状态
	DWORD_PTR m_dwAutoFastSunAddress;    // 目标地址 PlantsVsZombies_后台.exe+5FA98
	LPVOID m_pAutoFastSunMemory;         // 分配的内存地址
	DWORD_PTR m_dwAutoFastSunAllocated;
	BOOL m_bAutoFastSunMemoryAllocated;

	CButton m_checkAutoCollectSun;       // 自动收集阳光复选框
	BOOL m_bAutoCollectSunEnabled;       // 功能开关状态
	DWORD_PTR m_dwAutoCollectSunAddress; // 目标地址 PlantsVsZombies_后台.exe+3158F
	DWORD_PTR m_dwAutoCollectSunAllocated; // 分配的内存地址
	BOOL m_bAutoCollectSunMemoryAllocated; // 内存是否已分配


	CButton m_checkFastShoot;            // 快速发射复选框
	BOOL m_bFastShootEnabled;            // 功能开关状态
	DWORD_PTR m_dwFastShootAddress;      // 目标地址 PlantsVsZombies_后台.exe+64A96
	DWORD_PTR m_dwFastShootAllocated;    // 分配的内存地址
	BOOL m_bFastShootMemoryAllocated;    // 内存是否已分配

	// 新增函数声明
	void EnableFastShoot();               // 启用快速发射功能
	void DisableFastShoot();              // 禁用快速发射功能
	BOOL AllocateMemoryForFastShoot();    // 分配内存
	BOOL WriteCustomCodeForFastShoot();   // 写入自定义代码
	BOOL InstallHookForFastShoot();       // 安装Hook
	void FreeFastShootMemory();           // 释放内存

	CButton m_btnSelectProcess;          // 选择进程按钮
	CString m_strProcessName;            // 当前选择的进程名称

	CComboBox m_comboSlot1;              // 卡槽1下拉框
	CComboBox m_comboSlot2;              // 卡槽2下拉框
	CComboBox m_comboSlot3;              // 卡槽3下拉框
	CComboBox m_comboSlot4;              // 卡槽4下拉框
	CComboBox m_comboSlot5;              // 卡槽5下拉框
	CComboBox m_comboSlot6;              // 卡槽6下拉框
	CComboBox m_comboSlot7;              // 卡槽7下拉框
	CComboBox m_comboSlot8;              // 卡槽8下拉框
	CComboBox m_comboSlot9;              // 卡槽9下拉框
	CComboBox m_comboSlot10;             // 卡槽10下拉框

	DWORD_PTR m_dwSlotBaseAddress;       // 卡槽基址 6A9EC0
	DWORD_PTR m_dwSlotOffset1;           // 第一级偏移 768
	DWORD_PTR m_dwSlotOffset2;           // 第二级偏移 144

	// 植物名称数组
	CString m_arrPlantNames[48];          // 0-47 植物名称

	// 保存每个卡槽当前值，避免重复写入
	DWORD m_arrSlotCurrentValue[11];      // 索引1-10

	CButton m_checkFullScreenExplode;    // 全屏爆炸复选框
	BOOL m_bFullScreenExplodeEnabled;    // 功能开关状态

	// 三处地址的变量
	DWORD_PTR m_dwExplode1Address;       // 全屏爆炸1地址 PlantsVsZombies_后台.exe+1D8FF
	DWORD_PTR m_dwExplode2Address;       // 全屏爆炸2地址 PlantsVsZombies_后台.exe+1D905
	DWORD_PTR m_dwExplode3Address;       // 全屏爆炸3地址 PlantsVsZombies_后台.exe+1D91F

	// 三处分配的内存地址
	DWORD_PTR m_dwExplode1Allocated;     // 全屏爆炸1分配的内存地址
	DWORD_PTR m_dwExplode2Allocated;     // 全屏爆炸2分配的内存地址
	DWORD_PTR m_dwExplode3Allocated;     // 全屏爆炸3分配的内存地址

	// 内存分配标志
	BOOL m_bExplode1MemoryAllocated;
	BOOL m_bExplode2MemoryAllocated;
	BOOL m_bExplode3MemoryAllocated;

	CButton m_checkZombiesAllOut;        // 僵尸全部出动复选框
	BOOL m_bZombiesAllOutEnabled;        // 功能开关状态
	DWORD_PTR m_dwZombiesAllOutAddress;  // 目标地址 PlantsVsZombies_后台.exe+13E45
	DWORD_PTR m_dwZombiesAllOutAllocated; // 分配的内存地址
	BOOL m_bZombiesAllOutMemoryAllocated; // 内存是否已分配

	CButton m_checkPotatoMineNoCD;       // 土豆地雷无CD复选框
	BOOL m_bPotatoMineNoCDEnabled;       // 功能开关状态
	DWORD_PTR m_dwPotatoMineNoCDAddress; // 目标地址 PlantsVsZombies_后台.exe+5FE53
	DWORD_PTR m_dwPotatoMineNoCDAllocated; // 分配的内存地址
	BOOL m_bPotatoMineNoCDMemoryAllocated; // 内存是否已分配

	CButton m_checkChomperNoCD;          // 食人花无CD复选框
	BOOL m_bChomperNoCDEnabled;          // 功能开关状态
	DWORD_PTR m_dwChomperNoCDAddress;    // 目标地址 PlantsVsZombies_后台.exe+61565
	DWORD_PTR m_dwChomperNoCDAllocated;  // 分配的内存地址
	BOOL m_bChomperNoCDMemoryAllocated;  // 内存是否已分配

	CButton m_checkPlantInfiniteHP;      // 植物无限血复选框
	BOOL m_bPlantInfiniteHPEnabled;      // 功能开关状态
	DWORD_PTR m_dwPlantInfiniteHPAddress; // 目标地址 PlantsVsZombies_后台.exe+12FCF0
	DWORD_PTR m_dwPlantInfiniteHPAllocated; // 分配的内存地址
	BOOL m_bPlantInfiniteHPMemoryAllocated; // 内存是否已分配

	CButton m_checkIceMushroomFreeze;    // 寒冰菇一直冰冻复选框
	BOOL m_bIceMushroomFreezeEnabled;    // 功能开关状态
	DWORD_PTR m_dwIceMushroomFreezeAddress; // 目标地址 PlantsVsZombies_后台.exe+12B41F
	DWORD_PTR m_dwIceMushroomFreezeAllocated; // 分配的内存地址
	BOOL m_bIceMushroomFreezeMemoryAllocated; // 内存是否已分配

	CButton m_checkRepeatPlant;          // 重复种植复选框
	BOOL m_bRepeatPlantEnabled;          // 功能开关状态
	DWORD_PTR m_dwRepeatPlantAddress;    // 目标地址 PlantsVsZombies_后台.exe+FE2F
	DWORD_PTR m_dwRepeatPlantAllocated;  // 分配的内存地址
	BOOL m_bRepeatPlantMemoryAllocated;  // 内存是否已分配

	CButton m_checkSunMaxValue;          // 阳光最大值复选框
	BOOL m_bSunMaxValueEnabled;          // 功能开关状态
	DWORD_PTR m_dwSunMaxValueAddress;    // 目标地址 PlantsVsZombies_后台.exe+30A1D
	DWORD_PTR m_dwSunMaxValueAllocated;  // 分配的内存地址
	BOOL m_bSunMaxValueMemoryAllocated;  // 内存是否已分配

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CStatic m_PictureShow;
	void ShowBackgroundPicture(CString m_JpgPathName);
	afx_msg void OnStnClickedPictureshow();
	afx_msg void OnBnClickedBtnselpicture();

	afx_msg void OnTimer(UINT_PTR nIDEvent);  // 定时器消息

	CString m_strCurrentImagePath;            // 保存当前图片路径
	void DrawPictureToControl();              // 新增：实际的绘制函数
	// 辅助函数
	BOOL FindProcessId(LPCTSTR szProcessName, DWORD& dwProcessId);
	void AddLog(LPCTSTR szFormat, ...);
	DWORD_PTR ReadPointerChain(DWORD_PTR baseAddress, DWORD_PTR offset1, DWORD_PTR offset2);
	DWORD ReadSunlightValue();
	BOOL WriteSunlightValue(DWORD dwNewValue);
	BOOL AttachToProcess();
	void DetachFromProcess();
	void ShowSunlightAddress();
	afx_msg void OnBnClickedReadSunValue();
	afx_msg void OnBnClickedModifySunValue();
	afx_msg void OnBnClickedAttachprocess();
	afx_msg void OnBnClickedSmallsunadd1000();
	afx_msg void OnBnClickedBigsunadd2000();
	afx_msg void OnBnClickedSuninitbigvalue();

	// 新增函数声明
	void EnableSunInitBigValue();        // 启用初始值10000功能
	void DisableSunInitBigValue();       // 禁用初始值10000功能
	DWORD_PTR GetModuleBaseAddress();    // 获取模块基址

	// 新增函数声明
	void EnableNoPlantCD();             // 启用无CD功能
	void DisableNoPlantCD();            // 禁用无CD功能
	afx_msg void OnBnClickedNocdplant();
	
	// 新增函数声明
	BOOL AllocateMemoryForAutoFastSun();
	BOOL WriteCustomCodeForAutoFastSun();
	BOOL InstallHookForAutoFastSun();
	void FreeAutoFastSunMemory();

	void EnableAutoFastSun();             // 启用自动快速生产阳光功能
	void DisableAutoFastSun();            // 禁用自动快速生产阳光功能
	afx_msg void OnBnClickedAutosunproduce();
	

	void EnableAutoCollectSun();          // 启用自动收集阳光功能
	void DisableAutoCollectSun();         // 禁用自动收集阳光功能
	BOOL AllocateMemoryForAutoCollectSun(); // 分配内存
	BOOL WriteCustomCodeForAutoCollectSun(); // 写入自定义代码
	BOOL InstallHookForAutoCollectSun();    // 安装Hook
	void FreeAutoCollectSunMemory();        // 释放内存

	afx_msg void OnBnClickedAutocollectsun();
	afx_msg void OnBnClickedFastshoot();
	afx_msg void OnBnClickedSelectprocess();

	// 新增函数声明
	void SaveConfigToIni();              // 保存配置到INI文件
	void LoadConfigFromIni();            // 从INI文件加载配置
	void ApplyAllCheatsFromConfig();     // 根据配置应用所有修改功能
	

	// 新增函数声明
	DWORD_PTR GetSlotAddress(int nSlot);  // 获取指定卡槽地址
	DWORD ReadSlotValue(int nSlot);       // 读取卡槽值
	BOOL WriteSlotValue(int nSlot, DWORD dwValue);  // 写入卡槽值
	void InitPlantNames();                // 初始化植物名称
	void InitSlotComboBox(CComboBox& combo, int nSlot);  // 初始化单个卡槽下拉框
	void LoadSlotValue(int nSlot);        // 加载卡槽值到下拉框
	void OnSlotSelChange(int nSlot);      // 卡槽选择变化处理
	void LoadAllSlots();                  // 加载所有卡槽值

	afx_msg void OnCbnSelchangeSlotsel1();
	afx_msg void OnCbnSelchangeSlotsel2();
	afx_msg void OnCbnSelchangeSlotsel3();
	afx_msg void OnCbnSelchangeSlotsel4();
	afx_msg void OnCbnSelchangeSlotsel5();
	afx_msg void OnCbnSelchangeSlotsel6();
	afx_msg void OnCbnSelchangeSlotsel7();
	afx_msg void OnCbnSelchangeSlotsel8();
	afx_msg void OnCbnSelchangeSlotsel9();
	afx_msg void OnCbnSelchangeSlotsel10();

	// 函数声明
	void EnableFullScreenExplode();       // 启用全屏爆炸
	void DisableFullScreenExplode();      // 禁用全屏爆炸

	// 单个功能启用/禁用
	BOOL EnableExplode1();                // 启用爆炸1
	BOOL DisableExplode1();               // 禁用爆炸1
	BOOL EnableExplode2();                // 启用爆炸2
	BOOL DisableExplode2();               // 禁用爆炸2
	BOOL EnableExplode3();                // 启用爆炸3
	BOOL DisableExplode3();               // 禁用爆炸3

	// 内存分配和Hook安装
	BOOL AllocateMemoryForExplode1();
	BOOL AllocateMemoryForExplode2();
	BOOL AllocateMemoryForExplode3();
	BOOL WriteCustomCodeForExplode1();
	BOOL WriteCustomCodeForExplode2();
	BOOL WriteCustomCodeForExplode3();
	BOOL InstallHookForExplode1();
	BOOL InstallHookForExplode2();
	BOOL InstallHookForExplode3();
	void FreeExplodeMemory();

	afx_msg void OnBnClickedFullscreenexplosion();
	afx_msg void OnBnClickedZombiesallgo();

	// 函数声明
	void EnableZombiesAllOut();           // 启用僵尸全部出动
	void DisableZombiesAllOut();          // 禁用僵尸全部出动
	BOOL AllocateMemoryForZombiesAllOut(); // 分配内存
	BOOL WriteCustomCodeForZombiesAllOut(); // 写入自定义代码
	BOOL InstallHookForZombiesAllOut();    // 安装Hook
	void FreeZombiesAllOutMemory();        // 释放内存
	afx_msg void OnBnClickedPotatominenocd();

	// 函数声明
	void EnablePotatoMineNoCD();          // 启用土豆地雷无CD
	void DisablePotatoMineNoCD();         // 禁用土豆地雷无CD
	BOOL AllocateMemoryForPotatoMineNoCD(); // 分配内存
	BOOL WriteCustomCodeForPotatoMineNoCD(); // 写入自定义代码
	BOOL InstallHookForPotatoMineNoCD();    // 安装Hook
	void FreePotatoMineNoCDMemory();        // 释放内存

	// 函数声明
    void EnableChomperNoCD();             // 启用食人花无CD
    void DisableChomperNoCD();            // 禁用食人花无CD
    BOOL AllocateMemoryForChomperNoCD();  // 分配内存
    BOOL WriteCustomCodeForChomperNoCD(); // 写入自定义代码
    BOOL InstallHookForChomperNoCD();     // 安装Hook
    void FreeChomperNoCDMemory();         // 释放内存
	afx_msg void OnBnClickedEatzombiesnocd();

	// 函数声明
	void EnablePlantInfiniteHP();         // 启用植物无限血
	void DisablePlantInfiniteHP();        // 禁用植物无限血
	BOOL AllocateMemoryForPlantInfiniteHP(); // 分配内存
	BOOL WriteCustomCodeForPlantInfiniteHP(); // 写入自定义代码
	BOOL InstallHookForPlantInfiniteHP();    // 安装Hook
	void FreePlantInfiniteHPMemory();        // 释放内存
	afx_msg void OnBnClickedPlantinfinitehp();

	//函数声明
    void EnableIceMushroomFreeze();       // 启用寒冰菇一直冰冻
    void DisableIceMushroomFreeze();      // 禁用寒冰菇一直冰冻
    BOOL AllocateMemoryForIceMushroomFreeze(); // 分配内存
    BOOL WriteCustomCodeForIceMushroomFreeze(); // 写入自定义代码
    BOOL InstallHookForIceMushroomFreeze();    // 安装Hook
    void FreeIceMushroomFreezeMemory();        // 释放内存
	afx_msg void OnBnClickedMushroomfrozen();
	afx_msg void OnBnClickedClearplants();
	
	// 函数声明
	void EnableRepeatPlant();             // 启用重复种植
	void DisableRepeatPlant();            // 禁用重复种植
	BOOL AllocateMemoryForRepeatPlant();  // 分配内存
	BOOL WriteCustomCodeForRepeatPlant(); // 写入自定义代码
	BOOL InstallHookForRepeatPlant();     // 安装Hook
	void FreeRepeatPlantMemory();         // 释放内存

	afx_msg void OnBnClickedRepeatplants();

	// 函数声明
	void EnableSunMaxValue();             // 启用阳光最大值
	void DisableSunMaxValue();            // 禁用阳光最大值
	BOOL AllocateMemoryForSunMaxValue();  // 分配内存
	BOOL WriteCustomCodeForSunMaxValue(); // 写入自定义代码
	BOOL InstallHookForSunMaxValue();     // 安装Hook
	void FreeSunMaxValueMemory();         // 释放内存
	afx_msg void OnBnClickedSunvaluemax();
};






// myCalculatorDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "myCalculator.h"
#include "myCalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmyCalculatorDlg 对话框



CmyCalculatorDlg::CmyCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MYCALCULATOR_DIALOG, pParent)
	, inputValue(_T(""))
	, equationValue(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	result = NULL;
	operation = "";
}

void CmyCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, BUTTON_INPUT, inputValue);
	DDX_Control(pDX, BUTTON_INPUT, inputEdit);
	DDX_Control(pDX, BUTTON_EQUATION, equationEdit);
	DDX_Text(pDX, BUTTON_EQUATION, equationValue);
}

BEGIN_MESSAGE_MAP(CmyCalculatorDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BUTTON_NUM_1, &CmyCalculatorDlg::OnBnClickedNum1)
	ON_BN_CLICKED(BUTTON_NUM_2, &CmyCalculatorDlg::OnBnClickedNum2)
	ON_BN_CLICKED(BUTTON_NUM_3, &CmyCalculatorDlg::OnBnClickedNum3)
	ON_BN_CLICKED(BUTTON_NUM_4, &CmyCalculatorDlg::OnBnClickedNum4)
	ON_BN_CLICKED(BUTTON_NUM_5, &CmyCalculatorDlg::OnBnClickedNum5)
	ON_BN_CLICKED(BUTTON_NUM_6, &CmyCalculatorDlg::OnBnClickedNum6)
	ON_BN_CLICKED(BUTTON_NUM_7, &CmyCalculatorDlg::OnBnClickedNum7)
	ON_BN_CLICKED(BUTTON_NUM_8, &CmyCalculatorDlg::OnBnClickedNum8)
	ON_BN_CLICKED(BUTTON_NUM_9, &CmyCalculatorDlg::OnBnClickedNum9)
	ON_BN_CLICKED(BUTTON_ADD, &CmyCalculatorDlg::OnBnClickedAdd)
	ON_BN_CLICKED(BUTTON_MINUS, &CmyCalculatorDlg::OnBnClickedMinus)
	ON_BN_CLICKED(BUTTON_MULTIPLY, &CmyCalculatorDlg::OnBnClickedMultiply)
	ON_BN_CLICKED(BUTTON_DIVIDE, &CmyCalculatorDlg::OnBnClickedDivide)
	ON_BN_CLICKED(BUTTON_DELETE, &CmyCalculatorDlg::OnBnClickedDelete)
	ON_BN_CLICKED(BUTTON_CLEAR, &CmyCalculatorDlg::OnBnClickedClear)
	ON_BN_CLICKED(BUTTON_CLEAR_ENTRY, &CmyCalculatorDlg::OnBnClickedClearEntry)
	ON_BN_CLICKED(BUTTON_NEGATIVE, &CmyCalculatorDlg::OnBnClickedNegative)
	ON_BN_CLICKED(BUTTON_EQUALS, &CmyCalculatorDlg::OnBnClickedEquals)
	ON_BN_CLICKED(BUTTON_NUM_0, &CmyCalculatorDlg::OnBnClickedNum0)
	ON_BN_CLICKED(BUTTON_DOT, &CmyCalculatorDlg::OnBnClickedDot)
END_MESSAGE_MAP()


// CmyCalculatorDlg 消息处理程序

BOOL CmyCalculatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	font.DeleteObject();
	font.CreatePointFont(350, _T("微软雅黑"));
	inputEdit.SetFont(&font);

	//inputValue = "0";
	inputEdit.SetWindowTextW(_T("0"));

	enterFlag = false;

	//以下为键盘响应
	HACCEL num_0 = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_NUM_0));
	HACCEL num_1 = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_NUM_1));
	HACCEL num_2 = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_NUM_2));
	HACCEL num_3 = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_NUM_3));
	HACCEL num_4 = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_NUM_4));
	HACCEL num_5 = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_NUM_5));
	HACCEL num_6 = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_NUM_6));
	HACCEL num_7 = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_NUM_7));
	HACCEL num_8 = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_NUM_8));
	HACCEL num_9 = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_NUM_9));
	HACCEL buttonAdd = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_ADD));
	HACCEL buttonMinus = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_MINUS));
	HACCEL buttonMultiply = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_MULTIPLY));
	HACCEL buttonDivide = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_DIVIDE));
	HACCEL buttonEquals = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(BUTTON_EQUALS));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmyCalculatorDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmyCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmyCalculatorDlg::setInput(char i)
{
	inputValue.AppendChar(i);
	inputEdit.SetWindowTextW(inputValue);
}

void CmyCalculatorDlg::clearInput()
{
	inputValue = "";
	inputEdit.SetWindowTextW(_T("0"));
}

void CmyCalculatorDlg::addEquation(CString i)
{
	equationValue.Append(inputValue);
	equationValue.Append(_T(" "));
	equationValue.Append(i);
	equationValue.Append(_T(" "));
	equationEdit.SetWindowTextW(equationValue);
}

void CmyCalculatorDlg::clearEquation()
{
	equationValue = "";
	equationEdit.SetWindowTextW(equationValue);
}

void CmyCalculatorDlg::getResult(CString i)
{
	if (result == NULL && operation == "") {
		result = _wtof(inputValue);
		operation = i;
	}
	else {
		double tmpNum = _wtof(inputValue);
		if (inputValue.Mid(0, 1) == "-") {
			tmpNum = -tmpNum;
		}
		if (operation == "＋") {
			result += tmpNum;
		}
		else if (operation == "－") {
			result -= tmpNum;
		}
		else if (operation == "×") {
			result *= tmpNum;
		}
		else if (operation == "÷") {
			result /= tmpNum;
		}
		operation = i;
		CString resultStr;

		resultStr.Format(_T("%lf"), result);

		int count = 0;
		int i = resultStr.GetLength();
		while (resultStr.Mid(i - 1, 1) == "0")
		{
			count++;
			i--;
		}

		for (i = count; i > 0; i--) {
			resultStr = resultStr.Mid(0, resultStr.GetLength() - 1);
		}

		if (resultStr.Mid(resultStr.GetLength() - 1, 1) == ".") {
			resultStr = resultStr.Mid(0, resultStr.GetLength() - 1);
		}

		inputEdit.SetWindowTextW(resultStr);
	}
}

void CmyCalculatorDlg::clearResult()
{
	if (inputValue == "" && result != 0 && enterFlag == true) {
		result = 0;
		enterFlag = false;
	}
}

void CmyCalculatorDlg::setResult()
{
	enterFlag = false;
}

void CmyCalculatorDlg::OnBnClickedNum1()
{
	clearResult();
	setInput('1');
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedNum2()
{
	clearResult();
	setInput('2');
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedNum3()
{
	clearResult();
	setInput('3');
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedNum4()
{
	clearResult();
	setInput('4');
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedNum5()
{
	clearResult();
	setInput('5');
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedNum6()
{
	clearResult();
	setInput('6');
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedNum7()
{
	clearResult();
	setInput('7');
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedNum8()
{
	clearResult();
	setInput('8');
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedNum9()
{
	clearResult();
	setInput('9');
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedAdd()

{
	getResult(_T("＋"));

	addEquation(_T("＋"));

	inputValue = "";

	setResult();
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedMinus()
{
	getResult(_T("－"));

	addEquation(_T("－"));

	inputValue = "";

	setResult();
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedMultiply()
{
	getResult(_T("×"));

	addEquation(_T("×"));

	inputValue = "";

	setResult();
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedDivide()
{
	getResult(_T("÷"));

	addEquation(_T("÷"));

	inputValue = "";

	setResult();
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedDelete()
{
	inputValue = inputValue.Mid(0, inputValue.GetLength() - 1);
	inputEdit.SetWindowTextW(inputValue);
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedClear()
{
	clearInput();
	clearEquation();
	inputValue = "";
	result = 0;
	operation = "";
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedClearEntry()
{
	clearInput();
	inputValue = "";
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedNegative()
{
	CString negate = _T("-");

	CString str;

	if (enterFlag) {
		str.Format(_T("%lf"), result);

		int count = 0;
		int i = str.GetLength();
		while (str.Mid(i - 1, 1) == "0" || str.Mid(i - 1, 1) == ".") {
			count++;
			i--;
		}
		str = str.Mid(0, i);
	}
	else {
		str = inputValue;
	}

	double j = _wtof(str);
	if (j > 0) {
		negate.Append(str);
		str = negate;
	}
	else if (j < 0) {
		str = str.Mid(1, str.GetLength());
	}

	j = -j;
	
	if (enterFlag) {
		result = j;
	}

	inputValue = str;

	inputEdit.SetWindowTextW(inputValue);
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedEquals()
{
	clearEquation();
	getResult(_T("＝"));

	inputValue = "";
	operation = "";
	enterFlag = true;
	// TODO: 在此添加控件通知处理程序代码
}


void CmyCalculatorDlg::OnBnClickedNum0()
{
	clearResult();
	setInput('0');
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CmyCalculatorDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam)
		{
		case VK_NUMPAD0:
			OnBnClickedNum0(); return true;
		case VK_NUMPAD1:
			OnBnClickedNum1(); return true;
		case VK_NUMPAD2:
			OnBnClickedNum2(); return true;
		case VK_NUMPAD3:
			OnBnClickedNum3(); return true;
		case VK_NUMPAD4:
			OnBnClickedNum4(); return true;
		case VK_NUMPAD5:
			OnBnClickedNum5(); return true;
		case VK_NUMPAD6:
			OnBnClickedNum6(); return true;
		case VK_NUMPAD7:
			OnBnClickedNum7(); return true;
		case VK_NUMPAD8:
			OnBnClickedNum8(); return true;
		case VK_NUMPAD9:
			OnBnClickedNum9(); return true;
		case VK_ADD:
			OnBnClickedAdd(); return true;
		case VK_SUBTRACT:
			OnBnClickedMinus(); return true;
		case VK_MULTIPLY:
			OnBnClickedMultiply(); return true;
		case VK_DIVIDE:
			OnBnClickedDivide(); return true;
		case VK_RETURN:
			OnBnClickedEquals(); return true;
		//case VK_SEPARATOR:
		//	OnBnClickedEquals(); break;
		case VK_DELETE:
			OnBnClickedDelete(); return true;
		case VK_BACK:
			OnBnClickedDelete(); return true;
		default:
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}



//void CmyCalculatorDlg::OnOK()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	OnBnClickedEquals();
//}


void CmyCalculatorDlg::OnBnClickedDot()
{
	if (inputValue == "") {
		inputValue = "0.";
	}
	else if (inputValue.Find('.', 0) == -1) {
		inputValue.AppendChar('.');
	}
	inputEdit.SetWindowTextW(inputValue);
	// TODO: 在此添加控件通知处理程序代码
}

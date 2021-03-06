
// myCalculatorDlg.h: 头文件
//

#pragma once
#include "afxwin.h"


// CmyCalculatorDlg 对话框
class CmyCalculatorDlg : public CDialog
{
// 构造
public:
	CmyCalculatorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYCALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CFont font;

	CString inputValue;
	CEdit inputEdit;

	CEdit equationEdit;
	CString equationValue;

	CString operation;
	double result;

	bool enterFlag;

	void setInput(char i);
	void clearInput();

	void addEquation(CString i);
	void clearEquation();

	void getResult(CString i);
	void clearResult();
	void setResult();

	afx_msg void OnBnClickedNum1();
	afx_msg void OnBnClickedNum2();
	afx_msg void OnBnClickedNum3();
	afx_msg void OnBnClickedNum4();
	afx_msg void OnBnClickedNum5();
	afx_msg void OnBnClickedNum6();
	afx_msg void OnBnClickedNum7();
	afx_msg void OnBnClickedNum8();
	afx_msg void OnBnClickedNum9();

	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedMinus();
	afx_msg void OnBnClickedMultiply();
	afx_msg void OnBnClickedDivide();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedClearEntry();
	afx_msg void OnBnClickedNegative();
	afx_msg void OnBnClickedEquals();
	afx_msg void OnBnClickedNum0();

	//以下为键盘响应
	HACCEL num_0;
	HACCEL num_1;
	HACCEL num_2;
	HACCEL num_3;
	HACCEL num_4;
	HACCEL num_5;
	HACCEL num_6;
	HACCEL num_7;
	HACCEL num_8;
	HACCEL num_9;
	HACCEL buttonAdd;
	HACCEL buttonMinus;
	HACCEL buttonMultiply;
	HACCEL buttonDivide;
	HACCEL buttonEquls;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedDot();
};

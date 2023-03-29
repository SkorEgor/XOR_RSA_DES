
// Encoder.InformationSecurity.V2Dlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CEncoderInformationSecurityV2Dlg
class CEncoderInformationSecurityV2Dlg : public CDialogEx
{
// Создание
public:
	CEncoderInformationSecurityV2Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENCODERINFORMATIONSECURITYV2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString check_open;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit2();
	CString input_text;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedButton5();
	CString in_key;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedButton4();
	CString out_file;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton7();
	CButton gen;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio3();
	unsigned inputEncryptionN;
	unsigned inputEncryptionE;
	unsigned inputDecryptionN;
	unsigned inputDecryptionD;
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	CString DESinputKey;
};


// Encoder.InformationSecurity.V2Dlg.cpp: файл реализации
//


#include "pch.h"
#include "framework.h"
#include "Encoder.InformationSecurity.V2.h"
#include "Encoder.InformationSecurity.V2Dlg.h"
#include "afxdialogex.h"
#include "String"
#include "XOR.h"

#include "RSA.h"
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <utility>
#include <exception>
#include <tuple>

#include "DES.h"
#include <string>
#include <cmath>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define radioButtonXOR 1
#define radioButtonRSAencryption 2
#define radioButtonRSAdecryption 3
#define radioButtonDESencryption 4
#define radioButtonDESdecryption 5

int radioButtonNow = 0;
NED myKey;
DES valueDES;

//Зададим путь к папке по умолчанию
TCHAR InitialPathOpen[] = _T("C:\\Users\\Egor\\Documents\\Programm\\Encoder.InformationSecurity.V3 - копия - копия\\TestWork\\Example_in_file");
TCHAR InitialPathDownload[] = _T("C:\\Users\\Egor\\Documents\\Programm\\Encoder.InformationSecurity.V3 - копия - копия\\TestWork");
//Зададим фильтр принимаемых файлов
TCHAR FileFilter[] = _T("Текст (*.txt)\0*.txt\0Все файлы (*.*)\0*.*\0");


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CEncoderInformationSecurityV2Dlg

CEncoderInformationSecurityV2Dlg::CEncoderInformationSecurityV2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ENCODERINFORMATIONSECURITYV2_DIALOG, pParent)
	, check_open(_T(""))
	, input_text(_T(""))
	, in_key(_T(""))
	, out_file(_T(""))
	, DESinputKey(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEncoderInformationSecurityV2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, input_text);
	DDX_Text(pDX, IDC_EDIT4, in_key);
	DDX_Text(pDX, IDC_EDIT3, out_file);
	DDX_Control(pDX, IDC_BUTTON7, gen);
	DDX_Text(pDX, IDC_EDIT5, inputEncryptionN);
	DDX_Text(pDX, IDC_EDIT6, inputEncryptionE);
	DDX_Text(pDX, IDC_EDIT7, inputDecryptionN);
	DDX_Text(pDX, IDC_EDIT8, inputDecryptionD);
	DDX_Text(pDX, IDC_EDIT9, DESinputKey);
}

BEGIN_MESSAGE_MAP(CEncoderInformationSecurityV2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CEncoderInformationSecurityV2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CEncoderInformationSecurityV2Dlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT2, &CEncoderInformationSecurityV2Dlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CEncoderInformationSecurityV2Dlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON5, &CEncoderInformationSecurityV2Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CEncoderInformationSecurityV2Dlg::OnBnClickedButton6)
	ON_EN_CHANGE(IDC_EDIT4, &CEncoderInformationSecurityV2Dlg::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON4, &CEncoderInformationSecurityV2Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CEncoderInformationSecurityV2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &CEncoderInformationSecurityV2Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_RADIO2, &CEncoderInformationSecurityV2Dlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &CEncoderInformationSecurityV2Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &CEncoderInformationSecurityV2Dlg::OnBnClickedRadio3)
	ON_EN_CHANGE(IDC_EDIT5, &CEncoderInformationSecurityV2Dlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CEncoderInformationSecurityV2Dlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CEncoderInformationSecurityV2Dlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &CEncoderInformationSecurityV2Dlg::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, &CEncoderInformationSecurityV2Dlg::OnEnChangeEdit9)
	ON_BN_CLICKED(IDC_RADIO6, &CEncoderInformationSecurityV2Dlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CEncoderInformationSecurityV2Dlg::OnBnClickedRadio7)
END_MESSAGE_MAP()


// Обработчики сообщений CEncoderInformationSecurityV2Dlg

BOOL CEncoderInformationSecurityV2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CEncoderInformationSecurityV2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CEncoderInformationSecurityV2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CEncoderInformationSecurityV2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



/**********************ИСХОДНЫЙ ФАЙЛ**********************/
//Кнопка ОТКРЫТИЯ
void CEncoderInformationSecurityV2Dlg::OnBnClickedButton1()
{
	CFileDialog filedlg(true);											//Создаем объект типа CFile diolog; открытие файла - true, сохранения - false

	filedlg.m_pOFN->lpstrFilter = FileFilter;							//Фильтр принимаемых файлов, только текст (Все файлы (*.*)\0*.*\0)

	TCHAR WindowName[] = _T("Открытие нового файла");					//Название открывшегося окна
	filedlg.m_pOFN->lpstrTitle = WindowName;							//Передаем этот параметр в диалог

	//filedlg.m_pOFN->lpstrInitialDir = InitialPathOpen;					//Задаем начальную папку

	if (filedlg.DoModal() == IDOK)										//filedlg.DoModal()-Создание окна диалога открытия файла, если по возращение все ок, то выводим файл
	{
		CString Cstr;													//Хранение ТОЛЬКО строки из файла
		CStdioFile oResultFile(filedlg.GetPathName(), CFile::modeRead);	//Открытие файла с режимом чтения
		oResultFile.ReadString(Cstr);
		CString strFile= Cstr;												//Хранение ВСЕГО текста файла
		while (oResultFile.ReadString(Cstr) != NULL) {					//Считовать строку, пока не опустошим файл
			strFile += _T("\r\n") + Cstr;								//К тексту добавить строку из файла
		}
		oResultFile.Close();											//Закрыть

		//check_open = //filedlg.GetFileName()	 + "\n" +			/*Имя файла					hi.txt		*/
					 // filedlg.GetFileExt()	 + "\n" +			/*Расширение имени файла	txt			*/
					 //filedlg.GetFileTitle()	 + "\n" +			/*Имя файла без расширения	hi			*/
					 //filedlg.GetPathName()		 + _T("\n")  ;		/*Полный путь к файлу		C:\hi.txt	*/

		input_text = strFile/*.c_str() */;
		/*CString a = "a";
		CString B = "B";
		input_text = _T(char(int(a[0]) ^ int(B[0])));*/
	}

	UpdateData(false);											//Обновляем парметры
}
//Кнопка СОХРАНЕНИЯ
void CEncoderInformationSecurityV2Dlg::OnBnClickedButton2()
{
	//Открываем окно сохранения файла
	CFileDialog filedlg(false);											//Создаем объект типа CFile diolog; открытие файла - true, сохранения - false

	filedlg.m_pOFN->lpstrFilter = FileFilter;							//Фильтр принимаемых файлов, только текст (Все файлы (*.*)\0*.*\0)Пример строки для этого параметра из MFC (3 шаблона):	"Bitmap files(*.bmp)\0*.bmp\0JPEG files(*.jpg)\0*.jpg\0All files(*.*)\0*.*\0\0"

	TCHAR WindowName[] = _T("Сохранение файла");						//Название открывшегося окна
	filedlg.m_pOFN->lpstrTitle = WindowName;							//Передаем этот параметр в диалог

	//filedlg.m_pOFN->lpstrInitialDir = InitialPathDownload;				//Задаем начальную папку
	
	TCHAR StartName[_MAX_PATH] = _T("textORcode");						//Предложим название файла
	filedlg.m_pOFN->lpstrFile= StartName;

	//filedlg.DoModal();												//Создание окна диалога открытия файла

	if (filedlg.DoModal() == IDOK)										//filedlg.DoModal()-Создание окна диалога открытия файла, если по возращение все ок, то выводим файл
	{
		if (filedlg.m_pOFN->nFilterIndex == 1) {						//Под первым индеском фильтра стоит txt
			CStdioFile oResultFile(filedlg.GetPathName() + _T(".txt"),	//Открываем поток с приставкой формата
			CFile::modeCreate | CFile::modeReadWrite);					//Открытие файла с режимом создания и чтения записи
			oResultFile.WriteString( input_text);
			oResultFile.Close();										//Закрытие потока
		}
		if (filedlg.m_pOFN->nFilterIndex == 2) {						//Под первым индеском фильтра стоит all
			CStdioFile oResultFile(filedlg.GetPathName(),				//Открываем поток с приставкой формата
				CFile::modeCreate | CFile::modeReadWrite);				//Открытие файла с режимом создания и чтения записи
			oResultFile.WriteString(input_text);
			oResultFile.Close();										//Закрытие потока
		}
	}

	UpdateData(false);
}
//Edit control - ОТОБРАЖАЕТ файл
void CEncoderInformationSecurityV2Dlg::OnEnChangeEdit2() { 
	UpdateData(true);
}


/**********************ВЫХОДНОЙ ФАЙЛ**********************/
//Кнопка СОХРАНЕНИЯ
void CEncoderInformationSecurityV2Dlg::OnBnClickedButton4()
{
	//Открываем окно сохранения файла
	CFileDialog filedlg(false);											//Создаем объект типа CFile diolog; сохранениие - false

	filedlg.m_pOFN->lpstrFilter = FileFilter;							//Фильтр принимаемых файлов, только текст (Все файлы (*.*)\0*.*\0)Пример строки для этого параметра из MFC (3 шаблона):	"Bitmap files(*.bmp)\0*.bmp\0JPEG files(*.jpg)\0*.jpg\0All files(*.*)\0*.*\0\0"

	TCHAR WindowName[] = _T("Сохранение шифротекста");					//Название открывшегося окна
	filedlg.m_pOFN->lpstrTitle = WindowName;							//Передаем этот параметр в диалог

	//filedlg.m_pOFN->lpstrInitialDir = InitialPathDownload;				//Задаем начальную папку

	TCHAR StartName[_MAX_PATH] = _T("Ciphertext");						//Предложим название файла
	filedlg.m_pOFN->lpstrFile = StartName;

	//filedlg.DoModal();												//Создание окна диалога открытия файла

	if (filedlg.DoModal() == IDOK)										//filedlg.DoModal()-Создание окна диалога открытия файла, если по возращение все ок, то выводим файл
	{
		if (filedlg.m_pOFN->nFilterIndex == 1) {						//Под первым индеском фильтра стоит txt
			CStdioFile oResultFile(filedlg.GetPathName() + _T(".txt"),	//Открываем поток с приставкой формата
				CFile::modeCreate | CFile::modeReadWrite);					//Открытие файла с режимом создания и чтения записи
			oResultFile.WriteString(out_file);
			oResultFile.Close();										//Закрытие потока
		}
		if (filedlg.m_pOFN->nFilterIndex == 2) {						//Под первым индеском фильтра стоит all
			CStdioFile oResultFile(filedlg.GetPathName(),				//Открываем поток с приставкой формата
				CFile::modeCreate | CFile::modeReadWrite);				//Открытие файла с режимом создания и чтения записи
			oResultFile.WriteString(out_file);
			oResultFile.Close();										//Закрытие потока
		}
	}

	UpdateData(false);
}
//Edit control - ОТОБРАЖАЕТ файл
void CEncoderInformationSecurityV2Dlg::OnEnChangeEdit3() {
	UpdateData(true);
}


/************************XOR***************************/
//Вкл. радио кнопки XOR
void CEncoderInformationSecurityV2Dlg::OnBnClickedRadio1()
{
	//Запоминаем положение кнопки
	radioButtonNow = radioButtonXOR;

	//Вкл. параметров XOR
	GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);

	//Выкл. параметров RSA Шифрования
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);

	//Выкл. параметров RSA Дешифрования
	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);

	//Выкл. параметров DES
	GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);

	UpdateData(false);
}
//Edit control - ОТОБРАЖАЕТ файл
void CEncoderInformationSecurityV2Dlg::OnEnChangeEdit4() {
	UpdateData(true);
}



/************************RSA***************************/
/*Шифрование*/
//Вкл. радио кнопки RSA 
void CEncoderInformationSecurityV2Dlg::OnBnClickedRadio2()
{
	radioButtonNow = radioButtonRSAencryption;

	//Вкл. параметров XOR
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);

	//Выкл. параметров RSA Шифрования
	GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);

	//Выкл. параметров RSA Дешифрования
	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);

	//Выкл. параметров DES
	GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);

	UpdateData(false);
}
//Edit control - ОТОБРАЖАЕТ n
void CEncoderInformationSecurityV2Dlg::OnEnChangeEdit5() {
	UpdateData(true);
}
//Edit control - ОТОБРАЖАЕТ e
void CEncoderInformationSecurityV2Dlg::OnEnChangeEdit6() {
	UpdateData(true);
}
/*Дешифрование*/
//Вкл. радио кнопки RSA 
void CEncoderInformationSecurityV2Dlg::OnBnClickedRadio3()
{
	radioButtonNow = radioButtonRSAdecryption;

	//Вкл. параметров XOR
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);

	//Выкл. параметров RSA Шифрования
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);

	//Выкл. параметров RSA Дешифрования
	GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);

	//Выкл. параметров DES
	GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);

	UpdateData(false);
}
//Edit control - ОТОБРАЖАЕТ n
void CEncoderInformationSecurityV2Dlg::OnEnChangeEdit7() {
	UpdateData(true);
}
//Edit control - ОТОБРАЖАЕТ e
void CEncoderInformationSecurityV2Dlg::OnEnChangeEdit8() {
	UpdateData(true);
}


/************************DES***************************/
//Вкл. радио кнопки RSA Шифрования
void CEncoderInformationSecurityV2Dlg::OnBnClickedRadio6()
{
	radioButtonNow = radioButtonDESencryption;

	//Выкл. параметров XOR
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);

	//Выкл. параметров RSA Шифрования
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);

	//Выкл. параметров RSA Дешифрования
	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);

	//Вкл. параметров DES
	GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);

	UpdateData(false);
}
//Вкл. радио кнопки RSA Расшифрование
void CEncoderInformationSecurityV2Dlg::OnBnClickedRadio7()
{
	radioButtonNow = radioButtonDESdecryption;

	//Выкл. параметров XOR
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);

	//Выкл. параметров RSA Шифрования
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);

	//Выкл. параметров RSA Дешифрования
	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);

	//Вкл. параметров DES
	GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);

	UpdateData(false);
}
//Edit control - ОТОБРАЖАЕТ ключ DESinputKey
void CEncoderInformationSecurityV2Dlg::OnEnChangeEdit9(){
	UpdateData(true);
}


/*******************НАСТРОЙКА ШИФРОВАНИЯ******************/
//Кнопка Запуска
void CEncoderInformationSecurityV2Dlg::OnBnClickedButton3() {
	//Если режим XOR
	if (radioButtonNow == radioButtonXOR) {
		out_file = XOR(input_text, in_key);
	}

	//Если режим RSA шифрование
	else if (radioButtonNow == radioButtonRSAencryption) {
		out_file = RSA::encryptionRSA(input_text, inputEncryptionE, inputEncryptionN);
	}
	//Если режим RSA дешифрование
	else if (radioButtonNow == radioButtonRSAdecryption) {
		out_file = RSA::decryptionRSA(input_text, inputDecryptionD, inputDecryptionN);
	}

	//Если режим DES шифрования
	else if (radioButtonNow == radioButtonDESencryption) {
		out_file = valueDES.encryptionDES(input_text, DESinputKey);
	}
	//Если режим DES расшифрования
	else if (radioButtonNow == radioButtonDESdecryption) {
		out_file = valueDES.decryptionDES(input_text, DESinputKey);
	}

	UpdateData(false);
}

/*Управление ключами*/
//Кнопка Генератора
void CEncoderInformationSecurityV2Dlg::OnBnClickedButton7()
{
	if (radioButtonNow == 1) {
		CString key_gen;									//Переменная для сгенерированного ключа
		int len_key = 20;									//Длинна ключа
		int code_first_char = 48;							//Задаем промежуток из которого будем генерировать сиволы
		int code_last_char = 126;
		for (int i = 0; i < len_key; i++) {					//Сгенерируем 20 символов
			key_gen += ((char)(code_first_char + rand()		//рандомим
				% (code_last_char - code_first_char)));
		}
		in_key = key_gen;									//Вывод
	}
	else if (radioButtonNow == radioButtonRSAencryption || radioButtonNow == radioButtonRSAdecryption) {
		//Генерируем и сохраняем ключи
		myKey = RSA::keyGen();

		//Выводим значения сгенерированных ключей:
		inputEncryptionN = myKey.n;
		inputEncryptionE = myKey.e;
		inputDecryptionD = myKey.d;
		inputDecryptionN = myKey.n;
	}
	else if (radioButtonNow == radioButtonDESencryption || radioButtonNow == radioButtonDESdecryption) {
		DESinputKey = valueDES.encryptionKeyGenerator();
	}
	UpdateData(false);
}
//Кнопка ОТКРЫТИЯ
void CEncoderInformationSecurityV2Dlg::OnBnClickedButton5()
{
	if (radioButtonNow != 0) {
		CFileDialog filedlg(true);											//Создаем объект типа CFile diolog; открытие файла - true

		filedlg.m_pOFN->lpstrFilter = FileFilter;							//Фильтр принимаемых файлов, только текст (Все файлы (*.*)\0*.*\0)

		TCHAR WindowName[] = _T("Загрузка ключа");							//Название открывшегося окна
		filedlg.m_pOFN->lpstrTitle = WindowName;							//Передаем этот параметр в диалог

		//filedlg.m_pOFN->lpstrInitialDir = InitialPathOpen;					//Задаем начальную папку

		if (filedlg.DoModal() == IDOK)										//filedlg.DoModal()-Создание окна диалога открытия файла, если по возращение все ок, то выводим файл
		{
			if (radioButtonNow == radioButtonXOR) {
				CString Cstr;													//Хранение ТОЛЬКО строки из файла
				CStdioFile oResultFile(filedlg.GetPathName(), CFile::modeRead);	//Открытие файла с режимом чтения
				oResultFile.ReadString(Cstr);
				oResultFile.Close();											//Закрыть
				in_key = Cstr;
			}
			//Если RSA
			else if (radioButtonNow == radioButtonRSAencryption) {
				CString Cstr;													//Хранение ТОЛЬКО строки из файла
				CStdioFile oResultFile(filedlg.GetPathName(), CFile::modeRead);	//Открытие файла с режимом чтения
				oResultFile.ReadString(Cstr);
				inputEncryptionN = atoi(Cstr);
				oResultFile.ReadString(Cstr);
				inputEncryptionE = atoi(Cstr);

				oResultFile.Close();											//Закрыть
			}
			//Если расшифровываем RSA
			else if (radioButtonNow == radioButtonRSAdecryption) {
				CString Cstr;													//Хранение ТОЛЬКО строки из файла
				CStdioFile oResultFile(filedlg.GetPathName(), CFile::modeRead);	//Открытие файла с режимом чтения
				oResultFile.ReadString(Cstr);
				inputDecryptionN = atoi(Cstr);
				oResultFile.ReadString(Cstr);
				inputDecryptionD = atoi(Cstr);

				oResultFile.Close();											//Закрыть
			}
			//Если DES
			else if (radioButtonNow == radioButtonDESencryption || radioButtonNow == radioButtonDESdecryption) {
				CString Cstr;													//Хранение ТОЛЬКО строки из файла
				CStdioFile oResultFile(filedlg.GetPathName(), CFile::modeRead);	//Открытие файла с режимом чтения
				oResultFile.ReadString(Cstr);
				oResultFile.Close();											//Закрыть
				DESinputKey = Cstr;
			}
		}
		UpdateData(false);											//Обновляем парметры
	}
}
//Кнопка СОХРАНЕНИЯ
void CEncoderInformationSecurityV2Dlg::OnBnClickedButton6()
{
	if (radioButtonNow != 0) {
		//Открываем окно сохранения файла
		CFileDialog filedlg(false);											//Создаем объект типа CFile diolog; сохранениие - false

		filedlg.m_pOFN->lpstrFilter = FileFilter;							 //Фильтр принимаемых файлов, только текст (Все файлы (*.*)\0*.*\0)Пример строки для этого параметра из MFC (3 шаблона):	"Bitmap files(*.bmp)\0*.bmp\0JPEG files(*.jpg)\0*.jpg\0All files(*.*)\0*.*\0\0"

		TCHAR WindowName[] = _T("Сохранение ключа");						//Название открывшегося окна
		filedlg.m_pOFN->lpstrTitle = WindowName;							//Передаем этот параметр в диалог

		//filedlg.m_pOFN->lpstrInitialDir = InitialPathDownload;				//Задаем начальную папку

		if (radioButtonNow == radioButtonXOR) {

			TCHAR StartName[_MAX_PATH] = _T("XORkey");						//Предложим название файла
			filedlg.m_pOFN->lpstrFile = StartName;

			//filedlg.DoModal();												//Создание окна диалога открытия файла

			if (filedlg.DoModal() == IDOK)										//filedlg.DoModal()-Создание окна диалога открытия файла, если по возращение все ок, то выводим файл
			{

				if (filedlg.m_pOFN->nFilterIndex == 1) {						//Под первым индеском фильтра стоит txt
					CStdioFile oResultFile(filedlg.GetPathName() + _T(".txt"),	//Открываем поток с приставкой формата
						CFile::modeCreate | CFile::modeReadWrite);					//Открытие файла с режимом создания и чтения записи
					oResultFile.WriteString(in_key);
					oResultFile.Close();										//Закрытие потока
				}
				if (filedlg.m_pOFN->nFilterIndex == 2) {						//Под первым индеском фильтра стоит all
					CStdioFile oResultFile(filedlg.GetPathName(),				//Открываем поток с приставкой формата
						CFile::modeCreate | CFile::modeReadWrite);				//Открытие файла с режимом создания и чтения записи
					oResultFile.WriteString(in_key);
					oResultFile.Close();										//Закрытие потока
				}
			}
		}
		else if (radioButtonNow == radioButtonRSAencryption) {
			TCHAR StartName[_MAX_PATH] = _T("RSAopenKey");						//Предложим название файла
			filedlg.m_pOFN->lpstrFile = StartName;

			//filedlg.DoModal();												//Создание окна диалога открытия файла

			if (filedlg.DoModal() == IDOK)										//filedlg.DoModal()-Создание окна диалога открытия файла, если по возращение все ок, то выводим файл
			{
				CString str;

				if (filedlg.m_pOFN->nFilterIndex == 1) {						//Под первым индеском фильтра стоит txt
					CStdioFile oResultFile(filedlg.GetPathName() + _T(".txt"),	//Открываем поток с приставкой формата
						CFile::modeCreate | CFile::modeReadWrite);					//Открытие файла с режимом создания и чтения записи
					str.Format("%u", inputEncryptionN);
					oResultFile.WriteString(str);
					str.Format("%u", inputEncryptionE);
					oResultFile.WriteString(_T("\r\n") + str);
					oResultFile.Close();										//Закрытие потока
				}

				if (filedlg.m_pOFN->nFilterIndex == 2) {						//Под первым индеском фильтра стоит all
					CStdioFile oResultFile(filedlg.GetPathName(),				//Открываем поток с приставкой формата
						CFile::modeCreate | CFile::modeReadWrite);				//Открытие файла с режимом создания и чтения записи
					str.Format("%u", inputEncryptionN);
					oResultFile.WriteString(str);
					str.Format("%u", inputEncryptionE);
					oResultFile.WriteString(_T("\r\n") + str);
					oResultFile.Close();										//Закрытие потока
				}
				
			}
		}
		else if (radioButtonNow == radioButtonRSAdecryption) {
			TCHAR StartName[_MAX_PATH] = _T("RSAcloseKey");						//Предложим название файла
			filedlg.m_pOFN->lpstrFile = StartName;

			//filedlg.DoModal();												//Создание окна диалога открытия файла

			if (filedlg.DoModal() == IDOK)										//filedlg.DoModal()-Создание окна диалога открытия файла, если по возращение все ок, то выводим файл
			{
				CString str;

				if (filedlg.m_pOFN->nFilterIndex == 1) {						//Под первым индеском фильтра стоит txt
					CStdioFile oResultFile(filedlg.GetPathName() + _T(".txt"),	//Открываем поток с приставкой формата
						CFile::modeCreate | CFile::modeReadWrite);					//Открытие файла с режимом создания и чтения записи
					str.Format("%u", inputDecryptionN);
					oResultFile.WriteString(str);
					str.Format("%u", inputDecryptionD);
					oResultFile.WriteString(_T("\r\n") + str);
					oResultFile.Close();										//Закрытие потока
				}

				if (filedlg.m_pOFN->nFilterIndex == 2) {						//Под первым индеском фильтра стоит all
					CStdioFile oResultFile(filedlg.GetPathName(),				//Открываем поток с приставкой формата
						CFile::modeCreate | CFile::modeReadWrite);				//Открытие файла с режимом создания и чтения записи
					str.Format("%u", inputDecryptionN);
					oResultFile.WriteString(str);
					str.Format("%u", inputDecryptionD);
					oResultFile.WriteString(_T("\r\n") + str);
					oResultFile.Close();										//Закрытие потока
				}
				
			}
		
		}
		else if (radioButtonNow == radioButtonDESencryption || radioButtonNow == radioButtonDESdecryption) {
			TCHAR StartName[_MAX_PATH] = _T("DESkey");						//Предложим название файла
			filedlg.m_pOFN->lpstrFile = StartName;

			//filedlg.DoModal();												//Создание окна диалога открытия файла

			if (filedlg.DoModal() == IDOK)										//filedlg.DoModal()-Создание окна диалога открытия файла, если по возращение все ок, то выводим файл
			{

				if (filedlg.m_pOFN->nFilterIndex == 1) {						//Под первым индеском фильтра стоит txt
					CStdioFile oResultFile(filedlg.GetPathName() + _T(".txt"),	//Открываем поток с приставкой формата
						CFile::modeCreate | CFile::modeReadWrite);					//Открытие файла с режимом создания и чтения записи
					oResultFile.WriteString(DESinputKey);
					oResultFile.Close();										//Закрытие потока
				}
				if (filedlg.m_pOFN->nFilterIndex == 2) {						//Под первым индеском фильтра стоит all
					CStdioFile oResultFile(filedlg.GetPathName(),				//Открываем поток с приставкой формата
						CFile::modeCreate | CFile::modeReadWrite);				//Открытие файла с режимом создания и чтения записи
					oResultFile.WriteString(DESinputKey);
					oResultFile.Close();										//Закрытие потока
				}
			}
		}
		UpdateData(false);
	}
}
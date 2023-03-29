
// Encoder.InformationSecurity.V2.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CEncoderInformationSecurityV2App:
// Сведения о реализации этого класса: Encoder.InformationSecurity.V2.cpp
//

class CEncoderInformationSecurityV2App : public CWinApp
{
public:
	CEncoderInformationSecurityV2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CEncoderInformationSecurityV2App theApp;

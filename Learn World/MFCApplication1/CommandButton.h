
#if !defined __COMMANDBUTTON_H_
#define __COMMANDBUTTON_H_


#include <afxwin.h> 
#include <afxext.h>
#include "stdafx.h"
#include "resource.h"
class CommandButton : public CButton
{
	DECLARE_DYNAMIC(CommandButton);
public:

	//constructors & OVERRIDDEN
	CommandButton(){}
	~CommandButton(){}
	CBitmap m_Bmp;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};

#endif
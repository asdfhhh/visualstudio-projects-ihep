// DlgProxy.h: ͷ�ļ�
//

#pragma once

class Ckeithley1Dlg;


// Ckeithley1DlgAutoProxy ����Ŀ��

class Ckeithley1DlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(Ckeithley1DlgAutoProxy)

	Ckeithley1DlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	Ckeithley1Dlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~Ckeithley1DlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(Ckeithley1DlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


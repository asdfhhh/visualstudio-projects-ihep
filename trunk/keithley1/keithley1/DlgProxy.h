// DlgProxy.h: 头文件
//

#pragma once

class Ckeithley1Dlg;


// Ckeithley1DlgAutoProxy 命令目标

class Ckeithley1DlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(Ckeithley1DlgAutoProxy)

	Ckeithley1DlgAutoProxy();           // 动态创建所使用的受保护的构造函数

// 属性
public:
	Ckeithley1Dlg* m_pDialog;

// 操作
public:

// 重写
	public:
	virtual void OnFinalRelease();

// 实现
protected:
	virtual ~Ckeithley1DlgAutoProxy();

	// 生成的消息映射函数

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(Ckeithley1DlgAutoProxy)

	// 生成的 OLE 调度映射函数

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


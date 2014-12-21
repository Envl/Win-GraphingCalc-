// Windows Final  Cal.cpp : 定义应用程序的入口点。
//

/*----------------------------------------Yaoooooooooooooooooooooooooooooo-----------------------------------------*/

#include "stdafx.h"
#include "resource.h"
#include "Windows Final  Cal.h"//其中包含的内容需要存在于回调函数后
//全局变量和函数前向声明都放入了头文件

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  在此放置代码。
	hBitmap = (HBITMAP)LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPNewBG));//主界面画刷句柄
	if (hBitmap == NULL)
	{
		MessageBox(NULL, TEXT("主界面位图加载失败"), TEXT("Error"), MB_ICONERROR);
		return 0;
	}
	
	MSG msg;
	HACCEL hAccelTable;
	
	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINDOWSFINALCAL, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSFINALCAL));

	// 主消息循环: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}


//
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground =(HBRUSH)GetStockObject(NULL_BRUSH);
		//(HBRUSH)CreatePatternBrush(hBitmap); //这是另一种方案
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm =  LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassEx(&wcex);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	Command = nCmdShow;//保存在全局变量中
	BITMAP bm;
	GetObject(hBitmap, sizeof(bm), &bm);
	int nWindowWidth = bm.bmWidth-233 ;//
	int nWindowHeight = bm.bmHeight; //在BMP图片原来尺寸基础上调整窗口宽高  
   HWND hWnd;
   //绝对定义cxChar cyChar的值 防止系统不同显示效果不可控
   cxChar = 8;
   cyChar = 8;
   hInst = hInstance; // 将实例句柄存储在全局变量中
   //ImmDisableIME(-1);//要求在在创建窗口前调用这个函数. 禁用输入法 需要添加 library  这句 #pragma comment(lib, "imm32.lib") 于是后来使用修改layout实现了.
   hWnd = CreateWindow(szWindowClass, szTitle, WS_MINIMIZEBOX|WS_POPUP ,
      150,  60,nWindowWidth, nWindowHeight, NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }
   //建立文本框显示算术表达式					//ES_RIGHT+BS_RIGHT共同实现了文字靠右居中。  不知为什么bsright是居中的效果
   hStaticText = CreateWindow(TEXT("STATIC"), TEXT(""), WS_CHILD | WS_VISIBLE |ES_RIGHT|BS_RIGHT,
	   6* cxChar, 4 * cyChar, 54 * cxChar, 8 * cyChar, hWnd, (HMENU)IDC_EDIT, hInst, NULL);
   //SetFocus(hStaticText);
   //建立基本按钮
   for (int i = 1; i <= 5; i++){
	   for (int j = 1; j <= 4; j++){
		   hwndButton[4 * i - 4 + j - 1] = CreateWindow(TEXT("BUTTON"), buttonText[4 * i - 4 + j - 1],
			   WS_CHILD | WS_VISIBLE |BS_PUSHBOX|BS_FLAT|BS_BOTTOM, j * 6* cxChar+248, cyChar*(1 + 6 * i)+70,
			   5 * cxChar, 5 * cyChar, hWnd, (HMENU)(4 * i - 4 + j), hInst, NULL);
	   };
   };
   for (int i = 1; i <= 4; i++){
	   for (int j = 1; j <= 4; j++){
		   hwndButton[20 + 4 * i - 4 + j - 1] = CreateWindow(TEXT("button"), buttonText[20 + 4 * i - 4 + j - 1],
			   WS_CHILD | WS_VISIBLE | BS_PUSHBOX|BS_FLAT|BS_BOTTOM, j  * 6 * cxChar, cyChar*(1 + 6 * i)+70,
			   5 * cxChar, 5 * cyChar, hWnd, (HMENU)(20 + 4 * i - 4 + j), hInst, NULL);
	   }
   }
   //画图按钮
   hwndButton[37] = CreateWindow(TEXT("button"), buttonText[36],
	   WS_CHILD | WS_VISIBLE | BS_PUSHBOX | BS_FLAT|BS_BOTTOM, 1 * 6 * cxChar, cyChar*(1 + 6 * 5) + 70,
	   11 * cxChar, 5 * cyChar, hWnd, (HMENU)(37), hInst, NULL);
   //About 按钮
   hwndButton[38] = CreateWindow(TEXT("button"), TEXT("About"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBOX | BS_FLAT|BS_BOTTOM, 3 * 6 * cxChar, cyChar*(1 + 6 * 5) + 70,
	   11 * cxChar, 5 * cyChar, hWnd, (HMENU)(38), hInst, NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static HDC s_hdcMem; //放置缩放后的位图  
	HBITMAP hbmp;
	BITMAP bm;
	HDC hdcTemp;
	TCHAR tmpChar;//用来键盘输入各种算术符号
	switch (message)
	{
	
	case WM_CREATE:
		//更改键盘布局,这样就是英文输入状态,就能接受键盘 key 和 chars消息了.
		LoadKeyboardLayout(TEXT("0x0409"), KLF_ACTIVATE | KLF_SETFORPROCESS);
		// 设置分层属性  
		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hWnd, RGB(5, 255, 255), 233, LWA_ALPHA | LWA_COLORKEY);
		{//这个代码块实现位图可缩放
			hdc = GetDC(hWnd);
			hdcTemp = CreateCompatibleDC(hdc);
			SelectObject(hdcTemp, hBitmap);

			// 得到窗口大小  
			int nWidth, nHeight;
			GetWindowSize(hWnd, &nWidth, &nHeight);

			// 创建与窗口大小相等且能容纳位图的HDC - s_hdcMem  
			s_hdcMem = CreateCompatibleDC(hdc);
			hbmp = CreateCompatibleBitmap(hdc, nWidth, nHeight);
			SelectObject(s_hdcMem, hbmp);

			// 将原位图缩放
			GetObject(hBitmap, sizeof(bm), &bm);
			StretchBlt(s_hdcMem, 0, 0, nWidth, nHeight, hdcTemp, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

			// 释放资源  
			DeleteDC(hdcTemp);
			ReleaseDC(hWnd, hdc);
		}
		break;

	case WM_LBUTTONDOWN: //当鼠标左键点击时可以拖曳窗口  
		SendMessage(hWnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
		break;
	
	case WM_ERASEBKGND: //在窗口背景中直接贴图  
		hdc = (HDC)wParam;
		int nWidth, nHeight;
		GetWindowSize(hWnd, &nWidth, &nHeight);
		BitBlt(hdc, 0, 0, nWidth, nHeight, s_hdcMem, 0, 0, SRCCOPY);
		return TRUE;
	case WM_COMMAND:
	
		wmId = LOWORD(wParam);
		
		if (computed)//这样实现接着使用上次的计算结果进行计算
			if (wmId == 4 || wmId == 8 || wmId == 12 || wmId == 16 || wmId == 28 || wmId == 36)
			{
			ZeroMemory(expression, lstrlen(expression));
			ZeroMemory(expression4Display, lstrlen(expression4Display));
			lstrcpy(expression, value);
			lstrcpy(expression4Display, value);
			computed = false;
			}
			else if (wmId == 20||wmId==37){
				computed = true;
			}
			else 
			{
				ZeroMemory(expression, lstrlen(expression)*sizeof(expression[0]));
				ZeroMemory(expression4Display, lstrlen(expression4Display)*sizeof(expression4Display[0]));
				SetWindowText(hStaticText, expression4Display);
				computed = false;
			}
			
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_ABOUT:  //IDM_ABOUT=38
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:  //Resource.h中定义了  IDM_EXIT=1  
			DestroyWindow(hWnd);
			break;
		case 2:
			ZeroMemory(expression, lstrlen(expression)*sizeof(expression[0]));
			ZeroMemory(expression4Display, lstrlen(expression4Display)*sizeof(expression4Display[0]));
			SetWindowText(hStaticText, expression4Display);
			computed = false;
			break;
		case 3://删除按钮
			//因为存到expression中的为 原来的expression+'/0' 所以  length不用减 1 
			if(expression[0] != '\0')//必须做这个检测,否则如果字符串为空,内存访问就会出错.
				expression[lstrlen(expression) - 1] = '\0';
			GetWindowText(hStaticText, expression4Display, GetWindowTextLength(hStaticText));
			SetWindowText(hStaticText, expression4Display);

			break;
		case 4:
				lstrcat(expression, TEXT("/"));
				lstrcat(expression4Display, TEXT("/"));
				SetWindowText(hStaticText, expression4Display);
			break;
		case 8:
			lstrcat(expression, TEXT("*"));
			//SetWindowText(hStaticText, expression);
			lstrcat(expression4Display, TEXT("*"));
			SetWindowText(hStaticText, expression4Display);
			break;
		case 5:case 6:case 7:case 9:case 10:case 11:case 12:
		case 13:case 14:case 15:case 16:case 17:case 18:case 28:
		case 30:case 31:case 32:case 33:case 34:case 35:
		case 36:
			lstrcat(expression, buttonText[wmId - 1]);
			//SetWindowText(hStaticText, expression);
			lstrcat(expression4Display, buttonText[wmId - 1]);
			SetWindowText(hStaticText, expression4Display);
			break;
		case 19:
			if (expression[lstrlen(expression)-1] != '.')
			{
				lstrcat(expression, TEXT("."));
				lstrcat(expression4Display, TEXT("."));
				SetWindowText(hStaticText, expression4Display);
			}
			break;
		case 20:
			flag4Drawing = false;//计算表达式结果，表明此时不在绘图
			
			//if (expression[0] == 'y')
				//PostMessage(hWnd, WM_COMMAND, 37, 1);  //画图只许用指定的快捷键，不能用enter，--------------Single Path ---------
			//else	
			
			if (computed){
				//compvalue();
				SetWindowText(hStaticText, value);
			}
			else{//SetWindowText(hStaticText, expression);
				lstrcat(expression, TEXT("#"));
				lstrcat(expression4Display, TEXT("="));
				SetWindowText(hStaticText, expression4Display);
				if (expressionCheck(expression)&&BracketCommonOperatorCheck(expression)){
					expressionRepair(expression);
					trans(GetWindowTextLength(hStaticText), expression);//以上函数来自 同名.h 头文件 转换成逆波兰式
					compvalue();
					if (!flag4Alert)//用来计算的式子检测没问题才会显示出来,否则就会显示之前 的错误信息
						SetWindowText(hStaticText, value);

					computed = true;
					//int a=0; 用来设置断点的
				}
				else{
					ZeroMemory(expression, lstrlen(expression)*sizeof(expression[0]));
					ZeroMemory(expression4Display, lstrlen(expression4Display)*sizeof(expression[0]));
					if (flag4BracketNotMatch)
					{
						SetWindowText(hStaticText, TEXT("左右括号数量不匹配"));
						flag4BracketNotMatch = false;
						computed = true;
					}
					else
						SetWindowText(hStaticText, TEXT("表达式有误"));
						computed = true;
				}
			}

			break;
		case 21:
			lstrcat(expression, TEXT("s("));
			//SetWindowText(hStaticText, expression);
			lstrcat(expression4Display, TEXT("sin("));
			SetWindowText(hStaticText, expression4Display);
			break;
		case 22:
			lstrcat(expression, TEXT("c("));
			//SetWindowText(hStaticText, expression);
			lstrcat(expression4Display, TEXT("cos("));
			SetWindowText(hStaticText, expression4Display);
			break;
		case 23:
			lstrcat(expression, TEXT("t("));
			//SetWindowText(hStaticText, expression);
			lstrcat(expression4Display, TEXT("tan("));
			SetWindowText(hStaticText, expression4Display);
			break;
		case 24:
			lstrcat(expression, TEXT("3.14159265358979"));
			//SetWindowText(hStaticText, expression);
			lstrcat(expression4Display, TEXT("π"));
			SetWindowText(hStaticText, expression4Display);
			break;
		case 25:
			lstrcat(expression, TEXT("n("));
			//SetWindowText(hStaticText, expression);
			lstrcat(expression4Display, TEXT("ln("));
			SetWindowText(hStaticText, expression4Display);
			break;
		case 26:
			lstrcat(expression, TEXT("G("));
			lstrcat(expression4Display, TEXT("lg("));
			SetWindowText(hStaticText, expression4Display);
			break;
		case 27:
			lstrcat(expression, TEXT("g("));
			lstrcat(expression4Display, TEXT("√("));
			SetWindowText(hStaticText, expression4Display);
			break;
		case 29://   y√x 这个按钮
			lstrcat(expression, TEXT("e("));
			//SetWindowText(hStaticText, expression);
			lstrcat(expression4Display, TEXT("√("));
			SetWindowText(hStaticText, expression4Display);
			
			break;
		case 37://画函数图象
			flag4Drawing = true;//此时在绘图
			if (!computed)
			lstrcat(expression, TEXT("#"));
			if (expression[0] == 'y')
			{
				//去除表达式中的 'y=' 这两个字符
				TCHAR tmpExpression[257] = { 0 };
				int movelen = lstrlen(expression) - 2;
				CopyMemory(tmpExpression, expression + 2, movelen*sizeof(expression[0]));
				ZeroMemory(expression, lstrlen(expression)*sizeof(expression[0]));
				CopyMemory(expression, tmpExpression, movelen*sizeof(expression[0]));
				ZeroMemory(tmpExpression, lstrlen(tmpExpression)*sizeof(tmpExpression[0]));
				expressionRepair(expression);//修复表达式中的问题
			}
			isTheFistTime = true;
			expressionCheck4Drawing(expression);
			BracketCommonOperatorCheck(expression);
			if (flag4Factorial||!flag4Check)
			{
				flag4Factorial = false;
				SetWindowText(hStaticText, TEXT("绘图时不能有阶乘,或者括号不匹配，或者是你的表达式输入错误"));
				computed = true;//为了能够按一下键就彻底清除
				flag4Check = false;
			}
			else
			CreateNewChildWindow(hWnd,hwnd4Drawing);
		
			break;
		default:
			SetFocus(hWnd);//焦点给主窗口hWnd   以让它接收键盘消息
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		if (wmId!=37)//点击画图按钮后  主窗口不获取焦点
			SetFocus(hWnd);

		break;

	case WM_CHAR:
		if (computed)//这样实现接着使用上次的计算结果进行计算
			if (wParam == '+' || wParam == '-' || wParam == '*' || wParam == '/' || wParam == '%' || wParam == '!')
			{
			ZeroMemory(expression, lstrlen(expression));
			ZeroMemory(expression4Display, lstrlen(expression4Display));
			lstrcpy(expression, value);
			lstrcpy(expression4Display, value);
			computed = false;
			}
			else if (wParam == '\r'){
				computed = true;
			}
			else if (wParam == 'd' || wParam == 'D' || wParam == 'h' || wParam == 'H' ){
				//什么也不做
			}
			else//如果是按其他的键,就清空表达式,重新接受新的表达式
			{
				ZeroMemory(expression, lstrlen(expression)*sizeof(expression[0]));
				ZeroMemory(expression4Display, lstrlen(expression4Display)*sizeof(expression4Display[0]));
				SetWindowText(hStaticText, expression4Display);
				computed = false;
			}
		for (int i = 0; i < (int)LOWORD(lParam); i++)
		{
			switch (wParam)
			{
			case'\b':   //backspace
				SendMessage(hWnd, WM_COMMAND, 3, 1);
				break;
			case '\x1B':                  // escape
				SendMessage(hWnd, WM_COMMAND, 2, 1);
				break;
			case 'd':case'D':case'h':case'H':
				PostMessage(hWnd, WM_COMMAND, 37, 1);
				break;
			case'1':case'2':case'3':case'4':case'5':case'6':
			case'7':case'8':case'9':case'0':
			case'(':case')':case'x':case'=':case'y':
			case'-':case'+':case'*':case'/':case'!':case'^':
			case'%':
				lstrcat(expression,(LPCWSTR	)&wParam);
				//SetWindowText(hStaticText, expression);
				lstrcat(expression4Display, (LPCWSTR)&wParam);
				SetWindowText(hStaticText, expression4Display);
				break;
			case'.':
				SendMessage(hWnd, WM_COMMAND, 19, 1);
				break;
			case'…'://中文字符中的^按钮
				tmpChar = '^';
				lstrcat(expression, &tmpChar);
				//SetWindowText(hStaticText, expression);
				lstrcat(expression4Display, &tmpChar);
				SetWindowText(hStaticText, expression4Display);
				break;
			case'！'://中文字符中的!
				tmpChar = '!';
				lstrcat(expression, &tmpChar);
				//SetWindowText(hStaticText, expression);
				lstrcat(expression4Display, &tmpChar);
				SetWindowText(hStaticText, expression4Display);
				break;
			case'（'://中文字符中的（
				tmpChar = '(';
				lstrcat(expression, &tmpChar);
				//SetWindowText(hStaticText, expression);
				lstrcat(expression4Display, &tmpChar);
				SetWindowText(hStaticText, expression4Display);
				break;
			case'）':	//中文字符中的）
				tmpChar = ')';
				lstrcat(expression, &tmpChar);
				//SetWindowText(hStaticText, expression);
				lstrcat(expression4Display, &tmpChar);
				SetWindowText(hStaticText, expression4Display);
				break;
			case'\n':case'\r':
				SendMessage(hWnd, WM_COMMAND, 20, 1);
				break;
			case'l':case'L':
				SendMessage(hWnd, WM_COMMAND, 26, 1);
					break;
			case'n':case'N':
				SendMessage(hWnd, WM_COMMAND, 25, 1);
				break;
			case's':case'S':
				SendMessage(hWnd, WM_COMMAND, 21, 1);
				break;
			case'c':case'C':
				SendMessage(hWnd, WM_COMMAND, 22, 1);
				break;
			case't':case'T':
				SendMessage(hWnd, WM_COMMAND, 23, 1);
				break;
			case'p':case'P':
				SendMessage(hWnd, WM_COMMAND, 24, 1);
				break;
			default:
				break;
			}
		}
		break;

	case WM_DESTROY:
		DeleteDC(s_hdcMem);
		xmove = 0;
		ymove = 0;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

LRESULT CALLBACK Wnd4DrawingProc(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT wndRect=RECT();
	GetClientRect(hwnd, &wndRect);
	ww = wndRect.right - wndRect.left;//窗口宽度
	int wh = wndRect.bottom - wndRect.top;//窗口高度
	
	static float d = 53;//x值域   初始为[-ww*2/53，ww*2/53]  ,53在我的电脑上是一厘米的像素个数  1600 X 900 分辨率 13.3英寸
	static POINT pt = { 0, 0 };//存放之前鼠标所在点
	static HDC s_hdcMem; //放置缩放后的位图  
	static HPEN pen4s_hdcMem;

	HBITMAP hbmp;

	static float floatReplacement4X;//画图时用来替换每一个'x'字符为数字字符
	static char BufferBuffer[24];//char转TCHAR用来中转的 由于sprintf_s不支持转成TCHAR
	static TCHAR tmpString[300] = { 0 };
	static HBRUSH hBmBrush;
	static int position4EachX;//画图时用来 计数x有几个
	static int Y4Print, X4Print, CenterWindowPixelY, CenterWindowPixelX;//画图要用的坐标
	static int formerX=0, formerY=0;//用来保存之前的x y
	static RECT rect4DashLine;//用来清空之前画的虚线;
	static bool flag4Drew=false;//是否画完了图像

	if (isTheFistTime){//WM_CREATE消息不响应  于是这样。
		
		pen4s_hdcMem = CreatePen(PS_SOLID, 1, RGB(204, 237, 199));
		hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAPBG));
		if (hBitmap == NULL)
		{
			MessageBox(NULL, TEXT("绘图界面位图加载失败"), TEXT("Error"), MB_ICONERROR);
			return 0;
		}

		hBmBrush = (HBRUSH)CreatePatternBrush(hBitmap);
		// 创建与窗口大小相等且能容纳位图的HDC - s_hdcMem  
		hdc = GetDC(hwnd);
		s_hdcMem = CreateCompatibleDC(hdc);
		hbmp = CreateCompatibleBitmap(hdc, ww, wh);
		ReleaseDC(hwnd,hdc);
		SelectObject(s_hdcMem, hbmp);//建立个绘图客户区等大的兼容DC

		InvalidateRect(hwnd, &wndRect, true);//无效化客户区 促使产生  WM_PAINT
		isTheFistTime = false;
	}

	//int id = GetWindowLong(hwnd, GWL_ID);//暂未用到
	switch (message)
	{
	case WM_SIZE:
		ww = wndRect.right - wndRect.left;//窗口宽度
		wh = wndRect.bottom - wndRect.top;//窗口高度
		hdc = GetDC(hwnd);
		hbmp = CreateCompatibleBitmap(hdc, ww, wh);
		ReleaseDC(hwnd, hdc);
		SelectObject(s_hdcMem, hbmp);//建立个绘图客户区等大的兼容DC
		DeleteObject(hbmp);

		break;
	case WM_PAINT:
	{

		//设置文本颜色以及文本背景颜色
		SetTextColor(s_hdcMem, RGB(204, 237, 199));
		SetBkMode(s_hdcMem, TRANSPARENT);

		SelectObject(s_hdcMem, pen4s_hdcMem);//GetStockObject(WHITE_PEN));

		FillRect(s_hdcMem, &wndRect, hBmBrush);//清空背景
		
		/*下面是计算部分,确定每一个x对应的y然后依次描点连线*/

		for (int a = 0; a < 10; a++)//确定表达式中哪些位置是x,要被替换为数字
		{
			PositionOfX[a] = -1;
		}
		 position4EachX = 0;
		for (int n = 0; n < lstrlen(expression); n++)
		{
			if (expression[n] == 'x'){
				PositionOfX[position4EachX] = n;
				position4EachX++;
			}
		}

		for (int i = 0; i <= Point_Sum; i++)
		{
			CopyMemory(Expression, expression, (lstrlen(expression))*sizeof(expression[0]));
			
			//x取不同的实际值，用来替代表达式中的x 
			floatReplacement4X = (float)(i - Point_Sum / 2 + xmove)/d;//这就是真正的物理x值   单位是厘米 

			//下面把数字转成字符
			ZeroMemory(tmpString, lstrlen(tmpString)*sizeof(tmpString[0]));//这句是必须的
			tmpString[0] = '(';
			sprintf_s(BufferBuffer, "%f", floatReplacement4X);
			CharToTchar(BufferBuffer, tcharReplacement4X);
			lstrcat(tmpString, tcharReplacement4X);
			lstrcat(tmpString, TEXT(")"));
			ZeroMemory(tcharReplacement4X,24*sizeof(expression[0]));//先清空它再 复制数字字符给他
			CopyMemory(tcharReplacement4X, tmpString, (lstrlen(tmpString))*sizeof(tmpString[0]));//这样tcharReplacement4X 就被括号包起来了

			for (int p = 9; p >=0; p--){
				if (PositionOfX[p] != -1)
					ReplaceString(Expression, tcharReplacement4X, PositionOfX[p]);
				//int a;//为了设置断点
			}
			expressionRepair(Expression);//x替换成数字后  再次 修复表达式中的问题  解决负数问题

			trans(lstrlen(Expression), Expression);
			compvalue();//至此，只是得到了原始的真实物理x，y坐标  分别是 ffloatReplacement4X   、  value
		
			/*下面开始绘图！！！！ 好！！*/
			
			//以窗口中心为原点的x 、y像素坐标
			 CenterWindowPixelX =(floatReplacement4X*d-xmove);		//这个是真的x坐标
				//i*ww / Point_Sum - Point_Sum / 2; //这个是不变的x坐标，只由窗口宽度决定  现已舍弃
			 CenterWindowPixelY = result*d;

			 X4Print = CenterWindowPixelX + ww / 2;//左上角为原点的 屏幕 x、y像素坐标
			 Y4Print =wh/2- CenterWindowPixelY-ymove;//y轴方向的拖动  由ymove体现出来 --------------------------------------------
			ZeroMemory(Expression, lstrlen(Expression)*sizeof(Expression[0]));//这句是必须的
			//int a = 0;//为了设置断点
			//以下这堆逻辑实现了，跳过 『 不在定义域内的点 』绘图。
			if (i == 0)
			{
				//MoveToEx(hdc, X4Print, Y4Print, NULL);//先画在内存DC中,于是舍弃
				MoveToEx(s_hdcMem, X4Print, Y4Print, NULL);
			}
			if (flag4DidntDraw)
			{
				flag4DidntDraw = false;
				MoveToEx(s_hdcMem, X4Print, Y4Print, NULL);
				//MoveToEx(hdc, X4Print, Y4Print, NULL);
			}
			if (flag4NotDraw){
				flag4DidntDraw = true;
				flag4NotDraw = false;
			}
			else{
				//LineTo(hdc, X4Print, Y4Print);
				LineTo(s_hdcMem, X4Print, Y4Print);
			}
		}

		//这是画出 x、y轴
		MoveToEx(s_hdcMem, 0, wh / 2 - ymove,NULL);
		LineTo(s_hdcMem, ww, wh / 2 - ymove);//x轴
		MoveToEx(s_hdcMem, ww/2-xmove, 0,NULL);
		LineTo(s_hdcMem, ww/2-xmove, wh);//y轴

		/*测试方法*/
		
		/*已清空*/
		/*------------------------------*/


		/*现行办法，正确有效，效果不好*/
		//给x轴标上坐标点,
		for (int n = 0; n <= ww / 106; n++)
		{
			// (n*120-ww/2+xmove)/d   这个数代表在屏幕上x为 n*d 这个像素点  实际对应的物理真实点的 x 坐标    

			//下面把数字转成字符
			sprintf_s(BufferBuffer, "%f", (n * 106 - ww / 2 + xmove) / d);
			CharToTchar(BufferBuffer, tmpString);

			TextOut(s_hdcMem, n * 106, wh / 2 - ymove + 3, tmpString, 8);//wh / 2 - ymove是 x轴的 像素纵坐标
			MoveToEx(s_hdcMem, n * 106, wh / 2 - ymove + 5, NULL);//画出刻度
			LineTo(s_hdcMem, n * 106, wh / 2 - ymove - 5);
		}
		//给y轴标上坐标点
		for (int n = 0; n <= wh / 106; n++)
		{
			// (n*120-ww/2+xmove)/d   这个数代表在屏幕上x为 n*d 这个像素点  实际对应的物理真实点的 x 坐标    

			//下面把数字转成字符
			sprintf_s(BufferBuffer, "%f", (float)(wh / 2 - ymove - n * 106) / d);
			CharToTchar(BufferBuffer, tmpString);

			TextOut(s_hdcMem, ww / 2 - xmove + 3, n * 106, tmpString, 8);//wh / 2 - ymove是 x轴的 像素纵坐标
			MoveToEx(s_hdcMem, ww / 2 - xmove + 5, n * 106, NULL);//画出刻度
			LineTo(s_hdcMem, ww / 2 - xmove - 5, n * 106);
		}

		//唯一一次绘图到屏幕 所以不会闪烁
		hdc = BeginPaint(hwnd, &ps);
		BitBlt(hdc, 0, 0, ww, wh, s_hdcMem, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
	}
	computed = true;
	flag4Drew = true;
		break;
	case WM_SYSCOLORCHANGE:
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN: 
		//flag4LBDown = true;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		break;
	//case WM_LBUTTONUP:
		//flag4LBDown = false;//wParam & MK_LBUTTON  这个就能代表鼠标左键按下
		//break;
	case WM_MOUSEMOVE:
	{
		if ((wParam & MK_LBUTTON))
		{
			xmove -=LOWORD(lParam) - pt.x;
			ymove -=HIWORD(lParam) - pt.y;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			if (pt.x!=0&&pt.y!=0)
				InvalidateRect(hwnd, &wndRect, true);//无效化客户区 促使产生  WM_PAINT
		}
		else
		{
			//输出鼠标所指位置的 真实 物理坐标
			char BufferBuffer[24];
			float xInRealWorld = (LOWORD(lParam) - ww / 2 + xmove) / d;//真实 物理世界 的 x、y
			float yInRealWorld =-( (HIWORD(lParam) - wh / 2 + ymove) / d);
			sprintf_s(BufferBuffer, "%f", xInRealWorld);
			CharToTchar(BufferBuffer, tcharReplacement4X);
			hdc = GetDC(hwnd);
			
			SetTextColor(hdc, RGB(204, 237, 199));
			SetBkColor(hdc, RGB(40, 40, 40));

			TextOut(hdc, 0, 0, TEXT("x= "), 3);
			TextOut(hdc, 16, 0, tcharReplacement4X, 8);
			/*以上输出鼠标所指真实物理 x坐标 ，以下输出y坐标*/
			sprintf_s(BufferBuffer, "%f", yInRealWorld);
			CharToTchar(BufferBuffer, tcharReplacement4X);
			TextOut(hdc, 0, 16, TEXT("y= "), 3);
			TextOut(hdc, 16, 16, tcharReplacement4X, 8);
			
				SetROP2(hdc, R2_XORPEN);
				DeleteObject(SelectObject(hdc, pen4s_hdcMem)); //pen4s_hdcMem));//设置虚线颜色
				
				//只有函数图像和坐标都画好以后才绘制辅助线,否则第一条辅助线会有残留
				/*下面逻辑实现了绘制辅助线,并且擦出之前绘制的辅助线*/
				if (!flag4Drew)
				{
					//竖直方向
					MoveToEx(hdc, formerX, formerY, NULL);
					LineTo(hdc, formerX, wh / 2 - ymove);
					//水平方向
					MoveToEx(hdc, formerX, formerY, NULL);
					LineTo(hdc, ww / 2 - xmove, formerY);
					flag4Drew = true;
				}
				if (flag4Drew)
				{
					//竖直方向
					MoveToEx(hdc, LOWORD(lParam), HIWORD(lParam), NULL);
					LineTo(hdc, LOWORD(lParam), wh / 2 - ymove);
					//水平方向
					MoveToEx(hdc, LOWORD(lParam), HIWORD(lParam), NULL);
					LineTo(hdc, ww / 2 - xmove, HIWORD(lParam));
					flag4Drew = false;
					//更新former x y
				}
					formerX = LOWORD(lParam);
					formerY = HIWORD(lParam);
				
			ReleaseDC(hwnd, hdc);
		}

		break;
	}
	case 0x020A://WM_MOUSEWHEEL
		//实现鼠标滚轮缩放大小
		if ((INT)wParam > 0)
			d *= 1.1;
		else
			d /= 1.1;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_CHAR:
		for (int i = 0; i < (int)LOWORD(lParam); i++)
		{
			switch (wParam)
			{
			case '\x1B':                  // escape
			{
				DestroyWindow(hwnd);
				for (int i = 0; i <= 9; i++){
					if (hwnd4Drawing[i] == hwnd){
						hwnd4Drawing[i] = NULL;
						for (int j = 9; j >=0; j--)
							if (hwnd4Drawing[j] != NULL)
							{
								SetFocus(hwnd4Drawing[j]);
								break;
							}
					}
				}
				break;
			}
			case '-':
				d /= 1.2;
				InvalidateRect(hwnd, &wndRect, true);//无效化客 户区 促使产生  WM_PAINT
				break;
			case '+':case '=':
				d *= 1.2;
				InvalidateRect(hwnd, &wndRect, true);//无效化客户区 促使产生  WM_PAINT
				break;
			case 'z':case 'c':
				xmove = 0;
				ymove = 0;//函数图象回到中心
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			default:
				break;
			}
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT://键盘移动函数图象
			xmove -= 20;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case VK_RIGHT:
			xmove += 20;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case VK_UP:
			ymove -= 20;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case VK_DOWN:
			ymove += 20;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		break;
	case WM_DESTROY:
		//CloseWindow(hwnd);//只是让窗口不显示  
		//关闭窗口时，背景位图换回去
		hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAPNewBG));//主界面画刷句柄，绘图界面共用
		if (hBitmap == NULL)
		{
			MessageBox(NULL, TEXT("主界面位图加载失败"), TEXT("Error"), MB_ICONERROR);
			return 0;
		}
		DeleteObject(hBmBrush);
		DeleteObject(pen4s_hdcMem);
		DestroyWindow(hwnd);
		isTheFistTime = true;
		xmove = 0; ymove = 0;
		return  WndProc(hwnd, WM_PAINT, wParam, lParam);

		break;
	}
	return  DefWindowProc(hwnd, message, wParam, lParam);
}


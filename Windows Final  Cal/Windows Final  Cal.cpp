// Windows Final  Cal.cpp : ����Ӧ�ó������ڵ㡣
//

/*----------------------------------------Yaoooooooooooooooooooooooooooooo-----------------------------------------*/

#include "stdafx.h"
#include "resource.h"
#include "Windows Final  Cal.h"//���а�����������Ҫ�����ڻص�������
//ȫ�ֱ����ͺ���ǰ��������������ͷ�ļ�

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  �ڴ˷��ô��롣
	hBitmap = (HBITMAP)LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAPNewBG));//�����滭ˢ���
	if (hBitmap == NULL)
	{
		MessageBox(NULL, TEXT("������λͼ����ʧ��"), TEXT("Error"), MB_ICONERROR);
		return 0;
	}
	
	MSG msg;
	HACCEL hAccelTable;
	
	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINDOWSFINALCAL, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSFINALCAL));

	// ����Ϣѭ��: 
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
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
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
		//(HBRUSH)CreatePatternBrush(hBitmap); //������һ�ַ���
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm =  LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassEx(&wcex);
}

//
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	Command = nCmdShow;//������ȫ�ֱ�����
	BITMAP bm;
	GetObject(hBitmap, sizeof(bm), &bm);
	int nWindowWidth = bm.bmWidth-233 ;//
	int nWindowHeight = bm.bmHeight; //��BMPͼƬԭ���ߴ�����ϵ������ڿ��  
   HWND hWnd;
   //���Զ���cxChar cyChar��ֵ ��ֹϵͳ��ͬ��ʾЧ�����ɿ�
   cxChar = 8;
   cyChar = 8;
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
   //ImmDisableIME(-1);//Ҫ�����ڴ�������ǰ�����������. �������뷨 ��Ҫ��� library  ��� #pragma comment(lib, "imm32.lib") ���Ǻ���ʹ���޸�layoutʵ����.
   hWnd = CreateWindow(szWindowClass, szTitle, WS_MINIMIZEBOX|WS_POPUP ,
      150,  60,nWindowWidth, nWindowHeight, NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }
   //�����ı�����ʾ�������ʽ					//ES_RIGHT+BS_RIGHT��ͬʵ�������ֿ��Ҿ��С�  ��֪Ϊʲôbsright�Ǿ��е�Ч��
   hStaticText = CreateWindow(TEXT("STATIC"), TEXT(""), WS_CHILD | WS_VISIBLE |ES_RIGHT|BS_RIGHT,
	   6* cxChar, 4 * cyChar, 54 * cxChar, 8 * cyChar, hWnd, (HMENU)IDC_EDIT, hInst, NULL);
   //SetFocus(hStaticText);
   //����������ť
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
   //��ͼ��ť
   hwndButton[37] = CreateWindow(TEXT("button"), buttonText[36],
	   WS_CHILD | WS_VISIBLE | BS_PUSHBOX | BS_FLAT|BS_BOTTOM, 1 * 6 * cxChar, cyChar*(1 + 6 * 5) + 70,
	   11 * cxChar, 5 * cyChar, hWnd, (HMENU)(37), hInst, NULL);
   //About ��ť
   hwndButton[38] = CreateWindow(TEXT("button"), TEXT("About"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBOX | BS_FLAT|BS_BOTTOM, 3 * 6 * cxChar, cyChar*(1 + 6 * 5) + 70,
	   11 * cxChar, 5 * cyChar, hWnd, (HMENU)(38), hInst, NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static HDC s_hdcMem; //�������ź��λͼ  
	HBITMAP hbmp;
	BITMAP bm;
	HDC hdcTemp;
	TCHAR tmpChar;//�����������������������
	switch (message)
	{
	
	case WM_CREATE:
		//���ļ��̲���,��������Ӣ������״̬,���ܽ��ܼ��� key �� chars��Ϣ��.
		LoadKeyboardLayout(TEXT("0x0409"), KLF_ACTIVATE | KLF_SETFORPROCESS);
		// ���÷ֲ�����  
		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hWnd, RGB(5, 255, 255), 233, LWA_ALPHA | LWA_COLORKEY);
		{//��������ʵ��λͼ������
			hdc = GetDC(hWnd);
			hdcTemp = CreateCompatibleDC(hdc);
			SelectObject(hdcTemp, hBitmap);

			// �õ����ڴ�С  
			int nWidth, nHeight;
			GetWindowSize(hWnd, &nWidth, &nHeight);

			// �����봰�ڴ�С�����������λͼ��HDC - s_hdcMem  
			s_hdcMem = CreateCompatibleDC(hdc);
			hbmp = CreateCompatibleBitmap(hdc, nWidth, nHeight);
			SelectObject(s_hdcMem, hbmp);

			// ��ԭλͼ����
			GetObject(hBitmap, sizeof(bm), &bm);
			StretchBlt(s_hdcMem, 0, 0, nWidth, nHeight, hdcTemp, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

			// �ͷ���Դ  
			DeleteDC(hdcTemp);
			ReleaseDC(hWnd, hdc);
		}
		break;

	case WM_LBUTTONDOWN: //�����������ʱ������ҷ����  
		SendMessage(hWnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
		break;
	
	case WM_ERASEBKGND: //�ڴ��ڱ�����ֱ����ͼ  
		hdc = (HDC)wParam;
		int nWidth, nHeight;
		GetWindowSize(hWnd, &nWidth, &nHeight);
		BitBlt(hdc, 0, 0, nWidth, nHeight, s_hdcMem, 0, 0, SRCCOPY);
		return TRUE;
	case WM_COMMAND:
	
		wmId = LOWORD(wParam);
		
		if (computed)//����ʵ�ֽ���ʹ���ϴεļ��������м���
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
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:  //IDM_ABOUT=38
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:  //Resource.h�ж�����  IDM_EXIT=1  
			DestroyWindow(hWnd);
			break;
		case 2:
			ZeroMemory(expression, lstrlen(expression)*sizeof(expression[0]));
			ZeroMemory(expression4Display, lstrlen(expression4Display)*sizeof(expression4Display[0]));
			SetWindowText(hStaticText, expression4Display);
			computed = false;
			break;
		case 3://ɾ����ť
			//��Ϊ�浽expression�е�Ϊ ԭ����expression+'/0' ����  length���ü� 1 
			if(expression[0] != '\0')//������������,��������ַ���Ϊ��,�ڴ���ʾͻ����.
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
			flag4Drawing = false;//������ʽ�����������ʱ���ڻ�ͼ
			
			//if (expression[0] == 'y')
				//PostMessage(hWnd, WM_COMMAND, 37, 1);  //��ͼֻ����ָ���Ŀ�ݼ���������enter��--------------Single Path ---------
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
					trans(GetWindowTextLength(hStaticText), expression);//���Ϻ������� ͬ��.h ͷ�ļ� ת�����沨��ʽ
					compvalue();
					if (!flag4Alert)//���������ʽ�Ӽ��û����Ż���ʾ����,����ͻ���ʾ֮ǰ �Ĵ�����Ϣ
						SetWindowText(hStaticText, value);

					computed = true;
					//int a=0; �������öϵ��
				}
				else{
					ZeroMemory(expression, lstrlen(expression)*sizeof(expression[0]));
					ZeroMemory(expression4Display, lstrlen(expression4Display)*sizeof(expression[0]));
					if (flag4BracketNotMatch)
					{
						SetWindowText(hStaticText, TEXT("��������������ƥ��"));
						flag4BracketNotMatch = false;
						computed = true;
					}
					else
						SetWindowText(hStaticText, TEXT("���ʽ����"));
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
			lstrcat(expression4Display, TEXT("��"));
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
			lstrcat(expression4Display, TEXT("��("));
			SetWindowText(hStaticText, expression4Display);
			break;
		case 29://   y��x �����ť
			lstrcat(expression, TEXT("e("));
			//SetWindowText(hStaticText, expression);
			lstrcat(expression4Display, TEXT("��("));
			SetWindowText(hStaticText, expression4Display);
			
			break;
		case 37://������ͼ��
			flag4Drawing = true;//��ʱ�ڻ�ͼ
			if (!computed)
			lstrcat(expression, TEXT("#"));
			if (expression[0] == 'y')
			{
				//ȥ�����ʽ�е� 'y=' �������ַ�
				TCHAR tmpExpression[257] = { 0 };
				int movelen = lstrlen(expression) - 2;
				CopyMemory(tmpExpression, expression + 2, movelen*sizeof(expression[0]));
				ZeroMemory(expression, lstrlen(expression)*sizeof(expression[0]));
				CopyMemory(expression, tmpExpression, movelen*sizeof(expression[0]));
				ZeroMemory(tmpExpression, lstrlen(tmpExpression)*sizeof(tmpExpression[0]));
				expressionRepair(expression);//�޸����ʽ�е�����
			}
			isTheFistTime = true;
			expressionCheck4Drawing(expression);
			BracketCommonOperatorCheck(expression);
			if (flag4Factorial||!flag4Check)
			{
				flag4Factorial = false;
				SetWindowText(hStaticText, TEXT("��ͼʱ�����н׳�,�������Ų�ƥ�䣬��������ı��ʽ�������"));
				computed = true;//Ϊ���ܹ���һ�¼��ͳ������
				flag4Check = false;
			}
			else
			CreateNewChildWindow(hWnd,hwnd4Drawing);
		
			break;
		default:
			SetFocus(hWnd);//�����������hWnd   ���������ռ�����Ϣ
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		if (wmId!=37)//�����ͼ��ť��  �����ڲ���ȡ����
			SetFocus(hWnd);

		break;

	case WM_CHAR:
		if (computed)//����ʵ�ֽ���ʹ���ϴεļ��������м���
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
				//ʲôҲ����
			}
			else//����ǰ������ļ�,����ձ��ʽ,���½����µı��ʽ
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
			case'��'://�����ַ��е�^��ť
				tmpChar = '^';
				lstrcat(expression, &tmpChar);
				//SetWindowText(hStaticText, expression);
				lstrcat(expression4Display, &tmpChar);
				SetWindowText(hStaticText, expression4Display);
				break;
			case'��'://�����ַ��е�!
				tmpChar = '!';
				lstrcat(expression, &tmpChar);
				//SetWindowText(hStaticText, expression);
				lstrcat(expression4Display, &tmpChar);
				SetWindowText(hStaticText, expression4Display);
				break;
			case'��'://�����ַ��еģ�
				tmpChar = '(';
				lstrcat(expression, &tmpChar);
				//SetWindowText(hStaticText, expression);
				lstrcat(expression4Display, &tmpChar);
				SetWindowText(hStaticText, expression4Display);
				break;
			case'��':	//�����ַ��еģ�
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

// �����ڡ������Ϣ�������
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
	ww = wndRect.right - wndRect.left;//���ڿ��
	int wh = wndRect.bottom - wndRect.top;//���ڸ߶�
	
	static float d = 53;//xֵ��   ��ʼΪ[-ww*2/53��ww*2/53]  ,53���ҵĵ�������һ���׵����ظ���  1600 X 900 �ֱ��� 13.3Ӣ��
	static POINT pt = { 0, 0 };//���֮ǰ������ڵ�
	static HDC s_hdcMem; //�������ź��λͼ  
	static HPEN pen4s_hdcMem;

	HBITMAP hbmp;

	static float floatReplacement4X;//��ͼʱ�����滻ÿһ��'x'�ַ�Ϊ�����ַ�
	static char BufferBuffer[24];//charתTCHAR������ת�� ����sprintf_s��֧��ת��TCHAR
	static TCHAR tmpString[300] = { 0 };
	static HBRUSH hBmBrush;
	static int position4EachX;//��ͼʱ���� ����x�м���
	static int Y4Print, X4Print, CenterWindowPixelY, CenterWindowPixelX;//��ͼҪ�õ�����
	static int formerX=0, formerY=0;//��������֮ǰ��x y
	static RECT rect4DashLine;//�������֮ǰ��������;
	static bool flag4Drew=false;//�Ƿ�����ͼ��

	if (isTheFistTime){//WM_CREATE��Ϣ����Ӧ  ����������
		
		pen4s_hdcMem = CreatePen(PS_SOLID, 1, RGB(204, 237, 199));
		hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAPBG));
		if (hBitmap == NULL)
		{
			MessageBox(NULL, TEXT("��ͼ����λͼ����ʧ��"), TEXT("Error"), MB_ICONERROR);
			return 0;
		}

		hBmBrush = (HBRUSH)CreatePatternBrush(hBitmap);
		// �����봰�ڴ�С�����������λͼ��HDC - s_hdcMem  
		hdc = GetDC(hwnd);
		s_hdcMem = CreateCompatibleDC(hdc);
		hbmp = CreateCompatibleBitmap(hdc, ww, wh);
		ReleaseDC(hwnd,hdc);
		SelectObject(s_hdcMem, hbmp);//��������ͼ�ͻ����ȴ�ļ���DC

		InvalidateRect(hwnd, &wndRect, true);//��Ч���ͻ��� ��ʹ����  WM_PAINT
		isTheFistTime = false;
	}

	//int id = GetWindowLong(hwnd, GWL_ID);//��δ�õ�
	switch (message)
	{
	case WM_SIZE:
		ww = wndRect.right - wndRect.left;//���ڿ��
		wh = wndRect.bottom - wndRect.top;//���ڸ߶�
		hdc = GetDC(hwnd);
		hbmp = CreateCompatibleBitmap(hdc, ww, wh);
		ReleaseDC(hwnd, hdc);
		SelectObject(s_hdcMem, hbmp);//��������ͼ�ͻ����ȴ�ļ���DC
		DeleteObject(hbmp);

		break;
	case WM_PAINT:
	{

		//�����ı���ɫ�Լ��ı�������ɫ
		SetTextColor(s_hdcMem, RGB(204, 237, 199));
		SetBkMode(s_hdcMem, TRANSPARENT);

		SelectObject(s_hdcMem, pen4s_hdcMem);//GetStockObject(WHITE_PEN));

		FillRect(s_hdcMem, &wndRect, hBmBrush);//��ձ���
		
		/*�����Ǽ��㲿��,ȷ��ÿһ��x��Ӧ��yȻ�������������*/

		for (int a = 0; a < 10; a++)//ȷ�����ʽ����Щλ����x,Ҫ���滻Ϊ����
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
			
			//xȡ��ͬ��ʵ��ֵ������������ʽ�е�x 
			floatReplacement4X = (float)(i - Point_Sum / 2 + xmove)/d;//���������������xֵ   ��λ������ 

			//���������ת���ַ�
			ZeroMemory(tmpString, lstrlen(tmpString)*sizeof(tmpString[0]));//����Ǳ����
			tmpString[0] = '(';
			sprintf_s(BufferBuffer, "%f", floatReplacement4X);
			CharToTchar(BufferBuffer, tcharReplacement4X);
			lstrcat(tmpString, tcharReplacement4X);
			lstrcat(tmpString, TEXT(")"));
			ZeroMemory(tcharReplacement4X,24*sizeof(expression[0]));//��������� ���������ַ�����
			CopyMemory(tcharReplacement4X, tmpString, (lstrlen(tmpString))*sizeof(tmpString[0]));//����tcharReplacement4X �ͱ����Ű�������

			for (int p = 9; p >=0; p--){
				if (PositionOfX[p] != -1)
					ReplaceString(Expression, tcharReplacement4X, PositionOfX[p]);
				//int a;//Ϊ�����öϵ�
			}
			expressionRepair(Expression);//x�滻�����ֺ�  �ٴ� �޸����ʽ�е�����  �����������

			trans(lstrlen(Expression), Expression);
			compvalue();//���ˣ�ֻ�ǵõ���ԭʼ����ʵ����x��y����  �ֱ��� ffloatReplacement4X   ��  value
		
			/*���濪ʼ��ͼ�������� �ã���*/
			
			//�Դ�������Ϊԭ���x ��y��������
			 CenterWindowPixelX =(floatReplacement4X*d-xmove);		//��������x����
				//i*ww / Point_Sum - Point_Sum / 2; //����ǲ����x���ֻ꣬�ɴ��ڿ�Ⱦ���  ��������
			 CenterWindowPixelY = result*d;

			 X4Print = CenterWindowPixelX + ww / 2;//���Ͻ�Ϊԭ��� ��Ļ x��y��������
			 Y4Print =wh/2- CenterWindowPixelY-ymove;//y�᷽����϶�  ��ymove���ֳ��� --------------------------------------------
			ZeroMemory(Expression, lstrlen(Expression)*sizeof(Expression[0]));//����Ǳ����
			//int a = 0;//Ϊ�����öϵ�
			//��������߼�ʵ���ˣ����� �� ���ڶ������ڵĵ� ����ͼ��
			if (i == 0)
			{
				//MoveToEx(hdc, X4Print, Y4Print, NULL);//�Ȼ����ڴ�DC��,��������
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

		//���ǻ��� x��y��
		MoveToEx(s_hdcMem, 0, wh / 2 - ymove,NULL);
		LineTo(s_hdcMem, ww, wh / 2 - ymove);//x��
		MoveToEx(s_hdcMem, ww/2-xmove, 0,NULL);
		LineTo(s_hdcMem, ww/2-xmove, wh);//y��

		/*���Է���*/
		
		/*�����*/
		/*------------------------------*/


		/*���а취����ȷ��Ч��Ч������*/
		//��x����������,
		for (int n = 0; n <= ww / 106; n++)
		{
			// (n*120-ww/2+xmove)/d   �������������Ļ��xΪ n*d ������ص�  ʵ�ʶ�Ӧ��������ʵ��� x ����    

			//���������ת���ַ�
			sprintf_s(BufferBuffer, "%f", (n * 106 - ww / 2 + xmove) / d);
			CharToTchar(BufferBuffer, tmpString);

			TextOut(s_hdcMem, n * 106, wh / 2 - ymove + 3, tmpString, 8);//wh / 2 - ymove�� x��� ����������
			MoveToEx(s_hdcMem, n * 106, wh / 2 - ymove + 5, NULL);//�����̶�
			LineTo(s_hdcMem, n * 106, wh / 2 - ymove - 5);
		}
		//��y����������
		for (int n = 0; n <= wh / 106; n++)
		{
			// (n*120-ww/2+xmove)/d   �������������Ļ��xΪ n*d ������ص�  ʵ�ʶ�Ӧ��������ʵ��� x ����    

			//���������ת���ַ�
			sprintf_s(BufferBuffer, "%f", (float)(wh / 2 - ymove - n * 106) / d);
			CharToTchar(BufferBuffer, tmpString);

			TextOut(s_hdcMem, ww / 2 - xmove + 3, n * 106, tmpString, 8);//wh / 2 - ymove�� x��� ����������
			MoveToEx(s_hdcMem, ww / 2 - xmove + 5, n * 106, NULL);//�����̶�
			LineTo(s_hdcMem, ww / 2 - xmove - 5, n * 106);
		}

		//Ψһһ�λ�ͼ����Ļ ���Բ�����˸
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
		//flag4LBDown = false;//wParam & MK_LBUTTON  ������ܴ�������������
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
				InvalidateRect(hwnd, &wndRect, true);//��Ч���ͻ��� ��ʹ����  WM_PAINT
		}
		else
		{
			//��������ָλ�õ� ��ʵ ��������
			char BufferBuffer[24];
			float xInRealWorld = (LOWORD(lParam) - ww / 2 + xmove) / d;//��ʵ �������� �� x��y
			float yInRealWorld =-( (HIWORD(lParam) - wh / 2 + ymove) / d);
			sprintf_s(BufferBuffer, "%f", xInRealWorld);
			CharToTchar(BufferBuffer, tcharReplacement4X);
			hdc = GetDC(hwnd);
			
			SetTextColor(hdc, RGB(204, 237, 199));
			SetBkColor(hdc, RGB(40, 40, 40));

			TextOut(hdc, 0, 0, TEXT("x= "), 3);
			TextOut(hdc, 16, 0, tcharReplacement4X, 8);
			/*������������ָ��ʵ���� x���� ���������y����*/
			sprintf_s(BufferBuffer, "%f", yInRealWorld);
			CharToTchar(BufferBuffer, tcharReplacement4X);
			TextOut(hdc, 0, 16, TEXT("y= "), 3);
			TextOut(hdc, 16, 16, tcharReplacement4X, 8);
			
				SetROP2(hdc, R2_XORPEN);
				DeleteObject(SelectObject(hdc, pen4s_hdcMem)); //pen4s_hdcMem));//����������ɫ
				
				//ֻ�к���ͼ������궼�����Ժ�Ż��Ƹ�����,�����һ�������߻��в���
				/*�����߼�ʵ���˻��Ƹ�����,���Ҳ���֮ǰ���Ƶĸ�����*/
				if (!flag4Drew)
				{
					//��ֱ����
					MoveToEx(hdc, formerX, formerY, NULL);
					LineTo(hdc, formerX, wh / 2 - ymove);
					//ˮƽ����
					MoveToEx(hdc, formerX, formerY, NULL);
					LineTo(hdc, ww / 2 - xmove, formerY);
					flag4Drew = true;
				}
				if (flag4Drew)
				{
					//��ֱ����
					MoveToEx(hdc, LOWORD(lParam), HIWORD(lParam), NULL);
					LineTo(hdc, LOWORD(lParam), wh / 2 - ymove);
					//ˮƽ����
					MoveToEx(hdc, LOWORD(lParam), HIWORD(lParam), NULL);
					LineTo(hdc, ww / 2 - xmove, HIWORD(lParam));
					flag4Drew = false;
					//����former x y
				}
					formerX = LOWORD(lParam);
					formerY = HIWORD(lParam);
				
			ReleaseDC(hwnd, hdc);
		}

		break;
	}
	case 0x020A://WM_MOUSEWHEEL
		//ʵ�����������Ŵ�С
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
				InvalidateRect(hwnd, &wndRect, true);//��Ч���� ���� ��ʹ����  WM_PAINT
				break;
			case '+':case '=':
				d *= 1.2;
				InvalidateRect(hwnd, &wndRect, true);//��Ч���ͻ��� ��ʹ����  WM_PAINT
				break;
			case 'z':case 'c':
				xmove = 0;
				ymove = 0;//����ͼ��ص�����
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
		case VK_LEFT://�����ƶ�����ͼ��
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
		//CloseWindow(hwnd);//ֻ���ô��ڲ���ʾ  
		//�رմ���ʱ������λͼ����ȥ
		hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAPNewBG));//�����滭ˢ�������ͼ���湲��
		if (hBitmap == NULL)
		{
			MessageBox(NULL, TEXT("������λͼ����ʧ��"), TEXT("Error"), MB_ICONERROR);
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


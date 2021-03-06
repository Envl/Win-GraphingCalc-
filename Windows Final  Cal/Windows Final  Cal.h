#pragma once

#include<stdlib.h>
#include<stdio.h>
#include<stack>
#include<math.h>
#include<string.h>
#define max1 200
#define Point_Sum 2000//最后决定改成2000,毕竟大家分辨率都不高
#define MAX_LOADSTRING 100

// 全局变量: 
int availableAmount;
HBITMAP  hBitmap;//主界面位图句柄
HINSTANCE hInst;								// 当前实例
HWND hStaticText;//计算器的 显示器
HWND hwnd4Drawing[10];//用来绘图的子窗口的句柄。 最高支持10个
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
TCHAR value[24] = { '0' };  //用来存储计算结果
TCHAR Expression[257] = { 0 };//i每变化一次 即每循环一次 把原版未作改变的expression 复制给它
TCHAR tcharReplacement4X[24] = { 0 };//定义并申请输入缓冲区空间
TCHAR expression[512] = { '0#' };//存储表达式中内容
TCHAR expression4Display[512] = { '0' };//存储用于显示的表达式

double result = 0;//用来存储计算结果的数值
int xmove = 0;//鼠标拖动的x，y方向移动的值
int ymove = 0;
int ww = 0;//窗口宽度
int wh = 0;//窗口宽度
int PositionOfX[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };//表达式中有x的位置
int cxChar;//每个字符的平均宽高,但后来使用了定值
int cyChar;
int Command;//全局保存 nCmdShow
char ex[max1];/*存储后缀表达式*/

bool flag4Check = true;//表达式检测是否通过
bool isTheFistTime = true;//判断是否开始新的绘图  以决定是否invalidateRect
bool flag4DidntDraw = false;
bool flag4NotDraw = true;//x值不能取的时候不绘图
bool flag4Drawing = false;//代表正在绘图
bool computed = true;//标志 是否已经计算过表达式
bool flag4TAN = false;//tan函数
bool flag4Factorial = false;//表达式里面是否有 阶乘，若有，则不支持绘图
bool flag4NotExistNumber;//表达式中没有数字
bool flag4Alert;//如果不在值域内，不能除以0等等 此时flag就等于true
bool flag4BracketNotMatch = false;//左右括号不匹配flag   不匹配就是true

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Wnd4DrawingProc(HWND, UINT, WPARAM, LPARAM);
void GetWindowSize(HWND hwnd, int *pnWidth, int *pnHeight);
	/*----------------------------------------Yaoooooooooooooo---------------------------------------------------------------------------------*/

TCHAR*  buttonText[] = {
	TEXT("关"), TEXT("C"), TEXT("←"), TEXT("÷"),//0--4号按钮
	TEXT("7"), TEXT("8"), TEXT("9"), TEXT("x"),
	TEXT("4"), TEXT("5"), TEXT("6"), TEXT("-"),
	TEXT("1"), TEXT("2"), TEXT("3"), TEXT("+"),
	TEXT("0"), TEXT("000"), TEXT("."), TEXT("="),//以上是1到20号按钮
	TEXT("sin"), TEXT("cos"), TEXT("tan"), TEXT("PI"),//但是要注意  这里编号从1开始
	TEXT("ln"), TEXT("log"), TEXT("√x"), TEXT("%"),
	TEXT("y√x"), TEXT("("), TEXT(")"), TEXT("^"),
	TEXT("x"), TEXT("y"), TEXT("="), TEXT("!"),//32--->35号按钮
	TEXT("画图"),
	TEXT("g"), TEXT("G"), TEXT("e"), TEXT("n")//这些不是按钮，是用来给checkExpression比对表达式是否正确的
};
#define NUM (sizeof buttonText / sizeof buttonText[0])
HWND hwndButton[NUM];//每个按钮的句柄

//检测各种省略乘号 情况    以及在负数前加个0
void expressionRepair(TCHAR* str){
	int i = 0;
	int len;
	int moveLen;
	TCHAR tmpExpression[518] = { 0 };
	TCHAR tmpChar = '\0';
	TCHAR tmpTail[512] = { 0 };

	lstrcat(str, &tmpChar);
	while (str[i] != '#')
	{
		if (i == 0){
			if (str[i] == '-'||str[i]=='+')
			{
				ZeroMemory(tmpExpression, lstrlen(tmpExpression)*sizeof(tmpExpression[0]));

				len = lstrlen(str);
				MoveMemory(tmpExpression, str, len*sizeof(str[0]));
				str[0] = '0';
				//str[1] = '\0';
				MoveMemory(str + 1, tmpExpression, len*sizeof(str[0]));
				//lstrcat(str,tmpExpression);
			}
		}
		else if ((str[i] == '-' ||str[i] == '+' )&& (str[i - 1] == '^' || str[i - 1] == '('))
		{
			//通过操作内存 插入一个东西在  第i个 位置
			//这里是插入0在负号前面实现负数的运算
			ZeroMemory(tmpTail, lstrlen(tmpTail)*sizeof(tmpTail[0]));
			moveLen = lstrlen(str + i);
			MoveMemory(tmpTail, str + i, moveLen*sizeof(str[0]));
			str[i] = '0';
			MoveMemory(str + i + 1, tmpTail, moveLen*sizeof(str[0]));
			//lstrcat(str, tmpTail);
			//	int a = 1; //为了设置断点用的

		}
		//在！后面跟着一个数字的话，给他们之间加入一个 *
		else if (str[i] == '!'&&str[i + 1] >= '0'&&str[i + 1] <= '9')
		{
			ZeroMemory(tmpTail, lstrlen(tmpTail)*sizeof(tmpTail[0]));
			moveLen = lstrlen(str + i);
			MoveMemory(tmpTail, str + i + 1, moveLen*sizeof(str[0]));
			str[i + 1] = '*';
			MoveMemory(str + i + 2, tmpTail, moveLen*sizeof(str[0]));
			//int a = 1;//为了设置断点用的
		}
		//sin  cos  tan ln lg 情况  没有乘号
		else if ((str[i] == 's' || str[i] == 'c' || str[i] == 't' || str[i] == 'g' || str[i] == 'n' || str[i] == 'G' || str[i] == 'x' || str[i] == '(') &&((str[i-1]=='x')|| (str[i - 1] >= '0'&&str[i - 1] <= '9')))
		{
			ZeroMemory(tmpTail, lstrlen(tmpTail)*sizeof(tmpTail[0]));
			moveLen = lstrlen(str + i);
			MoveMemory(tmpTail, str + i, moveLen*sizeof(str[0]));
			str[i] = '*';
			MoveMemory(str + i + 1, tmpTail, moveLen*sizeof(str[0]));
			//	int a = 1;//为了设置断点用的
		}
		i++;
	}
}


//建立绘函数图像的子窗口
void CreateNewChildWindow(HWND hWND, HWND* h4ChildWND){
	if (expression4Display[0] != 'y' || expression4Display[1] != '=' || !flag4Check)
	{
		flag4Check = FALSE;
		expression[0] = '\0';
		ZeroMemory(expression4Display, lstrlen(expression4Display)*sizeof(expression4Display[0]));
		lstrcat(expression4Display, TEXT("输入有误，请这样输入函数: y=f(x)      可以直接开始输入函数"));
		SetWindowText(hStaticText, expression4Display);
		computed = true;
		flag4Check = true;
		SetFocus(hWND);
	}
	else for (int i = 0; i < 10; i++)
	{
		TCHAR DrawWndTitle[50] = {0};
		lstrcpy(DrawWndTitle, expression4Display);
		lstrcat(DrawWndTitle, TEXT("  的图像，按ESC关闭"));
		if (h4ChildWND[i] == 0){

			h4ChildWND[i] = CreateWindow(szWindowClass, DrawWndTitle, WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT,700,500, NULL, NULL, hInst, NULL);

			ShowWindow(h4ChildWND[i], Command);
			RECT tmpRect;
			GetClientRect(h4ChildWND[i], &tmpRect);
			InvalidateRect(h4ChildWND[i], &tmpRect, true);
			UpdateWindow(h4ChildWND[i]);
			SetWindowLong(hwnd4Drawing[i], GWL_WNDPROC, (LONG)Wnd4DrawingProc);
			break;
		}
	}
}

//用来检测是否连续的运算符后面没有跟数字 比如sinsin 这样后面没有数字就返回false
void operatorInfiniteCheck(TCHAR* str,int i)
{
	
	if (str[i] == '#')
		flag4Check = false;
	else if (str[i] <= '9'&&str[i] >= '0')
		flag4Check = true;
		else if (!(str[i] <= '9'&&str[i] >= '0'))
			operatorInfiniteCheck(str, ++i);

}

//检测括号是否匹配
//是否有无论如何都  不准连续  的两个运算符
bool BracketCommonOperatorCheck(TCHAR* str)
{
	int lBracketCounter = 0;
	int rBracketCounter = 0;
	int i=0;
	while (str[i] != '#')
	{
		//画图时 表达式等号右边不允许有 y/= 存在
		if (str[i] == 'y' || str[i] == '=')
		{
			flag4Check = false;
			return FALSE;
		}
		if (str[i] == '(')
			lBracketCounter++;
		if (str[i] == ')')
			rBracketCounter++;
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
			str[i] == '^' || str[i] == '%'  || str[i] == '.')
		{
			if (str[i+1] == '+' || str[i+1] == '-' || str[i+1] == '*' || str[i+1] == '/' ||
				str[i+1] == '^' || str[i+1] == '%' || str[i+1] == '!' || str[i+1] == '.')
				flag4Check = false;
		}
		i++;
	}
	if (lBracketCounter != rBracketCounter)//左右括号不匹配就报错
	{
		flag4Check = false;
		flag4BracketNotMatch = true;
	}
	return flag4Check;
}

//检查表达式是否有问题    V1---其中的字符是否有问题
//这是给普通计算用的
bool expressionCheck(TCHAR* str){
	int i = 0;
	
	flag4NotExistNumber = true;
	while (str[i] != '#')
	{
		if (str[i] >= '0'&&str[i] <= '9')
			flag4NotExistNumber = false;

		operatorInfiniteCheck(str, i);
		
		if (!flag4Check)
			return FALSE;
		/*------------------------------------------*/
		flag4Check = false;
		for (int j = 0; j < NUM; j ++ ){
			if (str[i] == '!')
				flag4Factorial = true;
			if (str[i] == *buttonText[j]&&(str[i]!='x'&&str[i]!='y'&&str[i]!='=')){
				flag4Check = true;
				return TRUE;
			}
		}
		if (flag4NotExistNumber)
		{
			flag4Check = false;
		}
		if (!flag4Check){
			return FALSE;
		}
		i++;
	}

	return flag4Check;
}


bool expressionCheck4Drawing(TCHAR* str){//这是给函数绘图用的
	int i = 0;
	while (str[i] != '#'){
		//对应的第  i  个字符是否存在于buttonText中   false代表不存在
		flag4Check = false;

		for (int j = 0; j < NUM; j++)
		{
			if (str[i] == *buttonText[j])
			{
				flag4Check = true;
				return TRUE;
			}
		}

		if (!flag4Check)
		{
			return FALSE;
		}
		i++;
	}

	return flag4Check;
}

//获取窗口大小信息
void GetWindowSize(HWND hwnd, int *pnWidth, int *pnHeight)
{
	RECT rc;
	GetWindowRect(hwnd, &rc);
	*pnWidth = rc.right - rc.left;
	*pnHeight = rc.bottom - rc.top;
}


//char转成TCHAR
void CharToTchar(const char * _char, TCHAR * tchar)
{
	int iLength;

	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

//函数ReplaceString(destination,insertion,length,position)
//通过操作内存 插入一个东西在  第j个 位置 会把第 i 个东西去掉 然后取代它
void ReplaceString(TCHAR* destination,TCHAR*  insertion,int position){
			int length = lstrlen(insertion);//要用来替换的字符串的长度

			TCHAR tmpTail[512] = { 0 };//用来保存插入地方以后的部分
			int moveLen = lstrlen(destination+position+1);//position以后的都move走
			MoveMemory(tmpTail, destination+position + 1, moveLen*sizeof(destination[0]));
			MoveMemory(destination+position, insertion, length*sizeof(destination[0]));
			MoveMemory(destination + position+length, tmpTail, moveLen*sizeof(destination[0]));
			ZeroMemory(tmpTail, lstrlen(tmpTail));
}
	
/*将算术表达式转化为后缀表达式*/
void trans(int length,TCHAR* str)
{
	char stack[max1]={0};/*作为栈使用*/
	char ch;
	int sum, i,  t, top = 0;
	i = length;
	sum = i;
	t = 1; i = 0;
	ch = str[i]; i++;
	//
	while (ch != '#')
	{
		if (top >= 0)
		switch (ch)
		{
		case'(':	 /*判定为左括号*/
			top++; 
			if (top >= 0)
				stack[top] = ch;
			break;

		case')':	/*判定为右括号*/
			if (top >= 0)
				while (stack[top] != '(')
			{
				if (top >= 0)
					ex[t] = stack[top]; top--; t++;
			}
			top--;
			break;

		case'+':	/*判定为加减号*/
		case'-':
			while (top != 0 && stack[top] != '(')
			{
				ex[t] = stack[top];
				top--;
				t++;
			}
			top++;
			stack[top] = ch;
			break;

		case'*':	/*判定为乘除号*/
		case'/':
		case'%':
			while (stack[top] == '*' || stack[top] == '/' || stack[top] == '%' || stack[top] == 'g' || stack[top] == '^'
				|| stack[top] == 's' || stack[top] == 'c' || stack[top] == 't' || stack[top] == 'G'
				|| stack[top] == 'n' || stack[top] == 'e' || stack[top] == '!')      /*优先级大于等于'*'，'/' ，下同 */
			{
				ex[t] = stack[top];
				top--;
				t++;
			}
			top++;
			stack[top] = ch;
			break;

		case'^':		 //计算x^y 
		case'e':		//计算y√x		   
			while (stack[top] == '^' || stack[top] == 'e')
			{
				ex[t] = stack[top];
				top--;
				t++;
			}
			top++;
			stack[top] = ch;
			break;

		case'!':		//计算阶乘   
			while (stack[top] == '!')
			{
				ex[t] = stack[top];
				top--;
				t++;
			}
			top++;
			stack[top] = ch;
			break;

		case'g':		//计算√x
		case's':		//计算sin x
		case'c':		//计算cos x
		case't':		//计算tan x
		case'n':		//计算ln x
		case'G':		//计算lg x

			while (stack[top] == 'g' || stack[top] == 's' || stack[top] == 'c' || stack[top] == 't'
				|| stack[top] == 'G' || stack[top] == 'n')
			{
				ex[t] = stack[top];
				top--;
				t++;
			}
			top++;
			stack[top] = ch;
			break;

		case' ':break;

		default:
			while (((ch >= '0') && (ch <= '9')) || (ch == '.'))
			{/*判定为数字*/
				ex[t] = ch; t++;
				ch = str[i]; i++;
			}
			i--;
			ex[t] = ' '; t++;
		}
		ch = str[i]; i++;
	}
	while (top != 0)
	{
		ex[t] = stack[top];
		t++; top--;
	}
	ex[t] = ' ';
	
}

/*计算后缀表达式的值*/
void compvalue()
{
	flag4Alert = false;//每次进入函数都要改成初始状态 false
	double stack[max1] = { 0 }, d, f;/*作为栈使用*/
	char ch;
	int t = 1, top = 0;/*t为ex下标，top为stack下标*/
	ch = ex[t]; t++;
	while (ch != ' ')
	{
		switch (ch)
		{
		case'+':			
			if (top >= 1)
			stack[top - 1] = stack[top - 1] + stack[top];
			top--;
			break;
		case'-':
			//top++;
			stack[top - 1] = stack[top - 1] - stack[top];
			top--;
			break;
		case'*':
			stack[top - 1] = stack[top - 1] * stack[top];
			top--;
			break;
		case'/':
			if (stack[top] != 0)
				stack[top - 1] = stack[top - 1] / stack[top];
			else
			{
				//printf("\n\t除零错误!\n");
				if (!flag4Drawing)//在绘图时就不进行这个操作了
					SetWindowText(hStaticText, TEXT("算式在除法部分有误"));
				flag4Alert = true;
				flag4Check = false;
				flag4NotDraw = true;//代表不要绘图
			//	exit(0);/*异常退出*/
			}
			top--;
			break;
		case'%':
			stack[top - 1] = fmod(stack[top - 1], stack[top]);
			top--;
			break;
		case'g':
			if (stack[top] >= 0)
				stack[top] = sqrt(stack[top]);
			else
			{
				if (!flag4Drawing)//在绘图时就不进行这个操作了
					SetWindowText(hStaticText, TEXT("不能给负数开根号"));
				flag4Alert = true;
				flag4Check = false;
				flag4NotDraw = true;
			}
			//top--;
			break;
		case's':
			stack[top] = sin(stack[top]);
			//top--;
			break;
		case'c':
			stack[top] = cos(stack[top]);
			//top--;
			break;
		case't':
			stack[top] = tan(stack[top]);
			flag4TAN = true;
			//top--;
			break;
		case'G':
			if (stack[top]>0)
				stack[top] = log10(stack[top]);
			else
			{
				if (!flag4Drawing)//在绘图时就不进行这个操作了
					SetWindowText(hStaticText, TEXT("不能是负数"));
				flag4Alert = true;
				flag4Check = false;
				flag4NotDraw = true;
			}
			//top--;
			break;
		case'n':
			if (stack[top]>0)
				stack[top] = log(stack[top]);
			else
			{
				if (!flag4Drawing)//在绘图时就不进行这个操作了
					SetWindowText(hStaticText, TEXT("不能是负数"));
				flag4Alert = true;
				flag4Check = false;
				flag4NotDraw = true;
			}
			//top--;
			break;
		case'^':
		{
			stack[top - 1] = pow(stack[top - 1], stack[top]);
			top--;
			break;
		}
		case'e':
			if (stack[top]>0)
				stack[top - 1] = pow(stack[top], 1 / stack[top-1]);
			else
			{
				if (!flag4Drawing)//在绘图时就不进行这个操作了
					SetWindowText(hStaticText, TEXT("不能给负数开根号"));
				flag4Alert = true;
				flag4Check = false;
				flag4NotDraw = true;
			}
			top--;
			break;
		case'!':
		{
			if (stack[top] - int(stack[top]) != 0)
			{
				//printf("\n\t不是整数!\n");
				if (!flag4Drawing)//在绘图时就不进行这个操作了
					SetWindowText(hStaticText, TEXT("阶乘前面不是整数！"));
				flag4Alert = false;
				flag4Check = false;
				flag4NotDraw = true;
				//exit(1);/*异常退出*/
			}
			double sum = 1;
			for (int i = 0; i < stack[top]; i++)
			{
				sum = sum * (stack[top] - i);
			}
			stack[top] = sum;
			//top--;
			break;
		}
		default:
			d = 0, f = 0;
			int count = 0;
			bool a = false;
			while (((ch >= '0') && (ch <= '9')) || (ch == '.'))
			{
				if ((ch == '.')){
					ch = ex[t++];
					a = true;
				}
				d = 10 * d + ch - '0';/*将数字字符转化为对应的数值*/
				ch = ex[t]; t++;
				if (a) count++;
			}
			top++;
			stack[top] = d / pow(10, count);
		}
		ch = ex[t];
		t++;
	}

	if (top >= 0)
		result = stack[top];
	
	if (result == -0.000000)
		flag4NotDraw = true;
	//下面行把数字转成字符
	TCHAR szBuffer[64];//定义并申请输入缓冲区空间
	char BufferBuffer[64];
	if (top >= 0)
		if (stack[top] == -9.2559631349317831e+061)//处理数值越界
	{
		if (top >= 0)
			stack[top] = 0;
		result = 0;
		computed = true;
	}
	sprintf_s(BufferBuffer, "%.10lf", stack[top]);//小数点后14位是极限,否则就会有9-0.332=8.667999999的问题了.  高精度算法暂时不搞
	CharToTchar(BufferBuffer, szBuffer);
	if (szBuffer[2] == '.'&&szBuffer[3] == '#')//这 有待处理 这是数值越界的情况
		flag4NotDraw = true;
	if (value[0] != '\0'&&expression[0]!='\0')
	{
		ZeroMemory(value, lstrlen(value)*sizeof(value[0]));
	}

	availableAmount=lstrlen(szBuffer);//有效数字的位数
	//if ((int)result-result!=0)//只有结果不是整数时才处理,否则会误把整数的零忽略掉
	{
		if (result != 0)//因为结果是0 的话,有效数字位数检测出来就是0了.这样就不会显示结果了
			for (availableAmount = lstrlen(szBuffer); availableAmount >0; availableAmount--)
			{
			if (szBuffer[availableAmount - 1] != '0')
				break;
			}
		else availableAmount = 1;//当result为0 的时候,不检测,直接把有效数字设置成一位
	}
	if (szBuffer[availableAmount - 1] == '.')//去除后面没有跟数字的 '.' 如果不这样做,99-9就会输出  "90." 
		availableAmount--;

	//最终结果复制给value
	MoveMemory(value, szBuffer, availableAmount*sizeof(szBuffer[0]));
	//int a;//为了设置断点
}
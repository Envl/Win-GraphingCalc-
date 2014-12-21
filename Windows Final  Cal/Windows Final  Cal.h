#pragma once

#include<stdlib.h>
#include<stdio.h>
#include<stack>
#include<math.h>
#include<string.h>
#define max1 200
using namespace std;
char ex[max1];/*�洢��׺���ʽ*/
 bool computed = true;//��־ �Ƿ��Ѿ���������ʽ
 bool flag4TAN = false;//tan����
 bool flag4Factorial = false;//���ʽ�����Ƿ��� �׳ˣ����У���֧�ֻ�ͼ
 bool flag4NotExistNumber;//���ʽ��û������
 bool flag4Alert;//�������ֵ���ڣ����ܳ���0�ȵ� ��ʱflag�͵���true
 bool flag4BracketNotMatch = false;//�������Ų�ƥ��flag   ��ƥ�����true
	/*----------------------------------------Yaoooooooooooooo---------------------------------------------------------------------------------*/

TCHAR*  buttonText[] = {
	TEXT("��"), TEXT("C"), TEXT("��"), TEXT("��"),//0--4�Ű�ť
	TEXT("7"), TEXT("8"), TEXT("9"), TEXT("x"),
	TEXT("4"), TEXT("5"), TEXT("6"), TEXT("-"),
	TEXT("1"), TEXT("2"), TEXT("3"), TEXT("+"),
	TEXT("0"), TEXT("000"), TEXT("."), TEXT("="),//������1��20�Ű�ť
	TEXT("sin"), TEXT("cos"), TEXT("tan"), TEXT("PI"),//����Ҫע��  �����Ŵ�1��ʼ
	TEXT("ln"), TEXT("log"), TEXT("��x"), TEXT("%"),
	TEXT("y��x"), TEXT("("), TEXT(")"), TEXT("^"),
	TEXT("x"), TEXT("y"), TEXT("="), TEXT("!"),//32--->35�Ű�ť
	TEXT("��ͼ"),
	TEXT("g"), TEXT("G"), TEXT("e"), TEXT("n")//��Щ���ǰ�ť����������checkExpression�ȶԱ��ʽ�Ƿ���ȷ��

};
TCHAR;
#define NUM (sizeof buttonText / sizeof buttonText[0])

//������ʡ�Գ˺� ���    �Լ��ڸ���ǰ�Ӹ�0
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
			//ͨ�������ڴ� ����һ��������  ��i�� λ��
			//�����ǲ���0�ڸ���ǰ��ʵ�ָ���������
			ZeroMemory(tmpTail, lstrlen(tmpTail)*sizeof(tmpTail[0]));

			moveLen = lstrlen(str + i);
			MoveMemory(tmpTail, str + i, moveLen*sizeof(str[0]));
			str[i] = '0';
			MoveMemory(str + i + 1, tmpTail, moveLen*sizeof(str[0]));
			//lstrcat(str, tmpTail);
			//	int a = 1; //Ϊ�����öϵ��õ�

		}
		//�ڣ��������һ�����ֵĻ���������֮�����һ�� *
		else if (str[i] == '!'&&str[i + 1] >= '0'&&str[i + 1] <= '9')
		{
			ZeroMemory(tmpTail, lstrlen(tmpTail)*sizeof(tmpTail[0]));
			moveLen = lstrlen(str + i);
			MoveMemory(tmpTail, str + i + 1, moveLen*sizeof(str[0]));
			str[i + 1] = '*';
			MoveMemory(str + i + 2, tmpTail, moveLen*sizeof(str[0]));
			//int a = 1;//Ϊ�����öϵ��õ�
		}
		//sin  cos  tan ln lg ���  û�г˺�
		else if ((str[i] == 's' || str[i] == 'c' || str[i] == 't' || str[i] == 'g' || str[i] == 'n' || str[i] == 'G' || str[i] == 'x' || str[i] == '(') &&((str[i-1]=='x')|| (str[i - 1] >= '0'&&str[i - 1] <= '9')))
		{
			ZeroMemory(tmpTail, lstrlen(tmpTail)*sizeof(tmpTail[0]));
			moveLen = lstrlen(str + i);
			MoveMemory(tmpTail, str + i, moveLen*sizeof(str[0]));
			str[i] = '*';
			MoveMemory(str + i + 1, tmpTail, moveLen*sizeof(str[0]));
			//	int a = 1;//Ϊ�����öϵ��õ�
		}

		i++;
	}
}


//�����溯��ͼ����Ӵ���
void CreateNewChildWindow(HWND hWND, HWND* h4ChildWND){
	if (expression4Display[0] != 'y'||!flag4Check)
	{
		flag4Check = FALSE;
		expression[0] = '\0';
		ZeroMemory(expression4Display, lstrlen(expression4Display)*sizeof(expression4Display[0]));
		lstrcat(expression4Display, TEXT("�����������������뺯��: y=f(x)      ����ֱ�ӿ�ʼ���뺯��"));
		SetWindowText(hStaticText, expression4Display);
		computed = true;
		flag4Check = true;
		SetFocus(hWND);
	}
	else for (int i = 0; i < 10; i++)
	{
		TCHAR DrawWndTitle[50] = {0};
		lstrcpy(DrawWndTitle, expression4Display);
		lstrcat(DrawWndTitle, TEXT("  ��ͼ�񣬰�ESC�ر�"));
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

//��������Ƿ����������������û�и����� ����sinsin ��������û�����־ͷ���false
void operatorInfiniteCheck(TCHAR* str,int i)
{
	
	if (str[i] == '#')
		flag4Check = false;
	else if (str[i] <= '9'&&str[i] >= '0')
		flag4Check = true;
		else if (!(str[i] <= '9'&&str[i] >= '0'))
			operatorInfiniteCheck(str, ++i);

}

//��������Ƿ�ƥ��
//�Ƿ���������ζ���׼���������������
bool BracketCommonOperatorCheck(TCHAR* str)
{
	int lBracketCounter = 0;
	int rBracketCounter = 0;
	int i=0;
	while (str[i] != '#')
	{
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
	if (lBracketCounter != rBracketCounter)//�������Ų�ƥ��ͱ���
	{
		flag4Check = false;
		flag4BracketNotMatch = true;
	}
	return flag4Check;
}
//�����ʽ�Ƿ�������    V1---���е��ַ��Ƿ�������
//���Ǹ���ͨ�����õ�
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


bool expressionCheck4Drawing(TCHAR* str){//���Ǹ�������ͼ�õ�
	int i = 0;
	while (str[i] != '#'){

		flag4Check = false;//��Ӧ�ĵ�  i  ���ַ��Ƿ������buttonText��   false��������
		
		for (int j = 0; j < NUM; j++){
			if (str[i] == *buttonText[j]){
				flag4Check = true;
				return TRUE;
			}
		}
		if (!flag4Check){
			return FALSE;
		}
		i++;
	}
	return flag4Check;

}

//��ȡ���ڴ�С��Ϣ
void GetWindowSize(HWND hwnd, int *pnWidth, int *pnHeight)
{
	RECT rc;
	GetWindowRect(hwnd, &rc);
	*pnWidth = rc.right - rc.left;
	*pnHeight = rc.bottom - rc.top;
}


//charת��TCHAR
void CharToTchar(const char * _char, TCHAR * tchar)
{
	int iLength;

	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

//����ReplaceString(destination,insertion,length,position)
//ͨ�������ڴ� ����һ��������  ��j�� λ�� ��ѵ� i ������ȥ�� Ȼ��ȡ����
void ReplaceString(TCHAR* destination,TCHAR*  insertion,int position){
			int length = lstrlen(insertion);//Ҫ�����滻���ַ����ĳ���

			TCHAR tmpTail[512] = { 0 };//�����������ط��Ժ�Ĳ���
			int moveLen = lstrlen(destination+position+1);//position�Ժ�Ķ�move��
			MoveMemory(tmpTail, destination+position + 1, moveLen*sizeof(destination[0]));
			MoveMemory(destination+position, insertion, length*sizeof(destination[0]));
			MoveMemory(destination + position+length, tmpTail, moveLen*sizeof(destination[0]));
			ZeroMemory(tmpTail, lstrlen(tmpTail));
}
	
/*���������ʽת��Ϊ��׺���ʽ*/
void trans(int length,TCHAR* str)
{
	char stack[max1]={0};/*��Ϊջʹ��*/
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
		case'(':	 /*�ж�Ϊ������*/
			top++; 
			if (top >= 0)
				stack[top] = ch;
			break;

		case')':	/*�ж�Ϊ������*/
			if (top >= 0)
				while (stack[top] != '(')
			{
				if (top >= 0)
					ex[t] = stack[top]; top--; t++;
			}
			top--;
			break;

		case'+':	/*�ж�Ϊ�Ӽ���*/
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

		case'*':	/*�ж�Ϊ�˳���*/
		case'/':
		case'%':
			while (stack[top] == '*' || stack[top] == '/' || stack[top] == '%' || stack[top] == 'g' || stack[top] == '^'
				|| stack[top] == 's' || stack[top] == 'c' || stack[top] == 't' || stack[top] == 'G'
				|| stack[top] == 'n' || stack[top] == 'e' || stack[top] == '!')      /*���ȼ����ڵ���'*'��'/' ����ͬ */
			{
				ex[t] = stack[top];
				top--;
				t++;
			}
			top++;
			stack[top] = ch;
			break;

		case'^':		 //����x^y 
		case'e':		//����y��x		   
			while (stack[top] == '^' || stack[top] == 'e')
			{
				ex[t] = stack[top];
				top--;
				t++;
			}
			top++;
			stack[top] = ch;
			break;

		case'!':		//����׳�   
			while (stack[top] == '!')
			{
				ex[t] = stack[top];
				top--;
				t++;
			}
			top++;
			stack[top] = ch;
			break;

		case'g':		//�����x
		case's':		//����sin x
		case'c':		//����cos x
		case't':		//����tan x
		case'n':		//����ln x
		case'G':		//����lg x

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
			{/*�ж�Ϊ����*/
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

/*�����׺���ʽ��ֵ*/
void compvalue()
{
	flag4Alert = false;//ÿ�ν��뺯����Ҫ�ĳɳ�ʼ״̬ false
	double stack[max1] = { 0 }, d, f;/*��Ϊջʹ��*/
	char ch;
	int t = 1, top = 0;/*tΪex�±꣬topΪstack�±�*/
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
				//printf("\n\t�������!\n");
				if (!flag4Drawing)//�ڻ�ͼʱ�Ͳ��������������
					SetWindowText(hStaticText, TEXT("��ʽ�ڳ�����������"));
				flag4Alert = true;
				flag4Check = false;
				flag4NotDraw = true;//����Ҫ��ͼ
			//	exit(0);/*�쳣�˳�*/
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
				if (!flag4Drawing)//�ڻ�ͼʱ�Ͳ��������������
					SetWindowText(hStaticText, TEXT("���ܸ�����������"));
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
				if (!flag4Drawing)//�ڻ�ͼʱ�Ͳ��������������
					SetWindowText(hStaticText, TEXT("�����Ǹ���"));
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
				if (!flag4Drawing)//�ڻ�ͼʱ�Ͳ��������������
					SetWindowText(hStaticText, TEXT("�����Ǹ���"));
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
				if (!flag4Drawing)//�ڻ�ͼʱ�Ͳ��������������
					SetWindowText(hStaticText, TEXT("���ܸ�����������"));
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
				//printf("\n\t��������!\n");
				if (!flag4Drawing)//�ڻ�ͼʱ�Ͳ��������������
					SetWindowText(hStaticText, TEXT("�׳�ǰ�治��������"));
				flag4Alert = false;
				flag4Check = false;
				flag4NotDraw = true;
				//exit(1);/*�쳣�˳�*/
			}
			float sum = 1;
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
				d = 10 * d + ch - '0';/*�������ַ�ת��Ϊ��Ӧ����ֵ*/
				ch = ex[t]; t++;
				if (a) count++;
			}
			top++;
			stack[top] = d / pow(10, count);
		}
		ch = ex[t];
		t++;
	}

	if (flag4TAN)//����ǻ�tan��ͼ�Ļ�
		if (abs(abs(result) - abs(stack[top])) > 10)  //����ֵ���̫��Ͳ���ͼ
		{
		flag4NotDraw = true;
		flag4TAN = false;
		}

	if (top >= 0)
		result = stack[top];
	
	if (result == -0.000000)
		flag4NotDraw = true;
	//�����а�����ת���ַ�
	TCHAR szBuffer[64];//���岢�������뻺�����ռ�
	char BufferBuffer[64];
	if (top >= 0)
		if (stack[top] == -9.2559631349317831e+061)
	{
		if (top >= 0)
			stack[top] = 0;
		result = 0;
		computed = true;
	}
	sprintf_s(BufferBuffer, "%.14lf", stack[top]);//С�����14λ�Ǽ���,����ͻ���9-0.332=8.667999999��������.  �߾����㷨��ʱ����
	CharToTchar(BufferBuffer, szBuffer);
	if (szBuffer[2] == '.'&&szBuffer[3] == '#')//�� �д�����
		flag4NotDraw = true;
	if (value[0] != '\0'&&expression[0]!='\0')
	{
		ZeroMemory(value, lstrlen(value)*sizeof(value[0]));
	}
	//for (i = 0; i < lstrlen(BufferBuffer);)
	int availableAmount;//��Ч���ֵ�λ��
	if (result!=0)//��Ϊ�����0 �Ļ�,��Ч����λ������������0��.�����Ͳ�����ʾ�����
		for (availableAmount = lstrlen(szBuffer); availableAmount > 0; availableAmount--)
		{
		if (szBuffer[availableAmount - 1] != '0'&&szBuffer[availableAmount - 1] != '.')
			break;
		}
	else availableAmount = 1;//��resultΪ0 ��ʱ��,�����,ֱ�Ӱ���Ч�������ó�һλ
	//int num = lstrlen(szBuffer) - availableAmount;
	MoveMemory(value, szBuffer, availableAmount*sizeof(szBuffer[0]));
	//int a;//Ϊ�����öϵ�
}
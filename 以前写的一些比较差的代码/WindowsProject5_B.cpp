// WindowsProject5_B.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "WindowsProject5_B.h"


#define MAX_LOADSTRING 100


// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT5B, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT5B));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT5B));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT5B);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//		这里是B样条点坐标的算法

//		第一步，查找 u 的位置，节点向量是单调不减数组，所以用二分查找.
//		n = m - p - 1; p为次数，U为节点向量数组

int FindSpan(int n, int p, double u, double U[])
{
	int low = 0, high = 0, mid = 0;
	if (u == U[n + 1])
		return n;
	low = p, high = n + 1;
	mid = (low + high) / 2;
	while (u < U[mid] || u >= U[mid + 1])
	{
		if (u < U[mid])
			high = mid;
		else
			low = mid;
		mid = (low + high) / 2;
	}
	return mid;
}

//   计算B样条基函数

void BasisN(int i, double u, int p, double U[], double N[])
{
	double *left, *right, saved, temp;
	//			对left ，right进行动态分配并且初始化

	left = (double *)malloc((p + 1) * sizeof(double));
	right = (double *)malloc((p + 1) * sizeof(double));
	for (int j = 0; j < p + 1; j++)
	{
		left[j] = 0;
		right[j] = 0;
	}
	N[0] = 1.0;
	for (int j = 1; j <= p; j++)
	{
		left[j] = u - U[i + 1 - j];
		right[j] = U[i + j] - u;
		saved = 0;
		for (int r = 0; r < j; r++)
		{
			temp = N[r] / (right[r + 1] + left[j - r]);
			N[r] = saved + right[r + 1] * temp;
			saved = left[j - r] * temp;
		}
		N[j] = saved;
	}
}

//		算B样条线上的点

double CurvePoint(int n, int p, double U[], double P[], double u, double N[])
{
	double C = 0;
	int span = 0;
	span = FindSpan(n, p, u, U);
	BasisN(span, u, p, U, N);
	for (int j = 0; j <= p; j++)
	{
		C = C + N[j] * P[span - p + j];
	}
	return C;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;


    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // TODO: 在此处添加使用 hdc 的任何绘图代码...


			double U[] = { 0,0,0,0,0.2,0.4,0.4,0.6,0.8,0.8,0.8,1,1,1,1 }, N[5];
			double Px[] = { 100,220,300,360,500,600,700,800,900,1000,1500 };
			double Py[] = { 100,340,200,410,300,700,540,390,420,180,300 };

			GetClientRect(hWnd, &rect);
			HPEN hPen;
			for (int i = 0; i < 11; i++)
			{
				hPen = CreatePen(PS_SOLID, 0, RGB(i+25, 0, 0));			//		初始化画笔，颜色每次循环都会变
				SelectObject(hdc, hPen);
				MoveToEx(hdc, Px[i], Py[i], NULL);						//		画控制多边形的直线
				LineTo(hdc, Px[i + 1], Py[i + 1]);
				hPen = CreatePen(PS_SOLID, 0, RGB(25+i*20, 0, 0));		//		初始化画笔
				SelectObject(hdc, hPen);
				Ellipse(hdc, Px[i] - 5, Py[i] + 5, Px[i] + 5, Py[i] - 5);	//	画控制顶点，画笔颜色同样每次循环都会变
			}

			double x=0, y=0;
			for (double u = 0.0001; u <= 1; u = u + 0.0001)
			{
				x = CurvePoint(11, 3, U, Px, u, N);
				y = CurvePoint(11, 3, U, Py, u, N);
				SetPixel(hdc, x, y, RGB(255, 00, 0));					//		画B样条曲线，一个像素点接一个像素点的画
			}

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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

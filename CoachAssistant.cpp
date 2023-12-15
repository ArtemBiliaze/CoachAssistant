// CoachAssistant.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "CoachAssistant.h"
#include "Autorization.h"
#include "TrainingM.h"

#define MAX_LOADSTRING 100

//* Дескриптори елементів управління
HWND hLogin, hPassword, hName, hSurname, hEmail, hLoginR, hPasswordR1, hPasswordR2, hEditC;
HWND hSubmit, hClear, hRegitresion;
HWND hCalendar;
HWND hTraningsList;
HWND hExcept, hReduce, hTreningFuture, hTreningLast, hSave, hClearC;

//* Ключові глобальні змінні:
bool isAutorize = false;
int index;
bool isCalendar = false;
bool isUnique = true;
auto userRepo = std::make_unique<Autorization>();
// *
auto trainingsRepo = std::make_unique<TrainingM>("Tranings.txt");
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// 1
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Auth(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Calendar(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,

                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_COACHASSISTANT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COACHASSISTANT));

    MSG msg;

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
// 2
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COACHASSISTANT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_COACHASSISTANT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
// 3
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

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
// 4
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Auth);
            if (!isAutorize) {
                DestroyWindow(hWnd);
            }
            else {
                TCHAR buff[100];
                lstrcpy(buff, L"Користувач - ");
                lstrcat(buff, userRepo->getCopyFirstName());
                lstrcat(buff, L"");
                lstrcat(buff, userRepo->getCopyLastName());
                lstrcat(buff, L"?");
                SetWindowText(hWnd, buff);
            }
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, Calendar);
            if (!isCalendar) {
                DestroyWindow(hWnd);
            }
        }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
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
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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
// 5
INT_PTR CALLBACK Auth(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        {
            hLogin = GetDlgItem(hDlg, IDC_EDIT1);
            hPassword = GetDlgItem(hDlg, IDC_EDIT2);
            hName = GetDlgItem(hDlg, IDC_EDIT3);
            hSurname = GetDlgItem(hDlg, IDC_EDIT4);
            hName = GetDlgItem(hDlg, IDC_EDIT3);
            hSurname = GetDlgItem(hDlg, IDC_EDIT4);
            hEmail = GetDlgItem(hDlg, IDC_EDIT5);
            hLoginR = GetDlgItem(hDlg, IDC_EDIT8);
            hPasswordR1 = GetDlgItem(hDlg, IDC_EDIT6);
            hPasswordR2 = GetDlgItem(hDlg, IDC_EDIT7);
            hSubmit = GetDlgItem(hDlg, IDC_BUTTON3);
            hClear = GetDlgItem(hDlg, IDC_BUTTON4);
            hRegitresion = GetDlgItem(hDlg, IDC_BUTTON8);
        }
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            TCHAR buff1[100];
            TCHAR buff2[100];
            TCHAR buff3[100];
            TCHAR buff4[100];
            TCHAR buff5[100];
            TCHAR buff6[100];
            // ->
            if (wmId == IDC_BUTTON3)
            {
                GetWindowText(hLogin, buff1, 100);
                if (lstrlen(buff1) == 0) {
                    MessageBox(hDlg, L"Вибачте але ви не вказали свій логін!", L"Попередження",
                        MB_OK | MB_ICONWARNING);
                    SetFocus(hLogin);
                }
                else {
                    GetWindowText(hPassword, buff2, 100);
                    if (lstrlen(buff2) == 0) {
                        MessageBox(hDlg, L"Вибачте але ви не вказали свій пароль!", L"Попередження",
                            MB_OK | MB_ICONWARNING);
                        SetFocus(hPassword);
                    }
                    else {
                        isAutorize = userRepo->autheticate(buff1, buff2);
                        if (!isAutorize) {
                            MessageBox(hDlg, L"Вибачте але цей юзер не знайдений",
                                L"Повідомлення", MB_OK | MB_ICONERROR);
                        }
                        else {
                            MessageBox(hDlg, L"Ви успішно авторизовані!",
                                    L"Повідомлення", MB_OK | MB_ICONERROR);
                            EndDialog(hDlg, wmId);

                        }
                    }
                }
            }
            if (wmId == IDC_BUTTON8)
            {
                GetWindowText(hName, buff1, 100);
                if (lstrlen(buff1) == 0) {
                    MessageBox(hDlg, L"Вибачте але ви не вказали своє ім'я!", L"Попередження",
                        MB_OK | MB_ICONWARNING);
                    SetFocus(hName);
                }
                GetWindowText(hSurname, buff2, 100);
                if (lstrlen(buff2) == 0) {
                    MessageBox(hDlg, L"Вибачте але ви не вказали своє прізвище!", L"Попередження",
                        MB_OK | MB_ICONWARNING);
                    SetFocus(hSurname);
                }
                GetWindowText(hEmail, buff3, 100);
                if (lstrlen(buff3) == 0) {
                    MessageBox(hDlg, L"Вибачте але ви не вказали свій Email!", L"Попередження",
                            MB_OK | MB_ICONWARNING);
                    SetFocus(hEmail);
                }
                GetWindowText(hLoginR, buff4, 100);
                if (lstrlen(buff4) == 0) {
                    MessageBox(hDlg, L"Вибачте але ви не вказали свій логін!", L"Попередження",
                            MB_OK | MB_ICONWARNING);
                    SetFocus(hLoginR);
                }
                GetWindowText(hPasswordR1, buff5, 100);
                if (lstrlen(buff5) == 0) {
                    MessageBox(hDlg, L"Вибачте але ви не вказали свій пароль!", L"Попередження",
                            MB_OK | MB_ICONWARNING);
                    SetFocus(hPasswordR1);
                }
                GetWindowText(hPasswordR2, buff6, 100);
                if (lstrlen(buff6) == 0) {
                    MessageBox(hDlg, L"Вибачте але ви не вказали свій підтверджений пароль!", L"Попередження",
                            MB_OK | MB_ICONWARNING);
                    SetFocus(hPasswordR2);
                }
                else
                {
                    userRepo->registry(buff1, buff2, buff3, buff4, buff5, buff6);
                    if (!isAutorize) {
                        MessageBox(hDlg, L"Вибачте але цей юзер не знайдений",
                            L"Повідомлення", MB_OK | MB_ICONERROR);
                    }
                    else {
                        MessageBox(hDlg, L"Ви успішно зареєстрованні!",
                            L"Повідомлення", MB_OK | MB_ICONERROR);
                        EndDialog(hDlg, wmId);
                    }
                }
                
            }
            else if (wmId == IDC_BUTTON4) {
                SetWindowText(hLogin, L"");
                SetWindowText(hPassword, L"");
                SetWindowText(hName, L"");
                SetWindowText(hSurname, L"");
                SetWindowText(hEmail, L"");
                SetWindowText(hPasswordR1, L"");
                SetWindowText(hPasswordR2, L"");
                SetFocus(hLogin);
                SetFocus(hLoginR);
            }
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
        }
        return (INT_PTR)FALSE;
    }
}

// 6
INT_PTR CALLBACK Calendar(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        {
            hCalendar = GetDlgItem(hDlg, IDC_DATETIMEPICKER1);
            hTraningsList = GetDlgItem(hDlg, IDC_LIST2);
            hEditC = GetDlgItem(hDlg, IDC_EDIT9);
            hExcept = GetDlgItem(hDlg, IDC_BUTTON6);
            hReduce = GetDlgItem(hDlg, IDC_BUTTON10);
            hTreningFuture = GetDlgItem(hDlg, IDC_BUTTON7);
            hTreningLast = GetDlgItem(hDlg, IDC_BUTTON9);
            hSave = GetDlgItem(hDlg, IDC_BUTTON11);
            hClearC = GetDlgItem(hDlg, IDC_BUTTON5);
        }
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            if (wmId == IDC_BUTTON11)
            {
                Training newT;
                trainingsRepo->addTraining(newT);
                if (!isUnique) {
                    MessageBox(hDlg, L"Вибачте але це тренування збережене",
                        L"Mistake", MB_OK | MB_ICONERROR);
                }
                else {
                    MessageBox(hDlg, L"Все тренування на цей день є!",
                        L"Messege", MB_OK | MB_ICONERROR);
                    EndDialog(hDlg, wmId);
                }
            }
            else (LOWORD(wParam) == IDC_BUTTON10); {
                  TCHAR buff[100];
                  GetWindowText(hEditC, buff, 100);
                  // ->
                  if (lstrlen(buff) == 0) {
                      MessageBox(hDlg, L"Ви не відреагували тренування!!!",
                          L"Mistake", MB_OK | MB_ICONERROR);
                      SetFocus(hEditC);
                  }
                  else {
                      trainingsRepo->redactionT(index, buff);
                      SendMessage(hTraningsList, LB_SETITEMDATA, index, LPARAM(buff));
                      trainingsRepo->saveData();
                      MessageBox(hDlg, L"Процес редагування зроблено", L"Message", MB_OK | MB_ICONINFORMATION);
                  }
            }
            if (HIWORD(wParam) == LBN_SELCHANGE) {
                int selectedIndex = SendMessage(GetDlgItem(hDlg, IDC_LIST2), LB_GETCURSEL, 0, 0);
                if (selectedIndex != LB_ERR) {
                    EnableWindow(hReduce, TRUE);
                }
            }
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
        }
        return (INT_PTR)FALSE;
    }
}
// 7
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
// lpChange = (LPNMDATETIMECHANGE) lParam;
//if (LOWORD(wParam) == IDC_DATETIMEPICKER1 && HIWORD(wParam) == DTN_DATETIMECHANGE) {
    //SYSTEMTIME chooseData;
    //TCHAR buff[100];
    //std::vector<Training> trainings = trainingsRepo->findTrainingsByDate(chooseData, trainings);
    //SendMessage(GetDlgItem(hDlg, IDC_LIST2), LB_RESETCONTENT, 0, 0);
    //for (const auto& training : trainings) {
        //SendMessage(GetDlgItem(hDlg, IDC_LIST2), LB_ADDSTRING, 0, LPARAM(buff));
    //}
//}

 //if (lpnmhdr->idFrom == IDC_DATETIMEPICKER1 && lpnmhdr->code == DTN_DATETIMECHANGE)
//{
    //LPNMDATETIMECHANGE lpChange = (LPNMDATETIMECHANGE)lParam;
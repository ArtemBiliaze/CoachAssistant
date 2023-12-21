// CoachAssistant.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "CoachAssistant.h"
#include "ExerciseRepo.h"
#include "NotesRepo.h"

#define MAX_LOADSTRING 100

//* Description element:
// MainMenu
HWND hPlaningTrainButton, hNotesTrainButton, hProtocolButton, hUsefulLinksButton, hBackButton;

// NoteTrain
HWND hNoteExersixeEdit,  hNoteList;
HWND hLoadingButton, hClearButton1, hClearButton2, hNoteBackButton, hAddButton;


//ProtocolCalc
HWND hBenchChoice, hSquatChoice, hDeadLiftChoice;
HWND hBenchWeightEdit, hSqatWeightEdit, hLiftWeightEdit, hCalcWeightEdit;
HWND hCalcProtocolButton, hClearProtocolButton, hBackProtocolButton;




//Repositories

auto notes = std::make_unique<NotesRepo>("Notes.txt");
auto bench = std::make_unique<ExerciseRepo>("BenchProtocol.txt");
auto squat = std::make_unique<ExerciseRepo>("SquatProtocol.txt");
auto deadlift = std::make_unique<ExerciseRepo>("DeadLiftProtocol.txt");

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING]; 



// имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    MainMenu(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    NoteTrain(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ProtocolCalc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_COACHASSISTANT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COACHASSISTANT));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COACHASSISTANT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_COACHASSISTANT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


//
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



//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    
    
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

// Обработчик сообщений для окна "О программе".
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

//*
INT_PTR CALLBACK MainMenu(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        {
            hPlaningTrainButton = GetDlgItem(hDlg, IDC_BUTTON1);
            hNotesTrainButton = GetDlgItem(hDlg, IDC_BUTTON2);
            hProtocolButton = GetDlgItem(hDlg, IDC_BUTTON3);
            hUsefulLinksButton = GetDlgItem(hDlg, IDC_BUTTON4);
            hBackButton = GetDlgItem(hDlg, IDC_BUTTON5);
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            if (wmId == IDC_BUTTON1) {
                
                
            }
            else if (wmId == IDC_BUTTON2)
            {
                EndDialog(hDlg, wmId);
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hDlg, NoteTrain);

            }
            else if (wmId == IDC_BUTTON3) {
                EndDialog(hDlg, wmId);
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hDlg, ProtocolCalc);
            }
            else if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }

        }
        break;
    }
    return (INT_PTR)FALSE;
}

//*
INT_PTR CALLBACK NoteTrain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        hNoteExersixeEdit = GetDlgItem(hDlg, IDC_EDIT1);
        hNoteList = GetDlgItem(hDlg, IDC_LIST1);

        hLoadingButton = GetDlgItem(hDlg, IDC_BUTTON1);
        hAddButton = GetDlgItem(hDlg, IDC_BUTTON4);
        hClearButton1 = GetDlgItem(hDlg, IDC_BUTTON2);
        hClearButton2 = GetDlgItem(hDlg, IDC_BUTTON5);
        hNoteBackButton = GetDlgItem(hDlg, IDC_BUTTON6);

       

        notes->loadData();
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        if (wmId == IDC_BUTTON1) {
            
            for (auto& note : notes->getNotes()) {
                
                SendMessage(hNoteList, LB_ADDSTRING, 0, LPARAM(note.getName()));
            }
        }
        else if (wmId == IDC_BUTTON4)
        {
            TCHAR buff[100];
            GetWindowText(hNoteExersixeEdit, buff, 100);

            if (lstrlen(buff) == 0) {
                MessageBox(hDlg, L"Ви не ввели информацию о вправі!",
                    L"Попередження", MB_OK | MB_ICONWARNING);
                SetFocus(hNoteExersixeEdit);
            }
            else {
                std::vector<Notes>& allNotes = notes->getNotes();

                int id = allNotes.empty() ? 1 : allNotes.back().getId() + 1;
                Notes newNote(id, buff);
                notes->addNotes(newNote);

                
                SendMessage(hNoteList, LB_ADDSTRING, 0, LPARAM(newNote.getName()));

                notes->saveData();
            }
        }
        
        else if (wmId == IDC_BUTTON2)
        {
            SetWindowText(hNoteExersixeEdit, L"");
        }
        else if (wmId == IDC_BUTTON5) 
        {
            SendMessage(hNoteList, LB_RESETCONTENT, 0, 0);
        }
        else if (wmId == IDC_BUTTON6)
        {
            EndDialog(hDlg, wmId);
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hDlg, MainMenu);
            
        }
        else if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//*
INT_PTR CALLBACK ProtocolCalc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        
        hBenchWeightEdit = GetDlgItem(hDlg, IDC_EDIT1);
        hSqatWeightEdit = GetDlgItem(hDlg, IDC_EDIT2);
        hLiftWeightEdit = GetDlgItem(hDlg, IDC_EDIT3);
        hCalcWeightEdit = GetDlgItem(hDlg, IDC_EDIT4);
        hCalcProtocolButton = GetDlgItem(hDlg, IDC_BUTTON1);
        hClearProtocolButton = GetDlgItem(hDlg, IDC_BUTTON2);
        hBackProtocolButton = GetDlgItem(hDlg, IDC_BUTTON8);

        bench->loadProgram();
        squat->loadProgram();
        deadlift->loadProgram();
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
      

        if (wmId == IDC_BUTTON1) {
            double pm1 = 0.0;
            TCHAR buffWeight[50];

            if (GetWindowTextLength(hBenchWeightEdit) > 0) {
                GetWindowText(hBenchWeightEdit, buffWeight, 50);
                pm1 = _tstof(buffWeight);
                SetWindowText(hCalcWeightEdit, L"");

                for (auto& train : bench->getExercice()) {
                    double weight = train.getPersent() * pm1 / 100;
                    TCHAR buffResult[200];
                    swprintf_s(buffResult, L"Train ID: %d, Exercise: %s, Weight: %.2f, Set: %d, Rep: %d\r\n",
                        train.getTrainId(), train.getExercise(), weight, train.getSet(), train.getRep());
                    SendMessage(hCalcWeightEdit, EM_REPLACESEL, 0, LPARAM(buffResult));
                }
                bench->saveProgram(pm1);
                
            }
            else if (GetWindowTextLength(hSqatWeightEdit) > 0) {
                GetWindowText(hSqatWeightEdit, buffWeight, 50);
                pm1 = _tstof(buffWeight);
                SetWindowText(hCalcWeightEdit, L"");

                for (auto& train : squat->getExercice()) {
                    double weight = train.getPersent() * pm1 / 100;
                    TCHAR buffResult[200];
                    swprintf_s(buffResult, L"Train ID: %d, Exercise: %s, Weight: %.2f, Set: %d, Rep: %d\r\n",
                        train.getTrainId(), train.getExercise(), weight, train.getSet(), train.getRep());
                    SendMessage(hCalcWeightEdit, EM_REPLACESEL, 0, LPARAM(buffResult));
                }
                squat->saveProgram(pm1);
            }
            else if (GetWindowTextLength(hLiftWeightEdit) > 0) {
                GetWindowText(hLiftWeightEdit, buffWeight, 50);
                pm1 = _tstof(buffWeight);
                SetWindowText(hCalcWeightEdit, L"");

                for (auto& train : deadlift->getExercice()) {
                    double weight = train.getPersent() * pm1 / 100;
                    TCHAR buffResult[200];
                    swprintf_s(buffResult, L"Train ID: %d, Exercise: %s, Weight: %.2f, Set: %d, Rep: %d\r\n",
                        train.getTrainId(), train.getExercise(), weight, train.getSet(), train.getRep());
                    SendMessage(hCalcWeightEdit, EM_REPLACESEL, 0, LPARAM(buffResult));
                }
                deadlift->saveProgram(pm1);
            }
            else {
                break;
            }
        }
        else if (wmId == IDC_BUTTON2) {
           
            SetWindowText(hCalcWeightEdit, L"");
        }
        else if (wmId == IDC_BUTTON8) {
            EndDialog(hDlg, wmId);
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hDlg, MainMenu);
        }
        else if (wmId == IDOK || wmId == IDCANCEL) {
            EndDialog(hDlg, wmId);
            return (INT_PTR)TRUE;
        }
        break;
    }
    }
    return (INT_PTR)FALSE;
}

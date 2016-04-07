

#include "resource.h"
#include "tetrisGraph.h"

char const szMainClassName[] = "TetrisAppClass";
static int idTimer = -1;

void show();

void new_figur();
void restart();
void begin();

char temp[2];

HWND hwnd;
HWND hwnd_button;
MSG msg;

HDC text_hdc;
RECT rectPlace;
HFONT hFont;

HINSTANCE hinst;

Tetris field;
extern HINSTANCE hInst;

//----------------------------------
// Window procedure
//----------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static DLGPROC lpfnDlgProc;

	switch (msg)
	{
	case WM_CREATE:
		field.setHdc(GetDC(hwnd));

		
		MessageBox(NULL,
			"Добро пожаловать в тетрис",
			"Welcome", MB_ICONASTERISK | MB_OK);
		
	case WM_PAINT:
		text_hdc = BeginPaint(hwnd, &ps);
		
		TextOut(text_hdc, 310, 270, "Next figure is:", 14);
		_itoa(field.score, temp, 10);
		TextOut(text_hdc, 610, 270, "Your score is: ", 16);
		TextOut(text_hdc, 610, 290, temp, 2);
		
		EndPaint(hwnd, &ps);
		return 0;

	case WM_COMMAND:
		if (wParam == IDB_BUTTON1)
		{
			DestroyWindow(hwnd_button);
			hwnd_button=CreateWindow("button", "Restart",
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				410, 370,
				90, 60,
				hwnd,
				(HMENU)IDB_BUTTONRE,
				hInst, NULL);
		
			SetTimer(hwnd, idTimer = 1, SPEED, NULL);
			
			begin();
			SetFocus(hwnd);
			return 0;
			break;
		}
		if (wParam == IDB_BUTTONL)
		{
			field.move_the_figure_left(m_figur);
			SetFocus(hwnd);
			return 0;
			break;
		}
		if (wParam == IDB_BUTTOND)
		{
			KillTimer(hwnd, 1);
			SetTimer(hwnd, idTimer = 1, SPEED_2, NULL);
			SetFocus(hwnd);
			return 0;
			break;
		}
		if (wParam == IDB_BUTTONR)
		{
			field.move_the_figure_right(m_figur);
			SetFocus(hwnd);
			return 0;
			break;
		}
		if (wParam == IDB_BUTTONRE)
		{
			KillTimer(hwnd, 1);
			SetTimer(hwnd, idTimer = 1, SPEED, NULL);
			
			restart();
			SetFocus(hwnd); 
			return 0;
			break;
		}
		if (wParam == IDB_BUTTONP)
		{
			if (field.check_the_povorot(m_figur))
				m_figur.povorot();
			else
			{
				m_figur.povorot();
				if (field.check_the_povorot(m_figur))
					m_figur.povorot();
				else
				{
					m_figur.povorot();
					if (field.check_the_povorot(m_figur))
						m_figur.povorot();
					else
					{
						m_figur.povorot();
						m_figur.povorot();
					}


				}
			}
			SetFocus(hwnd);
			return 0;
			break;
		}
		if (wParam == IDB_BUTTONU)
		{
			KillTimer(hwnd, 1);
			SetTimer(hwnd, idTimer = 1, SPEED , NULL);
			SetFocus(hwnd);
			return 0;
			break;
		}
		return 0;

	case WM_DESTROY:
		field.releaseHdc(hwnd);
		PostQuitMessage(0);
		return 0;

	case WM_TIMER:

		if (field.game_over)
		{
			KillTimer(hwnd, 1);
			MessageBox(NULL,
				"Вы проиграли =(",
				"FAIL", MB_ICONASTERISK | MB_OK);
			int result = MessageBox(NULL, "Хотите сыграть еще?!", "Задача",
				MB_ICONQUESTION | MB_YESNO);
			switch (result)
			{
				
			case IDYES:
				SetTimer(hwnd, idTimer = 1, SPEED, NULL);
				restart(); 
				SetFocus(hwnd); 
				break;
			case IDNO:  SendMessage(hwnd, WM_CLOSE, 0, 0L); 
				break;
			}
		}

		if (field.check_can_move(m_figur))
		{
			field.move_the_figure_down(m_figur);
			show();
		}
		else
		{
			field.check_screen();
			field.step_figur();
			
			new_figur();
			SetTimer(hwnd, idTimer = 1, SPEED , NULL);
		}
		
		return 0;

	case WM_KEYDOWN:

		switch (LOWORD(wParam))
		{
		case VK_LEFT:
			field.move_the_figure_left(m_figur);
			return 0;
			break;
		case VK_ESCAPE:
			SendMessage(hwnd, WM_CLOSE, 0, 0L);
			break;
		case VK_RIGHT:
				field.move_the_figure_right(m_figur);
			return 0;
			break;
		case VK_DOWN:
			KillTimer(hwnd, 1);
			SetTimer(hwnd, idTimer = 1, SPEED_2, NULL);
			return 0;
		case VK_UP:
			KillTimer(hwnd, 1);
			SetTimer(hwnd, idTimer = 1, SPEED, NULL);
			SetFocus(hwnd);
			return 0;
			break;
		case VK_SPACE:
			if (field.check_the_povorot(m_figur))
				m_figur.povorot();
			else
			{
				m_figur.povorot();
				if (field.check_the_povorot(m_figur))
					m_figur.povorot();
				else
				{
					m_figur.povorot();
					if (field.check_the_povorot(m_figur))
						m_figur.povorot();
					else
					{
						m_figur.povorot();
						m_figur.povorot();
					}


				}
			}
			return 0;
			break;

		default:
			break;
		}
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}





BOOL Register(HINSTANCE hInstance, HBRUSH hBrush)
{
	ATOM aWndClass;
	WNDCLASS wc;
	memset(&wc, 0, sizeof(wc));
	wc.style = 0;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = hBrush;
	wc.lpszMenuName = (LPSTR)NULL;
	wc.lpszClassName = (LPSTR)szMainClassName;
	aWndClass = RegisterClass(&wc);

	if (aWndClass == 0)
		return FALSE;

	return TRUE;
}


void show()
{
	HDC hdc;
	field.clear_sreen();
	hdc = GetDC(hwnd);

	field.get_figure_to_pole(m_figur);
	field.get_the_pole();
	ReleaseDC(hwnd, hdc);
}

void new_figur()
{
	m_figur = m_next_figur;
	m_next_figur=field.generate_figura(rand() % 7);
	InvalidateRect(hwnd, NULL, TRUE);
	show();
	field.get_next_figur_to_screen(m_next_figur);

}


void begin()
{
	srand(time(NULL));
	m_figur = field.generate_figura(rand() % 7);
	m_next_figur = field.generate_figura(rand() % 7);
	
	field.get_next_figur_to_screen(m_next_figur);
	SetFocus(hwnd);
	

	show();
}

void restart()
{
	Tetris neew;

	field = neew;
	InvalidateRect(hwnd, NULL, TRUE);
	begin();
}
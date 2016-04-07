#pragma once
#ifndef _TETRIS_GRAPH_
#define _TETRIS_GRAPH_
#include "stdafx.h"
#include "resource.h"

enum poloshenie
{
	p_up,                     // default 
	p_right,
	p_down,
	p_left,
};

enum figur_ch
{
	figura_7,
	figura_1,
	figura_2,
	figura_3,
	figura_4,
	figura_5,
	figura_6,
};

struct koord_yach
{
	int x;     // vertikal vnis
	int y;     // gorizontal vpravo 
};


struct koord
{
	bool **pole;											  //  pole figuri 1 est 0 pusto
	int size_x = 0;							    //   razmer po x 
	int size_y = 0;								  //    razmer po y
	koord_yach korrdinate;        //     koordinata 1 yacheiki 
	figur_ch choice;									 //      chto sa figura 
	int polozh;           //    default polosh

};

class figura
{
public:
	figura(int);  
	figura(figura &);//sosd figuru
	int povorot();     // povorachivaet figuru 
public:
	koord figur;
	figura& operator=(figura &obj);

};

static figura m_figur(1);
static figura m_next_figur(rand() % 7);

struct pole_struct 
{
	figur_ch choice;
	bool is_null;
};

class Tetris
{
        //the field
	HDC hdc_;

	static HBITMAP hBmpf1;
	static HBITMAP hBmpf2;
	static HBITMAP hBmpf3;
	static HBITMAP hBmpf4;
	static HBITMAP hBmpf5;
	static HBITMAP hBmpf6;
	static HBITMAP hBmpf7;
	static HBITMAP hBmpb2;

	void drawBitmap(int x, int y, HBITMAP hBitmap);


private:
	vector<vector<pole_struct>> m_pole;
	vector<vector<pole_struct>> m_pole_temp;
	
	

	

public:
	int score;
	bool game_over = false;
	void setHdc(HDC h) { hdc_ = h; }
	
	void releaseHdc(HWND hwnd) { ReleaseDC(hwnd, hdc_); }
	Tetris& operator=(Tetris &obj);
	static void setBmp1(HBITMAP h) { hBmpf1 = h; }
	static void setBmp2(HBITMAP h) { hBmpf2 = h; }
	static void setBmp3(HBITMAP h) { hBmpf3 = h; }
	static void setBmp4(HBITMAP h) { hBmpf4 = h; }
	static void setBmp5(HBITMAP h) { hBmpf5 = h; }
	static void setBmp6(HBITMAP h) { hBmpf6 = h; }
	static void setBmp7(HBITMAP h) { hBmpf7 = h; }
	static void setBmpback(HBITMAP h) { hBmpb2 = h; }
	static void deleteBmp1() { DeleteObject(hBmpf1); }
	static void deleteBmp2() { DeleteObject(hBmpf2); }
	static void deleteBmp3() { DeleteObject(hBmpf3); }
	static void deleteBmp4() { DeleteObject(hBmpf4); }
	static void deleteBmp5() { DeleteObject(hBmpf5); }
	static void deleteBmp6() { DeleteObject(hBmpf6); }
	static void deleteBmp7() { DeleteObject(hBmpf7); }
	static void deleteBmpback() { DeleteObject(hBmpb2); }

	Tetris();
	Tetris(Tetris &);
	void get_the_pole();
	figura generate_figura(int);
	int check_the_line_to_destroy(int);
	int check_the_line(int);
	int check_can_move(figura&);
	int check_screen();
	int check_the_povorot(figura&);
	int check_is_obj_behind(figura &,int);
	int check_dist(int, int, int);
	int check_dist_to_down(int, int);
	int check_is_obj_below(figura &);
	int check_can_povorot(figura &);
	void get_figure_to_pole(figura&);
	void get_next_figur_to_screen(figura &);
	void move_the_figure_down(figura &);
	void move_the_figure_left(figura &);
	void move_the_figure_right(figura &);
	void clear_sreen();
	void clear_line(int);
	void step_figur();
};



#endif

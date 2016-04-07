
#include "tetrisGraph.h"
#include "resource.h"


HBITMAP Tetris::hBmpf1 = (HBITMAP)0;
HBITMAP Tetris::hBmpf2 = (HBITMAP)0;
HBITMAP Tetris::hBmpf3 = (HBITMAP)0;
HBITMAP Tetris::hBmpf4 = (HBITMAP)0;
HBITMAP Tetris::hBmpf5 = (HBITMAP)0;
HBITMAP Tetris::hBmpf6 = (HBITMAP)0;
HBITMAP Tetris::hBmpf7 = (HBITMAP)0;
HBITMAP Tetris::hBmpb2 = (HBITMAP)0;



// paint the bitmap picture
void Tetris::drawBitmap(int x, int y, HBITMAP hBitmap)
{
	HDC hDCMemory;
	HBITMAP hOldBitmap;
	BITMAP bitmap;
	GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	hDCMemory = CreateCompatibleDC(hdc_);
	hOldBitmap = (HBITMAP)SelectObject(hDCMemory,hBitmap);
	BitBlt(hdc_, x, y, bitmap.bmWidth, bitmap.bmHeight,
                                  hDCMemory, 0, 0, SRCCOPY);
	SelectObject(hDCMemory, hOldBitmap);
	DeleteDC(hDCMemory);
}


////////////////////////////////////////////////////////////////////////
Tetris::Tetris(Tetris &obj)
{
	m_pole = obj.m_pole;
	m_pole_temp = obj.m_pole_temp;
	score = obj.score;
	game_over = obj.game_over;
}


Tetris &Tetris::operator=(Tetris &obj)
{
	m_pole = obj.m_pole;
	m_pole_temp = obj.m_pole_temp;
	score = obj.score;
	game_over = obj.game_over;
	return *this;

}

Tetris::Tetris()
{
	vector<pole_struct> temp;
	pole_struct temp_temp;
	temp_temp.choice = figura_1;
	temp_temp.is_null = true;
	bool exit = false;
	

	srand((unsigned int)time(NULL));


	temp.insert(temp.begin(), SCREEN_WEIGHT, temp_temp); //stroka pustih polei


		score = 0;
		m_pole.clear();
		m_pole.insert(m_pole.begin(), SCREEN_LENGTH, temp);
		m_pole_temp = m_pole;
		m_next_figur = generate_figura(rand() % 7);
}

void Tetris::clear_sreen()
{
	drawBitmap(38, 35, hBmpb2);
}


void Tetris::get_the_pole()
{
	int y = 38, x;
	
	for (int i = 0; i < SCREEN_LENGTH; ++i)
	{
		x = 41;
		for (int j = 0; j < SCREEN_WEIGHT; ++j)
		{
			if (m_pole.at(i).at(j).is_null);

			else
				switch (m_pole.at(i).at(j).choice)
				{
				case figura_1:
					drawBitmap(x, y, hBmpf1);
					break;
				case figura_2:
					drawBitmap(x, y, hBmpf2);
					break;
				case figura_3:
					drawBitmap(x, y, hBmpf3);
					break;
				case figura_4:
					drawBitmap(x, y, hBmpf4);
					break;
				case figura_5:
					drawBitmap(x, y, hBmpf5);
					break;
				case figura_6:
					drawBitmap(x, y, hBmpf6);
					break;
				case figura_7:
					drawBitmap(x, y, hBmpf7);
					break;
				}
			
			   //paint an empty cell
			x += 25;
		}
		y += 25;
	}
	
}

figura Tetris::generate_figura(int choice)
{
	figura obj(choice);



	if (check_the_line(0) || check_the_line(1))
		game_over = true;


	obj.figur.korrdinate.x = 0;
	obj.figur.korrdinate.y = SCREEN_WEIGHT / 2;

	return obj;
}

int Tetris::check_the_line(int line_number)
{
	for (int i = 0; i < SCREEN_WEIGHT; i++)
		if (!m_pole_temp.at(line_number).at(i).is_null)
			return 1;
	return 0;
}

int Tetris::check_the_line_to_destroy(int line_number)
{
	for (int i = 0; i < SCREEN_WEIGHT; i++)
		if (m_pole.at(line_number).at(i).is_null)
			return 0;
	return 1;
}

int Tetris::check_can_move(figura &temp)
{

	if (temp.figur.korrdinate.x +check_dist_to_down(temp.figur.polozh,temp.figur.choice) < SCREEN_LENGTH -1)
	{
		if (check_is_obj_below(temp))
			return 1;
		else
			return 0;
	}
	return 0;
}


void Tetris::get_figure_to_pole(figura &temp)
{
	m_pole = m_pole_temp;
	for (int i = 0; i < temp.figur.size_x; i++)
		for (int j = 0; j < temp.figur.size_y; j++)
			if (temp.figur.pole[i][j])
				switch (temp.figur.polozh)
				{
				case p_up:
					m_pole.at(temp.figur.korrdinate.x + i).at(temp.figur.korrdinate.y + j).is_null = !temp.figur.pole[i][j];
					m_pole.at(temp.figur.korrdinate.x + i).at(temp.figur.korrdinate.y + j).choice = temp.figur.choice;
					break;
				case p_right:
					m_pole.at(temp.figur.korrdinate.x + j).at(temp.figur.korrdinate.y - i).is_null =! temp.figur.pole[i][j];
					m_pole.at(temp.figur.korrdinate.x + j).at(temp.figur.korrdinate.y - i).choice = temp.figur.choice;
					break;
				case p_down:
					m_pole.at(temp.figur.korrdinate.x - i).at(temp.figur.korrdinate.y - j).is_null =! temp.figur.pole[i][j];
					m_pole.at(temp.figur.korrdinate.x - i).at(temp.figur.korrdinate.y - j).choice = temp.figur.choice;
					break;
				case p_left:
					m_pole.at(temp.figur.korrdinate.x - j).at(temp.figur.korrdinate.y + i).is_null = !temp.figur.pole[i][j];
					m_pole.at(temp.figur.korrdinate.x - j).at(temp.figur.korrdinate.y + i).choice = temp.figur.choice;
					break;

				}
}

void Tetris::step_figur()
{
	m_pole_temp = m_pole;
}


void Tetris::move_the_figure_down(figura &temp)
{
		temp.figur.korrdinate.x++;
}

void Tetris::move_the_figure_left(figura &temp)
{
	if (temp.figur.korrdinate.y - check_dist(temp.figur.polozh, 0, temp.figur.choice)>0)
		if(check_the_line(temp.figur.korrdinate.y+1))
			temp.figur.korrdinate.y--;
		else
		if (!check_is_obj_behind(temp, 0))
			temp.figur.korrdinate.y--;
}

void Tetris::move_the_figure_right(figura &temp)
{
	if (temp.figur.korrdinate.y + check_dist(temp.figur.polozh, 1, temp.figur.choice)<SCREEN_WEIGHT - 1)
		if (!check_the_line(temp.figur.korrdinate.x))
			temp.figur.korrdinate.y++;
		else
		if (!check_is_obj_behind(temp, 1))
			temp.figur.korrdinate.y++;
}



int Tetris::check_screen()
{
	for (int i = 3; i < SCREEN_LENGTH; i++)
		if (check_the_line_to_destroy(i))
			clear_line(i);
	return 0;
}

void Tetris::clear_line(int line_number)
{
	for (int i = line_number; i >2; i--)
		for (int j = 0; j < SCREEN_WEIGHT; j++)
		{
			m_pole.at(i).at(j).is_null = m_pole.at(i - 1).at(j).is_null;
			m_pole.at(i).at(j).choice = m_pole.at(i - 1).at(j).choice;
		}

	score++;
}


int Tetris::check_dist(int choice, int side, int type)
{
	if (side)//1 - right 0 - left 
	{
		switch (choice)
		{
		case p_up:
			switch (type)
			{
			case 1:
				return 3;
			case 4:
				return 1;
			default:
				return 2;
			}
			break;
		case p_down:
		case p_right:
			return 0;
			break;

		case p_left:
			switch (type)
			{
			case 1:
				return 0;
			default:
				return 1;
			}
			break;

		}

	}
	else
	{
		switch (choice)
		{
		case p_up:
		case p_left:
			return 0;
			break;
		case p_down:
			switch (type)
			{
			case 1:
				return 3;
			case 4:
				return 1;
			default:
				return 2;
			}
			break;
		case 	p_right:
			switch (type)
			{
			case 1:
				return 0;
			default:
				return 1;
			}
			break;
		}

	}
	return 0;
}

int Tetris::check_dist_to_down(int choice, int type)
{
	switch (choice)
	{
	case p_up:
		if (type == 1)
			return 0;
		else
			return 1;

		break;
	case p_right:
		switch (type)
		{
		case 1:
			return 3;
		case 4:
			return 1;
		default:
			return 2;
		}
		break;
	default:
		return 0;
		break;
	}
	return 0;
}


int Tetris::check_is_obj_below(figura &temp)
{
	switch (temp.figur.polozh)
	{
	case p_up:
	{
		switch (temp.figur.choice)
		{
		case figura_1:
			for (int i = 0; i < 4; i++)
				if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y + i).is_null)
					return 0;
			return 1;
			break;
		case figura_4:
			for (int i = 0; i < 2; i++)
				if (!m_pole_temp.at(temp.figur.korrdinate.x + 2).at(temp.figur.korrdinate.y + i).is_null)
					return 0;
			return 1;
		case figura_2:
		case figura_3:
		case figura_6:
			for (int i = 0; i < 3; i++)
				if (!m_pole_temp.at(temp.figur.korrdinate.x + 2).at(temp.figur.korrdinate.y + i).is_null)
					return 0;
			return 1;
		case figura_7:
			for (int i = 1; i < 3; i++)
				if (!m_pole_temp.at(temp.figur.korrdinate.x + 2).at(temp.figur.korrdinate.y + i).is_null)
					return 0;
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y).is_null)
				return 0;
			return 1;
		case figura_5:
			for (int i = 0; i < 2; i++)
				if (!m_pole_temp.at(temp.figur.korrdinate.x + 2).at(temp.figur.korrdinate.y + i).is_null)
					return 0;
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y + 2).is_null)
				return 0;
			return 1;
		}
		break;
	}
	case p_right:
	{
		switch (temp.figur.choice)
		{
		case 1:
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 4).at(temp.figur.korrdinate.y).is_null)
				return 0;
			return 1;
			break;
		case 2:
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 3).at(temp.figur.korrdinate.y - 1).is_null)
				return 0;
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y).is_null)
				return 0;
			return 1;
		case 0:
		case 6:
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 3).at(temp.figur.korrdinate.y - 1).is_null)
				return 0;
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 2).at(temp.figur.korrdinate.y).is_null)
				return 0;
			return 1;
		case 3:
			for (int i = 0; i < 2; i++)
				if (!m_pole_temp.at(temp.figur.korrdinate.x + 3).at(temp.figur.korrdinate.y - i).is_null)
					return 0;
			return 1;
		case 5:
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 2).at(temp.figur.korrdinate.y - 1).is_null)
				return 0;
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 3).at(temp.figur.korrdinate.y).is_null)
				return 0;
			return 1;
		}
		break;
	}
	case p_down:
	{

		switch (temp.figur.choice)
		{
		case 1:
			for (int i = 0; i < 4; i++)
				if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y - i).is_null)
					return 0;
			return 1;
			break;
		case 2:
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y).is_null)
				return 0;
			for (int i = 1; i < 3; i++)
				if (!m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - i).is_null)
					return 0;
			return 1;
		case 3:
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y - 2).is_null)
				return 0;
			for (int i = 0; i < 2; i++)
				if (!m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - i).is_null)
					return 0;
			return 1;
		case 6:
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y - 1).is_null)
				return 0;
			for (int i = 0; i < 3; i += 2)
				if (!m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - i).is_null)
					return 0;
			return 1;
			break;
		case 0:
			for (int i = 0; i < 2; i++)
				if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y - i).is_null)
					return 0;
			if (!m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - 2).is_null)
				return 0;
			return 1;
			break;
		case 5:
			if (!m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y).is_null)
				return 0;
			for (int i = 1; i < 3; i++)
				if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y - i).is_null)
					return 0;

			return 1;
			break;
		}
		break;
	}


	case p_left:
	{
		switch (temp.figur.choice)
		{
		case 1:
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y).is_null)
				return 0;
			return 1;
			break;
		case 2:
			for (int i = 0; i < 2; i++)
				if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y + i).is_null)
					return 0;
			break;
		case 0:
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y).is_null)
				return 0;
			if (!m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y + 1).is_null)
				return 0;
			return 1;
			break;
		case 6:
			if (!m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y).is_null)
				return 0;
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y + 1).is_null)
				return 0;
			return 1;
			break;
		case 3:
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y + 1).is_null)
				return 0;
			if (!m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y).is_null)
				return 0;
			return 1;
			break;
		case 5:
			if (!m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y).is_null)
				return 0;
			if (!m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y + 1).is_null)
				return 0;
			return 1;
			break;
		}
		break;
	}
	}
	return 1;
}



int Tetris::check_is_obj_behind(figura &temp,int side)
{
	if (side) //1 - right 0 - left 
	switch (temp.figur.polozh)
	{
	case p_up:
	{
		switch (temp.figur.choice)
		{
		case figura_1:
			return (!m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y + 4).is_null);
		case figura_2:
			if (m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y + 3).is_null && m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y+1).is_null)
				return 0;
			return 1;

		case figura_3:
			if (m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y + 3).is_null && m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y +3).is_null)
				return 0;
			return 1;
		case figura_4:
			if (m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y + 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y +2).is_null)
				return 0;
			return 1;
		case figura_5:
			if (m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y + 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y + 3).is_null)
				return 0;
			return 1;
		case figura_6:
		case figura_7:
			if (m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y + 3).is_null && m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y + 2).is_null)
				return 0;
			return 1;
		}
	}

	case p_right:
		switch (temp.figur.choice)
		{
		case figura_1:
			for (int i = 0; i < 4; i++)
				if (!m_pole_temp.at(temp.figur.korrdinate.x + i).at(temp.figur.korrdinate.y + 1).is_null)
					return 1;
			return 0;
		case figura_2:
			if (m_pole_temp.at(temp.figur.korrdinate.x ).at(temp.figur.korrdinate.y + 1).is_null && m_pole_temp.at(temp.figur.korrdinate.x+1).at(temp.figur.korrdinate.y ).is_null && m_pole_temp.at(temp.figur.korrdinate.x+2).at(temp.figur.korrdinate.y).is_null)
				return 0;
			return 1;
		case figura_3:
			if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y ).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 2).at(temp.figur.korrdinate.y+1).is_null)
				return 0;
			return 1;
		case figura_5:
			if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y+1).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 2).at(temp.figur.korrdinate.y + 1).is_null)
				return 0;
			return 1;
		case figura_6:
			if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y+1).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 2).at(temp.figur.korrdinate.y ).is_null)
				return 0;
			return 1;
		case figura_7:
			if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y+1).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y+1).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 2).at(temp.figur.korrdinate.y).is_null)
				return 0;
			return 1;

		}

	case p_down:
		switch (temp.figur.choice)
		{
		case figura_1:
			if (m_pole_temp.at(temp.figur.korrdinate.x ).at(temp.figur.korrdinate.y + 1).is_null )
				return 0;
			return 1;
		case figura_2:
			if (m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y ).is_null && m_pole_temp.at(temp.figur.korrdinate.x+1).at(temp.figur.korrdinate.y -1).is_null)
				return 0;
			return 1;
		case figura_3:
			if (m_pole_temp.at(temp.figur.korrdinate.x -1).at(temp.figur.korrdinate.y ).is_null && m_pole_temp.at(temp.figur.korrdinate.x+1).at(temp.figur.korrdinate.y - 1).is_null)
				return 0;
			return 1;
		case figura_5:
			if (m_pole_temp.at(temp.figur.korrdinate.x ).at(temp.figur.korrdinate.y ).is_null && m_pole_temp.at(temp.figur.korrdinate.x+1).at(temp.figur.korrdinate.y - 1).is_null)
				return 0;
			return 1;
		case figura_6:
			if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y - 1).is_null)
				return 0;
			return 1;
		case figura_7:
			if (m_pole_temp.at(temp.figur.korrdinate.x+1).at(temp.figur.korrdinate.y).is_null && m_pole_temp.at(temp.figur.korrdinate.x ).at(temp.figur.korrdinate.y - 1).is_null)
				return 0;
			return 1;
		}
	case p_left:
		switch (temp.figur.choice)
		{
		case figura_1:
			for (int i = 0; i < 4; i++)
				if (!m_pole_temp.at(temp.figur.korrdinate.x + i).at(temp.figur.korrdinate.y + 1).is_null)
					return 1;
			return 0;
		case figura_2:
			if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y + 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y+2).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 2).at(temp.figur.korrdinate.y+2).is_null)
				return 0;
			return 1;
		case figura_3:
			if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y + 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y +2).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 2).at(temp.figur.korrdinate.y + 2).is_null)
				return 0;
			return 1;
		case figura_5:
			if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y + 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y + 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 2).at(temp.figur.korrdinate.y + 1).is_null)
				return 0;
			return 1;
		case figura_6:
			if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y + 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y + 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 2).at(temp.figur.korrdinate.y + 2).is_null)
				return 0;
			return 1;
		case figura_7:
			if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y + 1).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y + 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 2).at(temp.figur.korrdinate.y + 2).is_null)
				return 0;
			return 1;

		}


	}
	else
		switch (temp.figur.polozh)
		{
		case  p_down:
		{
			switch (temp.figur.choice)
			{
			case figura_1:
				return (!m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - 4).is_null);
			case figura_2:
				if (m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y - 3).is_null && m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - 1).is_null)
					return 0;
				return 1;

			case figura_3:
				if (m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y - 3).is_null && m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - 3).is_null)
					return 0;
				return 1;
			
			case figura_5:
				if (m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y - 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - 3).is_null)
					return 0;
				return 1;
			case figura_6:
			case figura_7:
				if (m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y - 3).is_null && m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - 2).is_null)
					return 0;
				return 1;
			}
		}

		case p_left:
			switch (temp.figur.choice)
			{
			case figura_1:
				for (int i = 0; i < 4; i++)
					if (!m_pole_temp.at(temp.figur.korrdinate.x - i).at(temp.figur.korrdinate.y - 1).is_null)
						return 1;
				return 0;
			case figura_2:
				if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - 1).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 2).at(temp.figur.korrdinate.y).is_null)
					return 0;
				return 1;
			case figura_3:
				if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 2).at(temp.figur.korrdinate.y - 1).is_null)
					return 0;
				return 1;
			case figura_5:
				if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y - 1).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 2).at(temp.figur.korrdinate.y - 1).is_null)
					return 0;
				return 1;
			case figura_6:
				if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y - 1).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 2).at(temp.figur.korrdinate.y).is_null)
					return 0;
				return 1;
			case figura_7:
				if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - 1).is_null && m_pole_temp.at(temp.figur.korrdinate.x- 1).at(temp.figur.korrdinate.y - 1).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 2).at(temp.figur.korrdinate.y).is_null)
					return 0;
				return 1;

			}

		case p_up:
			switch (temp.figur.choice)
			{
			case figura_1:
				if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - 1).is_null)
					return 0;
				return 1;
			case figura_2:
				if (m_pole_temp.at(temp.figur.korrdinate.x ).at(temp.figur.korrdinate.y-1).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y - 1).is_null)
					return 0;
				return 1;
			case figura_3:
				if (m_pole_temp.at(temp.figur.korrdinate.x ).at(temp.figur.korrdinate.y+1).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y - 1).is_null)
					return 0;
				return 1;
			case figura_4:
				if (m_pole_temp.at(temp.figur.korrdinate.x +1).at(temp.figur.korrdinate.y - 1).is_null && m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - 1).is_null)
					return 0;
				return 1;
			case figura_5:
				if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y - 1).is_null)
					return 0;
				return 1;
			case figura_6:
				if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y - 1).is_null)
					return 0;
				return 1;
			case figura_7:
				if (m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y).is_null && m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - 1).is_null)
					return 0;
				return 1;
			}
		case p_right:
			switch (temp.figur.choice)
			{
			case figura_1:
				for (int i = 0; i < 4; i++)
					if (!m_pole_temp.at(temp.figur.korrdinate.x + i).at(temp.figur.korrdinate.y - 1).is_null)
						return 1;
				return 0;
			case figura_2:
				if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y - 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 2).at(temp.figur.korrdinate.y - 2).is_null)
					return 0;
				return 1;
			case figura_3:
				if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y- 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y - 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 2).at(temp.figur.korrdinate.y - 2).is_null)
					return 0;
				return 1;
			case figura_5:
				if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 1).at(temp.figur.korrdinate.y - 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x + 2).at(temp.figur.korrdinate.y - 1).is_null)
					return 0;
				return 1;
			case figura_6:
				if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y -2).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y - 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 2).at(temp.figur.korrdinate.y - 2).is_null)
					return 0;
				return 1;
			case figura_7:
				if (m_pole_temp.at(temp.figur.korrdinate.x).at(temp.figur.korrdinate.y - 1).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 1).at(temp.figur.korrdinate.y - 2).is_null && m_pole_temp.at(temp.figur.korrdinate.x - 2).at(temp.figur.korrdinate.y - 2).is_null)
					return 0;
				return 1;

			}


		}
		return 0;
}


int Tetris::check_the_povorot(figura &temp)
{
	int figura = temp.figur.choice;

	int polozh;
	if (temp.figur.polozh == p_left)
		polozh = p_up;
	else
		polozh = temp.figur.polozh + 1;
	switch (polozh)
	{
	case p_right:
		if ((temp.figur.korrdinate.x + check_dist_to_down(polozh, temp.figur.choice) < SCREEN_LENGTH) && (temp.figur.korrdinate.y - check_dist(polozh, 0, temp.figur.choice) >= 0))
		
			if (check_can_povorot(temp))
				return 1;
		return 0;
		break;
	case p_up:
		if 	((temp.figur.korrdinate.y + check_dist(polozh,1, temp.figur.choice) < SCREEN_WEIGHT)	&& (temp.figur.korrdinate.x + check_dist_to_down(polozh, temp.figur.choice) < SCREEN_LENGTH))
			if (check_can_povorot(temp))
				return 1;
		return 0;
		break;
	case p_left:
		if ((temp.figur.korrdinate.y + check_dist(polozh,1, temp.figur.choice) < SCREEN_WEIGHT) && (temp.figur.korrdinate.x - 5 >0))
			if (check_can_povorot(temp))
				return 1;
		return 0;
		break;
	case p_down:
		if ((temp.figur.korrdinate.y - check_dist(polozh, 0, temp.figur.choice) >= 0) && (temp.figur.korrdinate.x-4>=0))
			if (check_can_povorot(temp))
				return 1;
		return 0;

		break;
	}
	return 0;
}

int Tetris::check_can_povorot(figura &temp)
{
	int polozh;
	if (temp.figur.polozh == p_left)
		polozh = p_up;
	else
		polozh = temp.figur.polozh + 1;
	
	
	for (int i = 0; i < temp.figur.size_x; i++)
		for (int j = 0; j < temp.figur.size_y; j++)
			switch (polozh)
			{
			case p_up:
				if (temp.figur.korrdinate.x + i >= SCREEN_LENGTH)
					return 0;
				if (temp.figur.korrdinate.y + j >= SCREEN_WEIGHT)
					return 0;
				if ((!m_pole_temp.at(temp.figur.korrdinate.x + i).at(temp.figur.korrdinate.y + j).is_null) && (temp.figur.pole[i][j] == ZNAC_POLE))
					return 0;
				break;
			case p_right:
				if (temp.figur.korrdinate.x + j >= SCREEN_WEIGHT)
					return 0;
				if (temp.figur.korrdinate.y < i)
					return 0;
				if ((!m_pole_temp.at(temp.figur.korrdinate.x + j).at(temp.figur.korrdinate.y - i).is_null) && (temp.figur.pole[i][j] == ZNAC_POLE))
					return 0;
				break;
			case p_down:
				if (temp.figur.korrdinate.x < i)
					return 0;
				if (temp.figur.korrdinate.y <j)
					return 0;
				if ((!m_pole_temp.at(temp.figur.korrdinate.x - i).at(temp.figur.korrdinate.y - j).is_null) && (temp.figur.pole[i][j] == ZNAC_POLE))
					return 0;
				break;
			case p_left:
				if (temp.figur.korrdinate.y + i >= SCREEN_LENGTH)
					return 0;
				if (temp.figur.korrdinate.x < j)
					return 0;
				if ((!m_pole_temp.at(temp.figur.korrdinate.x - j).at(temp.figur.korrdinate.y + i).is_null) && (temp.figur.pole[i][j] == ZNAC_POLE))
					return 0;
				break;

			}
	return 1;
}


figura& figura::operator=(figura &obj)
{
	figur.choice = obj.figur.choice;
	figur.pole = obj.figur.pole;
	figur.size_x = obj.figur.size_x;
	figur.size_y = obj.figur.size_y;
	figur.korrdinate = obj.figur.korrdinate;
	figur.polozh = obj.figur.polozh;
	return *this;
}


int figura::povorot()
{
	switch (figur.choice)
	{
	case 4:  // kvadrat ne povorachivaem 
		break;
	default:
		if (figur.polozh == p_left)
			figur.polozh = p_up;
		else
			figur.polozh++;
		break;
	}
	return 0;
}

figura::figura(figura &obj)
{
	figur.choice = obj.figur.choice;
	figur.pole = obj.figur.pole;
	figur.size_x = obj.figur.size_x;
	figur.size_y = obj.figur.size_y;
	figur.korrdinate = obj.figur.korrdinate;
	figur.polozh = obj.figur.polozh;
}

figura::figura(int choice)
{
	figur.polozh = p_up;

	switch (choice)
	{
	case 1:                                                           //  ****
		figur.pole = new bool*[1];																			//
		figur.pole[0] = new bool[4];

		for (int i = 0; i < 4; i++)
			figur.pole[0][i] = ZNAC_POLE;

		figur.size_x = 1;
		figur.size_y = 4;
		figur.choice = figura_1;
		break;

	case 2:																													//    *  
		figur.pole = new bool*[2];																		//		***
		for (int i = 0; i < 2; i++)
			figur.pole[i] = new bool[3];

		figur.pole[0][0] = ZNAC_POLE;
		for (int i = 1; i < 3; i++)
			figur.pole[0][i] = ZNAC_PUSTOE_POLE;
		for (int i = 0; i < 3; i++)
			figur.pole[1][i] = ZNAC_POLE;
		figur.size_x = 2;
		figur.size_y = 3;
		figur.choice = figura_2;
		break;

	case 3:																														//    *	
		figur.pole = new bool*[2];																				//  ***
		for (int i = 0; i < 2; i++)
			figur.pole[i] = new bool[3];

		for (int i = 0; i < 2; i++)
			figur.pole[0][i] = ZNAC_PUSTOE_POLE;
		figur.pole[0][2] = ZNAC_POLE;
		for (int i = 0; i < 3; i++)
			figur.pole[1][i] = ZNAC_POLE;
		figur.size_x = 2;
		figur.size_y = 3;
		figur.choice = figura_3;
		break;

	case 4:																													//    **
		figur.pole = new bool*[2];																			//		**
		for (int i = 0; i < 2; i++)
			figur.pole[i] = new bool[2];

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				figur.pole[j][i] = ZNAC_POLE;
		figur.size_x = 2;
		figur.size_y = 2;
		figur.choice = figura_4;
		break;

	case 5:																													//	 **
		figur.pole = new bool*[2];																			//	** 
		for (int i = 0; i < 2; i++)
			figur.pole[i] = new bool[3];

		figur.pole[0][0] = ZNAC_PUSTOE_POLE;
		for (int i = 1; i < 3; i++)
			figur.pole[0][i] = ZNAC_POLE;
		figur.pole[1][2] = ZNAC_PUSTOE_POLE;
		for (int i = 0; i < 2; i++)
			figur.pole[1][i] = ZNAC_POLE;
		figur.size_x = 2;
		figur.size_y = 3;
		figur.choice = figura_5;
		break;

	case 6:																													//   *
		figur.pole = new bool*[2];																			//  ***
		for (int i = 0; i < 2; i++)
			figur.pole[i] = new bool[3];

		figur.pole[0][0] = ZNAC_PUSTOE_POLE;
		figur.pole[0][2] = ZNAC_PUSTOE_POLE;
		figur.pole[0][1] = ZNAC_POLE;
		for (int i = 0; i < 3; i++)
			figur.pole[1][i] = ZNAC_POLE;
		figur.size_x = 2;
		figur.size_y = 3;
		figur.choice = figura_6;
		break;

	case 0:																												//  ** 
		figur.pole = new bool*[2];																		//   **
		for (int i = 0; i < 2; i++)
			figur.pole[i] = new bool[3];

		figur.pole[0][2] = ZNAC_PUSTOE_POLE;
		for (int i = 0; i < 2; i++)
			figur.pole[0][i] = ZNAC_POLE;
		figur.pole[1][0] = ZNAC_PUSTOE_POLE;
		for (int i = 1; i < 3; i++)
			figur.pole[1][i] = ZNAC_POLE;

		figur.size_x = 2;
		figur.size_y = 3;
		figur.choice = figura_7;
		break;

	default:
		break;
	}


}


void Tetris::get_next_figur_to_screen(figura &temp)
{
	int x = 310;
	int y = 300;
	for (int i = 0; i < temp.figur.size_x; i++)
	{
		x= 310;
		for (int j = 0; j < temp.figur.size_y; j++)
		{
			if (temp.figur.pole[i][j])
				switch (temp.figur.choice)
				{
				case figura_1:
					drawBitmap(x, y, hBmpf1);
					break;
				case figura_2:
					drawBitmap(x, y, hBmpf2);
					break;
				case figura_3:
					drawBitmap(x, y, hBmpf3);
					break;
				case figura_4:
					drawBitmap(x, y, hBmpf4);
					break;
				case figura_5:
					drawBitmap(x, y, hBmpf5);
					break;
				case figura_6:
					drawBitmap(x, y, hBmpf6);
					break;
				case figura_7:
					drawBitmap(x, y, hBmpf7);
					break;
				}
			x += 25;
		}
		y += 25;
	}

}


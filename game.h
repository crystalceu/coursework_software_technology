/*!
\defgroup Game ����
\brief ������ ������ ��������� �������� ������� ���������� "������".

�� ������ ������ ���� ������������ ��������� ����������:
����������� ������ ���������, ������� ����������� � �������� ����������� 
������� ��������, ������ ����������� � ����������� ��������� ���������.
*/


#pragma once

/*!
\ingroup Game
\file
\brief ������������ ���� � ������������ ��������� Tetramino � ������� killstr, game. 

���� ����� �������� ����������� �������� ������� ��������� ������ - Tetramino � �������� ������� ��������� - game.
� ������� ������� �������� ���� killstr.
*/

#include <SFML/Graphics.hpp>
#include <time.h>

/*!
\ingroup Game
������� ��� �������� ��������� ���������� �������� ��������� ����� 
\param result ����������� ����� ������������ 
\return ���������� �������� ���������� result
*/
int killstr(int& result);

/*!
\ingroup Game
���������, ����������� �������� ������� ������� - ���������.
*/
struct Tetramino
{
	/*!
	\ingroup Game
	���� � ������� ��������
	*/
	int color{ };

	/*!
	\ingroup Game
	��� ��������
	*/
	int type{ };

	/*!
	\ingroup Game
	���������, ���������� ����� ��������� Tetramino � ����������� ���������� �����������.
	*/
	struct Coordinates
	{
		int x;
		int y;
	};

	Coordinates points[4]{ };

	/*!
	\ingroup Game
	��������� ������ int, ����������� ���������� ��������� �� ��� ����.
	*/
	int figures[7][4] =
	{
		1,3,5,7, // I																		
		2,4,5,7, // S																		
		3,5,4,6, // Z																		
		3,5,4,7, // T																		
		2,3,5,7, // L																		
		3,5,7,6, // J																		
		2,3,4,5, // O																		
	};

	/*!
	\ingroup Game
	�����, ������������ ��������� �� ������ ������� ����������� ���������� rand()
	\return ����� ��� void
	*/
	void generate();

	/*!
	\ingroup Game
	����� ��������� ���������
	\param window ���� ���������
	\param thatCoubes ������ ���������
	\param tetrisFeildLeft �������� ���������� �������� ���� � ����
	\param tetrisFeildTop �������� ���������� �������� ���� � ����
	\return ����� ��� void
	*/
	void drawCoubes(sf::RenderWindow& window, sf::Sprite& thatCoubes, int tetrisFeildLeft, int tetrisFeildTop);

	/*!
	\ingroup Game
	���������� ����� �� ����������� ����������, ������������ ������������ ����������� ���������
	\return ���������� �������� ���� bool
	*/
	bool check();

	/*!
	\ingroup Game
	����� ������������ ��������� ���� �� ������������ ����
	\param state ���� ����������� ��������� ���������
	\return ����� ��� void
	*/
	void MovingDown(bool& state);

	/*!
	\ingroup Game
	����� ������������ ��������� ����� ��� ������, � ����������� �� ������������ �������� where
	\param where �������� �� ������ ����� ���������� ������� ���������� ��������� 
	\return ����� ��� void
	*/
	void MovingSmwh(int where);

	/*!
	\ingroup Game
	����� �������������� ��������� ������ ��������� �� ������
	\return ����� ��� void
	*/
	void Rotating();

};

/*!
\ingroup Game
�������� ������� ����������, � ���� ������� ���������� �������� � ��������� ���� ������� ��������.
�������� ���������� ���� ��������� �������� ���������, ���� ���������� � ������ � main.
\return ����� ��� void
*/
void game();

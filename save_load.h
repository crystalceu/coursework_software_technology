/*!
\defgroup Save&Load ���������� � ��������
\brief ������ ������ ��������� ������� ���������� � ����������� �����������.

���������� ������������ ���������� ����������� ������, � ������� ������ ���� 
� ���� "��� ����������"
*/

#pragma once

/*!
\ingroup Save&Load
\file
\brief ������������ ���� � ������������ ������� save_res � print_results.

���� ����� �������� ����������� ������� ����������� ��� ������ ����������� ���� � 
.txt ����, ����������� � ���������� game/data/, � ����������� �� � ���� ���� ("��� ����������").
*/

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>

/*!
\ingroup Save&Load
������� ��� ������ �������� ���������� result � ������� ���� � �������,
��� ������ ������ ofstream � ������� time � gmtime.
\param result ����������� ����� ������������
\param save ����, ����������� ��������� ����������
\return ����� ��� void
*/
void save_res(int& result, bool& save);

/*!
\ingroup Save&Load
������� ��� ������ � ������������ ������ ������ ���� 
����� �� ���������� ����� � ������������, ���������� �������� ���� ifstream
� ������� ��� ������ �� �������� getline.
\param window ���� ���������
\return ����� ��� void
*/
void print_results(sf::RenderWindow& window);
/*!
\defgroup Save&Load Сохранения и загрузка
\brief Данный модуль описывает функции сохранения и отображения результатов.

Приложение поддерживает сохранение результатов игрока, и выводит первые пять 
в окне "Мои результаты"
*/

#pragma once

/*!
\ingroup Save&Load
\file
\brief Заголовочный файл с определением функций save_res и print_results.

Этот хедер содержит определение функций необходимых для записи результатов игры в 
.txt файл, находящийся в директории game/data/, и отображения их в окне игры ("Мои результаты").
*/

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>

/*!
\ingroup Save&Load
Функция для записи значения переменной result и текущих даты и времени,
про помощи потока ofstream и функций time и gmtime.
\param result колличиство очков пользователя
\param save флаг, позволяющий выполнить сохранение
\return имеет тип void
*/
void save_res(int& result, bool& save);

/*!
\ingroup Save&Load
Функция для чтения и последующего вывода первых пяти 
строк из текстового файла с результатами, использует файловый оток ifstream
и функцию для работы со строками getline.
\param window окно программы
\return имеет тип void
*/
void print_results(sf::RenderWindow& window);
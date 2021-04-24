/*!
\defgroup Game Игра
\brief Данный модуль описывает основную функцию приложения "Тетрис".

На данный момент игра поддерживает следующий функционал:
Возможность выбора сложности, который заключается в скорости перемещения 
игровых объектов, Запись результатов и возможность просмотра последних.
*/


#pragma once

/*!
\ingroup Game
\file
\brief Заголовочный файл с определением структуры Tetramino и функций killstr, game. 

Этот хедер содержит определение основной игровой структуры данных - Tetramino и основной функции программы - game.
И функции очитски игрового поля killstr.
*/

#include <SFML/Graphics.hpp>
#include <time.h>

/*!
\ingroup Game
Функция для удаления полностью заполненых игровыми объектами линий 
\param result колличиство очков пользователя 
\return возвращает значение переменной result
*/
int killstr(int& result);

/*!
\ingroup Game
Структура, описывающая основную игровую единицу - тетрамино.
*/
struct Tetramino
{
	/*!
	\ingroup Game
	поле с номером текстуры
	*/
	int color{ };

	/*!
	\ingroup Game
	тип тетрамин
	*/
	int type{ };

	/*!
	\ingroup Game
	Структура, являющаяся полем структуры Tetramino и описывающая координаты экземпляров.
	*/
	struct Coordinates
	{
		int x;
		int y;
	};

	Coordinates points[4]{ };

	/*!
	\ingroup Game
	Двумерный массив int, описывающий построение тетрамино по его типу.
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
	Метод, генерирующий тетрамино на основе функции стандартной библиотеки rand()
	\return имеет тип void
	*/
	void generate();

	/*!
	\ingroup Game
	Метод отрисовки тетрамино
	\param window окно программы
	\param thatCoubes спрайт тетрамино
	\param tetrisFeildLeft параметр ориентации игрового поля в окне
	\param tetrisFeildTop параметр ориентации игрового поля в окне
	\return имеет тип void
	*/
	void drawCoubes(sf::RenderWindow& window, sf::Sprite& thatCoubes, int tetrisFeildLeft, int tetrisFeildTop);

	/*!
	\ingroup Game
	Логический метод не принимающий параметров, определяющий корректность перемещения тетрамино
	\return возвращает значение типа bool
	*/
	bool check();

	/*!
	\ingroup Game
	Метод перемещающий тетрамино вниз на координатном поле
	\param state флаг разрешающий генерацию тетрамино
	\return имеет тип void
	*/
	void MovingDown(bool& state);

	/*!
	\ingroup Game
	Метод перемещающий тетрамино влево или вправо, в зависимости от передеанного значения where
	\param where значение на которе будут изменяться иксовые координаты тетрамино 
	\return имеет тип void
	*/
	void MovingSmwh(int where);

	/*!
	\ingroup Game
	Метод поворачивающий тетрамино вокруг координат ее центра
	\return имеет тип void
	*/
	void Rotating();

};

/*!
\ingroup Game
Основная функция приложения, в теле которой происходит создание и обработка всех игровых объектов.
Передает управление всем остальным функциям программы, сама вызывается в только в main.
\return имеет тип void
*/
void game();

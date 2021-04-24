#include "game.h"
#include "save_load.h"

const int M = 25; // высота поля игры										
const int N = 20; // ширина поля
const int a = 20; // сторона квадрата

int field[M][N]{}; // массив для хранения состояния ячеек поля

int killstr(int& result)
{															
	int k = M - 1;				
	for (int i = M - 1; i > 0; i--)					
	{
		int count = 0;
		for (int j = 0; j < N; j++)
		{
			if (field[i][j]) count++;
			field[k][j] = field[i][j];
		}

		if (count < N) k--;
		else result++;						
	}
	return result;
}
// генерируем координаты для нового тетрамино 
void Tetramino::generate()
{
	color = 1 + rand() % 6;
	type = rand() % 6;
	for (int i = 0; i < 4; i++)
	{
		points[i].x = figures[type][i] % 2 + 5;
		points[i].y = figures[type][i] / 2;
	}
};

void Tetramino::drawCoubes(sf::RenderWindow& window, sf::Sprite& thatCoubes, int tetrisFeildLeft, int tetrisFeildTop)
{
	// Рисуем тетрамино из класса Tetramino																		
	for (int i = 0; i < 4; i++)
	{																			
		thatCoubes.setTextureRect(sf::IntRect(color * a, 0, a, a));
		thatCoubes.setPosition(points[i].x * a, points[i].y * a);
		thatCoubes.move(tetrisFeildLeft, tetrisFeildTop);
		window.draw(thatCoubes);
	}
};

bool Tetramino::check()
{
	for (int i = 0; i < 4; i++)
	{
		if (points[i].x < 0 || points[i].x >= N || points[i].y >= M)
		{
			return false;
		}
		else if (field[points[i].y][points[i].x])
		{
			return false;
		}
	}
	return true;
}

void Tetramino::MovingDown(bool& state)
{
	int x[4]{};
	int y[4]{};
	for (int i = 0; i < 4; i++)
	{
		y[i] = points[i].y;
		x[i] = points[i].x;
	}
	for (int i = 0; i < 4; i++)
	{
		points[i].y += 1;
	}
	if (check() == false)
	{
		for (int i = 0; i < 4; i++)
		{
			points[i].y = y[i];
			field[y[i]][x[i]] = color;
		}
		generate();
		if (check() == false)
		{
			state = false;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					field[j][i] = 0;
				}
			}
		}
	}
}

void Tetramino::MovingSmwh(int where)
{
	int x[4]{};
	int y[4]{};
	for (int i = 0; i < 4; i++)
	{
		y[i] = points[i].y;
		x[i] = points[i].x;
	}
	for (int i = 0; i < 4; i++) points[i].x += where;
	if (check() == false)
	{
		for (int i = 0; i < 4; i++) points[i].x = x[i];
	}
}

void Tetramino::Rotating()
{
	int x[4]{};
	int y[4]{};
	for (int i = 0; i < 4; i++)
	{
		y[i] = points[i].y;
		x[i] = points[i].x;
	}
	int originX = points[1].x; //центры																  
	int originY = points[1].y; //вращения																  
	for (int i = 0; i < 4; i++)
	{
		int dy = points[i].y - originY;																	  
		int dx = points[i].x - originX;																	  
		points[i].x = originX - dy;																	  
		points[i].y = originY + dx;																	  
	}
	if (check() == false)
	{
		for (int i = 0; i < 4; i++) points[i].x = x[i];
	}
}

void game()
{
	//флаг локализации
	bool local = true;

	srand(time(0));
	int result{ 0 };
	bool state = true;

	Tetramino tetramino;
	tetramino.generate();


	sf::RenderWindow window(sf::VideoMode(800, 960), "Tetris");

	// Создание и загрузка текстур для отрисовки окна с игрой																								  
	sf::Texture coubesTexture, gameBackground, tetrisBackground;
	coubesTexture.loadFromFile("images/coubes.png");
	gameBackground.loadFromFile("images/GameBackground.png");
	tetrisBackground.loadFromFile("images/TetrisField.png");																									  
	sf::Sprite coubes(coubesTexture), gameBg(gameBackground), tetrisBg(tetrisBackground);

	// Переменные для таймера и задержки																							  
	float timer = 0;
	float delay1 = 0.6;
	float delay2 = 0.1;
	float delay = delay1;
	int simplek = 1;
	int mediumk = 2;
	int hardk = 4;


	// Часы (таймер)																												  
	sf::Clock clock;
	// Создание и загрузка текстур для отрисовки окна с настройками
	sf::Texture settingsTexture, simpleTexture, mediumTexture, hardTexture;
	settingsTexture.loadFromFile("images/SettingsBackground.jpg");
	simpleTexture.loadFromFile("images/1simple.png");
	mediumTexture.loadFromFile("images/2medium.png");
	hardTexture.loadFromFile("images/3hard.png");
	sf::Sprite settingsBg(settingsTexture), simple(simpleTexture), medium(mediumTexture), hard(hardTexture);
	settingsBg.setPosition(0, 0);
	simple.setPosition(30, 400);
	medium.setPosition(95, 470);
	hard.setPosition(30, 540);
	
	//EN
	sf::Texture settingsTexture_en, simpleTexture_en, mediumTexture_en, hardTexture_en, t_en, t_ru;
	settingsTexture_en.loadFromFile("images/SettingsBackground.en.jpg");
	simpleTexture_en.loadFromFile("images/1simple.en.png");
	mediumTexture_en.loadFromFile("images/2medium.en.png");
	hardTexture_en.loadFromFile("images/3hard.en.png");
	t_en.loadFromFile("images/english.png");
	t_ru.loadFromFile("images/russian.png");
	sf::Sprite settingsBg_en(settingsTexture_en), simple_en(simpleTexture_en), medium_en(mediumTexture_en), hard_en(hardTexture_en), s_en(t_en), s_ru(t_ru);
	settingsBg_en.setPosition(0, 0);
	simple_en.setPosition(30, 400);
	medium_en.setPosition(30, 460);
	hard_en.setPosition(30, 520);
	s_en.setPosition(70,890);
	s_ru.setPosition(70,790);

	// Создание и загрузка текстур для отрисовки окна с меню
	sf::Texture menuTextureStart, menuTextureResults, menuTextureSettings, menuTextureExit, aboutTexture, menuBackground, isaboutwindow;
	menuTextureStart.loadFromFile("images/1start.png");
	menuTextureResults.loadFromFile("images/2results.png");
	menuTextureSettings.loadFromFile("images/3set.png");
	menuTextureExit.loadFromFile("images/4exit.png");
	aboutTexture.loadFromFile("images/5about.png");
	menuBackground.loadFromFile("images/menu.jpg");
	isaboutwindow.loadFromFile("images/isabout.jpg");
	sf::Sprite start(menuTextureStart), results(menuTextureResults), settings(menuTextureSettings), exit(menuTextureExit), about(aboutTexture), menuBg(menuBackground), isabout(isaboutwindow);
	start.setPosition(124, 130);
	results.setPosition(50, 180);
	settings.setPosition(71, 230);
	about.setPosition(121, 280);
	exit.setPosition(131, 330);
	menuBg.setPosition(0, 0);
	isabout.setPosition(0, 0);

	//EN
	sf::Texture menuTextureStart_en, menuTextureResults_en, menuTextureSettings_en, menuTextureExit_en, aboutTexture_en, menuBackground_en, isaboutwindow_en;
	menuTextureStart_en.loadFromFile("images/1start.en.png");
	menuTextureResults_en.loadFromFile("images/2results.en.png");
	menuTextureSettings_en.loadFromFile("images/3set.en.png");
	menuTextureExit_en.loadFromFile("images/4exit.en.png");
	aboutTexture_en.loadFromFile("images/5about.en.png");
	menuBackground_en.loadFromFile("images/menu.jpg");
	isaboutwindow_en.loadFromFile("images/isabout.en.jpg");
	sf::Sprite start_en(menuTextureStart_en), results_en(menuTextureResults_en), settings_en(menuTextureSettings_en), exit_en(menuTextureExit_en), about_en(aboutTexture_en), menuBg_en(menuBackground_en), isabout_en(isaboutwindow_en);
	start_en.setPosition(30, 80);
	results_en.setPosition(30, 140);
	settings_en.setPosition(30, 200);
	about_en.setPosition(30, 260);
	exit_en.setPosition(30, 320);
	menuBg_en.setPosition(0, 0);
	isabout_en.setPosition(0, 0);

	// Создание и загрузка текстуры для отрисовки окна с результатами
	sf::Texture resultsTexture;
	resultsTexture.loadFromFile("images/ResultsBackground.jpg");
	sf::Sprite resultsBg(resultsTexture);
	resultsBg.setPosition(0, 0);

	//EN
	sf::Texture resultsTexture_en;
	resultsTexture_en.loadFromFile("images/ResultsBackground.en.jpg");
	sf::Sprite resultsBg_en(resultsTexture_en);
	resultsBg_en.setPosition(0, 0);

	// Флаги активности отрисовывающихся "окон" (в кавычках, потому что все рисуется на самом деле в одном окне)
	bool isMenu = true;
	bool isAbout = false;
	bool isGame = false;
	bool save = false;
	bool isResults = false;
	bool isSettings = false;
																  
	while (window.isOpen())
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
													  
		float time = clock.getElapsedTime().asSeconds(); // Время с начала отсчета переведеное в секунды
		clock.restart();
		timer += time;
																							  
		sf::Event event;
		while (window.pollEvent(event))
		{															  
			if (event.type == sf::Event::Closed) window.close();
			if (isMenu)
			{
				window.clear();
				if (local) 
				{
					window.draw(menuBg);
					window.draw(start);
					window.draw(results);
					window.draw(settings);
					window.draw(about);
					window.draw(exit);
				}
				else 
				{
					window.draw(menuBg_en);
					window.draw(start_en);
					window.draw(results_en);
					window.draw(settings_en);
					window.draw(about_en);
					window.draw(exit_en);
				}
				window.display();
			}
			if (isResults) 
			{
				window.clear();
				if(local) window.draw(resultsBg);
				else window.draw(resultsBg_en);
				print_results(window);
				window.display();
			}
			if (isSettings)
			{
				window.clear();
				if (local) 
				{
					window.draw(settingsBg);
					window.draw(simple);
					window.draw(medium);
					window.draw(hard);
				}
				else 
				{
					window.draw(settingsBg_en);
					window.draw(simple_en);
					window.draw(medium_en);
					window.draw(hard_en);
				}
				window.draw(s_ru);
				window.draw(s_en);
				window.display();
			}
			if (isGame)
			{																		  
				if (event.type == sf::Event::KeyPressed)
				{																					  
					if (event.key.code == sf::Keyboard::Left) tetramino.MovingSmwh(-1);				// Влево																		  
					else if (event.key.code == sf::Keyboard::Right) tetramino.MovingSmwh(1);			// Вправо
					else if (event.key.code == sf::Keyboard::Up) tetramino.Rotating();						// Поворот
				}															  
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) delay = delay2;							// Ускорение движения вниз
			}
			if (event.type == sf::Event::MouseMoved && isMenu) // Подсветка клавиш при наведении на них в меню
			{
				start.setColor(sf::Color::White); start_en.setColor(sf::Color::White);
				results.setColor(sf::Color::White); results_en.setColor(sf::Color::White);
				settings.setColor(sf::Color::White); settings_en.setColor(sf::Color::White);
				about.setColor(sf::Color::White); about_en.setColor(sf::Color::White);
				exit.setColor(sf::Color::White); exit_en.setColor(sf::Color::White);
				if ((mouse_position.x >= 124) && (mouse_position.x <= 257) && (mouse_position.y >= 130) && (mouse_position.y <= 181)) start.setColor(sf::Color::Cyan); 
				if ((mouse_position.x >= 30) && (mouse_position.x <= 248) && (mouse_position.y >= 80) && (mouse_position.y <= 146)) start_en.setColor(sf::Color::Cyan);
				if ((mouse_position.x >= 50) && (mouse_position.x <= 330) && (mouse_position.y >= 180) && (mouse_position.y <= 231)) results.setColor(sf::Color::Cyan); 
				if ((mouse_position.x >= 30) && (mouse_position.x <= 247) && (mouse_position.y >= 150) && (mouse_position.y <= 217)) results_en.setColor(sf::Color::Cyan);
				if ((mouse_position.x >= 71) && (mouse_position.x <= 309) && (mouse_position.y >= 230) && (mouse_position.y <= 277)) settings.setColor(sf::Color::Cyan);
				if ((mouse_position.x >= 30) && (mouse_position.x <= 502) && (mouse_position.y >= 200) && (mouse_position.y <= 271)) settings_en.setColor(sf::Color::Cyan);
				if ((mouse_position.x >= 121) && (mouse_position.x <= 259) && (mouse_position.y >= 280) && (mouse_position.y <= 320)) about.setColor(sf::Color::Cyan); 
				if ((mouse_position.x >= 30) && (mouse_position.x <= 223) && (mouse_position.y >= 260) && (mouse_position.y <= 314)) about_en.setColor(sf::Color::Cyan);
				if ((mouse_position.x >= 131) && (mouse_position.x <= 250) && (mouse_position.y >= 330) && (mouse_position.y <= 370)) exit.setColor(sf::Color::Cyan); 
				if ((mouse_position.x >= 30) && (mouse_position.x <= 122) && (mouse_position.y >= 320) && (mouse_position.y <= 371)) exit_en.setColor(sf::Color::Cyan);
			} 
			if (event.type == sf::Event::MouseMoved && isSettings) // Подсветка клавиш при наведении на них в настройках
			{
				simple.setColor(sf::Color::White); simple_en.setColor(sf::Color::White);
				medium.setColor(sf::Color::White); medium_en.setColor(sf::Color::White);
				hard.setColor(sf::Color::White); hard_en.setColor(sf::Color::White);
				s_en.setColor(sf::Color::White); s_ru.setColor(sf::Color::White);
				if ((mouse_position.x >= 30) && (mouse_position.x <= 380) && (mouse_position.y >= 400) && (mouse_position.y <= 468)) simple.setColor(sf::Color::Cyan); 
				if ((mouse_position.x >= 30) && (mouse_position.x <= 100) && (mouse_position.y >= 400) && (mouse_position.y <= 465)) simple_en.setColor(sf::Color::Cyan);
				if ((mouse_position.x >= 95) && (mouse_position.x <= 277) && (mouse_position.y >= 470) && (mouse_position.y <= 536)) medium.setColor(sf::Color::Cyan);
				if ((mouse_position.x >= 30) && (mouse_position.x <= 194) && (mouse_position.y >= 460) && (mouse_position.y <= 519)) medium_en.setColor(sf::Color::Cyan);
				if ((mouse_position.x >= 30) && (mouse_position.x <= 378) && (mouse_position.y >= 540) && (mouse_position.y <= 590)) hard.setColor(sf::Color::Cyan);
				if ((mouse_position.x >= 30) && (mouse_position.x <= 205) && (mouse_position.y >= 520) && (mouse_position.y <= 572)) hard_en.setColor(sf::Color::Cyan);

				if ((mouse_position.x >= 70) && (mouse_position.x <= 228) && (mouse_position.y >= 890) && (mouse_position.y <= 939)) s_en.setColor(sf::Color::Cyan);
				if ((mouse_position.x >= 70) && (mouse_position.x <= 247) && (mouse_position.y >= 790) && (mouse_position.y <= 862)) s_ru.setColor(sf::Color::Cyan);
			}
			//ускорение, в зависимости от уровня сложности
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left && (isSettings))
			{
				if ((mouse_position.x >= 30) && (mouse_position.x <= 380) && (mouse_position.y >= 400) && (mouse_position.y <= 468) && local == true)
				{
					delay1 /= simplek; delay2 /= simplek;
				}
				if ((mouse_position.x >= 30) && (mouse_position.x <= 100) && (mouse_position.y >= 400) && (mouse_position.y <= 465) && local == false)
				{
					delay1 /= simplek; delay2 /= simplek;
				}
				if ((mouse_position.x >= 95) && (mouse_position.x <= 277) && (mouse_position.y >= 470) && (mouse_position.y <= 536) && local == true)
				{
					delay1 /= mediumk; delay2 /= mediumk;
				}
				if ((mouse_position.x >= 30) && (mouse_position.x <= 194) && (mouse_position.y >= 460) && (mouse_position.y <= 519) && local == false)
				{
					delay1 /= mediumk; delay2 /= mediumk;
				}
				if ((mouse_position.x >= 30) && (mouse_position.x <= 378) && (mouse_position.y >= 540) && (mouse_position.y <= 590) && local == true)
				{
					delay1 /= hardk; delay2 /= hardk;
				}
				if ((mouse_position.x >= 30) && (mouse_position.x <= 205) && (mouse_position.y >= 520) && (mouse_position.y <= 572) && local == false)
				{
					delay1 /= hardk; delay2 /= hardk;
				}
				//RU
				if ((mouse_position.x >= 70) && (mouse_position.x <= 247) && (mouse_position.y >= 790) && (mouse_position.y <= 862))
				{
					local = true;
				}
				//EN
				if ((mouse_position.x >= 70) && (mouse_position.x <= 228) && (mouse_position.y >= 890) && (mouse_position.y <= 939))
				{
					local = false;
				}
			}
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left && (isMenu)) // Переключение между кнопками меню
			{
				//старт
				if ((mouse_position.x >= 124) && (mouse_position.x <= 257) && (mouse_position.y >= 130) && (mouse_position.y <= 181) && local == true)
				{
					isMenu = false;
					isGame = true;
					state = true;
				}
				if ((mouse_position.x >= 30) && (mouse_position.x <= 248) && (mouse_position.y >= 80) && (mouse_position.y <= 146) && local == false)
				{
					isMenu = false;
					isGame = true;
					state = true;
				}
				//результаты
				if ((mouse_position.x >= 50) && (mouse_position.x <= 330) && (mouse_position.y >= 180) && (mouse_position.y <= 231) && local == true)
				{
					isMenu = false;
					isResults = true;
				}
				if ((mouse_position.x >= 30) && (mouse_position.x <= 247) && (mouse_position.y >= 150) && (mouse_position.y <= 217) && local == false)
				{
					isMenu = false;
					isResults = true;
				}
				//настройки
				if ((mouse_position.x >= 71) && (mouse_position.x <= 309) && (mouse_position.y >= 230) && (mouse_position.y <= 277) && local == true)
				{
					isMenu = false;
					isSettings = true;
				}
				if ((mouse_position.x >= 30) && (mouse_position.x <= 502) && (mouse_position.y >= 200) && (mouse_position.y <= 271) && local == false)
				{
					isMenu = false;
					isSettings = true;
				}
				//о нас
				if ((mouse_position.x >= 121) && (mouse_position.x <= 259) && (mouse_position.y >= 280) && (mouse_position.y <= 320) && local == true)
				{
					isMenu = false;
					isAbout = true;
					window.clear();
					window.draw(isabout);
					window.display();
				}
				if ((mouse_position.x >= 30) && (mouse_position.x <= 223) && (mouse_position.y >= 260) && (mouse_position.y <= 314) && local == false)
				{
					isMenu = false;
					isAbout = true;
					window.clear();
					window.draw(isabout_en);
					window.display();
				}
				//выход
				if ((mouse_position.x >= 131) && (mouse_position.x <= 250) && (mouse_position.y >= 330) && (mouse_position.y <= 370) && local == true) window.close();
				if ((mouse_position.x >= 30) && (mouse_position.x <= 122) && (mouse_position.y >= 320) && (mouse_position.y <= 371) && local == false) window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && isMenu == false) // Нажатие на ESC
			{
				isGame = false;
				isResults = false;
				isSettings = false;
				save = true;
				save_res(result, save);
				isAbout = false;
				isMenu = true;
			}
		}


		if (isGame)
		{
			if (timer > delay && state)
			{
				tetramino.MovingDown(state);
				timer = 0;
			}

			killstr(result);

			delay = delay1;

																					  
			window.clear();

			// Отрисовка фона игры и игрового поля																											  
			window.draw(gameBg);
			window.draw(tetrisBg);

			int tetrisFeildTop{ 100 };
			int tetrisFeildLeft{ 0 };

			// Выводим количество заработанных очков
			sf::Font font;
			font.loadFromFile("images/mistral.ttf");
			sf::Text text;
			text.setFont(font);
			std::string resultStr;
			if (local == true) resultStr = "Moi ochki: " + std::to_string(result);
			if (local == false) resultStr = "Score: " + std::to_string(result);

			text.setString(resultStr);
			text.setCharacterSize(40);
			text.setFillColor(sf::Color::Cyan);
			text.setStyle(sf::Text::Bold | sf::Text::Underlined);
			text.setPosition(135, 10);
			if (state)
			{
				for (int varHeight = 0; varHeight < M; varHeight++)
				{
					for (int j = 0; j < N; j++)
					{
						if (field[varHeight][j] == 0)
						{
							coubes.setTextureRect(sf::IntRect(8 * a, 0, a, a)); //в спрайте 8 квадратик - прозрачный; наше поле состоит из квадратиков, которые по else разукрашиватся в нужный цвет(фигуру которая туда помещается)
							coubes.setPosition(tetrisFeildLeft + j * a, tetrisFeildTop + varHeight * a);
							window.draw(coubes);
						}
						else coubes.setTextureRect(sf::IntRect(field[varHeight][j] * a, 0, a, a)); //цвет помещаемой фигуры															  
						coubes.setPosition(tetrisFeildLeft + j * a, tetrisFeildTop + varHeight * a);
						window.draw(coubes);
					}
				}
				tetramino.drawCoubes(window, coubes, tetrisFeildLeft, tetrisFeildTop);
				window.draw(text);
			}
			else
			{
				// Выводим GAME OVER и количество баллов
				std::string endresult;
				if (local == true) endresult ="Tvoy chet: " + std::to_string(result);
				if (local == false) endresult = "Final score: " + std::to_string(result);
				text.setString(endresult);
				text.setCharacterSize(100);
				text.setFillColor(sf::Color::Color(246, 64, 105));
				text.setStyle(sf::Text::Bold);
				text.setPosition(200, 2);
				window.clear();
				sf::Texture asukaTexture;
				asukaTexture.loadFromFile("images/asuka.png");																											  
				sf::Sprite gameOver(asukaTexture);
				gameOver.setPosition(0, 0);
				window.draw(gameOver);
				window.draw(text);
			}																										  
			window.display();
		}
	}
}
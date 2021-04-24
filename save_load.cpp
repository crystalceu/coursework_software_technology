#define _CRT_SECURE_NO_DEPRECATE
#include "save_load.h"

void save_res(int& result, bool& save) // Сохраняем результат, чтобы отображать его в результатах
{
	time_t now = time(0);
	tm* gmtm = gmtime(&now);
	std::stringstream strbuf(std::stringstream::out);
	std::ofstream fout("data/results.txt", std::ios::app);
	strbuf << fout.rdbuf();
	fout << std::to_string(result) << ' ' << asctime(gmtm);
	fout << strbuf.str();
	fout.close();
	result = 0;
	save = false;
}

void print_results(sf::RenderWindow& window)
{
	sf::Font font;
	font.loadFromFile("images/mistral.ttf");
	sf::Text text_res;
	text_res.setFont(font);
	text_res.setCharacterSize(40);
	text_res.setFillColor(sf::Color::Color(246, 62, 105));
	std::string result_Str = "Moi rezylitati: ";

	std::string s; // сюда будем класть считанные строки
	std::ifstream file("data/results.txt"); // файл из которого читаем

	//пока не конец строки
	int num(1);
	while (num < 6)
	{
		int num1(6);
		std::string bufStr;
		window.draw(text_res);
		getline(file, s);
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ' ') bufStr += s[i];
			else if (s[i] == ' ' || i == s.length() - 1)
			{
				if (bufStr.length() != 0)
				{
					text_res.setString(bufStr);
					text_res.setPosition(120 * (7 - num1), 100 * (num + 3));
					window.draw(text_res);
					num1--;
				}
				bufStr = "";
			}
		}
		num++;
	}
	file.close();
}
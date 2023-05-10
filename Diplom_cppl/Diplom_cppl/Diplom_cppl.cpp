#include <iostream>
#include <string>
#include <Windows.h>
#include "Parser.h"

#pragma execution_character_set("utf-8")

int main(int argc, char** argv) {

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);
	
	std::string section = "[Section1]",
				user_section = "",
				variable = "var1",
				path = "",
				in_skb = "[",
				out_skb = "]";
	int action = 1;

	std::cout << "Введите путь и имя файла: ";
	std::cin >> path;
	Parser parser(path);

	do {
		system("cls");

		do {
			std::cout << "Найти ещё переменную - 1, вывести имена переменных - 2, "
				" вывести имена секторов - 3, вывести весь ini файл - 4, выйти - 0" << "\n";
			std::cin >> action;
		} while (action < 0 && action > 4); 
		
		try {
			
			if (action == 1) {
				std::cout << "Введите имя секции: ";
				std::cin >> user_section;
				section = in_skb + user_section + out_skb;
				std::cout << "Введите имя переменной: ";
				std::cin >> variable;
				auto result = parser.getValue<double>(section, variable);
				std::cout << "Значение " << section << " в переменной " <<
					variable << ": = " << result << "\n";
			}
			if (action == 2) {
				auto nameVar = parser.getVarName();
				std::cout << "Имена переменных: " << "\n";
				for (const auto& st : nameVar) {
					std::cout << st << "\n";
				}
			}
			if (action == 3) {
				auto nameSec = parser.getSecName();
				std::cout << "Имена секторов: " << "\n";
				for (const auto& st : nameSec) {
					std::cout << st << "\n";
				}
			}
			if (action == 4) {
				parser.printIni();
			}
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << "\n";
		}
	} while (action);

	/*try {
		std::cout << parser.getValue<std::string>("Section1", "var1") << std::endl;
		std::cout << parser.getValue<double>("Section1", "var1") << std::endl;
		std::cout << parser.getValue<int>("Section1", "var1") << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << "\n";
	}*/

	return 0;
}
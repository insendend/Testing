#include "Menu.h"
#include "Test.h"
#include "Funcs.h"

int main()
{
	setlocale(LC_ALL, "rus");

	try
	{
		try
		{
			Menu m;	
			
			// главное меню
			Menu::Choice Action = m.MainChoice();

			// ѕроверка на выход
			if (Action == Menu::Choice::EXIT)
				return 0;

			// выбор самого теста
			const std::string testName = m.TestChoice();
			
			// создаем объект, инициализиру€ тестом
			Test first(testName);

			// выполн€ем сооветствующее действие над тестом
			first.Do(Action);
		}
		catch (const std::exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
	catch (...)
	{
		std::cout << "Unknown exception" << std::endl;
	}

	return 0;
}
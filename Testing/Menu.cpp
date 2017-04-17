#include "Menu.h"

Menu::Menu(void)
{ 
	// инициализация вектора с названиями тестов, если они есть
	// и вывод соответствующего сообщения, если их нет
	Search(this->vTestNames);
}

// корректность отображения слова
void Menu::OutputWord(const size_t &i) const throw()
{
	//	1	тест
	//	2-4 теста
	//	5+	тестов
	if (i == 1)
		std::cout << "Найден " << i << " тест, введите \"1\", чтобы его ";
	else if (i >= 2 && i <= 4)
		std::cout << "Найдено " << i << " теста, выбирите тот, который хотите ";
	else
		std::cout << "Найдено " << i << " тестов, выбирите тот, который хотите ";
}

// отображение пунктов меню
void Menu::Main(void) const throw()
{
	std::cout << "1. Пройти тест" << std::endl;
	std::cout << "2. Редактировать тест" << std::endl;
	std::cout << "3. Показать вопросы теста" << std::endl;
	std::cout << "4. Выход" << std::endl;
	std::cout << "Ваш выбор -> ";
}

// отображение пунктов меню
void Menu::Edit(void) const throw()
{
	std::cout << "1. Добавить новый вопрос" << std::endl;
	std::cout << "2. Удалить существующий вопрос" << std::endl;
	std::cout << "3. Выход" << std::endl;
	std::cout << "Ваш выбор -> ";
}

// отображение списка тестов
void Menu::TestList(void) const	throw()
{
	std::cout << "Выбирите тест" << std::endl;
	auto cit = this->vTestNames.cbegin();
	for (size_t i = 0; cit != this->vTestNames.cend(); ++cit, ++i)
		std::cout << i + 1 << ". "
		<< this->vTestNames[i].substr( 0, this->vTestNames[i].find(".test") ) // название теста без расширения
		<< std::endl;
	
	std::cout << "Ваш выбор -> ";
}

// пользовательский ввод (выбор действия)
Menu::Choice Menu::MainChoice(void) const
{
	size_t choice = 0;
	std::string buf;

	do
	{
		// вывод пунктов меню
		(*this).Main();

		std::getline(std::cin, buf);
		system("cls");

		try
		{
			// преобразуем из строки в size_t
			choice = static_cast < size_t > (stoi(buf));
		}

		// исключение stoi()
		catch (const std::invalid_argument &ia)
		{
			std::cout << ia.what() << std::endl;
		}

	} while (choice > 4 || choice < 1);

	// конвертируем из size_t в Choice
	return static_cast <Choice> (choice);
}

// пользовательский ввод (выбор теста)
const std::string& Menu::TestChoice(void) const 
{
	size_t testNumber = 0;
	std::string buf;

	do
	{
		// вывод списка тестов
		(*this).TestList();

		std::getline(std::cin, buf);
		system("cls");

		try
		{
			// преобразуем из строки в size_t
			testNumber = static_cast < size_t > (stoi(buf));
		}

		// исключение stoi()
		catch (const std::invalid_argument &ia)
		{
			std::cout << ia.what() << std::endl;
		}

	} while (testNumber > this->vTestNames.size() || testNumber < 1);

	// возвращаем элемент вектора (название теста)
	return this->vTestNames[testNumber - 1];
}
#include "Test.h"
#include <conio.h>

// конструктор с параметром
Test::Test(const std::string &testName) : points(0), testName(testName)
{
	// буфер для текста всего теста
	std::string buf;

	// считывание из файла в буфер
	ReadFrom(this->testName, buf);

	// разбитие буфера на отдельные части (вопрос, ответы, правильный ответ)
	// и инициализация переменной класса
	InitAll(buf);

	// перетасовка вектора вопросов
	std::random_shuffle(this->questions.begin(), this->questions.end(), Test::Pred());
}

// разделение буфера на лексемы
void Test::InitAll(std::string &buf)
{
	// разделители
	const std::string leksemes = std::string("\n\n");

	// позиции начала и конца первого вопроса
	int posStart = 0;
	int posEnd = buf.find(leksemes, posStart);

	// если найдена лексема, записываем и ищем дальше
	while (posStart != std::string::npos)
	{
		// неотредактированный вопрос
		std::string tmp = buf.substr(posStart, posEnd - posStart);

		// редактируем вопрос, разбивая на: вопрос, верный ответ и варианты ответов
		Question q(tmp);
		
		// добавляем в список вопросов
		questions.push_back(q);

		// ищем позициии следующее слова
		posStart = buf.find_first_not_of(leksemes, posEnd);
		posEnd = buf.find(leksemes, posStart);
	}
}

// начало теста
void Test::Start(void)
{
	for (const auto &i : this->questions)
	{		
		// вывод вопроса с вариантами ответа
		std::cout << i;
		
		// выбор пользователя среди всех вариантов ответов
		size_t posInVector = this->UserInputAnswer( i.GetVecAnswers().size() );

		// сравнение выбранного варианта ответа с правильным
		if ( i.GetVecAnswers()[posInVector] == i.GetRightAnswer() )
			this->points++;
	}
}

// редактирование теста
Test::ForEdit Test::EditChoice(void)
{
	size_t choice = 0;
	std::string buf;
	Menu m;

	do
	{
		// вывод пунктов меню редактирования
		m.Edit();

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

	} while (choice > 3 || choice < 1);

	return static_cast <ForEdit> (choice);
}

// отображение вопросов теста
void Test::Show(void) const throw()
{
	// порядковый номер вопроса
	size_t iCount = 1;
	
	// вывод вопросов
	for (const auto &i : this->questions)
		std::cout << iCount++ <<". " << i.GetTextQustion() << std::endl;
}

// действие над тестом
void Test::Do(const Menu::Choice &ch)
{
	switch (ch)
	{
	
	// прохождение теста
	case Menu::Choice::PASS:
		this->Start();
		std::cout << "U got " << this->GetPoints() << "/" << this->questions.size() << " points" << std::endl;
		this->Saving();
		break;
	
	// редактирование теста
	case Menu::Choice::EDIT:
		this->Edit( this->EditChoice() );
		break;
	
	// отображение вопросов теста
	case Menu::Choice::SHOW:
		this->Show();
		break;
	
	// выход из программы
	case Menu::Choice::EXIT:
		exit(0);
	
	default:
		throw (std::exception("Main Switch Default"));
	}
}

// ввод ответа от пользователя
size_t Test::UserInputAnswer(const size_t &index)
{
	size_t choice = 1;
	std::string buf;

	do
	{
		std::cout << "Ваш выбор -> ";
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

	} while (choice > index || choice < 1);

	// позиция варианта ответа в векторе ответов
	return --choice;
}

// результаты прохождения теста
const size_t &Test::GetPoints()
{
	return this->points;
}

// реализация редактирования теста
void Test::Edit(const Test::ForEdit &ch)
{
	switch (ch)
	{
	
	// добавление вопросов теста
	case Test::ForEdit::ADD:
		this->AddQuestion();
		break;
	
	// удаление вопроса по вводу пользователя
	case Test::ForEdit::DELETE:
		this->DeleteQuestion();
		break;
	
	// выход
	case Test::ForEdit::EXIT:
		exit(0);
		break;
	
	default:
		throw (std::exception("Edit Switch Default"));
	}
}

// добавление вопроса
void Test::AddQuestion(void)
{
	// добавляем текст вопроса в буфер
	std::cout << "Введите текст вопроса:" << std::endl;
	std::string buf;
	std::getline(std::cin, buf);
	buf.push_back('\n');

	// туда же добавляем правильный вариант ответа с меткой
	std::cout << "Введите правильный ответ:" << std::endl;
	std::string tmp;
	std::getline(std::cin, tmp);
	buf += tmp;
	buf += std::string(" (верно)");
	buf.push_back('\n');
	tmp.clear();

	// добавляем другой вариант ответа
	std::cout << "Добавьте еще хотя бы один вариант:" << std::endl;
	std::getline(std::cin, tmp);
	buf += tmp;
	buf.push_back('\n');
	tmp.clear();
	
	// добавляем аналогичным образом по желанию пользователя
	char c;
	do
	{
		std::cout << "Добавить еще вариант?(y - да, n - нет) -> ";
		c = _getche();
		std::cout << std::endl;
		if (c == 'y')
		{
			std::cout << "Введите следующий вариант ответа:" << std::endl;
			std::getline(std::cin, tmp);
			buf += tmp;
			buf.push_back('\n');
			tmp.clear();
		}
	} while (c != 'n');
	
	// добавление текста вопроса в файл
	WriteTo(testName, buf);
	
	// добавление вопроса в вектор в памяти
	this->questions.push_back(Question(buf));

	// запускаем себя же, если нужно добавить еще вопрос
	do
	{
		system("cls");
		std::cout << "Хотите добавить еще вопрос?(y - да, n - нет) -> ";
		c = _getche();

		system("cls");

		if (c == 'y')
			this->AddQuestion();

	} while (c != 'n');
}

// удадение вопроса по вводу пользователя
void Test::DeleteQuestion(void)
{
	// выводим список вопросов
	std::cout << "Какой из вопрос желаете удалить?" << std::endl;
	this->Show();
	
	std::string tmp;
	size_t questNumber = 0;	// порядковый номер вопроса в списке
	
	do
	{
		std::cout << "Ваш выбор -> ";
		std::getline(std::cin, tmp);
		system("cls");

		try
		{
			// преобразуем из строки в size_t
			questNumber = static_cast < size_t > (stoi(tmp));
		}

		// исключение stoi()
		catch (const std::invalid_argument &ia)
		{
			std::cout << ia.what() << std::endl;
		}

	} while (questNumber > this->questions.size() || questNumber < 1);

	// порядковый номер вопроса в векторе вопросов
	questNumber--;
	 
	// убираем вопрос из файла
	Delete( this->questions[questNumber] );	

	// убираем вопрос из вектора в памяти
	this->questions.erase(this->questions.cbegin() + questNumber);
}

// удаление из файла вопроса из параметров
void Test::Delete(const Question &q)
{
	// считываем в буфер из файла
	std::string buf;
	ReadFrom(this->testName, buf);

	// находим начало и конец указанного вопроса с ответами
	int posStart = buf.find(q.GetTextQustion());
	int posEnd = buf.find("\n\n", posStart);

	// стираем его из буфера
	buf.erase(posStart, posEnd);

	// открытие файла с тестом для перезаписи
	std::ofstream ofs(this->testName, std::ios::trunc);

	if (!ofs.is_open())
		throw std::exception("Can't open file with test");
	
	// записываем обратно в файл
	ofs.write(&buf[0], buf.length());
}

// сохранение результатов прохождения теста
void Test::Saving(void)
{
	std::cout << "Хотите сохранить результат?(y - да) -> ";
	char c = _getche();
	std::cout << std::endl;
	if (c == 'y')
	{
		std::cout << "Ваше имя? ";
		std::string name;
		std::getline(std::cin, name);

		std::ofstream ofs("result.txt", std::ios::app);
		
		if (!ofs.is_open())
			throw std::exception("Can't open file with results");

		// записываем в файл
		ofs << name 
			<< '\t' 
			<< this->testName 
			<< '\t' 
			<< static_cast <double> (this->points)  / static_cast <double> (this->questions.size()) * 100
			<< "%" 
			<< std::endl;
	}
}
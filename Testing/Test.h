#pragma once
#include <ctime>
#include <vector>
#include <algorithm>
#include "Question.h"
#include "Menu.h"
#include "Funcs.h"

class Question;

class Test
{
	// вектор вопросов с ответами
	std::vector < Question > questions;

	// имя выбранного теста
	std::string testName;

	// предикат для тасовки вопросов
	struct Pred
	{
		Pred(void)
		{
			srand(static_cast < unsigned int > ( time(nullptr) ) );
		}
		int operator()(const int &i) const throw()
		{
			return rand() % i;
		}
	};

	// пункты меню для редактирования теста
	enum ForEdit { ADD = 1, DELETE, EXIT };

	// результат прохождения теста
	size_t points;

public:

	// конструктор по умолчанию
	Test() = delete;

	// конструктор с параметром для инициализации 
	Test(const std::string &);
	
	// действие над тестом
	void Do(const Menu::Choice &);

	// приватные методы класса
private:

	// разбитие буфера на лексемы
	void InitAll(std::string &);

	// начало теста
	void Start(void);

	// выбор элемента редактирования
	ForEdit EditChoice(void);

	// реадизация редактирования
	void Edit(const ForEdit &);

	// отображение теста
	void Show(void) const throw();

	// ответ от пользователя на вопрос теста
	size_t UserInputAnswer(const size_t &);

	// возвращаем кол-во правильных ответов
	const size_t &GetPoints();

	// добавление вопроса
	void AddQuestion(void);

	// выбор пользователем вопроса для удаления
	void DeleteQuestion(void);

	// удаление вопроса по объекту в параметрах
	void Delete(const Question &);

	// сохранение результатов в файле
	void Saving(void);

};
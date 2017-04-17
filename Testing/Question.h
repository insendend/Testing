#pragma once
#include "Test.h"

class Question
{
	std::string strTextQuestion;			// текст вопроса
	std::vector <std::string> vecAnswers;	// варианты ответов
	std::string strRightAnswer;				// правильный ответ

	// предикат для рандомного вывода вопроса
	struct Pred
	{
		Pred(void)
		{
			srand( static_cast < unsigned int > ( time(nullptr) ) );
		}
		int operator()(const int &i) const throw()
		{
			return rand() % i;
		}
	};
public:
	// конструктор с параметром (инициализация всего вопроса)
	Question(std::string &);

	// вывод вопроса на экран
	friend std::ostream & operator << (std::ostream &, const Question &);

	// вопрос
	const std::string & GetTextQustion(void) const throw();

	// правильный ответ
	const std::string & GetRightAnswer(void) const throw();
	
	// вектор всех вариантов ответов
	const std::vector<std::string> & GetVecAnswers(void) const throw();

private:

	// инициализация правильного ответа
	void InitRightAnswer(std::string &);

	// инициализация самого вопроса
	void InitTextQuestion(std::string &);

	// инициализация вектора всех вариантов ответов
	void InitAnswers(std::string &);
};
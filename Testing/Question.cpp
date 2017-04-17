#include "Question.h"

// конструктор с параметром
Question::Question(std::string &buf)
{
	// инициализация самого вопроса
	InitTextQuestion(buf);

	// инициализация правильного ответа
	InitRightAnswer(buf);

	// инициализация вектора всех вариантов ответов
	InitAnswers(buf);
}

// инициализация самого вопроса
void Question::InitTextQuestion(std::string &buf)
{
	const std::string leksem = std::string("\n");
	
	// поиск конца вопроса
	const int posEnd = buf.find(leksem);
	
	// инициализация текста вопроса
	this->strTextQuestion = buf.substr(0, posEnd);
	
	// очищаем текст вопроса
	buf.erase( 0, this->strTextQuestion.length() + 1);
}

void Question::InitRightAnswer(std::string &buf)
{
	// метка поиска правильного ответа в неотредактированном вопросе
	const std::string mark = std::string(" (верно)");

	// ищем метку
	const int posMark = buf.find(mark);

	// начало строки с ответом
	const int posStart = buf.rfind('\n', posMark) + sizeof('\n');

	// инициализация правильного ответа
	this->strRightAnswer = buf.substr(posStart, posMark - posStart);

	// убираем метку
	buf.erase( posMark, mark.length() );
}

void Question::InitAnswers(std::string &buf)
{
	const std::string leksem = std::string("\n");

	// поиск конца варианта ответа
	int posEnd = buf.find(leksem);

	while (posEnd != std::string::npos)
	{
		const std::string answer = buf.substr(0, posEnd);
		this->vecAnswers.push_back(answer);
		buf.erase( 0, answer.length() + 1);
		posEnd = buf.find(leksem);
	}
	if ( buf.size() )
		this->vecAnswers.push_back(buf);

	// перетасовка вектора вариантов ответов
	std::random_shuffle(this->vecAnswers.begin(), this->vecAnswers.end(), Question::Pred());
}

// перегрузка оператора вывода
std::ostream & operator << (std::ostream &os, const Question &q)
{
	static int iCountQuest = 1;
	int iCountAnswer = 1;
	
	// запись в поток вопроса
	os << iCountQuest++ <<". " << q.strTextQuestion << std::endl;

	// запись в поток вариантов ответа
	for (const auto &i : q.vecAnswers)
		os << "   " << iCountAnswer++ << ". " << i << std::endl;

	// возвращаем поток
	return os;
}

// строка вопроса
const std::string & Question::GetTextQustion(void) const throw()
{
	return this->strTextQuestion;
}

// строка верного ответа
const std::string & Question::GetRightAnswer(void) const throw()
{
	return this->strRightAnswer;
}

// вектор с вариантами ответов
const std::vector<std::string> & Question::GetVecAnswers(void) const throw()
{
	return this->vecAnswers;
}
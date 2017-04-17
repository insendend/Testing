#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Funcs.h"

class Menu
{
	// вектор, для хранения названий тестов
	std::vector < std::string > vTestNames;

public:
	// пункты меню
	enum Choice { PASS = 1, EDIT, SHOW, EXIT };

	// конструктор по умолчанию, инициализация массива указателей
	Menu(void);
	
	// пользовательский ввод в главном меню
	Choice MainChoice(void) const;

	// пользовательский ввод (выбор теста)
	const std::string& TestChoice(void) const;
	
	// отображение пунктов меню
	void Edit(void) const throw();

private:
	
	// вывод на экран пунктов главного меню
	void Main(void) const throw();

	// вывод на экран пунктов внутреннего меню
	void TestList(void) const throw();
	
	// склонение слова "тест" по падежам, в зависимости от кол-ва тестов	
	void OutputWord(const size_t &i) const throw();
};
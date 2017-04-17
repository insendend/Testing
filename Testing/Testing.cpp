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
			
			// ������� ����
			Menu::Choice Action = m.MainChoice();

			// �������� �� �����
			if (Action == Menu::Choice::EXIT)
				return 0;

			// ����� ������ �����
			const std::string testName = m.TestChoice();
			
			// ������� ������, ������������� ������
			Test first(testName);

			// ��������� �������������� �������� ��� ������
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
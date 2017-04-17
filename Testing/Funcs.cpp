#include "Funcs.h"

// поиск всех тестов в папке с проэктом
void Search(std::vector < std::string > &v)
{
	std::string path = std::string("*.test");	// тесты именно с таким расширением
	_finddata_t fd = { 0 };
	std::unique_ptr<Wrap> up;

	// запускаем поиск
	up.reset(new Wrap(_findfirst(&path[0], &fd)));

	// проверка
	if (!*up)
	{
		std::cout << "Не найдено ни одного теста, добавьте хотя бы один в папку с проэктом..." << std::endl;
		exit(1);
	}

	do
	{
		std::string name(std::string(fd.name));

		// если это каким-то образом директория (*.test)
		if (fd.attrib & _A_SUBDIR)
			continue;

		// если файл
		else
			// сохраняем имя теста в вектор
			v.push_back( name );

	} while (!_findnext(*up, &fd));
}

// считывание содержимое файла в буфер
void ReadFrom(const std::string &from, std::string &buf)
{
	buf.resize(4096);

	// открытие файла с тестом
	std::ifstream ifs(from);

	if (!ifs.is_open())
		throw std::exception("Can't open file with test");

	// запись содержимого в буфер
	while (!ifs.eof())
	{
		ifs.read(&buf[0], buf.size());

		size_t sizeRead = static_cast <size_t> (ifs.gcount());
		if (!sizeRead)
			throw std::exception("file is empty");

		buf.resize(sizeRead);
	}
}

// запись в файл
void WriteTo(const std::string &dest, std::string &buf)
{
	// открытие файла с тестом
	std::ofstream ofs(dest, std::ios::app);

	if (!ofs.is_open())
		throw std::exception("Can't open file with test");
	
	// запись потока в файл
	ofs << '\n';
	ofs.write(&buf[0], buf.length());
}
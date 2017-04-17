#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <memory>
#include <io.h>
#include "WrapFind.h"

// поиск всех тестов в папке с проэктом
void Search(std::vector < std::string > &);

// считывание содержимое файла в буфер
void ReadFrom(const std::string &, std::string &);

// запись в файл указанного буфера
void WriteTo(const std::string &, std::string &);
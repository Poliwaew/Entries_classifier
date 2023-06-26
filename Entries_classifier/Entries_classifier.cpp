#include <iostream>
#include "functions.h"

#include "../test_findClassesFromString/pch.h"
#include "../test_findEntriesFromString/pch.h"
#include "../test_inputTextFromFiles/pch.h"
#include "../test_isAllElemsEqual/pch.h"
#include "../test_isContainElem/pch.h"
#include "../test_makeDataFromText/pch.h"

using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    vector<string> entriesText, classesText;
    vector<entry> entries;
    vector<_class> classes;

    // Проверка на наличие названий файлов с входными данными
    if (argc < 2)
    {
        printf("Не указаны входные данные.");
        return 0;
    }

    // Счёт данных из файла, с последующей обработкой ошибок
    if (inputTextFromFiles(argv[1], argv[2], entriesText, classesText))
    {
        printf("Неверно указан файл с входными данными. Возможно, файл не существует.");
        return 0;
    }

    // Преобразование текста в данные, с последующей обработкой ошибок
    int returnIndex = makeDataFromText(entriesText, classesText, entries, classes);
    if (returnIndex == 1)
    {
        printf("Неверный порядок данных в наборе записей.");
        return 0;
    }
    if (returnIndex == 2)
    {
        printf("Неверный порядок данных в наборе классов.");
        return 0;
    }

    // Создание файла вывода
    makeOutputFile(entries, classes);
}
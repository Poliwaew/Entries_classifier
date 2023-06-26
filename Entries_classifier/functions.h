#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

enum propertyTypes {equalNames, numberOfValues, numberIsPresent, valuesMatch};

struct property
{
	string name;
	vector<int> values;
};

struct entry
{
	string name;
	vector<property> properties;
};

struct _class
{
	string name;
	property properties;
	propertyTypes type;
};

/*!
* \—читывает данные из файлов
* \param[in] entriesFileName Ц адрес файла, содержащего набор записей
* \param[in] classesFileName Ц адрес файла, содержащего набор классов
* \param[in/out] entriesText Ц текст, содержащий набор записей
* \param[in/out] classesText Ц текст, содержащий набор классов
* \return - успех выполнени€ функции
*/
int inputTextFromFiles(string entriesFileName, string classesFileName, vector<string>& entriesText, vector<string>& classesText)
{
    string line;

    // „тение из файла с набором записей
    ifstream inputData(entriesFileName);

    if (inputData.is_open())
        while (getline(inputData, line))
            entriesText.push_back(line);
    else return 1;

    inputData.close();

    // „тение из файла с набором классов
    inputData.open(classesFileName);

    if (inputData.is_open())
        while (getline(inputData, line))
            classesText.push_back(line);
    else return 1;

    inputData.close();

    return 0;
}

/*!
* \ѕреобразовывает текст с набором записей в данные
* \param[in] entriesText Ц текст, содержащий набор записей
* \param[out] entries Ц список данных записей
* \return - успех выполнени€ функции
*/
int findEntriesFromString(vector<string> entriesText, vector<entry>& entries)
{
    int index = 0;
    for (int i = 0; i < entriesText.size(); i++)
    {
        entries.resize(entries.size() + 1);
        if (entriesText[i].find(':') == string::npos)   return 1;
        //—читываем им€ записи
        for (int k = 0; entriesText[i][k] != ':'; k++)
            entries[i].name.push_back(entriesText[i][k]);
        if (entries[i].name.empty())    return 1;

        while ((index = entriesText[i].find('=', index + 1)) != string::npos)
        {
            entries[i].properties.resize(entries[i].properties.size() + 1);
            //—читываем имена свойств
            for (int k = index - 1; k > 0 && !(entriesText[i][k] == ' ' && (entriesText[i][k - 1] == ',' || entriesText[i][k - 1] == ':')); k--)
                entries[i].properties[entries[i].properties.size() - 1].name.insert(0, 1, entriesText[i][k]);
            if (entries[i].properties[entries[i].properties.size() - 1].name.empty())    return 1;

            string value = "";
            //—читываем числовые значени€ свойств
            for (int k = index + 2; entriesText[i][k - 1] != ']'; k++)
            {
                if (isdigit(entriesText[i][k]))
                    value.push_back(entriesText[i][k]);
                if (!isdigit(entriesText[i][k]) && value != "")
                {
                    entries[i].properties[entries[i].properties.size() - 1].values.resize(entries[i].properties[entries[i].properties.size() - 1].values.size() + 1);
                    entries[i].properties[entries[i].properties.size() - 1].values[entries[i].properties[entries[i].properties.size() - 1].values.size() - 1] = stoi(value);
                    value = "";
                }
            }
        }
    }
    return 0;
}

/*!
* \ѕреобразовывает текст с набором классов в данные
* \param[in] classesText Ц текст, содержащий набор классов
* \param[out] classes Ц список данных классов
* \return - успех выполнени€ функции
*/
int findClassesFromString(vector<string> classesText, vector<_class>& classes)
{
    for (int i = 0; i < classesText.size(); i++)
    {
        classes.resize(classes.size() + 1);
        if (classesText[i].find('<') == string::npos)   return 1;
        //—читываем им€ класса
        for (int k = classesText[i].find('<') + 1; classesText[i][k] != '>'; k++)
            classes[i].name.push_back(classesText[i][k]);
        if (classes[i].name.empty())    return 1;

        //—читываем им€ свойства
        for (int k = classesText[i].find('<', classesText[i].find('<') + 1) + 1; classesText[i][k] != '>'; k++)
            classes[i].properties.name.push_back(classesText[i][k]);
        if (classes[i].properties.name.empty())    return 1;

        //—читываем тип свойства
        if (classesText[i].find('<', classesText[i].find('<', classesText[i].find('<') + 1) + 1) == string::npos)   classes[i].type = equalNames;
        else if (classesText[i].find("<[") != string::npos)    classes[i].type = valuesMatch;
        else if (classesText[i].find("значением") != string::npos || classesText[i].find("значени€ми") != string::npos)    classes[i].type = numberOfValues;
        else if (classesText[i].find("есть значение <") != string::npos)    classes[i].type = numberIsPresent;
        else return 1;

        //—читываем числовое значение свойства
        if (classes[i].type == numberOfValues || classes[i].type == numberIsPresent)
        {
            classes[i].properties.values.resize(1);
            string value = "";
            for (int k = classesText[i].rfind('<') + 1; classesText[i][k] != '>'; k++)
                value.push_back(classesText[i][k]);
            classes[i].properties.values[0] = stoi(value);
        }
        if (classes[i].type == valuesMatch)
        {
            string value = "";
            for (int k = classesText[i].find('[') + 1; classesText[i][k - 1] != ']'; k++)
            {
                if (isdigit(classesText[i][k]))
                    value.push_back(classesText[i][k]);
                if (!isdigit(classesText[i][k]) && value != "")
                {
                    classes[i].properties.values.resize(classes[i].properties.values.size() + 1);
                    classes[i].properties.values[classes[i].properties.values.size() - 1] = stoi(value);
                    value = "";
                }
            }
        }
    }
    return 0;
}

/*!
* \ѕреобразовывает текст в данные
* \param[in] entriesText Ц текст, содержащий набор записей
* \param[in] classesText Ц текст, содержащий набор классов
* \param[in/out] entries Ц список данных записей
* \param[in/out] classes Ц список данных классов
* \return - успех выполнени€ функции
*/
int makeDataFromText(vector<string>& entriesText, vector<string>& classesText, vector<entry>& entries, vector<_class>& classes)
{
    if (findEntriesFromString(entriesText, entries)) return 1;

    if (findClassesFromString(classesText, classes)) return 2;

    return 0;
}

/*!
* \ѕровер€ет наличие элемента в списке
* \param[in] vect Ц список дл€ сравнени€
* \param[in] elem Ц элемент дл€ сравнени€
* \return - успех выполнени€ функции
*/
bool isContainElem(vector<int> vect, int elem)
{
    for (int i = 0; i < vect.size(); i++)
        if (elem == vect[i])
            return true;
    return false;
}

/*!
* \ѕровер€ет равенство всех элементов двух списков
* \param[in] v1 Ц первый список дл€ сравнени€
* \param[in] v2 Ц второй список дл€ сравнени€
* \return - успех выполнени€ функции
*/
bool isAllElemsEqual(vector<int> v1, vector<int> v2)
{
    if (v1.size() != v2.size()) return false;
    for (int i = 0; i < v1.size(); i++)
        if (v1[i] != v2[i])     return false;
    return true;
}

/*!
* \—оздаЄт файл вывода
* \param[in] entries Ц список данных записей
* \param[in] classes Ц список данных классов
*/
void makeOutputFile(vector<entry>& entries, vector<_class>& classes)
{
    vector<string> outputText;

    outputText.resize(classes.size());
    for (int i = 0; i < outputText.size(); i++)
    {
        outputText[i] = "<" + classes[i].name + ">: ";

        bool isAnyAdded = false;
        for (int k = 0; k < entries.size(); k++)
            for (int m = 0; m < entries[k].properties.size(); m++)
                // —равниваем свойство записи и класса
                if (entries[k].properties[m].name == classes[i].properties.name)
                {
                    bool isOk = false;
                    if (classes[i].type == equalNames)  isOk = true;
                    if (classes[i].type == numberOfValues && entries[k].properties[m].values.size() == classes[i].properties.values[0])  isOk = true;
                    if (classes[i].type == numberIsPresent && isContainElem(entries[k].properties[m].values, classes[i].properties.values[0]))  isOk = true;
                    if (classes[i].type == valuesMatch && isAllElemsEqual(entries[k].properties[m].values, classes[i].properties.values))  isOk = true;

                    if (isOk)
                    {
                        if (isAnyAdded)     outputText[i] += ", " + entries[k].name;
                        else
                        {
                            outputText[i] += entries[k].name;
                            isAnyAdded = true;
                        }
                    }
                }
        if (!isAnyAdded)    outputText[i] += "-";
    }

    // «апись в файл
    ofstream output("output.txt");

    if (output.is_open())
        for (int i = 0; i < outputText.size(); i++)
            output << outputText[i] << std::endl;

    output.close();
}
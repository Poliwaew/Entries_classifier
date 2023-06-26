#include "pch.h"
#include "CppUnitTest.h"
#include "../Entries_classifier/functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testmakeDataFromText
{
	TEST_CLASS(testmakeDataFromText)
	{
	public:
		
		TEST_METHOD(test_hasNoClassAndEntryNames)
		{
			vector<string> inputEntry, inputClass;
			int expErrorIndex = 1;
			vector<entry> realEntry;
			vector<_class> realClass;

			inputEntry.resize(1);
			inputClass.resize(1);
			inputEntry[0] = "цвет=[1, 2], размер=[10, 40, 60]\0";
			inputClass[0] = "Запись принадлежит классу <С покрытием>, если у нее есть свойство <покрытие>.\0";

			int realIndex = makeDataFromText(inputEntry, inputClass, realEntry, realClass);
			
			Assert::AreEqual(expErrorIndex, realIndex);
		}
		TEST_METHOD(test_emptyClassInput)
		{
			vector<string> inputEntry, inputClass;
			int expErrorIndex = 2;
			vector<entry> realEntry;
			vector<_class> realClass;

			inputEntry.resize(1);
			inputClass.resize(1);
			inputEntry[0] = "Шкаф: цвет=[1, 2], размер=[10, 40, 60]\0";
			inputClass[0] = "\0";

			int realIndex = makeDataFromText(inputEntry, inputClass, realEntry, realClass);

			Assert::AreEqual(expErrorIndex, realIndex);
		}
	};
}

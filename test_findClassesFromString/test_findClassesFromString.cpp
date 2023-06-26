#include "pch.h"
#include "CppUnitTest.h"
#include "../Entries_classifier/functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testfindClassesFromString
{
	TEST_CLASS(testfindClassesFromString)
	{
	public:
		
		TEST_METHOD(test_hasNoClassName)
		{
			vector<string> input;
			string expName = "покрытие";
			vector<_class> realClass;

			input.resize(1);
			input[0] = "Запись принадлежит классу, если у нее есть свойство <покрытие>.\0";

			findClassesFromString(input, realClass);

			Assert::AreEqual(expName, realClass[0].name);
		}

		TEST_METHOD(test_hasNoOptions)
		{
			vector<string> input;
			int expErrorIndex = 1;
			vector<_class> realClass;

			input.resize(1);
			input[0] = "Запись принадлежит классу, если у нее есть свойство, которое представлено значениями.\0";

			int realIndex = findClassesFromString(input, realClass);

			Assert::AreEqual(expErrorIndex, realIndex);
		}
	};
}

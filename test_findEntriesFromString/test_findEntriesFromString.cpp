#include "pch.h"
#include "CppUnitTest.h"
#include "../Entries_classifier/functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testfindEntriesFromString
{
	TEST_CLASS(testfindEntriesFromString)
	{
	public:
		
		TEST_METHOD(test_hasNoEntryNames)
		{
			vector<string> inputEntry;
			int expErrorindex = 1;
			vector<entry> realEntry;

			inputEntry.resize(1);
			inputEntry[0] = ": цвет=[1, 2], размер=[10, 40, 60]\0";

			int realIndex = findEntriesFromString(inputEntry, realEntry);

			Assert::AreEqual(expErrorindex, realIndex);
		}

		TEST_METHOD(test_hasNoPropertiesNames)
		{
			vector<string> inputEntry;
			int expErrorindex = 1;
			vector<entry> realEntry;

			inputEntry.resize(1);
			inputEntry[0] = "Стол: =[1, 4], =[20, 40], =[44]\0";

			int realIndex = findEntriesFromString(inputEntry, realEntry);

			Assert::AreEqual(expErrorindex, realIndex);
		}
	};
}

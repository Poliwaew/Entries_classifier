#include "pch.h"
#include "CppUnitTest.h"
#include "../Entries_classifier/functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testinputTextFromFiles
{
	TEST_CLASS(testinputTextFromFiles)
	{
	public:
		
		TEST_METHOD(test_wrongEntryFileName)
		{
			string inputEntryFileName = "no_such_file1.txt", inputClassFileName = "inputClasses.txt";
			int expErrorIndex = 1;
			vector<string> realEntryText, realClassText;

			int realIndex = inputTextFromFiles(inputEntryFileName, inputClassFileName, realEntryText, realClassText);

			Assert::AreEqual(expErrorIndex, realIndex);
		}
		TEST_METHOD(test_wrongClassFileName)
		{
			string inputEntryFileName = "inputEntries.txt", inputClassFileName = "no_such_file1.txt";
			int expErrorIndex = 1;
			vector<string> realEntryText, realClassText;

			int realIndex = inputTextFromFiles(inputEntryFileName, inputClassFileName, realEntryText, realClassText);

			Assert::AreEqual(expErrorIndex, realIndex);
		}
	};
}

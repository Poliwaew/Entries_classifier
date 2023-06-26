#include "pch.h"
#include "CppUnitTest.h"
#include "../Entries_classifier/functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testisContainElem
{
	TEST_CLASS(testisContainElem)
	{
	public:
		
		TEST_METHOD(test_emptyVector)
		{
			bool expValue = false;
			vector<int> inputVector;
			int inputElem = 10;

			bool realValue = isContainElem(inputVector, inputElem);

			Assert::AreEqual(expValue, realValue);
		}
		TEST_METHOD(test_emptyElem)
		{
			bool expValue = false;
			vector<int> inputVector = {1, 2, 3, 4, 5};
			int inputElem = NULL;

			bool realValue = isContainElem(inputVector, inputElem);

			Assert::AreEqual(expValue, realValue);
		}
	};
}

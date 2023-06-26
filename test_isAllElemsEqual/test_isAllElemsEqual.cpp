#include "pch.h"
#include "CppUnitTest.h"
#include "../Entries_classifier/functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testisAllElemsEqual
{
	TEST_CLASS(testisAllElemsEqual)
	{
	public:
		
		TEST_METHOD(test_emptyVectors)
		{
			bool expValue = true;
			vector<int> inputVector1, inputVector2;

			bool realValue = isAllElemsEqual(inputVector1, inputVector2);

			Assert::AreEqual(expValue, realValue);
		}
		TEST_METHOD(test_oneEmptyVector)
		{
			bool expValue = false;
			vector<int> inputVector1 = {1, 2, 3, 4, 5}, inputVector2;

			bool realValue = isAllElemsEqual(inputVector1, inputVector2);

			Assert::AreEqual(expValue, realValue);
		}
	};
}

#include "pch.h"
#include "CppUnitTest.h"
#include "../MonopolyProject/Monopoly.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Monopoly m;
			int id = static_cast<int>(m.cards[0].id);
			Assert::AreEqual(id, 0);
		}
	};
}

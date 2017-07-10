#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Archive/FileWriter.h"
#include "../Archive/FileReader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArchiveUnitTest
{		

	struct TestStruct
	{
		int n = 0;
		float f = 0.f;
		double d = 0;

		bool operator ==(const TestStruct& rhs)
		{
			return n == rhs.n 
				&& f == rhs.f
				&& d == rhs.d;
		}

		void Serialize(archive::Archive& Ar)
		{
			Ar << n;
			Ar << f;
			Ar << d;
		}
	};

	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(NumericWriteReadTest)
		{
			using namespace archive;
			const wchar_t* filePath = L"NumericWriteReadTest.sav";

			TestStruct StructForWrite;

			StructForWrite.n = 20;
			StructForWrite.f = 11.5f;
			StructForWrite.d = 567.2;

			{ // save block
				FileWriter Writer(filePath);
				StructForWrite.Serialize(Writer);
			}
			TestStruct StructForRead;
			Assert::IsFalse(StructForWrite == StructForRead);

			{ // load block
				FileReader Reader(filePath);
				StructForRead.Serialize(Reader);
			}
			Assert::IsTrue(StructForWrite == StructForRead);
		}

		TEST_METHOD(StringWriteReadTest)
		{
			using namespace archive;

			const wchar_t* filePath = L"StringWriteReadTest.sav";

			std::wstring StringForWrite = L"TestString";

			{
				FileWriter Writer(filePath);
				Writer << StringForWrite;
			}
			std::wstring StringForRead = L"";

			{
				FileReader Reader(filePath);
				Reader << StringForRead;
			}

			Assert::AreEqual(StringForWrite, StringForRead);
		}
	};
}
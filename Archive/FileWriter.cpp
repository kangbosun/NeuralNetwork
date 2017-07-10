#include "FileWriter.h"


namespace archive
{
	FileWriter::FileWriter(const wchar_t * path)
	{
		File.open(path, std::fstream::binary);
		assert(File.is_open());
	}

	void FileWriter::SerializeInternal(void* valuePtr, size_t length)
	{
		File.write((char*)valuePtr, length);
	}

	void FileWriter::Serialize(std::wstring& str)
	{
		size_t len = str.length() + 1;
		*this << len;
		SerializeInternal((void*)str.c_str(), sizeof(wchar_t) * str.length());
	}
}

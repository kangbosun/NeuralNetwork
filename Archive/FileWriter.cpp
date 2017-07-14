#include "FileWriter.h"


namespace archive
{
	FileWriter::FileWriter(const wchar_t * path)
	{
		File.open(path, std::fstream::binary);
		assert(File.is_open());
	}

	void FileWriter::Serialize(void* valuePtr, size_t length)
	{
		File.write((char*)valuePtr, length);
	}
}

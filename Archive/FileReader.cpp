
#include <assert.h>
#include <vector>
#include "FileReader.h"


namespace archive
{
	FileReader::FileReader(const wchar_t* path)
	{
		File.open(path, std::fstream::binary);
		assert(File.is_open());
	}

	bool FileReader::IsSaving()
	{
		return false;
	}

	void FileReader::SerializeInternal(void * valuePtr, size_t length)
	{
		File.read((char*)valuePtr, length);
	}
}
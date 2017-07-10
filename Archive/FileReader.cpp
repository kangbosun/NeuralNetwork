
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

	void FileReader::Serialize(std::wstring & str)
	{
		uint32_t len = 0;
		*this << len;

		std::vector<wchar_t> array(len);

		SerializeInternal(&array[0], len * sizeof(wchar_t));

		str = std::wstring(&array[0]);
	}
}
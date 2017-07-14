#include "Archive.h"

namespace archive
{
	void Archive::Serialize(std::wstring & str)
	{
		if (IsSaving())
		{
			size_t len = str.length() + 1;
			*this << len;
			Serialize((void*)str.c_str(), sizeof(wchar_t) * str.length());
		}

		else if (IsLoading())
		{
			size_t len = 0;
			*this << len;

			std::vector<wchar_t> array(len);

			Serialize(&array[0], len * sizeof(wchar_t));

			str = std::wstring(&array[0]);
		}
	}
}

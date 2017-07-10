#pragma once

#include <fstream>
#include "Archive.h"

namespace archive
{
	class FileReader : public Archive
	{
	public:
		FileReader(const wchar_t* path);

		// Inherited via Archive
		virtual bool IsSaving() override;
		virtual void SerializeInternal(void * valuePtr, size_t length) override;

	protected:
		std::ifstream File;

		// Inherited via Archive
		virtual void Serialize(std::wstring & str) override;
	};
}


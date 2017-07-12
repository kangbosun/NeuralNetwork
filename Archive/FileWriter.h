#pragma once

#include <fstream>
#include <assert.h>
#include "Archive.h"

namespace archive
{
	// save file as binary
	class FileWriter : public Archive
	{
	public:
		FileWriter(const wchar_t* path);

		// Inherited via Archive
		virtual bool IsSaving() override { return true; }
		virtual void SerializeInternal(void* valuePtr, size_t length) override;

	protected:
		std::ofstream File;
	};
}

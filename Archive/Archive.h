#pragma once

#include <vector>

namespace archive
{
	class Archive
	{
	public:
		template<typename T>
		Archive& operator<<(T& value)
		{
			SerializeInternal((void*)&value, sizeof(T));

			return *this;
		}
		
		template<>
		Archive& operator<<(std::wstring& value)
		{
			Serialize(value);
			return *this;
		}
		

	public:
		virtual bool IsSaving() = 0;
		bool IsLoading() { return !IsSaving(); }

	protected:

		virtual void SerializeInternal(void* valuePtr, size_t length) = 0;

		virtual void Serialize(std::wstring& str);
	};
}


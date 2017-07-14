#pragma once

#include <vector>
#include <type_traits>

namespace archive
{
	// SFINAE test
	template <typename T>
	struct Has_Serialize
	{
		typedef char (&Yes)[1];
		typedef char (&No)[2];

		template<typename C> static Yes check(decltype(&C::Serialize));
		template<typename> static No check(...);

		static bool const value = sizeof(check<T>(0)) == sizeof(Yes);
	};

	class Archive
	{
	public:
		template<typename T>
		Archive& operator<<(T& value)
		{
			SerializeInternal<T, Has_Serialize<T>::value>(*this, value);

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
		template <typename T, bool has_serialize> 
		struct SerializeInternal;

		template <typename T> 
		struct SerializeInternal<T, false>
		{
			SerializeInternal(Archive& ar, T& value)
			{
				ar.Serialize((void*)&value, sizeof(T));
			}
		};

		template <typename T> 
		struct SerializeInternal<T, true>
		{
			SerializeInternal(Archive& ar, T& value)
			{
				value.Serialize(ar);
			}
		};

		virtual void Serialize(void* valuePtr, size_t length) = 0;

		virtual void Serialize(std::wstring& str);
	};
}


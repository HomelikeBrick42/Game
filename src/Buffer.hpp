#pragma once

#include "./Typedefs.hpp"

template<typename T>
class Buffer {
public:
	Buffer(u64 capacity = 0)
		: Data(nullptr), Length(0), Capacity(capacity) {
		if (this->Capacity > 0) {
			this->Data = new T[this->Capacity];
		}
	}

	~Buffer() {
		if (this->Data) {
			delete[] this->Data;
		}
	}

	T& Push(const T& value) {
		if (this->Capacity == 0 || this->Length + 1 >= this->Capacity) {
			this->Capacity = this->Capacity != 0 ? this->Capacity * 2 : 1;
			T* newData = new T[this->Capacity];

			if (this->Data) {
				u8* ptr = cast(u8*) this->Data;
				u8* newPtr = cast(u8*) newData;
				for (u64 i = 0; i < this->Length * sizeof(T); i++) {
					*newPtr++ = *ptr++;
				}

				delete[] this->Data;
			}

			this->Data = newData;
		}
		
		u8* ptr = cast(u8*) &this->Data[this->Length];
		u8* valPtr = cast(u8*) &value;
		for (u64 i = 0; i < sizeof(T); i++) {
			*ptr++ = *valPtr++;
		}

		return this->Data[this->Length++];
	}

	T& operator[](u64 index) {
		#if !defined(NO_ARRAY_BOUNDS_CHECK)
			ASSERT(index < this->Length);
		#endif
		return this->Data[index];
	}

	const T& operator[](u64 index) const {
		#if !defined(NO_ARRAY_BOUNDS_CHECK)
			ASSERT(index < this->Length);
		#endif
		return this->Data[index];
	}
public:
	T* Data;
	u64 Length;
private:
	u64 Capacity;
};

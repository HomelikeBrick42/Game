#pragma once

#include "./Typedefs.hpp"

struct String {
	u8* Data;
	u64 Length;

	u8& operator[](u64 index) {
		#if !defined(NO_ARRAY_BOUNDS_CHECK)
			ASSERT(index < this->Length);
		#endif
		return this->Data[index];
	}

	const u8& operator[](u64 index) const {
		#if !defined(NO_ARRAY_BOUNDS_CHECK)
			ASSERT(index < this->Length);
		#endif
		return this->Data[index];
	}
};

#define StringFromLiteral(s) (String) { .Data = cast(u8*) s, .Length = sizeof(s) - 1 }

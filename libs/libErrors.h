#ifndef LIBERRORS_H_
#define LIBERRORS_H_
#include <iostream>

//class containing handled errors
enum class EXCEPTION_CODE {
	allocationError,
	fileOpenError,
	fileCreateError,
	nullPointerError,
	valueOutOfBoundaries,
	invalidData
};

/*
Shows why certain error occurred
@param err - type of error
*/
void ShowException(EXCEPTION_CODE err);


/*
Throw error if pointer set to null
@param ptr - ptr to check
*/
template <class T>
inline void CheckPointer(T* ptr) {
	if (ptr == nullptr)
		throw EXCEPTION_CODE::nullPointerError;
}

/*
Check if passed value is between min and max
@param value - value to check
@param min - value must be greater than this
@param max - value must be lesser than this
*/
template<class T> inline void InBoundaries(T value, T min, T max) {
	if (max < value or min > value)
		throw EXCEPTION_CODE::valueOutOfBoundaries;
};

#endif // !LIBERRORS_H_


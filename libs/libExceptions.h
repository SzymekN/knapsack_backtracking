#ifndef LIBEXCEPTIONS_H
#define LIBEXCEPTIONS_H

#include <exception>
#include <string>

namespace MyRuntimeExceptions {

	class ZeroDivisionException : public std::runtime_error {
	public:
		ZeroDivisionException() : runtime_error("Zero division ERROR") {};
		ZeroDivisionException(std::string msg) : runtime_error(msg.c_str()) {};
	};

	class NegativeNumberException : public std::runtime_error {
	public:
		NegativeNumberException() : runtime_error("Negative number ERROR") {};
		NegativeNumberException(std::string msg) : runtime_error(msg.c_str()) {};
	};

	class NullPtrException : public std::runtime_error {
	public:
		NullPtrException() : runtime_error("Null pointer ERROR") {};
		NullPtrException(std::string msg) : runtime_error(msg.c_str()) {};
	};

	class FileException : public std::runtime_error {
	public:
		FileException() : runtime_error("file ERROR") {};
		FileException(std::string msg) : runtime_error(msg.c_str()) {};
	};

	class AllocationException : public std::runtime_error {
	public:
		AllocationException() : runtime_error("Space alloaction ERROR") {};
		AllocationException(std::string msg) : runtime_error(msg.c_str()) {};
	};

	class InputDataException : public std::runtime_error {
	public:
		InputDataException() : runtime_error("Input data ERROR") {};
		InputDataException(std::string msg) : runtime_error(msg.c_str()) {};
	};

}

#endif // !LIBEXCEPTIONS_H
#pragma once

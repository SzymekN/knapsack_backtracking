#include "libErrors.h"

void ShowException(EXCEPTION_CODE err)
{
	switch (err)
	{
	case EXCEPTION_CODE::allocationError:
		std::cerr << "ERROR: Cannot create array";
		break;
	case EXCEPTION_CODE::fileOpenError:
		std::cerr << "ERROR: File opening error";
		break;
	case EXCEPTION_CODE::fileCreateError:
		std::cerr << "ERROR: File creating error";
		break;
	case EXCEPTION_CODE::nullPointerError:
		std::cerr << "ERROR: Pointer not set";
		break;
	case EXCEPTION_CODE::valueOutOfBoundaries:
		std::cerr << "ERROR: Wrong value";
		break;
	case EXCEPTION_CODE::invalidData:
		std::cerr << "ERROR: Invalid data";
		break;
	default:
		std::cerr << "ERROR: Unknown error";
		break;
	}
}


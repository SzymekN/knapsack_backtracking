#include<exception>
#include "libs/libKnapsackBacktracking.h"
#include "libs/libFiles.h"


int main()
{
	int returnCode{};
	std::ifstream readFromFile;
	int size{};
	int maxWeight{};
	Options options;

	try {
		OpenFile(readFromFile, "in.txt");
		readFromFile >> size;
		readFromFile >> maxWeight;

		if (size < 1 or maxWeight < 1)
			throw MyRuntimeExceptions::InputDataException();
		
		size++;
		options.size = size;
		options.maxWeight = maxWeight;

		Item* items = new Item[size];
		if (items == nullptr)
			throw MyRuntimeExceptions::NullPtrException();

		for (int i = 1; i < size; i++) {
			int p, w, pw;
			items[i].i = i;
			readFromFile >> p;
			readFromFile >> w;
			readFromFile >> pw;

			if (p < 0 or w < 1 or pw < 0)
				throw MyRuntimeExceptions::InputDataException();
			
			items[i].price = p;
			items[i].weight = w;
			items[i].pricePerWeight = pw;
		}

		//InitializePPW(items, size);
		//ShowItems(items, size);
		MergeSort(items, 1, size - 1);
		options.items = items;
		//ShowItems(options.items, size);
		KnapsackStart(items, options);
	}
	catch (std::exception& err) {
		returnCode = -1;
		std::cerr << err.what();
	}
	return returnCode;
}

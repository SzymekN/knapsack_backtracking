#include <locale.h>
#include "libs/libKnapsackBacktracking.h"
#include "libs/libFiles.h"


int main()
{
	setlocale(LC_ALL, "Polish");

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

		MergeSort(items, 1, size - 1);

		options.size = size;
		options.maxWeight = maxWeight;
		options.items = items;
		options.posInTree = CreateArray<int>(options.size);
		CreateFile(options.writeToFile, "results.txt");
		memset(options.posInTree, 0, sizeof(int) * options.size);
		options.posInTree[0] = -1;

		KnapsackBacktracking(options, 0, 0, 0, true);
		std::cout << "\nMax profit: " << options.maxProfit;
		options.writeToFile << "\nMax profit: " << options.maxProfit;

	}
	catch (std::exception& err) {
		returnCode = -1;
		std::cerr << err.what();
	}
	return returnCode;
}

#include <locale.h>
#include "libs/libKnapsackBacktracking.h"
#include "libs/libFiles.h"


int main()
{
	setlocale(LC_ALL, "Polish");

	int returnCode{};
	//number of items
	int size{};
	//max weight of knapsack
	int maxWeight{};
	//read from this file
	std::ifstream readFromFile;
	//important information needed in algorithm
	Options options;
	//array of items available
	Item* items{};

	try {
		OpenFile(readFromFile);
		readFromFile >> size;
		readFromFile >> maxWeight;

		if (size < 1 or maxWeight < 1)
			throw MyRuntimeExceptions::InputDataException();
		
		//size++ because first row is set to 0
		size++;

		items = CreateArray<Item>(size);
		if (items == nullptr)
			throw MyRuntimeExceptions::NullPtrException();

		//read items from file
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
		
		//sort items by price per weight
		MergeSort(items, 1, size - 1);

		options.size = size;
		options.maxWeight = maxWeight;
		options.items = items;
		options.posInTree = CreateArray<int>(options.size);
		memset(options.posInTree, 0, sizeof(int) * options.size);
		//-1 to set later root as (0,0)
		options.posInTree[0] = -1;
		CreateFile(options.writeToFile, "results.txt");

		KnapsackBacktracking(options, 0, 0, 0, true);
		std::cout << "\nMax profit: " << options.maxProfit;
		options.writeToFile << "\nMax profit: " << options.maxProfit;

		DeleteArray(items);
		readFromFile.close();
		options.writeToFile.close();
	}
	catch (std::exception& err) {
		returnCode = -1;
		std::cerr << err.what();
	}
	return returnCode;
}

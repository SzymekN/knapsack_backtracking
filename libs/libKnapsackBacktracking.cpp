#include "libKnapsackBacktracking.h"



void InitializePPW(Item* items, int size) {
    for (int i = 1; i < size; i++)
        items[i].pricePerWeight = items[i].price / items[i].weight;
}

void ShowItems(Item* items, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << std::setw(4)<<items[i].price <<std::setw(4)<< " "
            << std::setw(4)<<items[i].weight << std::setw(4)<<" "
            << std::setw(4)<<items[i].pricePerWeight <<std::setw(4)<< " "
            << "\n";
    }
}

void KnapsackStart(Item*& i, Options& opt) {
    if (i == nullptr)
        throw MyRuntimeExceptions::NullPtrException();

    CreateFile(opt.writeToFile, "results.txt");

    opt.posInTree = CreateArray<int>(opt.size);
    memset(opt.posInTree, 0, sizeof(int) * opt.size);
    //set -1 to set root to (0,0)
    opt.posInTree[0] = - 1;
    std::cout << std::setw(10) << "pos:" << std::setw(10) << "p:"
        << std::setw(10) << "w:" << std::setw(10) << "b:" << std::setw(10) << "mp:\n";
    opt.writeToFile << std::setw(10) << "pos:" << std::setw(10) << "p:"
        << std::setw(10) << "w:" << std::setw(10) << "b:" << std::setw(10) << "mp:\n";
    KnapsackBacktracking(opt, 0, 0, 0, false);
    std::cout << "\nMax profit: " << opt.maxProfit;
    opt.writeToFile << "\nMax profit: " << opt.maxProfit;
}


bool Promising(Options& opt, int i, int weight, int profit)
{
    int k{ 0 };
    int totweight{ 0 };
    int bound{ 0 };
    std::string position{};

    opt.posInTree[i]++;
    position = "( " + std::to_string(i) + ", " + std::to_string(opt.posInTree[i]) + " )";

    std::cout << std::setw(10) << position << std::setw(10) << profit;
    opt.writeToFile << std::setw(10) << position << std::setw(10) << profit;
    if (weight >= opt.maxWeight) {
        std::cout << std::setw(10) << weight << std::setw(10) << bound << std::setw(10) << opt.maxProfit << "\n";
        opt.writeToFile << std::setw(10) << weight << std::setw(10) << bound << std::setw(10) << opt.maxProfit << "\n";
        return false;
    }
    totweight = weight;
    bound = profit;
    k = i + 1;

    while (totweight < opt.maxWeight) {
        if (totweight + opt.items[k].weight > opt.maxWeight)
            break;

        if (k >= opt.size)
            break;
        totweight += opt.items[k].weight;
        bound += opt.items[k].price;
        k++;
    }

    if (k < opt.size)
        bound += (opt.maxWeight - totweight) * opt.items[k].pricePerWeight;


    std::cout << std::setw(10) << weight << std::setw(10) << bound << std::setw(10) << opt.maxProfit << "\n";
    opt.writeToFile<< std::setw(10) << weight << std::setw(10) << bound << std::setw(10) << opt.maxProfit << "\n";
    if (bound <= opt.maxProfit)
        return false;

    return true;
}
void KnapsackBacktracking(Options& opt, int i, int profit, int weight, bool include)
{
    if (include) {
        profit += opt.items[i].price;
        weight += opt.items[i].weight;
    }

    if (weight <= opt.maxWeight && profit > opt.maxProfit)
        opt.maxProfit = profit;


    if (i < opt.size and Promising(opt,i, weight, profit)) {
        KnapsackBacktracking(opt, i + 1, profit, weight, true);
        KnapsackBacktracking(opt, i + 1, profit, weight, false);
    }

}

void Merge(Item*& arr, int left, int middle, int right)
{

    //size of left part of an array
    int leftArrSize = middle - left + 1;
    //size of right size of an array 
    int RightArrSize = right - middle;

    //create temporary arrays used in sorting process 
    Item* leftArray = CreateArray<Item>(leftArrSize);
    Item* rightArray = CreateArray<Item>(RightArrSize);

    // Copy data to temporary arrays 
    for (int i = 0; i < leftArrSize; i++)
        leftArray[i] = arr[left + i];
    for (int j = 0; j < RightArrSize; j++)
        rightArray[j] = arr[middle + 1 + j];


    //default index of first array
    int firstArrayIndex = 0;
    //default index of second array
    int secondArrayIndex = 0;
    //default index of merged array
    int mergedArrayIndex = left;

    //merge smaller arrays to bigger one
    while (firstArrayIndex < leftArrSize && secondArrayIndex < RightArrSize) {
        if (leftArray[firstArrayIndex].pricePerWeight >= rightArray[secondArrayIndex].pricePerWeight) {
            arr[mergedArrayIndex] = leftArray[firstArrayIndex];
            firstArrayIndex++;
        }
        else {
            arr[mergedArrayIndex] = rightArray[secondArrayIndex];
            secondArrayIndex++;
        }
        mergedArrayIndex++;
    }

    // Copy the remaining elements of left array
    while (firstArrayIndex < leftArrSize) {
        arr[mergedArrayIndex] = leftArray[firstArrayIndex];
        firstArrayIndex++;
        mergedArrayIndex++;
    }

    // Copy the remaining elements of right array
    while (secondArrayIndex < RightArrSize) {
        arr[mergedArrayIndex] = rightArray[secondArrayIndex];
        secondArrayIndex++;
        mergedArrayIndex++;
    }
}

void MergeSort(Item*& arr, int left, int right)
{

    if (right <= left)
        return;

    int middle = (left + right) / 2;

    //partition left side of an array into smaller and smaller chunks, until size of 1 
    MergeSort(arr, left, middle);
    //partition right side of an array 
    MergeSort(arr, middle + 1, right);
    //merge chunks of array and sort
    Merge(arr, left, middle, right);
}

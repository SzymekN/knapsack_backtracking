#include "libKnapsackBacktracking.h"

int maxProfit{};
int maxWeight{};
int size{};
int* posInTree{};
Item* items = nullptr;


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

void KnapsackStart(Item*& i, int& s, int& maxW) {
    if (i == nullptr)
        throw MyRuntimeExceptions::NullPtrException();

    if (s < 1 or maxW < 1)
        throw MyRuntimeExceptions::InputDataException();

    items = i;
    size = s;
    maxWeight = maxW;
    posInTree = CreateArray<int>(size);
    memset(posInTree, 0, sizeof(int) * size);
    //set -1 to set root to (0,0)
    posInTree[0] = - 1;
    std::cout << std::setw(10) << "pos:" << std::setw(10) << "p:"
        << std::setw(10) << "w:" << std::setw(10) << "b:" << std::setw(10) << "mp:\n";
    KnapsackBacktracking(0, 0, 0, false);
    std::cout << maxProfit;
}


bool Promising(int i, int weight, int profit)
{
    int k{ 0 };
    int totweight{ 0 };
    int bound{ 0 };
    std::string position{};

    posInTree[i]++;
    position = "( " + std::to_string(i) + ", " + std::to_string(posInTree[i]) + " )";

    std::cout << std::setw(10) << position << std::setw(10) << profit;
    if (weight >= maxWeight) {
        std::cout << std::setw(10) << weight << std::setw(10) << bound << std::setw(10) << maxProfit << "\n";
        return false;
    }
    totweight = weight;
    bound = profit;
    k = i + 1;

    while (totweight < maxWeight) {
        if (totweight + items[k].weight > maxWeight)
            break;

        if (k >= size - 1)
            break;
        totweight += items[k].weight;
        bound += items[k].price;
        k++;
    }

    if (k < size)
        bound += (maxWeight - totweight) * items[k].pricePerWeight;


    std::cout << std::setw(10) << weight << std::setw(10) << bound << std::setw(10) << maxProfit << "\n";
    if (bound <= maxProfit)
        return false;

    return true;
}
void KnapsackBacktracking(int i, int profit, int weight, bool include)
{
    if (include) {
        profit += items[i].price;
        weight += items[i].weight;
    }

    if (weight <= maxWeight && profit > maxProfit)
        maxProfit = profit;


    if (i < size and Promising(i, weight, profit)) {
        KnapsackBacktracking(i + 1, profit, weight, true);
        KnapsackBacktracking(i + 1, profit, weight, false);
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

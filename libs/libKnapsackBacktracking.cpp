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
void KnapsackBacktracking(Options& opt, int i, int profit, int weight, bool include)
{
    std::string position{};

    opt.posInTree[i]++;
    //prepare information about node position
    position = "( " + std::to_string(i) + ", " + std::to_string(opt.posInTree[i]) + " )";
    std::cout << "\nPrzechodzê do wierzcho³ka " << position << "\n";
    opt.writeToFile << "\nPrzechodzê do wierzcho³ka " << position << "\n";

    //if item shoud be included
    if (include) {
        profit += opt.items[i].price;
        weight += opt.items[i].weight;
        std::cout << "Obliczam nowy zysk. Profit = " << profit << "\n";
        std::cout << "Obliczam now¹ wagê. Weight = " << weight << "\n";
        opt.writeToFile << "Obliczam nowy zysk. Profit = " << profit << "\n";
        opt.writeToFile << "Obliczam now¹ wagê. Weight = " << weight << "\n";
    }

    if (weight <= opt.maxWeight && profit > opt.maxProfit) {
        opt.maxProfit = profit;
        std::cout << "Przedmiot mieœci siê w plecaku oraz zysk jest wiêkszy. Max profit = " << opt.maxProfit << "\n";
        opt.writeToFile << "Przedmiot mieœci siê w plecaku oraz zysk jest wiêkszy. Max profit = " << opt.maxProfit << "\n";
    }


    if (i < opt.size and Promising(opt, i, weight, profit)) {
        //left node
        KnapsackBacktracking(opt, i + 1, profit, weight, true);
        //right node
        KnapsackBacktracking(opt, i + 1, profit, weight, false);
    }

}

bool Promising(Options& opt, int i, int weight, int profit)
{
    int k{ 0 };
    int totweight{ 0 };
    int bound{ 0 };


    //std::cout << std::setw(10) << position << std::setw(10) << profit;
    //opt.writeToFile << std::setw(10) << position << std::setw(10) << profit;
    if (weight >= opt.maxWeight) {
        //std::cout << std::setw(10) << weight << std::setw(10) << bound << std::setw(10) << opt.maxProfit << "\n";
        //opt.writeToFile << std::setw(10) << weight << std::setw(10) << bound << std::setw(10) << opt.maxProfit << "\n";
        std::cout << "Do³o¿enie przedmiotu przekracza wagê maksymaln¹ - Wêze³ nieobiecuj¹cy\n";
        opt.writeToFile << "Do³o¿enie przedmiotu przekracza wagê maksymaln¹ - Wêze³ nieobiecuj¹cy\n";
        return false;
    }
    totweight = weight;
    bound = profit;
    k = i + 1;

    //sum total weight and bound, set k
    while (totweight < opt.maxWeight) {
        if (totweight + opt.items[k].weight > opt.maxWeight)
            break;

        if (k >= opt.size)
            break;
        totweight += opt.items[k].weight;
        bound += opt.items[k].price;
        k++;
    }

    //if weight exceeded and not all items packed add to bound
    if (k < opt.size)
        bound += (opt.maxWeight - totweight) * opt.items[k].pricePerWeight;
    std::cout << "Wyznaczam K. K = " << k << "\n";
    std::cout << "Wyznaczam granicê. Bound = " << bound << "\n";
    opt.writeToFile << "Wyznaczam K. K = " << k << "\n";
    opt.writeToFile << "Wyznaczam granicê. Bound = " << bound << "\n";

    //std::cout << std::setw(10) << weight << std::setw(10) << bound << std::setw(10) << opt.maxProfit << "\n";
    //opt.writeToFile<< std::setw(10) << weight << std::setw(10) << bound << std::setw(10) << opt.maxProfit << "\n";
    if (bound <= opt.maxProfit) {
        std::cout << "Granica mniejsza b¹dŸ równa maksymalnemu zyskowi - Wêzê³ nieobiecuj¹cy\n";
        opt.writeToFile << "Granica mniejsza b¹dŸ równa maksymalnemu zyskowi - Wêzê³ nieobiecuj¹cy\n";
        return false;
    }

    return true;
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

#ifndef LIBKNAPSACKBACKTRACKING_H
#define LIBKNAPSACKBACKTRACKING_H

#include <iostream>
#include <iomanip>
#include <string>
#include "libArrays.h"
#include "libFiles.h"

struct Item
{
    int i{};
    int price{};
    int weight{};
    int pricePerWeight{};
};

struct Options {
    int maxProfit{};
    int maxWeight{};
    int size{};
    int* posInTree{};
    Item* items = nullptr;
    std::ofstream writeToFile;
};

void KnapsackBacktracking(Options &opt, int i, int profit, int weight, bool include);

bool Promising(Options &opt, int i, int weight, int profit);

void Merge(Item*& arr, int left, int middle, int right);

void MergeSort(Item*& arr, int left, int right);

void InitializePPW(Item* items, int size);

void ShowItems(Item* items, int size);

void KnapsackStart(Item*& i, Options &opt);

#endif // !LIBKNAPSACKBACKTRACKING_H

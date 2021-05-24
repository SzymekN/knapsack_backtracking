#ifndef LIBKNAPSACKBACKTRACKING_H
#define LIBKNAPSACKBACKTRACKING_H

#include <iostream>
#include <iomanip>
#include <string>
#include "libArrays.h"

struct Item
{
    int i{};
    int price{};
    int weight{};
    int pricePerWeight{};
};

void KnapsackBacktracking(int i, int profit, int weight, bool include);

bool Promising(int i, int weight, int profit);

void Merge(Item*& arr, int left, int middle, int right);

void MergeSort(Item*& arr, int left, int right);

void InitializePPW(Item* items, int size);

void ShowItems(Item* items, int size);

void KnapsackStart(Item*& i, int& s, int& maxW);

#endif // !LIBKNAPSACKBACKTRACKING_H

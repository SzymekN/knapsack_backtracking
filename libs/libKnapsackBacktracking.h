#ifndef LIBKNAPSACKBACKTRACKING_H
#define LIBKNAPSACKBACKTRACKING_H

#include <iostream>
#include <iomanip>
#include <string>
#include "libArrays.h"
#include "libFiles.h"


//struct holding information about items
struct Item
{
    int i{};
    int price{};
    int weight{};
    int pricePerWeight{};
};

//Structure holds variables that don't change in every node
struct Options {
    int maxProfit{};
    int maxWeight{};
    int size{};
    int* posInTree{};
    Item* items = nullptr;
    std::ofstream writeToFile;
};
/*
Implementation of backtracking knapsack algorithm
@param opt Options structure holding important info
@param i index of current item
@param profit profit in current node
@param weight weigh in current node
@param include true if current item should be included
*/
void KnapsackBacktracking(Options &opt, int i, int profit, int weight, bool include);

/*
Check if node is promising
@param opt Options structure holding important info
@param i index of current item
@param profit profit in current node
@param weight weigh in current node
@return true if node promising
*/
bool Promising(Options &opt, int i, int weight, int profit);

/*
Merge sort algorithm for sorting Item objects
@param arr array to sort
@param left left boundry of sorting
@param rigth right boundry of sorting
*/
void Merge(Item*& arr, int left, int middle, int right);

/*
Merge sorted chunks of array for Item objects
@param arr array to sort
@param left left boundry of first merged chunk
@param middle right boundry of first chunk and left of second chunk
@param right right boundry of second merged chunk
*/
void MergeSort(Item*& arr, int left, int right);

/*
Set price per weight for items
@items array of Item objects
@param size size of an array
*/
void InitializePPW(Item* items, int size);

/*
Show available items 
@param items array of items
@param size size of an array
*/
void ShowItems(Item* items, int size);

#endif // !LIBKNAPSACKBACKTRACKING_H

#include <iostream>

int maxProfit = 0;
int maxWeight = 16;
int size = 5;
int* prices = new int[size];
int* weights = new int[size];

bool Promising(int i, int weight, int profit)
{
    int k{0};
    int totweight{0};
    int bound{0};
    std::cout << "i: " << i << ", p: " << profit;
    if (weight >= maxWeight) {
        std::cout << ", w: " << weight << ", b: " << bound << ", mp: " << maxProfit << "\n";
        return false;
    }
    totweight = weight;
    bound = profit;
    k = i + 1;

    while (totweight < maxWeight) {
        if (totweight + weights[k] > maxWeight){
            break;
        }
        if (k >= size)
            break;
        totweight += weights[k];
        bound += prices[k];
        k++;
    }

    if(k<size)
        bound += (maxWeight - totweight) * prices[k] / weights[k];


    std::cout << ", w: " << weight << ", b: " << bound<<", mp: "<<maxProfit<<"\n";
    if (bound <= maxProfit)
        return false;

    return true;
}
void KnapsackBacktracking(int i, int profit, int weight, bool include)
{
    if (include) {
        profit += prices[i];
        weight += weights[i];
    }
    if (weight <= maxWeight && profit > maxProfit) {    
        maxProfit = profit;                 
    }                                        

    if (i < size and Promising(i, weight, profit)) {
        KnapsackBacktracking(i + 1, profit, weight, true);
        KnapsackBacktracking(i + 1, profit, weight, false);
    }
}


int main()
{
    prices[0] = 0;
    prices[1] = 40;
    prices[2] = 30;
    prices[3] = 50;
    prices[4] = 10;

    weights[0] = 0;
    weights[1] = 2;
    weights[2] = 5;
    weights[3] = 10;
    weights[4] = 5;

    KnapsackBacktracking(0, 0, 0, false);

    std::cout << maxProfit;
    delete weights;
    delete prices;
    return 0;
}

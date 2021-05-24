#include "libArrays.h"

int DeleteDuplicates(long long* arr, int size)
{
	int temp = 1;
	for (int i = 1; i < size; i++) {
		if (arr[temp - 1] != arr[i]) {
			arr[temp] = arr[i];
			temp++;
		}
	}
	return temp;
}

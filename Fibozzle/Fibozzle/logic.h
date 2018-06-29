#include <stdio.h>
#include <stdlib.h>

int *fiblookup;
int fibn;
int searchFib(int l, int r, int key)
{
	int m = (l + r - 1) / 2;
	if (l <= r)
	{
		if (fiblookup[m] == key)
		{
			return m;
		}
		if (fiblookup[m] > key)
		{
			return searchFib(l, m - 1, key);
		}
		else
		{
			return searchFib(m + 1, r, key);
		}
	}
	return -1;
}

int getFibN(int size)
{
	fibn = (2 * (size *  size));
	return fibn;
}

int *generateFibo(int n)
{
	int first = 1, second = 2, next = 0;
	int *fibarr = (int *)calloc(n-2, sizeof(int));
	fibarr[0] = first;
	fibarr[1] = second;
	for (int i = 2; i < n - 1; i++)
	{
		next = first + second;
		fibarr[i] = next;
		first = second;
		second = next;
		printf("%d ",fibarr[i]);
	}
	return fibarr;
}

void createFibLookup(int size)
{
	int n = getFibN(size);
	fiblookup = generateFibo(n);
}

bool canBeMerged(int a, int b)
{
	if (a == -1 || b == -1)
	{
		return false;
	}
	if (a == 0 && b == 0)
	{
		return true;
	}
	if (a > b)
	{
		int c = a - b;
		return (c == 1) ? true : false;
	}
	else
	{
		int c = b - a;
		return (c == 1) ? true : false;
	}
}

//top - left = 0
//bottom - right = 1
int *mergeTiles(int *arr, int size, int dir)
{
	int i,j;
	int *merged = (int *)calloc(size, sizeof(int));
	i = (dir == 0) ? 0 : size - 1;
	if (dir == 0)
	{
		while (i < size-1)
		{
			//didnt handle the situations like merging 1001-1010 - only handled 1100 0011 etc
			int key1 = searchFib(0, fibn, arr[i]);
			int key2 = searchFib(0, fibn, arr[i + 1]);
			bool canMerge = canBeMerged(key1, key2);
			if (canMerge && (!merged[i]) && (!merged[i+1]))
			{
				arr[i] += arr[i + 1];
				arr[i + 1] = 0;
				merged[i] = merged[i + 1] = true;
				i += 2;
			}
			else
			{
				i++;
			}
		}
		i = 0;
		while (i<size)
		{
			if (arr[i] == 0)
			{
				j = i;
				while (j < size)
				{
					if (arr[j] == 0)
					{
						j++;
						continue;
					}
					else
					{
						arr[i] = arr[j];
						arr[j] = 0;
						break;
					}
				}
			}
			i++;
		}
	}
	else
	{
		while (i > 0)
		{
			int key1 = searchFib(0, fibn, arr[i]);
			int key2 = searchFib(0, fibn, arr[i - 1]);
			bool canMerge = canBeMerged(key1, key2);
			if (canMerge && (!merged[i]) && (!merged[i - 1]))
			{
				arr[i] += arr[i - 1];
				arr[i - 1] = 0;
				merged[i] = merged[i - 1] = true;
				i -= 2;
			}
			else
			{
				i--;
			}
		}
		i = size - 1;
		while (i >= 0)
		{
			if (arr[i] == 0)
			{
				j = i;
				while (j >= 0)
				{
					if (arr[j] == 0)
					{
						j--;
						continue;
					}
					else
					{
						arr[i] = arr[j];
						arr[j] = 0;
						break;
					}
				}
			}
			i--;
		}
	}
	return arr;
}

void performOperation(int **board, int size, int dir)
{
	int *check = (int *)calloc(size, sizeof(int));
	int i, j;
	if (dir == 1 || dir == 3)
	{
		i = 0;
		while (i < size)
		{
			j = 0;
			while (j < size)
			{
				check[j] = board[j][i];
				j++;
			}
			check = (dir == 1) ? mergeTiles(check, size, 0) : mergeTiles(check, size, 1);
			j = 0;
			while (j < size)
			{
				board[j][i] = check[j];
				j++;
			}
			i++;
		}
	}/*
	if (dir == 3)
	{
		i = 0;
		while (i < size)
		{
			j = 0;
			while (j < size)
			{
				check[j] = board[j][i];
				j++;
			}
			mergeTiles(check, size, 1);
			i++;
		}
	}*/
	if (dir == 2 || dir == 4)
	{
		i = 0;
		while (i < size)
		{
			j = 0;
			while (j < size)
			{
				check[j] = board[i][j];
				j++;
			}
			check  = (dir == 2) ? mergeTiles(check, size, 1) : mergeTiles(check, size, 0);
			j = 0;
			while (j < size)
			{
				board[i][j] = check[j];
				j++;
			}
			i++;
		}
	}/*
	if (dir == 4)
	{
		i = 0;
		while (i < size)
		{
			j = 0;
			while (j < size)
			{
				check[j] = board[i][j];
				j++;
			}
			mergeTiles(check, size, 0);
			i++;
		}
	}*/
}
#include<iostream>
using namespace std;

//Method that provides the required crossover sequence.
auto crossArray(int i, int n, int* arr)
{
	struct result { int* crossArray; int* indexes; int* size; };
	int k = abs(n - (i + 2));
	int* size = &k;
	int* crossArray = new int[k];
	int* indexes = new int[k];

	for (int j = 0; j < k; j++)
	{
		crossArray[j] = arr[j + i + 2];
		indexes[j] = j + i + 2;
	}

	return result{ crossArray,indexes,size };
}

int main()
{
	int arr[] = { -5, 13, 88,-65, 27, -150, 138 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int biggestSubSize = 0, subSize = 2;
	int blockCtHolder = 0, blockCt = 0, currentBlockCt = 0;
	int index = 0, wIndex = 0, rIndex = 0;
	int** subsets = new int* [1000];
	int* indexes = new int[1000];
	int* totals = new int[1000];
	int total = 0, finalIndex = 0;
	int* crossArr, * indexesOfCrossArr, * size;
	int sizeOfCrossArr, FLAG = 1;
	int* lengthOfsubsets = new int[1000];

	//The for loop to be executed for each element of the array.
	for (int i = 0; i < n - 2; i++)
	{
		if ((n - i) % 2 == 0)
		{
			biggestSubSize = (n - i) / 2;
		}
		else
		{
			biggestSubSize = ((n - i) / 2) + 1;
		}

		index = i;
		blockCtHolder = 1;
		subSize = 2;

		do //Our loop that will continue until subsets of each array elements are created.
		{
			auto result = crossArray(index, n, arr);
			crossArr = result.crossArray;
			indexesOfCrossArr = result.indexes;
			size = result.size;
			sizeOfCrossArr = *size;

			for (int j = 0; j < sizeOfCrossArr; j++)//The for loop with the size of the crossover sequence.
			{
				total = 0;
				subsets[wIndex] = new int[subSize];
				for (int k = 0; k < subSize - 1; k++)
				{
					if (FLAG == 1)
					{
						subsets[wIndex][k] = arr[i];
					}
					else if (FLAG == 0)
					{
						subsets[wIndex][k] = subsets[rIndex - 1][k];
					}
				}

				for (int k = subSize - 1; k < subSize; k++)//In this loop, the crossover parts of the subset to be derived are written.
				{
					subsets[wIndex][k] = crossArr[j];
					if (indexesOfCrossArr[j] < (n - 2))blockCt++;
					if (indexesOfCrossArr[j] == (n - 1))currentBlockCt++;
				}

				indexes[wIndex] = indexesOfCrossArr[j];
				lengthOfsubsets[wIndex] = subSize;

				for (int x = 0; x < subSize; x++)//Calculating the sum of the subset.
				{
					total += subsets[wIndex][x];
				}

				totals[wIndex] = total;
				wIndex++;
			}

			if (currentBlockCt == blockCtHolder)//If the number of blocks available is equal to the variable that holds how many blocks should be.
			{								    //A block refers to the subsets created along a crossover sequence.
				subSize++;
				blockCtHolder = blockCt;
				blockCt = 0;
				currentBlockCt = 0;
			}

			index = indexes[rIndex];

			/*If our index value coincides with the last two indices, 
			it means that subsets with those indices should be skipped. 
			For this, the read index is increased and the index value is created again. 
			Until the subset with the appropriate index value is passed.*/
			while (index == (n - 2) || index == (n - 1))
			{
				rIndex++; index = indexes[rIndex];
			}
			rIndex++;
			FLAG = 0;
		} while (subSize <= biggestSubSize);//The loop should continue until it reaches the largest sized subset of the current array element.

		rIndex--;
		FLAG = 1;
	}

	int max = totals[0];
	for (int i = 0; i < wIndex; i++)//In this loop, the comparison is made until the max total value is found.
	{
		if (totals[i] > max)
		{
			max = totals[i];
			finalIndex = i;
		}
	}

	//Display of results.
	cout << "The subset with the max sum: {";
	for (int i = 0; i < lengthOfsubsets[finalIndex]; i++)
	{
		cout << subsets[finalIndex][i] << " ";
	}
	cout << "}" << "  Max sum: " << max << endl;
	cout << "Subsets: " << endl;

	for (int i = 0; i < wIndex; i++)
	{
		cout << "{";
		for (int j = 0; j < lengthOfsubsets[i]; j++)
			cout << subsets[i][j] << " ";
		cout << "}" << "\tSum: " << totals[i] << endl;
	}
}
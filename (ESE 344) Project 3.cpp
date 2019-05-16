// Jonathan Cruzate
// jcruzate
// 110130802
// ESE 344
// Project 3

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

int quickCount = 0, heapCount = 0, hashCompCount = 0, hashCollCount = 0, quickCountArr[30], heapCountArr[30], hashCompCountArr[10], hashCollCountArr[10];

const int hash_size = 1021;

struct Node
{
	int data;
	Node* prev;
	Node* next;

	Node(const int& d = int{ }, Node* p = nullptr, Node* n = nullptr) : data{ d }, prev{ p }, next{ n } { }

	Node(int&& d, Node* p = nullptr, Node* n = nullptr) : data{ std::move(d) }, prev{ p }, next{ n } { }
};

class HashTable {
public:
	void insert(int value);
	void print();
private:
	Node* front = 0;
};

void HashTable::print() {
	Node* temp = front;
	cout << endl;
	while (temp != 0 && temp->next != NULL) {
		cout << temp->data << "  ";
		temp = temp->next;
	}
}

void HashTable::insert(int value) {
	if (front == 0)
	{
		front = new Node(value);
	}
	else
	{
		hashCollCount++;
	}

	hashCompCount++;
	if (front->data > value) {
		Node* n = new Node(value);
		n->next = front;
		front = n;
	}
	else
	{
		Node* temp = front;

		hashCompCount++;
		while (temp->next != 0 && temp->next->data < value)
		{
			temp = temp->next;
			hashCompCount++;
		}

		Node* n = new Node(value);
		n->next = temp->next;
		temp->next = n;
	}
}

int hash_func(int key)
{
	int value = 0;
	for (int position = 0; position < 8; position++)
	{
		value = 4 * value + key;
	}
	return value % hash_size;
}

void insert_heap(int entry[], int current, int low, int high)
{
	int large;

	large = 2 * low + 1;

	while (large <= high)
	{
		++heapCount;
		if (large < high && entry[large] < entry[large + 1])
		{
			large++;
		}

		++heapCount;
		if (current >= entry[large])
		{
			break;
		}
		else
		{
			entry[low] = entry[large];
			low = large;
			large = 2 * low + 1;
		}
	}
	entry[low] = current;
}

void build_heap(int entry[], int count, int current)
{
	int low;

	for (low = count / 2 - 1; low >= 0; low--)
	{
		current = entry[low];
		insert_heap(entry, current, low, count - 1);
	}
}

void heap_sort(int entry[], int count)
{
	int current = 0, last_unsorted;

	build_heap(entry, count, current);

	for (last_unsorted = count - 1; last_unsorted > 0; last_unsorted--)
	{
		current = entry[last_unsorted];
		entry[last_unsorted] = entry[0];
		insert_heap(entry, current, 0, last_unsorted - 1);
	}
}

void swap(int entry[], int low, int high)
{
	int temp;
	temp = entry[low];
	entry[low] = entry[high];
	entry[high] = temp;
}

int partition(int entry[], int low, int high)
{
	int i, pivot, last_small;
	swap(entry, low, (low + high) / 2);
	pivot = entry[low];
	last_small = low;

	for (i = low + 1; i <= high; i++)
	{
		++quickCount;
		if (entry[i] < pivot)
		{
			last_small = last_small + 1;
			swap(entry, last_small, i);
		}
	}

	swap(entry, low, last_small);

	return last_small;
}

void quick_sort(int entry[], int low, int high)
{
	int pivot_position;

	++quickCount;
	if (low < high)
	{
		pivot_position = partition(entry, low, high);
		quick_sort(entry, low, pivot_position - 1);
		quick_sort(entry, pivot_position + 1, high);
	}
}

void main()
{
	int inputSel, numEnt = 5000, nextDat, quickCountArrVar = 0, heapCountArrVar = 0, len = 0, qsum = 0, hsum = 0, hashCollCountSum = 0, hashCompCountSum = 0, qmean = 0, hmean = 0, hashCollCountMean = 0, hashCompCountMean = 0, qsd = 0, hsd = 0, index, i, j, quickSortArr[5000], heapSortArr[5000];

	cout << "Enter 0 for simulation input, and 1 for external input.\n";
	cin >> inputSel;
	if (inputSel != 1)
	{
		inputSel = 0;
	}

	for (i = 0; i < 30; i++)
	{
		srand((unsigned int)time(NULL));

		quickCount = 0;
		heapCount = 0;

		for (j = 0; j < numEnt; j++)
		{
			if (inputSel == 1)
			{
				cout << " Enter next data : \n";
				cin >> nextDat;
			}
			else
			{
				nextDat = (int)(rand() % 1000001);
			}
			quickSortArr[j] = nextDat;
			heapSortArr[j] = nextDat;
		}

		len = sizeof(quickSortArr) / sizeof(int);
		quick_sort(quickSortArr, 0, len - 1);

		cout << endl;

		cout << "Quick Sort" << endl;
		for (j = 0; j < numEnt; j++)
		{
			cout << "  (" << j << "," << quickSortArr[j] << ") ";
		}
		quickCountArr[i] = quickCount;
		cout << endl;
		cout << "Number of Comparison Operations: " << quickCount << endl;
		cout << endl;

		len = sizeof(heapSortArr) / sizeof(int);
		heap_sort(heapSortArr, len);

		cout << endl;

		cout << "Heap Sort" << endl;
		for (j = 0; j < numEnt; j++)
		{
			cout << "  (" << j << "," << heapSortArr[j] << ") ";
		}
		heapCountArr[i] = heapCount;
		cout << endl;
		cout << "Number of Comparison Operations: " << heapCount << endl;
		cout << endl;
	}

	len = sizeof(quickCountArr) / sizeof(int);
	quick_sort(quickCountArr, 0, len - 1);

	len = sizeof(heapCountArr) / sizeof(int);
	quick_sort(heapCountArr, 0, len - 1);

	for (int i = 0; i < 30; ++i)
	{
		qsum += quickCountArr[i];
		hsum += heapCountArr[i];
	}

	qmean = qsum / 30;
	hmean = hsum / 30;

	for (int i = 0; i < 30; ++i)
	{
		quickCountArrVar += pow(quickCountArr[i] - qmean, 2);
		heapCountArrVar += pow(heapCountArr[i] - hmean, 2);
	}

	// 1a

	for (int i = 0; i < 30; ++i)
	{
		cout << quickCountArr[i] << " ";
	}

	cout << endl;

	cout << "Minimum of Quick Sort Comparison Operations: " << quickCountArr[0] << endl;
	cout << "Maxium of Quick Sort Comparison Operations: " << quickCountArr[29] << endl;
	cout << "Mean of Quick Sort Comparison Operations: " << qmean << endl;
	cout << "Median of Quick Sort Comparison Operations: " << (quickCountArr[15] + quickCountArr[16]) / 2 << endl;
	cout << "Standard Deviation of Quick Sort Comparison Operations: " << sqrt(quickCountArrVar / 30) << endl;

	cout << endl;

	// 1b

	for (int i = 0; i < 30; ++i)
	{
		cout << heapCountArr[i] << " ";
	}

	cout << endl;

	cout << "Minimum of Heap Sort Comparison Operations: " << heapCountArr[0] << endl;
	cout << "Maxium of Heap Sort Comparison Operations: " << heapCountArr[29] << endl;
	cout << "Mean of Heap Sort Comparison Operations: " << hmean << endl;
	cout << "Median of Heap Sort Comparison Operations: " << (heapCountArr[15] + heapCountArr[16]) / 2 << endl;
	cout << "Standard Deviation of Heap Sort Comparison Operations: " << sqrt(heapCountArrVar / 30) << endl;

	cout << endl;

	// 2

	for (i = 0; i < 10; i++)
	{
		srand((unsigned int)time(NULL));

		hashCompCount = 0;
		hashCollCount = 0;

		HashTable table[hash_size];

		for (j = 0; j < numEnt; j++)
		{
			if (inputSel == 1)
			{
				cout << " Enter next data : \n";
				cin >> nextDat;
			}
			else
			{
				nextDat = (int)(rand() % 1000001);
			}
			index = hash_func(nextDat);
			table[index].insert(nextDat);
		}

		for (j = 0; j < hash_size; j++)
		{
			table[j].print();
		}
		cout << endl;
		cout << "Number of Collisions: " << hashCollCount << endl;
		cout << "Number of Comparisons: " << hashCompCount << endl;
		cout << endl;

		hashCompCountArr[i] = hashCompCount;
		hashCollCountArr[i] = hashCollCount;
		cout << endl;
	}

	for (int i = 0; i < 10; ++i)
	{
		hashCollCountSum += hashCollCountArr[i];
		hashCompCountSum += hashCompCountArr[i];
	}

	hashCollCountMean = hashCollCountSum / 10;
	hashCompCountMean = hashCompCountSum / 10;

	for (int i = 0; i < 10; ++i)
	{
		cout << hashCollCountArr[i] << " ";
	}

	cout << endl;

	cout << "Mean of Collisions: " << hashCollCountMean << endl;

	for (int i = 0; i < 10; ++i)
	{
		cout << hashCompCountArr[i] << " ";
	}

	cout << endl;

	cout << "Mean of Comparisons: " << hashCompCountMean << endl;

	cout << endl;
}
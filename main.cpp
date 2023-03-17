#include <iostream>
#include <chrono>
#include <fstream>
using namespace std::chrono;
using namespace std;
void fisier(int dim)
{
    ofstream fout("C:\\Users\\Ciprian\\Documents\\GitHub\\SD-lab1\\nr2.txt");

    srand(time(0));
    for (int i=0; i<dim; i++)
        fout<<rand()%1000<<" ";

    fout.close();
}

/// Radix Sort
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSort(int arr[], int n, int exp)
{
    int *output=new int[n];
    int i, count[10] = { 0 };
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
    delete[] output;
}

void radixsort(int arr[], int n)
{
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

///Insertion Sort
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

///Merge Sort
void merge(int array[], int const left, int const mid,
           int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    auto *leftArray = new int[subArrayOne],
            *rightArray = new int[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne
            = 0,
            indexOfSubArrayTwo
            = 0;
    int indexOfMergedArray
            = left;

    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray]
                    = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray]
                    = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

///Shell Sort
int shellSort(int arr[], int n)
{
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
    return 0;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i
            = (low
               - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int main() {

    int dim=1e0;
    int *arr = new int[dim];

    fisier(dim);

    ///Radix
    ifstream fin("C:\\Users\\Ciprian\\Documents\\GitHub\\SD-lab1\\nr2.txt");
    for(int i=0; i<dim; i++)
        fin>>arr[i];
    fin.close();

    auto start = high_resolution_clock::now();
    radixsort(arr, dim);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"\n"<<"radix :"<<duration.count()/1000.0;

    ///Merge
    fin.open("C:\\Users\\Ciprian\\Documents\\GitHub\\SD-lab1\\nr2.txt");
    for(int i=0; i<dim; i++)
        fin>>arr[i];
    fin.close();

    start = high_resolution_clock::now();
    mergeSort(arr, 0, dim-1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"\n"<<"Merge :"<<duration.count()/1000.0;

    ///Shell
    fin.open("C:\\Users\\Ciprian\\Documents\\GitHub\\SD-lab1\\nr2.txt");
    for(int i=0; i<dim; i++)
        fin>>arr[i];
    fin.close();

    start = high_resolution_clock::now();
    shellSort(arr, dim);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"\n"<<"Shell :"<<duration.count()/1000.0;

    ///Quick
    if(dim < 1e8)
    {
        fin.open("C:\\Users\\Ciprian\\Documents\\GitHub\\SD-lab1\\nr2.txt");
        for(int i=0; i<dim; i++)
            fin>>arr[i];
        fin.close();

        start = high_resolution_clock::now();
        quickSort(arr, 0, dim-1);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout<<"\n"<<"Quick :"<<duration.count()/1000.0;
    }
    else
        cout<<"\n"<<"Quick : -";


    ///Ins
    fin.open("C:\\Users\\Ciprian\\Documents\\GitHub\\SD-lab1\\nr2.txt");
    for(int i=0; i<dim; i++)
        fin>>arr[i];
    fin.close();

    start = high_resolution_clock::now();
    insertionSort(arr, dim);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<"\n"<<"Ins :"<<duration.count()/1000.0;
    delete[] arr;
    return 0;
}

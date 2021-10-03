/***
 * ���������:
 * 1. ����������� �������� ��������� ���������� (���� ��: ���������� �������, ���������, ���������)
 * 2. ����������� �������� ������� ���������� (���������� ����� ��� ���������� ��������)
 * 3. ����������� ��������� ������ �������� � ��������������� ������� (����������� ��������, �������� �����) - ���� �������
* ������� � �������:
 * 1. ���������� ����������� ������� ������ ��������� ���������� (���������� �������) �� ����� ��������� �������
 * 2. ���������� ����������� ������� ������ ������� ���������� (���������� �����/���������� ��������)  �� ����� ��������� �������
 * 3. ���������� ���������� ��������� ������� ��� ������� ��������� ���������� �������� ������� �������.
 * 4. ���������� ����������� ������� ������ ������������ ������ �� ���������� ��������� ������� � ���������� �������� ������
 * 5. ���������� ����������� ������� ������ ��������� ������ �� ���������� ��������� ������� � ���������� �������� ������
 * 6. ���������� ������ ������� ���������� � ��������������, �������� ������������ ������� ������ ��������������� ���������.
 * 7. ���������� ��������� �������� ��������� N, ��� ������� ��� ��� ���� �������� ���������� ��������
 * 8. ���������� ������������ �������� ��������� MAX_N (� ��������� �� �������� �����) ��� ������� ��������� ����� ��������
*/

#include <iostream>
#include "extension.hpp"

unsigned long long const MAX_N = 100000; //������������ ���������� ��������� � �������

//******************************����� �������� � �������**********************************
unsigned long search_index(long* A, unsigned long begin, unsigned long end, long elem) {
    for (unsigned long i = begin; i < end; ++i) {
        if (A[i] == elem) {
            return i;
        }
    }
    return end;
}
//�������� ����� ������� ������� ��������� ����� ��������� �������� � ������� � ���������� ��� ������

//***************************************************************************************

//***********************���������� �������********************************************
void SelectionSort(long* arr, int size_of_array) {
    int smallest;
    for (int i = 0; i < size_of_array; ++i) {
        smallest = i;
        for (int j = i + 1; j < size_of_array; ++j) {
            if (arr[j] < arr[smallest]) {
                smallest = j;
            }
        }
        if (i != smallest) std::swap(arr[i], arr[smallest]);
    }
}

//�������� ����� ������� ������� ��������� ���������� ������� ����������� �� �������

//***************************************************************************************

//**********************************����������� ��������*********************************
void Merge(long* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    
    long* L = new long[n1];
    long* R = new long[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    
    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }


    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
}

void MergeSort(long* arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    MergeSort(arr, l, m);
    MergeSort(arr, m + 1, r);
    Merge(arr, l, m, r);
}



//�������� ����� ������� ������� ��������� ���������� ������� �������� (���� �� ��� ��� ���������)

//***************************************************************************************

//**********************************���������� �����*************************************

//�������� ����� ������� ������� ��������� ���������� ����� ��� ����������� �� ������� (���� �� ��� ��� ���������)

//***************************************************************************************

void search_test_function(long* A, unsigned long N, unsigned long requests_counts) {
    Utils util;
    long* requests = new long[requests_counts];
    util.generate_data(requests, requests, requests_counts);

    Timer t; t.start();
    unsigned long misses = 0;
    for (auto i = 0ul; i < requests_counts; ++i) {
        unsigned long index = 0;
        index = search_index(A, 0, N, requests[i]);
        //index =  .... ; ���������� ����� ����� ������� ������ �������� requests[i] � ������� A �����
        if (index >= N) {
            ++misses;
        }
        if (index < N && A[index] != requests[i]) {
            std::cout << "Fail to search " << requests[i] << ". A[index] == " << A[index] << std::endl;
            return;
        }
    }
    t.stop();

    std::cout << "Processed " << requests_counts << " requests for array size " << N << ". Missed " << misses
        << " requests. Elapsed time: "
        << t.elapsed() << " microseconds." << std::endl;

    delete[] requests;
}

int main() {
    Utils util;

    long* slow_data = new long[MAX_N];
    long* rapid_data = new long[MAX_N];

    unsigned long const N = 100000; //����������� ��������. ����� ����� �������� ��� ��������� ����������� ������� �� N. N <= MAX_N

    //��������� N ������������ ����� �� ������� [-1000, 1000] � ������� slow_data � rapid_data. slow_data[i] == rapid_data[i]
    util.generate_data(slow_data, rapid_data, N);

    //*****************************������������ ��������� ����������******************************************************
    {
        Timer t;
        t.start();

        //���������� ����� ������� ��������� ���������� ��� ������� slow_data �����
        SelectionSort(slow_data, N);
            t.stop();

        if (!util.check_order(slow_data, N)) {
            std::cout << "Sort order is wrong. Check the sort function." << std::endl;
        }
        else {
            std::cout << "Performed slow sort of " << N << " elements. Elapsed time: " << t.elapsed() << " microseconds.\n";
        }
        std::cout << "First min(" << N << ", 10) elements:\n";
        for (auto i = 0; i < std::min(N, 10ul); ++i)
            std::cout << slow_data[i] << " ";
        std::cout << std::endl;
    }
    //********************************************************************************************************************

    //*****************************������������ ������� ����������********************************************************
    {
        Timer t;
        t.start();
        MergeSort(rapid_data, 0, N);
        //���������� ����� ������� ������� ���������� ��� ������� rapid_data �����

        t.stop();

        if (!util.check_order(rapid_data, N)) {
            std::cout << "Sort order is wrong. Check the sort function." << std::endl;
        }
        else {
            std::cout << "Performed rapid sort of " << N << " elements. Elapsed time: " << t.elapsed() << " microseconds.\n";
        }

        std::cout << "First min(" << N << ", 10) elements:\n";
        for (auto i = 0; i < std::min(N, 10ul); ++i)
            std::cout << rapid_data[i] << " ";
        std::cout << std::endl;
    }
    //********************************************************************************************************************

    //*****************************������������ ������ �������� � �������*************************************************
    unsigned long request_count = 100; //���������� �������� ������. ����� ����������� � �������������� (� �������� �������) ��������
    search_test_function(slow_data, N, request_count);
    //********************************************************************************************************************

    return 0;
}



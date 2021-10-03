/***
 * Требуется:
 * 1. Реализовать алгоритм медленной сортировки (один из: сортировка выбором, вставками, пузырьком)
 * 2. Реализовать алгоритм быстрой сортировки (сортировка Хоара или сортировка слиянием)
 * 3. Реализовать алгоритмы поиска элемента в отсортированном массиве (тривиальный алгоритм, бинарный поиск) - пока оставим
* Вопросы к заданию:
 * 1. Определить зависимость времени работы медленной сортировки (сортировки выбором) от числа элементов массива
 * 2. Определить зависимость времени работы быстрой сортировки (сортировка Хоара/сортировка слиянием)  от числа элементов массива
 * 3. Определить количество элементов массива при котором медленная сортировка работает быстрее быстрой.
 * 4. Определить зависимость времени работы тривиального поиска от количества элементов массива и количества запросов поиска
 * 5. Определить зависимость времени работы бинарного поиска от количества элементов массива и количества запросов поиска
 * 6. Обменяться кодами быстрой сортировки с одногрупниками, провести исследование времени работы альтернативного алгоритма.
 * 7. Определить диапазоны значений параметра N, для которых тот или иной алгоритм сортировки применим
 * 8. Определите максимальное значение параметра MAX_N (с точностью до десятков тысяч) при котором программа может работать
*/

#include <iostream>
#include "extension.hpp"

unsigned long long const MAX_N = 100000; //Максимальное количество элементов в массиве

//******************************Поиск элемента в массиве**********************************
unsigned long search_index(long* A, unsigned long begin, unsigned long end, long elem) {
    for (unsigned long i = begin; i < end; ++i) {
        if (A[i] == elem) {
            return i;
        }
    }
    return end;
}
//Напишите здесь функцию которая выполняет поиск заданного элемента в массиве и возвращает его индекс

//***************************************************************************************

//***********************Сортировка выбором********************************************
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

//Напишите здесь функцию которая выполняет сортировку выбором переданного ей массива

//***************************************************************************************

//**********************************Сортировака слиянием*********************************
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



//Напишите здесь функцию которая выполняет сортировку массива слиянием (если от вас это требуется)

//***************************************************************************************

//**********************************Сортировка Хоара*************************************

//Напишите здесь функцию которая выполняет сортировку Хоара для переданного ей массива (если от вас это требуется)

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
        //index =  .... ; Разместите вызов вашей функции поиска элемента requests[i] в массиве A здесь
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

    unsigned long const N = 100000; //Варьируемый параметр. Можно смело изменять для получения зависимости времени от N. N <= MAX_N

    //Генерация N произвольных числе из отрезка [-1000, 1000] в массивы slow_data и rapid_data. slow_data[i] == rapid_data[i]
    util.generate_data(slow_data, rapid_data, N);

    //*****************************Тестирование медленной сортировки******************************************************
    {
        Timer t;
        t.start();

        //Разместите вызов функции медленной сортировки для массива slow_data здесь
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

    //*****************************Тестирование быстрой сортировки********************************************************
    {
        Timer t;
        t.start();
        MergeSort(rapid_data, 0, N);
        //Разместите вызов функции быстрой сортировки для массива rapid_data здесь

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

    //*****************************Тестирование поиска элемента в массиве*************************************************
    unsigned long request_count = 100; //Количество запросов поиска. Можно варьировать в неограниченных (в разумной степени) пределах
    search_test_function(slow_data, N, request_count);
    //********************************************************************************************************************

    return 0;
}



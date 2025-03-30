#ifndef SORT_H
#define SORT_H

#include "../include/graph.h"

void TrocaVerticeCor(VerticeCor* a, VerticeCor* b);

int Partition(VerticeCor* array, int low, int high);
void QSort(VerticeCor* array, int low, int high);
VerticeCor* QuickSort(Grafo* g);

void Merge(VerticeCor* array, int left, int middle, int right);
void MSort(VerticeCor* array, int left, int right);
VerticeCor* MergeSort(Grafo* g);

void heapify(VerticeCor* array, int n, int i);
void HSort(VerticeCor* array, int n);
VerticeCor* HeapSort(Grafo* g);

VerticeCor* BubbleSort(Grafo* g);
VerticeCor* InsertionSort(Grafo* g);
VerticeCor* SelectionSort(Grafo* g);

VerticeCor* BubbleSort_variation(Grafo* g);

#endif
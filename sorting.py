"""Inlämningsuppgift A, Oliver Bölin, dv1620"""
"""
Källor
1. s.  151, Introductions to algorithms
2. s.  171, Introductions to algorithms
3. s.  171, Introductions to algorithms
4. s.  154, Introductions to algorithms
5. s.  157, Introductions to algorithms
6. s.  160, Introductions to algorithms
"""
import sys
import time

def partision(lst, low, high):
    """Partision för båda quicksort funktionerna"""
    pivot = lst[high] #It is high because we switched it earlier
    pivot_index = low - 1

    for checker in range(low, high): ##Do not need -1 because of pythons range
        if lst[checker] <= pivot:
            pivot_index += 1
            lst[pivot_index], lst[checker] = lst[checker], lst[pivot_index]

    lst[pivot_index+1], lst[high] = lst[high], lst[pivot_index+1]
    return pivot_index+1

def quicksort(lst, low, high):
    """Quicksort hjälpare för pivot först"""
    if low < high:
        lst[low], lst[high] = lst[high], lst[low] ##allowed?
        pivot_index = partision(lst, low, high)
        quicksort(lst, low, pivot_index-1)
        quicksort(lst, pivot_index+1, high)

def quicksort_median(lst, low, high):
    """Quicksort hjälpare för median pivot"""
    if low < high:
        ##Quicksort of median list
        ##Manual sort of median list
        middle = round((low + high)/2)
        print(lst[low],lst[middle],lst[high])
        if ((lst[middle] > lst[low]) and (lst[middle] < lst[high]) or (lst[middle] < lst[low]) and (lst[middle] > lst[high])): #Middle is more than low, but less than high therefor median
            lst[middle], lst[high] = lst[high], lst[middle]
        elif (lst[low] > lst[middle] and lst[low] < lst[high]) or (lst[low] < lst[middle]) and (lst[low] > lst[high]): #Low is more than middle but less than high therefor median
            lst[high], lst[low] = lst[low], lst[high]
        ##If none of those are true high is median and a switch is not necessary.

       
        pivot_index = partision(lst, low, high)
        quicksort_median(lst, low, pivot_index-1)
        quicksort_median(lst, pivot_index+1, high)

def quicksort_pivot_first(lst):
    """Pivot först, enligt uppgift"""
    quicksort(lst, 0, len(lst) - 1)

def quicksort_pivot_median(lst):
    """Pivot median, enligt uppgift"""
    quicksort_median(lst, 0, len(lst)-1)

def heapify(lst, i, heap_size, d):
    """Heapify, (Max-heapify) för heapsort"""
    largest = i
    for count in range(1,d+1):
        child = d*i + count
        if child < heap_size and lst[child] > lst[largest]:
            largest = child
    if largest != i:
        lst[i], lst[largest] = lst[largest], lst[i]
        heapify(lst, largest, heap_size, d)

def build_max_heap(lst, d, heap_size):
    """Bygger en max-heap"""
    temp_d = d
    if d > len(lst):
        if len(lst) != 0:
            temp_d = len(lst)
    for p in range(round(len(lst)/temp_d)-1, -1, -1): #Down to zero
        heapify(lst, p, heap_size, d)

def heapsort(lst,d:int = 2):
    """Huvudfunktion för heapsort"""
    heap_size = len(lst)
    build_max_heap(lst, d, heap_size)

    for i in range(len(lst)-1, 0, -1):
        lst[0], lst[i] = lst[i], lst[0]
        heap_size -= 1
        heapify(lst, 0, heap_size, d)

def main():
    """//main\\"""

    sys.setrecursionlimit(1000000)
    lst=[int(line.strip()) for line in open('Testdata/random_50000.txt')]
    before = time.perf_counter()
    
    
    quicksort_pivot_median(lst)
    #heapsort(lst, 5)

    after = time.perf_counter()
    print(f"Time: {after - before}")
    #print(lst, " Sorted")
if __name__ == "__main__":
    main()

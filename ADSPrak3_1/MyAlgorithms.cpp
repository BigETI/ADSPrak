#include "MyAlgorithms.h"

#include <thread>

using namespace std;

namespace MyAlgorithms {

	void swift_through(vector<int> & a, int i)
	{
		int li = ((i * 2) + 1), ri(li + 1);
		if (a.size() > i)
		{
			if (a.size() > ri)
			{
				// 2 Nachfolger
				if (a[li] > a[ri])
				{
					if (a[i] < a[li])
						a[i] ^= a[li] ^= a[i] ^= a[li];
				}
				else
				{
					if (a[i] < a[ri])
						a[i] ^= a[ri] ^= a[i] ^= a[ri];
				}
			}
			else if (a.size() > li)
			{
				// 1 Nachfolger
				if (a[i] < a[li])
					a[i] ^= a[li] ^= a[i] ^= a[li];
			}
		}
	}

	//Heapsort
	void max_heapify(vector<int> &a, int i, int n) {
		/*******************************************/
		// implement heapsort helper function here //
		/*******************************************/
		for (int x(n - 1); x >= i; x--)
			swift_through(a, x);

	}
	void HeapSort(vector<int> &a, int n) {
		/***************************/
		// implement heapsort here //
		/***************************/

	}

	//MergeSort
	void Merge(vector<int> &a, int low, int pivot, int high) {
		/********************************************/
		// implement mergesort helper function here //
		/********************************************/
		int n1((pivot - low) + 1), n2(high - pivot);
		vector<int> l(n1 + 1), r(n2 + 1);
		for (int i(0); i < n1; i++)
			l[i] = a[low + 1];
		for (int i(0); i < n2; i++)
			r[i] = a[pivot + 1 + i];
		int i(0), j(0), k(low);
		while ((i < n1) && (j < n2))
		{
			if (l[i] <= r[j])
				a[k] = l[i++];
			else
				a[k] = r[j++];
			++k;
		}
		while (i < n1)
			a[k++] = l[i++];
		while (j < n2)
			a[k++] = r[j++];
	}

	void MergeSort(vector<int> &a, int low, int high) {
		/****************************/
		// implement mergesort here //
		/****************************/
		int pivot;
		if (low < high)
		{
			pivot = (low + high) / 2;
			MergeSort(a, low, pivot);
			MergeSort(a, pivot + 1, high);
			Merge(a, low, pivot, high);
		}
	}

	//Quicksort
	/*int QuickSort_div(vector<int> & arr, int left, int right)
	{
		int i(left), j(right - 1), p(arr[right]);
		do
		{
			while ((arr[i] <= p) & (i < right))
				++i;
			while ((arr[i] >= p) & (j > left))
				--j;
		} while (i < j);
		if (i < j)
			arr[i] ^= arr[j] ^= arr[i] ^= arr[j];
		return i;
	}*/

	void QuickSort(vector<int> &arr, int left, int right) {
		/****************************/
		// implement quicksort here //
		/****************************/
		int i = left, j = right;
		int tmp;
		int pivot = arr[(left + right) / 2];
		while (i <= j)
		{
			while (arr[i] < pivot)
				i++;
			while (arr[j] > pivot)
				j--;
			if (i <= j) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				i++;
				j--;
			}
		}
		if (left < j)
			QuickSort(arr, left, j);
		if (i < right)
			QuickSort(arr, i, right);
	}

	// Insertion sort
	void InsertionSort(std::vector<int> &a, int b, int e)
	{
		int i, j, nv, sz((e - b) + 1);
		for (i = (b + 1); i < sz; i++) {
			nv = a[i];
			j = i;
			while ((j > 0) && (a[j - 1] > nv)) {
				a[j] = a[j - 1];
				j--;
			}
			a[j] = nv;
		}
	}

	// To-Do
	void ShellSort(std::vector<int> &a, int parts)
	{
		/*vector<thread *> ts;
		thread *t;
		int b, e, sz, r;
		if ((a.size() / parts) < 2)
			parts = a.size() / 2;
		sz = a.size() / parts;
		r = a.size() % parts;
		for (int i = 0; i < parts; i++)
		{
			b = i * sz;
			e = ((i + 1) * sz) - 1;
			t = new thread(InsertionSort, a, b, e);
			ts.push_back(t);
		}
		if (r > 0)
		{
			b = parts * sz;
			e = a.size() - 1;
			t = new thread(InsertionSort, a, b, e);
			ts.push_back(t);
			InsertionSort(a, b, e);
		}
		for (vector<thread *>::iterator it(ts.begin()), end(ts.end()); it != end; ++it)
		{
			t = (*it);
			t->join();
			delete t;
		}
		ts.clear();*/

		int n(a.size());
		for (int gap(n / 2); gap > 0; gap /= 2)
		{
			for (int i(gap); i < n; i++)
			{
				int x(a[i]), j(i);
				for (; (j >= gap) && (x < a[j - gap]); j -= gap)
					a[j] = a[j - gap];
				a[j] = x;
			}
		}
	}

	void MatrixMul_ColMajor(vector<double> &A, vector<double> &B, vector<double> &C,
		int n) {
		//lda, ldb, ldc are leading dimensions of matrices A,B and C
		int lda = n;
		int ldb = n;
		int ldc = n;
		double s = 0.0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				s = 0.0;
				for (int k = 0; k < n; k++) {
					s = s + A[i + k*lda] * B[k + j*ldb];
				}
				C[i + j*ldc] = s;
			}
		}
	}

	void MatrixMul_RowMajor(vector<double> &A, vector<double> &B, vector<double> &C,
		int n) {
		//lda, ldb, ldc are leading dimensions of matrices A,B and C
		int lda = n;
		int ldb = n;
		int ldc = n;
		double s = 0.0;
		/***************************************/
		// implement row major calculation here//
		/***************************************/
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				s = 0.0;
				for (int k = 0; k < n; k++) {
					s = s + A[(i * lda) + k] * B[(j * ldb) + k];
				}
				C[i + j*ldc] = s;
			}
		}
	}

} // end namespace


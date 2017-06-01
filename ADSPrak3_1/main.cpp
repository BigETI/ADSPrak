#include <iostream>
#include <fstream> 
#include <iomanip> 
#include <vector>
#include <omp.h>
#include "MyAlgorithms.h"

using namespace std;

int main(int argc, char** argv) {
  ofstream file;
  file.open("example.txt");
  double dtime;
  int n_start = 1000;
  int n_step = 1000;
  int n_end = 1000000;
  
  for (int n = n_start; n<n_end; n+=n_step) {    
    cout << "n: " << n << endl;
    /**********************/
    // init data here //
    /**********************/
	vector<int> data;
	for (int i(0); i < 10; i++)
		data.push_back(rand() % 100);
    dtime = omp_get_wtime();
	cout << "List: ";
	for (int i(0); i < data.size(); i++)
	{
		if (i > 0)
			cout << ", ";
		cout << data[i];
	}
    /**********************/
    // run algorithm here //
    /**********************/
	MyAlgorithms::ShellSort(data, 4);
    dtime = omp_get_wtime() - dtime;
    file << n << "\t" << scientific << setprecision(10) << dtime << endl;
	cout << "Sorted List: ";
	for (int i(0); i < data.size(); i++)
	{
		if (i > 0)
			cout << ", ";
		cout << data[i];
	}
  }
  file.close();
}

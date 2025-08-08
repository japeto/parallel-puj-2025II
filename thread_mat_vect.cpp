#include <iostream>
#include <vector>
#include <pthread.h>

using namespace std;

// structure
struct tdata{
	vector<vector<int>>* a_mat;
	vector<int>* a_vector;
	vector<int>* result;
	int start;
	int end;
};

void * multiplyRow( void * args){
	tdata* data = (tdata*) args;
	for (int i= data->start; i< data->end; ++i){
	 (*data->result)[i] = 0;
 		for(int j=0;j < data->a_vector->size();++j){
			(*data->result)[i] += (*data->a_mat)[i][j] * (*data->a_vector)[j];
		}	 
	}
	pthread_exit(NULL);
}

int main (int argc, char* argv[]){
	// TODO: Allows you to change inputs
	// matrix 4x3
	vector<vector <int>> mat ={
		{2,7,3},
		{4,7,3},
		{5,9,3},
		{9,9,9}
	};
	// vector
	vector <int> vec = {2,9,2};
	
	const int n_threads =5;
	pthread_t threads[n_threads];
	tdata thr_data[n_threads];

	// TODO: validate dimension
	// dimension
	int rows = mat.size();
	int cols = vec.size();
	
	int rows_per_thread= rows/n_threads;
	int extra_rows = rows % n_threads;
	int current_row=0;
	
	vector <int> result(rows, 0);

	// Create and execute threads
	for(int i=0;i< n_threads;++i){
		thr_data[i].a_mat= &mat;
		thr_data[i].a_vector= &vec;
		thr_data[i].result = &result;
		thr_data[i].start=current_row;

		// filas x hilo
		thr_data[i].end = current_row + rows_per_thread + (i < extra_rows ? 1 : 0);
		current_row = thr_data[i].end;

		pthread_create(&threads[i], NULL, multiplyRow, (void*) &thr_data[i]);
	}

	// wait for threads
	for (int j=0;j<n_threads;++j){
		pthread_join(threads[j], NULL);
	}
	
	for(int j=0;j<cols;++j ){
		std::cout << result[j] << " " << std::endl;
	}
	return 0;
}
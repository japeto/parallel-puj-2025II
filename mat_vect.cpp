#include <iostream>
#include <vector>

using namespace std;

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
	
	// TODO: validate dimension
	// dimension
	int rows = mat.size();
	int cols = vec.size();
	vector <int> result(rows, 0);
	// multitplication
	for (int i =0;i< rows;++i){
		for(int j=0;j <cols; ++j){
			result[i] += mat[i][j] * vec[j];
		}
	}
	for(int j=0;j<cols;++j ){
		std::cout << result[j] << " " << std::endl;
	}
	return 0;
}
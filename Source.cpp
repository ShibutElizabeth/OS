#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

int n, m, p, numberOfThreads;

vector<vector<int>> matrixA;
vector<vector<int>> matrixB;
vector<thread> threads1;
vector<thread> threads2;
vector<thread> threads3;

void printResult(vector<vector<int>>& matrix) {
	cout << "Matrix C: " << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < p; ++j) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}

}

void algotithm1(vector<vector<int>> &result1, int count) {
	int firstRow = n / numberOfThreads * count;
	int lastRow = n / numberOfThreads * (count + 1);
	if ((n - 1) < lastRow) {
		lastRow = n - 1;
	}
	for (int i = firstRow; i <= lastRow; ++i) {
		for (int j = 0; j < p; ++j) {
			for (int h = 0; h < m; ++h)
				result1[i][j] += matrixA[i][h] * matrixB[h][j];
		}
	}
}

void algorithm2(vector<vector<int>>& result2, int count) {
	int firstCol = m / numberOfThreads * count;
	int lastCol = m / numberOfThreads * (count + 1);
	if (m - 1 < lastCol) {
		lastCol = m - 1;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < p; ++j) {
			for (int k = firstCol; k <= lastCol; ++k)
				result2[i][j] += matrixA[i][k] * matrixB[k][j];
		}
	}
}

void algorithm3(vector<vector<int>>& result3,int count) {
	int first1 = n / numberOfThreads * count;
	int last1 = n / numberOfThreads * (count + 1);
	int first2 = m / numberOfThreads * count;
	int last2 = m / numberOfThreads * (count + 1);
	if ((n - 1) < last1) {
		last1 = n - 1;
	}
	if ((m - 1) < last2) {
		last2 = m - 1;
	}
	for (int i = first1; i <= last1; ++i) {
		for (int j = 0; j < p; ++j) {
			for (int h = first2; h <= last2; ++h)
				result3[i][j] += matrixA[i][h] * matrixB[h][j];
		}
	}
}

int main() {
	ifstream fin("input.txt");
	double duration;
	fin >> numberOfThreads >> n >> m >> p;
	matrixA.resize(n, vector<int>(m, 0));
	matrixB.resize(m, vector<int>(p, 0));
	vector<vector<int>> matrixC(n, vector<int>(p, 0));
	vector<vector<int>> result1(n, vector<int>(p, 0));
	vector<vector<int>> result2(n, vector<int>(p, 0));
	vector<vector<int>> result3(n, vector<int>(p, 0));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			fin >> matrixA[i][j];
		}
	}
	cout << "Matrix A: " << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout << matrixA[i][j] << "\t";
		}
		cout << endl;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < p; j++) {
			fin >> matrixB[i][j];
		}
	}
	cout << endl;
	cout << "Matrix B: " << endl;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < p; ++j) {
			cout << matrixB[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	fin.close();

	
	cout << "Simple multiplication:\n";
	unsigned int timeBegin = clock();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < p; ++j) {
			for (int k = 0; k < m; ++k)
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
		}
	}
	duration = (clock() - (double)timeBegin) / (double)CLOCKS_PER_SEC;
	printResult(matrixC);
	cout << "Time:" << duration << endl;
	cout << endl;

	cout << "The first algorithm: " << endl;
	unsigned int timeBegin1 = clock();
	for (int i = 0; i < numberOfThreads; ++i) {
		threads1.push_back(thread(algotithm1, ref(result1), i));
	}
	for (auto& t : threads1) {
		t.join();
	}
	duration = (clock() - (double)timeBegin1) / (double)CLOCKS_PER_SEC;
	cout << "Time:" << duration << endl;
	cout << endl;

	cout << "The second algorithm: " << endl;
	unsigned int timeBegin2 = clock();
	for (int i = 0; i < numberOfThreads; ++i) {
		threads2.push_back(thread(algorithm2, ref(result2), i));
	}
	for (auto& t : threads2) {
		t.join();
	}
	duration = (clock() - (double)timeBegin2) / (double)CLOCKS_PER_SEC;
	cout << "Time:" << duration << endl;
	cout << endl;
	
	cout << "The third algorithm: " << endl;
	unsigned int timeBegin3 = clock();
	for (int i = 0; i < numberOfThreads; ++i) {
		threads3.push_back(thread(algorithm3, ref(result3), i));
	}
	for (auto& t : threads3) {
		t.join();
	}
	duration = (clock() - (double)timeBegin3) / (double)CLOCKS_PER_SEC;
	cout << "Time:" << duration << endl;

	cout << endl;
	
	return 0;
}
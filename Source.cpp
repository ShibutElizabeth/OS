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


int first1, first2, last1, last2;

void printResult(vector<vector<int>>& matrix) {
	cout << "Matrix C: " << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < p; ++j) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}

}

void algotithm1(vector<vector<int>> &result1, int i, int j) {
	first1 = (n / numberOfThreads) <= 1 ? 1:(n/numberOfThreads);
	last1 = (p / numberOfThreads) <= 1? 1: (p/ numberOfThreads);
	int n1, n2, p1, p2;
	if (i >= numberOfThreads - 1 || i >= n - 1) {
		n1 = i * first1;
		n2 = n;
	}
	else {
		n1 = i * first1;
		n2 = (i + 1) * first1;
	}
	if (j >= numberOfThreads - 1 || j >= p - 1) {
		p1 = j * last1;
		p2 = p;
	}
	else {
		p1 = j * last1;
		p2 = (j + 1) * last1;
	}
	for (int i = n1; i < n2; ++i) {
		for (int j = p1; j < p2; ++j) {
			for (int h = 0; h < m; ++h)
				result1[i][j] += matrixA[i][h] * matrixB[h][j];
		}
	}
}

void algorithm2(vector<vector<int>>& result2, int count) {
	first1 = (m / numberOfThreads) <= 1 ? 1: (m/numberOfThreads);
	int m1, m2;
	if (count >= numberOfThreads - 1 || count >= m - 1) {
		m1 = count * first1;
		m2 = m;
	}
	else {
		m1 = count * first1;
		m2 = (count + 1) * first1;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < p; ++j) {
			for (int k = m1; k < m2; ++k)
				result2[i][j] += matrixA[i][k] * matrixB[k][j];
		}
	}
}

void algorithm3(vector<vector<int>>& result3,int i, int h, int j) {
	int n1, n2, m1, m2, p1, p2;
	first1 = (n / numberOfThreads) <= 1 ? 1 : (n / numberOfThreads);
	last1 = (m / numberOfThreads) <= 1 ? 1 : (m / numberOfThreads);
	last2 = (p / numberOfThreads) <= 1 ? 1 : (p / numberOfThreads);

	if (i >= numberOfThreads - 1 || i >= n - 1) {
		n1 = i * first1;
		n2 = n;
	}
	else {
		n1 = i * first1;
		n2 = (i + 1) * first1;
	}
	if (h >= numberOfThreads - 1 || h >= m - 1) {
		m1 = h * last1;
		m2 = m;
	}
	else {
		m1 = h * last1;
		m2 = (h + 1) * last1;
	}
	if (j >= numberOfThreads - 1 || j >= p - 1) {
		p1 = j * last2;
		p2 = p;
	}
	else {
		p1 = j * last2;
		p2 = (j + 1) * last2;
	}
	for (int i = n1; i < n2; ++i) {
		for (int j = p1; j < p2; ++j) {
			for (int d = m1; d <m2; ++d)
				result3[i][j] += matrixA[i][d] * matrixB[d][j];
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
	cout << "Time:" << duration << endl;
	printResult(matrixC);
	cout << endl;

	cout << "The first algorithm: " << endl;
	unsigned int timeBegin1 = clock();
	for (int i = 0; i < numberOfThreads; ++i) {
		for (int j = 0; j < numberOfThreads; ++j) {
			threads1.push_back(thread(algotithm1, ref(result1), i, j));
		}
	}
	for (auto& t : threads1) {
		t.join();
	}
	duration = (clock() - (double)timeBegin1) / (double)CLOCKS_PER_SEC;
	cout << "Time:" << duration << endl;
	printResult(result1);
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
	printResult(result2);
	cout << endl;
	
	
	cout << "The third algorithm: " << endl;

	unsigned int timeBegin3 = clock();
	for (int i = 0; i < numberOfThreads; ++i) {
		for (int h = 0; h < numberOfThreads; ++h) {
			for (int j = 0; j < numberOfThreads; ++j) {
				threads3.push_back(thread(algorithm3, ref(result3), i, h, j));
			}
		}
	}
	for (auto& t : threads3) {
		t.join();
	}
	duration = (clock() - (double)timeBegin3) / (double)CLOCKS_PER_SEC;
	cout << "Time:" << duration << endl;
	printResult(result3);
	cout << endl;
	
	return 0;
}

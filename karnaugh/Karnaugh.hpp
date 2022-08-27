#pragma once
#include <vector>
#include <iostream>

using namespace std;

struct Value
{
	int value = -1;
	int row = -1, col = -1;
	int a, b, c, d;

	Value(int a = -1, int b = -1, int c = -1, int d = -1) {
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	}

	void setIndex(int i, int j) {
		row = i;
		col = j;
	}
};

class Karnaugh
{
private:
	int maxRows;
	int maxCols;

	vector<vector<int>> colsOctFound, rowsOctFound;
	vector<int> colsQuarFound, rowsQuarFound;


public:
	vector<vector<Value>> matriz;

	Karnaugh(int nroVariables) {
		switch (nroVariables)
		{
		case 2:
			matriz.push_back({ Value(0, 0), Value(0, 1) });
			matriz.push_back({ Value(1, 0), Value(1, 1) });
			break;
		case 3:
			matriz.push_back({ Value(0, 0, 0), Value(0, 0, 1), Value(0, 1, 1), Value(0, 1, 0) });
			matriz.push_back({ Value(1, 0, 0), Value(1, 0, 1), Value(1, 1, 1), Value(1, 1, 0) });
			break;
		case 4:
			matriz.push_back({ Value(0, 0, 0, 0), Value(0, 0, 0, 1), Value(0, 0, 1, 1), Value(0, 0, 1, 0) });
			matriz.push_back({ Value(0, 1, 0, 0), Value(0, 1, 0, 1), Value(0, 1, 1, 1), Value(0, 1, 1, 0) });
			matriz.push_back({ Value(1, 1, 0, 0), Value(1, 1, 0, 1), Value(1, 1, 1, 1), Value(1, 1, 1, 0) });
			matriz.push_back({ Value(1, 0, 0, 0), Value(1, 0, 0, 1), Value(1, 0, 1, 1), Value(1, 0, 1, 0) });
			break;
		default:
			cout << "failed to initialize Karnaugh\n";
			break;
		}
		
		maxCols = matriz[0].size();
		maxRows = matriz.size();

		assignPositionValues();
	}

	void showMatriz() {
		for (int i = 0; i < matriz.size(); i++) {
			for (int j = 0; j < matriz[i].size(); j++)
				cout << matriz[i][j].value << " ";
			cout << "\n";
		}
	}

	void setMatriz(int matriz[][4], int nRow, int nCol) {
		for (int i = 0; i < nRow; i++)
			for (int j = 0; j < nCol; j++)
				this->matriz[i][j].value = matriz[i][j];
	}


	bool existAll() {
		int count = 0;
		for (int i = 0; i < matriz.size(); i++)
			for (int j = 0; j < matriz[i].size(); j++)
				if (matriz[i][j].value) count++;
		return count == maxRows * maxCols;
	}

	void findOctets() {
		for (int i = 0, countCol, countRows; i < 4; i++) {
			countCol = 0;
			// verify rows
			for (int j = 0; j < maxCols; j++) {

				if (matriz[i][j].value && matriz[maxRangeRows(i)][j].value)
				{
					countCol++;
				}
				if (countCol == maxCols) {
					rowsOctFound.push_back({i, maxRangeRows(i)});

					cout << "octeto exist in rows " << i << ", " << (i + 1 < 4 ? i + 1 : 0) << "\n";

					for (int i = 0; i < rowsOctFound.size(); i++) { // temportal
						for (int j = 0; j < rowsOctFound[i].size(); j++)
						{
							cout << rowsOctFound[i][j] << ", ";
						}
						cout << endl;
					} // endtemporal

				}
			}

			// verify cols
			countRows = 0;
			for (int j = 0; j < maxRows; j++) {
				if (matriz[j][i].value && matriz[j][maxRangeCols(i)].value) {
					countRows++;
				}
				if (countRows == maxRows) {
					colsOctFound.push_back({ i, maxRangeCols(i) });

					cout << "octeto exist in columns " << i << ", " << maxRangeCols(i) << endl;

					for (int i = 0; i < colsOctFound.size(); i++) { // temportal
						for (int j = 0; j < colsOctFound[i].size(); j++)
						{
							cout << colsOctFound[i][j] << ", ";
						}
						cout << endl;
					} // endtemporal
				}
			}
		}

	}

	void findQuartets() {
		for (int i = 0, countCol, countRow; i < 4; i++) {
			// verify rows
			countCol = 0;
			for (int j = 0; j < maxCols; j++) {
				if (matriz[i][j].value) countCol++;
				if (countCol == maxCols) {
					if (!existValue(rowsOctFound, i)) {
						cout << "exist in rows " << i << "\n";
						rowsQuarFound.push_back(i);
					}
				}
			}

			// verify cols
			countRow = 0;
			for (int j = 0; j < maxRows; j++) {
				if (matriz[j][i].value) countRow++;
				if (countRow == maxRows) {
					if (!existValue(colsOctFound, i)) {
						cout << "exist in col " << i << "\n";
						colsQuarFound.push_back(i);
					}
				}
			}

		}

		// temporal
		for (size_t i = 0; i < colsQuarFound.size(); i++)
		{
			cout << "v col: " << colsQuarFound[i] << " ";
		}
		cout << endl;
		for (size_t i = 0; i < rowsQuarFound.size(); i++)
		{
			cout << "v row: " << rowsQuarFound[i] << " ";
		}
		cout << endl;
		// endtemporal

	}

	void findBox() {
		vector<vector<Value>> values;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				
				// verify two cols (j, j + 1) if exist in vector of octs cols
				if (existValue(colsOctFound, j) && existValue(colsOctFound, maxRangeCols(j))) break;

				// verify two rows (i, i + 1) if exist in vector of octs rows
				if (existValue(rowsOctFound, i) && existValue(rowsOctFound, maxRangeRows(i))) break;

				if (matriz[i][j].value && matriz[i][maxRangeCols(j)].value &&
					matriz[maxRangeRows(i)][j].value && matriz[maxRangeRows(i)][maxRangeCols(j)].value) {

					values.push_back({ 
						matriz[i][j], 
						matriz[i][maxRangeCols(j)], 
						matriz[maxRangeRows(i)][j], 
						matriz[maxRangeRows(i)][maxRangeCols(j)]});

					cout << "exist in pos: \n";
					cout << "[" << i << "]" << "[" << j << "]," << "[" << i << "][" << maxRangeCols(j) << "]\n";
					cout << "[" << maxRangeRows(i) << "]" << "[" << j << "]," << "[" << maxRangeRows(i) << "][" << maxRangeCols(j) << "]\n";
				
					cout << "--- i: " << i << "---j: " << j << endl;
				}
				
			}
		}

		// TODO: delete repeats and return Value
		removeRepeatsBoxes(values);
	}


	vector<Value> findOnes() {
		vector<Value> values;
		for (int i = 0; i < matriz.size(); i++) {
			for (int j = 0; j < matriz[i].size(); j++) {
				if (matriz[i][j].value) {
					if (!matriz[i][maxRangeCols(j)].value && !matriz[maxRangeRows(i)][j].value &&
						!matriz[i][minRangeCols(j)].value && !matriz[minRangeRows(i)][j].value) {
						cout << "exist one in pos [" << i << ", " << j << "]\n";
						values.push_back(matriz[i][j]);
					}
				}
			}
		}
		return values;
	}


private: 
	int maxRangeCols(int number) { return number + 1 < maxCols ? number + 1 : 0; }
	int maxRangeRows(int number) { return number + 1 < maxRows ? number + 1 : 0; }
	int minRangeCols(int number) { return number - 1 >= 0 ? number - 1 : maxCols - 1; }
	int minRangeRows(int number) { return number - 1 >= 0 ? number - 1 : maxRows - 1; }

	bool existValue(vector<vector<int>> vector, int value) {
		for (int i = 0; i < vector.size(); i++) 
			for (int j = 0; j < 2; j++)
				if (vector[i][j] == value) return true;
		return false;
	}

	void assignPositionValues() {
		for (int i = 0; i < maxRows; i++)
			for (int j = 0; j < maxCols; j++)
				matriz[i][j].setIndex(i, j);
	}

	vector<vector<Value>> removeRepeatsBoxes(vector<vector<Value>> values) {
		vector<Value> current;
		vector<int> index;
		int count;
		Value aux;
	
		for (int nroVector = 0; nroVector < values.size(); nroVector++) {
			current = values[nroVector];

			for (int i = 0; i < values.size(); i++) {
				if (nroVector == i) break; // dont repeat wit the same vector
				aux = current[i];


				for (int j = 0; j < values[i].size(); j++) {
					if (aux.col == values[i][j].col && aux.row == values[i][j].row) {
						
						break;
					}

					for (int k = 0; k < values[i].size(); k++) {

					}
				}
			}
		}

		//for (int i = 0; i < index.size(); i++)
		//	values.erase(values.begin() + index[i]);

		return values;
	}

};
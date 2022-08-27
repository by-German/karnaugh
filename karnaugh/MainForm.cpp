#include "MainForm.h"
#include "Karnaugh.hpp"

void findRows(int matriz[4][4], int maxCols = 4) {
	for (size_t i = 0, countCol; i < 4; i++)
	{
		countCol = 0;

		for (size_t j = 0; j < maxCols; j++)
		{
			if (matriz[i][j] == 1 && matriz[i + 1 < 4 ? i + 1 : 0][j] == 1)
			{
				countCol++;
			}
			if (countCol == 4) {
				cout << "exist in rows " << i << ", " << (i + 1 < 4 ? i + 1 : 0) << "\n";
			}
		}
	}
}

void findColumns(int matriz[4][4], int maxRows = 4) {

	for (size_t i = 0, countRows; i < 4; i++)
	{
		countRows= 0;

		for (size_t j = 0; j < maxRows; j++)
		{
			if (matriz[j][i] == 1 && matriz[j][i + 1 < 4 ? i + 1 : 0] == 1)
			{
				countRows++;
			}
			if (countRows == 4) {
				cout << "exist in columns " << i << ", " << (i + 1 < 4 ? i + 1 : 0) << "\n";
			}
		}
	}
}

void findBox(int matriz[4][4]) {
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (matriz[i][j] && matriz[i][j + 1 < 4 ? j + 1 : 0] &&
				matriz[i + 1 < 4 ? i + 1 : 0][j] && matriz[i + 1 < 4 ? i + 1 : 0][j + 1 < 4 ? j + 1 : 0])
			{
				cout << "exist in pos: \n";
				cout << "[" << i << "]" << "[" << j << "]," << "[" << i << "][" << (j + 1 < 4 ? j + 1 : 0) << "]\n";
				cout << "[" << (i + 1 < 4 ? i + 1 : 0) << "]" << "[" << j << "]," << "[" << (i + 1 < 4 ? i + 1 : 0) << "][" << (j + 1 < 4 ? j + 1 : 0) << "]\n\n";
			}
		}
	}
}

void findRow(int matriz[4][4]) {
	for (size_t i = 0, countCol, countRow; i < 4; i++)
	{
		countCol = 0;
		countRow = 0;

		for (size_t j = 0; j < 4; j++)
		{
			if (matriz[i][j] == 1) countCol++;
			if (countCol == 4) cout << "exist in rows " << i << "\n";

			if (matriz[j][i] == 1) countRow++;
			if (countRow == 4) cout << "exist in col " << i << "\n";
		}
	}
}

void findPairs(int matriz[4][4]) {
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			// horizontal
			if (matriz[i][j] && matriz[i][j + 1 < 4 ? j + 1 : 0])
			{
				cout << "exist horizontal in pos: \n";
				cout << "[" << i << "][" << j << "],[" << i << "][" << (j + 1 < 4 ? j + 1 : 0) << "]\n";
			}
			// vertical
			if (matriz[j][i] && matriz[j + 1 < 4 ? j + 1 : 0][i])
			{
				cout << "exist vertical in pos: \n";
				cout << "[" << j << "][" << i << "],[" << (j + 1 < 4 ? j + 1 : 0) << "][" << i << "]\n";
			}
		}
	}
}

int main() {

	// 4 variables

	int matriz[][4] = {
		{1, 0, 1, 1},
		{1, 0, 1, 1},
		{1, 1, 1, 1},
		{1, 1, 0, 0}
	};

	//int matriz[][4] = {
	//	{1, 1, 0, 1},
	//	{1, 1, 1, 1},
	//	{1, 0, 1, 1},
	//	{1, 0, 0, 1}
	//};

	// To verify cases in matriz 4 x 4
	//cout << "n = 2^4\n";
	//findAll(matriz);

	//cout << "n = 2^3\n";
	/*findRows(matriz);
	findColumns(matriz);*/

	//cout << "n = 2^2\n";
	//findBox(matriz);
	//findRow(matriz);

	//cout << "n = 2^1\n";
	//findPairs(matriz);

	//cout << "n = 2^0\n";
	//findOne(matriz);


	Karnaugh k = Karnaugh(4);
	k.setMatriz(matriz, 4, 4);
	k.showMatriz();


	if (!k.existAll()) {

		k.findOctets();
		k.findBox();
		k.findQuartets();

		vector<Value> ones = k.findOnes();
		for (size_t i = 0; i < ones.size(); i++)
		{
			cout << ones[i].a << " " << ones[i].b << " " << ones[i].c << " " << ones[i].d << " ";
		}
	}

	system("pause");
	return 0;
}

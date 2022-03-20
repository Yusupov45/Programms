#include <iostream>
#include <string>
#include <fstream>

using namespace std;
void vvod1();
void vvod2();
void vivodCRS();
void SumCRS(int*& mas_zn1, int*& mas_stol1, int*& mas_str1, int& razm1, int& razm12, int*& mas_zn2, int*& mas_stol2, int*& mas_str2, int& razm2, int razm22);
int** VSmass(int*& mas_str, int*& mas_stol, int*& mas_zn, int a, int b);
int** Sort(int**& vsmatsumm, int razm1, int razm2, int razm12, int count);
void umnCRS(int*& mas_zn1, int*& mas_stol1, int*& mas_str1, int razm1, int razm12, int*& mas_zn2, int*& mas_stol2, int*& mas_str2, int& razm2, int razm22);
void tr(int**& vsmat2, int razm2);
void matDos();
void SumCRS1();
void umnCRS1();

int main()
{
	setlocale(LC_ALL, "ru");
	int a;
	cout << "1 - Чтение с консоли" << endl << "2 - Чтение с файла" << endl << "3 - Вывод в формате CRS" << endl << "4 - матрица достижимости в формате CRS" << endl <<"5 - суммирование в формате CRS" << endl << "6 - умножение в формате CRS"<< endl;
	cin >> a;
	switch (a) {
	case 1:
		vvod1();
		break;
	case 2:
		vvod2();
		break;
	case 3:
		vivodCRS();
		break;
	case 4:
		matDos();
		break;
	case 5:
		SumCRS1();
		break;
	case 6:
		umnCRS1();
		break;
	default:
		cout << "Указан неверный номер";
	}
	return 0;

}

void vvod1()  // ввод с консоли
{
	int a1, a2;
	int stroka;
	int stolb = 2;
	int razm;
	cout << "Введите кол-во вершин: ";
	cin >> razm;
	cout << "Введите кол-во дуг: ";
	cin >> stroka;
	int** mat = new int* [stroka];  // создания массива в котором находятся номера смежных вершин
	for (int i = 0; i < stroka; i++) {
		mat[i] = new int[stolb];
	}
	int** smat = new int* [razm];
	for (int i = 0; i < razm; i++) { // создание матрицы смежности
		smat[i] = new int[razm];
	}
	for (int i = 0; i < razm; i++) {
		for (int j = 0; j < razm; j++) { // заполнение матрицы смежности 0
			smat[i][j] = 0;
		}
	}
	cout << "Введите смежные вершины: ";
	for (int i = 0; i < stroka; i++) {
		cin >> a1 >> a2;
		mat[i][0] = a1; // заполнение матрицы смежных вершин значениями
		mat[i][1] = a2;
		smat[a1 - 1][a2 - 1] = 1; // заполнение матрицы смежности единицами 
	}


	for (int i = 0; i < razm; i++) {
		for (int j = 0; j < razm; j++) { // вывод матрицы смежности
			cout << smat[i][j] <<" ";
		}
		cout << endl;
	}

	for (int i = 0; i < razm; i++) {
		delete[] smat[i];
	}
	delete[] smat;


	for (int i = 0; i < stroka; i++) {
		delete[] mat[i];
	}
	delete[] mat;
}




void vvod2() // ввод с файла 
{
	int a1, a2, razm, b;
	

	ifstream fin;
	fin.open("D:\\praka\\praka\\vvod.txt"); // открытие файла
	if (!fin.is_open()) {
		cout << "Ошибка чтения";
	}
	else {
		while (!fin.eof()) {
			fin >> razm >> b;              // кол-во вершин и дуг

			int** mat = new int* [b]; // создания массива в котором находятся номера смежных вершин
			for (int i = 0; i < b; i++) {
				mat[i] = new int[2];
			}
			int** smat = new int* [razm];
			for (int i = 0; i < razm; i++) { // создание матрицы смежности
				smat[i] = new int[razm];
			}
			for (int i = 0; i < razm; i++) {
				for (int j = 0; j < razm; j++) { // заполнение матрицы смежности 0
					smat[i][j] = 0;
				}
			}
			for (int i = 0; i < b; i++) { // чтение файла и занесение значений в массив
				fin >> a1 >> a2;
				mat[i][0] = a1;
				mat[i][1] = a2;
				smat[a1 - 1][a2 - 1] = 1; // заполнение матрицы смежности единицами
			}
			for (int i = 0; i < razm; i++) {
				for (int j = 0; j < razm; j++) { // вывод матрицы смежности
					cout << smat[i][j];
				}
				cout << endl;
			}
		}
	}
	fin.close();

}




void vivodCRS() // вывод матрицы смежности в формате CRS
{
	int razm, a;
	bool flag = false;
	int count = 0;
	int count2 = 0;
	cout << "Введите порядок квадратной матрицы: ";
	cin >> razm;
	int** mat = new int* [razm];  // создания матрицы смежности 
	for (int i = 0; i < razm; i++) {
		mat[i] = new int[razm];
	}
	cout << "Вводите значения матрицы смежности: ";
	for (int i = 0; i < razm; i++) {
		for (int j = 0; j < razm; j++) { // заполнение матрицы смежности 
			cin >> a;
			mat[i][j] = a;
			if (a == 1) {
				count++; // счетчик предназначен для считывания кол-ва единиц 
			}
		}
	}
	int* mas_zn = new int[count]; // создание массива значений
	int* mas_stol = new int[count]; // cоздание массива индексации столбцов
	int* mas_str = new int[razm + 1]; // создание массива индексации строк

	for (int i = 0; i < count; i++) {
		mas_zn[i] = 1;                 // заполнение массива значений 
	}

	mas_str[0] = 0;
	for (int i = 0; i < razm; i++) {
		for (int j = 0; j < razm; j++) {  // заполнение массива индексации строк
			if (mat[i][j] == 1) {
				count2 = count2 + 1;
			}
		}
		mas_str[i + 1] = count2;
	}

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < razm; j++) {
			for (int k = 0; k < razm; k++) {  // заполнение массива индексации столбцов
				if (mat[j][k] == 1) {
					mas_stol[i] = k;
					mat[j][k] = 0;
					flag = true;
					break;
				}
			}
			if (flag) {
				flag = false;
				break;
			}
		}
	}



	cout << "Вывод введеной матрицы в формате CRS:" << endl;
	for (int i = 0; i < count; i++) {
		cout << mas_zn[i];
	}
	cout << endl;

	for (int i = 0; i < count; i++) {   // Вывод на экран в формате CRS
		cout << mas_stol[i];
	}
	cout << endl;

	for (int i = 0; i < razm + 1; i++) {
		cout << mas_str[i];
	}


	ofstream fout;
	fout.open("D:\\praka\\praka\\vivodCRS.txt");
	if (!fout.is_open()) {
		cout << "Ошибка открытия файла";
	}
	else {
		fout << "Вывод введеной матрицы в формате CRS:" << endl;
		for (int i = 0; i < count; i++) {
			fout << mas_zn[i];
		}
		fout << endl;

		for (int i = 0; i < count; i++) {   // Вывод в файл в формате CRS
			fout << mas_stol[i];
		}
		fout << endl;

		for (int i = 0; i < razm + 1; i++) {
			fout << mas_str[i];
		}
	}
	fout.close();

}




void SumCRS(int*& mas_zn1, int*& mas_stol1, int*& mas_str1, int& razm1, int& razm12, int*& mas_zn2, int*& mas_stol2, int*& mas_str2, int& razm2, int razm22) // Суммирование в формате CRS
{
	int** vsmat1;
	int** vsmat2;

	vsmat1 = VSmass(mas_str1, mas_stol1, mas_zn1, razm1, razm12); // заполнение вспомогательных матриц в которых хранятся индексы ненулевых элементов 
	vsmat2 = VSmass(mas_str2, mas_stol2, mas_zn2, razm2, razm22);

	int r = razm1 + razm2;
	int** vsmatsumm = new int* [r];  // создание и заполнение вспомогательной матрицы где будет храниться сумма
	for (int i = 0; i < r; i++) {
		vsmatsumm[i] = new int[3];
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < 3; j++) {
			vsmatsumm[i][j] = 0;
		}
	}

	if (razm1 == 0) {
		for (int i = 0; i < razm2; i++) {
			vsmatsumm[i][0] = vsmat2[i][0];
			vsmatsumm[i][1] = vsmat2[i][1]; // если одна матрица нулевая
			vsmatsumm[i][2] = vsmat2[i][2];
		}
	}

	if (razm2 == 0) {
		for (int i = 0; i < razm1; i++) {
			vsmatsumm[i][0] = vsmat1[i][0];
			vsmatsumm[i][1] = vsmat1[i][1];
			vsmatsumm[i][2] = vsmat1[i][2];
		}
	}


	for (int i = 0; i < razm1; i++) {
		for (int j = 0; j < razm2; j++) {
			if ((vsmat1[i][0] == vsmat2[j][0]) && (vsmat1[i][1] == vsmat2[j][1])) {
				vsmatsumm[i][0] = vsmat1[i][0];
				vsmatsumm[i][1] = vsmat1[i][1]; // суммирование 1ч.
				vsmatsumm[i][2] = (vsmat1[i][2] + vsmat2[j][2]);
				break;
			}
			else {
				vsmatsumm[i][0] = vsmat1[i][0];
				vsmatsumm[i][1] = vsmat1[i][1];
				vsmatsumm[i][2] = vsmat1[i][2];
			}
		}
	}


	bool flag = false;
	int count = 0;

	for (int i = 0; i < razm2; i++) {
		for (int j = 0; j < razm1; j++) {
			if ((vsmat2[i][0] == vsmat1[j][0]) && (vsmat2[i][1] == vsmat1[j][1])) {
				flag = false;
				break;
			}
			else {
				flag = true;
			}
		}
		if (flag) {
			vsmatsumm[(i + razm1)][0] = vsmat2[i][0]; // суммирование 2ч.
			vsmatsumm[(i + razm1)][1] = vsmat2[i][1];
			vsmatsumm[(i + razm1)][2] = vsmat2[i][2];
			flag = true;
		}

	}

	for (int i = 0; i < (razm1 + razm2); i++) {
		if ((vsmatsumm[i][0] == 0) && (vsmatsumm[i][1] == 0) && (vsmatsumm[i][2] == 0)) {
			count++; // нахождение кол-ва строк со всеми нулевыми элементами 
		}
	}

	int** vsmatsumm1 = Sort(vsmatsumm, razm1, razm2, razm12, count); // сортироровка и избавление от строк со всеми нулевыми элементами


	int* mas_znsumm = new int[razm1 + razm2 - count];
	int* mas_stolsumm = new int[razm1 + razm2 - count]; // создание crs массивов суммы
	int* mas_strsumm = new int[razm22];


	for (int i = 0; i < razm1 + razm2 - count; i++) {
		mas_znsumm[i] = vsmatsumm1[i][2];
		mas_stolsumm[i] = vsmatsumm1[i][1]; // заполнение
	}


	mas_strsumm[0] = 0;
	int count1 = 0;
	for (int i = 0; i < razm22 - 1; i++) {
		for (int j = 0; j < razm1 + razm2 - count; j++) { // заполнение
			if (vsmatsumm1[j][0] == i) {
				count1++;
			}
		}
		mas_strsumm[i + 1] = count1;
	}

	for (int i = 0; i < razm1 + razm2 - count; i++) {
		delete[] vsmatsumm1 [i]; // чистка памяти
	}
	delete[] vsmatsumm1;


	mas_zn1 = mas_znsumm;
	mas_stol1 = mas_stolsumm; 
	mas_str1 = mas_strsumm;
	razm1 = razm1 + razm2 - count;

}


int** VSmass(int*& mas_str, int*& mas_stol, int*& mas_zn, int a, int b) {
	int** mat = new int* [a];
	for (int i = 0; i < a; i++) {
		mat[i] = new int[3];
	}


	for (int i = 1; i < b; i++) {
		for (int j = mas_str[i - 1]; j < mas_str[i]; j++) { // создание вспомогательной матрицы с помощью crs
			mat[j][0] = i - 1;
			mat[j][1] = mas_stol[j];
			mat[j][2] = mas_zn[j];
		}
	}

	return mat;

}

int** Sort(int**& vsmatsumm, int razm1, int razm2, int razm12, int count)
{
	int* temp = new int[3];

	int** vsmatsumm1 = new int* [(razm1 + razm2 - count)]; // создание вспомогательной матрицы где не будет строк со всеми нулевыми значениями
	for (int i = 0; i < razm1 + razm2 - count; i++) {
		vsmatsumm1[i] = new int[3];
	}

	for (int i = 0; i < razm1 + razm2 - count; i++) {
		for (int j = 0; j < razm1 + razm2; j++) {
			if (vsmatsumm[j][2] != 0) {
				vsmatsumm1[i][0] = vsmatsumm[j][0];
				vsmatsumm1[i][1] = vsmatsumm[j][1]; // заполнение новой вспомогательной матрицы
				vsmatsumm1[i][2] = vsmatsumm[j][2];
				vsmatsumm[j][0] = 0;
				vsmatsumm[j][1] = 0;
				vsmatsumm[j][2] = 0;
				break;
			}
		}
	}


	for (int i = 0; i < razm1 + razm2 - count; i++) {
		for (int j = 0; j < razm1 + razm2 - count - i - 1; j++) {
			if (vsmatsumm1[j][0] > vsmatsumm1[j + 1][0]) {
				temp[0] = vsmatsumm1[j][0];
				temp[1] = vsmatsumm1[j][1];
				temp[2] = vsmatsumm1[j][2];
				vsmatsumm1[j][0] = vsmatsumm1[j + 1][0]; // сортировка по первым индексам (индексы строк)
				vsmatsumm1[j][1] = vsmatsumm1[j + 1][1];
				vsmatsumm1[j][2] = vsmatsumm1[j + 1][2];
				vsmatsumm1[j + 1][0] = temp[0];
				vsmatsumm1[j + 1][1] = temp[1];
				vsmatsumm1[j + 1][2] = temp[2];

			}
		}
	}
	for (int i = 0; i < razm12 - 1; i++) {
		for (int j = 0; j < razm1 + razm2 - count; j++) {
			for (int k = 0; k < razm1 + razm2 - count - j - 1; k++) {
				if ((vsmatsumm1[k][1] > vsmatsumm1[k + 1][1]) && (vsmatsumm1[k][0] == i && vsmatsumm1[k + 1][0] == i)) {
					temp[0] = vsmatsumm1[k][0];
					temp[1] = vsmatsumm1[k][1];
					temp[2] = vsmatsumm1[k][2];
					vsmatsumm1[k][0] = vsmatsumm1[k + 1][0];
					vsmatsumm1[k][1] = vsmatsumm1[k + 1][1]; // сортировка по вторым индесам (индексы столбцов)
					vsmatsumm1[k][2] = vsmatsumm1[k + 1][2];
					vsmatsumm1[k + 1][0] = temp[0];
					vsmatsumm1[k + 1][1] = temp[1];
					vsmatsumm1[k + 1][2] = temp[2];
				}
			}
		}
	}

	for (int i = 0; i < razm1 + razm2; i++) {
		delete[] vsmatsumm[i];
	}
	delete[] vsmatsumm; 
	delete[] temp; 


	return vsmatsumm1;
}


void umnCRS(int*& mas_zn1, int*& mas_stol1, int*& mas_str1, int razm1, int razm12, int*& mas_zn2, int*& mas_stol2, int*& mas_str2, int& razm2, int razm22) {
	int** vsmat1;
	int** vsmat2;

	vsmat1 = VSmass(mas_str1, mas_stol1, mas_zn1, razm1, razm12); // заполнение вспомогательных матриц в которых хранятся индексы ненулевых элементов 
	vsmat2 = VSmass(mas_str2, mas_stol2, mas_zn2, razm2, razm22);


	int summ = 0;
	int count = 0;

	tr(vsmat2, razm2);

	for (int k = 0; k < razm12 - 1; k++) {
		for (int n = 0; n < razm12 - 1; n++) {
			for (int i = 0; i < razm1; i++) {
				for (int j = 0; j < razm2; j++) {
					if (vsmat1[i][0] == k && vsmat2[j][0] == n && vsmat1[i][1] == vsmat2[j][1]) {
						summ = summ + vsmat1[i][2] * vsmat2[j][2];
					}
				} // считаем кол-во ненулевых значений при умножении 
			}
			if (summ != 0) {
				count++;
			}
			summ = 0;
		}
	}

	summ = 0;

	int** vsmatumn = new int* [count];
	for (int i = 0; i < count; i++) { // создание результирующего вспомогательного массива где будут храниться ненулевые значения после умножения
		vsmatumn[i] = new int[3];
	}

	int x = 0;

	for (int k = 0; k < razm12 - 1; k++) {
		for (int n = 0; n < razm12 - 1; n++) {
			for (int i = 0; i < razm1; i++) {
				for (int j = 0; j < razm2; j++) {
					if (vsmat1[i][0] == k && vsmat2[j][0] == n && vsmat1[i][1] == vsmat2[j][1]) {
						summ = summ + vsmat1[i][2] * vsmat2[j][2];
					}
				}
			}
			if (summ != 0) {
				vsmatumn[x][0] = k;
				vsmatumn[x][1] = n;  // заполнение результирующего вспомогательного массива
				vsmatumn[x][2] = summ;
				x++;
				summ = 0;
			}
		}
	}


	int* mas_znsumm = new int[count];
	int* mas_stolsumm = new int[count]; // создание crs массивов суммы
	int* mas_strsumm = new int[razm22];



	for (int i = 0; i < count; i++) {
		mas_znsumm[i] = vsmatumn[i][2];
		mas_stolsumm[i] = vsmatumn[i][1]; // заполнение массивов значений и столбцов
	}


	mas_strsumm[0] = 0;
	int count1 = 0;
	for (int i = 0; i < razm22 - 1; i++) {
		for (int j = 0; j < count; j++) { // заполнение массива строк
			if (vsmatumn[j][0] == i) {
				count1++;
			}
		}
		mas_strsumm[i + 1] = count1;
	}

	for (int i = 0; i < count; i++) {
		delete[] vsmatumn[i]; // чистка памяти
	}
	delete[] vsmatumn;

	for (int i = 0; i < razm1; i++) { // чистка памяти
		delete[] vsmat1[i];
	}
	delete [] vsmat1;
	for (int i = 0; i < razm2; i++) { // чистка памяти
		delete[] vsmat2[i];
	}
	delete [] vsmat2;


	mas_zn2 = mas_znsumm;
	mas_stol2 = mas_stolsumm;
	mas_str2 = mas_strsumm;
	razm2 = count;

}


void tr(int**& vsmat2, int razm2) {
	int temp;
	for (int i = 0; i < razm2; i++) {
		temp = vsmat2[i][0];
		vsmat2[i][0] = vsmat2[i][1];  // транспонирование
		vsmat2[i][1] = temp;
	}
}


void matDos() {
	int razm, a;
	bool flag = false;
	int count = 0;
	int count2 = 0;
	cout << "Введите порядок квадратной матрицы: ";
	cin >> razm;
	int** mat = new int* [razm];  // создания матрицы смежности 
	for (int i = 0; i < razm; i++) {
		mat[i] = new int[razm];
	}
	cout << "Вводите значения матрицы смежности: ";
	for (int i = 0; i < razm; i++) {
		for (int j = 0; j < razm; j++) { // заполнение матрицы смежности 
			cin >> a;
			mat[i][j] = a;
			if (a != 0) {
				count++; // счетчик предназначен для считывания кол-ва единиц 
			}
		}
	}
	int* mas_zn = new int[count]; // создание массива значений
	int* mas_stol = new int[count]; // cоздание массива индексации столбцов
	int* mas_str = new int[razm + 1]; // создание массива индексации строк

	for (int i = 0; i < count; i++) {
		mas_zn[i] = 1;                 // заполнение массива значений 
	}

	mas_str[0] = 0;
	for (int i = 0; i < razm; i++) {
		for (int j = 0; j < razm; j++) {  // заполнение массива индексации строк
			if (mat[i][j] == 1) {
				count2++;
			}
		}
		mas_str[i + 1] = count2;
	}

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < razm; j++) {
			for (int k = 0; k < razm; k++) {  // заполнение массива индексации столбцов
				if (mat[j][k] != 0) {
					mas_stol[i] = k;
					mat[j][k] = 0;
					flag = true;
					break;
				}
			}
			if (flag) {
				flag = false;
				break;
			}
		}
	}


	int* mas_znf;
	int* mas_stolf; // для умножений
	int* mas_strf;
	int razm1 = razm + 1;
	int razm2 = count;
	int razm22 = razm1;
	mas_znf = mas_zn;
	mas_stolf = mas_stol;
	mas_strf = mas_str;


	int razms = razm;
	int razms2 = razm + 1;
	int* mas_znv = new int[razms]; // для сложений
	int* mas_stolv = new int[razms];
	int* mas_strv = new int[razms2];

	mas_strv[0] = 0;

	for (int i = 0; i < razms; i++) {
		mas_znv[i] = 1;
		mas_stolv[i] = i; // единичная матрица
		mas_strv[i + 1] = i + 1;
	}

	SumCRS(mas_znv, mas_stolv, mas_strv, razms, razms2, mas_znf, mas_stolf, mas_strf, razm2, razm22); // складывание единичной матрицы и матрицы достижимости 

	

	for (int i = 2; i < razm; i++) {
		umnCRS(mas_zn, mas_stol, mas_str, count, razm1, mas_znf, mas_stolf, mas_strf, razm2, razm22);//  формула матрицы достижимости
		SumCRS(mas_znv, mas_stolv, mas_strv, razms, razms2, mas_znf, mas_stolf, mas_strf, razm2, razm22);
	}


	cout << "Массив значений: ";
	for (int i = 0; i < razms; i++) {
		cout << mas_znv[i] << " ";
	}
	cout << endl;

	cout << "Массив столбцов: ";
	for (int i = 0; i < razms; i++) { // вывод матрицы достижимости
		cout << mas_stolv[i] << " ";
	}
	cout << endl;

	cout << "Массив строк: ";
	for (int i = 0; i < razms2; i++) {
		cout << mas_strv[i] << " ";
	}

	
	ofstream fout;
	fout.open("D:\\praka\\praka\\vivodMatDos.txt");
	if (!fout.is_open()) {
		cout << "Ошибка открытия файла";
	}
	else {
		fout << "матрица достижимости в формате CRS:" << endl;
		fout << "Массив значений: ";
		for (int i = 0; i < razms; i++) {
			fout << mas_znv[i]<<" ";
		}
		fout << endl;

		fout << "Массив столбцов: ";
		for (int i = 0; i < razms; i++) {   // Вывод в файл матрицы достижимости
			fout << mas_stolv[i]<< " ";
		}
		fout << endl;

		fout << "Массив строк: ";
		for (int i = 0; i < razms2; i++) {
			fout << mas_strv[i]<< " ";
		}
	}
	fout.close(); 


}

void SumCRS1() // Суммирование в формате CRS
{
	int razm1, razm12, razm2, razm22;
	int** vsmat1;
	int** vsmat2;
	cout << "Введите размерность массивов первого CRS, 1 - значения,столбы, 2- строки: ";
	cin >> razm1 >> razm12;
	cout << "Введите размерность массивов второго CRS, 1 - значения,столбы, 2- строки: ";
	cin >> razm2 >> razm22;
	int* mas_zn1 = new int[razm1];
	int* mas_stol1 = new int[razm1];
	int* mas_str1 = new int[razm12];


	int* mas_zn2 = new int[razm2];
	int* mas_stol2 = new int[razm2];
	int* mas_str2 = new int[razm22];


	cout << "Введите значения элементов первого массива значений: ";   // заполнение массивов
	for (int i = 0; i < razm1; i++) {
		cin >> mas_zn1[i];
	}
	cout << "Введите значения элементов первого массива столбцов: ";
	for (int i = 0; i < razm1; i++) {
		cin >> mas_stol1[i];
	}
	cout << "Введите значения элементов первого массива строк: ";
	for (int i = 0; i < razm12; i++) {
		cin >> mas_str1[i];
	}
	cout << "Введите значения элементов второго массива значений: ";
	for (int i = 0; i < razm2; i++) {
		cin >> mas_zn2[i];
	}
	cout << "Введите значения элементов второго массива столбцов: ";
	for (int i = 0; i < razm2; i++) {
		cin >> mas_stol2[i];
	}
	cout << "Введите значения элементов второго массива строк: ";
	for (int i = 0; i < razm22; i++) {
		cin >> mas_str2[i];
	}


	vsmat1 = VSmass(mas_str1, mas_stol1, mas_zn1, razm1, razm12); // заполнение вспомогательных матриц в которых хранятся индексы ненулевых элементов 
	vsmat2 = VSmass(mas_str2, mas_stol2, mas_zn2, razm2, razm22);

	int r = razm1 + razm2;
	int** vsmatsumm = new int* [r];  // создание и заполнение вспомогательной матрицы где будет храниться сумма
	for (int i = 0; i < r; i++) {
		vsmatsumm[i] = new int[3];
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < 3; j++) {
			vsmatsumm[i][j] = 0;
		}
	}

	if (razm1 == 0) {
		for (int i = 0; i < razm2; i++) {
			vsmatsumm[i][0] = vsmat2[i][0];
			vsmatsumm[i][1] = vsmat2[i][1];
			vsmatsumm[i][2] = vsmat2[i][2];  // для случая когда есть нулевая матрица
		}
	}

	if (razm2 == 0) {
		for (int i = 0; i < razm1; i++) {
			vsmatsumm[i][0] = vsmat1[i][0];
			vsmatsumm[i][1] = vsmat1[i][1];
			vsmatsumm[i][2] = vsmat1[i][2];
		}
	}

	for (int i = 0; i < razm1; i++) {
		for (int j = 0; j < razm2; j++) {
			if ((vsmat1[i][0] == vsmat2[j][0]) && (vsmat1[i][1] == vsmat2[j][1])) {
				vsmatsumm[i][0] = vsmat1[i][0];
				vsmatsumm[i][1] = vsmat1[i][1]; // суммирование 1ч.
				vsmatsumm[i][2] = (vsmat1[i][2] + vsmat2[j][2]);
				break;
			}
			else {
				vsmatsumm[i][0] = vsmat1[i][0];
				vsmatsumm[i][1] = vsmat1[i][1];
				vsmatsumm[i][2] = vsmat1[i][2];
			}
		}
	}


	bool flag = false;
	int count = 0;

	for (int i = 0; i < razm2; i++) {
		for (int j = 0; j < razm1; j++) {
			if ((vsmat2[i][0] == vsmat1[j][0]) && (vsmat2[i][1] == vsmat1[j][1])) {
				flag = false;
				break;
			}
			else {
				flag = true;
			}
		}
		if (flag) {
			vsmatsumm[(i + razm1)][0] = vsmat2[i][0]; // суммирование 2ч.
			vsmatsumm[(i + razm1)][1] = vsmat2[i][1];
			vsmatsumm[(i + razm1)][2] = vsmat2[i][2];
			flag = true;
		}

	}

	for (int i = 0; i < (razm1 + razm2); i++) {
		if ((vsmatsumm[i][0] == 0) && (vsmatsumm[i][1] == 0) && (vsmatsumm[i][2] == 0)) {
			count++; // нахождение кол-ва строк со всеми нулевыми элементами 
		}
	}

	int** vsmatsumm1 = Sort(vsmatsumm, razm1, razm2, razm12, count); // сортироровка и избавление от строк со всеми нулевыми элементами

	int* mas_znsumm = new int[razm1 + razm2 - count];
	int* mas_stolsumm = new int[razm1 + razm2 - count]; // создание crs массивов суммы
	int* mas_strsumm = new int[razm22];


	for (int i = 0; i < razm1 + razm2 - count; i++) {
		mas_znsumm[i] = vsmatsumm1[i][2];
		mas_stolsumm[i] = vsmatsumm1[i][1]; // заполнение
	}


	mas_strsumm[0] = 0;
	int count1 = 0;
	for (int i = 0; i < razm22 - 1; i++) {
		for (int j = 0; j < razm1 + razm2 - count; j++) { // заполнение
			if (vsmatsumm1[j][0] == i) {
				count1++;
			}
		}
		mas_strsumm[i + 1] = count1;
	}

	cout << "Массив значений: ";
	for (int i = 0; i < razm1 + razm2 - count; i++) {
		cout << mas_znsumm[i] << " ";
	}
	cout << endl;

	cout << "Массив столбцов: ";
	for (int i = 0; i < razm1 + razm2 - count; i++) {  // вывод
		cout << mas_stolsumm[i] << " ";
	}
	cout << endl;

	cout << "Массив строк: ";
	for (int i = 0; i < razm22; i++) {
		cout << mas_strsumm[i] << " ";
	}

}

void umnCRS1() {
	int razm1, razm12, razm2, razm22;
	int** vsmat1;
	int** vsmat2;
	cout << "Введите размерность массивов первого CRS, 1 - значения,столбы, 2- строки: ";
	cin >> razm1 >> razm12;
	cout << "Введите размерность массивов второго CRS, 1 - значения,столбы, 2- строки: ";
	cin >> razm2 >> razm22;
	int* mas_zn1 = new int[razm1];
	int* mas_stol1 = new int[razm1];
	int* mas_str1 = new int[razm12];


	int* mas_zn2 = new int[razm2];
	int* mas_stol2 = new int[razm2];
	int* mas_str2 = new int[razm22];


	cout << "Введите значения элементов первого массива значений: ";   // заполнение массивов
	for (int i = 0; i < razm1; i++) {
		cin >> mas_zn1[i];
	}
	cout << "Введите значения элементов первого массива столбцов: ";
	for (int i = 0; i < razm1; i++) {
		cin >> mas_stol1[i];
	}
	cout << "Введите значения элементов первого массива строк: ";
	for (int i = 0; i < razm12; i++) {
		cin >> mas_str1[i];
	}
	cout << "Введите значения элементов второго массива значений: ";
	for (int i = 0; i < razm2; i++) {
		cin >> mas_zn2[i];
	}
	cout << "Введите значения элементов второго массива столбцов: ";
	for (int i = 0; i < razm2; i++) {
		cin >> mas_stol2[i];
	}
	cout << "Введите значения элементов второго массива строк: ";
	for (int i = 0; i < razm22; i++) {
		cin >> mas_str2[i];
	}

	vsmat1 = VSmass(mas_str1, mas_stol1, mas_zn1, razm1, razm12); // заполнение вспомогательных матриц в которых хранятся индексы ненулевых элементов 
	vsmat2 = VSmass(mas_str2, mas_stol2, mas_zn2, razm2, razm22);

	int summ = 0;
	int count = 0;

	tr(vsmat2, razm2);

	for (int k = 0; k < razm12 - 1; k++) {
		for (int n = 0; n < razm12 - 1; n++) {
			for (int i = 0; i < razm1; i++) {
				for (int j = 0; j < razm2; j++) {
					if (vsmat1[i][0] == k && vsmat2[j][0] == n && vsmat1[i][1] == vsmat2[j][1]) {
						summ = summ + vsmat1[i][2] * vsmat2[j][2];
					}
				} // считаем кол-во ненулевых значений при умножении 
			}
			if (summ != 0) {
				count++;
			}
			summ = 0;
		}
	}

	summ = 0;

	int** vsmatumn = new int* [count];
	for (int i = 0; i < count; i++) { // создание результирующего вспомогательного массива где будут храниться ненулевые значения после умножения
		vsmatumn[i] = new int[3];
	}

	int x = 0;

	for (int k = 0; k < razm12 - 1; k++) {
		for (int n = 0; n < razm12 - 1; n++) {
			for (int i = 0; i < razm1; i++) {
				for (int j = 0; j < razm2; j++) {
					if (vsmat1[i][0] == k && vsmat2[j][0] == n && vsmat1[i][1] == vsmat2[j][1]) {
						summ = summ + vsmat1[i][2] * vsmat2[j][2];
					}
				}
			}
			if (summ != 0) {
				vsmatumn[x][0] = k;
				vsmatumn[x][1] = n;  // заполнение результирующего вспомогательного массива
				vsmatumn[x][2] = summ;
				x++;
				summ = 0;
			}
		}
	}


	int* mas_znsumm = new int[count];
	int* mas_stolsumm = new int[count]; // создание crs массивов суммы
	int* mas_strsumm = new int[razm22];



	for (int i = 0; i < count; i++) {
		mas_znsumm[i] = vsmatumn[i][2];
		mas_stolsumm[i] = vsmatumn[i][1]; // заполнение массивов значений и столбцов
	}


	mas_strsumm[0] = 0;
	int count1 = 0;
	for (int i = 0; i < razm22 - 1; i++) {
		for (int j = 0; j < count; j++) { // заполнение массива строк
			if (vsmatumn[j][0] == i) {
				count1++;
			}
		}
		mas_strsumm[i + 1] = count1;
	}


	cout << "Массив значений: ";
	for (int i = 0; i < count; i++) {
		cout << mas_znsumm[i] << " ";
	}
	cout << endl;

	cout << "Массив столбцов: ";
	for (int i = 0; i < count; i++) {  // вывод
		cout << mas_stolsumm[i] << " ";
	}
	cout << endl;

	cout << "Массив строк: ";
	for (int i = 0; i < razm22; i++) {
		cout << mas_strsumm[i] << " ";
	}

}
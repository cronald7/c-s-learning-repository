//#include "pch.h"
#include <iostream>
using namespace std;
//定义类模板时，要使用<T>
template <class T>
class CArray3D {
public:
	//定义一个二维数组类模板
	template <class T1>
	class CArray2D {
	private:
		T1 *p1;
		int j, k;
	public:
		CArray2D() { p1 = NULL; }
		CArray2D(int j_, int k_) : j(j_), k(k_) {
			p1 = new T1[j * k];
		}
		T1 *operator[](int t) {
			return p1 + j * t;
		}
		~CArray2D() {
			if (p1 != NULL) delete[]p1;
		}
	};
	//定义三维数组类模板
	CArray3D() { array2D = NULL; }
	CArray3D(int i, int j, int k) {
		array2D = new CArray2D<T> *[i];
		for (int n = 0; n < i; ++n) {
			array2D[n] = new CArray2D<T>(j, k);
		}
	}
	CArray2D<T> &operator[](int i) {
		return *array2D[i];
	}
	~CArray3D() {
		if (array2D != NULL) delete[]array2D;
	}
private:
	CArray2D<T> **array2D;
};

int main()
{
	CArray3D<int> a(3, 4, 5);
	int No = 0;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 5; ++k)
				a[i][j][k] = No++;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 5; ++k)
				cout << a[i][j][k] << ",";
	return 0;
}
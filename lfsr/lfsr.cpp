#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#define MAX_LEN 31
using namespace std; 

int main() {   
	int a[MAX_LEN] = {1, 1, 1, 0, 1}; 
	for (int i = 5; i < MAX_LEN; ++i)
		a[i] = (a[i - 2] + a[i - 5]) % 2;
	cout << "密钥如下：" << endl;
	for (int i = 0; i < MAX_LEN; ++i)
		cout << a[i];
	cout << endl;
	int i = 0, j = 0, key;
	cout << "请选择操作方式" << endl << "1:加密clear.txt中的内容" << endl << "2:解密cipher.txt中的内容" << endl;
	cin >> key;
	ifstream in;
	ofstream out;
	if (key == 1) {
		in.open("clear.txt", ios::in);
		out.open("cipher.txt", ios::out);
	}
	else if (key == 2) {
		in.open("cipher.txt", ios::in);
		out.open("clear.txt", ios::out);
	}
	else {
		cout << "错误的操作！" << endl;
		return 1;
	} 
	char c;
	vector<int> s;
	while ((c = in.get()) != EOF) {
		int sum = 0;
		for (j = 0; j < 8; ++j)
			sum += pow(2, 7 - j) * a[(i + j) % MAX_LEN];
		if (i + j > 32)
			i = (i + j - 1) % MAX_LEN + 1;
		else
			i += 8;
		s.push_back((int(c)) ^ sum);
	}
	for (int k = 0; k < s.size(); ++k)
		out << char(s[k]);
	cout << "操作已完成！" << endl;
	return 0;
}


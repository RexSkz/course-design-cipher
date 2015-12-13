#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std; 

int main() {   
	int a[31] = {1, 1, 0, 0, 1}; 
	for (int i = 5; i < 31; ++i)
		a[i] = (a[i - 2] + a[i - 5]) % 2;
	cout << "��Կ���£�" << endl;
	for (int i = 0; i<31; ++i)
		cout << a[i] << " ";
	cout << endl;
	int i = 0, j = 0, key;
	cout << "��ѡ�������ʽ" << endl << "1:����clear.txt�е�����" << endl << "2:����cipher.txt�е�����" << endl;
	cin >> key;
	vector<int> s, ss;
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
		cout << "����Ĳ�����" << endl;
		return 1;
	} 
	char c;
	while ((c = in.get()) != EOF) {
		int sum = 0;
		for (j = 0; j < 8; ++j)
			sum += pow(2, 7 - j) * a[(i + j) % 31];
		if (i + j > 32)
			i = (i + j - 1) % 31 + 1;
		else
			i += 8;
		s.push_back((int(c)) ^ sum);
	}
	for (int k = 0; k < s.size(); ++k)
		out << char(s[k]);
	cout << "��������ɣ�" << endl;
	return 0;
}


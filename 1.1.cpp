#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

const int k2_rev[] = {0, 1, 0, 9, 0, 21, 0, 15, 0, 3, 0, 19, 0, 0, 0, 7, 0, 23, 0, 11, 0, 5, 0, 17, 0, 25};

string encrypt(string s, int k1, int k2) {
	string t = "";
	for (int i = 0; i < s.size(); ++i) {
		int ch = s[i] - 'a';
		ch = (k1 + k2 * ch) % 26;
		t += (char)ch;
	}
	return t;
}

int main(int argc, char** argv) {
	int k1, k2, method;
	ostringstream buf;
	char ch;
	ifstream inf(argv[1]);
	while (buf && inf.get(ch)) buf.put(ch);
	string s = buf.str();
	cout << "Input k1, k2, method(1 for encrypt, -1 for decrypt): ";
	cin >> k1 >> k2 >> method;
	return 0;
}
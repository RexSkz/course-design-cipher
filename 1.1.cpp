#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

const int rev[] = {0, 1, 0, 9, 0, 21, 0, 15, 0, 3, 0, 19, 0, 0, 0, 7, 0, 23, 0, 11, 0, 5, 0, 17, 0, 25};

string affine(string s, int k1, int k2, string method) {
	string t = "";
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] >= 'A' && s[i] <= 'Z' || s[i] >= 'a' && s[i] <= 'z') {
			char tar;
			if (s[i] >= 'A' && s[i] <= 'Z') tar = 'A';
			else if (s[i] >= 'a' && s[i] <= 'z') tar = 'a';
			int ch = s[i] - tar;
			if (method == "encrypt")
				ch = (k1 + k2 * ch) % 26;
			else if (method == "decrypt")
				ch = rev[k2] * (ch - k1 + 26) % 26;
			t += (char)(ch + tar);
		}
		else t += s[i];
	}
	return t;
}

void count(string s) {
	int a[26] = {0};
	for (int i = 0; i < s.size(); ++i) {
		char ch;
		if (s[i] >= 'A' && s[i] <= 'Z') ch = s[i] - 'A';
		else if (s[i] >= 'a' && s[i] <= 'z') ch = s[i] - 'a';
		else continue;
		++a[ch];
	}
	for (int i = 0; i < 26; ++i) {
		cout << (char)(i + 'A') << ": " << a[i] << "\t";
	}
	cout << endl;
}

int main(int argc, char** argv) {
	int k1, k2, method;
	ostringstream buf;
	char ch;
	ifstream inf(argv[1]);
	while (buf && inf.get(ch)) buf.put(ch);
	string s = buf.str();
	cout << "Input k1, k2: ";
	cin >> k1 >> k2;
	// shows that encrypt and decrypt function is correct
	string t = affine(s, k1, k2, "encrypt");
	s = affine(t, k1, k2, "decrypt");
	cout << s << endl;
	cout << "Count for clear text: " << endl;
	count(s);
	cout << "Count for cipher text: " << endl;
	count(t);
	return 0;
}
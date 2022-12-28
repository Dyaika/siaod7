#include "Compression.h"

string Compression::rle(string str)
{
	string res = "";
	int count = 0;
	for (int i = 0; i < str.size(); i++) {
		count = 1;
		while (str.size() > i + 1 and str[i] == str[i + 1]) {
			count++;
			i++;
		}
		res += to_string(count) + str[i];
	}
	return res;
}

vector<Compression::node77> Compression::lz77(string str)
{
	vector<node77> res;
	for (int i = 0; i < str.size(); i++) {
		int offset = 0;
		int length = 0;
		for (int j = i - 1; j >= 0; j--) {
			int k = 0;
			while (i + k < str.size() and str[i + k] == str[j + k]) {//!
				k++;
			}
			if (k > length) {
				if (k > length) {
					offset = i - j;
					length = k;
				}
			}
		}
		node77 node(offset, length, str[i + length]);
		res.push_back(node);
		i += length;
	}
	return res;
}

string Compression::to_text77(vector<node77> nodes)
{
	string res = "";
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes[i].length; j++) {
			res += res[res.size() - nodes[i].offset];
		}
		res += nodes[i].next;
	}
	return res;
}

vector<Compression::node78> Compression::lz78(string str)
{
	vector<node78> res;
	map<string, int> dictionary;
	node78 node{ 0, ' ' };
	string buffer = "";
	for (int i = 0; i < str.size(); i++) {
		if (dictionary[buffer + str[i]] != 0) {
			buffer += str[i];

		}
		else {
			node.position = dictionary[buffer];
			node.next = str[i];
			res.push_back(node);
			dictionary[buffer + str[i]] = dictionary.size() - 1;
			buffer = "";
		}
	}
	if (buffer.size() > 0) {
		char last = buffer[buffer.size() - 1];
		buffer = buffer.substr(0, buffer.size() - 1);
		node.position = dictionary[buffer];
		node.next = last;
		res.push_back(node);
	}
	return res;
}

string Compression::to_text78(vector<node78> nodes)
{
	string res = "";
	vector<string> strs;
	strs.push_back("");
	for (int i = 0; i < nodes.size(); i++) {
		string word = strs[nodes[i].position] + nodes[i].next;
		res += word;
		strs.push_back(word);
	}
	return res;
}

void Compression::test()
{
	setlocale(LC_ALL, "rus");
	int n;
	int task = 1;
	string str, comp_str;
	vector<node77> nodes77;
	vector<node78> nodes78;
	cout << "Welcome to test program. Choose algorithm:";
	while (task > 0 and task < 6) {
		cout << "\n1) run length encoding (RLE)\n2) Lempel-Ziv algorithm (LZ77)\n3) Lempel-Ziv algorithm (LZ78)\n4) Shannon-Fano algorithm\n5) Huffman algorithm\n> ";
		cin >> task;
		switch (task)
		{
		case 1:
			str = "AAAAAAAAAAAAAAABBBBBBBBBBBBJJJJJJJJJIIIIIIIIIJJJJJJJJJOOOOOOOOOJJJJJJJ";
			cout << "Normal: " << str;
			comp_str = rle(str);
			cout << "\nCompressed: " << comp_str;
			cout << "\nkoef=" << (comp_str.size() * 1.0) / (str.size() * 1.0) << "\n\n";
			str = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMCDEFGHIJKLZ";
			cout << "Normal: " << str;
			comp_str = rle(str);
			cout << "\nCompressed: " << comp_str;
			cout << "\nkoef=" << (comp_str.size() * 1.0) / (str.size() * 1.0) << "\n\n";

			cout << "---completed---\n";
			break;
		case 2:
			str = "101000100101010001011";
			nodes77 = lz77(str);
			cout << "Normal: " << str;
			cout << "\nCompressed:\n";
			for (int i = 0; i < nodes77.size(); i++) {
				nodes77[i].printNode();
				cout << "\n";
			}
			comp_str = to_text77(nodes77);
			cout << "Decoded: " << comp_str << "\n";
			cout << "---completed---\n";
			break;
		case 3:
			str = "какатанекатанекатата";
			nodes78 = lz78(str);
			cout << "Normal: " << str;
			cout << "\nCompressed:\n";
			for (int i = 0; i < nodes78.size(); i++) {
				nodes78[i].printNode();
				cout << "\n";
			}
			comp_str = to_text78(nodes78);
			cout << "Decoded: " << comp_str << "\n";
			cout << "---completed---\n";
			break;
		case 4:
			cout << "---completed---\n";
			break;
		case 5:
			cout << "---completed---\n";
			break;
		default:
			break;
		}
	}
	cout << "---exit---\n";
}

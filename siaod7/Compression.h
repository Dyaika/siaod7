#ifndef __COMPRESSION_H
#define __COMPRESSION_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>
using namespace std;
class Compression
{
private:
	
public:
	struct node77 {
		int offset = 0;
		int length = 0;
		char next = ' ';
		node77(int offset, int length, char next) {
			this->offset = offset;
			this->length = length;
			this->next = next;
		}
		void printNode() {
			cout << offset << " " << length << " " << next;
		}
	};
	struct node78 {
		int position;
		char next;
		void printNode() {
			cout << position << " " << next;
		}
	};
	//run length encoding / ����������� ���� ����� / ��������� �����������
	string rle(string str);
	
	//LZ77 �����������
	vector<node77> lz77(string str);

	//LZ77 �������������
	string to_text77(vector<node77> nodes);

	//LZ78 �����������
	vector<node78> lz78(string str);

	//LZ78 �������������
	string to_text78(vector<node78> nodes);

	//����
	void test();
};
#endif // !__COMPRESSION_H




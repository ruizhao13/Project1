#include <iostream>  
#include <string>  
#include <fstream>
#include <io.h>  
#include<ctype.h>
using namespace std;
long long TotalNum_chars = 0;
long long TotalNum_lines = 0;
long long TotalNum_words = 0;
void NumOfCharsLinesInFile(string FileLocation)
{//�����ļ���ͳ���ַ������������������������뵽ȫ�ֱ����С����Ե��ʽ��д�������map�ֵ��С�
	int NumberChars = 0;
	int NumberLines = 0;
	int NumberWords = 0;
	char last_char = ' ';
	char current_char;
	bool wordbegin = false;
	string current_word;
	string last_word;
	ifstream infile;
	infile.open(FileLocation, ifstream::in);
	while (infile.good())
	{
		current_char = infile.get();
		if (current_char == -1) {
			break;
		}
		//�ж��Ƿ�Ϊ����
		if (((last_char<127) && (last_char>=0))&&(!isalpha(last_char)) && (!isdigit(last_char)) && (isalpha(current_char)))
		{
			wordbegin = true;
			current_word = current_char;
		}
		else if (wordbegin)
		{
			
			if (  ((last_char<127) && (last_char >= 0)) &&   ((isalpha(current_char)) || (isdigit(current_char)))  )
			{
				current_word = current_word + current_char;
			}
			else
			{
				wordbegin = false;
				//�ж����ڵ�current_word�Ƿ�����word��Ҫ��ǰ�ĸ��ַ�������ĸ
				if (isalpha(current_word[0]))
				{
					if (isalpha(current_word[1]))
					{
						if (isalpha(current_word[2]))
						{
							if (isalpha(current_word[3]))
							{
								//˵��current_word����Ҫ��
								//cout << current_word << endl;
								NumberWords++;
								//EnterMap(last_word, current_word);
								last_word = current_word;
								current_word.clear();
							}
						}
					}
				}

				//�������wordҪ����NumberWords++���������word����last_word=current_word


				//��current_word���
			}
		}




		//�ж��Ƿ�Ϊ���ʽ���
		NumberChars++;
		if (current_char == '\n') {
			NumberLines++;
		}
		last_char = current_char;
	}
	infile.close();
	if (NumberChars != 0) {
		NumberLines++;
	}
	TotalNum_chars += NumberChars;
	TotalNum_lines += NumberLines;
	TotalNum_words += NumberWords;
	//
}
int main(int argc, char *argv[])
{
	//�ݹ�����ļ���  
	NumOfCharsLinesInFile("D:/android-ndk/test.txt");
	cout << TotalNum_chars << endl << TotalNum_words << endl << TotalNum_lines << endl;
	return 0;
}
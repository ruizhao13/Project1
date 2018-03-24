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
{//读入文件，统计字符数、行数、单词数，并加入到全局变量中。并对单词进行处理，加入map字典中。
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
		//判断是否为单词
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
				//判断现在的current_word是否满足word的要求：前四个字符都是字母
				if (isalpha(current_word[0]))
				{
					if (isalpha(current_word[1]))
					{
						if (isalpha(current_word[2]))
						{
							if (isalpha(current_word[3]))
							{
								//说明current_word满足要求
								//cout << current_word << endl;
								NumberWords++;
								//EnterMap(last_word, current_word);
								last_word = current_word;
								current_word.clear();
							}
						}
					}
				}

				//如果满足word要求，则将NumberWords++，并处理该word，并last_word=current_word


				//将current_word清空
			}
		}




		//判断是否为单词结束
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
	//递归遍历文件夹  
	NumOfCharsLinesInFile("D:/android-ndk/test.txt");
	cout << TotalNum_chars << endl << TotalNum_words << endl << TotalNum_lines << endl;
	return 0;
}
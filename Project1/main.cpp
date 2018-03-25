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
		if (current_char < -1 || current_char>255)
		{
			current_char = ' ';
		}
		//判断是否为单词
		if ((!isalpha(last_char)) && (!isdigit(last_char)) && (isalpha(current_char)))
		{
			wordbegin = true;
			current_word = current_char;
		}
		else if (wordbegin)
		{
			if ((isalpha(current_char)) || (isdigit(current_char)))
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


//深度优先递归遍历当前目录下文件夹和文件及子文件夹和文件  
void DfsFolder(string path, int layer)
{
	_finddata_t file_info;
	string current_path = path + "/*.*"; //也可以用/*来匹配所有  
	intptr_t handle = _findfirst(current_path.c_str(), &file_info);
	//返回值为-1则查找失败  
	if (-1 == handle)
	{
		cout << "cannot match the path" << endl;
		return;
	}

	do
	{
		//判断是否子目录  
		if (file_info.attrib == _A_SUBDIR)
		{
			//递归遍历子目录  

			int layer_tmp = layer;
			if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)  //.是当前目录，..是上层目录，必须排除掉这两种情况  
				DfsFolder(path + '/' + file_info.name, layer_tmp + 1); //再windows下可以用\\转义分隔符，不推荐  
		}
		else
		{
			//打印记号反映出深度层次  
			//for (int i = 0; i<layer; i++)
			//	cout << "--";
			//cout << file_info.name << endl;
			string filename = file_info.name;
			string suffixStr = filename.substr(filename.find_last_of('.') + 1);//获取文件后缀
			NumOfCharsLinesInFile(path + '/' + file_info.name);
		}
	} while (!_findnext(handle, &file_info));  //返回0则遍历完  
											   //关闭文件句柄  
	_findclose(handle);
}

int main(int argc, char *argv[])
{
	//递归遍历文件夹  
	DfsFolder("D:/android-ndk", 0);
	//递归遍历文件夹结束
	cout << "characters: " << TotalNum_chars << endl;
	cout << "words: " << TotalNum_words << endl;
	cout << "lines: " << TotalNum_lines << endl; 
	return 0;
}
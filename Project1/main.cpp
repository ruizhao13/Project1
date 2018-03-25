#include <iostream>  
#include <string>  
#include <fstream>
#include <io.h>  
#include<ctype.h>
#include<map>
#include <algorithm>
#include <unordered_map>
using namespace std;
long long TotalNum_chars = 0;
long long TotalNum_lines = 0;
long long TotalNum_words = 0;
struct my_word
{
	string sort_word = "zzzzzzzzzzzzzzzzzz";
	size_t appear_count = 0;
};

my_word ten_word[11];
struct my_phrase
{
	string sort_phrase = "zzzzzzzzzzzzzzzzzz";
	size_t appear_count = 0;
};
unordered_map<string, my_word>word_count;
unordered_map<string, my_phrase>phrase_count;

string transform_word(string raw_word)
{
	int len = raw_word.length();
	string simple_word;
	string temp_word = raw_word;
	transform(temp_word.begin(), temp_word.end(), temp_word.begin(), ::tolower);
	bool is_start = false;
	for (int i = len - 1; i >= 0; i--)
	{
		if (isalpha(temp_word[i]))
		{
			is_start = true;
			simple_word = temp_word.substr(0, i + 1);
			break;
		}
	}
	return simple_word;
}

bool if_update(string new_word, string present_wrod)
{
	if (new_word < present_wrod)
	{
		return true;
	}
	else return false;

}

void EnterMap(string last_word, string current_word)
{
	string simple_last_word;
	string simple_current_word;
	simple_last_word = transform_word(last_word);
	simple_current_word = transform_word(current_word);
	//此处可以优化，减少查找map的次数
	//
	word_count[simple_current_word].appear_count++;
	if (if_update(current_word, word_count[simple_current_word].sort_word))
	{
		word_count[simple_current_word].sort_word = current_word;
	}


	//phrase这里有问题，没有考虑最后的输出字典序最小的原型
	string simple_phrase = simple_last_word + '_' + simple_current_word;
	string raw_phrase = last_word + '_' + current_word;
	phrase_count[simple_phrase].appear_count++;
	if (if_update(raw_phrase, phrase_count[simple_current_word].sort_phrase))
	{
		phrase_count[simple_current_word].sort_phrase = raw_phrase;
	}
}

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
								EnterMap(last_word, current_word);
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

bool compare(my_word a, my_word b)
{
	return a.appear_count>b.appear_count;   //升序排列
}

void Getten_word() {

	my_word temporary_word;
	for (const auto &w : word_count)
	{
		ten_word[10] = w.second;
		for (int i = 0; i <= 9; i++)
		{
			if (ten_word[i].appear_count < ten_word[i + 1].appear_count)
			{
				temporary_word = ten_word[i];
				ten_word[i] = ten_word[i + 1];
				ten_word[i + 1] = temporary_word;
			}
		}
	}
	sort(ten_word, ten_word + 10, compare);
}

int main(int argc, char *argv[])
{
	//递归遍历文件夹  
	DfsFolder("D:/android-ndk/test.txt", 0);
	//递归遍历文件夹结束
	cout << "characters: " << TotalNum_chars << endl;
	cout << "words: " << TotalNum_words << endl;
	cout << "lines: " << TotalNum_lines << endl;
	Getten_word();
	for (int i = 0; i < 10; i++)
	{
		cout << ten_word[i].sort_word << "  " << ten_word[i].appear_count << endl;

	}

	return 0;
}
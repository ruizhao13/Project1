#include <iostream>  
#include <string>  
#include <fstream>
#include <io.h>  
#include<ctype.h>
#include <algorithm>
#include <unordered_map>
#include <time.h>
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

my_phrase ten_phrase[11];
unordered_map<string, my_word>word_count;
unordered_map<string, size_t>phrase_count;

string transform_word(string raw_word)
{
	size_t len = raw_word.length();
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

void EnterMap(string last_word, string current_word)
{
	string simple_last_word;
	string simple_current_word;	
	size_t len = last_word.length();
	string temp_word = last_word;
	transform(temp_word.begin(), temp_word.end(), temp_word.begin(), ::tolower);
	bool is_start = false;
	for (size_t i = len - 1; i >= 0; i--)
	{
		if (isalpha(temp_word[i]))
		{
			is_start = true;
			simple_last_word = temp_word.substr(0, i + 1);
			break;
		}
	}
	len = current_word.length();
	temp_word = current_word;
	transform(temp_word.begin(), temp_word.end(), temp_word.begin(), ::tolower);
	is_start = false;
	for (size_t i = len - 1; i >= 0; i--)
	{
		if (isalpha(temp_word[i]))
		{
			is_start = true;
			simple_current_word = temp_word.substr(0, i + 1);
			break;
		}
	}
	unordered_map<string, my_word> ::iterator got = word_count.find(simple_current_word);
	if (got == word_count.end())
	{
		word_count.insert({ simple_current_word,{current_word,1} });
	}
	else
	{
		got->second.appear_count++;
		if (current_word<got->second.sort_word)
			{
				got->second.sort_word = current_word;
			}
	}

	string simple_phrase = simple_last_word + '_' + simple_current_word;
	phrase_count[simple_phrase]++;
	
}


void NumOfCharsLinesInFile(string FileLocation)
{//Read the file, count the number of characters, lines, and words, and add it to the global variable. The word is processed and added to the map dictionary.
	//int NumberChars = 0;
	int NumberLines = 1;
	int NumberWords = 0;
	char last_char = ' ';
	char current_char;
	bool wordbegin = false;
	string current_word;
	string last_word;

	size_t sz;
	FILE * fp = fopen(FileLocation.c_str(), "rb");
	fseek(fp, 0L, SEEK_END);
	sz = ftell(fp);
	
	rewind(fp);
	char*buf;
	buf = (char*)malloc(sz * sizeof(char));
	int len = fread(buf, sizeof(char), sz, fp);
	//if (len) {
	//	NumberLines++;
	//}

	for(int i = 0;i<len;i++)
	{
		current_char = buf[i];
		if (current_char == '\n') {
			NumberLines++;
		}
		if (current_char < 32 || current_char>126)
		{
			current_char = ' ';
			TotalNum_chars--;
		}
		//≈–∂œ «∑ÒŒ™µ•¥ 
		if ((!isalpha(last_char)) && (!isdigit(last_char)) && (isalpha(current_char)))
		{
			wordbegin = true;
			current_word = current_char;
		}
		else if (wordbegin)  
		{
			if ((isalpha(current_char)) || (isdigit(current_char)))
			{
				//current_word.push_back(current_char);
				current_word.push_back(current_char);
				if (i == len-1) {
					goto panduan;
				}
			}
			else
			{
panduan:				wordbegin = false;
				//Determines whether the current current word meets the word requirement: the first four characters are all letters
				if (isalpha(current_word[1]) && isalpha(current_word[2]) && isalpha(current_word[3]))
				{
					
					//that current_word meets the requirements
					NumberWords++;
					EnterMap(last_word, current_word);
					last_word = current_word;  //NumberWords++£¨word£¨last_word=current_word
					current_word.clear();   
					
				}				
			}
		}		
		last_char = current_char;
	}

	free(buf);
		
	
	TotalNum_chars += sz;
	TotalNum_lines += NumberLines;
	TotalNum_words += NumberWords;
	fclose(fp);
	fp = NULL;
}
  
int DfsFolder(string path, int layer)
{
	_finddata_t file_info;
	string current_path = path + "/*.*"; 
	intptr_t handle = _findfirst(current_path.c_str(), &file_info);
	if (-1 == handle)
	{
		cout << "cannot match the path" << endl;
		return 1;
	}

	do
	{
		//To determine whether the subdirectory
		if (file_info.attrib == _A_SUBDIR)
		{
			//Recursively traversing subdirectories

			int layer_tmp = layer;
			if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)  //. is the current directory, .. is the upper directory and these two conditions must be eliminated  
				DfsFolder(path + '/' + file_info.name, layer_tmp + 1); //  Can use \\ escape separator in windows, not recommended
		}
		else
		{
			string filename = file_info.name;
			string suffixStr = filename.substr(filename.find_last_of('.') + 1);//Get the file suffix
			NumOfCharsLinesInFile(path + '/' + file_info.name);
		}
	} while (!_findnext(handle, &file_info));  //ended if return 0  
	_findclose(handle);
	return 0;
}

bool compare(my_word a, my_word b)
{
	return a.appear_count>b.appear_count;   //…˝–Ú≈≈¡–
}

bool phrase_compare(my_phrase a, my_phrase b)
{
	return a.appear_count>b.appear_count;   //…˝–Ú≈≈¡–
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

void Getten_phrase()
{
	my_phrase temporary_phrase;
	for (const auto &w : phrase_count)
	{
		ten_phrase[10].appear_count = w.second;
		ten_phrase[10].sort_phrase = w.first;
		for (int i = 0; i <= 9; i++)
		{
			if (ten_phrase[i].appear_count < ten_phrase[i + 1].appear_count)
			{
				temporary_phrase = ten_phrase[i];
				ten_phrase[i] = ten_phrase[i + 1];
				ten_phrase[i + 1] = temporary_phrase;
			}
		}
	}
	sort(ten_phrase, ten_phrase + 10, phrase_compare);
}

int main(int argc, char *argv[])
{
	clock_t tStart = clock();  
	int state = DfsFolder(argv[1], 0);
	if (state)
	{
		return 0;
	}
	cout << "char_number :" << TotalNum_chars << endl;
	cout << "line_number :" << TotalNum_lines << endl; 
	cout << "word_number :" << TotalNum_words << endl;
	Getten_word();
	cout <<endl<< "the top ten frequency of word : " << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << ten_word[i].sort_word << "  " << ten_word[i].appear_count << endl;
		
	}
	Getten_phrase();
	cout <<"\n\n"<< "the top ten frequency of phrase :" << endl;
	for (int i = 0; i < 10; i++)
	{
		string phrase_now = ten_phrase[i].sort_phrase;
		string temp1, temp2;
		int x = phrase_now.length();
		int k;
		for (k = 0; k < x; k++) {
			if (phrase_now[k] == '_')break;
			
		}
		temp1 = phrase_now.substr(0, k);
		temp2 = phrase_now.substr(k + 1, x - k - 1);
		string xx = phrase_now.substr(0, k);
		cout << word_count[phrase_now.substr(0, k)].sort_word << ' ' << word_count[phrase_now.substr(k + 1, x - k - 1)].sort_word <<" "<< ten_phrase[i].appear_count << endl;
	}
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	return 0;
}
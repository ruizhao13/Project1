#include <iostream>  
#include <string>  
#include <fstream>
#include <io.h>  
using namespace std;
long long TotalNum_chars = 0;
long long TotalNum_lines = 0;
void NumOfCharsLinesInFile(string FileLocation)
{
	//ifstream inMyStream(FileLocation);
	int NumberChars = 0;
	int NumberLines = 0;
	char cc;
	ifstream infile;
	infile.open(FileLocation, ifstream::in);
	while (infile.good())
	{
		cc = infile.get();
		if (cc == -1) {
			break;
		}
		NumberChars++;
		if (cc == '\n') {
			NumberLines++;
		}
	}
	infile.close();
	if (NumberChars != 0) {
		NumberLines++;
	}
	TotalNum_chars += NumberChars;
	TotalNum_lines += NumberLines;
	return;
}


//������ȵݹ������ǰĿ¼���ļ��к��ļ������ļ��к��ļ�  
void DfsFolder(string path, int layer)
{
	_finddata_t file_info;
	string current_path = path + "/*.*"; //Ҳ������/*��ƥ������  
	intptr_t handle = _findfirst(current_path.c_str(), &file_info);
	//����ֵΪ-1�����ʧ��  
	if (-1 == handle)
	{
		cout << "cannot match the path" << endl;
		return;
	}

	do
	{
		//�ж��Ƿ���Ŀ¼  
		if (file_info.attrib == _A_SUBDIR)
		{
			//�ݹ������Ŀ¼  

			int layer_tmp = layer;
			if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)  //.�ǵ�ǰĿ¼��..���ϲ�Ŀ¼�������ų������������  
				DfsFolder(path + '/' + file_info.name, layer_tmp + 1); //��windows�¿�����\\ת��ָ��������Ƽ�  
		}
		else
		{
			//��ӡ�Ǻŷ�ӳ����Ȳ��  
			//for (int i = 0; i<layer; i++)
			//	cout << "--";
			//cout << file_info.name << endl;
			string filename = file_info.name;
			string suffixStr = filename.substr(filename.find_last_of('.') + 1);//��ȡ�ļ���׺
			NumOfCharsLinesInFile(path + '/' + file_info.name);
		}
	} while (!_findnext(handle, &file_info));  //����0�������  
											   //�ر��ļ����  
	_findclose(handle);
}

int main(int argc, char *argv[])
{
	//�ݹ�����ļ���  
	DfsFolder("D:/android-ndk", 0);
	cout << TotalNum_chars << endl << TotalNum_lines << endl;
	return 0;
}
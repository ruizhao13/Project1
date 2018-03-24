#include <iostream>  
#include <string>  
#include <io.h>  
using namespace std;

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
			//��ӡ�Ǻŷ�ӳ����Ȳ��  
			for (int i = 0; i<layer; i++)
				cout << "--";
			cout << file_info.name << endl;
			int layer_tmp = layer;
			if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)  //.�ǵ�ǰĿ¼��..���ϲ�Ŀ¼�������ų������������  
				DfsFolder(path + '/' + file_info.name, layer_tmp + 1); //��windows�¿�����\\ת��ָ��������Ƽ�  
		}
		else
		{
			//��ӡ�Ǻŷ�ӳ����Ȳ��  
			for (int i = 0; i<layer; i++)
				cout << "--";
			cout << file_info.name << endl;

		}
	} while (!_findnext(handle, &file_info));  //����0�������  
											   //�ر��ļ����  
	_findclose(handle);
}

int main(int argc, char *argv[])
{
	//�ݹ�����ļ���  
	DfsFolder("D:/android-ndk", 0);
	return 0;
}
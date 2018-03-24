#include <iostream>  
#include <string>  
#include <io.h>  
using namespace std;

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
			//打印记号反映出深度层次  
			for (int i = 0; i<layer; i++)
				cout << "--";
			cout << file_info.name << endl;
			int layer_tmp = layer;
			if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0)  //.是当前目录，..是上层目录，必须排除掉这两种情况  
				DfsFolder(path + '/' + file_info.name, layer_tmp + 1); //再windows下可以用\\转义分隔符，不推荐  
		}
		else
		{
			//打印记号反映出深度层次  
			for (int i = 0; i<layer; i++)
				cout << "--";
			cout << file_info.name << endl;

		}
	} while (!_findnext(handle, &file_info));  //返回0则遍历完  
											   //关闭文件句柄  
	_findclose(handle);
}

int main(int argc, char *argv[])
{
	//递归遍历文件夹  
	DfsFolder("D:/android-ndk", 0);
	return 0;
}
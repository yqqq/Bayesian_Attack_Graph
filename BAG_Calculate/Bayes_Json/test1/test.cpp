/*
*进行json数据读取测试，并进行测试获取json数据元素获取
*
*/


#include<iostream>
#include<string.h>
#include "cJSON.h"
#include "cJSON.c"
using namespace std;

/*
//定义json数据结构体
typedef struct cJSON {
    struct cJSON *next,*prev;   // 数组 对象数据中用到
    struct cJSON *child;        // 数组 和对象中指向子数组对象或值

    int type;           // 元素的类型，如是对象还是数组

    char *valuestring;          // 如果是字符串
    int valueint;               // 如果是数值
    double valuedouble;         // 如果类型是cJSON_Number

    char *string;               // The item's name string, if this item is the child of, or is in the list of subitems of an object.
} cJSON;
*/

//json数据解析
void doit(char *text)
{
	char *out;cJSON *json;

	json=cJSON_Parse(text);
	if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
	else
	{
		out=cJSON_Print(json);

		//获取json数据中的元素
		cJSON *name = cJSON_GetObjectItem(json,"name");
        //string na = cJSON_GetObjectItem(name,"name");
        //cout<<na<<endl;
        string str=name->valuestring;
		cout<<str<<endl;
        cJSON *format = cJSON_GetObjectItem(json,"format");
        int framerate = cJSON_GetObjectItem(format,"frame rate")->valueint;
   		//int width = cJSON_GetObjectItem(format,"width")->valueint;

        cout<<framerate<<endl;
        cout<<name->next->valuestring<<endl;

		cJSON_Delete(json);//delete
		//int width = cJSON_GetObjectItem(format,"width")->valueint;
        //cout<<width<<endl;
		printf("%s\n",out);
		free(out);
	}
}


//读取json文件
void dofile(char *filename)
{
	FILE *f=fopen(filename,"rb");
	fseek(f,0,SEEK_END);//指针移动到文件尾
	long len=ftell(f);//获取当前文件读写位置,得到文件长度
	fseek(f,0,SEEK_SET);//文件指针移动到文件头
	char *data=(char*)malloc(len+1);
	fread(data,1,len,f);
	fclose(f);
    //printf("%s\n",data);

	//data含有json数据
	doit(data);
	free(data);
}


int main()
{
    dofile("test");
}

/*
*解析json数据，获取用于生成Bayes_MATLAB使用的LCPD
*
*/


#include<iostream>
#include<string.h>
#include "cJSON.h"
#include "cJSON.c"
using namespace std;

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
		int name_count = cJSON_GetArraySize(name);
		for ( int i =0 ; i < name_count ; i++)
        {
            cJSON *node = cJSON_GetArrayItem(name,i);//获取节点信息
            //int node_count = cJSON_GetArraySize(node);

            //前驱节点
            cJSON *attr = cJSON_GetObjectItem(node,"pre");
            int pre_count = cJSON_GetArraySize(attr);//获取前驱节点

            for ( int j = 0; j < pre_count ; j++)
            {
                cJSON *pre = cJSON_GetArrayItem(attr,j);
                cout<<pre->valuestring<<endl;
                //cout<<11111111111111111<<endl;
            }

            //获取LCPD

            //T
            cJSON *probability_T = cJSON_GetObjectItem(node,"T");
            int pro_count_T = cJSON_GetArraySize(probability_T);

            for (int k =0 ; k < pro_count_T ; k++)
            {
                cJSON *pro = cJSON_GetArrayItem(probability_T,k);
                cout<<pro->valuedouble<<endl;
            }

            //F
            cJSON *probability_F = cJSON_GetObjectItem(node,"F");
            int pro_count_F= cJSON_GetArraySize(probability_F);

            for (int k =0 ; k < pro_count_F ; k++)
            {
                cJSON *pro = cJSON_GetArrayItem(probability_F,k);
                cout<<pro->valuedouble<<endl;
            }
        }

		cJSON_Delete(json);//delete
		//int width = cJSON_GetObjectItem(format,"width")->valueint;
        //cout<<width<<endl;
        cout<<endl;
		//printf("%s\n",out);
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

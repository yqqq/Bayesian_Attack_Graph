#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void change_to_string()
{
	int a=115455;
	char c[7];
	itoa(a,c,10);
	printf("%s",c);
}

int change_to_2sec(int a,int b,int c,int d)
{
	printf("Calculating all probability\n\n");
	FILE *fp;					// 声明一个文件流类型的变量，FILE 为 stdio.h 里定义的
	fp=fopen("one_zero.txt","w");		//用 fopen 函数打开文件，第一个参数表示文件名，若不是当前
	for(d = 0;d<c;d++)
	{
		//int set[10] = {};
		for (int i = 0,b = a; b > 0; i++,b--)
			//b=3;
		{
			//int set[10] = {0};
			//set[i] = (d >> (b - 1)) & 1;
			if (fp!=NULL)				// 打开成功
				//printf ("set: %d\n",set[i]);
				fprintf (fp,"%d", (d >> (b - 1)) & 1);
			//system("pause");
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	printf("Done in one_zero.txt\n\n");
    system("pause");
	return 1;
}

int main()
{
    //change_to_string();
	int a,b,c;
	int d = 0;
    FILE *fp;
	printf("Opening pre_number.txt\n\n");
	if(fp = fopen("pre_number.txt","r"))
	{
		fscanf(fp,"%d",&b);
		printf("Successfuly opened pre_number.txt\n\n");
	}
	else
		printf("Open pre_number.txt Error!\n\n");
	//printf("input size: \n");            //size->b
    //scanf("%d",&b);
    c = pow(2.0,b);
	//int set[100][b] = {0};
	a =b;
    //printf("%d\n",c);
    //printf("input a num: \n");
    //scanf("%d", &a);
    change_to_2sec(a,b,c,d);
}	
	

/*
{
    int a, b;
    printf("input a num: \n");
    scanf("%d", &a);
    printf ("\n\n2: ");
    for (b = 16; b > 0; b--)  printf ("%d", (a >> (b - 1)) & 1);
    system("pause");
	return 1;
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>//gcc -lm to build
#include <string.h>

/**
*Creating the one_zreo.txt
*useing the txt to calculate the probality
*
*eg.
*000
*001
*010
*011
*100
*101
*110
*111
*/

/*
void Reverse(string str)
{
    reverse(str.begin(),str.end());
    //cout<<str<<endl;;
}
*/

int change_to_2sec(int LCPD_Pre_Number)
{
    int d;//just for
    int LCPD_Probability_Count=pow(2,LCPD_Pre_Number);//the count of the LCPD

	printf("Creating the one=_zero.txt\n\n");

	//read and write the 0-1 matrix into the one_zero.txt
	FILE *fp;
	fp=fopen("one_zero.txt","w");
	for(d = 0;d<LCPD_Probability_Count;d++)
	{

		for (int i = 0; LCPD_Pre_Number > 0; i++,LCPD_Pre_Number--)
		{

			if (fp!=NULL)	//open successfully
			{
                //string str;
                //char str;//=(LCPD_Probability_Count >> (LCPD_Pre_Number - 1)) & 1;
                //sprintf(str,"%d",(LCPD_Probability_Count >> (LCPD_Pre_Number - 1)) & 1);
                //fprintf (fp,"%d", reverse(str.begin(),str.end()));
                fprintf(fp,"%d",(LCPD_Probability_Count >> (LCPD_Pre_Number - 1)) & 1);
                //printf("%s\n",str);

			}

		}
		fprintf(fp,"\n");
	}
	fclose(fp);

	printf("Done in one_zero.txt\n\n");

	return 1;
}

int main()
{
	int LCPD_Pre_Number;


	/**reading file
	*get the pre number of the node
	*/

    FILE *fp;
	printf("Opening pre_number.txt\n\n");
	if(fp = fopen("pre_number.txt","r"))
	{
		fscanf(fp,"%d",&LCPD_Pre_Number);
		printf("Successfuly opened pre_number.txt\n\n");
		fclose(fp);
	}
	else
		printf("Open pre_number.txt Error!\n\n");

    change_to_2sec(LCPD_Pre_Number);
}

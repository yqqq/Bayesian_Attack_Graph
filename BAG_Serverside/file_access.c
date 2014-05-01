#include<stdio.h>
#include<unistd.h>

int check_file_access(char *bag_filename){
	FILE *fp;
	time_t log_time;
	if((access(bag_filename,0))!=-1)
	{
		if((fp=fopen("/home/lovingmage/Desktop/Graph_Error.log","a"))>=0)
        	{
            		t=time(0);
            		fprintf(fp,"%s ->Required file not exist,Please check your file path.",asctime(localtime(&t)));
            		fclose(fp);
            	}		
	}
	else if((access(bag_filename,2))!=-1)
	{
		if((fp=fopen("/home/lovingmage/Desktop/Graph_Error.log","a"))>=0)
        	{
            		t=time(0);
            		fprintf(fp,"%s ->Required FILE Need more prilvage(WRITE PERMISSIONS).",asctime(localtime(&t)));
            		fclose(fp);
            	}		
	}
        else if((access(bag_filename,4))!=-1)
	{
		if((fp=fopen("/home/lovingmage/Desktop/Graph_Error.log","a"))>=0)
        	{
            		t=time(0);
            		fprintf(fp,"%s ->Required FILE Need more prilvage(READ PERMISSIONS).",asctime(localtime(&t)));
            		fclose(fp);
            	}		
	}
	return 0;
}

int main(){
	char *filename="'/home/lovingmage/Desktop/Graph_Attack/robot.txt";
	check_file_access(filename);
	return 0;
}

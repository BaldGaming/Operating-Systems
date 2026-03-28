#include<stdio.h>
#include<stdlib.h>
#define MAXLINE 100
void Error(char* msg){fprintf(stderr, "Error:%s\n", msg);  exit(1);}

int main(int argc, char* argv[]){
	FILE *in,*out;
	char buff[MAXLINE];	
	if(argc>3)	Error("Bad number of parameters\n");
	if(argc==3){
		if((out=fopen(argv[2],"w"))==NULL)	Error("Can't open output file\n");
	}
	else
		out=stdout;
	if(argc>1){
		if((in=fopen(argv[1],"r"))==NULL)	Error("Can't open input file\n");
	}
	else
		in=stdin;
	while(fgets(buff, MAXLINE, in)!=NULL)
		fputs(buff, out);
	if(out!=stdout)
		fclose(out);
	if(in!=stdin)
		fclose(in);
	return 0;
}

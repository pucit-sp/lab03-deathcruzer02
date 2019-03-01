#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void mygrep(FILE*, char*);

void myreplace(FILE *fp, char *find, char *replace);

char *replaceWord(const char *s, const char *oldW, const char *newW);

int  main(int argc,char *argv[])
{
	int behaviour;
	FILE *fp;
	char *filename=argv[1];
	char *find=argv[2];
	char *replace;

	if(argc < 4)
	{
		behaviour = 1;
	}
	else if(argc < 5)
	{
		behaviour = 2;
		replace = argv[3];
	}
	else
	{
		behaviour = -1;
	}

	fp=fopen(filename,"rt");
	if(behaviour == 1)
	{
		mygrep(fp,find);
	}
	else if (behaviour == 2)
	{
		myreplace(fp,find,replace);
	}
	
	fclose(fp);		
	return 0;
}


void mygrep(FILE *fp,char *find)
{
	char c1[500];

	while(!feof(fp))
	{
		fgets(c1,500,fp);
		if(strstr(c1,find))
		  printf("%s\n",c1);
	}
}

void myreplace(FILE *fp,char *find, char *replace)
{
	char c[500];
	while(!feof(fp))
	{
		fgets(c,500,fp);
		if(strstr(c,find))
		  printf("%s\n",c);
	}
	
	char c2[500];
	char *result=NULL;
	fseek(fp,0,SEEK_SET);
	while (!feof(fp))
	{
		fgets(c2,500,fp);
		if(strstr(c2,find))
		{
			result=replaceWord(c2,find,replace);
			printf("%s\n",result);
			free(result);
			break;	
		}
	}
	
}

char *replaceWord(const char *s, const char *oldWord, const char *newWord) 
{ 
	char *result; 
	int i, cnt = 0; 
	int newWlen = strlen(newWord); 
	int oldWlen = strlen(oldWord); 

	for (i = 0; s[i] != '\0'; i++) 
	{ 
		if (strstr(&s[i], oldWord) == &s[i]) 
		{ 
			cnt++;  
			i += oldWlen - 1; 
		} 
	} 

	result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1); 
	int counter=0;
	i = 0; 
	while (*s) 
	{
		if (strstr(s, oldWord) == s && counter<=0) 
		{ 
			strcpy(&result[i], newWord);
			i += newWlen; 
			s += oldWlen;
			counter++;
		} 
		else
			result[i++] = *s++; 
	} 

	result[i] = '\0'; 
	return result; 
}

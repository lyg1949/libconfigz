#include "configz.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER 1024

///去掉两边的空格
void trim(char * buf)
{
	if(buf == NULL)
	{
		return;
	}
	int i = strlen(buf)-1;
	while(isspace(buf[i]) && i >= 0)
	{
		i--;
	}
	buf[i+1] = '\0';
	char * t = buf;
	while(isspace(*t))
	{
		t++;
	}
	if(*t == '\0')
	{
		*buf = '\0';
	}
	else
	{
		strcpy(buf,t);
	}
}

///判断是否为注释行，会对line进行修改（不会改变有效内容）
int isCommentLine(char * line)
{
	trim(line);
	
	if(line == NULL || strlen(line) == 0 || line[0] == '#')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

///判断是否为Label行，会对line进行修改（不会改变有效内容）
int isLabel(char * line)
{
	if(strlen(line) < 2)
	{
		return 0;
	}
	char * content = strtok(line,"#");
	strcpy(line,content);
	if(line == NULL)
	{
		return 0;
	}
	trim(line);
	int len =strlen(line); 
	if(len < 2)
	{
		return 0;
	}
	
	if(line[0] == '[' && line[len-1] == ']')
	{
		return 1;
	}
	else
	{
		
		return 0;
	}
}

///从打开文件中的当前位置开始读取key的对应value，找到或者文件结束或者读到下一个Label行则返回
int readKV(FILE * file, const char * key, char * value)
{
	char buffer[BUFFER];
	memset(buffer,0,BUFFER);
	int key_len = strlen(key);
	while(fgets(buffer,BUFFER,file) != NULL)
	{
		if(isCommentLine(buffer))
		{
			continue;
		}
		if(isLabel(buffer))
		{
			break;
		}
		char * t_key = strtok(buffer,"=");
		if(t_key == NULL)
		{
			continue;
		}
		trim(t_key);
		if(strlen(t_key) != key_len || strcmp(t_key,key) !=0)
		{
			continue;
		}
		char* t_value = strtok(NULL,"#");
		if(t_value == NULL)
		{
			fclose(file);
			return -1;
		}
		trim(t_value);
		if(strlen(t_value) == 0)
		{
			fclose(file);
			return -1;
		}
		strcpy(value,t_value);
		fclose(file);
		return 0;
	}
	fclose(file);
	return -1;
}

int configz_readKV(const char * configfile, const char * key, char * value)
{
	FILE * file =fopen(configfile,"r");
	if(file == NULL)
	{
		return -1;
	}
	return readKV(file, key, value);
}

int configz_countLabel(const char * configfile,const char * label)
{
	FILE * file =fopen(configfile,"r");
	if(file == NULL)
	{
		return -1;
	}
	char buffer[BUFFER];
	memset(buffer,0,BUFFER);
	int label_len = strlen(label);
	int label_num = 0;
	while(fgets(buffer,BUFFER,file) != NULL)
	{
		if(isCommentLine(buffer))
		{
			continue;
		}
		if(isLabel(buffer) && strlen(buffer) == label_len+2 && strncmp(buffer+1,label,label_len) ==0)
		{
			label_num++;
		}
	}
	fclose(file);
	return label_num;
}
int configz_readLKV(const char * configfile, const char * label, const char * key, char * value, int num)
{
	if(num < 1)
	{
		return -1;
	}
	FILE * file =fopen(configfile,"r");
	if(file == NULL)
	{
		return -1;
	}
	char buffer[BUFFER];
	memset(buffer,0,BUFFER);
	int label_len = strlen(label);
	int label_num = 0;
	while(fgets(buffer,BUFFER,file) != NULL)
	{
		if(isCommentLine(buffer))
		{
			continue;
		}
		if(isLabel(buffer) && strlen(buffer) == label_len+2 && strncmp(buffer+1,label,label_len) ==0)
		{
			label_num++;
			if(label_num == num)
			{
				break;
			}
		}
	}
	if(label_num != num)
	{
		fclose(file);
		return -1;
	}
	return readKV(file, key, value);
}

int configz_readSLKV(const char * configfile, const char * label, const char * key, char * value)
{
	return configz_readLKV(configfile, label, key, value, 1);
}

/*int main()
{
	char value[100];
	memset(value,0 ,100);
	printf("%d\n",configz_countLabel("log.ini","base"));
	printf("%d\n",configz_countLabel("log.ini","tcp"));
	printf("%d\n",configz_countLabel("log.ini","udp"));
	if(configz_readSLKV("log.ini","base","test",value) ==0)
	{
		printf("base   test = %s\n",value);
	}
	if(configz_readLKV("log.ini","base","test",value,2) ==0)
	{
		printf("base   test2 = %s\n",value);
	}
	if(configz_readLKV("log.ini","base","test",value,3) ==0)
	{
		printf("base   test3 = %s\n",value);
	}
	if(configz_readLKV("log.ini","base","test",value,4) ==0)
	{
		printf("base   test4 = %s\n",value);
	}
	return 0;
}
*/

#include <stdio.h>
#include <string.h>
#include<stdlib.h>

void StrInsert(char *str, char *str_ins);
char* substring(char* ch, int pos, int length);
void character_Append(char *str, char ch);

unsigned int flag_3 = 0;//出现zhengxing zhu() 的g字母丢失，临时解决办法
unsigned int flag_4 = 0;//出现zhengxing zhu()的“ ”空格被保留，临时解决办法
unsigned int flag_switch = 1; //flag_3和flag_4的总开关
int main()
{
	FILE *fp;
	char buff[255];
	char str_temp[255];
	char str[255];
	char* result;
	int i, j;
	unsigned int count = 0, flag_1 = 1,flag_2 = 0;
	fp = fopen("ChineseToPinYin.c", "r");
	remove("PinYinToEnglish.c");	//删除test_1.txt文件
	FILE *fp_1 = fopen("PinYinToEnglish.c", "w+");

	//测试代码
	//char test_1[255] = "return 0;";

	while (!feof(fp))
	{
		memset(buff, 0, sizeof(buff));
		memset(str_temp, 0, sizeof(str_temp));
		fgets(buff, sizeof(buff), fp);
		//测试代码
		//strcpy(buff, test_1);

		for (i = 0; i < strlen(buff); i++)
		{
			if ((buff[i] >= 'A' && buff[i] <= 'Z') || \
				(buff[i] >= 'a' && buff[i] <= 'z') || \
				(buff[i] >= '0' && buff[i] <= '9') || \
				buff[i] == '_' || buff[i] == ' ')
			{
				count++;
				if ((buff[i + 1]<'0') || \
					((buff[i + 1]>'9') && (buff[i + 1]<'A')) || \
					((buff[i + 1]>'Z') && (buff[i + 1]<'_')) || \
					((buff[i + 1]>'_') && (buff[i + 1]<'a')) || \
					(buff[i + 1]>'z'))
				{
					flag_1 = 0;
				}
				if (flag_switch == 1)
				{
					if (buff[i + 1] == ' ')//出现zhengxing zhu() 的g字母丢失，临时解决办法
					{
						flag_3 = 1;
					}
					if (buff[i - 1] == ' ')//出现zhengxing zhu()的“ ”空格被保留，临时解决办法
					{
						flag_4 = 1;
					}
				}

			}
			if ((flag_1 == 0) && (i > 1))
			{
				result = substring(buff, i - count + 1, i);
				memset(str, 0, sizeof(str));
				strcpy(str, result);
				if (strcmp(str, "baohan") == 0)
				{
					strcpy(str, "include");
				}
				if (strcmp(str, "biaozhunshuruchu") == 0)
				{
					strcpy(str, "stdio");
				}
				if (strcmp(str, "tou") == 0)
				{
					strcpy(str, "h");
				}
				if (strcmp(str, "zhengxing") == 0)
				{
					strcpy(str, "int");
				}
				if (strcmp(str, "zhu") == 0)
				{
					strcpy(str, "main");
					flag_switch = 0;
				}
				if (strcmp(str, "geshihuashuchu") == 0)
				{
					strcpy(str, "printf");
				}
				if (strcmp(str, "fanhui") == 0)
				{
					strcpy(str, "return");
				}
				strcat(str_temp, str);
				flag_1 = 1;
				if (flag_switch == 1)
				{
					flag_3 = 0;//出现zhengxing zhu() 的g字母丢失，临时解决办法
					flag_4 = 0;//出现zhengxing zhu()的“ ”空格被保留，临时解决办法
				}
				count = 0;
				//flag_2 = 1;
			}
			if ((buff[i]<'0') || \
				((buff[i]>'9') && (buff[i]<'A')) || \
				((buff[i]>'Z') && (buff[i]<'_')) || \
				((buff[i]>'_') && (buff[i]<'a')) || \
				(buff[i]>'z')
				)
			{
				//str_temp[i] = buff[i];
				character_Append(str_temp, buff[i]);
				//flag_2 = 1;
			}

			
			//写入加个判断如是上次内容则不执行该语句
			if (i==strlen(buff)-1)
			{
				fprintf(fp_1, str_temp);
				flag_2 = 0;
			}
		}
	}
	fclose(fp);
	fclose(fp_1);
	return 0;
}

char* substring(char* ch, int pos, int length)
{
	if (flag_switch == 1)
	{
		if (flag_3 == 1)//出现zhengxing zhu() 的g字母丢失，临时解决办法
		{
			length++;
		}
		if (flag_4 == 1)//出现zhengxing zhu()的“ ”空格被保留，临时解决办法
		{
			pos++;
		}
	}
	char* pch = ch;//定义一个字符指针，指向传递进来的ch地址。
	char* subch = (char*)calloc(sizeof(char), length + 1);//通过calloc来分配一个length长度的字符数组，返回的是字符指针。
	int i;//只有在C99下for循环中才可以声明变量，这里写在外面，提高兼容性。
	pch = pch + pos;//是pch指针指向pos位置。
	for (i = 0; i<(length-pos+1); i++)
	{
		//subch[i] = *(pch);//循环遍历赋值数组。g不能被赋予值过去
		*(subch + i) = *(pch++);
	}
	subch[length] = '\0';//加上字符串结束符。
	return subch;       //返回分配的字符数组地址。
}

void character_Append(char *str, char ch)
{
	int length = strlen(str);
	//	printf("%d\n",length);
	*(str + length) = ch;
	str[length + 2] = '\0';//加上字符串结束符。
}


#include <stdio.h>
#include <string.h>
#include<stdlib.h>

void StrInsert(char *str, char *str_ins);
char* substring(char* ch, int pos, int length);
void character_Append(char *str, char ch);

unsigned int flag_3 = 0;//����zhengxing zhu() ��g��ĸ��ʧ����ʱ����취
unsigned int flag_4 = 0;//����zhengxing zhu()�ġ� ���ո񱻱�������ʱ����취
unsigned int flag_switch = 1; //flag_3��flag_4���ܿ���
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
	remove("PinYinToEnglish.c");	//ɾ��test_1.txt�ļ�
	FILE *fp_1 = fopen("PinYinToEnglish.c", "w+");

	//���Դ���
	//char test_1[255] = "return 0;";

	while (!feof(fp))
	{
		memset(buff, 0, sizeof(buff));
		memset(str_temp, 0, sizeof(str_temp));
		fgets(buff, sizeof(buff), fp);
		//���Դ���
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
					if (buff[i + 1] == ' ')//����zhengxing zhu() ��g��ĸ��ʧ����ʱ����취
					{
						flag_3 = 1;
					}
					if (buff[i - 1] == ' ')//����zhengxing zhu()�ġ� ���ո񱻱�������ʱ����취
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
					flag_3 = 0;//����zhengxing zhu() ��g��ĸ��ʧ����ʱ����취
					flag_4 = 0;//����zhengxing zhu()�ġ� ���ո񱻱�������ʱ����취
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

			
			//д��Ӹ��ж������ϴ�������ִ�и����
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
		if (flag_3 == 1)//����zhengxing zhu() ��g��ĸ��ʧ����ʱ����취
		{
			length++;
		}
		if (flag_4 == 1)//����zhengxing zhu()�ġ� ���ո񱻱�������ʱ����취
		{
			pos++;
		}
	}
	char* pch = ch;//����һ���ַ�ָ�룬ָ�򴫵ݽ�����ch��ַ��
	char* subch = (char*)calloc(sizeof(char), length + 1);//ͨ��calloc������һ��length���ȵ��ַ����飬���ص����ַ�ָ�롣
	int i;//ֻ����C99��forѭ���вſ�����������������д�����棬��߼����ԡ�
	pch = pch + pos;//��pchָ��ָ��posλ�á�
	for (i = 0; i<(length-pos+1); i++)
	{
		//subch[i] = *(pch);//ѭ��������ֵ���顣g���ܱ�����ֵ��ȥ
		*(subch + i) = *(pch++);
	}
	subch[length] = '\0';//�����ַ�����������
	return subch;       //���ط�����ַ������ַ��
}

void character_Append(char *str, char ch)
{
	int length = strlen(str);
	//	printf("%d\n",length);
	*(str + length) = ch;
	str[length + 2] = '\0';//�����ַ�����������
}


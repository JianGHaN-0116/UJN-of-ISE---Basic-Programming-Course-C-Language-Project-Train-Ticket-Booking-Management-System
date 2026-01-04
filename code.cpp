#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STR_LEN 18//定义随机输出的字符串长度。
#define CHAR_MIN '!'
#define CHAR_MAX '~' //定义输出随机字符串每个字符的最大最小值。
int main()
{
    FILE *fp;
    char str[STR_LEN + 1] = {0};
    int i;

    srand(time(NULL));//通过时间函数设置随机数种子，使得每次运行结果随机。
    for(i = 0; i < STR_LEN; i ++)
    {
        str[i] = rand()%(CHAR_MAX-CHAR_MIN + 1) + CHAR_MIN; //生成要求范围内的随机数。
    }
    fp=fopen("code.txt","w");//输出生成的随机数。
    fputs(str,fp);
    fclose(fp);
    return 0;
}
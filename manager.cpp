#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
typedef struct Dtime//时刻
{
    short year;
    short month;
    short day;
    short hour;
    short minute;
}D;
typedef struct train
{
    char terminal[20];
    char sequence[20];
    struct Dtime StartTime;
    float fare;
    int SpareTicketnum;
    struct node *head;
}T;
typedef struct node//乘客
{
    char name[20];
    char IDcard[20];
    int TicketNum;
    struct node *next;
}N;
#define lenT sizeof(T)
int main()
    {
        struct train t[5];
        time_t now_time;
        time(&now_time);
        FILE *fp,*fp1,*fp2,*fpi;
        char dynamic_code[81],account[81];
        char correct[81];
        int count=0;
        printf("欢迎使用火车订票系统！ V2023.2036\n");
        printf("欢迎进入管理员系统，共3122管理员，请输入账号：");
        scanf("%s",account);
        printf("输入动态密码：");
        scanf("%s",dynamic_code);
        fp=fopen("code.txt","r");//动态密码
        fp1=fopen("error recordings.txt","a");//错误日志
        fp2=fopen("information","wb");//信息存储
        fgets(correct,19,fp);
        while(strcmp(dynamic_code,correct)!=0)
        {
            count++;
            if(count==3)
            {
                fputs(account,fp1);
                fputc(' ',fp1);
                fputc(' ',fp1);
                fputs(ctime(&now_time),fp1);
                printf("系统锁定！！！已经将日志保存");
                exit(0);
            }
            printf("请重新输入：");
            scanf("%s",dynamic_code);
        }
        {
            int i;
            for(i=0;i<5;i++)
            {
                printf("No.%d\n",i+1);
                printf("终点站：");
                scanf("%s",t[i].terminal);
                printf("车次：");
                scanf("%s",t[i].sequence);
                printf("发车时间：");
                scanf("%d%d%d%d%d",&t[i].StartTime.year,&t[i].StartTime.month,&t[i].StartTime.day,&t[i].StartTime.hour,&t[i].StartTime.minute);
                printf("车票数：");
                scanf("%d",&t[i].SpareTicketnum);
                printf("票价：");
                scanf("%f",&t[i].fare);
               
                printf("当前车次列车信息保存成功\n");
            }
             fwrite(t,lenT,5,fp2);

        }
        fclose(fp);
        fclose(fp1);
        fclose(fp2);
        return 0; 
    }
//管理员系统，用来写入信息，和客户端用文件链接；

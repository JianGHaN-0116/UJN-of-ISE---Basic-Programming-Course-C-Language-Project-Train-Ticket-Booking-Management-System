//新版 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node//乘客
{
    char name[20];
    char IDcard[20];
    int TicketNum;
    struct node *next;
}N;
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
#define lenN sizeof(N)
#define lenD sizeof(D)
#define lenT sizeof(T)
N *creat()
{
	N *head=(N*)malloc(lenN);
	memset(head->name,0,20);
	memset(head->IDcard,0,20);
	head->next=NULL;
	return head;
}
N *buy(N *head,int ticket,int num)
{
	N *p1,*p2=head;
	p1=(N*)malloc(lenN);
	printf("请输入姓名：");
	scanf("%s",p1->name);
	printf("请输入身份证号：");
	scanf("%s",p1->IDcard);
	p1->TicketNum=num;
	while(p2->next)
	{
		p2=p2->next;
	}
	p2->next=p1;
	p1->next=NULL;
	return head;
}
N *del(N *head,char t[])
{
    N *p,*q=NULL;
    p=head;
    while(strcmp(t,p->IDcard)!=0&&p->next!=NULL)
    {
        q=p;
        p=p->next;
    }
    if(strcmp(t,p->IDcard)==0)
    {
        if(p==head) head=p->next;
        else q->next=p->next;
        free(p);
    }
    printf("退票成功！！！\n"); 
    return head;
}
int list(N *head)
{
    N *p;
    p=head;
    while(p!=NULL)
    {
    	if(strlen(p->name)!=0)
        printf("姓名：%s 身份证号：%s 订票数：%d\n",p->name,p->IDcard,p->TicketNum);
        p=p->next;
    }
    return 1;
}
N *load(N *head,char s[])
{
	
	FILE *fpn;
	fpn=fopen(s,"rb");
	N temp,*p;
	p=head;
	if(fpn!=NULL)
	{
		while(fread(&temp,lenN,1,fpn)!=0)
		{
			N *q;
			q=(N*)malloc(lenN);
			strcpy(q->IDcard,temp.IDcard);
			strcpy(q->name,temp.name);
			q->TicketNum=temp.TicketNum;
			while(p->next!=NULL) p=p->next;
			q->next=NULL; 
			p->next=q;	
		}
	}
	fclose(fpn);
	return head;
}
int main()
{
	FILE *fp1;
    fp1=fopen("information.dat","rb");
    struct train t[5];
    fread(t,sizeof(T),5,fp1);
    for(int j=0;j<5;j++) 
    {
        t[j].head=creat();
		t[j].head=load(t[j].head,t[j].sequence);
	}
	fclose(fp1);
	do
	{
	int op;
	printf("---------------------------------------------------------------------------\n"); 
	for(int k=0;k<5;k++)
	{
		printf("终点站：%s 车次：%s 发车时间：%d.%d.%d %d:%d 票价：%f 余票数：%d\n",t[k].terminal,t[k].sequence,t[k].StartTime.year,t[k].StartTime.month,t[k].StartTime.day,t[k].StartTime.hour,t[k].StartTime.minute,t[k].fare,t[k].SpareTicketnum);
	}
	printf("---------------------------------------------------------------------------\n"); 
    printf("欢迎使用火车订票系统！ V2023.2036\n");
	printf("查询线路请按1，订票功能请按2，退票功能请按3，其他功能请按4，退出系统请按5：");
	scanf("%d",&op);
	if(op==1)
	{
		int op1;
        printf("终点站查询请按1，车次查询请按2：");
        scanf("%d",&op1);
        if(op1==1)
        {
        	int i;
            char tar[20];
            printf("请输入终点站：");
            scanf("%s",tar);
               for(i=0;i<5;i++)
               {
                   if(strcmp(t[i].terminal,tar)==0) printf("终点站：%s\n车次：%s\n发车时间：%d.%d.%d.%d:%d\n票价：%f\n余票数：%d\n",t[i].terminal,t[i].sequence,t[i].StartTime.year,t[i].StartTime.month,t[i].StartTime.day,t[i].StartTime.hour,t[i].StartTime.minute,t[i].fare,t[i].SpareTicketnum);
                    break;
               }
               if(i==5) printf("没有找到该车次，请确认后再输入！\n");
        }
        if(op1==2)
        {
            char tar[20];
            int i;
            printf("请输入车次：");
            scanf("%s",tar);
            for(i=0;i<5;i++)
            {
                 if(strcmp(t[i].sequence,tar)==0) 
                 {
                    printf("终点站：%s\n车次：%s\n发车时间：%d.%d.%d %d:%d\n票价：%f\n余票数：%d\n",t[i].terminal,t[i].sequence,t[i].StartTime.year,t[i].StartTime.month,t[i].StartTime.day,t[i].StartTime.hour,t[i].StartTime.minute,t[i].fare,t[i].SpareTicketnum);
                    break;
                 }
            }
            if(i==5) printf("没有找到该车次，请确认后再输入！\n");
        }
	}
	if(op==2)
	{
		char tar[20];
        int num;
        printf("请输入车次和票数：");
        scanf("%s %d",tar,&num);
        int i;
        for(i=0;i<5;i++)
        {
            if(strcmp(t[i].sequence,tar)==0)
            {
                if(t[i].SpareTicketnum>=num) 
                {
                    printf("票价：%.2f\n",num*t[i].fare);
                    t[i].head=buy(t[i].head,t[i].SpareTicketnum,num);
                    t[i].SpareTicketnum=t[i].SpareTicketnum-num;
                }
                
                else printf("余票数不足，订票失败！\n");
                break;
            }
        }
        if(i==5) printf("没有找到该车次，请确认后再输入！\n");
	}
	if(op==3)
	{
		int i;
        char tar[20];
        printf("请输入退票车次：");
        scanf("%s",tar);
        for(i=0;i<5;i++)
        {
            if(strcmp(t[i].sequence,tar)==0)//找到目标车次
            {
                char tID[20];
                int d=0;
                int num;
                N *p;
                p=(N*)malloc(lenN);
                p=t[i].head;
                printf("请输入身份证号：");
                scanf("%s",tID);
                while(p!=NULL) 
                {
                	
                    if(strcmp(p->IDcard,tID)==0)//找目标人物
                    {
                        printf("请输入退票数：");
                        scanf("%d",&num);
                        
                        if(num<p->TicketNum)
                        {
                            t[i].SpareTicketnum=t[i].SpareTicketnum+num;//更改票数
                        }
                        else
                        {
                            t[i].SpareTicketnum=t[i].SpareTicketnum+p->TicketNum;//更改票数
                            
                            t[i].head=del(t[i].head,tID); //删除
                        }
                    }
                    p=p->next;
                    
                }
                free(p);
                
                break;
            }
        }
        if(i==5) printf("没有找到该车次，请确认后再输入！\n");
	}
	if(op==4)
    {
    int op2;
    do
    {
    printf("(1)输入车次，输出该车次的全部订票信息\n(2)输入车次，输出该车次的订票数和余票数\n(3)输入终点站名称，输出相关火车线路的信息\n(4)输入日期（X X X），输出发车时间为该天的火车线路的信息\n(5)输出余票数为0的火车线路信息\n若想返回上一级请输入6\n请输入序号：");
    scanf("%d",&op2);
    if(op2==1)
    {        	
    	int i;
        char tar[20];
        printf("请输入车次：");
        scanf("%s",tar);
        for(i=0;i<5;i++)
        {
            if(strcmp(t[i].sequence,tar)==0)
            {
                if(t[i].head->next==NULL) printf("尚没有人员订票！！！\n");
				else list(t[i].head); 
                break; 
            }
        }
        if(i==5) printf("没有找到该车次，请确认后再输入！\n");	
    }
    if(op2==2)
    {
        char tar[20];
        printf("请输入车次：");
        scanf("%s",tar);
        int i;
        for(i=0;i<5;i++)
        {
            if(strcmp(t[i].sequence,tar)==0)
            {
                printf("订票数：%d\n余票数：%d\n",300-t[i].SpareTicketnum,t[i].SpareTicketnum);
                break;
            }
        }
        if(i==5) printf("没有找到该车次，请确认后再输入！\n");
    }
    if(op2==3)
    {
        int i;
        char tar[20];
        printf("请输入终点站：");
        scanf("%s",tar);
        for(i=0;i<5;i++)
        {
            if(strcmp(t[i].terminal,tar)==0)
            {
                printf("终点站：%s\n车次：%s\n发车时间：%d年%d月%d日%d时%d分\n票价：%f\n余票数：%d\n",t[i].terminal,t[i].sequence,t[i].StartTime.year,t[i].StartTime.month,t[i].StartTime.day,t[i].StartTime.hour,t[i].StartTime.minute,t[i].fare,t[i].SpareTicketnum);   
            	break;
			}
        }
        if(i==5) printf("没有找到该车次，请确认后再输入！\n");
    }
    if(op2==4)
    {
        int year,month,day,i,count=0;
        printf("请输入发车时间（XX XX XX）：");
        scanf("%d%d%d",&year,&month,&day);
        for(i=0;i<5;i++)
        {
            if(year==t[i].StartTime.year && month==t[i].StartTime.month && day==t[i].StartTime.day)
            {
                count++;
				printf("终点站：%s\n车次：%s\n发车时间：%d年%d月%d日%d时%d分\n票价：%f\n余票数：%d\n",t[i].terminal,t[i].sequence,t[i].StartTime.year,t[i].StartTime.month,t[i].StartTime.day,t[i].StartTime.hour,t[i].StartTime.minute,t[i].fare,t[i].SpareTicketnum);
			}
        }
        if(count==0) printf("没有找到符合车次！！\n");
    }
    if(op2==5)
    {
    	int count=0;
        for(int i=0;i<5;i++)
        {
            if(t[i].SpareTicketnum==0)
            {
                count++;
				printf("终点站：%s\n车次：%s\n发车时间：%d年%d月%d日%d时%d分\n票价：%f\n余票数：%d\n",t[i].terminal,t[i].sequence,t[i].StartTime.year,t[i].StartTime.month,t[i].StartTime.day,t[i].StartTime.hour,t[i].StartTime.minute,t[i].fare,t[i].SpareTicketnum);
            }
        }
        if(count==0) printf("所有列车都有余座！！\n");
    }
    if(op2==6) break;
    if(op<1||op>6) continue;
	}while(1);
	}
	if(op==5)
	{
		FILE *fp2,*fp3;
		fp2=fopen("information.dat","wb");
		fwrite(t,lenT,5,fp2);
		fclose(fp2);
		
		for(int j=0;j<1;j++)
		{
			
			fp3=fopen(t[j].sequence,"wb");
			N *s;
			s=t[j].head;
			while(s!=NULL)
			{
				fwrite(s,lenN,1,fp3);
				s=s->next;
			}
			fclose(fp3);
		}
		
		exit(0);
	}
	}while(1);
	return 0;
}

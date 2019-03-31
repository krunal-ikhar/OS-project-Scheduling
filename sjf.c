#include<conio.h>
#include<string.h>
#include<stdio.h>

void chart();
void Input_data();
void SJF();

int Total_waiting_time,Total_turnaround_time,Arrival_time[50],Waiting_time[50],m,Burst_time[50];
float Avg_turnaround_time,Avg_wait_time;
char Process_name[20][20];


void Input_data()
{
    int i;
    printf("\n Enter the Total no. of Processes:: ");
    scanf("%d",&m);
    for(i=1;i<=m;i++)
    {
        fflush(stdin);
        printf("\n\n Enter Process name: ");
        scanf("%s",&Process_name[i]);
        printf("\n Enter BurstTime for Process %s = ",Process_name[i]);
        scanf("%d",&Burst_time[i]);
        printf("\n Enter Arrival Time for Process %s =  ",Process_name[i]);
        scanf("%d",&Arrival_time[i]);
    }
}

void chart()
{
    int i;
    printf("\n\nGANTT CHART");
    printf("\n================================================================\n");
    for(i=1;i<=m;i++)
        printf("|\t%s\t",Process_name[i]);
    printf("|\t\n");
    printf("\n================================================================\n");
    printf("\n");
    for(i=1;i<=m;i++)
        printf("%d\t\t",Waiting_time[i]);
    printf("%d",Waiting_time[m]+Burst_time[m]);
    printf("\n================================================================\n");
    printf("\n");
 }

void SJF()
{   char S[10],c[20][20];
    int w=0,t,i,B[10],Tt=0,temp,j;
    int temp1;
    printf("\n\n Shortest Job First Scheduling Algorithm \n\n");
    Total_waiting_time=Total_turnaround_time=0;


    for(i=1;i<=m;i++)
    {
        B[i]=Burst_time[i];
        S[i]='T';
        Tt=Tt+B[i];
    }
    for(i=1;i<=m;i++)
    {
        for(j=3;j<=m;j++)
        {
            if(B[j-1]>B[j])
            {
                temp=B[j-1];
                temp1=Arrival_time[j-1];
                B[j-1]=B[j];
                Arrival_time[j-1]=Arrival_time[j];
                B[j]=temp;
                Arrival_time[j]=temp1;
                strcpy(c[j-1],Process_name[j-1]);
                strcpy(Process_name[j-1],Process_name[j]);
                strcpy(Process_name[j],c[j-1]);
            }
        }
    }
    //For the 1st process
    Waiting_time[1]=0;
    w=w+B[1];
    t=w;
    S[1]='F';
    while(w<Tt)
    {
        i=2;
        while(i<=m)
        {
            if(S[i]=='T'&&Arrival_time[i]<=t)
            {
                Waiting_time[i]=w;
                S[i]='F';
                w=w+B[i];
                t=w;
                i=2;
            }
            else
                i++;
        }
    }

    for(i=1;i<=m;i++)
    {
        Total_waiting_time=Total_waiting_time+(Waiting_time[i]-Arrival_time[i]);
        Total_turnaround_time=Total_turnaround_time+((Waiting_time[i]+Burst_time[i])-Arrival_time[i]);
    }
    printf("\n\n\tProcess\tAT\tBT\tTAT\tWT\n\n");
    printf("\n-------------------------------------------------\n");
    for(i=0;i<=m;i++)
    {
     printf("\tP%s\t%d\t%d\t%d\t%d\n",Process_name[i],Arrival_time[i],Burst_time[i],(Waiting_time[i]+Burst_time[i])-Arrival_time[i],Waiting_time[i]-Arrival_time[i]);
     printf("\n");
     }
    Avg_turnaround_time=(float)Total_turnaround_time/m;
    Avg_wait_time=(float)Total_waiting_time/m;
    printf("\n\n Average Turn around time=%3.2f ms ",Avg_turnaround_time);
    printf("\n\n AverageWaiting Time=%3.2f ms",Avg_wait_time);
    chart();
}
void main()
{
    //clrscr();
    Input_data();
    SJF();
    getch();
}

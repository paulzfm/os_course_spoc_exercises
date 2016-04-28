#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cmath>

#define IDLE 0
#define WAIT 1
#define ACTIVE 2

using namespace std;

int turn;
int flags[1020];
int now[1020];//当前i进程应该执行第多少条指令
int n,m,deeplimit;
int IIndex[1020];
int finish[1020];
int nowrun,nowstate;

void runCheck(int pid,int state)
{
//  printf("%d %d\n",pid,state);
  if(state == 1)
  {
    //进入时，需要没有程序在运行
    if(nowrun)
    {
      printf("ERROR\n");
      exit(0);
    }

    nowrun = pid;
    nowstate = 1;
  }else if(state == 2)
  {
    if(nowrun!=pid)
    {
      printf("ERROR\n");
      exit(0);
    }
    if(nowstate!=1)
    {
      printf("ERROR\n");
      exit(0);
    }
    nowstate = 2;
  }else if(state == 3)
  {
    if(nowrun!=pid)
    {
      printf("1: %d %d\n",nowrun,nowstate);
      printf("ERROR\n");
      exit(0);
    }
    if(nowstate!=2)
    {
      printf("2: %d %d",nowrun,nowstate);
      printf("ERROR\n");
      exit(0);
    }
    nowstate = 0;
    nowrun = 0;
  }else
  {
    printf("%d %d",pid,state);
    printf("ERROR\n");
    exit(0);
  }
}

void runModify(int pid)
{
  int y=now[pid];
  switch (y)
  {
    case 0:
      flags[pid]= WAIT;
      now[pid] = 1;
      break;
    case 1:
      IIndex[pid] = turn;
      now[pid] = 2;
      break;
    case 2:
      if( IIndex[pid] != pid) now[pid] = 3;
      else now[pid] = 4;
      break;
    case 3:
      if (flags[IIndex[pid]]!=IDLE)IIndex[pid] = turn;
      else IIndex[pid]=(IIndex[pid]+1 )% n;
      now[pid] = 2;
      break;
    case 4:
      flags[pid] = ACTIVE;
      now[pid] = 5;
      break;
    case 5:
      IIndex[pid]=0;
      now[pid]=6;
      break;
    case 6:
      if ((IIndex[pid] < n) && ((IIndex[pid] == pid) || (flags[IIndex[pid]] != ACTIVE)))now[pid]=7;
      else now[pid]=8;
      break;
    case 7:
      ++IIndex[pid];
      now[pid]=6;
      break;
    case 8:
      if ((IIndex[pid] >= n) && ((turn == pid) || (flags[turn] == IDLE)))
        now[pid] = 9;
      else
        now[pid] = 0;
      break;
    case 9:
      turn = pid;
      runCheck(pid,1);
      //printf("ENTER PROCESS %d\n",pid);
      now[pid] = 10;
      break;
    case 10:
      //printf("RUNNING PROCESS %d\n",pid);
      runCheck(pid,2);
      now[pid]=11;
      break;
    case 11:
      //printf("EXIT PROCESS %d\n",pid);
      runCheck(pid,3);
      IIndex[pid] = (turn+1)%n;
      now[pid]=12;
      break;
    case 12:
      if (flags[IIndex[pid]]==IDLE)now[pid]=13;
      else now[pid]=14;
      break;
    case 13:
      IIndex[pid]=(IIndex[pid]+1)%n;
      now[pid]=12;
      break;
    case 14:
      turn = IIndex[pid];
      now[pid]=15;
      break;
    case 15:
      flags[pid] = IDLE;
      now[pid]=16;
      break;
    case 16:
      now[pid]=16;
      finish[pid]=1;
      break;
    default:
      printf("ERROR!\n");
      break;

  }
}

void init()
{
  memset(flags,0,sizeof(flags));
  memset(finish,0,sizeof(finish));
  memset(IIndex,0,sizeof(IIndex));
  memset(now,0,sizeof(now));
  turn = 0;
  nowrun = 0;
  nowstate = 0;
}

void load_(int *save_state)
{
  turn = save_state[0];
  nowrun = save_state[1];
  nowstate = save_state[2];
  memcpy(flags+1,save_state+3,n*sizeof(int));
  memcpy(now+1,save_state+3+n,n*sizeof(int));
  memcpy(IIndex+1,save_state+3+n+n,n*sizeof(int));
  memcpy(finish+1,save_state+3+n+n+n,n*sizeof(int));
}

void save_(int *save_state)
{
  save_state[0] = turn;
  save_state[1] = nowrun;
  save_state[2] = nowstate;
  memcpy(save_state+3,flags+1,n*sizeof(int));
  memcpy(save_state+3+n,now+1,n*sizeof(int));
  memcpy(save_state+3+n+n,IIndex+1,n*sizeof(int));
  memcpy(save_state+3+n+n+n,finish+1,n*sizeof(int));
}

void dfs(int deep, int thisrun,int thisruntime)
{
//  printf("%d\n",deep);
  if(deep > deeplimit)return;
  int *save_state = new int[4*n+5];
  for(int i=1;i<=n;++i)
  {
    save_(save_state);
    if(i==thisrun && thisruntime == m)
    if(!finish[i])
    {
      runModify(i);
    /*  for(int j=1;j<=n;++j)
      {
        printf("%d ",now[j]);
      }
      printf("\n");*/
      if(i==thisrun)dfs(deep+1, i,thisruntime+1);
      else dfs(deep+1, i, 0);
      //printf("load?\n");
      load_(save_state);
    }
  }
  //printf("delete?\n");
  delete save_state;
}

int main()
{

  scanf("%d%d%d",&n,&m,&deeplimit);

  init();
  dfs(0,0,0);

/*  for(int i=1;i<=m;++i)
  {
    for(int j=0;j<n;++j)
      runModify(j);
  }*/
  printf("OK\n");
  return 0;

}

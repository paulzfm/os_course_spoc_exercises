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
int n,m;
int IIndex[1020];

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
      printf("ENTER PROCESS %d\n",pid);
      now[pid] = 10;
      break;
    case 10:
      printf("RUNNING PROCESS %d\n",pid);
      now[pid]=11;
      break;
    case 11:
      printf("EXIT PROCESS %d\n",pid);
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
      break;
    default:
      printf("ERROR!\n");
      break;

  }
}

int main()
{
  freopen("input.txt","r",stdin);
  freopen("output2.txt","w",stdout);

  scanf("%d%d",&n,&m);

  for(int i=1;i<=m;++i)
  {
    int x;
    scanf("%d",&x);
    runModify(x);//执行x进程一条指令
  }

/*  for(int i=1;i<=m;++i)
  {
    for(int j=0;j<n;++j)
      runModify(j);
  }*/
  return 0;

}

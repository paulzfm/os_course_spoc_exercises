/*

  edf是实时调度算法，需要给出每个任务的请求时间，执行时间，相对截止时间
  输入数据假定如下：
  第一行一个数字n，表示一共n个任务
  接下来n行每行三个数字i,j,k，i表示任务请求时间，j表示任务执行时间，k表示任务相对截止时间
  这里不对算法本身进行优化
  所有数字均假定设定为整数

*/


#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cmath>
#define maxn 1020
using namespace std;

bool finish[maxn];
int response[maxn];
int turnaround[maxn];
int waittime[maxn];

int a[maxn];//请求时间
int b[maxn];//运行时间
int c[maxn];//相对截止时间
int dl[maxn];
int n;
int main()
{
  freopen("input.txt","r",stdin);

  scanf("%d",&n);
  for(int i=1;i<=n;++i)
  {
    scanf("%d%d%d",&a[i],&b[i],&c[i]);
    c[i]+=a[i];
  }

  int now = 0;//当前时间
  int havedone = 0;
  printf("Execution trace:\n");
  while(havedone<n)
  {
    int choose = -1;
    for(int i=1;i<=n;++i)
    {
      if(a[i]>now)//请求还未到达
        continue;
      if(finish[i])//请求已经结束
        continue;
      if(choose<0||c[choose]>c[i])choose = i;
    }
    if(choose<0)//当前没有可执行请求
      ++now;
    else{

      response[choose]=now-a[choose];
      turnaround[choose]=now+b[choose]-a[choose];
      waittime[choose]=now-a[choose];
      ++havedone;
      dl[havedone]=choose;
      printf("  [ time   %d ] Run job %d for %d.00 secs ( DONE at %d.00 )\n",now,choose-1,b[choose],turnaround[choose]+a[choose]);
      now+=b[choose];
      finish[choose]=true;
    }

  }

  double x1,y1,z1;
  x1=y1=z1=0.0;
  printf("Final statistics:\n");
  for(int i=1;i<=n;++i)
  {
    x1+=response[i];
    y1+=turnaround[i];
    z1+=waittime[i];
    printf("Job   %d -- Response: %d.00  Turnaround %d.00  Wait %d.00\n",dl[i]-1,response[dl[i]],turnaround[dl[i]],waittime[dl[i]]);
  }
  x1/=double(n);
  y1/=double(n);
  z1/=double(n);
  printf("  Average -- Response: %.2lf  Turnaround %.2lf  Wait %.2lf\n",x1,y1,z1);

  return 0;
}

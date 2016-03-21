#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;
struct pageLink
{
    pageLink *prev;
    pageLink *next;
    int pageNumber;
    int pageTime;
};
int main()
{
    freopen("input.txt","r",stdin);
    int N,T,M;
    scanf("%d%d%d",&N,&T,&M);
    pageLink *head = NULL;
    pageLink *tail = NULL;
    
    int pageSize = 0;
    for(int i=1;i<=M;++i)
    {
        int x;
        scanf("%d",&x);
        --x; //from 0 to N - 1
        pageLink *pageNow;
        printf("第%d次访存： ",i);
        bool flag = false;
        for(pageNow = head; pageNow!= NULL; pageNow = pageNow->next)
        {
        //    printf("%d ",pageNow->pageNumber);
            if(pageNow->pageNumber == x)
            {
                printf("页面存在 ");
                pageNow->pageTime = i;
                flag =true;
                break;
            }
        }

        if(!flag)
        {
            pageLink * newNode = new pageLink;
            newNode->pageNumber = x;
            newNode->pageTime = i;
            printf("  缺页，第%d页加入工作集  ",x+1);
            newNode->next = NULL;
            newNode->prev = tail;
            if(head == NULL)head = newNode;
            if(tail != NULL)tail->next = newNode;
            tail = newNode;
        }
        for(pageNow = head; pageNow!= NULL; pageNow = pageNow->next)
        {
            if(pageNow->pageTime <= i - T)
            {
                printf("访存时，将第%d页拿出工作集",pageNow->pageNumber);
                if(pageNow->prev!=NULL)
                {
                    pageNow->prev->next = pageNow->next;
                }else head = pageNow->next;
                if(pageNow->next!=NULL)
                {
                    pageNow->next->prev = pageNow->prev;
                }else tail = pageNow->prev;
                delete pageNow;
                break;
            }
        }
        printf("\n");
    }
    return 0;
}
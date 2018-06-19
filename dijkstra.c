#include<stdio.h>
#include<stdlib.h>
#define blocked 2
#define infinity 1111
int A[100][100],weight[100][100],predecessor[100],label[100],node_status[100],s1,s2,t1,t2,b1,b2,b3,b4,f1,f2,f3,f4,m,n,z,source,dest,dest1,vertices;
void path(int source, int dest);
void dijkstra(int source);
int temp();
int main(int argc, char *argv[])
{
    int i,j,k,l;
    for(i=0; i<100; i++)
        for(j=0; j<100; j++)
        A[i][j]=blocked;
    FILE *infile;
    infile = fopen(argv[1],"r");
    if(infile==NULL)
    {
        printf("Not a valid filename\n");
        exit(0);
    }
    fscanf(infile,"%d",&m);
    fscanf(infile,"%d",&n);
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
        A[i][j]=1;
    if (m>n || m==n)
        z=m;
    else
        z=n;
    fscanf(infile,"%d",&s1);
    fscanf(infile,"%d",&s2);
    s1=m-s1;
    s2=s2-1;
    fscanf(infile,"%d",&t1);
    fscanf(infile,"%d",&t2);
    t1=m-t1;
    t2=t2-1;
    fscanf(infile,"%d",&b1);
    fscanf(infile,"%d",&b2);
    fscanf(infile,"%d",&b3);
    fscanf(infile,"%d",&b4);
    fscanf(infile,"%d",&f1);
    fscanf(infile,"%d",&f2);
    fscanf(infile,"%d",&f3);
    fscanf(infile,"%d",&f4);
    if((s1<0 || s2<0 || t1<0 || t2<0 || b1<0 || b2<0 || b3<0 || b4<0 || f1<0 || f2<0 || f3<0 || f4<0) || (s1>z || s2>z || t1>z || t2>z || b1>z || b2>z || b3>z || b4>z || f1>z || f2>z || f3>z || f4>z))
    {
        printf("Incorrect input..please check the input file for errors\n");
        exit(0);
    }
    for(i=m-b3;i<=m-b1;i++)
    {
        for(j=b2-1;j<=b4-1;j++)
            A[i][j]=blocked;
    }
    for(i=m-f3;i<=m-f1;i++)
    {
        for(j=f2-1;j<=f4-1;j++)
            A[i][j]=0;
    }
   /*for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",A[i][j]);
        }printf("\n");
    }*/
    for(i=0;i<m*n;i++)
    {
        for(j=0;j<m*n;j++)
        {
            weight[i][j]=infinity;
        }
    }
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            for(k=0;k<m;k++)
            {
                for(l=0;l<n;l++)
                {
                    if (abs(k-i)+abs(l-j)==1)
                    {
                    if(A[i][j]==blocked || A[k][l]==blocked)
                        {
                            weight[i*n+j][k*n+l]=infinity;
                        }
                    else if(A[i][j]==0 && A[k][l]==0)
                        {
                            weight[i*n+j][k*n+l]=0;
                        }
                    else
                        {
                            weight[i*n+j][k*n+l]=abs(k-i)+abs(l-j);
                        }
                    }
                }
            }
        }
    }
/*for(i=0;i<m*n;i++)
    {
        for(j=0;j<m*n;j++)
        {
            printf("%d ",weight[i][j]);
        }printf("\n");
    }*/
//printf("\n%d %d %d %d\n",s1,s2,t1,t2);
source=s1*n+s2;
dest=t1*n+t2;
vertices=m*n;
dest1=dest;
dijkstra(source);
path(source,dest);
return 0;
}
void dijkstra(int source)
{
int u,v;
for(v = 0; v < vertices; v++)
{
predecessor[v] = -1;
label[v] = infinity;
node_status[v] = 0;
}
label[source] = 0;
while(1)
{
u = temp();
if(u == -1)
return;
node_status[u] = 1;
for(v = 0; v < vertices; v++)
{
if(weight[u][v] != 1111 && node_status[v] == 0)
{
if( label[u] + weight[u][v] < label[v])
{
predecessor[v] = u;
label[v] = label[u] + weight[u][v];
}
}
}
}
}
int temp()
{
int v;
int min = infinity;
int x = -1;
for(v = 0; v < vertices; v++)
{
if(node_status[v] == 0 && label[v] < min)
{

min = label[v];
x = v;
}
}
return x;
}
void path(int source, int dest)
{
int count,u,x,y;
int path[20],label[20];
int dist = 0;
int temp = 0;
printf("Minimum cost path from (%d %d) to (%d %d) is:\n",m-s1,s2+1,m-t1,t2+1);
while(dest != source)
{
path[temp] = dest;
u = predecessor[dest];
dist = dist + weight[u][dest];
dest = u;
label[temp]=dest+1;
temp++;
}
for(count = temp-1; count >= 0; count--)
{
x=(label[count]-1)/n;
y=(label[count]-1)-(n*x);
x=m-x;
y=y+1;
printf("(%d %d) ",x,y);
x=0; y=0;
}
printf("(%d %d)",m-t1,t2+1);
printf("\nTotal path cost: %d\n", dist);
}

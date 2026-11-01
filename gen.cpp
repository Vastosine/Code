#include <bits/stdc++.h>
using namespace std;
int main(){ const int M=15100000; vector<bool> is(M+1,true); is[0]=is[1]=false;
 for(long long i=2;i*i<=M;i++) if(is[i]) for(long long j=i*i;j<=M;j+=i) is[j]=false;
 vector<int> ps; for(int i=M;i>=2&&(int)ps.size()<300000;i--) if(is[i]) ps.push_back(i);
 printf("%d\n",(int)ps.size()); for(int p:ps) printf("%d ",p); printf("\n"); }

#include <vector>
#include <cstdio>
using namespace std;
vector<int> primes; vector<bool> is;
void init(){ int n=1e7+1; is.assign(n,1); is[0]=is[1]=0;
 for(int i=2;i<n;i++){ if(is[i]) primes.push_back(i);
  for(const auto &p:primes){ if(1ll*i*p>=n) break; is[i*p]=0; if(i%p) break; } } }
int main(){ init(); printf("primes.size() = %zu  (correct 664579)\n", primes.size());
 printf("is[9]=%d is[25]=%d is[49]=%d (1 means wrongly prime)\n",(int)is[9],(int)is[25],(int)is[49]); return 0; }

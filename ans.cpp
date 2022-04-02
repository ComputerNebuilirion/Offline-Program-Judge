#include <cstdio>
#include <cmath>
using namespace std;
int P;
const unsigned long long int Base = 10000000000ULL;
const int maxn = 50 + 10;
unsigned long long val[maxn];
int main()
{
	scanf("%d",&P);
	printf("%d\n",(int)(P * log(2) / log(10)) + 1);
	val[0] = 1;
	while(P--)
	{
		for(int i = 0; i < 50; i++)
			val[i] *= 2;
		for(int i = 0; i < 50; i++)
		{
			if(val[i] >= Base)
			{
				val[i + 1] += val[i] / Base;
				val[i] %= Base;
			}
		}
	}
	val[0]--;
	for(int i = 49; i >= 0; i--)
	{
		printf("%010llu",val[i]);
		if(i % 5 == 0)
			printf("\n");
	}
		
	return 0;
}

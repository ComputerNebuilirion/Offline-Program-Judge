//Program Judge  version 1.0.0
#include <bits/stdc++.h>
#include <windows.h>
#include <ctime>
#define WEXITSTATUS(status)   (((status) & 0xff00) >> 8)
#define WIFEXITED(status) ((status & 0x7f) == 0)
using namespace std;
const int maxn = 1e4 + 5;
char ANS[maxn],STD[maxn] = "",in[maxn]="";
int ans_time,std_time;
char route_l[maxn] = "ans.exe < ",route_r[maxn] = " > ans.out",back[maxn] = "out",str[maxn],buffer[maxn] = "stat\\testpoint.in";
int length[maxn],num_length[maxn],no_length[maxn],Time[maxn],Name[maxn];
struct c_tr{
	char buf[maxn];
	char time_lim[maxn],test_point_name[maxn];
}stor[maxn];
int cnt = 0,tot= 0,st = 0;
void enter_deal(const char* filename)
{
	char s[maxn];
	int j = 0;
	FILE *p;
    p = fopen(filename,"r");
    fscanf(p,"%[^#]",s);
    fclose(p);
    for(int i = 0; i < (int)strlen(s); i++)
	{
        if(s[i] == ' ' || s[i] == '\n') 
			continue;
        s[j++] = s[i];
    }
    s[j] = 0;
    p = fopen(filename,"w");
    fprintf(p,"%s",s);
    fclose(p);
    return;
}
void absorb()
{
	memset(Time,0,sizeof(Time));
	for(int i = 0; i < cnt; i++)
		for(int j = 0; j < num_length[i]; j++)
		{
			int len = num_length[i];
			int number = (int)(stor[i].time_lim[j] - '0');
			for(int k = len - 1; k > j; k--)
				number *= 10;
			Time[i] += number;
		}
}
void check()
{
	int ans_length = strlen(ANS),std_length = strlen(STD);
	if(ans_length > std_length)
	{
		printf("WA:Wrong Answer\nAnswer too long.\n");
		return;
	}
	if(ans_length < std_length)
	{
		printf("WA:Wrong Answer\nAnswer too short.\n");
		return;
	}
	if(ans_length == std_length)
	{
		for(int i = 0; i < ans_length; i++)
		{
			if(ANS[i] != STD[i])
			{
				printf("WA:Wrong Answer\nOn No.%d character:Read %c,Expect %c.\n",i,ANS[i],STD[i]);
				return;
			}
		}
		
		return;
	}
}
void execute(int num)
{
	char cr_num,stat_route[maxn] = "";
	int right = 0;
	cr_num = num + '0';
	for(int i = 0; i < strlen(buffer); i++)
		stat_route[i] = buffer[i];
	for(int i = strlen(stat_route) - 1; i >= 0; i--)
		if(stat_route[i] == '.')
			right = i - 1;
	for(int i = right; stat_route[i] != '\\'; i--)
	{
		stat_route[i] = ' ';
		if(stat_route[i - 1] == '\\')
			stat_route[i] = cr_num;
	}
	int j = 0;
	for(int i = 0; i < (int)strlen(stat_route); i++)
	{
        if(stat_route[i] == ' ') 
			continue;
        stat_route[j++] = stat_route[i];
    }
    for(int i = j + 1; i <strlen(stat_route); i++)
    	stat_route[i] = ' ';
	char command[maxn] = "";
	strcat(command,route_l);
	strcat(command,stat_route);
	strcat(command,route_r);
	int outcheck_ans,ans_begin = 0,ans_end = 0,max_time = Time[num - 1];
	ans_begin = clock();
	outcheck_ans = system(command);
	ans_end = clock();
	ans_time = (int)(ans_end - ans_begin);
	if(ans_time > max_time)
	{
		printf("Test Point #%d\nTLE:Time Limit Exceeded\n",num);
		printf("%d ms\n",ans_time);
		return ;
	}
	int left = 0,tot = 0;
	for(int i = strlen(stat_route) - 1; i >= 0; i--)
		if(stat_route[i] == '.')
			left = i + 1;
	for(int i = left; i < strlen(stat_route); i++)
		stat_route[i] = ' ';
	for(int i = left; i < left + strlen(back); i++)
		stat_route[i] = back[tot++];
	enter_deal("ans.out");
    enter_deal(stat_route);
	freopen(stat_route,"r",stdin);
	scanf("%s",STD);
	freopen("ans.out","r",stdin);
	scanf("%s",ANS);
	if(strcmp(ANS,STD) == 0)
		printf("Test Point #%d\nAC:Accepted\n%d ms\n",num,ans_time);
	else
	{
		printf("Test Point #%d\n",num);	
		check();
		printf("%d ms\n",ans_time);	
	}
	return;
}
void character_deal()
{
	FILE *fp;
	if ((fp = fopen(buffer, "r") )== NULL)
	{
		printf("UKE:Unknown Error\n");
        return ;
    }
    fclose(fp);
	enter_deal(buffer);
	freopen(buffer,"r",stdin);
	scanf("%s",str);
	for(int i = 0; i < strlen(str); i++)
	{
		if(str[i] == ';')
		{
			for(int j = st; j <= i; j++)
				stor[cnt].buf[++tot] = str[j];
			length[cnt] = i - st + 2;
			cnt++;
			tot = 0;
			st = i;
			st++;
		}
	}
	int num = 0,no = 0;
	for(int i = 0; i < cnt; i++)
	{
		for(int j = 0; j < length[i]; j++)
		{
			if(stor[i].buf[j] == ':')
			{
				for(int k = j + 1; k < length[i]; k++)
				{
					if(stor[i].buf[k] != ',')
						stor[i].test_point_name[num++] = stor[i].buf[k];
					else
					{
						no_length[i] = num;
						num = 0;
						break;
					}
						
				}
			}
			if(stor[i].buf[j] == '=')
			{
				for(int k = j + 1; k < length[i]; k++)
				{
					if(stor[i].buf[k] != ';')
						stor[i].time_lim[no++] = stor[i].buf[k];
					else
					{
						num_length[i] = no;
						no = 0;
						break;
					}
						
				}
			}
		}
	}
	absorb();
	for(int i = 0; i < cnt; i++)
	{
		for(int j = 0; j < no_length[i]; j++)
			execute(stor[i].test_point_name[j] - '0');
	}
	return;
}

int main()
{
    system("color f0");
    if(sizeof(char*) == 4)
    {
    	int status_ans32 = 0;
    	status_ans32 = system("g++ -o ans.exe -m32 ans.cpp");
    	if(status_ans32 == -1 || WIFEXITED(status_ans32) == false || 0 != WEXITSTATUS(status_ans32))
    	{
    		printf("CE:Compile Error");
    		return 0;
		}
	}
	if(sizeof(char*) == 8)
	{
		int status_std = 0, status_ans = 0;
    	status_ans = system("g++ -o ans.exe ans.cpp");
    	if(status_ans == -1 || WIFEXITED(status_ans) == false || 0 != WEXITSTATUS(status_ans))
    	{
    		printf("CE:Compile Error\n");
    		return 0;
    	}
	}
	character_deal();
	system("del ans.exe");
	return 0;
}

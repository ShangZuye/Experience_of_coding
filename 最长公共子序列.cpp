#include<iostream> //递推题：找状态，找边界条件，找递推关系式子
#include<cstring>
#include<math.h>
using namespace std;
char sz1[1000];
char sz2[1000];
int MaxLen[1001][1001]; //状态
int main(){
	cout<<"请输入series1和series2： "<<endl;
	while(cin>> sz1 >> sz2 ){
		int len1 = strlen(sz1);
		int len2 = strlen(sz2);
/*		for(int i=0;i<len1;i++)
			cout<< sz1[i];
		cout <<endl;
		for(int i=0;i<len2;i++)
			cout<< sz2[i];
		cout << endl;
*/
		for(int i=0;i<=len1;i++) //边界条件
			MaxLen[i][0] = 0;
		for(int j=0;j<=len2;j++)
			MaxLen[0][j] = 0;
		for(int i=1;i<=len1;i++){
			for(int j=1;j<=len2;j++){
				if(sz1[i-1] == sz2[j-1]) //递推关系
					MaxLen[i][j] = MaxLen[i-1][j-1]+1;
				else
					MaxLen[i][j] = max(MaxLen[i-1][j], MaxLen[i][j-1]);
			}
		}
		cout << "最长子序列长度： " << MaxLen[len1][len2] << endl;
	}
	return 0;
}
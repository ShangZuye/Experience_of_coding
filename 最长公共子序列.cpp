#include<iostream> //�����⣺��״̬���ұ߽��������ҵ��ƹ�ϵʽ��
#include<cstring>
#include<math.h>
using namespace std;
char sz1[1000];
char sz2[1000];
int MaxLen[1001][1001]; //״̬
int main(){
	cout<<"������series1��series2�� "<<endl;
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
		for(int i=0;i<=len1;i++) //�߽�����
			MaxLen[i][0] = 0;
		for(int j=0;j<=len2;j++)
			MaxLen[0][j] = 0;
		for(int i=1;i<=len1;i++){
			for(int j=1;j<=len2;j++){
				if(sz1[i-1] == sz2[j-1]) //���ƹ�ϵ
					MaxLen[i][j] = MaxLen[i-1][j-1]+1;
				else
					MaxLen[i][j] = max(MaxLen[i-1][j], MaxLen[i][j-1]);
			}
		}
		cout << "������г��ȣ� " << MaxLen[len1][len2] << endl;
	}
	return 0;
}
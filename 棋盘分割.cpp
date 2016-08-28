//���̷ָ����⣺��C++��Ƶ��ĵݹ�һ�ڣ�
//1.ע��ݹ麯���Ĳ����仯
//2.����ƥ���ڽ��г�������ʱע����һ�����ͣ�Ӧ��Ϊdouble���ͣ�
//3.�������ʽ���ƺ�����setiosflags
//������λ��Ч���ֵ�д����cout<<setiosflags(ios:fixed)<<setprecision(3)<<����<<endl;

#include<iostream>
#include<cmath>
#include<memory.h>
#include<iomanip>
using namespace std;
//�洢�ռ��ʼ��
int s[9][9];
int sum[9][9];
int res[15][9][9][9][9];
//����subsum(x1,y1,x2,y2)
int subsum(int x1, int y1, int x2, int y2){
	return sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
}
int fun(int n, int x1, int y1, int x2, int y2){
	if(res[n][x1][y1][x2][y2] != -1)
		return res[n][x1][y1][x2][y2];
	if(n ==1){
		int s=subsum(x1,y1,x2,y2);
		//����ǰ�����Ǳ��res
		res[n][x1][y1][x2][y2] = s*s;
		return s*s;
	}
	int left,right,upper,bottom,sum_square,minvalue=100000;
	for(int a=x1;a<x2;a++){   //����ǰ��for(int a=1;a<8;a++)
		left=fun(n-1, x1, y1, a, y2) + fun(1, a+1, y1, x2, y2);
		right = fun(1, x1, y1, a, y2) + fun(n-1, a+1, y1, x2, y2);
		sum_square = min(left, right);
		if(minvalue > sum_square)
			minvalue = sum_square;
	}
	for(int a=y1;a<y2;a++){  //����ǰ��for(int a=1;a<8;a++)
		upper = fun(n-1, x1, y1, x2, a) + fun(1, x1, a+1, x2, y2);
		bottom = fun(1, x1, y1, x2, a) + fun(n-1, x1, a+1, x2, y2);
		sum_square = min(upper, bottom);
		if(minvalue > sum_square)
			minvalue = sum_square;
	}
	//����ǰ�� ���Ǳ��res
	res[n][x1][y1][x2][y2] = minvalue;
	return minvalue;
}
int main(){
	memset(sum, 0, sizeof(sum));
	memset(res, -1, sizeof(res));

	int n;
	cout<< "������ָ�Ŀ�����" << endl;
	cin>> n;
	cout<< "�������̵ĳ�ʼ����" << endl;
	for(int i=1;i<9;i++){
		for(int j=1, rowsum=0;j<9;j++){
			cin>> s[i][j];
			rowsum +=s[i][j];
			sum[i][j] += rowsum + sum[i-1][j];
		}
	}
	/* ����ǰ�� ���Ͳ�ƥ�䣬�������ʱ���ȡ���ģ�����
	int minvalue = fun(n, 1, 1, 8, 8);
	double sigma = sqrt((minvalue -sum[8][8]*sum[8][8]/n )/n);
	cout << "ʹ�þ�������С�Ľ��ֵ: " << sigma << endl;*/
	double result = n*fun(n,1,1,8,8)-sum[8][8]*sum[8][8];
	cout << setiosflags(ios::fixed)<<setprecision(3)<< sqrt(result/(n*n))<<endl;


	return 0;
}

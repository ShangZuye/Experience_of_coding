//棋盘分割问题：（C++视频里的递归一节）
//1.注意递归函数的参数变化
//2.类型匹配在进行除法运算时注意检查一下类型，应设为double类型；
//3.输出流格式控制函数：setiosflags
//保留三位有效数字的写法：cout<<setiosflags(ios:fixed)<<setprecision(3)<<变量<<endl;

#include<iostream>
#include<cmath>
#include<memory.h>
#include<iomanip>
using namespace std;
//存储空间初始化
int s[9][9];
int sum[9][9];
int res[15][9][9][9][9];
//计算subsum(x1,y1,x2,y2)
int subsum(int x1, int y1, int x2, int y2){
	return sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
}
int fun(int n, int x1, int y1, int x2, int y2){
	if(res[n][x1][y1][x2][y2] != -1)
		return res[n][x1][y1][x2][y2];
	if(n ==1){
		int s=subsum(x1,y1,x2,y2);
		//修正前：忘记标记res
		res[n][x1][y1][x2][y2] = s*s;
		return s*s;
	}
	int left,right,upper,bottom,sum_square,minvalue=100000;
	for(int a=x1;a<x2;a++){   //修正前：for(int a=1;a<8;a++)
		left=fun(n-1, x1, y1, a, y2) + fun(1, a+1, y1, x2, y2);
		right = fun(1, x1, y1, a, y2) + fun(n-1, a+1, y1, x2, y2);
		sum_square = min(left, right);
		if(minvalue > sum_square)
			minvalue = sum_square;
	}
	for(int a=y1;a<y2;a++){  //修正前：for(int a=1;a<8;a++)
		upper = fun(n-1, x1, y1, x2, a) + fun(1, x1, a+1, x2, y2);
		bottom = fun(1, x1, y1, x2, a) + fun(n-1, x1, a+1, x2, y2);
		sum_square = min(upper, bottom);
		if(minvalue > sum_square)
			minvalue = sum_square;
	}
	//修正前： 忘记标记res
	res[n][x1][y1][x2][y2] = minvalue;
	return minvalue;
}
int main(){
	memset(sum, 0, sizeof(sum));
	memset(res, -1, sizeof(res));

	int n;
	cout<< "请输入分割的块数：" << endl;
	cin>> n;
	cout<< "进行棋盘的初始化：" << endl;
	for(int i=1;i<9;i++){
		for(int j=1, rowsum=0;j<9;j++){
			cin>> s[i][j];
			rowsum +=s[i][j];
			sum[i][j] += rowsum + sum[i-1][j];
		}
	}
	/* 修正前： 类型不匹配，计算除法时候会取整的！！！
	int minvalue = fun(n, 1, 1, 8, 8);
	double sigma = sqrt((minvalue -sum[8][8]*sum[8][8]/n )/n);
	cout << "使得均方差最小的结果值: " << sigma << endl;*/
	double result = n*fun(n,1,1,8,8)-sum[8][8]*sum[8][8];
	cout << setiosflags(ios::fixed)<<setprecision(3)<< sqrt(result/(n*n))<<endl;


	return 0;
}

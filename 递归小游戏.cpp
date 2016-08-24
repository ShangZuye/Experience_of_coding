#include<cstdio>
#include<memory.h>
#include<iostream>
using namespace std;

const int MAXMUM = 75;
char attr[MAXMUM+2][MAXMUM+2];
int w,h,minstep = 10000, towhere[4][2]= {{0,1}, {1,0}, {0,-1}, {-1,0}};
bool mark[MAXMUM+2][MAXMUM+2];

void search(int begin_h, int begin_w, int end_h, int end_w, int unstep, int f ){
	if(unstep > minstep) return;
	if(begin_h == end_h && begin_w == end_w){
		if(unstep < minstep){
			minstep = unstep;
			return;
		}
	}
	for(int i=0; i<4; i++){
		int x= begin_h + towhere[i][0];
		int y = begin_w + towhere[i][1];
		//判断新走的位置是否为有效的位置，有效的位置满足如下条件：
		//1.判断新的位置超出边界了没有（人为将边界拓宽一圈）-1< x <w+2 && -1< y < h+2
		//2.attr[][]==" " && mark[][]==false
		//3.此处标记为“X”，但是为终点值attr[][]="X" && x == end_w && y == end_w
		if((x > -1)&&(x < h+2)&&(y > -1)&&(y < w+2)&&
			(attr[x][y] == ' ')&&(mark[x][y] == false) ||
			(attr[x][y] == 'X')&&(x == end_h)&&(y == end_w)){
				//确认新的位置有效，首先应该标记已经走过：mark[][]=True；
				//计入步数，进入下一轮的选择（递归）
				//如果选择的道路走不通，回到上一步，重新标记mark[][]= false，回到没做过的情形
				mark[x][y] = true;
				if(i == f) search(x, y, end_h, end_w, unstep, i);
				else search(x, y, end_h, end_w, unstep+1, i);
				mark[x][y] = false;
		}
	}
}
int main(){
	int Boardnum = 0;
	cout<< "请分别输入Board的宽和高："<<endl;
	while(cin >> w >> h ){
		if(w == 0 && h ==0) break;
		Boardnum++;
		cout<<"Board: "<< Boardnum<<endl;
		for(int i=0; i< MAXMUM+2;i++) attr[0][i] = attr[i][0] = ' ';
		for(int i=1; i<h+1; i++){
			getchar();
			for(int j=1; j<w+1; j++){
				attr[i][j] = getchar();
			}
		}
		for(int i=0;i<w+1;i++)
			attr[h+1][i+1] = ' ';
		for(int i=0;i<h+1;i++)
			attr[i+1][w+1]= ' ';
		cout<< "请分别输入起点和终点："<< endl;
		int begin_h, begin_w, end_h, end_w, count = 0;
		while(cin>> begin_h >> begin_w >> end_h >> end_w){
			if(begin_h ==0 && begin_w==0 && end_h ==0 && end_w == 0) break;
			count++;
			minstep = 10000;
			memset(mark, false, sizeof(mark));
			search(begin_h, begin_w, end_h, end_w, 0, -1);

			if(minstep < 10000)
				cout<< "pair " << count << ": "<< minstep << endl;
			else
				cout<< "pair " << count << ": " << "impossible" <<endl;
		}
	}
	return 0;
}










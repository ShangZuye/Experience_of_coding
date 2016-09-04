//总结：
//知识要点：
//  1 两个转换：序号和排列的相互转换，字符型数组与整形数组的相互转换
//  2 自己设计队列实现：判空， 入队， 出队
//  3 状态转移方法：swithch
//  4 广度搜索的算法步骤：队列判空 —> 判断符合目标需求 -> 节点拓展，入队（判重） -> 出队 ——
//                       |————<———————————————————————————|
//  5 利用 bitset 存储使用状态 ： .reset(); .set();
//  6 字符数组的初始化和赋值问题，具体说：(unknown??)
//			char sz4Moves[] = "udrl" ;
//			GenPermulationByNum((char*)"012345678",strStatus,9,n);
//			*(s2+i) = *(s1+perInt[i]);

#include<iostream>
#include<bitset> //新用法
#include<cstring>
using namespace std;


int goalStatus;  //目标状态
bitset<362880> Flags;  //节点是否拓展的标记
const int MAXS = 400000;
char result[MAXS]; //结果

struct Node{
	int status;  //状态，即排列的编号
	int father;  //父节点的指针
	char move;  //父节点到本节点的移动方式 u/d/r/l
	Node(int s, int f, char m):status(s),father(f),move(m){}
	Node(){}
};
Node myQueue[MAXS]; //状态队列，状态总数362880 （不用STL的顾虑是啥？）
int qHead; int qTail;  //队头指针和队尾指针
char sz4Moves[]= "udrl"; //四种动作      （  研究一下字符数组的初始化 ！！！）
unsigned int factorial[21]; //存放0-20的阶乘。 21的阶乘unsigned放不下

unsigned int GetPermulationNumForInt(int * perInt, int len){
	//perInt 里面放着整数0到len-1的一个排列，求它是第几个排列
	//len不能超过21
	unsigned int num = 0;
	bool used[21];
	memset(used, 0, sizeof(bool)*len);
	for(int i=0;i<len;++i){
		unsigned int n = 0;
		for(int j=0;j<perInt[i];++j ){
			if(!used[j])
				++n;
		}
		num +=n*factorial[len-i-1];
		used[perInt[i]] = true ;
	}
	return num;
}

template<class T>
unsigned int GetPermulationNum(T s1, T s2, int len){
	//给定排列，求序号。[s1, s1+len)里面放着第0号排列
	//[s2, s2+len)是要求序号的排列
	//排列的每个元素都不一样。返回排列的编号
	int *perInt= new int[len];//要转换成[0,len-1]的整数
	  //new 生成可动态变化的动态数组
	 //由字符形式的存储转化为整型
	for(int i=0;i<len;++i){
		for(int j=0;j<len;++j){
			if(*(s2+i) == *(s1+j)){
				perInt[i] = j;
				break;
			}
		}
	}
		unsigned int num = GetPermulationNumForInt(perInt,len);
		delete [] perInt;
		return num;
}

template<class T>
void GenPermulationByNum(T s1, T s2, int len, unsigned int No){
	//根据排列编号，生成排列len不能超过21
	int perInt[21]; //要转换成[0,len-1]的整形排列
	bool used[21];
	memset(used,0,sizeof(bool)*len);
	for(int i=0;i<len;++i){
		int n=0; int j;
		for(j = 0; j<len ; ++j){
			if(!used[j]){
				if(factorial[len-i-1]>=No+1) break;
				else No-=factorial[len-i-1];
			}
		}
		perInt[i] = j;
		used[j] = true;
	}
	for(int i=0;i<len;++i)
		*(s2+i) = *(s1+perInt[i]);
	//delete []perInt;
	//delete [] used;
}
int StrStatusToIntStatus(const char* strStatus){
	//字符串形式的状态，转换为整数形式的状态（排列序号）
	return GetPermulationNum ("012345678", strStatus, 9);
}

void IntStatusToStrStatus(int n, char *strStatus){
	//整数形式的状态（排列序号），转换为字符串形式的状态
	GenPermulationByNum((char*)"012345678",strStatus,9,n); //“012345678”是字符串形式，需要强制转换为字符数组！！！
}

int NewStatus(int nStatus, char cMove){
	//求从nStatus经过cMove移动后得到的新状态。若移动不可行则返回-1；
	char szTmp[20]; int nZeroPos;
	IntStatusToStrStatus(nStatus,szTmp);
	for(int i=0;i<9;++i)
		if(szTmp[i] == '0'){
			nZeroPos = i;
			break;
		}//返回空格的位置
	switch(cMove){
	case 'u':if(nZeroPos - 3 <0 ) return -1;
			 else{	szTmp[nZeroPos] = szTmp[nZeroPos -3];
					szTmp[nZeroPos-3] = '0';}
			 break;
	case 'd': if(nZeroPos + 3 > 8) return -1;
			  else{	szTmp[nZeroPos] = szTmp[nZeroPos+3];
					szTmp[nZeroPos+3] = '0';}
			  break;
	case 'l': if(nZeroPos%3 == 0) return -1;
			  else{	szTmp[nZeroPos]=szTmp[nZeroPos-1];
					szTmp[nZeroPos-1]= '0';}
			  break;
	case 'r': if(nZeroPos%3==2) return -1;
			  else{	szTmp[nZeroPos] = szTmp[nZeroPos+1];
					szTmp[nZeroPos+1] = '0';}
			  break;
	}
	return StrStatusToIntStatus(szTmp);
}
					
bool Bfs(int nStatus){//寻找从初始状态nStatus到目标的路径
	int nNewStatus;
	Flags.reset();
	qHead = 0; qTail = 1;
	myQueue[qHead] = Node(nStatus, -1,0);
	while(qHead != qTail){//队列不为空
		nStatus = myQueue[qHead].status;
		if(nStatus == goalStatus) //找到目标状态
			return true;
		for(int i =0;i<4;i++){//尝试四种移动
			nNewStatus = NewStatus(nStatus, sz4Moves[i]);
			if(nNewStatus == -1) continue;  //不可移，继续
			if(Flags[nNewStatus]) continue;  //判重，继续
			Flags.set(nNewStatus, true); //bitset的操作方法（封闭性）
			myQueue[qTail++] = Node(nNewStatus,qHead, sz4Moves[i]);
			//新节点入队列
		}
		qHead++;
	}
	return false;
}

int main(){
	//初始化阶乘
	for(int i=0;i<21;i++){
		if(i==0) factorial[i] = 1;
		else
			factorial[i]= factorial[i-1]*i;
	}
	goalStatus = StrStatusToIntStatus("123456780");
	cout <<goalStatus;
	char szLine[50]; char szLine2[20];
	while(cin.getline(szLine, 48)){
		int i,j;
		//将输入的原始字符串变为数字字符串
		for(i=0,j=0;szLine[i];i++ ){
			if(szLine[i]!=' '){
				if(szLine[i] == 'x') szLine2[j++]='0';
				else szLine2[j++] = szLine[i];
			}
		}
		szLine2[j] = 0;
		int sumGoal = 0;//下面用奇偶性判断是否有解
		for(int i = 0;i<8;++i)
			sumGoal +=i-1;
		int sumOri = 0;
		for(int i=0;i<9;++i){
			if(szLine2[i]=='0')
				continue;
			for(int j=0;j<i;j++){
				if(szLine2[j]<szLine2[i] && szLine2[j]!='0')
					sumOri++;
			}
		}
		if(sumOri%2!=sumGoal%2){
			cout << "unsolvable"<<endl;
			continue;
		}
		//上面用奇偶性判断是否有解
		if(Bfs(StrStatusToIntStatus(szLine2))){
			int nMoves = 0;
			int nPos = qHead;
			do{//通过father找到成功的状态序列，输出相应步骤
				result[nMoves++]= myQueue[nPos].move;
				nPos = myQueue[nPos].father;
			}while(nPos);//nPos=0说明已经回到初始状态了
			for(int i = nMoves-1;i>=0;i--)
				cout<<result[i];
		}
		else cout <<"unsolvable"<<endl;
	}
	return 0;
}
//�ܽ᣺
//֪ʶҪ�㣺
//  1 ����ת������ź����е��໥ת�����ַ�������������������໥ת��
//  2 �Լ���ƶ���ʵ�֣��пգ� ��ӣ� ����
//  3 ״̬ת�Ʒ�����swithch
//  4 ����������㷨���裺�����п� ��> �жϷ���Ŀ������ -> �ڵ���չ����ӣ����أ� -> ���� ����
//                       |��������<������������������������������������������������������|
//  5 ���� bitset �洢ʹ��״̬ �� .reset(); .set();
//  6 �ַ�����ĳ�ʼ���͸�ֵ���⣬����˵��(unknown??)
//			char sz4Moves[] = "udrl" ;
//			GenPermulationByNum((char*)"012345678",strStatus,9,n);
//			*(s2+i) = *(s1+perInt[i]);

#include<iostream>
#include<bitset> //���÷�
#include<cstring>
using namespace std;


int goalStatus;  //Ŀ��״̬
bitset<362880> Flags;  //�ڵ��Ƿ���չ�ı��
const int MAXS = 400000;
char result[MAXS]; //���

struct Node{
	int status;  //״̬�������еı��
	int father;  //���ڵ��ָ��
	char move;  //���ڵ㵽���ڵ���ƶ���ʽ u/d/r/l
	Node(int s, int f, char m):status(s),father(f),move(m){}
	Node(){}
};
Node myQueue[MAXS]; //״̬���У�״̬����362880 ������STL�Ĺ�����ɶ����
int qHead; int qTail;  //��ͷָ��Ͷ�βָ��
char sz4Moves[]= "udrl"; //���ֶ���      ��  �о�һ���ַ�����ĳ�ʼ�� ��������
unsigned int factorial[21]; //���0-20�Ľ׳ˡ� 21�Ľ׳�unsigned�Ų���

unsigned int GetPermulationNumForInt(int * perInt, int len){
	//perInt �����������0��len-1��һ�����У������ǵڼ�������
	//len���ܳ���21
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
	//�������У�����š�[s1, s1+len)������ŵ�0������
	//[s2, s2+len)��Ҫ����ŵ�����
	//���е�ÿ��Ԫ�ض���һ�����������еı��
	int *perInt= new int[len];//Ҫת����[0,len-1]������
	  //new ���ɿɶ�̬�仯�Ķ�̬����
	 //���ַ���ʽ�Ĵ洢ת��Ϊ����
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
	//�������б�ţ���������len���ܳ���21
	int perInt[21]; //Ҫת����[0,len-1]����������
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
	//�ַ�����ʽ��״̬��ת��Ϊ������ʽ��״̬��������ţ�
	return GetPermulationNum ("012345678", strStatus, 9);
}

void IntStatusToStrStatus(int n, char *strStatus){
	//������ʽ��״̬��������ţ���ת��Ϊ�ַ�����ʽ��״̬
	GenPermulationByNum((char*)"012345678",strStatus,9,n); //��012345678�����ַ�����ʽ����Ҫǿ��ת��Ϊ�ַ����飡����
}

int NewStatus(int nStatus, char cMove){
	//���nStatus����cMove�ƶ���õ�����״̬�����ƶ��������򷵻�-1��
	char szTmp[20]; int nZeroPos;
	IntStatusToStrStatus(nStatus,szTmp);
	for(int i=0;i<9;++i)
		if(szTmp[i] == '0'){
			nZeroPos = i;
			break;
		}//���ؿո��λ��
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
					
bool Bfs(int nStatus){//Ѱ�Ҵӳ�ʼ״̬nStatus��Ŀ���·��
	int nNewStatus;
	Flags.reset();
	qHead = 0; qTail = 1;
	myQueue[qHead] = Node(nStatus, -1,0);
	while(qHead != qTail){//���в�Ϊ��
		nStatus = myQueue[qHead].status;
		if(nStatus == goalStatus) //�ҵ�Ŀ��״̬
			return true;
		for(int i =0;i<4;i++){//���������ƶ�
			nNewStatus = NewStatus(nStatus, sz4Moves[i]);
			if(nNewStatus == -1) continue;  //�����ƣ�����
			if(Flags[nNewStatus]) continue;  //���أ�����
			Flags.set(nNewStatus, true); //bitset�Ĳ�������������ԣ�
			myQueue[qTail++] = Node(nNewStatus,qHead, sz4Moves[i]);
			//�½ڵ������
		}
		qHead++;
	}
	return false;
}

int main(){
	//��ʼ���׳�
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
		//�������ԭʼ�ַ�����Ϊ�����ַ���
		for(i=0,j=0;szLine[i];i++ ){
			if(szLine[i]!=' '){
				if(szLine[i] == 'x') szLine2[j++]='0';
				else szLine2[j++] = szLine[i];
			}
		}
		szLine2[j] = 0;
		int sumGoal = 0;//��������ż���ж��Ƿ��н�
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
		//��������ż���ж��Ƿ��н�
		if(Bfs(StrStatusToIntStatus(szLine2))){
			int nMoves = 0;
			int nPos = qHead;
			do{//ͨ��father�ҵ��ɹ���״̬���У������Ӧ����
				result[nMoves++]= myQueue[nPos].move;
				nPos = myQueue[nPos].father;
			}while(nPos);//nPos=0˵���Ѿ��ص���ʼ״̬��
			for(int i = nMoves-1;i>=0;i--)
				cout<<result[i];
		}
		else cout <<"unsolvable"<<endl;
	}
	return 0;
}
1.原来照片格式是提交不了的——invalid format

2.作为一个分布式版本控制软件，应该是管理文本和代码块的

3.我猜想肯定有办法传输的，图片可以利用html语言传送上去啊，但是应该要设计到比较深入的东西。

4.本地任意位置创建一个github容器，且与远程库关联的方法：
	（1）git init  //初始化本地容器
		git add <filename>
		git commit -m"...(文本)"
	（2）如果原先创建了一个远程关联，先使用 git remote remove origin 删除 origin
		git remote add origin git@github.com:ShangZuye/远程库名字.git
		git push -u origin master
		下次同步直接输入： git push origin master
	（3）版本回退和返回的操作：
		也就是想回退到某一个版本，回退到某个版本又后悔想回来的方法：
		git reset --hard commit_id
		回退时，用 git log （--pretty=oneline）确定回到那个版本号
		重返未来，用 git reflog 	确定重返的版本号
		
		
5.动态规划专题（动规）
    ——C++视频动态规划一节的总结
	
	1.动态规划的思路：
		是一种自下而上的解决方法，有较底层的状态推出较上层的状态；
	
	2.与递归的区别：
		在逻辑上看，递推与递归相逆，但实质上是一样的，递归就是一步步递归	到底层，再一步步递推回来；
	
	3.递推具有的特点：
		(1)一般问题有不同的状态，确定不同的状态，找到状态递推的关系式（	状态转移方程）；
		(2)具有最优子结构，全局最优的话，子问题也必须是一个最优问题
		(3)无后效性：一阶马氏链，当前状态只跟前一个状态有关系
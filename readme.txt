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
		
		

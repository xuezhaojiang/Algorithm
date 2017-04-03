# AlgorithmExperiment
算法实验      
快速排序、背包问题(01背包、分数背包)、任务调度、平衡树（红黑树red black tree、treap tree）     
红黑树效果图      
     
![](红黑树.JPG)       
TreapTree效果图      
      
![](TreapTree.JPG)       
       
       
# 图算法      
实现了图的深度、广度优先遍历，以及Dijkstra最短路径问题。      
     
     
# Strassen
Strassen方法计算矩阵乘法,并且用三重循环的方式算了一遍，亲测有效。    
由于二维数组作为函数参数传递时，要求指定第二个下标，并且要求第二个下标为常数，这给递归带来了很大的不便。     
在函数Strassen中，指定参数为A[][NN],这样空间利用效率低。     
在函数Strassen2中，将A强制转化为（int \*）类型，并且利用\*((A+i\*N))+j)来访问A[i][j]，提高空间利用率。                
至于为什么不转化为(int \*\*)类型，这是因为(int \*\*)并没有从本质上改变 A 是一个二级指针的性质，\*(\*(A+i))+j)，编译器不知道怎么处理A+i，而\*((A+i\*N))+j)则不知所云。      
      
      
# StudyUnion     
学习结构的使用    
深入理解计算机系统3.67      
&emsp;&emsp;在大一学习c语言的时候我就想，对于
```int a[10];```
在运行时，a是一个常量指针，在计算器中在哪里存放a的值的。     
&emsp;&emsp;是专门有个4个byte的指针类型的块存放a的值吗？     
&emsp;&emsp;进一步这个问题，对于```int i;```是怎样通过i找到数据区的，难道是再开辟一个指针存数据区的地址吗？那又是怎样找到这个存数据区地址的指针的数据区的呢？    
&emsp;&emsp;最近在学习csapp是，发现所有的汇编代码中，只有寄存器和堆栈。我突然想明白了，在汇编中根本没有a,没有i，数组的首地址以及i的值在寄存器中或者
堆栈中，a和i在编译过程中就给消除了。      
&emsp;&emsp;数据只有两个属性，数值、地址，没有名字这一说。寄存器的名字可以理解为是一种特殊的地址。

      
echo "# AlgorithmExperiment" >> README.md   
git init    
git add README.md     
git commit -m "first commit"     
git remote add origin https://github.com/xuezhaojiang/AlgorithmExperiment.git      
git push -u origin master      
…or push an existing repository from the command line     
      
git remote add origin https://github.com/xuezhaojiang/AlgorithmExperiment.git      
git push -u origin master      

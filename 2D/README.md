# 2D algorithm

## 1. 计算两条线段的交点，计算两个多边形的交点。

### 算法步骤：

**1. 快速排序实验**  
设以线段P1P2为对角线的矩形为R，设以线段Q1Q2为对角线的矩形为T，如果R和T不相交，则两线段不相交。
所以P1P2和Q1Q2相交的必要条件是以他们为对角线的矩形相交，即：
```c++
min(p1.x,p2.x) <= max(q1.x,q2.x) &&
min(q1.x,q2.x) <= max(p1.x,p2.x) &&
min(p1.y,p2.y) <= max(q1.y,q2.y) &&
min(q1.y,q2.y) <= max(p1.y,p2.y);
``` 
**2. 跨立实验**  
如果两线段相交，则两线段必然相互跨立对方。  

a、若P1P2跨立Q1Q2，则矢量(P1-Q1)和(P2-Q1)位于矢量(Q2-Q1)的两侧，即{( P1 - Q1 ) × ( Q2 - Q1 )} * {( P2 - Q1 ) × ( Q2 - Q1 )} <= 0。
b、若Q1Q2跨立P1P2，则矢量(Q1-P1)和(Q2-P1)位于矢量(P2-P1)的两侧，即{( Q1 - P1 ) × ( P2 - P1 )} * {( Q2 - P1 ) × ( P2 - P1 )} <= 0。

a和b两个不等式需要同时满足。  
![跨立实验](https://github.com/HongfeiXu/CG_SmallAlgo/blob/master/2D/images/GetCrossPoint_01.png)

![快速排序&&跨立实验](https://github.com/HongfeiXu/CG_SmallAlgo/blob/master/2D/images/GetCrossPoint_00.png)

**3. 计算两条线段交点**  
当判定两条线段相交后，可以进行交点的求解，求交点可以用平面几何方法，列点斜式方程来完成。但由于点斜式方程难以处理斜率为0的特殊情况，不方便求解。因而，参用向量法求解交点。

**4. 调用上面的计算线段交点函数来计算两个多边形的交点**

### 代码：  
[GetCrossPoint.h](https://github.com/HongfeiXu/CG_SmallAlgo/blob/master/2D/GetCrossPoint.h)  
[GetCrossPoint_test.cpp](https://github.com/HongfeiXu/CG_SmallAlgo/blob/master/2D/GetCrossPoint_test.cpp)  
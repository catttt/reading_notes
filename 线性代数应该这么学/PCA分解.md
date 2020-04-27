# PCA主成分分析

文章转自 https://zhuanlan.zhihu.com/p/37777074。

供自己温故知新。

目录：

1. 相关背景
2. 数据降维
3. PCA原理详解

​    3.1 PCA的概念

​    3.2 协方差

​    3.3 特征值与特征向量

​    3.4 SVD分解原理

​    3.5 PCA算法两种实现方法

​        (1) 基于特征值分解协方差矩阵实现PCA算法

​        (2) 基于SVD分解协方差矩阵实现PCA算法

\4. PCA实例

\5. PCA的理论推导

\6. 选择降维后的维度K(主成分的个数)

## 1.相关背景

​    在许多领域的研究与应用中，通常需要对含有多个变量的数据进行观测，收集大量数据后进行分析寻找规律。多变量大数据集无疑会为研究和应用提供丰富的信息，但是也在一定程度上增加了数据采集的工作量。更重要的是在很多情形下，许多变量之间可能存在相关性，从而增加了问题分析的复杂性。如果分别对每个指标进行分析，分析往往是孤立的，不能完全利用数据中的信息，因此盲目减少指标会损失很多有用的信息，从而产生错误的结论。

​    因此需要找到一种合理的方法，在减少需要分析的指标同时，尽量减少原指标包含信息的损失，以达到对所收集数据进行全面分析的目的。由于各变量之间存在一定的相关关系，因此可以考虑将关系紧密的变量变成尽可能少的新变量，使这些新变量是两两不相关的，那么就可以用较少的综合指标分别代表存在于各个变量中的各类信息。主成分分析与因子分析就属于这类降维算法。

## 2. 数据降维

​    降维就是一种对高维度特征数据预处理方法。降维是将高维度的数据保留下最重要的一些特征，去除噪声和不重要的特征，从而实现提升数据处理速度的目的。在实际的生产和应用中，降维在一定的信息损失范围内，可以为我们节省大量的时间和成本。降维也成为应用非常广泛的数据预处理方法。

降维具有如下一些优点：

- 使得数据集更易使用。
- 降低算法的计算开销。
- 去除噪声。
- 使得结果容易理解。

降维的算法有很多，比如[奇异值分解(SVD)](https://link.zhihu.com/?target=https%3A//mp.weixin.qq.com/s/Dv51K8JETakIKe5dPBAPVg)、主成分分析(PCA)、因子分析(FA)、独立成分分析(ICA)。

## 3. PCA原理详解

## 3.1 PCA的概念

   PCA(Principal  Component  Analysis)，即主成分分析方法，是一种使用最广泛的数据降维算法。PCA的主要思想是将n维特征映射到k维上，这k维是全新的正交特征也被称为主成分，是在原有n维特征的基础上重新构造出来的k维特征。PCA的工作就是从原始的空间中顺序地找一组相互正交的坐标轴，新的坐标轴的选择与数据本身是密切相关的。其中，第一个新坐标轴选择是原始数据中方差最大的方向，第二个新坐标轴选取是与第一个坐标轴正交的平面中使得方差最大的，第三个轴是与第1,2个轴正交的平面中方差最大的。依次类推，可以得到n个这样的坐标轴。通过这种方式获得的新的坐标轴，我们发现，大部分方差都包含在前面k个坐标轴中，后面的坐标轴所含的方差几乎为0。于是，我们可以忽略余下的坐标轴，只保留前面k个含有绝大部分方差的坐标轴。事实上，这相当于只保留包含绝大部分方差的维度特征，而忽略包含方差几乎为0的特征维度，实现对数据特征的降维处理。

**思考：**我们如何得到这些包含最大差异性的主成分方向呢？

**答案：**事实上，通过计算数据矩阵的协方差矩阵，然后得到协方差矩阵的特征值特征向量，选择特征值最大(即方差最大)的k个特征所对应的特征向量组成的矩阵。这样就可以将数据矩阵转换到新的空间当中，实现数据特征的降维。

由于得到协方差矩阵的特征值特征向量有两种方法：特征值分解协方差矩阵、奇异值分解协方差矩阵，所以PCA算法有两种实现方法：基于特征值分解协方差矩阵实现PCA算法、基于SVD分解协方差矩阵实现PCA算法。

既然提到协方差矩阵，那么就简单介绍一下方差和协方差的关系。然后概括介绍一下特征值分解矩阵原理、奇异值分解矩阵的原理。概括介绍是因为在我之前的[《机器学习中SVD总结》](https://link.zhihu.com/?target=https%3A//mp.weixin.qq.com/s/Dv51K8JETakIKe5dPBAPVg)文章中已经详细介绍了特征值分解原理和奇异值分解原理，这里就不再重复讲解了。可以看我的

[《机器学习中SVD总结》](https://link.zhihu.com/?target=https%3A//mp.weixin.qq.com/s/Dv51K8JETakIKe5dPBAPVg)文章。地址：[机器学习中SVD总结](https://link.zhihu.com/?target=https%3A//mp.weixin.qq.com/s/Dv51K8JETakIKe5dPBAPVg)

## 3.2 协方差和散度矩阵

样本均值：

![[公式]](https://www.zhihu.com/equation?tex=%5Cbar%7Bx%7D%3D%5Cfrac%7B1%7D%7Bn%7D%5Csum_%7Bi%3D1%7D%5E%7BN%7D%7Bx_%7Bi%7D%7D) 

样本方差：

![[公式]](https://www.zhihu.com/equation?tex=S%5E%7B2%7D%3D%5Cfrac%7B1%7D%7Bn-1%7D%5Csum_%7Bi%3D1%7D%5E%7Bn%7D%7B%5Cleft%28+x_%7Bi%7D-%5Cbar%7Bx%7D+%5Cright%29%5E2%7D) 

样本X和样本Y的协方差：

![[公式]](https://www.zhihu.com/equation?tex=%5Cbegin%7Balign%2A%7D+Cov%5Cleft%28+X%2CY+%5Cright%29%26%3DE%5Cleft%5B+%5Cleft%28+X-E%5Cleft%28+X+%5Cright%29+%5Cright%29%5Cleft%28+Y-E%5Cleft%28+Y+%5Cright%29+%5Cright%29+%5Cright%5D+%5C%5C+%26%3D%5Cfrac%7B1%7D%7Bn-1%7D%5Csum_%7Bi%3D1%7D%5E%7Bn%7D%7B%28x_%7Bi%7D-%5Cbar%7Bx%7D%29%28y_%7Bi%7D-%5Cbar%7By%7D%29%7D+%5Cend%7Balign%2A%7D) 

由上面的公式，我们可以得到以下结论：

(1) 方差的计算公式是针对一维特征，即针对同一特征不同样本的取值来进行计算得到；而协方差则必须要求至少满足二维特征；方差是协方差的特殊情况。

(2) 方差和协方差的除数是n-1,这是为了得到方差和协方差的无偏估计。

协方差为正时，说明X和Y是正相关关系；协方差为负时，说明X和Y是负相关关系；协方差为0时，说明X和Y是相互独立。Cov(X,X)就是X的方差。当样本是n维数据时，它们的协方差实际上是协方差矩阵(对称方阵)。例如，对于3维数据(x,y,z)，计算它的协方差就是：

![[公式]](https://www.zhihu.com/equation?tex=Cov%28X%2CY%2CZ%29%3D%5Cleft%5B+%5Cbegin%7Bmatrix%7D+Cov%28x%2Cx%29+%26+Cov%28x%2Cy%29%26Cov%28x%2Cz%29+%5C%5C+Cov%28y%2Cx%29%26Cov%28y%2Cy%29%26Cov%28y%2Cz%29+%5C%5C+Cov%28z%2Cx%29%26Cov%28z%2Cy%29%26Cov%28z%2Cz%29+%5Cend%7Bmatrix%7D+%5Cright%5D) 

散度矩阵定义为：

![img](https://pic2.zhimg.com/80/v2-49ec8132e7c3459b8269475c912f1ced_720w.jpg)散度矩阵

对于数据X的散度矩阵为 ![[公式]](https://www.zhihu.com/equation?tex=XX%5ET) 。其实协方差矩阵和散度矩阵关系密切，散度矩阵就是协方差矩阵乘以（总数据量-1）。因此它们的**特征值**和**特征向量**是一样的。这里值得注意的是，散度矩阵是**SVD奇异值分解**的一步，因此PCA和SVD是有很大联系。

## 3.3 特征值分解矩阵原理

(1) 特征值与特征向量

如果一个向量v是矩阵A的特征向量，将一定可以表示成下面的形式：

![[公式]](https://www.zhihu.com/equation?tex=Av%3D%5Clambda+v)

其中，λ是特征向量v对应的特征值，一个矩阵的一组特征向量是一组正交向量。

(2) 特征值分解矩阵

对于矩阵A，有一组特征向量v，将这组向量进行正交化单位化，就能得到一组正交单位向量。**特征值分解**，就是将矩阵A分解为如下式：

![[公式]](https://www.zhihu.com/equation?tex=A%3DQ%5CSigma+Q%5E%7B-1%7D)

其中，Q是矩阵A的特征向量组成的矩阵，![[公式]](https://www.zhihu.com/equation?tex=%5CSigma)则是一个对角阵，对角线上的元素就是特征值。

具体了解这一部分内容看我的[《机器学习中SVD总结》](https://link.zhihu.com/?target=https%3A//mp.weixin.qq.com/s/Dv51K8JETakIKe5dPBAPVg)文章。地址：[机器学习中SVD总结](https://link.zhihu.com/?target=https%3A//mp.weixin.qq.com/s/Dv51K8JETakIKe5dPBAPVg)

## 3.4 SVD分解矩阵原理

  奇异值分解是一个能适用于任意矩阵的一种分解的方法，对于任意矩阵A总是存在一个奇异值分解：

![[公式]](https://www.zhihu.com/equation?tex=A%3DU%5CSigma+V%5E%7BT%7D)

  假设A是一个m*n的矩阵，那么得到的U是一个m*m的方阵，U里面的正交向量被称为左奇异向量。Σ是一个m*n的矩阵，Σ除了对角线其它元素都为0，对角线上的元素称为奇异值。 ![[公式]](https://www.zhihu.com/equation?tex=V%5E%7BT%7D) 是v的转置矩阵，是一个n*n的矩阵，它里面的正交向量被称为右奇异值向量。而且一般来讲，我们会将Σ上的值按从大到小的顺序排列。

**SVD分解矩阵A的步骤：**

(1) 求![[公式]](https://www.zhihu.com/equation?tex=AA%5ET) 的特征值和特征向量，用单位化的特征向量构成 U。

(2) 求 ![[公式]](https://www.zhihu.com/equation?tex=A%5ETA) 的特征值和特征向量，用单位化的特征向量构成 V。

(3) 将 ![[公式]](https://www.zhihu.com/equation?tex=AA%5ET) 或者 ![[公式]](https://www.zhihu.com/equation?tex=A%5ETA) 的特征值求平方根，然后构成 Σ。

具体了解这一部分内容看我的[《机器学习中SVD总结》](https://link.zhihu.com/?target=https%3A//mp.weixin.qq.com/s/Dv51K8JETakIKe5dPBAPVg)文章。地址：[机器学习中SVD总结](https://link.zhihu.com/?target=https%3A//mp.weixin.qq.com/s/Dv51K8JETakIKe5dPBAPVg)

## 3.5 PCA算法两种实现方法

## **(1) 基于特征值分解协方差矩阵实现PCA算法**

输入：数据集 ![[公式]](https://www.zhihu.com/equation?tex=X%3D%5Cleft%5C%7B+x_%7B1%7D%2Cx_%7B2%7D%2Cx_%7B3%7D%2C...%2Cx_%7Bn%7D+%5Cright%5C%7D) ，需要降到k维。

1) 去平均值(即去中心化)，即每一位特征减去各自的平均值。

2) 计算协方差矩阵 ![[公式]](https://www.zhihu.com/equation?tex=%5Cfrac%7B1%7D%7Bn%7DXX%5ET),注：这里除或不除样本数量n或n-1,其实对求出的特征向量没有影响。

3) 用特征值分解方法求协方差矩阵![[公式]](https://www.zhihu.com/equation?tex=%5Cfrac%7B1%7D%7Bn%7DXX%5ET) 的特征值与特征向量。

4) 对特征值从大到小排序，选择其中最大的k个。然后将其对应的k个特征向量分别作为行向量组成特征向量矩阵P。

5) 将数据转换到k个特征向量构建的新空间中，即Y=PX。

**总结：**

1)关于这一部分为什么用 ![[公式]](https://www.zhihu.com/equation?tex=%5Cfrac%7B1%7D%7Bn%7DXX%5ET) ,这里面含有很复杂的线性代数理论推导，想了解具体细节的可以看下面这篇文章。

[CodingLabs - PCA的数学原理](https://link.zhihu.com/?target=http%3A//blog.codinglabs.org/articles/pca-tutorial.html)

2)关于为什么用特征值分解矩阵，是因为 ![[公式]](https://www.zhihu.com/equation?tex=%5Cfrac%7B1%7D%7Bn%7DXX%5ET) 是方阵，能很轻松的求出特征值与特征向量。当然，用奇异值分解也可以，是求特征值与特征向量的另一种方法。

**举个例子：**

![[公式]](https://www.zhihu.com/equation?tex=X%3D%5Cleft%28+%5Cbegin%7Bmatrix%7D+-1+%26+-1+%260%262%260%5C%5C+-2%260%260%261%261+%5Cend%7Bmatrix%7D+%5Cright%29) 

以X为例，我们用PCA方法将这两行数据降到一行。

1)因为X矩阵的每行已经是零均值，所以不需要去平均值。

2)求协方差矩阵：

![[公式]](https://www.zhihu.com/equation?tex=C%3D%5Cfrac%7B1%7D%7B5%7D%5Cleft%28+%5Cbegin%7Bmatrix%7D+-1%26-1%260%262%260%5C%5C+-2%260%260%261%261+%5Cend%7Bmatrix%7D+%5Cright%29+%5Cleft%28+%5Cbegin%7Bmatrix%7D+-1%26-2%5C%5C+-1%260%5C%5C+0%260%5C%5C+2%261%5C%5C+0%261+%5Cend%7Bmatrix%7D+%5Cright%29+%3D+%5Cleft%28+%5Cbegin%7Bmatrix%7D+%5Cfrac%7B6%7D%7B5%7D%26%5Cfrac%7B4%7D%7B5%7D%5C%5C+%5Cfrac%7B4%7D%7B5%7D%26%5Cfrac%7B6%7D%7B5%7D+%5Cend%7Bmatrix%7D+%5Cright%29) 

3)求协方差矩阵的特征值与特征向量。

求解后的特征值为：

![[公式]](https://www.zhihu.com/equation?tex=%5Clambda_%7B1%7D%3D2%EF%BC%8C%5Clambda_%7B2%7D%3D%5Cfrac%7B2%7D%7B5%7D) 

对应的特征向量为：

![[公式]](https://www.zhihu.com/equation?tex=c_%7B1%7D+%5Cleft%28+%5Cbegin%7Bmatrix%7D+1%5C%5C+1+%5Cend%7Bmatrix%7D+%5Cright%29) , ![[公式]](https://www.zhihu.com/equation?tex=c_%7B2%7D+%5Cleft%28+%5Cbegin%7Bmatrix%7D+-1%5C%5C+1+%5Cend%7Bmatrix%7D+%5Cright%29) 

其中对应的特征向量分别是一个通解， ![[公式]](https://www.zhihu.com/equation?tex=c_%7B1%7D) 和 ![[公式]](https://www.zhihu.com/equation?tex=c_%7B2%7D) 可以取任意实数。那么标准化后的特征向量为：

![[公式]](https://www.zhihu.com/equation?tex=+%5Cleft%28+%5Cbegin%7Bmatrix%7D+%5Cfrac%7B1%7D%7B%5Csqrt%7B2%7D%7D%5C%5C+%5Cfrac%7B1%7D%7B%5Csqrt%7B2%7D%7D+%5Cend%7Bmatrix%7D+%5Cright%29) , ![[公式]](https://www.zhihu.com/equation?tex=+%5Cleft%28+%5Cbegin%7Bmatrix%7D+-%5Cfrac%7B1%7D%7B%5Csqrt%7B2%7D%7D%5C%5C+%5Cfrac%7B1%7D%7B%5Csqrt%7B2%7D%7D+%5Cend%7Bmatrix%7D+%5Cright%29) 

4)矩阵P为：

![[公式]](https://www.zhihu.com/equation?tex=P%3D%5Cleft%28+%5Cbegin%7Bmatrix%7D+%5Cfrac%7B1%7D%7B%5Csqrt%7B2%7D%7D%26%5Cfrac%7B1%7D%7B%5Csqrt%7B2%7D%7D%5C%5C+-%5Cfrac%7B1%7D%7B%5Csqrt%7B2%7D%7D%26%5Cfrac%7B1%7D%7B%5Csqrt%7B2%7D%7D%5C%5C+%5Cend%7Bmatrix%7D+%5Cright%29) 

5)最后我们用P的第一行乘以数据矩阵X，就得到了降维后的表示：

![[公式]](https://www.zhihu.com/equation?tex=Y%3D%5Cleft%28+%5Cbegin%7Bmatrix%7D+%5Cfrac%7B1%7D%7B%5Csqrt%7B2%7D%7D+%26+%5Cfrac%7B1%7D%7B%5Csqrt%7B2%7D%7D+%5Cend%7Bmatrix%7D+%5Cright%29+%5Cleft%28+%5Cbegin%7Bmatrix%7D+-1+%26+-1%26+0%262%260%5C%5C+-2%260%260%261%261+%5Cend%7Bmatrix%7D+%5Cright%29+%3D+%5Cleft%28+%5Cbegin%7Bmatrix%7D+-%5Cfrac%7B3%7D%7B%5Csqrt%7B2%7D%7D+%26+-+%5Cfrac%7B1%7D%7B%5Csqrt%7B2%7D%7D+%260%26%5Cfrac%7B3%7D%7B%5Csqrt%7B2%7D%7D+%26+-%5Cfrac%7B1%7D%7B%5Csqrt%7B2%7D%7D+%5Cend%7Bmatrix%7D+%5Cright%29) 

![img](https://pic2.zhimg.com/80/v2-f5b0a7ae6d0b400e65220a02a0f0c1c1_720w.jpg)数据矩阵X降维投影结果

**注意：如果我们通过特征值分解协方差矩阵，那么我们只能得到一个方向的PCA降维。这个方向就是对数据矩阵X从行(或列)方向上压缩降维。**

## **(2) 基于SVD分解协方差矩阵实现PCA算法**

输入：数据集 ![[公式]](https://www.zhihu.com/equation?tex=X%3D%5Cleft%5C%7B+x_%7B1%7D%2Cx_%7B2%7D%2Cx_%7B3%7D%2C...%2Cx_%7Bn%7D+%5Cright%5C%7D) ，需要降到k维。

1) 去平均值，即每一位特征减去各自的平均值。

2) 计算协方差矩阵。

3) 通过SVD计算协方差矩阵的特征值与特征向量。

4) 对特征值从大到小排序，选择其中最大的k个。然后将其对应的k个特征向量分别作为列向量组成特征向量矩阵。

5) 将数据转换到k个特征向量构建的新空间中。

在PCA降维中，我们需要找到样本协方差矩阵 ![[公式]](https://www.zhihu.com/equation?tex=XX%5ET) 的最大k个特征向量，然后用这最大的k个特征向量组成的矩阵来做低维投影降维。可以看出，在这个过程中需要先求出协方差矩阵 ![[公式]](https://www.zhihu.com/equation?tex=XX%5ET),当样本数多、样本特征数也多的时候，这个计算还是很大的。当我们用到SVD分解协方差矩阵的时候，SVD有两个好处：

1) 有一些SVD的实现算法可以先不求出协方差矩阵 ![[公式]](https://www.zhihu.com/equation?tex=XX%5ET) 也能求出我们的右奇异矩阵V。也就是说，我们的PCA算法可以不用做特征分解而是通过SVD来完成，这个方法在样本量很大的时候很有效。实际上，scikit-learn的PCA算法的背后真正的实现就是用的SVD，而不是特征值分解。

2)注意到PCA仅仅使用了我们SVD的左奇异矩阵，没有使用到右奇异值矩阵，那么右奇异值矩阵有什么用呢？

假设我们的样本是m*n的矩阵X，如果我们通过SVD找到了矩阵 ![[公式]](https://www.zhihu.com/equation?tex=X%5ETX) 最大的k个特征向量组成的k*n的矩阵 ![[公式]](https://www.zhihu.com/equation?tex=V%5ET) ,则我们可以做如下处理：

![[公式]](https://www.zhihu.com/equation?tex=X_%7Bm%2Ak%7D%5E%7B%27%7D%3DX_%7Bm%2An%7DV_%7Bn%2Ak%7D%5E%7BT%7D) 

可以得到一个m*k的矩阵X',这个矩阵和我们原来m*n的矩阵X相比，列数从n减到了k，可见对列数进行了压缩。也就是说，左奇异矩阵可以用于对行数的压缩；右奇异矩阵可以用于对列(即特征维度)的压缩。这就是我们用SVD分解协方差矩阵实现PCA可以得到两个方向的PCA降维(即行和列两个方向)。

## 4. PCA实例

（1）PCA的Python实现：

```python3
##Python实现PCA
import numpy as np
def pca(X,k):#k is the components you want
  #mean of each feature
  n_samples, n_features = X.shape
  mean=np.array([np.mean(X[:,i]) for i in range(n_features)])
  #normalization
  norm_X=X-mean
  #scatter matrix
  scatter_matrix=np.dot(np.transpose(norm_X),norm_X)
  #Calculate the eigenvectors and eigenvalues
  eig_val, eig_vec = np.linalg.eig(scatter_matrix)
  eig_pairs = [(np.abs(eig_val[i]), eig_vec[:,i]) for i in range(n_features)]
  # sort eig_vec based on eig_val from highest to lowest
  eig_pairs.sort(reverse=True)
  # select the top k eig_vec
  feature=np.array([ele[1] for ele in eig_pairs[:k]])
  #get new data
  data=np.dot(norm_X,np.transpose(feature))
  return data

X = np.array([[-1, 1], [-2, -1], [-3, -2], [1, 1], [2, 1], [3, 2]])

print(pca(X,1))
```

上面代码实现了对数据X进行特征的降维。结果如下：

![img](https://pic4.zhimg.com/80/v2-cff33e89e1eb2022e0f6565087d80c6f_720w.jpg)

（2）用sklearn的PCA与我们的PCA做个比较：

```python3
##用sklearn的PCA
from sklearn.decomposition import PCA
import numpy as np
X = np.array([[-1, 1], [-2, -1], [-3, -2], [1, 1], [2, 1], [3, 2]])
pca=PCA(n_components=1)
pca.fit(X)
print(pca.transform(X))
```

结果如下：

![img](https://pic2.zhimg.com/80/v2-156a9a8d46c8411028d3a0358b34c1cd_720w.jpg)

搞了半天结果不是很一样啊！分析一下吧！

sklearn中的PCA是通过svd_flip函数实现的，sklearn对奇异值分解结果进行了一个处理，因为ui*σi*vi=(-ui)*σi*(-vi)，也就是u和v同时取反得到的结果是一样的，而这会导致通过PCA降维得到不一样的结果（虽然都是正确的）。具体了解可以看参考文章9或者自己分析一下sklearn中关于PCA的源码。

## 5. PCA的理论推导

PCA有两种通俗易懂的解释：(1)最大方差理论；(2)最小化降维造成的损失。这两个思路都能推导出同样的结果。

我在这里只介绍最大方差理论：

![img](https://pic2.zhimg.com/80/v2-228997babc87e98cbc6cc4281cf986d9_720w.jpg)

在信号处理中认为信号具有较大的方差，噪声有较小的方差，信噪比就是信号与噪声的方差比，越大越好。样本在u1上的投影方差较大，在u2上的投影方差较小，那么可认为u2上的投影是由噪声引起的。

​     因此我们认为，最好的k维特征是将n维样本点转换为k维后，每一维上的样本方差都很大。

​     比如我们将下图中的5个点投影到某一维上，这里用一条过原点的直线表示（数据已经中心化）：

![img](https://pic4.zhimg.com/80/v2-9d2ae3938c931df5846d4d1169f6326f_720w.jpg)

假设我们选择两条不同的直线做投影，那么左右两条中哪个好呢？根据我们之前的方差最大化理论，左边的好，因为投影后的样本点之间方差最大（也可以说是投影的绝对值之和最大）。

计算投影的方法见下图：

![img](https://pic4.zhimg.com/80/v2-879762c603ddc4d8f333626cefb46b53_720w.jpg)

图中，红色点表示样例，蓝色点表示在u上的投影，u是直线的斜率也是直线的方向向量，而且是单位向量。蓝色点是在u上的投影点，离原点的距离是<x,u>（即 ![[公式]](https://www.zhihu.com/equation?tex=X%5ETU) 或者 ![[公式]](https://www.zhihu.com/equation?tex=U%5ETX) ）。

## 6. 选择降维后的维度K(主成分的个数)

如何选择主成分个数K呢？先来定义两个概念：

![img](https://pic2.zhimg.com/80/v2-6a8e8ee1840b8515fa149f07a5fd2439_720w.jpg)

选择不同的K值，然后用下面的式子不断计算，选取能够满足下列式子条件的最小K值即可。

![img](https://pic1.zhimg.com/80/v2-6c90b8a3ebfbd910026fcc3220732ac8_720w.jpg)

其中t值可以由自己定，比如t值取0.01，则代表了该PCA算法保留了99%的主要信息。当你觉得误差需要更小，你可以把t值设置的更小。上式还可以用SVD分解时产生的S矩阵来表示，如下面的式子：

![img](https://pic4.zhimg.com/80/v2-7ac10fd4f9ef481be16b7ac9fb8ec40f_720w.jpg)

## Reference:

(1) [http://blog.csdn.net/zhongkelee/article/details/44064401](https://link.zhihu.com/?target=http%3A//blog.csdn.net/zhongkelee/article/details/44064401)

(2) [机器学习之PCA主成分分析 - steed灬 - 博客园](https://link.zhihu.com/?target=https%3A//www.cnblogs.com/steed/p/7454329.html)

(3) [简单易学的机器学习算法——主成分分析(PCA)](https://link.zhihu.com/?target=https%3A//blog.csdn.net/google19890102/article/details/27969459)

(4) [机器学习实战之PCA - 笨鸟多学 - 博客园](https://link.zhihu.com/?target=https%3A//www.cnblogs.com/zy230530/p/7074215.html)

(5) [机器学习中的数学(5)-强大的矩阵奇异值分解(SVD)及其应用 - LeftNotEasy - 博客园](https://link.zhihu.com/?target=http%3A//www.cnblogs.com/LeftNotEasy/archive/2011/01/19/svd-and-applications.html)

(6) [从PCA和SVD的关系拾遗](https://link.zhihu.com/?target=https%3A//blog.csdn.net/Dark_Scope/article/details/53150883)

(7) [CodingLabs - PCA的数学原理](https://link.zhihu.com/?target=http%3A//blog.codinglabs.org/articles/pca-tutorial.html)

(8) [PCA(主成分分析)python实现](https://link.zhihu.com/?target=https%3A//www.jianshu.com/p/4528aaa6dc48)

(9) [主成分分析PCA（Principal Component Analysis）在sklearn中的应用及部分源码分析](https://link.zhihu.com/?target=https%3A//www.cnblogs.com/lochan/p/7001907.html)




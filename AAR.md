[toc]

#  简历项目

## 空中加油项目

### 1.控制算法

#### 固定翼飞机模型

状态量一共是有12维度，位置信息NED，姿态信息RPY，姿态变化率pqr以及导航方程组V $\alpha$ $\beta$

力方程组 运动学 力矩和导航

控制量一共是4个维度，控制面包括升降舵，油门，方向舵和副翼 e t r a。

设计PI控制器，Ki和Kp位置，使用的是x和位置误差，具体的Kp和Ki通过LQR控制器的方式去求。系统增广的时候加入状态信息，更好的控制，因为只控制位置误差大，引入状态和速度。



1. **力方程组（Force Equations）**：
   $$
   重力：F_{\text{重力}} = m \cdot g\\
   升力：F_{\text{升力}} = \frac{1}{2} \cdot \rho \cdot V^2 \cdot S \cdot C_L\\
   阻力：F_{\text{阻力}} = \frac{1}{2} \cdot \rho \cdot V^2 \cdot S \cdot C_D\\
   推力：F_{\text{推力}} = T
   $$
   
2. **力矩方程组（Moment Equations）**：
   $$
   - 绕纵轴的力矩：M_{\text{绕纵轴}} = q \cdot S \cdot c \cdot C_m \\
   - 绕横轴的力矩：M_{\text{绕横轴}} = p \cdot S \cdot b \cdot C_l \\
   - 绕垂直轴的力矩：M_{\text{绕垂直轴}} = r \cdot S \cdot b \cdot C_n
   $$
   
3. **运动方程组（Motion Equations）**：
   $$
   - 飞机的加速度：a = \frac{F_{\text{合力}}}{m}\\
   - 飞机的速度变化：\frac{dV}{dt} = a\\
   - 飞机的位置变化：\frac{dS}{dt} = V
   $$
   
4. **导航方程组（Navigation Equations）**：
   $$
   - 导航坐标系中的速度：V_n = V \cdot \cos(\theta)\\
   - 导航坐标系中的航向：\theta_n = \theta\\
   - 导航坐标系中的位置：x_n = x
   $$
   

$$
这些公式涉及了各种力和运动变量，其中 $m$ 是飞机质量，$ g $ 是重力加速度，$\rho$ 是空气密度，$V$ 是飞机速度，$S$ 是气动参考面积，$C_L$ 是升力系数，$C_D$ 是阻力系数，$T$ 是推力，$q$、$p$、$r$ 分别是飞机绕三个轴的角速度，$c$ 和 $b$ 是机翼和机身的长度，$x$ 是飞机的位置，$\theta$ 是飞机的航向，$V_n$ 是导航坐标系中的速度，$\theta_n$ 是导航坐标系中的航向，$x_n$ 是导航坐标系中的位置。
$$



这些公式只是飞机动力学和运动的基本原理，实际飞行动力学模型可能更加复杂，考虑了更多的因素和参数。

横向方程：
$$
epos(东) phi(滚转) psi（偏航）beta（侧滑角）p（roll rate）r（yaw rate）Ail（roll）Rud（yaw）\\
控制量 a和r
$$


纵向方程：   
$$
npos(北) h（高度） theta（pitch） Vt（空速） alpha（攻角） q（pitch） Thr（油门） Ele（升降舵）\\
控制量是 t和e
$$


```matlab
% linearized model : x_dot = A * x + B * u
%   
%   ----State Variables --------                          
%01      x = [ npos  ( ft )        - north position              
%02            epos  ( ft )        - east position    
%03            h     ( ft )        - height 
%04            phi   ( rad )       - Euler angle  (roll)   
%05            theta ( rad )       - Euler angle  (pitch)     
%06            psi   ( rad )       - Euler angle  (yaw)  
%07            Vt    ( ft/sec)     - total speed   
%08            alpha ( rad )       - angle of attack   
%09            beta  ( rad )       - sideslip angle 
%10            p     ( rad/sec )   - roll rate   
%11            q     ( rad/sec )   - pitch rate
%12            r     ( rad/sec )   - yaw rate              
%13            Thr   ( - )         - throttle actuator  
%14            Ele   ( - )         - elevon actuator    
%15            Ail   ( - )         - aileron actuator  
%16            Rud   ( - )         - rudder actuator  
%17            Q     ( ft )        - dynamic pressure  
%18            Ps    ( ft )        - static pressure   
%          ];            
%                                                         
%   ---- Control Variables --------                       
%      u = [ delta_t   ( lbs )     - throttle setting  1000~19000   
%            delta_e   ( deg )     - elevon deflection  +-30    
%            delta_a   ( deg )     - aileron deflection +-30    
%            delta_r   ( deg )     - rudder deflection  +-30
%           ];   

%%-------------------Longitudinal equation-------------------------------%%

% linearized model : x_lon_dot = A_lon * x_lon + B_lon * u_lon
%   
%   ----State Variables --------  
%   01.npos , 02.h , 03.theta , 04.Vt , 05.alpha , 06.q , 07.Thr , 08.Ele
%                                                         
%   ---- Control Variables --------  
%   delta_t delta_e
%
%   ---- Output --------  
%   C_lo_xd_h  -  npos , h
%

A_lon=A([1,3,5,7,8,11,13,14],[1,3,5,7,8,11,13,14]);
B_lon=B([1,3,5,7,8,11,13,14],1:2);
C_lon_xd_h=[1 zeros(1,7);
    0 1 zeros(1,6)];

%增广系统矩阵，加入h和xd的误差积分项
AA_lon=[A_lon,zeros(8,2);-C_lon_xd_h,zeros(2,2)];
BB_lon=[B_lon;zeros(2,2)];
Q_lon=diag([4 10 10 1 10 10 0 0 1 3]);

%%%R越大相应的输入量越小，控制越弱，响应时间越长
R_lon=diag([50 50]);
[k_lon,p_lon,e_lon]=lqr(AA_lon,BB_lon,Q_lon,R_lon);

%eig(AA_lon-BB_lon*k_lon)

Kp_lon=k_lon(:,1:8);
Ki_lon=-k_lon(:,9:10);


%%-------------------lateral equation-------------------------------%%

% linearized model : x_la_dot = A_la * x_la + B_la * u_la
%   
%   ----State Variables --------  
%   01.epos , 02.phi , 03.psi , 04.beta , 05.p , 06.r , 07.Ail , 08.Rud 
%                                                         
%   ---- Control Variables --------  
%   delta_a delta_r
%
%   ---- Output --------  
%   C_la_yd  -  epos
%

A_la=A([2,4,6,9,10,12,15,16],[2,4,6,9,10,12,15,16]);
B_la=B([2,4,6,9,10,12,15,16],3:4);
C_la_yd=[1 zeros(1,7)];

%增广系统矩阵，加入yd的误差积分项
AA_la=[A_la,zeros(8,1);-C_la_yd,zeros(1,1)];
BB_la=[B_la;zeros(1,2)];
Q_la=diag([10 2 4 4 2 2 0 0 4]);

%%%R越大相应的输入量越小，控制越弱，响应时间越长
R_la=diag([500 500]);
[k_la,p_la,e_la]=lqr(AA_la,BB_la,Q_la,R_la);

%eig(AA_la-BB_la*k_la)
Kp_la=k_la(:,1:8);
Ki_la=-k_la(:,9);

%%-------------------total equation-------------------------------%%
Kp=zeros(4,18);
Kp(1:2,[1,3,5,7,8,11,13,14])=Kp_lon;
Kp(3:4,[2,4,6,9,10,12,15,16])=Kp_la;

Kp(:,13)=zeros(4,1);

Ki=zeros(4,3);
Ki(1:2,1:2)=Ki_lon;
Ki(3:4,3)=Ki_la;

```

#### 四旋翼飞机模型

![[公式]](https://www.zhihu.com/equation?tex=+%5Cbegin%7Bcases%7D+%09%5Cboldsymbol%7B%5Cdot%7Bp%7D%7D%5Ee%3D%5Cboldsymbol%7Bv%7D%5Ee%5C%5C+%09%5Cboldsymbol%7B%5Cdot%7Bv%7D%7D%5Ee%3Dg%5Cboldsymbol%7Be%7D_3-%5Cfrac%7Bf%7D%7Bm%7D%5Cboldsymbol%7BR%7D_%7Bb%7D%5E%7Be%7D%5Cboldsymbol%7Be%7D_3%5C%5C+%09%5Cboldsymbol%7B%5Cdot%7B%5CvarTheta%7D%7D%3D%5Cboldsymbol%7BW%7D%5Ccdot+%5Cboldsymbol%7B%5Comega+%7D%5Eb%5C%5C+%09%5Cboldsymbol%7BJ%5Cdot%7B%5Comega%7D%7D%5Eb%3D-%5Cboldsymbol%7B%5Comega+%7D%5Eb%5Ctimes+%5Cboldsymbol%7BJ%5Comega+%7D%5Eb%2B%5Cboldsymbol%7BG%7D_%7B%5Cboldsymbol%7Ba%7D%7D%2B%5Cboldsymbol%7B%5Ctau+%7D%5C%5C+%5Cend%7Bcases%7D++)

​	

这个是以欧拉角进行的表示。

![image-20230823153301299](assets/image-20230823153301299.png)





#### 汽车模型

#### 视觉伺服控制

$$
\frac{dp}{dt}=\omega\cross{p}+v
$$

在既有旋转又有平移的系统中，位置对时间的微分=角速度叉乘位置+速度

总的来说两点：雅各比矩阵对应控制关系，设计控制器让其指数衰减，就ok了

视觉伺服的核心，控制量速度角速度和s的关系（s就是图像中的坐标），只要建立起来雅各比矩阵就行

![image-20230822171833624](assets/image-20230822171833624.png)

雅各比矩阵是下面的建立起来的

![image-20230822171910381](assets/image-20230822171910381.png)

#### PID控制器

怎么调参的，示例。

#### LQR控制器

![image-20230821175401908](assets/image-20230821175401908.png)

simulation pace控制仿真的速度，固定步长

系统中的ABQR都是已知的，这里需要计算反馈矩阵K，K是由P得到的，P就是通过ABQR解出来的。

![image-20230814195135967](\assets\image-20230814195135967.png)

https://blog.csdn.net/tianzy16/article/details/87919313

具体的LQR方程的推导。

好理解的思路是，通过直接设置
$$
u=-Kx
$$
把u带入到
$$
J=1/2*\int{x^TQx+u^TRu}dt=1/2*\int{x^T(Q+K^TPK)xdt}
$$
再设计,就是把后面那一堆从积分号里面解放出来
$$
\frac{d}{dt}{x^TPx} = -x^T(Q+K^TPK)x   (*)
$$

$$
J=-\frac{1}{2} \int \frac{d}{dt}{x^T P x}dt=\frac{1}{2}x^T(0)Px(0)
$$

因为t趋于无穷的时候x(t)趋于0，所以就是上式。

把式子(*)拆开得到ABKPQR的方程，设计
$$
K=R^{-1}B^TP
$$
解出P就能知道K，K带入化简就能得到黎卡提方程，所以先给定QR就能根据黎卡提方程得到P，进而得到K。



#### ILC迭代学习控制器



### 2.感知算法

#### 卡尔曼滤波算法

#### YOLOV5网络架构

### 3.UE4的使用及渲染相关的知识

#### 引擎相关

1. **.build.cs文件？**

`.Build.cs` 文件是用于定义UE4插件或项目模块的构建规则的脚本文件。每个插件或项目模块都需要一个对应的 `.Build.cs` 文件，以指定其依赖项、包含的源代码文件、编译选项等信息。

.ini是配置文件 引擎相关的配置

.uasset和.uexp ubulk umap

uasset资源文件的扩展名，包括一些网格体，材质，动画，纹理等等的资源数据，比较小是框架配置信息

uexp扩展数据文件的扩展名，配合上面的资源文件使用，由于版本和编译的问题，分离更有利于资源的管理，比较大，是实际的数据。

ubulk存储资源的原始二进制数据

umap存储关卡和地图文件

2. generate.h 反射是什么

当一个头文件中 include “xxx.generated.h“，意味着这个头文件加入了反射系统。那些 UPROPERTY, UFUNCTION 之类的宏，也标记着这些方法属性等等加入了 UE4 的反射系统，加入了反射系统，UE4 才能帮你做 GC（垃圾回收），你才能实现蓝图、C++ 通信等等很多功能。

3. **虚函数是UFunction么 Uclass是啥**

4. **宏定义**

5. [**反射机制**](https://www.unrealengine.com/en-US/blog/unreal-property-system-reflection?sessionInvalidated=true)

   反射是程序的一种能力，借助于它可以在运行时查看自身。作为虚幻引擎中的基础技术，它相当有用，增强了众多的系统比如编辑器中的属性面板，对象序列化，垃圾回收，网络对象传输以及蓝图脚本和C++之间的通信等。不过C++语言本身并不提供任何形式的反射，因此虚幻引擎实现了一套自己的反射系统，通过它来收集，查询和修改C++中的类，结构，函数，成员变量和枚举的信息。在本文中我们提到反射通常是指属性系统，而不是图形学中的概念。

   反射系统是可选的。如果你希望某些类型或者属性对反射系统可见，那么就必须给它们加上修饰宏，这样在编译工程时Unreal Header Tool (UHT) 才会去收集这些信息。

   Unreal Build Tool (UBT) 和 Unreal Header Tool (UHT)在实现运行时的反射功能中扮演着核心的角色。UBT的工作就是扫描头文件，如果一个头文件包含至少一个反射类型则记录该头文件所在的模块。如果这些头文件在编译之后发生改变，UHT就会被唤起收集并更新对应的反射数据。UHT解析头文件，创建反射数据集合，然后生成包含反射数据（包含在每个模块都有的.generated.inl里）以及各类辅助类和函数（包含在每个头文件对应的.generated.h里）的C++代码。

   之所以通过生成的C++代码来保存反射信息，一个主要的好处是这样可以确保这些信息和最终的二进制文件保持同步。把反射信息和引擎代码一起编译，并在启动时通过C++表达式来计算成员的偏移等信息，而不是逆向工程某个特定的平台/编译器/优化选项的组合，这样你永远都不会加载到错误的反射信息。UHT作为一个独立的程序，它不会修改任何生成的头文件，这样就避免了在UE3脚本编译中经常被抱怨的先有蛋还是先有鸡这样的问题。

6. **多个模块之间的依赖**
   组织模块的描述文件有以下几种：

   [ProjectName].uproject文件：项目描述文件，里面描述了Module的类型，加载时机等。
   [PluginName].uplugin文件：插件描述文件，描述了插件中的Module，格式与 .uproject文件相同。
   [ModuleName].build.cs文件：主要描述所在Module的编译环境。
   [ProjectName].Target.cs文件：游戏的编译配置文件，描述游戏依赖的Module
   [ProjectName]Editor.Target.cs文件：编辑器编译配置文件，描述依赖的Module

7. **游戏引擎由工具架构和运行时组件组成（Tool+RunTime），继续细分又可以把运行时组件分为4层。故总体是五层架构.**

   - [Tool Layer 工具层](https://devpress.csdn.net/aws-game/63d8c631406cc11597718976.html?spm=1001.2101.3001.6650.5&utm_medium=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~activity-5-123650897-blog-126901784.235^v32^pc_relevant_default_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~activity-5-123650897-blog-126901784.235^v32^pc_relevant_default_base3&utm_relevant_index=10#Tool_Layer__8)

     - 提供可视化界面和接口给使用引擎的人员。

       这层也处理各种animation、mesh等资产的第三方格式导入导出（资产管道）

   - [Function Layer 功能层](https://devpress.csdn.net/aws-game/63d8c631406cc11597718976.html?spm=1001.2101.3001.6650.5&utm_medium=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~activity-5-123650897-blog-126901784.235^v32^pc_relevant_default_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~activity-5-123650897-blog-126901784.235^v32^pc_relevant_default_base3&utm_relevant_index=10#Function_Layer__12)

     - 物理，渲染，动画都在这层

     - Tick又分为tickLogic和tickRender。分别处理逻辑和渲染。

       引擎跑起来的时候，先进行Logic物理计算下一帧的世界状态，然后将计算好的内容Render到二维平面。故称logic和render为两大神兽

       这里注意写引擎代码的时候，表现绘制render（裁剪、光照、shader……）一定要和逻辑logic分开

       此外注意在看引擎代码的时候，一定要时刻记住引擎采用的是多核架构，是多线程在跑（其中如何协调具有依赖关系的两个job是难点）

   - [Resource Layer 资源层](https://devpress.csdn.net/aws-game/63d8c631406cc11597718976.html?spm=1001.2101.3001.6650.5&utm_medium=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~activity-5-123650897-blog-126901784.235^v32^pc_relevant_default_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~activity-5-123650897-blog-126901784.235^v32^pc_relevant_default_base3&utm_relevant_index=10#Resource_Layer__24)

     - 资源从别的软件格式转换到对引擎来说比较高效的格式，每个游戏资产具有唯一的识别号（GUID）用于资产之间依赖记录。

       负责存储联系不同的游戏资产，管理资产实时的生命周期（什么时候加载卸载、GC、LOD延迟加载等）。

       如材质，纹理和mesh的资产依赖记录、

       如不需要的资产回收和延迟加载（deferred loading，如远处的景等到人物靠近了才进行加载）

   - [Core Layer 核心层](https://devpress.csdn.net/aws-game/63d8c631406cc11597718976.html?spm=1001.2101.3001.6650.5&utm_medium=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~activity-5-123650897-blog-126901784.235^v32^pc_relevant_default_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~activity-5-123650897-blog-126901784.235^v32^pc_relevant_default_base3&utm_relevant_index=10#Core_Layer__32)

     - 通用功能的集合。

       如内存管理，垃圾回收，自定义数据结构及算法，矩阵计算等数学库。

       这层的代码要精心设计，因其对效率要求很高。

       内存管理要做到效率高，底层逻辑只有三条：

       1. 数据尽可能都放在一起
       2. 读数据的时候尽可能让读的顺序和物理存放的顺序一致
       3. 抹除数据的时候尽可能一次抹除一片，效率比一个一个抹除要高

   - [Platform Layer 平台层](https://devpress.csdn.net/aws-game/63d8c631406cc11597718976.html?spm=1001.2101.3001.6650.5&utm_medium=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~activity-5-123650897-blog-126901784.235^v32^pc_relevant_default_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~activity-5-123650897-blog-126901784.235^v32^pc_relevant_default_base3&utm_relevant_index=10#Platform_Layer__43)

     - 使引擎能够兼容各种硬件平台，实现引擎的平台无关性

       由于不同游戏平台对同一个文件的处理可能不一样。如Win和Mac路径的写法。更严重的是硬件架构都可能不同（如PS3具有多个协处理器SPU，需要设计一个计算具体是跑在哪个核上）。所以需要一个平台独立层运行在各层之下，包装操作系统调用和其它API，保证引擎在不同硬件平台上达到相同的运行效果

       可以通过虚函数、定义不同平台的宏等方法来实现

       RHI（Render Hardware Interface）就是做平台层封装的工作

   - [第三方中间件](https://devpress.csdn.net/aws-game/63d8c631406cc11597718976.html?spm=1001.2101.3001.6650.5&utm_medium=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~activity-5-123650897-blog-126901784.235^v32^pc_relevant_default_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromBaidu~activity-5-123650897-blog-126901784.235^v32^pc_relevant_default_base3&utm_relevant_index=10#Platform_Layer__43)

     - 在上述五层的构造中，都由可能使用到现成的第三方中间件。数据结构和算法，碰撞和物理，图形，角色动画，人工智能，生物力学……这些都有现成的优秀第三方库可以使用

   

   游戏引擎可以分为五层架构，从下往上分别是：平台层、核心层、资源层、功能层、工具层。其中前四层属于runtime：运行时组件。工具层为引擎的工具架构

   只允许上层调用下层接口，避免出现循环依赖

   基本所有引擎的架构都是由此基本架构延申。但不同游戏类型的游戏引擎存在差异（一个具体的游戏引擎通常是为了某类型的游戏设计的）

8. **什么是渲染管线**

   渲染管线（渲染[流水线](https://so.csdn.net/so/search?q=流水线&spm=1001.2101.3001.7020)）是将三维场景模型转换到屏幕像素空间输出的过程。图形渲染管线接受一组3D坐标，然后把它们转变为屏幕上的有色2D像素输出。

   ![img](https://img-blog.csdnimg.cn/28a95f67229841bc9c6ae052943648be.png)

   **流水线可抽象为三个阶段：应用阶段、几何阶段、光栅化阶段。**

   - **应用阶段**：这是一个由开发者完全控制的阶段，在这一阶段将进行数据准备，并通过CPU向GPU输送数据，例如顶点数据、摄像机位置、视锥体数据、场景模型数据、光源等等；此外，为了提高渲染性能，还会对这些数据进行处理，比如剔除不可见物体；最后还要设置每个模型的渲染状态，这些渲染状态包括但不限于所使用的材质、纹理、shader等。**这一阶段最重要的输出是渲染所需的几何信息，即渲染图元，通俗来讲渲染图元可以是点、线、面等。**
   - **几何阶段**：几何阶段运行在GPU中，几何阶段用于处理我们要绘制的几何相关事情，它和每个渲染图元打交道。几何阶段最重要的任务是将顶点坐标变换到屏幕空间中。后面会对几何阶段进行更详细的表述。
   - **光栅化阶段**：光栅化阶段运行在GPU中，其主要任务是决定每个渲染图元中哪些像素应该被绘制在屏幕上，它需要对上一阶段得到的逐顶点数据进行插值，然后进行逐像素处理。

   应用阶段：开发者控制，起点是CPU，CPU和GPU的通信即是应用阶段。

   - 加载

     大多数显卡没有直接访问RAM的能力，将数据加载到显存中使GPU能更快的访问这些数据。当把数据加载到显存后，内存中的数据便可以释放了，但对于一些还需要使用的数据则需要继续保留在内存中，如CPU需要网格数据进行碰撞检测。

   - 设置渲染状态

     渲染状态的一个通俗解释就是，定义了场景中的网格是怎样被渲染的。例如，使用哪个顶点着色器/片段着色器、光源属性、材质等。如果不设置渲染状态，那所有的网格将使用同一种渲染，显然这是不希望得到的结果

   - 调用Draw Call进行渲染

     当所有的数据准备好后，CPU就需要调用一个渲染指令告诉GPU，按照上述设置进行渲染，这个渲染命令就是Draw Call。Draw Call命令仅仅会指向一个需要被渲染的图元列表，而不包含任何材质信息，因为这些信息已经在上一个阶段中完成。执行DrawCall后GPU就会按照渲染流水线进行渲染计算，并输出到显示设备中，所执行的操作便是下述GPU渲染管线的内容。

   ![img](https://img-blog.csdnimg.cn/7bb2804b06f849ef9d8e386e2b50b8d1.png)

   

   几何阶段：

   绿色是可编程部分。GPU的很多小核心上的程序就是shader。

   - **顶点数据**：顶点数据是渲染流水线的输入，顶点数据包括顶点坐标、法线、切线、顶点颜色、纹理坐标等

   - **顶点着色器**：顶点着色器的处理单位是顶点，即对于输入的每个顶点都会调用一次顶点着色器。**顶点着色器主要功能是进行坐标系变换操**作，所输入的顶点坐标等位于模型局部坐标空间，在这一阶段需要将顶点坐标数据变换为到齐次裁剪空间。当顶点坐标被变换到齐次裁剪空间后，通常再由硬件做透视除法，最终得到归一化的设备坐标(NDC)。

   - **曲面细分着色器(可选)**：曲面细分着色器是一个可选的阶段。曲面细分是利用镶嵌化处理技术**对三角形进行细分**，以此来增加物体表面的三角面数量。

   - **几何着色器(可选)**：几何着色器也是一个可选的阶段。顶点着色器以顶点数据作为输入，**而几何着色器则以完整的图元(Primitive)作为输入数据**。例如，以三角形的三个顶点作为输入，然后输出对应的图元。与顶点着色器不能销毁或创建顶点不同，**几何着色器的主要亮点就是可以创建或销毁几何图元**，此功能让GPU可以实现一些有趣的效果。例如，根据输入图元类型扩展为一个或更多其他类型的图元，或者不输出任何图元。需要注意的是，几何着色器的输出图元不一定和输入图元相同。几何着色器的一个拿手好戏就是将一个点扩展为一个四边形(即两个三角形)。

   - **裁剪（硬件完成）**：裁剪操作就是将相机看不到的物体、顶点剔除，使其不被下一阶段处理。只有当图元完全位于视锥体内时，才会将它送到下一阶段，对于部分位于视锥体内的图元，外部的顶点将被剔除掉。由于已经知道在NDC下的顶点位置（即顶点位置在一个立方体内），因此裁剪就变得简单：只需要将图元裁剪到单位立方体内。裁剪这一步骤是硬件的固定操作，因此是不可编程的。

   - **屏幕映射（硬件完成）**：这一步输入的坐标仍是三维坐标（范围在单位立方体内），屏幕映射的任务就是将每个图元的x、y值变换到屏幕坐标系（屏幕坐标系是一个2D空间）。由于输入坐标范围在[-1,1]，因此这是一个拉伸到屏幕分辨率大小的过程。对于输入的坐标z值不做任何处理（实际上屏幕坐标系和z坐标一起构成窗口坐标系），这些值会被一起传递到光栅化阶段。

     屏幕坐标系在OpenGL和DirectX中的定义方式不同。

     OpenGL的原点在笛卡尔坐标系的原点，DirextX与之关于x轴对称。![在这里插入图片描述](https://img-blog.csdnimg.cn/0959f80b7301416cbf727a0d1e23f67e.png)

   - **三角形设置**：光栅化第的第一个流水线阶段是三角形设置，这个阶段会计算光栅化一个三角形所需的信息。说白了就是离散化，生成三角形信息，为将来找到覆盖的元素做准备

   - **三角形遍历**：检查是否覆盖，如果覆盖，覆盖部分就有一个片元，这就是找像素的过程。并且对于覆盖区域的深度进行插值。

   - **片元着色器**：前面的光栅化阶段实际上并不会影响每个像素的颜色值。

     片元着色器的输入是上一个阶段对顶点信息进行插值的结果（是根据从顶点着色器输出的数据插值得到的），而它的输出是像素颜色值。这一阶段可以完成很多重要的渲染技术，**其中最重要的技术有纹理采样、逐片光照计算等**，**覆盖片元的纹理坐标是通过前述的阶段的顶点数据插值得到的**。

   - **逐片元操作（输出合并）**：

     - 决定每个片元的可见性，这涉及到很多测试功能，例如**深度测试、模板测试**。

       - **模板测试**与之相关的是**模板缓冲**，模板测试通常用来限制渲染的区域，渲染阴影，轮廓渲染等。无论一个片元有没有经过模板测试，都可以根据模板测试和下面的深度测试结果来修改模板缓冲区。

         stencil buffer

       - 如果开启了深度测试，GPU会把该片元的深度值和已经存在于**深度缓冲区**中的深度值进行比较。通常这个值是小于等于的关系，因为我们总想显示出离相机最近的物体(不包括透明/半透明)，而那些被遮挡的就不需要出现在屏幕。如果一个片元通过了测试，那么开发者可以指定是否要用这个片元的深度值覆盖所有的深度值

     - 如果一个片元通过了所有测试，就需要把这些片元的颜色值和颜色缓冲中已有的颜色值进行混合。

9. **LOD的存储结构？**

   四叉树或者八叉树。不需要的就不展开，节省空间。

   距离剔除体积和可视化剔除体积

   二叉空间分区树BSP树

   耗时 不解决可见表面确定的问题

   用于碰撞检测 光线追踪  复杂空间场景的处理

   地形里面的LOD算法可以分为：非连续LOD模型、连续LOD模型以及节点LOD模型。
   非连续LOD模型：它实质上保存了原始模型的多个副本，每个副本对应某一特定的分辨率，所有副本构成一个金字塔模型。该模型的优点是不必在线生成模型，可视速度快；缺点是数据冗余大，容易引起几何数据的不一致性，而且由于不同分辨率之间没有任何关联，不同分辨率间的转换易引起视觉上的间跳现象。
   连续LOD模型：它是在某一时间只保留某一分辨率的模型，在实际应用中根据需要，采用一定的算法实时生成另一分辨率的模型。该模型优缺点正好与不连续LOD模型相反，即优点是没有数据冗余，能够保证几何数据的一致性和视觉连续性；缺点是需要在线生成不同分辨率的模型，算法设计复杂，可视速度慢。
   节点LOD模型：本身是一个分辨率结构。不同分辨率模型之间用节点相连，通过对节点的激活来操作相应的部件。所有节点均被激活时，实质就是一个全分辨率结构，优点是结构简单、操作方便，适合表达复杂的不连续的体模型对象。

   

OpenGL相关的基础知识

UE的插件：只需要拷贝整个plugin文件就行。

XML的格式和实时读取：

Gazebo的源码二次开发？

### 4.项目的实现

1. **实现共享内存？**

   socket，setsocket，recvfrom，check，unpack

   一个是传感器数据的共享内存

   另一个是取图的大小

   mmap的mmap函数 初始地址和空间大小

   mmap.mmap(0,66*4)

   ```python
   # struct UE4CommMemData {
   #  int Checksum;//校验位，设置为1234567890
   #  int totalNum;//最大传感器数量
   #  int WidthHeigh[64];//分辨率宽高序列，包含最多32个传感器的
   # }
   ```

   ```python
   取图
   mm=mmap.mmap(0, DataWidth*DataHeight*dim*dimSize+1+8+otherSize, 'RflySim3DImg_'+str(SeqID))
   ```

   如果是多个传感器，多线程开始

   udp的结构:第一个存入包头，剩下的检验时间戳 相对接近

   ```python
   dd = struct.unpack('4i1d',buf[0:fhead_size])#校验，包长度，包序号，总包数，时间戳
   ```

   ```python
   if not math.isclose(timeStmpStore,dd[4],rel_tol=0.00001):
   ```


2. **仿真中摄像机取图的原理是什么？**

摄像机的配置在json文件里面，包括端口和IP地址，以及图像分辨率等等参数。







各模块之间的通信：

1. UE和python之间，使用共享内存的方式读取图像数据，共享内存的大小，怎么实现的。
2. simulink和UE之间，发送模型数据过去。simunlink-python发送的模型的位置和姿态
3. python和simulink之间，UDP的方式进行通信，共享的数据是锥套相对于相机的位置，三个double数据。

yolov5网络的实现：在哪里进行视频流的调整 LoadStream这里

三次B样条插值的原理

OpenCV的基本操作

## SLAM项目

根据图像来计算相机的运动：直接法和关键点法

ORB特征：FAST提取角点，过亮或者过暗，阈值，以3个像素为半径的16个像素，连续N个超过阈值上下限。几何中心和质心的向量代表方向。 Oriented FAST

BRIEF计算描述子：128维度的描述子 01

暴力匹配和FLANN快速近似最近邻

相机2d图像 2d-2d 对极几何：极线 极点 E=t^R F=KEK(K是内参)  丢失一个维度 所以只有5个自由度 8个点好 8点法

同一个平面上的特征点，运动变化单应矩阵H

p=HP 第三行线性相关 一个点就有两个方程4个点就8个方程，缺一个维度刚好 解方程DLT直接线性变换

相机的3d点  3d-3dICP  

残差 两项都最小  旋转前后的质心差 得到R   第二项得到t

3d点和投影位置，估计相机运动 2d-3d位置 PnP



VINS-FUSION的基本原理。

相机内参的标定方法：张正友标定法

角点的检测方法：

预积分：

3D-2D，3D-3D等的计算方法

高斯牛顿法

## 测试相关



## 扫地机器人项目

项目介绍：在docker环境中，进行扫地机器人功能的开发。

分很多子模块，包括application模块，planning模块，mapping模块等大的划分。

一个模块使用一个node，包装成application，然后一个模块中根据功能需要，划分成不同的Component，具体的实现是在handler里面实现的，每一个handler注册在component里面，component注册在application里面。



applicationAPP（下面的Component注册在这里）

Debug（DebugComponent加入EventLoop中去执行）Communicator（Communication Component）......

CleanModuleControllerHandler（注册在DebugComponent中）

Process处理具体的业务





docker环境：

[ROS的基础知识](https://blog.csdn.net/weixin_39772704/article/details/131853900?spm=1001.2014.3001.5502)：一些基本的框架概念整理出来了，再补充一些语法。



[mqtt协议和protobuf协议](https://blog.csdn.net/weixin_39772704/article/details/132356499?spm=1001.2014.3001.5502)：

mqtt的概念，

protobuf的优缺点，使用的语法 xml和json文件

使用的[设计模式](https://blog.csdn.net/weixin_39772704/article/details/132036013?spm=1001.2014.3001.5502)：单例（懒汉和饿汉），观察者模式

线程池的使用，eventloop 的使用[多线程](https://blog.csdn.net/weixin_39772704/article/details/132335309?spm=1001.2014.3001.5502)相关的[概念](https://blog.csdn.net/weixin_39772704/article/details/131851040?spm=1001.2014.3001.5502)。



## 相关的机器学习算法



## 自己做一下tinyrpc或者webserver项目

shared_ptr的使用实现，线程池的使用的实现，LRU算法

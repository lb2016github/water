# water
这是一个基于学习目的而开发的游戏引擎。

## 目录结构
|目录名|描述|
|--|--|
|src|存放源代码|
|res|存放资源|
|lib|存放第三方库的lib文件|
|include|存放以来的头文件|
|3rdparty|防止第三方库的源码|

## 依赖的第三方库
引擎会依赖一些第三方库，避免重复造轮子。由于我的开发环境是vs2015和vs2019，所以lib中只存放了vc140和vc142版本的库，如果需要其他版本的，则需要自己取编译。
第三方库有：
- Boost: 有些Boost库是需要手动编译的，目前需要编译的boost库有：filesystem 
- assimp: 用来加载mesh资源。
- glfw3: 用来管理窗体系统。
- irrXML: assimp的依赖库。
- zlib: assimp的依赖库\
还有一些不需要预编译，直接以源码形式加入代码中的第三方库，这些库的代码在include目录中
- glad: 初始化
- glm: 3d数学库
- pugixml: 解析xml
- stb_image: 加载贴图
- KHR: glfw3的依赖

## 项目模块
主要包括以下几个模块：
- world：管理场景，模型等，是逻辑层的主要模块
- render：实现底层渲染模块
- filesystem：文件和文件系统模块
- math3d: 提供3d数学的相关接口
- window：实现窗体系统，并向提供相关接口
- test：一些测试模块

### render模块
对图形库做了封装，并抽象出一些典型的概念，如material, technique等。
还把整个渲染操作做了分解，划分成一个个RenderTask概念。
一个RenderTask对应一个

- mesh: mesh数据的结构
- material: 材质的数据
- technique：渲染管线的描述，指定使用的shader，shader中uniform的类型
- render_target: FrameBuffer的封装，用来实现离屏渲染
- texture：贴图的加载，绑定和管理
- render_task: 对应实际渲染过程中的一个draw_call
- light：对方向光，点光，聚光等的封装
- device：指定了一些依赖于图形库实现的接口。
- device_opengl: 对device的opengl版本实现。以后扩展图形库的时候，就需要实现device_dx, device_vulkan等。

渲染线程与主线程的交互
- RenderTask: 存放一次DrawCall的所有信息。所有的RenderTask组成了一帧的渲染。
- 主线程用两个buffer存放RenderTask信息，BackBuffer用来添加当前帧的RenderTask，完毕后置为Ready，并和FrontBuffer互换。
- 渲染线程有一个buffer，存放RenderTask。当buffer不为空的时候，渲染线程会不断的读取RenderTask，并进行渲染。渲染完毕后，拷贝主线程的FrontBuffer。


### world模块
实现了一套简陋版的ECS(Entity Component System)，除了world，其他对象都继承了ComponentObject。
- gameobejcts
    - world：单例，可以包含多个scene
    - scene：场景
    - model：模型
    - camera：相机
    - component_object: 模板实现的组件对象类，可以在申明时候包含任意多的组件
- components
    - transform_component: 管理对象的位移，旋转，缩放
    - material_component: 管理可渲染对象的材质
    - mesh_component: 管理网格数据
    - render_component: 管理渲染操作
    - shadowmap_component: 挂载到场景对象上，实现场景的shadowmap效果
    - camera_control_component: 管理相机的操作，如移动，旋转等
## 资源管理
shader，材质的管理，没有使用第三方库，而是自己实现了一套简单的管理逻辑。基本思路是
用xml文件配置文件信息，并用xsd（xml scheme)对xml的文件结构进行描述。
- .model：模型文件，指定了mesh文件和mat文件，并用model.xsd描述约束结构
- .scene: 场景文件，包括光照，模型，shadowmap等配置，并用scene.xsd描述约束结构
- .mat: 材质文件，指定了使用的technique，指定了shader参数。并用material.xsd描述约束结构
- .tech: technique文件，包含了render_state信息，shader信息。并用technique.xsd描述约束结构
- .xsd: xsd文件，用来描述xml文件结构
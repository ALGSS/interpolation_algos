# Descriptions
The source idea from https://www.cnblogs.com/arxive/p/5119632.html, 
but it's a visual studio project, business IDE and huge files to install is very uncomfortable. 
So I think can refactor to cmake the project for public users and will use easily.


# Install

## dependcies

执行根目录下的脚本:
```sh
install_thirdparties.sh
```


本项目，具体依赖的第三方库为：
* thirdparty/svpng <br/>
  https://github.com/miloyip/svpng
* thirdparty/imgui <br/>
  https://github.com/ocornut/imgui.git



# Logs

* v 2.0.0 24.6.22
  * remove outdated c++ visual framework of MFC; 
  * add imgui for algorithm ui;
  * add manual docs;
  * remove 3d view temply.


* v 1.0.2  2019.12.30 0032<br/>
  补充所依赖的gl/glaux.h等到lib目录下。一站式配齐。在VS2017下测试通过。


* v 1.0.1 WENG<br/>
  Kriging 算法实现 2维和3维地图等高线
  
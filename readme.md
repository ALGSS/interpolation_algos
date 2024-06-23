# Descriptions
This program features: 
* Inverse Distance Weighted Interpolation  
* Kriging Interpolation

The source idea from https://www.cnblogs.com/arxive/p/5119632.html, 
but it's a visual studio project, business IDE and huge files to install is very uncomfortable. 
So I think can refactor it to cmake project for public users using easily.

# Usage
```sh
# 编译好程序后, cd到二进制文件所在目录，以 data/testdata.txt, 进行克里金插值 为例说明。
./kriging_weng path_to_project_root/data/testdata.txt 1
```
备注：<br/>
第二个参数为0， 是反距离插值； 第二个参数为1， 则为克里金插值。



[data/testdata.txt](data/testdata.txt) interpolation result compare：

| Inverse Distance Weighted Interpolation           | Kriging Interpolation                        |
| ------------------------------------------------- | -------------------------------------------- |
| ![](doc/img/interpolated_result_inverse_dist.png) | ![](doc/img/interpolated_result_kriging.png) |




# Install

## Dependencies

执行根目录下的脚本:
```sh
install_thirdparties.sh
```

本项目，具体依赖的第三方库为：
* thirdparty/svpng <br/>
  https://github.com/miloyip/svpng

~~* thirdparty/imgui <br/>
  https://github.com/ocornut/imgui.git~~



## Compile

```
# cd to  this porject root dir,  and then:
mkdir build &&  cd build
cmake ..
make -j6
```



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
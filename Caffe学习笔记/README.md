# Caffe 框架学习笔记

## caffe ubuntu16.04安装

### 1 安装依赖库

sudo apt-get install -y libprotobuf-dev libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev 

sudo apt-get install -y protobuf-compiler libatlas-base-dev libhdf5-serial-dev libboost-all-dev libboost-all-dev

### 2 安装python-pip

sudo apt-get install -y python-pip

### 3 clone caffe

git clone https://github.com/BVLC/caffe.git

### 4 安装python相关安装包

sudo apt-get install -y python-numpy python-scipy python-matplotlib ipython ipython-notebook

sudo apt-get install -y python-pandas python-sympy python-nose


### 5 pip安装caffe/python/requirements.txt

pip install -r requirements.txt

### 6 修改Makefile.config

cp Makefile.config.example Makefile.config

第一处：CPU_ONLY :=1前面的#去掉，因为这里我们使用的是cpu。

第二处：

INCLUDE_DIRS :=$(PYTHON_INCLUDE) /usr/local/include /usr/include/hdf5/serial

LIBRARY_DIRS := $(PYTHON_LIB) /usr/local/lib /usr/lib/x86_64-linux-gnu/hdf5/serial

如果是opencv3，第三处：取消opencv3注释。

### 7 编译安装

sudo make -j4

sudo make test

sudo make runtest

如果出现PASSED,则安装完成。
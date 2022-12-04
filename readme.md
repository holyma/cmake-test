# linux 软件安装
```sh
# essential
apt update
apt updrade
apt install -y cmake make gdb g++ gcc build-essential
# optional
apt install -y git tmux zip
```

# vscode插件安装
```
c/c++ ; cmake ; cmake tools
```

# libtorch
``` sh
# libtorch下载：
# https://pytorch.org/get-started/locally/
```

# ~/.bashrc 配置
```sh
export LIBTORCH_HOME=/path/to/libtorch
export LD_LIBRARY_PATH=$LIBTORCH_HOME/lib:$LD_LIBRARY_PATH  # 动态库目录
export LIBRARY_PATH=$LIBTORCH_HOME/lib:$LIBRARY_PATH        # 静态库目录

# gcc,g++ find .h in dir
export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:$LIBTORCH_HOME/include:$LIBTORCH_HOME/include/torch/csrc/api/include
export C_INCLUDE_PATH=$LIBTORCH_HOME/include:$C_INCLUDE_PATH

# cmake-gcc路径
export CC=/data/apps/gcc/7.3.0/bin/gcc
export CXX=/data/apps/gcc/7.3.0/bin/g++

```
# Reference:
libtorch API:https://pytorch.org/cppdocs/api/library_root.html

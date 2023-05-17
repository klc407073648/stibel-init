# 使用方法

CMakeLists.txt 包含以下内容即可

```
# 依赖StiBel库的内容
## 选项
include(${PROJECT_SOURCE_DIR}/cmake/options.cmake)

## 3partlib和comlib
include(${PROJECT_SOURCE_DIR}/cmake/3partlib.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/comlib.cmake)

## 链接头文件和库
include(${PROJECT_SOURCE_DIR}/cmake/linklib.cmake)

# 依赖StiBel库的内容
```
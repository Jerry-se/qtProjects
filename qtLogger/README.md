# qtLogger

logger using QT

## QtMessageHandler

参考资料:
- [QMessageLogger](https://doc.qt.io/qt-6/qmessagelogger.html)
- [qInstallMessageHandler](https://doc.qt.io/qt-6/qtglobal.html#qInstallMessageHandler)

## Log4Qt

把 Log4Qt 编译成静态库
1. qmake: qmake 带有 "DEFINES+=LOG4QT_STATIC" 或者取消 `build.pri` 文件中的 `LOG4QT_STATIC` 注释。
2. cmake: cmake 带有 '-DBUILD_STATIC_LOG4CXX_LIB=ON|OFF' 参数。

将 MSVC runtime 从 MD 修改为 MT 需要修改 CMakeLists.txt 文件:
```cmake
if (POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)
...
if (MSVC)
  message(STATUS "link to static C and C++ runtime lirbary(/MT /MTd)")
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
```

使用新策略设置静态运行时：https://cmake.org/cmake/help/latest/policy/CMP0091.html

```shell
$ cd <repo clone dir>
$ mkdir build
$ cd build
$ cmake .. -DBUILD_STATIC_LOG4CXX_LIB=ON
$ cmake .. -DBUILD_SHARED_LIBS=OFF
$ cmake --build . --config Debug
$ cmake --build . --config Release
```

参考资料:
- [Log4Qt](https://github.com/MEONMedical/Log4Qt)
- [Log4Qt Original project](https://log4qt.sourceforge.net/)

## 总结

修改成 MultiThreaded 后，Debug 编译运行后有 "debug assertion failed" 问题，log4xx 系列有些社区不活跃，维护和更新不够好。

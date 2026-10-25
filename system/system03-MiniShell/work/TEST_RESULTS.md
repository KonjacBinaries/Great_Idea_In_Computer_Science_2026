# Basic 本地验收记录

验收日期：2026-10-25。运行环境：Ubuntu（WSL），GNU C++ 15.2.0，CMake 4.2.3。

## 执行命令

在本 work 目录执行：

~~~bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
~~~

配置、编译和测试命令的退出码均为 0。实际编译选项为：

~~~text
-std=c++17 -Wall -Wextra -Wpedantic
~~~

编译期间没有警告或错误。

## 测试结果

| 测试 | 结果 |
| --- | --- |
| example1（官方演示） | Passed |
| example2（空目录、空文件、echo、排序） | Passed |
| example3（touch 保留与 echo 覆盖） | Passed |
| example4（错误后继续执行） | Passed |
| example5（多词文本写入与覆盖） | Passed |
| example6（ASCII 字典序） | Passed |
| example7（echo 与 EOF） | Passed |
| example8（综合状态与多余参数） | Passed |
| example9（CRLF、空行、空白分词、exit） | Passed |
| example10（重定向语法与错误不修改状态） | Passed |
| example11（文件名边界与参数检查） | Passed |
| example12（空 echo 写入、换行、最后一行无换行的 EOF） | Passed |

CTest 实际汇总：

~~~text
100% tests passed, 0 tests failed out of 12

Total Test time (real) =   0.10 sec
~~~

完整执行日志见本地构建目录的 [CTest 日志](./build/Testing/Temporary/LastTest.log)。该目录是可重新生成的构建产物。

## 完整性检查

- 原始 8 组输入输出及比对脚本共 17 个文件，SHA-256 与课程版本逐一相同。
- [12 组输入与预期输出](./tests/README.md)已随成果保存，超过至少六组的提交要求。
- [Q1–Q5 回答](./ANSWERS.md)、[运行说明](./README.md)、[源码](./src/main.cpp)和 [CMake 配置](./CMakeLists.txt)齐全。
- 作业目录的 Git 状态仅新增 work；原始 basic、advance 和任务说明没有修改。
- 程序的模拟文件只存于内存；每个测试独立启动程序，验证新会话从空文件表开始。

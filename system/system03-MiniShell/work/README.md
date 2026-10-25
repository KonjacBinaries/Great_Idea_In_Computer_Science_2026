# MiniShell Basic 完成版

本目录是独立可构建的 Basic 提交成果。实现单层虚拟文件系统，全部文件仅存在于 `std::map<std::string, std::string>` 中。

## 编译、运行与验收

在 Ubuntu / WSL 中进入本 work 目录后运行（需要 C++17 编译器、CMake 和 diff）：

~~~bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/minishell-basic
~~~

也可以仅使用编译器：

~~~bash
g++ -std=c++17 -Wall -Wextra -Wpedantic src/main.cpp -o minishell-basic
./minishell-basic
./minishell-basic < tests/example1.in
~~~

输入 `exit` 或按 Ctrl+D（EOF）结束。默认不打印提示符，交互与文件输入使用同一套行为。每次启动的虚拟文件表均为空。

## 命令与设计

| 命令 | 行为 |
| --- | --- |
| `pwd` | 输出 / 和换行 |
| `ls` | 按 ASCII 字典序列出文件，每行一个；空目录无输出 |
| `touch 文件名` | 创建空文件；已存在时保留内容 |
| `cat 文件名` | 原样输出内容，不额外增加换行 |
| `echo [参数...]` | 参数之间合并为一个空格，末尾加换行；无参数输出一个换行 |
| `echo [参数...] > 文件名` | 创建或覆盖虚拟文件，成功时无终端输出 |
| `exit` | 结束程序；多余参数时报错并继续运行 |

文件名只能包含 ASCII 英文字母、数字、下划线、点、连字符，不能是 `.` 或 `..`。未知命令、参数数量错误、非法文件名、读取不存在的文件、重定向缺少目标或目标后有多余词，均输出一行 ERROR 并继续执行。先验证命令再改动文件，错误命令不会创建或覆盖文件。

逐行用 getline 读取输入，移除 CRLF 的行尾 `\r`，再用字符串流分词。连续空格和制表符均作为分隔；空行忽略。只有独立的 `>` 词表示 echo 重定向，例如 `echo a>b` 输出文本 a>b。Basic 不实现引号、转义、变量、通配符、子目录或管道；普通 echo 参数按原文本处理，不做真实 Shell 的展开。

touch 使用 emplace 避免清空已有内容，cat 使用 find 避免误创建文件，echo 写文件时保留末尾换行。map 的有序键直接提供 ls 的文件名顺序。

## 提交内容

- [C++17 源码](./src/main.cpp)
- [CMake 构建与测试配置](./CMakeLists.txt)
- [Q1–Q5 回答](./ANSWERS.md)
- [测试说明](./tests/README.md)：12 组独立输入与预期输出，包含原始 8 组官方测试及 4 组补充边界测试
- [本地验收记录](./TEST_RESULTS.md)

测试输入中的模拟重定向只改动内存。运行命令中的 `< tests/example1.in` 是外层真实 Shell 把测试文件接到程序标准输入。

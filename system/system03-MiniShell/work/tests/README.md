# 测试用例

每组 exampleN.in 为完整标准输入，配对的 exampleN.out 为精确预期标准输出。每组启动新的程序，因此文件表相互独立。空白行也是预期输出的一部分；cat 空文件没有输出，而无参数 echo 会输出一个换行。

1–8 组和 [比对脚本](./run_example.cmake) 从课程 basic/tests 原样复制，保留原始换行。9–12 组为补充用例。

| 编号 | 输入与预期输出 | 验证内容 |
| --- | --- | --- |
| 1 | [输入](./example1.in) / [输出](./example1.out) | 课程演示、重复 touch、写入、读取、列出文件和根目录 |
| 2 | [输入](./example2.in) / [输出](./example2.out) | 空目录、排序、空文件、三种 echo |
| 3 | [输入](./example3.in) / [输出](./example3.out) | Q5：touch 保留、echo 覆盖 |
| 4 | [输入](./example4.in) / [输出](./example4.out) | 缺失/多余参数、未知命令、非法文件名、不存在文件及错误后继续 |
| 5 | [输入](./example5.in) / [输出](./example5.out) | 多词文本、覆盖、重复 touch |
| 6 | [输入](./example6.in) / [输出](./example6.out) | ASCII 文件名排序 |
| 7 | [输入](./example7.in) / [输出](./example7.out) | 无参数 echo、EOF 结束 |
| 8 | [输入](./example8.in) / [输出](./example8.out) | 综合文件状态及参数错误 |
| 9 | [输入](./example9.in) / [输出](./example9.out) | 空白行、连续空格和制表符、CRLF、空文件 cat、exit 多余参数、exit 后不再执行 |
| 10 | [输入](./example10.in) / [输出](./example10.out) | 错误重定向不改动已有文件、不创建新文件、多重 >、非法目标 |
| 11 | [输入](./example11.in) / [输出](./example11.out) | 合法文件名边界、非 ASCII/路径/特殊字符拒绝、缺失 cat 不创建文件 |
| 12 | [输入](./example12.in) / [输出](./example12.out) | 空 echo 覆盖与新建、换行保留、a>b 作为普通词、-n 作为普通参数、最后一行无换行的 EOF |

在上一级目录运行：

~~~bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
~~~

CMake 对每组分别执行程序，并使用 `diff -u --strip-trailing-cr` 对比输出；只忽略 CRLF 与 LF 的差异，不会忽略空行或空格差异。每个测试设有 5 秒超时。

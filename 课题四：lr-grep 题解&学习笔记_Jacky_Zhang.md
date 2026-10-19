# 课题四：lr-grep 题解&学习笔记_Jacky_Zhang

`Made by Jacky_Zhang Zhehao`

**在此先行感谢一下学长们真的有在认真阅读我的题解！**真的是倍感荣幸！

这个课题能让我做出一个属于我自己的有用的小程序！选择时也是直接一眼相中了。应该会在挑战中有不小的乐趣，希望在做这个小项目中多多学一点吧 ~ 

## 个人仓库链接：

https://github.com/jackyzzh0099/lr-grep-Jacky.git

---

## 思路 & 学习笔记 & 感悟：

### 先来学习一下 Linux 里原始的`grep` 指令：

#### 一、什么是`grep`：

**`grep` 是 Linux 中非常常用的文本搜索工具。可以理解为：在文本中查找符合条件的行，并把这些行打印出来。**

#### 二、拆解命令的结构

最常见的语法是：

```bash
grep [选项] "搜索内容" 文件名
```

结合例子理解：

```bash
grep -i "error" sample.log
```

`grep`：命令本身 → 负责搜索文本。

`-i`：选项（可选） → 忽略大小写。不同选项可以改变搜索行为。

`"error"`：搜索模式 → 告诉 grep 要寻找什么。可以是普通文本，也可以是正则表达式。

`sample.log`：输入文件 → 告诉 grep 去哪里搜索。

*注意：方括号 `[选项]` 只是语法说明中的占位符，实际输入命令时通常不需要把方括号写进去。*

#### 三、最常用的 6 个选项

| 命令        | 作用            | 记忆方法              |
| --------- | ------------- | ----------------- |
| `grep -i` | 忽略大小写         | `i` = ignore case |
| `grep -n` | 显示匹配行的行号      | `n` = line number |
| `grep -v` | 显示不匹配的行（反向筛选） | `v` = invert      |
| `grep -c` | 统计匹配的行数       | `c` = count       |
| `grep -r` | 递归搜索目录中的文件    | `r` = recursive   |
| `grep -w` | 匹配完整单词        | `w` = word        |

##### **强化理解：**

###### 1. **`-w`：匹配完整单词**

假设文件中有这些内容：

```
error occurred
terror detected
error123 found
```

执行：

```bash
grep -w "error" sample.log
```

只会匹配 `error occurred` 这一行。

因为 `terror` 中的 `error` 只是一个更长单词的一部分，而 `error123` 也不是完整的 `error` 单词。

###### 2. `-r`：搜索整个目录

例如，你有一个名为 `logs` 的目录，里面有很多日志文件：

```bash
grep -r "ERROR" logs/
```

这会递归搜索 `logs/` 目录及其子目录中的文件，输出包含 `ERROR` 的匹配行。

注意使用此命令需要把文件名换成以`/`结尾的文件夹名

#### 四、`grep`可以和 Linux 的管道搭配使用

管道符 `|` 的作用：把前一个命令的标准输出，传递给后一个命令作为输入。

如：

```bash
cat sample.log | grep -i "error"  # cat 作用是输出整个文件的内容
```

等价于

```bash
grep -i "error" sample.log
```

#### 五、除此以外，再认识一个概念：正则表达式（ ERE ）

##### `grep` 默认不仅能搜索普通文本，还能识别一些特殊的搜索模式，也就是正则表达式。

例如：

```bash
grep "^boot" sample.log
```

其中 `^` 表示一行的开头，因此这条命令会查找以 `boot` 开头的行。

再比如：

```bash
grep "ok$" sample.log
```

其中 `$` 表示一行的结尾，因此它会查找以 `ok` 结尾的行。

##### 再认识几个：

| `.`             | 任意单个字符           |
| --------------- | ---------------- |
| `*`             | 前一个元素重复零次或多次     |
| `[]`            | 匹配指定字符中的一个       |
| `[0-9]`         | 一个数字             |
| `+`             | 在 ERE 中表示重复一次或多次 |
| <code>\|</code> | 在 ERE 中表示“或者”    |
| `\.`            | 匹配真正的点号          |

ERE 较为复杂，以后需要的时候再系统学习。

本来还是很好奇的。但是主要是要加油完成主线任务（捂脸…… 现在每天任务太重了！

#### 六、关于搜索内容引号的使用

1. **只搜索一个单词**，不加引号：可以

```bash
grep error sample.log
```

等价于：

```bash
grep "error" sample.log
```

因为 `error` 是一个简单的单词，Shell 会直接把它作为一个参数传给 `grep`。

2. **有空格**：建议加引号

假设要搜索 `disk full`：

```bash
grep "disk full" sample.log
```

如果不加引号：

```bash
grep disk full sample.log
```

`grep` 会把它理解为：

- `disk`：搜索内容

- `full`：第一个文件名

- `sample.log`：第二个文件名

这样就不是搜索完整的 `disk full` 了。

3. **包含特殊符号：**建议加引号

例如：

```bash
grep "^ERROR" sample.log
```

这里的双引号能防止 Shell 预先处理某些特殊字符，让 `^ERROR` 原样传给 `grep` 作为正则表达式。

不过要注意：引号不会关闭正则表达式的功能。 `grep` 仍然会把 `^` 解释为行首。

#### 七、补充一下 bash 中`echo`和`;`的知识点

##### 基础功能：在屏幕上打印出指定内容，类似`printf`

如：

```bash
echo "Hello Linux"
```

输出：

```
Hello Linux
```

但是我还观察到凌睿题目说明里还提到两句：

```bash
grep zzz sample.log; echo "exit=$?"    # 没有匹配行
grep error sample.log no-such-file; echo "exit=$?"   # 其中一个文件打不开
```

##### 搭配特殊变量`$?`使用：

###### `$?`：Shell 的特殊变量，表示上一条命令的**退出状态码。**

**常见的退出状态码：**

| 状态码   | 含义                          |
| ----- | --------------------------- |
| `0`   | 命令执行成功                      |
| `1`   | 通常表示未找到匹配项，或其他一般性错误，具体取决于命令 |
| 其他非零值 | 通常表示某种错误或特殊情况，具体含义取决于命令     |

对于 `grep` 来说：

- `0`：找到匹配行。

- `1`：没有找到匹配行。

- `2`：发生错误，例如文件无法读取。

###### `;`：Shell 的命令分隔符。

它表示：先执行第一条命令，再执行第二条命令。

因此，第一条条命令中的：

```bash
grep zzz sample.log; echo "exit=$?"
```

可以理解为：

```
先搜索 zzz
然后打印 grep 的退出状态码
```

注意： `$?` 只保存最近执行的前一条命令的状态码。所以这里必须紧跟在 `grep` 后面读取；如果中间又执行了其他命令，`$?` 就会变成那条命令的状态码。

第二条指令相似，不多赘述。

---

### OK 原始的 `grep` 了解得差不多了，我们正式开始这道题

虽然说的很简单，要用 C 语言复现 `grep` 的功能，但是还是算是一个比较复杂的项目。

#### 拆解任务、要求和学习方向：

- **第一步：解析命令行参数**
  
  判断用户有没有输入搜索词、文件名，以及 `-n`、`-i`、`-c` 选项。
  
  例如：`lrg -ni error sample.log`

- **第二步：打开输入源**
  
  如果给了文件名，就打开文件；如果没给文件名，就从标准输入读取。
  
  这里要学习 Linux 的 `open()` 和文件描述符。

- 从文件中读取字节，拼出完整的一行。无论一行有多长，都不能截断。
  
  这里要学习 `read()`、缓冲区、动态内存。

- **第四步：判断一行是否匹配**
  
  检查当前行是否包含搜索词，必要时忽略 ASCII 英文字母的大小写。
  
  这里主要涉及字符串处理和遍历。

- **第五步：输出结果并收尾**
  
  根据选项打印内容、行号或计数；发生错误时报告原因；最后关闭文件并返回退出码。

好的，那么我们现在正式开始。

---

#### 一、学习让 C 语言从命令行里读取输入参数

- 记得在一轮面试的时候学长就考了我这个问题：`“有研究过 main 函数入口处、int main 后面的 () 中的参数的作用吗？”`，由于先前的实践中都暂时没有用上这个功能，故没有回答上。这也是在其他地方阅读一些 C 代码时经常困扰我的问题。那么今天我们将一次性把他学懂了。这也恰好是实现本题第一步的第一小步。

##### 在了解了基本定义后，我动手写了个实验小代码 `args.c`：

```c
#include <stdio.h>

int main(int argc, char *argv[]){                   //命令行读取
    printf("argc = %d\n",argc);                     //输出 argc
    int i;
    for(i = 0; i < argc; i ++){
        printf("argv[%d] = %s\n", i , argv[i]);     //逐个输出 argc[]
    }
    return 0;
}
```

##### 测试 & 结果：

```bash
$ ./args zzh hzh yyc lhy ymh zzr ttkx!
argc = 8
argv[0] = ./args
argv[1] = zzh
argv[2] = hzh
argv[3] = yyc
argv[4] = lhy
argv[5] = ymh
argv[6] = zzr
argv[7] = ttkx!
```

（我们寝室 6 个人的名字，ttkx ：天天开心）hhhh

##### 笔记：

在代码 `int main(int argc, char *argv[])` 中：

- `argc`：命令行参数的数量。

- `argv`：保存命令行参数的数组，每个元素都是一个字符串。

然后在终端中输入

```bash
./文件名 参数1 参数2 参数3 ...
```

`参数1`、`参数2`、`参数3`…… 就会自动被读取并存入 `argv[0]` 、`argv[1]` 、`argv[2]`……中了。而他们的个数将返回至 `argc` 中。

- 注意！`./文件名` 会作为 `参数1` 被存入 `argv[0]` 中，这也解释了为什么上面的实验小代码的 `argv[0]` 输出的是 `./args`。

---

#### 二、开始实现 “选项” 的解析

##### 大体的思路：

由输入参数解析 “选项” ，为了程序便于开发，**我决定采用模块化的思路。**本模块专门用于解析 “选项” 并设置状态参数来保存状态。如 `int show_line_number = 0 / 1` 来标识 `n` 选项。`i`、`c` 类似然后由后续程序读取这些状态参数，决定具体执行方式。

那我们先来解析选项。

##### 题目要求可处理的 “选项” 共有：

| - 参数   | 应该识别出的选项           |
| ------ | ------------------ |
| `-n`   | 显示行号               |
| `-i`   | 忽略大小写              |
| `-ni`  | 显示行号 + 忽略大小写       |
| `-in`  | 忽略大小写 + 显示行号       |
| `-nic` | 显示行号 + 忽略大小写 + 只计数 |

注意，由题：

- 从左往右扫描，遇到第一个不以 `-` 开头的参数就停止，它就是 `PATTERN`，其后的参数全是 `FILE`；
- 选项可以合并：`-ni` 等价于 `-n -i`；

说明还需要处理多个 `- 选项` 一个一个出现的情况，也需要处理。

##### ok，要求梳理清楚，我们来拆解任务：

###### 第一步：设计参数解析器

先把题目要求转化为程序需要保存的状态。

| 变量                 | 作用        | 初始值  |
| ------------------ | --------- | ---- |
| `show_line_number` | 是否显示行号    | `0`  |
| `ignore_case`      | 是否忽略大小写   | `0`  |
| `count_only`       | 是否只统计匹配行数 | `0`  |
| `pattern`          | 指向搜索词     | 尚未确定 |
| `first_file`       | 第一个文件参数   | 尚未确定 |

前三个变量都是开关。我们先用整数 `0` 和 `1` 表示关闭与开启。

后两个变量需要等解析器找到搜索词之后才能确定。

###### 第二步：使用双循环解析参数

外层循环：遍历参数

依次检查 `argv[1]`、`argv[2]`、`argv[3]`…… 判断当前参数是什么。

- 如果是选项，例如 `-ni`，进入内层循环。

- 如果是搜索词，例如 `error`，保存它并停止选项解析。

- 如果是单独的 `-`，按题目规定将它视为普通参数（即等于不写参数）。

内层循环：遍历 “选项” 字符

例如 `-nic`，依次检查 `n`、`i`、`c`。遇到其他字符，程序停止并报告用法错误。

##### 很清晰，开始动手实践

###### 先补充一个小点：怎么分别表示 `-ni` 中的 `n` 和 `i` 呢？

这就要联系以前学过的知识了

- 首先，C 语言没有储存字符串的变量类型，所有的字符串实际上是储存为一个 `char` 类型数组。

- 然后在保存时这个数组自动退化成首字符地址的指针，保存进指针数组 `argv[i]` 中。所以现在第二个字符串（保存 “选项” 的字符串）的名称为 `aegc[1]`

所以假如 `-ni` 存入了 `argv[1]` 中，那么很自然，`-` → `argv[1][0]` 、 `n` → `argv[1][1]` 、`i` → `argv[1][2]` 、`\0` → `argv[1][3]`，遇到 `\0` 就停止内层循环，这样就可以匹配上所有的 “选项” 要求了。

###### 我竟然不靠 AI 自己动手用 C 语言成功实现了这一步，写出了第一版代码

**第一版代码：**

```c
#include <stdio.h>

int main(int argc, char *argv[]){
    int i, j;                        // 用于循环控制的变量

    int show_line_number = 0;
    int ignore_case = 0;
    int count_only = 0;                 // 3 个 “选项” 参数

    int option = 0;                     // 为了便于参数解析，新建一个状态表示 “是否检验到 ‘状态’ 参数”
    int pat = 0;                        // 为了便于参数解析，新建一个状态表示 “是否检验到 pattern ”

    char *pattern = NULL;               // pattern 存放的位置
    char *file[ argc ];                 // 文件名列表

    int file_num = 1;                   // 文件计数器
    char *imp;                          // 未解析到文件名时，一般输入存储的位置


    for( i = 1; i < argc; i++ ){

        if( argv[i][0] == '-' ){
            j = 1;
            option = 1;

            while( argv[i][j] != 0 ){
            if( argv[i][j] == 'n' )
                show_line_number = 1;
            if( argv[i][j] == 'i' )
                ignore_case = 1;
            if( argv[i][j] == 'c' )
                count_only = 1;
            if( argv[i][j] != 'n' && argv[i][j] != 'i' && argv[i][j] != 'c' )
                return 2;

            j ++;

            }                                                   // 识别到 “选项” 时，设置 3 个 “选项” 参数

        }

        if( pat == 0 && argv[i][0] != '-' ){
            pattern = argv[i] ;
            pat = 1;
            continue;                                   // 读取 pattern 并防止重复读取以及 pattern 再次被识别成文件名
        }

        if( pat == 1 && argv[i][0] != '-' ){
            file[file_num] = argv[i];
            file_num ++ ;
        }                                               // 逐个读取文件名

    }

    if( pat == 0)
        return 2;                                       // 未解析到 pattern 时返回 2

    if( pat == 1 && file_num == 1){
        scanf("%s", imp);
    }                                                           // 未解析到文件名时，启用一般输入

    printf("show_line_number = %d\n", show_line_number);
    printf("ignore_case = %d\n", ignore_case);
    printf("count_only = %d\n", count_only);
    printf("pattern: %s\n", pattern);
    printf("How many files: %d\n", file_num - 1);                // 打印状态

    if( file_num != 1){
        for( i = 1; i < file_num; i ++ ){
            printf("file %d : %s\n", i , file[i]);
        }
    }                                                   // 逐个打印文件名

    return 0;
}
```

示例输入输出：

示例1：

```
$ ./options - - - -ni -c zzh hzh yyc

show_line_number = 1
ignore_case = 1
count_only = 1
pattern: zzh
How many files: 2
file 1 : hzh
file 2 : yyc
```

示例2：

```
$ ./options - - - -inc "" zzh hzh

show_line_number = 1
ignore_case = 1
count_only = 1
pattern: 
How many files: 2
file 1 : zzh
file 2 : hzh
```

示例3：（错误：使用非法 “选项” ）

```
$ ./options - - - -x zzh
( 退出 )
```

示例4：（错误：未解析到 pattern ）

```
$ ./options - - - -c
( 退出 )
```

###### 可以看到，很大程度上已经正确了

于是我把代码拿给 AI 审查，他发现了几个错误：

1. 即使已经识别出 `pattern`，后面遇到以 `-` 开头的文件名，程序仍然会把它当成选项。

2. > `imp` 是一个指针，但你没有让它指向一块可写的内存。它的值是 `NULL`。
   > 
   > `scanf("%s", imp)` 会尝试向这个指针指向的位置写入字符，但是此时 `imp` 没有指向确定、可写的内存，不能安全地接收输入。
   > 
   > 更重要的是，这一步本身也不应该放在参数解析程序里。
   > 
   > 你的设计意图应该是：没有指定文件时，从标准输入读取内容。但标准输入的内容属于后续的“搜索与读取”阶段，不属于“参数解析”阶段。
   > 
   > 所以，现阶段先删除这段代码：
   > 
   > ```c
   > if (pat == 1 && file_num == 1) {
   >     scanf("%s", imp);
   > }
   > ```

**AI 给出的建议是，先解析 “选项” 和 `pattern` ，一旦解析到 `pattern` 就跳出循环，然后把后面的一切都作为文件名，单独解析。**

###### 那么我现在开始修改

- 突然还发现一个自己的错误，这是读题目说明时的一个误解：

> 题目说明：**单独的 `-` 不是选项，按普通参数处理**

- 我一开始理解成：单独的 `-` 作为默认选项处理（即等价于不写选项）

- 而后面和 AI 探讨后意识到：这里的 “普通参数” 指的是相较于 “选项” 参数而普通的参数，比如单独的 `-` 放在 `argv[1]` 里就是 `pattern` 。

综合上述，修改后代码：

```c
#include <stdio.h>

int main(int argc, char *argv[]){
    int i, j;                        // 用于循环控制的变量

    int show_line_number = 0;
    int ignore_case = 0;
    int count_only = 0;                 // 3 个 “选项” 参数

    int option = 0;                     // 为了便于参数解析，新建一个状态表示 “是否检验到 ‘状态’ 参数”
    int pat = 0;                        // 为了便于参数解析，新建一个状态表示 “是否检验到 pattern ”

    char *pattern = NULL;               // pattern 存放的位置
    char *file[ argc ];                 // 文件名列表

    int file_num = 1;                   // 文件计数器


    for( i = 1; i < argc; i++ ){

        if( argv[i][0] == '-' && argv[i][1] != 0){
            j = 1;
            option = 1;

            while( argv[i][j] != 0 ){
            if( argv[i][j] == 'n' )
                show_line_number = 1;
            if( argv[i][j] == 'i' )
                ignore_case = 1;
            if( argv[i][j] == 'c' )
                count_only = 1;
            if( argv[i][j] != 'n' && argv[i][j] != 'i' && argv[i][j] != 'c' )
                return 2;

            j ++;

            }                                                   // 识别到 “选项” 时，设置 3 个 “选项” 参数

        }

        if( (pat == 0 && argv[i][0] != '-') || ( pat == 0 && option == 0 ) ){
            pattern = argv[i] ;
            pat = 1;
            break;                                   // 读取 pattern 并防止重复读取以及 pattern 再次被识别成文件名
        }

    }

    if( pat == 0 )
        return 2;                                       // 未解析到 pattern 时返回 2

    for( i = i + 1 ; i < argc ; i ++ ){
        file[file_num] = argv[i];
        file_num ++ ;
    }                                                   // 逐个解析文件名

    printf("show_line_number = %d\n", show_line_number);
    printf("ignore_case = %d\n", ignore_case);
    printf("count_only = %d\n", count_only);
    printf("pattern: %s\n", pattern);
    printf("How many files: %d\n", file_num - 1);                // 打印状态

    if( file_num != 1){
        for( i = 1; i < file_num; i ++ ){
            printf("file %d : %s\n", i , file[i]);
        }
    }                                                   // 逐个打印文件名

    return 0;
}
```

修复后输入输出示例：

```
$ ./options - - - -i -c -n zzh -n -x

show_line_number = 0
ignore_case = 0
count_only = 0
pattern: -
How many files: 8
file 1 : -
file 2 : -
file 3 : -i
file 4 : -c
file 5 : -n
file 6 : zzh
file 7 : -n
file 8 : -x
```

###### OK 现在应该是全部满足题目要求了，继续完善一下报错。

**学习使用新函数 `fprintf` 输出错误信息：**

我们现在已经会使用：

```c
printf("pattern: %s\n", pattern);
```

`printf` 默认向标准输出 `stdout` 打印内容，通常就是终端上正常显示的输出。

而 C 语言还提供了 `fprintf`，它允许你指定输出目标。

```c
fprintf(stderr, "usage: lrg [-nic] PATTERN [FILE...]\n");
```

因此，可以这样理解：

```c
printf("正常信息\n");           // 默认输出到 stdout
fprintf(stderr, "错误信息\n");  // 输出到 stderr
```

两者在终端上看起来可能完全一样，但它们是不同的输出流。比如使用 shell 重定向时，可以将正常输出和错误输出分别保存到不同文件。

###### 完善后代码：

```c
#include <stdio.h>

int main(int argc, char *argv[]){
    int i, j;                        // 用于循环控制的变量

    int show_line_number = 0;
    int ignore_case = 0;
    int count_only = 0;                 // 3 个 “选项” 参数

    int option = 0;                     // 为了便于参数解析，新建一个状态表示 “是否检验到 ‘状态’ 参数”
    int pat = 0;                        // 为了便于参数解析，新建一个状态表示 “是否检验到 pattern ”

    char *pattern = NULL;               // pattern 存放的位置
    char *file[ argc ];                 // 文件名列表

    int file_num = 1;                   // 文件计数器


    for( i = 1; i < argc; i++ ){

        if( argv[i][0] == '-' && argv[i][1] != 0){
            j = 1;
            option = 1;

            while( argv[i][j] != 0 ){
            if( argv[i][j] == 'n' )
                show_line_number = 1;
            if( argv[i][j] == 'i' )
                ignore_case = 1;
            if( argv[i][j] == 'c' )
                count_only = 1;
            if( argv[i][j] != 'n' && argv[i][j] != 'i' && argv[i][j] != 'c' ){
                fprintf(stderr, "usage: lrg [-nic] PATTERN [FILE...]\n");
                return 2;
            }

            j ++;

            }                                                   // 识别到 “选项” 时，设置 3 个 “选项” 参数

        }

        if( (pat == 0 && argv[i][0] != '-') || ( pat == 0 && option == 0 ) ){
            pattern = argv[i] ;
            pat = 1;
            break;                                   // 读取 pattern 并防止重复读取以及 pattern 再次被识别成文件名
        }

    }

    if( pat == 0 ){
        fprintf(stderr, "usage: lrg [-nic] PATTERN [FILE...]\n");
        return 2; 
    }
                                              // 未解析到 pattern 时返回 2

    for( i = i + 1 ; i < argc ; i ++ ){
        file[file_num] = argv[i];
        file_num ++ ;
    }                                                   // 逐个解析文件名

    printf("show_line_number = %d\n", show_line_number);
    printf("ignore_case = %d\n", ignore_case);
    printf("count_only = %d\n", count_only);
    printf("pattern: %s\n", pattern);
    printf("How many files: %d\n", file_num - 1);                // 打印状态

    if( file_num != 1){
        for( i = 1; i < file_num; i ++ ){
            printf("file %d : %s\n", i , file[i]);
        }
    }                                                   // 逐个打印文件名

    return 0;
}
```

报错输出样例：

```
$ ./options -i

usage: lrg [-nic] PATTERN [FILE...]
```

```
$ ./options -x

usage: lrg [-nic] PATTERN [FILE...]
```

#### 好的，至此参数解析板块已全部完成。

---

#### 三、系统调用（读取文件）及文件描述符

##### 题目明确要求使用 Linux 系统调用读取文件：

- `open()`：打开文件。

- `read()`：读取文件中的字节。

- `close()`：关闭文件。

这三个函数构成了最基础的文件读取流程。

##### 文件描述符是什么？

调用 `open()` 后，系统会**返回一个整数，**叫作文件描述符（file descriptor，简称 fd）。

##### 读取过程：

```c
文件 sample.txt （磁盘上的数据）
            ↓
open("sample.txt", O_RDONLY)
（ 打开文件，返回 fd，例如 3 ）
            ↓
read(fd, buffer, sizeof buffer)
  （ 把字节读取到内存缓冲区 ）
            ↓
        close(fd)
    （ 关闭文件描述符 ）
```

##### 看懂 `read()` 的返回值

```c
ssize_t n = read(fd, buffer, sizeof buffer);
```

`read()` 的返回值有三种主要情况：

| 返回值       | 含义          | 应当怎么理解            |
| --------- | ----------- | ----------------- |
| `n > 0`   | 实际读取的字节数    | 成功读取了 `n` 个字节     |
| `n == 0`  | 到达文件末尾（EOF） | 当前没有更多数据可读        |
| `n == -1` | 读取发生错误      | 检查 `errno`，判断错误原因 |

**这里有两个细节：**

- `sizeof buffer` 表示本次最多读取多少字节，不代表一定能读满。

- `read()` 读取的是字节，不是行。一次读取可能得到半行、一行或多行内容。

例如，文件有 100 个字节，而缓冲区有 16 个字节，那么程序可能需要**多次调用** `read()` 才能读完。

##### 动手实践 & 语法细节补充

在本处我希望做一个能够读取指定文件并输出内容的实验性小程序

同时学习此过程中的语法细节。

###### 实现所需头文件

| 头文件          | 本程序用它做什么                                          | 助记              |
| ------------ | ------------------------------------------------- | --------------- |
| `<fcntl.h>`  | 使用 `open()` 和 `O_RDONLY`                          | = file control  |
| `<unistd.h>` | 使用 `read()`、`write()`、`close()` 和 `STDOUT_FILENO` | = Unix standard |
| `<stdio.h>`  | 使用 `fprintf()`、`stderr` 和 `perror()`              |                 |

###### `read()` 函数的语法

```c
int fd = open(argv[1], O_RDONLY);
```

拆开看：

| 部分          | 含义                       |
| ----------- | ------------------------ |
| `int`       | 声明一个整数变量                 |
| `fd`        | 变量名，通常表示 file descriptor |
| `=`         | 把右侧表达式的结果赋给左侧变量          |
| `open(...)` | 调用打开文件的函数                |
| `argv[1]`   | 要打开的文件名                  |
| `O_RDONLY`  | 以只读方式打开                  |

假设文件打开成功，`open()` 会返回一个非负整数，存入 `fd` 按前面所学知识，此即文件描述符。可以理解成在此程序运行过程中文件的代码，**后续 `read()` 和 `close()` 都靠文件描述符操作对应的文件。**

假设文件打开失败，`open()` 会返回 `-1` 。

###### `perror("open")` 是什么？

`perror()` 会**输出你提供的提示文本，以及系统记录的最近一次错误原因。**

例如，文件不存在时，可能输出：

```
open: No such file or directory
```

具体文字会受系统语言和环境影响。

这里的 `"open"` 是你提供的提示前缀，不是文件名本身。

**注意！通常不用在引号里加冒号**。`perror()` 的标准行为是：

- 如果参数字符串**非空**，先输出这个字符串，然后**自动输出 `": "`（冒号加空格）**，再输出 `errno` 对应的错误描述，最后**自动换行**。

- 如果参数是**空字符串 `""`**，则**不会**输出前缀和冒号，只输出错误描述。

###### 题目要求不能一次性把文件全部读入内存，于是我们利用 `read()` 特点，设置一个小的缓冲区（内存上），反复调用反复读取。

**实现第一步：先准备读取缓冲区 `buffer`**

```c
char buffer[16];
ssize_t n;
```

`char buffer[16]` 是一个数组声明。

- `char`：数组中每个元素的类型。

- `buffer`：数组名。

- `[16]`：数组有 16 个元素。

因此：

```c
char buffer[16];
```

相当于在内存中准备了 16 个 `char` 元素，用来存储读取到的字节。

这样就实现了不需要提前把整个文件放进内存，只需要准备一个小缓冲区，反复使用它即可。

> ！！注意
> 
> `ssize_t` 是一种整数类型，常用于表示 `read()`、`write()` 这类函数返回的字节数。
> 
> 为什么不用 `int`？
> 
> 因为这些函数的返回值类型就是 `ssize_t`。使用对应的类型更准确，也能避免在不同平台上因整数宽度不同而出现的问题。
> 
> 变量 `n` 用来记录每次实际读取到多少字节。

**实现第二步：循环调用 `read()` 读取文件**

```c
while ((n = read(fd, buffer, sizeof buffer)) > 0) {
    // write(STDOUT_FILENO, buffer, n);     （下一步）
}
```

参考前面的 `read()` 函数的语法，可以知道 `read(...)` 这句话的意思是：从 `fd` 对应的文件中读取数据，最多读取 `sizeof buffer` 个字节，并把数据放进 `buffer`。

`while()` 判断：`read()` 是读取到了有效字节的，那么继续执行 `write()` ，并且实现循环 `read()` 和 `write()` 。

**实现第三步：使用 `write()` 打印内容**

> 首先了解 `write()` 和 `printf()` 的区别：`write()` 和 `printf()` 虽然都能"输出"，但它们处在**完全不同的层次**上，核心区别是：**`write()` 是系统调用（直接与内核打交道），`printf()` 是 C 标准库函数（经过缓冲后最终调用 `write()`）**。

```c
write(STDOUT_FILENO, buffer, n);
```

这行的作用是将刚读取的字节写到标准输出。

它的三个参数分别是：

| 参数              | 含义                  |
| --------------- | ------------------- |
| `STDOUT_FILENO` | 标准输出对应的文件描述符，值为 `1` |
| `buffer`        | 数据所在的内存位置           |
| `n`             | 这次要写出的字节数           |

注意：

- `STDOUT_FILENO` 是 `<unistd.h>` 里定义的宏，通常定义为 `1`。

- 另外两个常用宏：
  
  - `STDIN_FILENO` = `0`，标准输入
  
  - `STDERR_FILENO` = `2`，标准错误

- 用 `STDOUT_FILENO` 比直接写 `1` **更可读、更规范**，所以一般推荐保留宏，而不是改成 `1`。

**补充：`write()` 的返回值：**

| 返回值       | 含义                                            |
| --------- | --------------------------------------------- |
| **`> 0`** | 成功写入的**实际字节数**，可能**小于** `n`                   |
| **`0`**   | 通常表示**什么也没写**（对普通文件很少见；对 `n == 0` 时返回 0 是正常的） |
| **`-1`**  | **失败**，具体原因看 `errno`                          |

所以我们可以在此基础上，利用 `write()` 的返回值来判断是否写入成功。

###### 又靠自己写完了！太爽。感觉又学会了一个很实用的技能

**`read.c` 程序代码：**

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

    if ( argc != 2){
        fprintf(stderr, "usage: read FILE\n");
        return 2;
    }                   // 判断是否输入的格式是 "usage: read FILE"，若否，则向 stderr 中写入错误提示信息并打印


    int fd = open(argv[1], O_RDONLY);       // 以只读打开 argv[1] 中文件名对应的文件，并生成文件描述符

    if( fd == -1 ){
        perror("open");
        return 2;
    }

    char buffer[16];                // 创建缓存区（当前设置 16 字节）
    ssize_t n;                      // 设置变量 n 用以存储 read() 的返回值

    while((n = read( fd, buffer, sizeof buffer)) > 0 ){         // 条件判断（是否读取完毕） & 读取文件写入缓存区
        write( STDOUT_FILENO, buffer, n );                     // 标准输出缓存区内容
    }

    if( n == -1 ){                  // 读取错误的处理
        perror("read");
        close(fd);
        return 2;
    }

    close(fd);          // 标准结束的处理
    return 0;
}
```

**测试文件 `readtest.txt` ：**

```
hzh ttkx!
zzh ttkx!
yyc ttkx!
lhy ttkx!
zzr ttkx!
yym ttkx!
This is readtest.txt
Jacky is very nb !
```

**终端输出：**

```
$ ./read readtest.txt
hzh ttkx!
zzh ttkx!
yyc ttkx!
lhy ttkx!
zzr ttkx!
yym ttkx!
This is readtest.txt
Jacky is very nb !
```

###### 细节完善

**问题一、`write()` 不一定全部成功**

我们要就其返回值判断程序状态并给出相应的报错提示和程序返回值

加上错误返回 `-1` 的审查：

```c
char buffer[16];                // 创建缓存区（当前设置 16 字节）
ssize_t n;                      // 设置变量 n 用以存储 read() 的返回值

    while((n = read( fd, buffer, sizeof buffer)) > 0 ){         // 条件判断（是否读取完毕） & 读取文件写入缓存区
        ssize_t w = write( STDOUT_FILENO, buffer, n );                     // 标准输出缓存区内容
        if ( w == -1 ){
            perror("write");
            close(fd);
            return 2;                    // wirte() 返回 -1 的情况的报错和退出
        }
    }
```

但是我去请 AI 审查后了解到，还有一种情况是**短写**，为了解决这个问题，我完善了代码，虽然依然暂时不能防止 `EINTR` 的错误，但是至少短写的问题可以得到解决：

```c
char buffer[16];                // 创建缓存区（当前设置 16 字节）
    ssize_t n, written = 0;                      // 设置变量 n, written 用以存储 read() 和 write() 的返回值

    while((n = read( fd, buffer, sizeof buffer)) > 0 ){         // 条件判断（是否读取完毕） & 读取文件写入缓存区

        while( written < n ){
            ssize_t w = write( STDOUT_FILENO , buffer + written , n - written );

            if( w == -1 ){
                perror("write");
                close(fd);
                return 2;
            }                           // write 错误后打印错误信息及退出（暂时不防 EINTR）

            written += w; 
        }                           

        written = 0;                // 整体是防止 write() 发生短写的写法

    }
```

#### 完美成功，至此系统调用、文件读取和板块学习完成

---

#### 四、按行读取，写入动态内存

在第三步的实验程序 `read.c` 基础上，本段实验程序也是由我自己出乎意料地快地完成了，虽然不可避免地使用了 AI 进行代码审查，不过确实都是我自己写的和改的。不得不说经过系统性的学习和一段时间的历练，现在对 C 语言也是越来越有感觉了，逻辑、语法……越来越不在话下。**现在 C 语言对我来说有一点从高高在上的学习对象变成用以实现我的想法的工具的感觉，这个过程，无疑是充满爽感的。**一步一步地解这道题，实现越来越多地功能，越来越接近目标，真的可谓是一直激发着我的学习欲望。

##### 那么我们还是先来看看这部分实验代码 `line.c` 吧：

（本代码是已经经过修正的正确代码，依旧暂时忽略 `EINTR` 和 `write()` 短写的处理）

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    if ( argc != 2){
        fprintf(stderr, "usage: read FILE\n");
        return 2;
    }                   // // 检查命令行参数数量是否正确，若否，则向 stderr 中写入错误提示信息并打印


    int fd = open(argv[1], O_RDONLY);       // 以只读打开 argv[1] 中文件名对应的文件，并生成文件描述符

    if( fd == -1 ){
        perror("open");
        return 2;
    }

    char buffer[16];                // 创建缓存区（当前设置 16 字节）
    ssize_t n, written = 0;                      // 设置变量 n, written 用以存储 read() 和 write() 的返回值

    char *line = NULL;
    size_t line_len = 0;
    size_t line_cap = 64;

    line = malloc( line_cap ) ;
    if( line == NULL ){
        perror("malloc fail");
        return 2;
    }

    while((n = read( fd, buffer, sizeof buffer)) > 0 ){         // 条件判断（是否读取完毕） & 读取文件写入缓存区

        for( size_t i = 0 ; i < n ; i ++ ){
            if( buffer[i] == '\n' ){
                write( STDOUT_FILENO , line , line_len );
                write( STDOUT_FILENO , "\n" , 1 );
                line_len = 0;                           // 遇到换行符时标准输出当前 line 里的行
            }
            else{

                if( line_len == line_cap ){
                    char *tmp = realloc( line , line_cap * 2);
                    if( tmp == NULL ){
                        perror("realloc fail");
                        free( line );
                        close(fd);
                        return 2;
                    }
                    else{
                        line = tmp;
                        line_cap *= 2;
                    }                               // 若行内存不够，将扩容到原来 2 倍
                }

                line[line_len] = buffer[i];
                line_len += 1;                      // 将普通字符添加至 line 末尾
            }
        }

    }

    if( n == -1 ){                  // 读取错误的处理
        perror("read");
        free( line );
        close(fd);
        return 2;
    }

    if( n == 0 && line_len > 0){
        write( STDOUT_FILENO , line , line_len );
        write( STDOUT_FILENO , "\n" , 1 );
        line_len = 0;                                // 若读取结束，但 line_len != 0，说明 line 里面还有最后一行的内容 → 用以处理文件末尾没有 \n 的情况。
    }

    free( line );
    close(fd);          // 标准结束的处理
    return 0;
}
```

##### 踩过的坑其实不少，我们来梳理最大的两个

###### （1）`write()` 函数的参数定义其实是：

```c
ssize_t write(int fd, const void *buf, size_t count);
```

我一开始想写 `write( STDOUT_FILENO , '\n' , 1 );` 但是编译器就给我报了相应的错，后面改成 `write( STDOUT_FILENO , "\n" , 1 );` 之后就通过了。

我去询问了 AI 原因，了解到：

> - `'\n'`：字符常量，类型是 `int`，表示换行字符对应的数值。
> 
> - `"\n"`：字符串字面量，包含一个换行字符，作为参数时会转换为指向字符数据的指针。
> 
> 第二个参数 `buf` 必须是指向待写入数据的指针，所以直接传入 `'\n'` 会出现类型不匹配。

看来很多 C 语言的底层特性，尤其是与指针有关的这些东西，还是得在日后的工程实践中慢慢积累和精进。

###### （2）无论是正常分支还是错误分支，都别忘了 `free()` 和 `close()` ！

这一点真的很难察觉，但是成败往往在于这样的细节。

##### Well，让我们来看看 `line.c` 的测试结果

###### 测试数据1：`readtest.txt（和 read.c 用的一样）`

```
hzh ttkx!
zzh ttkx!
yyc ttkx!
lhy ttkx!
zzr ttkx!
yym ttkx!
This is readtest.txt
Jacky is very nb !
```

程序执行结果：

```
$ ./line readtest.txt
hzh ttkx!
zzh ttkx!
yyc ttkx!
lhy ttkx!
zzr ttkx!
yym ttkx!
This is readtest.txt
Jacky is very nb !
```

基本功能正常

###### 测试数据2：`linetest.txt（超长单行，用以测试动态内存扩展功能）`

```
hzh ttkx!
zzh ttkx!
yyc ttkx!
lhy ttkx!
zzr ttkx!
yym ttkx!
This is linetest.txt  Jacky is very nb !  This is linetest.txt  Jacky is very nb !  This is linetest.txt  Jacky is very nb !  This is linetest.txt  Jacky is very nb !  
hzh ttkx!   zzh ttkx!   yyc ttkx!   lhy ttkx!   zzr ttkx!   yym ttkx!
```

程序执行结果：

```
$ ./line linetest.txt
hzh ttkx!
zzh ttkx!
yyc ttkx!
lhy ttkx!
zzr ttkx!
yym ttkx!
This is linetest.txt  Jacky is very nb !  This is linetest.txt  Jacky is very nb !  This is linetest.txt  Jacky is very nb !  This is linetest.txt  Jacky is very nb !  
hzh ttkx!   zzh ttkx!   yyc ttkx!   lhy ttkx!   zzr ttkx!   yym ttkx!
```

非常完美的超长单行！！我自己都觉得太棒了。太厉害了。

#### 那么至此，按行读取并写入动态内存板块已圆满完成。

---

#### 五、拼合 `options.c` 和 `line.c` ，为后续匹配打基础

能识别选项、`pattern`、多个文件名并且实现了可以按行输出多个文件内容

代码：

```c
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    int i, j;                        // 用于循环控制的变量

    int show_line_number = 0;
    int ignore_case = 0;
    int count_only = 0;                 // 3 个 “选项” 参数

    int option = 0;                     // 为了便于参数解析，新建一个状态表示 “是否检验到 ‘状态’ 参数”
    int pat = 0;                        // 为了便于参数解析，新建一个状态表示 “是否检验到 pattern ”

    char *pattern = NULL;               // pattern 存放的位置
    char *file[ argc ];                 // 文件名列表

    int file_num = 1;                   // 文件计数器


    for( i = 1; i < argc; i++ ){

        if( argv[i][0] == '-' && argv[i][1] != 0){
            j = 1;
            option = 1;

            while( argv[i][j] != 0 ){
            if( argv[i][j] == 'n' )
                show_line_number = 1;
            if( argv[i][j] == 'i' )
                ignore_case = 1;
            if( argv[i][j] == 'c' )
                count_only = 1;
            if( argv[i][j] != 'n' && argv[i][j] != 'i' && argv[i][j] != 'c' ){
                fprintf(stderr, "usage: lrg [-nic] PATTERN [FILE...]\n");
                return 2;
            }

            j ++;

            }                                                   // 识别到 “选项” 时，设置 3 个 “选项” 参数

        }

        if( (pat == 0 && argv[i][0] != '-') || ( pat == 0 && option == 0 ) ){
            pattern = argv[i] ;
            pat = 1;
            break;                                   // 读取 pattern 并防止重复读取以及 pattern 再次被识别成文件名
        }

    }

    if( pat == 0 ){
        fprintf(stderr, "usage: lrg [-nic] PATTERN [FILE...]\n");
        return 2; 
    }
                                              // 未解析到 pattern 时返回 2

    for( i = i + 1 ; i < argc ; i ++ ){
        file[file_num] = argv[i];
        file_num ++ ;
    }                                                   // 逐个解析文件名

    printf("show_line_number = %d\n", show_line_number);
    printf("ignore_case = %d\n", ignore_case);
    printf("count_only = %d\n", count_only);
    printf("pattern: %s\n", pattern);
    printf("How many files: %d\n", file_num - 1);                // 打印状态

    if( file_num != 1){
        for( i = 1; i < file_num; i ++ ){
            printf("file %d : %s\n", i , file[i]);


            int fd = open(file[i], O_RDONLY);       // 以只读打开 argv[1] 中文件名对应的文件，并生成文件描述符

            if( fd == -1 ){
                perror("open");
                return 2;
            }

            char buffer[16];                // 创建缓存区（当前设置 16 字节）
            ssize_t n, written = 0;                      // 设置变量 n, written 用以存储 read() 和 write() 的返回值

            char *line = NULL;
            size_t line_len = 0;
            size_t line_cap = 64;

            line = malloc( line_cap ) ;
            if( line == NULL ){
                perror("malloc fail");
                return 2;
            }

            while((n = read( fd, buffer, sizeof buffer)) > 0 ){         // 条件判断（是否读取完毕） & 读取文件写入缓存区

                for( size_t i = 0 ; i < n ; i ++ ){
                    if( buffer[i] == '\n' ){
                        write( STDOUT_FILENO , line , line_len );
                        write( STDOUT_FILENO , "\n" , 1 );
                        line_len = 0;                           // 遇到换行符时标准输出当前 line 里的行
                    }
                    else{

                        if( line_len == line_cap ){
                            char *tmp = realloc( line , line_cap * 2);
                            if( tmp == NULL ){
                                perror("realloc fail");
                                free( line );
                                close(fd);
                                return 2;
                            }
                            else{
                                line = tmp;
                                line_cap *= 2;
                            }                               // 若行内存不够，将扩容到原来 2 倍
                        }

                        line[line_len] = buffer[i];
                        line_len += 1;                      // 将普通字符添加至 line 末尾
                    }
                }

            }

            if( n == -1 ){                  // 读取错误的处理
                perror("read");
                free( line );
                close(fd);
                return 2;
            }

            if( n == 0 && line_len > 0){
                write( STDOUT_FILENO , line , line_len );
                write( STDOUT_FILENO , "\n" , 1 );
                line_len = 0;                                // 若读取结束，但 line_len != 0，说明 line 里面还有最后一行的内容 → 用以处理文件末尾没有 \n 的情况。
            }

            free( line );
            close(fd);          // 标准结束的处理

        }
    }                                                   // 逐个打印文件名

    return 0;
}
```

输出测试：

```
$ ./find -n -ic find readtest.txt linetest.txt
show_line_number = 1
ignore_case = 1
count_only = 1
pattern: find
How many files: 2
file 1 : readtest.txt
hzh ttkx!
zzh ttkx!
yyc ttkx!
lhy ttkx!
zzr ttkx!
yym ttkx!
This is readtest.txt
Jacky is very nb !
file 2 : linetest.txt
hzh ttkx!
zzh ttkx!
yyc ttkx!
lhy ttkx!
zzr ttkx!
yym ttkx!
This is linetest.txt  Jacky is very nb !  This is linetest.txt  Jacky is very nb !  This is linetest.txt  Jacky is very nb !  This is linetest.txt  Jacky is very nb !  
hzh ttkx!   zzh ttkx!   yyc ttkx!   lhy ttkx!   zzr ttkx!   yym ttkx!
```

#### 嗯到目前为止都非常完美，我们进行下一步：筛选出匹配的行

---

#### 六、筛选出匹配的行

将直接在 `find.c` 的基础上进行修改。

##### `find.c` 主要修改处：

###### 增添函数 `suit()` 用以检验 `line` 是否含有 `pattern`

`suit()`：

```c
int suit( char *line , char *pattern , ssize_t line_len , ssize_t pattern_len ){        // 该函数用以扫描 line 里面有没有 pattern
    if( pattern_len > line_len )
        return 0;                               // 若 pattern_len 比 line_len 还大，那么不可能匹配

    if( pattern_len == 0 )
        return 1;                               // 若 pattern_len = 0，即空字符串，则按照题目要求匹配所有行

    int l , t ;                                 // 外层、内层循环标识量
    for( l = 0 ; l <= line_len - pattern_len ; l ++ ){       // 从 line 的首元素开始，区长度为 pattern_len 的一小段与 pattern 对比
        for( t = 0 ; t < pattern_len ; t ++ ){
            if( pattern[t] != line[ l + t ] )               // 若不完全符合，则将 line 上用以对比的这一小段向后移动 1 个字节
                break;
        }
        if( t == pattern_len )                         // 直到连续 pattern_len 个元素扫描完成，即 line 中存在完全符合 patten 的段
            return 1;
    }

    return 0;
}
```

###### 与之搭配的 `pattern_len` 计算器：

```c
while( pattern[pattern_len] != 0 ){
    pattern_len += 1;
}                                       // pattern 长度计算
```

###### 以及最终输出 `line` 的条件判断 → 决定本程序不会输出整个文件

（部分示意）

```c
for( size_t i = 0 ; i < n ; i ++ ){
    if( buffer[i] == '\n' ){
        suit_or_no = suit( line , pattern , line_len , pattern_len );
        if( suit_or_no == 1 ){                              // 调用 suit() 函数并加入条件判断，当且仅当该行匹配时才输出
            write( STDOUT_FILENO , line , line_len );
            write( STDOUT_FILENO , "\n" , 1 );
        }
......
```

以及修改了其他的一点点细节，

###### 呈现最终代码：

```c
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int suit( char *line , char *pattern , ssize_t line_len , ssize_t pattern_len ){        // 该函数用以扫描 line 里面有没有 pattern
    if( pattern_len > line_len )
        return 0;                               // 若 pattern_len 比 line_len 还大，那么不可能匹配

    if( pattern_len == 0 )
        return 1;                               // 若 pattern_len = 0，即空字符串，则按照题目要求匹配所有行

    int l , t ;                                 // 外层、内层循环标识量
    for( l = 0 ; l < line_len - pattern_len ; l ++ ){       // 从 line 的首元素开始，区长度为 pattern_len 的一小段与 pattern 对比
        for( t = 0 ; t < pattern_len ; t ++ ){
            if( pattern[t] != line[ l + t ] )               // 若不完全符合，则将 line 上用以对比的这一小段向后移动 1 个字节
                break;
        }
        if( t == pattern_len )                         // 直到连续 pattern_len 个元素扫描完成，即 line 中存在完全符合 patten 的段
            return 1;
    }

    return 0;
}


int main(int argc, char *argv[]){
    int i, j, k = 0;                        // 用于循环控制的变量

    int show_line_number = 0;
    int ignore_case = 0;
    int count_only = 0;                 // 3 个 “选项” 参数

    int option = 0;                     // 为了便于参数解析，新建一个状态表示 “是否检验到 ‘状态’ 参数”
    int pat = 0;                        // 为了便于参数解析，新建一个状态表示 “是否检验到 pattern ”

    char *pattern = NULL;               // pattern 存放的位置
    char *file[ argc ];                 // 文件名列表

    int file_num = 1;                   // 文件计数器

    ssize_t pattern_len = 0;            // pattern 长度计数器，初始化为 0 

    int suit_or_no = 0;                 // 设置表示该 line 是否存在匹配 pattern 的段的状态参数。

    for( i = 1; i < argc; i++ ){

        if( argv[i][0] == '-' && argv[i][1] != 0){
            j = 1;
            option = 1;

            while( argv[i][j] != 0 ){
            if( argv[i][j] == 'n' )
                show_line_number = 1;
            if( argv[i][j] == 'i' )
                ignore_case = 1;
            if( argv[i][j] == 'c' )
                count_only = 1;
            if( argv[i][j] != 'n' && argv[i][j] != 'i' && argv[i][j] != 'c' ){
                fprintf(stderr, "usage: lrg [-nic] PATTERN [FILE...]\n");
                return 2;
            }

            j ++;

            }                                                   // 识别到 “选项” 时，设置 3 个 “选项” 参数

        }

        if( (pat == 0 && argv[i][0] != '-') || ( pat == 0 && option == 0 ) ){
            pattern = argv[i] ;

            while( pattern[pattern_len] != 0 ){
                pattern_len += 1;
            }                                       // pattern 长度计算

            pat = 1;
            break;                                   // 读取 pattern 并防止重复读取以及 pattern 再次被识别成文件名
        }

    }

    if( pat == 0 ){
        fprintf(stderr, "usage: lrg [-nic] PATTERN [FILE...]\n");
        return 2; 
    }
                                              // 未解析到 pattern 时返回 2

    for( i = i + 1 ; i < argc ; i ++ ){
        file[file_num] = argv[i];
        file_num ++ ;
    }                                                   // 逐个解析文件名

    printf("show_line_number = %d\n", show_line_number);
    printf("ignore_case = %d\n", ignore_case);
    printf("count_only = %d\n", count_only);
    printf("pattern: %s\n", pattern);
    printf("How many files: %d\n", file_num - 1);                // 打印状态

    if( file_num != 1){
        for( i = 1; i < file_num; i ++ ){
            printf("file %d : %s\n", i , file[i]);


            int fd = open(file[i], O_RDONLY);       // 以只读打开 argv[1] 中文件名对应的文件，并生成文件描述符

            if( fd == -1 ){
                perror("open");
                return 2;
            }

            char buffer[16];                // 创建缓存区（当前设置 16 字节）
            ssize_t n, written = 0;                      // 设置变量 n, written 用以存储 read() 和 write() 的返回值

            char *line = NULL;
            size_t line_len = 0;
            size_t line_cap = 64;

            line = malloc( line_cap ) ;
            if( line == NULL ){
                perror("malloc fail");
                return 2;
            }

            while((n = read( fd, buffer, sizeof buffer)) > 0 ){         // 条件判断（是否读取完毕） & 读取文件写入缓存区

                for( size_t i = 0 ; i < n ; i ++ ){
                    if( buffer[i] == '\n' ){
                        suit_or_no = suit( line , pattern , line_len , pattern_len );
                        if( suit_or_no == 1 ){                              // 调用 suit() 函数并加入条件判断，当且仅当该行匹配时才输出
                            write( STDOUT_FILENO , line , line_len );
                            write( STDOUT_FILENO , "\n" , 1 );
                        }
                        suit_or_no = 0;
                        line_len = 0;                           // 遇到换行符时标准输出当前 line 里的行
                    }
                    else{

                        if( line_len == line_cap ){
                            char *tmp = realloc( line , line_cap * 2);
                            if( tmp == NULL ){
                                perror("realloc fail");
                                free( line );
                                close(fd);
                                return 2;
                            }
                            else{
                                line = tmp;
                                line_cap *= 2;
                            }                               // 若行内存不够，将扩容到原来 2 倍
                        }

                        line[line_len] = buffer[i];
                        line_len += 1;                      // 将普通字符添加至 line 末尾
                    }
                }

            }

            if( n == -1 ){                  // 读取错误的处理
                perror("read");
                free( line );
                close(fd);
                return 2;
            }

            if( n == 0 && line_len > 0){
                suit_or_no = suit( line , pattern , line_len , pattern_len );
                if( suit_or_no == 1 ){                              // 调用 suit() 函数并加入条件判断，当且仅当该行匹配时才输出
                    write( STDOUT_FILENO , line , line_len );
                    write( STDOUT_FILENO , "\n" , 1 );
                }

                line_len = 0;                                // 若读取结束，但 line_len != 0，说明 line 里面还有最后一行的内容 → 用以处理文件末尾没有 \n 的情况。
            }
            suit_or_no = 0;
            free( line );
            close(fd);          // 标准结束的处理

        }
    }                                                   // 逐个打印文件名

    return 0;
}
```

##### 测试样例：

###### 新增 `findtest.txt` ，用以测试多行匹配输出：

```
zzh ttkx!
zzh ttkx!
zzh ttkx!
zzh ttkx!
zzh ttkx!
hzh ttkx!
718 ttkx!
```

其余测试文件保持不变

###### 输出结果：

```
$ ./find -n -ic zzh readtest.txt findtest.txt linetest.txt
show_line_number = 1
ignore_case = 1
count_only = 1
pattern: zzh
How many files: 3
file 1 : readtest.txt
zzh ttkx!
file 2 : findtest.txt
zzh ttkx!
zzh ttkx!
zzh ttkx!
zzh ttkx!
zzh ttkx!
file 3 : linetest.txt
zzh ttkx!
hzh ttkx!   zzh ttkx!   yyc ttkx!   lhy ttkx!   zzr ttkx!   yym ttkx!
```

#### 可谓是非常的完而美之！！

wok 我怎么这么厉害（崇拜自己。好爽好爽好爽！从第五步的拼合 `options.c` 和 `line.c` 到这一步的实现匹配并筛选输出，都基本上没有使用 AI 。越来越可以依靠自己走完从想法、逻辑构思、代码实现、结果验证与代码修复的全流程了，而且越来越流畅！！好爽啊这种感觉（hhh再抒发一下）。从小我就对编写代码很热爱，但是就是一直苦于不能靠自己很丝滑地把想法用代码正确实现，总是很卡。哎……果然死去活来——死去了才能活过来，非常感谢自己这段时间的付出与坚持，至少在 C 语言程序设计方面，应该算是让自己这个一开始只有一腔热血的小白成功跨进了 C 语言的大门。

迫不及待地继续。

---

#### 七、实现 `-c`

先从这个最简单的做起，继续在 `find.c` 的基础上进行修改。

##### 加入匹配计数器，及其运算（节选）：

```c
int suit_num = 0;          // 表示某文件里匹配的 line 的数量

...

if( suit_or_no == 1 ){
    suit_num += 1;                      // 匹配数量计数器 +1
}

...
```

##### 并修改打印 `line` 的条件（节选）：

```c
if( suit_or_no == 1 && count_only == 0 ){   
// 调用 suit() 函数并加入条件判断，当且仅当该行匹配且未选择 -c 时才输出
```

##### 优化输出并增加 `count` 输出（节选）：

（去掉了 `file xx : ` 的输出，改成 `文件名: ` ）

```c
if( file_num > 2 ){                 // 只有大于一个文件时才打印文件名
    printf("%s: ", file[i] );
}
...
if( count_only == 1 ){
    printf("%d\n", suit_num );
}
suit_num = 0;           // 匹配计数器归零
...
```

并优化了其他一些细节。

##### 测试结果：

###### 一、多文件输入（输出文件名：`count` ）

```
$ ./find -n -ic zzh readtest.txt findtest.txt linetest.txt
show_line_number = 1
ignore_case = 1
count_only = 1
pattern: zzh
How many files: 3
readtest.txt: 1
findtest.txt: 5
linetest.txt: 2
```

###### 二、单文件输入（直接输出 `count` ）

```
$ ./find -c zzh findtest.txt
show_line_number = 0
ignore_case = 0
count_only = 1
pattern: zzh
How many files: 1
5
```

（前面的状态信息还是暂时不管，用来可视化调试程序的）

#### 好的至此也是完美实现了包含 `-c` 选项的处理了

---

#### 八、实现 `-n` 选项

##### 加入行号计数器以及每次检测到 `\n` 就 `+1` 的运算

```c
int line_num = 0;                   // 行号计数器
...
if( buffer[i] == '\n' ){
    line_num += 1;                  // 行号计数器 +1
...
```

##### 当选项 `-n` 输入时，在匹配的行前输出行号（节选）

```c
if( suit_or_no == 1 && count_only == 0 ){                              // 调用 suit() 函数并加入条件判断，当且仅当该行匹配且未选择 -c 时才输出
    if( show_line_number == 1 ){
        printf("%d: ", line_num );
        fflush(stdout);                         // 强制把 printf() 尚未输出的缓冲内容刷新出去
    } 
    write( STDOUT_FILENO , line , line_len );
    write( STDOUT_FILENO , "\n" , 1 );
}
...
```

###### !!! 重点坑（我踩了）

- `printf()`：经过 C 标准 I/O 缓冲机制输出。

- `write()`：直接通过系统调用写入文件描述符。

- `printf()` 和 `write()` 混用时，**输出顺序可能因为缓冲机制而错乱。**

- `fflush(stdout)`：强制刷新 `stdout` 的输出缓冲区，避免混用两种输出方式时出现顺序问题。

##### 输出测试

```
$ ./find -n zzh findtest.txt readtest.txt
show_line_number = 1
ignore_case = 0
count_only = 0
pattern: zzh
How many files: 2
findtest.txt: 
1: zzh ttkx!
2: zzh ttkx!
3: zzh ttkx!
4: zzh ttkx!
5: zzh ttkx!
readtest.txt: 
2: zzh ttkx!
```

#### 这还说啥了😆😆我好棒棒！

---

#### 九、实现 `-i` 选项

依旧在 `find.c` 的基础上进行修改

##### 更新 `suit()` 函数的条件判断（同时增添函数传入参数：`ignore_case`）

```c
int suit( char *line , char *pattern , ssize_t line_len , ssize_t pattern_len , int ignore_case ){        // 该函数用以扫描 line 里面有没有 pattern
    if( pattern_len > line_len )
        return 0;                               // 若 pattern_len 比 line_len 还大，那么不可能匹配

    if( pattern_len == 0 )
        return 1;                               // 若 pattern_len = 0，即空字符串，则按照题目要求匹配所有行

    int l , t ;                                 // 外层、内层循环标识量
    for( l = 0 ; l <= line_len - pattern_len ; l ++ ){       // 从 line 的首元素开始，区长度为 pattern_len 的一小段与 pattern 对比
        for( t = 0 ; t < pattern_len ; t ++ ){
            if( pattern[t] != line[ l + t ] ){               // 若不完全符合，则将 line 上用以对比的这一小段向后移动 1 个字节
                if( ( line[ l + t ] >= 65 && line[ l + t ] <= 90  || line[ l + t ] >= 97 && line[ l + t ] <= 122 )
                    && ignore_case == 1 
                    && ( line[ l + t ] + 32 == pattern[t] || pattern[t] + 32 == line[ l + t ] ) ){
                    continue;                   // 加入 -i 判断，可以忽略大小写不匹配
                }
                else
                    break;
            }
        }
        if( t == pattern_len )                         // 直到连续 pattern_len 个元素扫描完成，即 line 中存在完全符合 patten 的段
            return 1;
    }

    return 0;
}
```

思路：若匹配时允许 `line` 里的值与 `pattern` 里的值相差 32 ，则实现忽略大小写。

注意限制 `line` 里的值（ `-i` 处理对象）必须处于范围 `A~Z` 和 `a~z` 内

**注意！&& 的优先级大于 ||**

##### 记得在 `main` 函数里更新 `suit()` 的调用传参（节选）

```c
if( buffer[i] == '\n' ){
    line_num += 1;                  // 行号计数器 +1
    suit_or_no = suit( line , pattern , line_len , pattern_len , ignore_case );
```

#### OK 直接拿下，至此要求的功能已经全部完成

删除打印状态指示的代码，至此最终代码 `find.c` 如下：

```c
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int suit( char *line , char *pattern , ssize_t line_len , ssize_t pattern_len , int ignore_case ){        // 该函数用以扫描 line 里面有没有 pattern
    if( pattern_len > line_len )
        return 0;                               // 若 pattern_len 比 line_len 还大，那么不可能匹配

    if( pattern_len == 0 )
        return 1;                               // 若 pattern_len = 0，即空字符串，则按照题目要求匹配所有行

    int l , t ;                                 // 外层、内层循环标识量
    for( l = 0 ; l <= line_len - pattern_len ; l ++ ){       // 从 line 的首元素开始，区长度为 pattern_len 的一小段与 pattern 对比
        for( t = 0 ; t < pattern_len ; t ++ ){
            if( pattern[t] != line[ l + t ] ){               // 若不完全符合，则将 line 上用以对比的这一小段向后移动 1 个字节
                if( line[ l + t ] >= 65 && line[ l + t ] <= 90  || line[ l + t ] >= 97 && line[ l + t ] <= 122
                    && ignore_case == 1 
                    && ( line[ l + t ] + 32 == pattern[t] || pattern[t] + 32 == line[ l + t ] ) ){
                    continue;                   // 加入 -i 判断，可以忽略大小写不匹配
                }
                else
                    break;
            }
        }
        if( t == pattern_len )                         // 直到连续 pattern_len 个元素扫描完成，即 line 中存在完全符合 patten 的段
            return 1;
    }

    return 0;
}


int main(int argc, char *argv[]){
    int i, j, k = 0;                        // 用于循环控制的变量

    int show_line_number = 0;
    int ignore_case = 0;
    int count_only = 0;                 // 3 个 “选项” 参数

    int option = 0;                     // 为了便于参数解析，新建一个状态表示 “是否检验到 ‘状态’ 参数”
    int pat = 0;                        // 为了便于参数解析，新建一个状态表示 “是否检验到 pattern ”

    char *pattern = NULL;               // pattern 存放的位置
    char *file[ argc ];                 // 文件名列表

    int file_num = 1;                   // 文件计数器

    ssize_t pattern_len = 0;            // pattern 长度计数器，初始化为 0 

    int suit_or_no = 0;                 // 设置表示该 line 是否存在匹配 pattern 的段的状态参数。
    int suit_num = 0;                   // 表示某文件里匹配的 line 的数量

    int line_num = 0;                   // 行号计数器

    for( i = 1; i < argc; i++ ){

        if( argv[i][0] == '-' && argv[i][1] != 0){
            j = 1;
            option = 1;

            while( argv[i][j] != 0 ){
            if( argv[i][j] == 'n' )
                show_line_number = 1;
            if( argv[i][j] == 'i' )
                ignore_case = 1;
            if( argv[i][j] == 'c' )
                count_only = 1;
            if( argv[i][j] != 'n' && argv[i][j] != 'i' && argv[i][j] != 'c' ){
                fprintf(stderr, "usage: lrg [-nic] PATTERN [FILE...]\n");
                return 2;
            }

            j ++;

            }                                                   // 识别到 “选项” 时，设置 3 个 “选项” 参数

        }

        if( (pat == 0 && argv[i][0] != '-') || ( pat == 0 && option == 0 ) ){
            pattern = argv[i] ;

            while( pattern[pattern_len] != 0 ){
                pattern_len += 1;
            }                                       // pattern 长度计算

            pat = 1;
            break;                                   // 读取 pattern 并防止重复读取以及 pattern 再次被识别成文件名
        }

    }

    if( pat == 0 ){
        fprintf(stderr, "usage: lrg [-nic] PATTERN [FILE...]\n");
        return 2; 
    }
                                              // 未解析到 pattern 时返回 2

    for( i = i + 1 ; i < argc ; i ++ ){
        file[file_num] = argv[i];
        file_num ++ ;
    }                                                   // 逐个解析文件名

    // printf("show_line_number = %d\n", show_line_number);
    // printf("ignore_case = %d\n", ignore_case);
    // printf("count_only = %d\n", count_only);
    // printf("pattern: %s\n", pattern);
    // printf("How many files: %d\n", file_num - 1);                // 打印状态

    if( file_num != 1){
        for( i = 1; i < file_num; i ++ ){
            if( file_num > 2 ){                         // 只有大于一个文件时才打印文件名
                printf("%s: \n", file[i] );
            }

            int fd = open(file[i], O_RDONLY);       // 以只读打开 argv[1] 中文件名对应的文件，并生成文件描述符

            if( fd == -1 ){
                perror("lrg: open file fail");
                return 2;
            }

            char buffer[16];                // 创建缓存区（当前设置 16 字节）
            ssize_t n, written = 0;                      // 设置变量 n, written 用以存储 read() 和 write() 的返回值

            char *line = NULL;
            size_t line_len = 0;
            size_t line_cap = 64;

            line = malloc( line_cap ) ;
            if( line == NULL ){
                perror("lrg: malloc fail");
                return 2;
            }

            while((n = read( fd, buffer, sizeof buffer)) > 0 ){         // 条件判断（是否读取完毕） & 读取文件写入缓存区

                for( size_t i = 0 ; i < n ; i ++ ){
                    if( buffer[i] == '\n' ){
                        line_num += 1;                  // 行号计数器 +1
                        suit_or_no = suit( line , pattern , line_len , pattern_len , ignore_case );
                        if( suit_or_no == 1 ){
                            suit_num += 1;                      // 匹配数量计数器 +1
                        }
                        if( suit_or_no == 1 && count_only == 0 ){                              // 调用 suit() 函数并加入条件判断，当且仅当该行匹配且未选择 -c 时才输出
                            if( show_line_number == 1 ){
                                printf("%d: ", line_num );
                                fflush(stdout);                         // 强制把 printf() 尚未输出的缓冲内容刷新出去
                            } 
                            write( STDOUT_FILENO , line , line_len );
                            write( STDOUT_FILENO , "\n" , 1 );
                        }
                        suit_or_no = 0;
                        line_len = 0;                           // 遇到换行符时标准输出当前 line 里的行
                    }
                    else{

                        if( line_len == line_cap ){
                            char *tmp = realloc( line , line_cap * 2);
                            if( tmp == NULL ){
                                perror("lrg: realloc fail");
                                free( line );
                                close(fd);
                                return 2;
                            }
                            else{
                                line = tmp;
                                line_cap *= 2;
                            }                               // 若行内存不够，将扩容到原来 2 倍
                        }

                        line[line_len] = buffer[i];
                        line_len += 1;                      // 将普通字符添加至 line 末尾
                    }
                }

            }

            if( n == -1 ){                  // 读取错误的处理
                perror("lrg: read file fail");
                free( line );
                close(fd);
                return 2;
            }

            if( n == 0 && line_len > 0){                // 若读取结束，但 line_len != 0，说明 line 里面还有最后一行的内容 → 用以处理文件末尾没有 \n 的情况。
                line_num += 1;                          // 行号计数器 +1
                suit_or_no = suit( line , pattern , line_len , pattern_len , ignore_case );
                if( suit_or_no == 1 ){
                    suit_num += 1;                      // 匹配数量计数器 +1
                }
                if( suit_or_no == 1 && count_only == 0 ){                              // 调用 suit() 函数并加入条件判断，当且仅当该行匹配且未选择 -c 时才输出
                    if( show_line_number == 1 ){
                        printf("%d: ", line_num );
                        fflush(stdout);                 // 强制把 printf() 尚未输出的缓冲内容刷新出去
                    }
                    write( STDOUT_FILENO , line , line_len );
                    write( STDOUT_FILENO , "\n" , 1 );
                }

                line_len = 0;                                
            }
            suit_or_no = 0;

            if( count_only == 1 ){
                printf("%d\n", suit_num );
            }
            suit_num = 0;           // 匹配计数器归零
            line_num = 0;
            free( line );
            close(fd);          // 标准结束的处理

        }
    }                                                   

    return 0;
}
```

过程中也进行了一些错误处理，现在来完成剩下部分。

---

#### 十、错误处理汇总

至此，`find.c` 创建副本并归档，副本正式更名为 `lrg.c` 

##### 先列举已经能够处理的错误、错误提示和错误码：

###### 一、目前已经实现的错误处理

| 错误情况                    | 当前错误提示                                | 返回码 | 实现情况                     |
| ----------------------- | ------------------------------------- | --- | ------------------------ |
| 缺少 `PATTERN`            | `usage: lrg [-nic] PATTERN [FILE...]` | `2` | 已实现                      |
| 出现未知选项字符，例如 `-x`、`-nix` | `usage: lrg [-nic] PATTERN [FILE...]` | `2` | 已实现                      |
| `open()` 打开文件失败         | `lrg: open file fail: ...`            | `2` | 已实现提示与返回码，但还有后续处理问题      |
| `read()` 读取文件失败         | `lrg: read file fail: ...`            | `2` | 已实现提示与返回码，但尚未处理 `EINTR`  |
| `malloc()` 分配内存失败       | `lrg: malloc fail: ...`               | `2` | 已实现提示与返回码，但没有关闭已打开的文件    |
| `realloc()` 扩容失败        | `lrg: realloc fail: ...`              | `2` | 已实现提示、释放 `line`、关闭文件及返回码 |

这里的 `...` 表示 `perror()` 根据 `errno` 输出的系统错误描述，例如 `No such file or directory`。

###### 二、题目要求但尚未实现，或尚未完全实现的错误处理

| 题目要求                   | 你当前的实现情况 | 正确行为要求                                    | 应返回的错误码             |
| ---------------------- | -------- | ----------------------------------------- | ------------------- |
| 打开文件失败后继续处理其他文件        | ❌ 未实现    | 输出错误信息，跳过当前文件，继续处理剩余文件                    | 最终返回 `2`            |
| 读取文件时遇到 `EINTR`        | ❌ 未实现    | 判断 `errno == EINTR`，重新调用 `read()`，而不是直接退出 | 不应仅因 `EINTR` 返回 `2` |
| 多个文件中某个文件读取失败后继续处理其他文件 | ❌ 未实现    | 释放当前文件的资源，继续处理其他文件，最终返回 `2`               | 最终返回 `2`            |
| 所有文件处理完成后，根据错误情况决定退出码  | ⚠️ 未实现   | 即使部分文件成功，只要发生错误，最终仍返回 `2`                 | `2`                 |
| 没有任何匹配结果时返回 `1`        | ❌ 未实现    | 没有错误且没有匹配行时返回 `1`                         | `1`                 |
| 有匹配结果且没有错误时返回 `0`      | ⚠️ 部分实现  | 当前程序正常结束时固定返回 `0`，没有记录全局是否匹配              | `0`                 |

好的现在开始逐个处理：

##### （1）实现多个文件中某个文件打开失败后继续处理其他文件

###### 创建表示文件打开错误的状态参数

```c
int open_file_fail = 0;             // 表示状态：文件是否打开失败。用以程序在一个文件打开失败后继续处理后续文件并最终返回 2
```

###### 在出现文件打开失败后先记录状态而不是直接 return

```c
int fd = open(file[i], O_RDONLY);       // 以只读打开 argv[1] 中文件名对应的文件，并生成文件描述符

    if( fd == -1 ){
        perror("lrg: open file fail");
        open_file_fail = 1;
        continue;               // 实现当某个文件打开错误的时候可以继续处理后续文件
    }
```

###### 全部文件处理完成后，根据状态决定返回值

```c
if( open_file_fail == 1 ){
    return 2;                           // 若曾出现文件打开失败最终返回 2
}
```

##### （2） 多个文件中某个文件读取失败后继续处理其他文件（暂时忽略 EINTR ）

###### 创建表示文件读取错误的状态参数

```c
int read_file_fail = 0;             // 表示状态：文件是否读取失败。用以程序在一个文件读取失败后继续处理后续文件并最终返回 2
```

###### 在出现文件读取失败后先记录状态而不是直接 return

```c
if( n == -1 ){                  // 读取错误的处理
    perror("lrg: read file fail");
    free( line );
    close(fd);
    read_file_fail = 1;
    suit_num = 0;
    line_num = 0;
    continue;
}
```

###### 全部文件处理完成后，根据状态决定返回值

```c
if( open_file_fail == 1 || read_file_fail == 1 ){
    return 2;               // 若曾出现文件打开失败最终返回 2
}
```

！！注意，文件读取失败后不要忘记把 `suit_num` 和 `line_num` 计数器清零。

##### （3）满足题目要求，将错误信息一律写到 **stderr**，并格式化输出

###### 添加头文件：

```c
#include <errno.h>
#include <string.h>  
```

- `<errno.h>`：提供 `errno`，用于获取系统调用失败时的错误代码。

- `<string.h>`：提供 `strerror()`，将错误代码转换为可读的原因文本

###### 修改 `perror` ，利用 `fprintf` 将错误信息一律写到 stdder

用 `open()` 为例，其他几处类似。

```c
// perror("lrg: open file fail");
    int err = errno;  // 保存 errno ，防止后续调用函数导致 errno 被篡改
    fprintf( stderr , "lrg: %s: %s\n", file[i] , strerror(err) );
```

！！重点：在调用 `fprintf` 打印错误信息前记得保存 `errno` ，防止后续调用函数导致 `errno` 被篡改。

- 过程中修复一个小问题：`malloc` 失败后没有 `close(fd)` 

##### （4）实现读取中断后重试（解决 EINTR）

###### `EINTR` 是什么？

- `EINTR` 是一个错误码，英文是 Interrupted system call，意思是“系统调用被中断”。

进程可能收到一个信号（signal），如果这个信号打断了系统调用，而且系统调用没有自动重新启动，那么 `read()` 就可能返回 `-1`，并将 `errno` 设置为 `EINTR`。

- 所以我们只需要在 `read()` 返回 `-1` 时，再读取 `errno` 。若等于 `EINTR` 则尝试重新读取。

- 另外，如果 `read()` 在被信号打断之前已经读取了一部分数据，它通常会返回已经读取的字节数，而不是 `-1`。所以不要把所有与信号有关的情况都当成 `EINTR`。但是我的程序本来就是读取完成一次而后进行逐字节处理，所以此种情况不需要再单独判断。

好的，那我们开始处理

###### 使用 `goto` 语法，遇到 `EINTR` 时回到 `read()` 重新执行读取

改进后的错误判断（分为 `EINTR` 错误和一般错误）：

```c
if( n == -1 ){                  // 读取错误的处理
    // perror("lrg: read file fail");
    int err = errno;
    if( err == EINTR ){
        goto read;
    }
    else{
        fprintf( stderr , "lrg: %s: %s\n", file[i] , strerror(err) );
        free( line );
        close(fd);
        read_file_fail = 1;
        suit_num = 0;
        line_num = 0;
        continue;
    }
}
```

`read` 标签的位置：

```c
read:
        while((n = read( fd, buffer, sizeof buffer)) > 0 ){         // 条件判断（是否读取完毕） & 读取文件写入缓存区
...
```

- 这样就实现了遇到 `read()` 的 `EINTR` 错误时重新执行读取

##### （5）实现当没有任何错误且没有任何匹配项时返回 1

因为在每个文件被检索完成后，`suit_num` 会被重置为 `0` ，所以不能用 `suit_num` 来进行判断。

###### 于是我们新建一个状态参数：

```c
int matched = 0;                    // 表示状态：是否曾至少一次匹配成功
```

###### 在原来程序的基础上，每次 `suit_num += 1` 之后就立刻将 `matched` 复制 `1`

用以表示状态：是否曾至少一次匹配成功。

因为此参数从不清零，故可以用来判断 “是否从来没有成功匹配”

###### 最终判断：

```c
if( matched == 0 ){
    return 1;                   // 若没有发生错误且没有任何匹配最终返回 1
}
```

- 至此已完成题目对返回值的所有要求

##### （6）当未解析到文件名时，将标准输入作为源

###### 改动条件并增添判断：

```c
...
if( file_num > 0 ){
    for( i = 1; i < ( file_num == 1 ? 2 : file_num ); i ++ ){

        int fd;
        if( file_num != 1 )
            fd = open(file[i], O_RDONLY);       // 以只读打开 argv[1] 中文件名对应的文件，并生成文件描述符
        else
            fd = STDIN_FILENO;          // 若没有键入文件名，那么将标准输入作为源
...
```

这样就可以在程序一开始选择源了。

其中表达式 `file_num == 1 ? 2 : file_num` 是 AI 提供的解决思路，解决当文件名不存在即 `file_num = 1` 时程序根本进入不了 `for()` 的问题。**我认为非常非常巧妙。作为经验积累下来。**

经过测试，成功。

##### （7）格式化输出（文件名相关）

###### 按照题目期望，总结出以下格式要求：

| 文件名个数 | `-i`/无选项   | `-in`/`-n`     | `-c`            |
| ----- | ---------- | -------------- | --------------- |
| 0     | 直接输出匹配行    | 直接输出带行号的匹配行    | 直接输出 `count`    |
| 1     | 直接输出匹配行    | 直接输出带行号的匹配行    | 直接输出 `count`    |
| > 1   | 输出文件名: 匹配行 | 输出文件名: 带行号的匹配行 | 输出 `文件名: count` |

- 无匹配行：什么也不输出

- 多个文件的情况从题目要求里看不出来，但是按照逻辑讲，这种情况也应该在每行前输出文件名。

现在依照这些要求对程序进行修改。

###### 首先，删除了开头打印文件名的代码。

###### 然后我们直接去 `-c` 和 `-n` 控制的地方进行修改。

`-c` 区修改后：

```c
if( count_only == 1 ){
    if( file_num > 2 )
        printf("%s: ", file[i] );
    printf("%d\n", suit_num );
}
```

`-n` / 无选项修改后（节选）：

```c
if( suit_or_no == 1 && count_only == 0 ){                              // 调用 suit() 函数并加入条件判断，当且仅当该行匹配且未选择 -c 时才输出
    if( file_num > 2 ){
        printf("%s: ", file[i] );
        fflush(stdout);
    }
    if( show_line_number == 1 ){
        printf("%d: ", line_num );
        fflush(stdout);                         // 强制把 printf() 尚未输出的缓冲内容刷新出去
    } 
    write( STDOUT_FILENO , line , line_len );
    write( STDOUT_FILENO , "\n" , 1 );
}
```

解决，现在可以按照上表展示的格式输出了。

##### （8）`-i` bug 修复

修复后：

```c
if( ( pattern[t] >= 65 && pattern[t] <= 90  || pattern[t] >= 97 && pattern[t] <= 122 )
    && ( line[ l + t ] >= 65 && line[ l + t ] <= 90  || line[ l + t ] >= 97 && line[ l + t ] <= 122 )
    && ignore_case == 1 
    && ( line[ l + t ] + 32 == pattern[t] || pattern[t] + 32 == line[ l + t ] ) ){
    continue;                   // 加入 -i 判断，可以忽略大小写不匹配
```

此次加入了 `pattern[t]` 是否是英文字母的判断（第一行），这样确保了 `pattern[t]` 和 `line[ l + t ]` 都是英文字母。判断更加严密。

##### （9）又解决了一些杂项，略。

###### 展示完整代码：

```c
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>  

int suit( char *line , char *pattern , ssize_t line_len , ssize_t pattern_len , int ignore_case ){        // 该函数用以扫描 line 里面有没有 pattern
    if( pattern_len > line_len )
        return 0;                               // 若 pattern_len 比 line_len 还大，那么不可能匹配

    if( pattern_len == 0 )
        return 1;                               // 若 pattern_len = 0，即空字符串，则按照题目要求匹配所有行

    int l , t ;                                 // 外层、内层循环标识量
    for( l = 0 ; l <= line_len - pattern_len ; l ++ ){       // 从 line 的首元素开始，区长度为 pattern_len 的一小段与 pattern 对比
        for( t = 0 ; t < pattern_len ; t ++ ){
            if( pattern[t] != line[ l + t ] ){               // 若不完全符合，则将 line 上用以对比的这一小段向后移动 1 个字节
                if( ( pattern[t] >= 65 && pattern[t] <= 90  || pattern[t] >= 97 && pattern[t] <= 122 )
                    && ( line[ l + t ] >= 65 && line[ l + t ] <= 90  || line[ l + t ] >= 97 && line[ l + t ] <= 122 )
                    && ignore_case == 1 
                    && ( line[ l + t ] + 32 == pattern[t] || pattern[t] + 32 == line[ l + t ] ) ){
                    continue;                   // 加入 -i 判断，可以忽略大小写不匹配
                }
                else
                    break;
            }
        }
        if( t == pattern_len )                         // 直到连续 pattern_len 个元素扫描完成，即 line 中存在完全符合 patten 的段
            return 1;
    }
    
    return 0;
}


int main(int argc, char *argv[]){
    int i, j, k = 0;                        // 用于循环控制的变量

    int show_line_number = 0;
    int ignore_case = 0;
    int count_only = 0;                 // 3 个 “选项” 参数

    int option = 0;                     // 为了便于参数解析，新建一个状态表示 “是否检验到 ‘状态’ 参数”
    int pat = 0;                        // 为了便于参数解析，新建一个状态表示 “是否检验到 pattern ”

    char *pattern = NULL;               // pattern 存放的位置
    char *file[ argc ];                 // 文件名列表

    int file_num = 1;                   // 文件计数器

    ssize_t pattern_len = 0;            // pattern 长度计数器，初始化为 0 

    int suit_or_no = 0;                 // 设置表示该 line 是否存在匹配 pattern 的段的状态参数。
    int suit_num = 0;                   // 表示某文件里匹配的 line 的数量
    
    int line_num = 0;                   // 行号计数器

    int open_file_fail = 0;             // 表示状态：文件是否打开失败。用以程序在一个文件打开失败后继续处理后续文件并最终返回 2
    int read_file_fail = 0;             // 表示状态：文件是否读取失败。用以程序在一个文件读取失败后继续处理后续文件并最终返回 2

    int matched = 0;                    // 表示状态：是否曾至少一次匹配成功

    for( i = 1; i < argc; i++ ){

        if( argv[i][0] == '-' && argv[i][1] != 0){
            j = 1;
            option = 1;

            while( argv[i][j] != 0 ){
            if( argv[i][j] == 'n' )
                show_line_number = 1;
            if( argv[i][j] == 'i' )
                ignore_case = 1;
            if( argv[i][j] == 'c' )
                count_only = 1;
            if( argv[i][j] != 'n' && argv[i][j] != 'i' && argv[i][j] != 'c' ){
                fprintf(stderr, "usage: lrg [-nic] PATTERN [FILE...]\n");
                return 2;
            }
                
            j ++;

            }                                                   // 识别到 “选项” 时，设置 3 个 “选项” 参数

        }

        if( (pat == 0 && argv[i][0] != '-') || ( pat == 0 && argv[i][0] == '-' && argv[i][1] == 0 ) ){
            pattern = argv[i] ;

            while( pattern[pattern_len] != 0 ){
                pattern_len += 1;
            }                                       // pattern 长度计算

            pat = 1;
            break;                                   // 读取 pattern 并防止重复读取以及 pattern 再次被识别成文件名
        }

    }

    if( pat == 0 ){
        fprintf(stderr, "usage: lrg [-nic] PATTERN [FILE...]\n");
        return 2; 
    }
                                              // 未解析到 pattern 时返回 2

    for( i = i + 1 ; i < argc ; i ++ ){
        file[file_num] = argv[i];
        file_num ++ ;
    }                                                   // 逐个解析文件名

    // printf("show_line_number = %d\n", show_line_number);
    // printf("ignore_case = %d\n", ignore_case);
    // printf("count_only = %d\n", count_only);
    // printf("pattern: %s\n", pattern);
    // printf("How many files: %d\n", file_num - 1);                // 打印状态
    
    if( file_num > 0){
        for( i = 1; i < ( file_num == 1 ? 2 : file_num ); i ++ ){
            
            int fd;
            if( file_num != 1 )
                fd = open(file[i], O_RDONLY);       // 以只读打开 argv[1] 中文件名对应的文件，并生成文件描述符
            else
                fd = STDIN_FILENO;          // 若没有键入文件名，那么将标准输入作为源

            if( fd == -1 ){
                // perror("lrg: open file fail");
                int err = errno;
                if( file_num != 1 )
                    fprintf( stderr , "lrg: %s: %s\n", file[i] , strerror(err) );
                else
                    fprintf( stderr , "lrg: standard input: %s\n", strerror(err) );
                open_file_fail = 1;
                continue;               // 实现当某个文件打开错误的时候可以继续处理后续文件
            }

            char buffer[16];                // 创建缓存区（当前设置 16 字节）
            ssize_t n, written = 0;                      // 设置变量 n, written 用以存储 read() 和 write() 的返回值

            char *line = NULL;
            size_t line_len = 0;
            size_t line_cap = 64;

            line = malloc( line_cap ) ;
            if( line == NULL ){
                // perror("lrg: malloc fail");
                int err = errno;
                if( file_num != 1 )
                    fprintf( stderr , "lrg: %s: %s\n", file[i] , strerror(err) );
                else
                    fprintf( stderr , "lrg: standard input: %s\n", strerror(err) );
                close(fd);
                return 2;
            }
read:
            while((n = read( fd, buffer, sizeof buffer)) > 0 ){         // 条件判断（是否读取完毕） & 读取文件写入缓存区

                for( size_t j = 0 ; j < n ; j ++ ){
                    if( buffer[j] == '\n' ){
                        line_num += 1;                  // 行号计数器 +1
                        suit_or_no = suit( line , pattern , line_len , pattern_len , ignore_case );
                        if( suit_or_no == 1 ){
                            suit_num += 1;                      // 匹配数量计数器 +1
                            matched = 1;
                        }
                        if( suit_or_no == 1 && count_only == 0 ){                              // 调用 suit() 函数并加入条件判断，当且仅当该行匹配且未选择 -c 时才输出
                            if( file_num > 2 ){
                                printf("%s: ", file[i] );
                                fflush(stdout);
                            }
                            if( show_line_number == 1 ){
                                printf("%d: ", line_num );
                                fflush(stdout);                         // 强制把 printf() 尚未输出的缓冲内容刷新出去
                            } 
                            write( STDOUT_FILENO , line , line_len );
                            write( STDOUT_FILENO , "\n" , 1 );
                        }
                        suit_or_no = 0;
                        line_len = 0;                           // 遇到换行符时标准输出当前 line 里的行
                    }
                    else{

                        if( line_len == line_cap ){
                            char *tmp = realloc( line , line_cap * 2);
                            if( tmp == NULL ){
                                // perror("lrg: realloc fail");
                                int err = errno;
                                if( file_num != 1 )
                                    fprintf( stderr , "lrg: %s: %s\n", file[i] , strerror(err) );
                                else
                                    fprintf( stderr , "lrg: standard input: %s\n", strerror(err) );
                                free( line );
                                close(fd);
                                return 2;
                            }
                            else{
                                line = tmp;
                                line_cap *= 2;
                            }                               // 若行内存不够，将扩容到原来 2 倍
                        }
                        
                        line[line_len] = buffer[j];
                        line_len += 1;                      // 将普通字符添加至 line 末尾
                    }
                }

            }

            if( n == -1 ){                  // 读取错误的处理
                // perror("lrg: read file fail");
                int err = errno;
                if( err == EINTR ){
                    goto read;
                }
                else{
                    if( file_num != 1 )
                        fprintf( stderr , "lrg: %s: %s\n", file[i] , strerror(err) );
                    else
                        fprintf( stderr , "lrg: standard input: %s\n", strerror(err) );
                    free( line );
                    close(fd);
                    read_file_fail = 1;
                    suit_num = 0;
                    line_num = 0;
                    continue;
                }
                
            }

            if( n == 0 && line_len > 0){                // 若读取结束，但 line_len != 0，说明 line 里面还有最后一行的内容 → 用以处理文件末尾没有 \n 的情况。
                line_num += 1;                          // 行号计数器 +1
                suit_or_no = suit( line , pattern , line_len , pattern_len , ignore_case );
                if( suit_or_no == 1 ){
                    suit_num += 1;                      // 匹配数量计数器 +1
                    matched = 1;
                }
                if( suit_or_no == 1 && count_only == 0 ){                              // 调用 suit() 函数并加入条件判断，当且仅当该行匹配且未选择 -c 时才输出
                    if( file_num > 2 ){
                        printf("%s: ", file[i] );
                        fflush(stdout);
                    }
                    if( show_line_number == 1 ){
                        printf("%d: ", line_num );
                        fflush(stdout);                 // 强制把 printf() 尚未输出的缓冲内容刷新出去
                    }
                    write( STDOUT_FILENO , line , line_len );
                    write( STDOUT_FILENO , "\n" , 1 );
                }

                line_len = 0;                                
            }
            suit_or_no = 0;

            if( count_only == 1 ){
                if( file_num > 2 )
                    printf("%s: ", file[i] );
                printf("%d\n", suit_num );
            }
            suit_num = 0;           // 匹配计数器归零
            line_num = 0;
            free( line );
            close(fd);          // 标准结束的处理
            
            
        }
    }                                                   

    if( open_file_fail == 1 || read_file_fail == 1 ){
        return 2;                           // 若曾出现文件打开失败最终返回 2
    }

    if( matched == 0 ){
        return 1;                           // 若没有发生错误且没有任何匹配最终返回 1
    }

    return 0;
}
```

经过我很多的测试，应该是真的没有问题了

给出几个测试示例：

示例一：单文件，多选项

```
$ ./lrg -n -i zzh findtest.txt
1: zzh ttkx!
2: zzh ttkx!
3: zzh ttkx!
4: zzh ttkx!
5: zzh ttkx!
8: ZZH ttkx!

```

示例二：多文件，合并选项

```
$ ./lrg -ni zzh readtest.txt findtest.txt
readtest.txt: 2: zzh ttkx!
findtest.txt: 1: zzh ttkx!
findtest.txt: 2: zzh ttkx!
findtest.txt: 3: zzh ttkx!
findtest.txt: 4: zzh ttkx!
findtest.txt: 5: zzh ttkx!
findtest.txt: 8: ZZH ttkx!

```

示例三：非法输入

```
$ ./lrg -x zzh readtest.txt
usage: lrg [-nic] PATTERN [FILE...]

```

示例四：多文件，`-c` + `-ni` 干扰 + 打开文件失败

```
$ ./lrg -c -ni zzh readtest.txt findtest.txt no_such_file.txt
readtest.txt: 1
findtest.txt: 6
lrg: no_such_file.txt: No such file or directory

```

示例五：标准输入（使用 `findtest.txt` ）

```
$ ./lrg -i -n zzh
zzh ttkx!
zzh ttkx!
zzh ttkx!
zzh ttkx!
zzh ttkx!
hzh ttkx!
718 ttkx!
ZZH ttkx!
LHY ttkx!1: zzh ttkx!
2: zzh ttkx!
3: zzh ttkx!
4: zzh ttkx!
5: zzh ttkx!
8: ZZH ttkx!

```

... 更多样例与边界条件略，欢迎学长随意测试

（反正我测试了很多边界条件也都没有发现问题哈哈哈）

---

#### 十一、目前实现的错误提示和返回清单

| 错误情况                    | 当前错误提示                                | 返回码 |
| ----------------------- | ------------------------------------- | --- |
| 缺少 `PATTERN`            | `usage: lrg [-nic] PATTERN [FILE...]` | `2` |
| 出现未知选项字符，例如 `-x`、`-nix` | `usage: lrg [-nic] PATTERN [FILE...]` | `2` |
| `open()` 打开文件失败         | `lrg: 文件名: 错误原因`                      | `2` |
| `read()` 读取文件失败         | `lrg: 文件名: 错误原因`                      | `2` |
| `malloc()` 分配内存失败       | `lrg: 文件名: 错误原因`                      | `2` |
| `realloc()` 扩容失败        | `lrg: 文件名: 错误原因`                      | `2` |
| 存在匹配且未发生错误              | 无错误提示                                 | `0` |
| 没有匹配且未发生错误              | 无错误提示                                 | `1` |

---

#### 终于算是写完了。。。啊好累😫

写的过程是越写越爽的…… debug 的过程是越来越绝望的，跟坐牢一样。修复一个问题又蹦出来另一个问题…… 不过还好当全部问题都修好之后还是非常有成就感的，看到自己写的程序能处理各种各样的异常情况还是非常满足的。而且这是我自己写的第一个有比较有实用意义而且功能比较高级的程序，还是非常的开心，也是体验到了开发一个能实现某种功能的软件的快乐了哈哈哈！

最大的感受就是现在写 C 语言越来越上手了，可能是经历了 asm 的历练（苦笑），现在感觉 C 语言咋这么好用呢？？简直就是手到擒来般的丝滑。这个工程绝对算是我现在开发过的最大的项目，真的是给我写爽了（我指的是满足🤣

真的还是非常非常感谢学长们能仔细阅读我的题解，你们鼓励的评语真的是我做题非常大的动力，而且通过你们认真的反馈我也能及时找出自己的不足，并回头加强学习。至于题解用力过猛嘛…… 其实每次的 markdown 一方面是要求上交的题解，另一方面是我用以梳理思绪的上佳载体，用 markdown 记录下思维过程能让我更高效地理解。而且最后也算是我收获的非常珍贵的学习笔记，足够详细也就非常便于日后的复习。毕竟题是我自己做的，笔记也是我自己做的，所以哪些知识点对我来说是重点都能在 markdown 笔记里面体现出来，一开始我写这样的笔记本来也就是为了学习到真东西哈哈哈！就是确实苦了你们改题人！实在抱歉！以后可以通过我的各种标题来快速浏览我的思路和实现~ 主要还是这些题目选的太好了，一点都不想浪费！

ok 那我先歇息了😆~ 可为了这些个招新题熬了好几个夜呢！

辛苦你们！

---

## 参考资料

- 主旋律：https://chatgpt.com/share/6ad64018-accc-83eb-a78c-0108dbef7800

- C 语法和杂项辅助：https://chat.deepseek.com/share/mq5usyusjdh8wp669i

- Linux 语法和相关知识学习：https://chatgpt.com/share/6ad64071-0ae4-83ed-9828-7630680eb002

---

`Made by Jacky_Zhang Zhehao`

> 顾名思义，这是一个用于存放`ACM`竞赛与训练代码的仓库。
> 模板代码来源比较分散，主要来自各路OJ的提交记录，如有侵权，实在抱歉，请与我联系。

## 免责声明

所有代码都**没有**经过`format`处理，处处是压行，码风奇差，任何的阅读障碍都属于正常情况。

同时，不保证代码的正确性，特别是`template`目录下的。

---

如果你**不幸**用了本仓库的代码，并且喜提`WA`，可以从以下方面考虑`debug`:

+ 注意起始下标（作者码风奇差，`0-indexed`和`1-indexed`混用严重）
+ **变量名习惯**的差异（比较细的细节，建议仔细甄别）
+ 是否定义了与本代码模板**相同的宏**，但是实现不同。
  尽可能只使用如下的宏：
  ```cpp
  #define PII pair<int, int>
  #define vec vector
  #define str string
  #define fi first
  #define se second
  #define all(a) a.begin(), a.end()
  #define SZ(x) static_cast<int>((x).size())

  using db = double;
  using ll = long long;
  ```
  编译参数如下：
  ```cmd
  -std=c++17 -Wall -Ofast -DLOCAL -ID:\Document\repos\Code-of-ACM\template\debug\
  ```
+ **本模板出错（或者适用范围与你所面对的问题不同）** 若您能提交`PR`解决或者在`issue`中提出，本人将不胜感激。
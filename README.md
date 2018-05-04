# uy_shared_ptr
C++ 中动态内存的管理通过一对运算符 new 和 delete 进行申请和释放，而在正确的时机释放内存是很困难的。

使用动态内存容易出现的问题

> * 当我们失去了指向动态内存的指针时，意味着我们永远也找不到这块内存空间，也同样无法释放它，这样就造成了所谓的内存泄漏。

> * 而当我们不小心释放了这块动态内存，却还有指针指向它并对之进行操作时，就访问了非法内存，这是严重的错误并将导致不可预估的后果。

> * 对同一块内存释放两次
这时智能指针的作用就体现出来了。
通过引用计数，我们可以知道当前有多少指针指向这块内存。
当引用计数为 0 时，意味着没有指针可以找到这块内存（实际上智能指针本身此时还持有这块内存的指针），此时应当释放这块内存。

对智能指针的拷贝和赋值会增加引用计数，智能指针的析构或改变指向的对象等操作会减少引用计数。

我们使用动态内存通常都是出于以下原因

> * 程序在运行前无法确定自己需要使用多少个对象
> * 程序在运行前无法确定所需对象的类型
> * 程序需要在多个对象间共享数据

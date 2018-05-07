# uy_shared_ptr
C++ 中动态内存的管理通过一对运算符 new 和 delete 进行申请和释放，而在正确的时机释放内存是很困难的。

使用动态内存容易出现的问题

> * 当我们失去了指向动态内存的指针时，意味着我们永远也找不到这块内存空间，也同样无法释放它，这样就造成了所谓的内存泄漏。
> * 而当我们不小心释放了这块动态内存，却还有指针指向它并对之进行操作时，就访问了非法内存，这是严重的错误并将导致不可预估的后果。
> * 对同一块内存释放两次。



我们使用动态内存通常都是出于以下原因

> * 程序在运行前无法确定自己需要使用多少个对象。
> * 程序在运行前无法确定所需对象的类型。
> * 程序需要在多个对象间共享数据。
。
## 实现

通过引用计数，我们可以知道当前有多少指针指向这块内存。

当引用计数为 0 时，意味着没有指针可以找到这块内存（实际上智能指针本身此时还持有这块内存的指针），此时应当释放这块内存。

对智能指针的拷贝和赋值会增加引用计数，智能指针的析构或改变指向的对象等操作会减少引用计数。

## 注意点

* 在不需要使用 shared_ptr 时，应尽量使用 unique_ptr ，shared_ptr 需要消耗更多的资源来维护引用计数并可能在无意间赋值给另一个 shared_ptr 造成非期待的后果。
* 谨慎使用裸指针，裸指针和智能指针混用可能导致动态的内存的地址被赋值给了裸指针，而 shared_ptr 的引用计数却没有增加，这样可能导致在智能指针释放内存后，却不慎通过保存下来的裸指针访问了非法内存。
* 不使用静态分配的内存初始化智能指针，智能指针释放空间时试图 delete 非动态分配的内存将导致未定义的行为。
* get() 返回的是裸指针，应谨慎使用。
* 有时为了判断对象是否还存在，可以通过一个弱指针 weak_ptr 调用 lock() 方法尝试提升为一个 shared_ptr 来判断对象是否已被删除。
* 使用动态数组时，应该使用自定义的 deleter ,否则只会释放数组的第一个对象（默认情况使用delete,而我们期待使用delete[]，可以通过显示传入一个删除器解决），而剩余对象所在内存未被释放将会造成内存泄漏。
* 使用 shared_ptr 应避免循环引用，这样引用计数都被增加，都得不到释放。

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>

class FuckClass {
public:
    FuckClass(): ptr_(nullptr) {}
    FuckClass(int value): ptr_(new int(value))
    {  // 构造函数，存在开辟内存、复制资源的操作
        std::cout << "Default constructor called: MyClass(int value)" << std::endl;
    }
    FuckClass(const FuckClass& other)  // 拷贝构造函数，存在开辟内存、复制资源的操作
        :
        ptr_(new int(*other.ptr_))
    {
        std::cout << "Copy constructor called: MyClass(const MyClass& other)" << std::endl;
    }
    FuckClass& operator=(const FuckClass& other)
    {
        /*
         * 拷贝运算符
         */
        if (&other == this) {
            return *this;  // 自我赋值，直接返回
        }
        if (ptr_) {
            delete ptr_;  // 释放原有内存
        }
        ptr_ = new int(*other.ptr_);

        std::cout << "Copy assignment called: FuckClass&operator=(const MyClass& other)" << std::endl;
        return *this;
    }
    FuckClass(FuckClass&& other) noexcept  // 移动构造函数，只是地址的复制，没有新开内存、资源复制
        :
        ptr_(other.ptr_)
    {
        other.ptr_ = nullptr;
        std::cout << "FuckClass move constructor called: FuckClass(MyClass&& other)" << std::endl;
    }
    FuckClass& operator=(FuckClass&& other)
    {
        /*
         * 移动运算符
         */
        other.ptr_ = nullptr;
        std::cout << "FuckClass assignment fucntion called: FuckClass& operator=(FuckClass&& other)" << std::endl;
        return *this;
    }
    ~FuckClass()
    {
        if (ptr_) {
            delete ptr_;
        }
        std::cout << "Destructor called." << std::endl;
    }
    int GetValue(void)
    {
        return *ptr_;
    }
    void PrintData() const
    {
        std::cout << "Data: " << *ptr_ << std::endl;
    }

private:
    int* ptr_;  // 相当于Class内部管理的资源
};
FuckClass test_call(FuckClass ite)
{
    return ite;
}
int main(void)
{
    FuckClass obj1(10);  // 调用默认构造函数
    FuckClass obj2;
    obj2 = std::move(obj1);            // 调用移动构造函数
    FuckClass obj3(30);                // 调用默认构造函数
    FuckClass obj4(std::move(obj3));   // 调用移动构造函数
    FuckClass obj5 = std::move(obj4);  // 调用移动构造函数

    std::cout << "test fucntion call" << std::endl;

    FuckClass obj6 = test_call(obj5);
    return 0;
}

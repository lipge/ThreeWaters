#pragma once
#include <memory>

template<typename T>
class Singleton {
public:

    static T& GetInstance() {
        static T instance;
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    ~Singleton<T>() = default;
protected:

    Singleton<T>() = default;  // 保护构造函数

    Singleton<T>(const Singleton<T>&) = delete;
    Singleton<T>& operator=(const Singleton<T>&) = delete;

};

#pragma once
#include "const.h"

template<typename T>
class Singleton {
protected:
    static std::shared_ptr<T> _instance;        // ·µ»ØµÄÊµÀý

    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton& operator=(const Singleton<T>&) = delete;

public:
    static std::shared_ptr<T> GetInstance() {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            _instance = std::shared_ptr<T>(new T);
            });
        return _instance;
    }
    ~Singleton() {
        std::cout<< "Singleton destroy" ;
    }
};

template<typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;
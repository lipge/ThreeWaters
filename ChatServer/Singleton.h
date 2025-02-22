#pragma once
#include <memory>

template<typename T>
class Singleton {
public:

    static T& GetInstance() {
        static T instance;
        return instance;
    }

    // ɾ���������캯���͸�ֵ�����
    ~Singleton<T>() = default;
protected:

    Singleton<T>() = default;  // �������캯��

    Singleton<T>(const Singleton<T>&) = delete;
    Singleton<T>& operator=(const Singleton<T>&) = delete;

};

//
// Created by vladislav on 01.02.2021.
//

#ifndef INCLUDE_SHAREDPTR_HPP_
#define INCLUDE_SHAREDPTR_HPP_

#include <atomic>
#include <iostream>
#include <utility>

template <typename T>

class SharedPtr
{

public:

    SharedPtr()
    {
        _Ptr = nullptr;
        _NumberOfPtr = nullptr;
    }

    explicit SharedPtr(T* Ptr)
    {
        _Ptr = Ptr;
        if (Ptr == nullptr)
        {
            _NumberOfPtr = nullptr;
        }
        else
        {
            _NumberOfPtr = new std::atomic_uint;
            *_NumberOfPtr = 1;
        }
    }

    SharedPtr(const SharedPtr& Object)
    {
        _Ptr = Object._Ptr;
        _NumberOfPtr = Object._NumberOfPtr;
        if (_Ptr)
        {
            *_NumberOfPtr = *_NumberOfPtr + 1;
        }
        else
        {
            _NumberOfPtr = nullptr;
        }
    }

    SharedPtr(SharedPtr&& Object)
    {
        _Ptr = Object._Ptr;
        _NumberOfPtr = Object._NumberOfPtr;

        Object._Ptr = nullptr;
        Object._NumberOfPtr = nullptr;
    }

    ~SharedPtr()
    {
        if (_NumberOfPtr)
        {
            if (*_NumberOfPtr == 1)
            {
                delete _Ptr;
                delete _NumberOfPtr;
            }
            else
            {
                *_NumberOfPtr = *_NumberOfPtr - 1;
            }
        }
        _Ptr = nullptr;
        _NumberOfPtr = nullptr;
    }

    auto operator=(const SharedPtr& Object) -> SharedPtr&
    {
        if (this != &Object)
        {
            _Ptr = Object._Ptr;
            _NumberOfPtr = Object._NumberOfPtr;
            if (_Ptr)
            {
                *_NumberOfPtr = *_NumberOfPtr + 1;
            }
            else
            {
                _NumberOfPtr = nullptr;
            }
        }
        return *this;
    }

    auto operator=(SharedPtr&& Object) -> SharedPtr&
    {
        if (this != &Object)
        {
            _Ptr = Object._Ptr;
            _NumberOfPtr = Object._NumberOfPtr;
        }
        return *this;
    }

    operator bool() const
    {
        if (_Ptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    auto operator*() const -> T&
    {
        if (_Ptr)
        {
            return *_Ptr;
        }
        else
        {
            return nullptr;
        }
    }

    auto operator->() const -> T*
    {
        return _Ptr;
    }

    auto get() -> T*
    {
        return _Ptr;
    }

    void reset()
    {
        if (*_NumberOfPtr == 1)
        {
            delete _Ptr;
            delete _NumberOfPtr;
        }
        else
        {
            *_NumberOfPtr = *_NumberOfPtr - 1;
        }

        _Ptr = nullptr;
        _NumberOfPtr = nullptr;
    }

    void reset(T* Ptr)
    {
        if (*_NumberOfPtr == 1)
        {
            delete _Ptr;
            delete _NumberOfPtr;
        }
        else
        {
            *_NumberOfPtr = *_NumberOfPtr - 1;
        }
        _Ptr = Ptr;
        if (Ptr == nullptr)
        {
            _NumberOfPtr = nullptr;
        }
        else
        {
            _NumberOfPtr = new std::atomic_uint;
            *_NumberOfPtr = 1;
        }
    }

    void swap(SharedPtr& Object)
    {
        T* Tmp(std::move(Object._Ptr));
        Object._Ptr = std::move(_Ptr);
        _Ptr = std::move(Tmp);
        std::atomic_uint* TmpNumberOfPtr = Object._NumberOfPtr;
        Object._NumberOfPtr = _NumberOfPtr;
        _NumberOfPtr = TmpNumberOfPtr;
    }

    auto use_count() const -> size_t
    {
        if (_NumberOfPtr)
        {
            return *_NumberOfPtr;
        }
        else
        {
            return 0;
        }
    }

private:

    T* _Ptr;
    std::atomic_uint* _NumberOfPtr;

};

#endif //INCLUDE_SHAREDPTR_HPP_

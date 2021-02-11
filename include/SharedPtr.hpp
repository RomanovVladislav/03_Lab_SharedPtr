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
        ptr = nullptr;
        count_ptr = nullptr;
    }

    explicit SharedPtr(T* point)
    {
        ptr = point;
        if (point == nullptr)
        {
            count_ptr = nullptr;
        }
        else
        {
            count_ptr = new std::atomic_uint;
            *count_ptr = 1;
        }
    }

    SharedPtr(const SharedPtr& r)
    {
        ptr = r.ptr;
        count_ptr = r.count_ptr;
        if (ptr)
        {
            *count_ptr = *count_ptr + 1;
        }
        else
        {
            count_ptr = nullptr;
        }
    }

    SharedPtr(SharedPtr&& r)
    {
        ptr = r.ptr;
        count_ptr = r.count_ptr;

        r.ptr = nullptr;
        r.count_ptr = nullptr;
    }

    ~SharedPtr()
    {
        if (count_ptr)
        {
            if (*count_ptr == 1)
            {
                delete ptr;
                delete count_ptr;
            }
            else
            {
                *count_ptr = *count_ptr - 1;
            }
        }
        ptr = nullptr;
        count_ptr = nullptr;
    }

    auto operator=(const SharedPtr& r) -> SharedPtr&
    {
        if (this != &r)
        {
            ptr = r.ptr;
            count_ptr = r.count_ptr;
            if (ptr)
            {
                *count_ptr = *count_ptr + 1;
            }
            else
            {
                count_ptr = nullptr;
            }
        }
        return *this;
    }

    auto operator=(SharedPtr&& r) -> SharedPtr&
    {
        if (this != &r)
        {
            ptr = r.ptr;
            count_ptr = r.count_ptr;
        }
        return *this;
    }

    operator bool() const
    {
        if (ptr)
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
        if (ptr)
        {
            return *ptr;
        }
        else
        {
            return nullptr;
        }
    }

    auto operator->() const -> T*
    {
        return ptr;
    }

    auto get() -> T*
    {
        return ptr;
    }

    void reset()
    {
        if (*count_ptr == 1)
        {
            delete ptr;
            delete count_ptr;
        }
        else
        {
            *count_ptr = *count_ptr - 1;
        }

        ptr = nullptr;
        count_ptr = nullptr;
    }

    void reset(T* point)
    {
        if (*count_ptr == 1)
        {
            delete ptr;
            delete count_ptr;
        }
        else
        {
            *count_ptr = *count_ptr - 1;
        }
        ptr = point;
        if (point == nullptr)
        {
            count_ptr = nullptr;
        }
        else
        {
            count_ptr = new std::atomic_uint;
            *count_ptr = 1;
        }
    }

    void swap(SharedPtr& r)
    {
        T* tmp_ptr(std::move(r.ptr));
        r.ptr = std::move(ptr);
        ptr = std::move(tmp_ptr);
        std::atomic_uint* tmp_count_ptr = r.count_ptr;
        r.count_ptr = count_ptr;
        count_ptr = tmp_count_ptr;
    }

    auto use_count() const -> size_t
    {
        if (count_ptr)
        {
            return *count_ptr;
        }
        else
        {
            return 0;
        }
    }

private:
    T* ptr;
    std::atomic_uint* count_ptr;
};

#endif //INCLUDE_SHAREDPTR_HPP_

#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_
#include <assert.h>

namespace qh
{
    template<class T>
    class vector {
    public:
        //ctor
        vector()
            : data_(NULL), size_(0), capacity_(1)
        {
            data_ = new T[capacity_];
        }

        explicit vector( size_t n, const T& value = T())
        {
            size_     = n;
            capacity_ = n;
            data_     = new T[capacity_];

            for (size_t i = 0; i < n; ++i)
            {
                data_[i] = value;
            }
        }

        //添加拷贝构造函数,避免浅拷贝
        vector(const vector<T>& rhs)
        {
            size_ = rhs.size_;
            capacity_ = rhs.capacity_;
            
            data_ = new T[capacity_];
            for(size_t i = 0; i < size_; ++i)
            {
                data_[i] = rhs.data_[i];
            }
        }

        vector<T>& operator=(const vector<T>& rhs)
        {
            //自身复制
            if(this == &rhs)
                return *this;
            
            size_ = rhs.size_;
            capacity_ = rhs.capacity_;

            if(data_)
                delete [] data_;
            
            data_ = new T[capacity_];
            for(size_t i = 0; i < size_; ++i)
            {
                data_[i] = rhs.data_[i];
            }

            return *this;
        }

        //dtor
        ~vector()
        {
            if (data_)
            {
                delete [] data_;
            }
        }

        //get
        size_t size() const
        {
            return size_;
        }

        size_t capacity() const
        {
            return capacity_;
        }

        // set & get
        T& operator[](size_t index)
        {
            //防止越界
            assert(index < size_);
            return data_[index];
        }

        // set
        //push_back，当size==capacity时，将capacity变为原来的2倍，并拷贝数据
        void push_back(const T& element)
        {
            if(size_ == capacity_)
            {
                reAlloc(2*capacity_);
            }              
            data_[size_++] = element;
        }

        //pop_back弹出最后一个元素，更改指针(size_)即可
        void pop_back()
        {
            --size_;
        }
        //参考stl的resize实现，resize一定会改变size的大小，且初始化多余的空间
        void resize(size_t n)
        {
            if(n > size_ && n <= capacity_)
            {
                for(size_t i = size_; i < n; ++i)
                {
                    data_[i] = T();
                }
            }
            else if(n > capacity_)
            {
                reAlloc(n);
                for(size_t i = size_; i < n; ++i)
                {
                    data_[i] = T();
                }
            }
            size_ = n;
        }

        //参考stl的reserve实现，只改变capacity，不改变size，且重新分配空间时不初始化多余空间
        void reserve(size_t n)
        {
            if(n > capacity_)
            {
                reAlloc(n);
            }
        }

        void reAlloc(size_t n)
        {
            T *tmp = new T[n];
            for(size_t i = 0; i < size_; ++i)
            {
                tmp[i] = data_[i];
            }
            //注意加[]，元素可能会有非平凡析构函数
            delete [] data_;
            data_     = tmp;
            tmp       = NULL;
            capacity_ = n;
        }

        void clear()
        {
            size_ = 0;
        }
        bool empty()
        {
            return (size_ == 0);
        }

    private:
        T*      data_;
        size_t  size_;
        //使用capacity_避免频繁的内存分配
        size_t  capacity_;
    };
}

#endif
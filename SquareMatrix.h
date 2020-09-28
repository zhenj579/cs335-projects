#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H


template <typename T>
class SquareMatrix {
private:
    size_t sz; // max capacity of matrix
    T **ptr;
public:
    SquareMatrix() : sz(0), ptr(nullptr) { } //default constructor

    //big 5
    /* function: destructor
     * -iterate through every subarray in the 2d array and delete
     * -fix the dangling pointer and set sz and capacity to 0
     */
    ~SquareMatrix()
    {
        for(size_t i = 0; i < sz; i++)
        {
            delete[] ptr[i];
        }
        delete[] ptr;
        ptr = nullptr;
        sz = 0;
    }
    /* function: copy constructor
     * copy the other square matrix's members
     * iterate through both matrices and copy the content of other to this object
     */
    SquareMatrix(const SquareMatrix<T>& other)
    {
        resize(other.sz);
        for(size_t i = 0; i < sz; i++)
        {
            for(size_t j = 0; j < sz; j++)
            {
                ptr[i][j] = other.ptr[i][j];
            }
        }
    }
    /* function: move constructor
     * transfer ownership of the temporary's resources to this object
     */
    SquareMatrix(SquareMatrix<T>&& other): sz(other.sz), ptr(other.ptr)
    {
        other.ptr = nullptr;
        other.sz = 0;
    }
//
//    /* function: copy assignment
//     * use the current allocated memory of this object
//     * and copy the members of rhs
//     */
    SquareMatrix<T>& operator=(const SquareMatrix<T> &rhs)
    {
        if(this != &rhs)
        {
            resize(rhs.sz);
            for(size_t i = 0; i < sz; i++)
            {
                for(size_t j = 0; j < sz; j++)
                {
                    ptr[i][j] = rhs.ptr[i][j];
                }
            }
        }
        return *this;
    }

//    /* function: move assignment
//     * transfer ownership of the resources from rhs to this object
//     */
    SquareMatrix<T>& operator=(SquareMatrix<T> &&rhs)
    {
        sz = rhs.sz;
        ptr = rhs.ptr;
        rhs.ptr = nullptr;
        rhs.sz = 0;
        return *this;
    }

    bool operator==(const SquareMatrix<T> &rhs) const
    {
        if(ptr == rhs.ptr) return true;
        if(sz != rhs.sz) return false;
        for(size_t i = 0; i < sz; i++)
        {
            for(size_t j = 0; j < sz; j++)
            {
                if(ptr[i][j] != rhs.ptr[i][j]) return false;
            }
        }
        return true;
    }

    void resize(size_t new_size)
    {
        for(size_t i = 0; i < sz; i++)
        {
            delete[] ptr[i];
        }
        delete[] ptr;
        sz = new_size;
        ptr = new T*[sz];
        for(size_t i = 0; i < sz; i++)
        {
            ptr[i] = new T[sz];
        }
    }

    T& at(size_t row, size_t column)
    {
        if(row >= sz || column >= sz || row < 0 || column < 0) throw std::out_of_range("row or col does not exist");
        return ptr[row][column];
    }

    size_t size() const
    {
        return sz;
    }

    SquareMatrix<T> operator+(const SquareMatrix<T> &rhs)
    {
        SquareMatrix<T> result;
        result.resize(rhs.sz);
        for(size_t i = 0; i < rhs.sz; i++)
        {
            for(size_t j = 0; j < rhs.sz; j++)
            {
                result.ptr[i][j] = ptr[i][j] + rhs.ptr[i][j];
            }
        }
        return result;
    }

};

#endif

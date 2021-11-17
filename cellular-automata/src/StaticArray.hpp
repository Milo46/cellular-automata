#ifndef STATIC_ARRAY_HPP_INCLUDED
#define STATIC_ARRAY_HPP_INCLUDED

#include <initializer_list>

template<typename _StaticArray>
class StaticArrayIterator
{
public:
    using ValueType     = typename _StaticArray::Type;
    using PointerType   = ValueType*;
    using ReferenceType = ValueType&;

public:
    StaticArrayIterator(PointerType pointer)
        : m_Pointer(pointer) {}

    StaticArrayIterator& operator++() { return (++m_Pointer, *this); }
    StaticArrayIterator& operator--() { return (--m_Pointer, *this); }

    StaticArrayIterator& operator++(int)
    {
        auto iterator{ *this };
        return (++(*this), iterator);
    }

    StaticArrayIterator& operator--(int)
    {
        auto iterator{ *this };
        return (--(*this), iterator);
    }

    PointerType operator->()  { return m_Pointer; }
    ReferenceType operator*() { return *m_Pointer; }

    bool operator==(const StaticArrayIterator& other) const { return m_Pointer == other.m_Pointer; }
    bool operator!=(const StaticArrayIterator& other) const { return m_Pointer != other.m_Pointer; }

private:
    PointerType m_Pointer;
};

template<typename _Ty>
class StaticArray
{
public:
    using Iterator = StaticArrayIterator<StaticArray>;
    using Type     = _Ty;

public:
    StaticArray(size_t size) { _Allocate(size); }
    ~StaticArray()           { _Deallocate(); }

    StaticArray(const std::initializer_list<_Ty>& list);

    StaticArray(const StaticArray& other);
    StaticArray(StaticArray&& other) noexcept;

    StaticArray& operator=(const StaticArray& other);

public:
    _Ty& GetData() noexcept;

    size_t GetSize() const noexcept;
    size_t GetCapacity() const noexcept;
    const _Ty* GetData() const noexcept;

    // TOCHECK(index < elem.GetSize())
    _Ty& operator[](size_t index) const noexcept { return m_Data[index]; }

    // Unfortunately C++ requires begin and end methods to be written in lowercase letters :(
    Iterator begin() const noexcept { return Iterator{ m_Data }; }
    Iterator end() const noexcept   { return Iterator{ m_Data + m_Size }; }

private:
    void _Allocate(size_t size) const noexcept;
    void _Copy(const StaticArray& other) const noexcept;
    void _Deallocate() const noexcept;

private:
    mutable _Ty* m_Data       = nullptr;
    mutable size_t m_Size     = 0u;
    mutable size_t m_Capacity = 0u;
};

template<typename _Ty>
inline StaticArray<_Ty>::StaticArray(const std::initializer_list<_Ty>& list)
{
    _Allocate(list.size());

    size_t i = 0u;
    for (const auto& it : list)
    {
        m_Data[i++] = it;
    }
}

template<typename _Ty>
inline StaticArray<_Ty>::StaticArray(const StaticArray& other)
{
    _Deallocate();
    _Allocate(other.m_Size);

    for (size_t i = 0u; i < other.m_Size; ++i)
    {
        m_Data[i] = other[i];
    }
}

template<typename _Ty>
inline StaticArray<_Ty>::StaticArray(StaticArray&& other) noexcept
{
    _Deallocate();

    m_Size = other.m_Size;
    m_Data = other.m_Data;

    other.m_Size = 0u;
    other.m_Data = nullptr;
}

template<typename _Ty>
inline StaticArray<_Ty>& StaticArray<_Ty>::operator=(const StaticArray& other)
{
    _Deallocate();
    _Allocate(other.m_Size);

    for (size_t i = 0u; i < other.m_Size; ++i)
    {
        m_Data[i] = other[i];
    }

    return *this;
}

template<typename _Ty>
inline size_t StaticArray<_Ty>::GetSize() const noexcept
{
    return m_Size;
}

template<typename _Ty>
inline size_t StaticArray<_Ty>::GetCapacity() const noexcept
{
    return m_Capacity;
}

template<typename _Ty>
inline _Ty& StaticArray<_Ty>::GetData() noexcept
{
    return m_Data;
}

template<typename _Ty>
inline const _Ty* StaticArray<_Ty>::GetData() const noexcept
{
    return m_Data;
}

template<typename _Ty>
inline void StaticArray<_Ty>::_Allocate(size_t size) const noexcept
{
    m_Size = size;
    m_Data = new Type[m_Size];
}

template<typename _Ty>
inline void StaticArray<_Ty>::_Copy(const StaticArray& other) const noexcept
{
    _Deallocate();
    _Allocate(other.GetSize());

    for (size_t i = 0u; i < other.GetSize(); ++i)
    {
        m_Data[i] = other[i];
    }
}

template<typename _Ty>
inline void StaticArray<_Ty>::_Deallocate() const noexcept
{
    delete[] m_Data;
}

#endif

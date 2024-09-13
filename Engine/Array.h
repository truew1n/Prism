#ifndef PE_ARRAY_H
#define PE_ARRAY_H

#include <iostream>
#include <cstdlib>
#include <cstring>

template<typename T>
class CArray
{
private:
    T *Data;
    size_t TypeSize;
    int32_t Size;

public:
    CArray()
    {
        Data = nullptr;
        TypeSize = sizeof(T);
        Size = 0;
    }

    CArray(int32_t InitialSize)
    {
        TypeSize = sizeof(T);
        Size = InitialSize;
        Data = (T *)malloc(Size * TypeSize);
        if (Data == nullptr) {
            std::cerr << "Memory allocation failed!" << std::endl;
            Size = 0;
        }
        else {
            Clear();
        }
    }

    ~CArray()
    {
        if (Data) {
            free(Data);
        }
    }

    bool InBounds(int32_t Index)
    {
        return (Index >= 0 && Index < Size);
    }

    int32_t Num()
    {
        return Size;
    }

    void Clear()
    {
        memset(Data, 0, Size * TypeSize);
    }

    void Resize(int32_t NewSize)
    {
        if (NewSize == Size) return;

        T *NewData = (T *)realloc(Data, NewSize * TypeSize);
        if (NewData == nullptr) {
            std::cerr << "Memory reallocation failed!" << std::endl;
            return;
        }

        Data = NewData;
        Size = NewSize;
    }

    void Add(T Item)
    {
        T *NewData = (T *)realloc(Data, (Size + 1) * TypeSize);
        if (NewData == nullptr) {
            std::cerr << "Memory reallocation failed!" << std::endl;
            return;
        }
        Data = NewData;
        Data[Size] = Item;
        Size++;
    }

    T Get(int32_t Index)
    {
        if (Index < 0 || Index >= Size) return T();
        return Data[Index];
    }

    void Set(T Item, int32_t Index)
    {
        if (Index < 0 || Index >= Size) return;
        Data[Index] = Item;
    }

    void Remove(int32_t Index)
    {
        if (Size == 0) return;
        if (Size == 1) {
            free(Data);
            Data = nullptr;
            Size = 0;
            return;
        }

        T *NewData = (T *)malloc((Size - 1) * TypeSize);
        if (NewData == nullptr) {
            std::cerr << "Memory allocation failed!" << std::endl;
            return;
        }

        // Use memcpy to copy data before and after the removed index
        memcpy(NewData, Data, Index * TypeSize);
        memcpy(NewData + Index, Data + Index + 1, (Size - Index - 1) * TypeSize);

        free(Data); // Free the old memory
        Data = NewData;
        Size--;
    }

    CArray<T> *GetRegion(int32_t Index, int32_t Length)
    {
        if (Length <= 0 || (Index < 0 || Index >= this->Num())) return new CArray<T>();
        CArray<T> *NewArray = new CArray<T>(Length);
        memcpy(NewArray->begin(), Data + Index, Length * TypeSize);
        return NewArray;
    }

    /*  Converts P-type array to T-type templated Array */
    static CArray<T> *From(T *Source, int32_t Length)
    {
        if (Length <= 0 || !Source) return new CArray<T>();
        CArray<T> *NewArray = new CArray<T>(Length);
        memcpy(NewArray->begin(), Source, Length * sizeof(T));
        return NewArray;
    }

    /*  Converts P-type variable to T-type templated Array */
    template<typename P>
    static CArray<T> *From(P Value)
    {
        int32_t Length = sizeof(P);
        if (Length <= 0) return new CArray<T>();
        CArray<T> *NewArray = new CArray<T>(Length);
        memcpy(NewArray->begin(), &Value, Length);
        return NewArray;
    }

    /*  Joins T-type templated Arrays */
    static CArray<T> *Join(CArray<T> *First, CArray<T> *Second)
    {
        if (!(First && Second)) return new CArray<T>();
        CArray<T> *NewArray = new CArray<T>(First->Num() + Second->Num());

        // Use memcpy to copy elements from First and Second arrays
        memcpy(NewArray->begin(), First->begin(), First->Num() * sizeof(T));
        memcpy(NewArray->begin() + First->Num(), Second->begin(), Second->Num() * sizeof(T));

        return NewArray;
    }

    /*  Compares T-type templated Arrays
        Note: Comparing 2 nullptr's will return true! */
    static bool Compare(CArray<T> *First, CArray<T> *Second)
    {
        if (First == Second) return true;
        if ((!(First && Second)) || (First->Num() != Second->Num())) return false;
        return (memcmp(First->begin(), Second->begin(), First->Num() * sizeof(T)) == 0);
    }

    T *begin()
    {
        return Data;
    }

    T *end()
    {
        return Data + Size;
    }
};

#endif

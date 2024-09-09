#ifndef PE_ARRAY_H
#define PE_ARRAY_H

#include <iostream>

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
        Data = new T[InitialSize];
        TypeSize = sizeof(T);
        Size = InitialSize;
        Clear();
    }

    ~CArray()
    {
        delete Data;
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
        for (int32_t i = 0; i < Size; ++i) {
            Data[i] = T();
        }
    }

    void Add(T Item)
    {
        T *NewData = new T[++Size];

        memcpy(NewData, Data, (Size - 1) * TypeSize);

        NewData[Size - 1] = Item;
        if (Data) delete Data;
        Data = NewData;
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
        if (!Size) return;
        if (Size == 1) {
            delete Data;
            Data = nullptr;
            Size = 0;
            return;
        }

        T *NewData = new T[--Size];

        memcpy(NewData, Data, (Index - 1) * TypeSize);
        memcpy(NewData + Index, Data + Index + 1, (Size - Index) * TypeSize);

        if (Data) delete Data;
        Data = NewData;
    }

    CArray<T> *GetRegion(int32_t Index, int32_t Length)
    {
        if (Length <= 0 || (Index < 0 || Index >= this->Num())) return new CArray<T>();
        CArray<T> *NewArray = new CArray<T>(Length);
        for (int32_t i = 0; i < Length; ++i) {
            NewArray->Set(Data[Index + i], i);
        }
        return NewArray;
    }

    /*  Convertes P-type array to T-type templated Array
    */
    static CArray<T> *From(T *Source, int32_t Length)
    {
        if (Length <= 0 || !Source) return new CArray<T>();
        CArray<T> *NewArray = new CArray<T>(Length);
        for (int32_t i = 0; i < Length; ++i) {
            NewArray->Set(Source[i], i);
        }
        return NewArray;
    }

    /*  Converts P-type variable to T-type templated Array
    */
    template<typename P>
    static CArray<T> *From(P Value)
    {
        int32_t Length = sizeof(P);
        if (Length <= 0) return new CArray<T>();
        CArray<T> *NewArray = new CArray<T>(Length);
        for (int32_t i = 0; i < Length; ++i) {
            NewArray->Set(((T *)(&Value))[i], i);
        }
        return NewArray;
    }

    /*  Joins T-type templated Arrays
    */
    static CArray<T> *Join(CArray<T> *First, CArray<T> *Second)
    {
        if (!(First && Second)) return new CArray<T>();
        CArray<T> *NewArray = new CArray<T>(First->Num() + Second->Num());
        for (int32_t i = 0; i < First->Num(); ++i) {
            NewArray->Set(First->Get(i), i);
        }
        for (int32_t i = 0; i < Second->Num(); ++i) {
            NewArray->Set(Second->Get(i), i + First->Num());
        }
        return NewArray;
    }
    /*  Compares T-type templated Arrays
        Note: Comparing 2 nullptr's will return true!
    */
    static bool Compare(CArray<T> *First, CArray<T> *Second)
    {
        if (First == Second) return true;
        if ((!(First && Second)) || (First->Num() != Second->Num())) return false;
        for (int32_t i = 0; i < First->Num(); ++i) {
            if (First->Get(i) != Second->Get(i)) return false;
        }
        return true;
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
#ifndef PE_PAIR_H
#define PE_PAIR_H

template<typename T, typename S>
class CPair {
private:
    T MFirst;
    S MSecond;
public:
    CPair() : MFirst(), MSecond() {}
    CPair(T IFirst, S ISecond) : MFirst(IFirst), MSecond(ISecond) {}

    static CPair<T, S> Make(T First, S Second)
    {
        return CPair(First, Second);
    }

    T GetFirst() const { return MFirst; }
    S GetSecond() const { return MSecond; }
};

#endif
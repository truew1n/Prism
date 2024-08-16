#ifndef PE_PAIR_HPP
#define PE_PAIR_HPP

template<typename T, typename S>
class CPair {
private:
    T First;
    S Second;
public:
    CPair() : First(), Second() {}
    CPair(T First, S Second) : First(First), Second(Second) {}

    static CPair<T, S> Make(T First, S Second)
    {
        return CPair(First, Second);
    }

    T GetFirst() const { return First; }
    S GetSecond() const { return Second; }
};

#endif
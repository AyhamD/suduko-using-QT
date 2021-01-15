#include"interface.h"

suduko::suduko(int K) :K(K)
{
}

suduko::suduko(const suduko &rhs)
{
    K = rhs.K;
    std::copy(rhs.grid.begin(),rhs.grid.end(),grid.begin());
}

suduko &suduko::operator =(const suduko &rhs)
{
    suduko tmp(rhs);
    std::swap(K,tmp.K);
    return *this;
}

suduko::~suduko()
{
}

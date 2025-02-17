#ifndef RealComparisionUtility_HPP
#define RealComparisionUtility_HPP
#include<functional>

template<typename Real>
class RealComparisionUtility
{
    public:
    static bool isLower(Real a, Real b, Real tolerance = std::numeric_limits<Real>::epsilon())
    {
        return std::less<Real>{}(a,b);
    }

    static bool isHigher(Real a, Real b, Real tolerance = std::numeric_limits<Real>::epsilon())
    {
        return std::greater<Real>{}(a,b);
    }

    static bool isEqual(Real a, Real b)
    {
        return !std::less<Real>{}(a, b) && !std::less<Real>{}(b, a);
    }

};

#endif

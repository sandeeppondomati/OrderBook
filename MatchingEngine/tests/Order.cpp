#include "Order.hpp"
namespace MatchingEngine
{
    string Order::toString() const
    {
        string res = queryTime;
        res+=";";
        res+=id;
        res+=";";
        res+=symbol;
        res+=";";
        res+=type==Type::Market?"MKT":to_string(price);
        res+=";";
        res+=side==Side::Buy?"Buy":"Sell";
        res+=";";
        res+=to_string(quantity);

        return res;
    }

}

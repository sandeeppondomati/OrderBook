#ifndef Order_HPP
#define Order_HPP
#include<string>
namespace MatchingEngine
{
    using namespace std;


    enum class Side { None=0, Buy=1, Sell=2 };
    enum class Type { None=0, Market=1, Limit=2 };
    enum class Status { None=0, Rejected=1, Accepted=2, Replaced=3, Cancelled=4, Filled=5, PartiallyFilled=6 };

    class Order
    {
        private:
        string id;
        string symbol;
        double price;
        Side side;
        int quantity;
        Type type;
        Status status;
        pair<time_t, long> receivedTime;
	string queryTime;
         
        public:
        Order(const string &id, const string &symbol, double price, int side, int quantity, int type, pair<time_t,long> receivedTime, const string &queryTime):id(id), symbol(symbol), price(price), side(static_cast<Side>(side)), quantity(quantity), type(static_cast<Type>(type)), status(Status::None), receivedTime(receivedTime),queryTime(queryTime)
        {}
        Order(string &&id, string &&symbol, double &&price, int &&side, int &&quantity, int &&type, pair<time_t,long> &&receivedTime, string&& queryTime)
        {
            exchange(this->id, id);
            exchange(this->symbol, symbol);
            exchange(this->price, price);
            exchange(this->side, static_cast<Side>(side));
            exchange(this->quantity, quantity);
            exchange(this->type, static_cast<Type>(type));
            status = Status::None;
            exchange(this->receivedTime, receivedTime);
            exchange(this->queryTime, queryTime);
            
        }

        Order& operator=(const Order& copy)
	{
	    if(this != &copy)
	    {
                id=copy.id;
                symbol= copy.symbol;
                price= copy.price;
                side= copy.side;
                quantity= copy.quantity;
                type= copy.type;
                status= copy.status;
                receivedTime= copy.receivedTime;
	    }
     
            return *this;
            
	}
     
        string toString() const;

        inline Order clone()
        {
            return Order(*this);
        }  

        inline const string& getId() const
        {
            return id;
        }
        inline const string& getSymbol() const
        {
            return symbol;
        }
        inline double getPrice() const
        {
            return price;
        }
        inline const Side& getSide() const
        {
            return side;
        }
        inline int getQuantity() const
        {
            return quantity;
        }
        inline const Type& getType() const
        {
            return type;
        }
        inline const Status& getStatus() const
        {
            return status;
        }

        inline const pair<time_t, long>& getReceivedTime() const
        {
            return receivedTime;
	}
	inline void setQuantity(int qty)
	{
	    quantity = qty;
	}

        inline void setId(string &&id)
        {
            exchange(this->id, id);
        }
        inline void setSymbol(string &&symbol)
        {
            exchange(this->symbol, symbol);
        }
        inline void setPrice(double &&price)
        {
            exchange(this->price, price);
        }
        inline void setPrice(double &price)
        {
            (this->price = price);
        }
        inline void setSide(Side &&side)
        {
            exchange(this->side, static_cast<Side>(side));
        }
        inline void setType(Type &&type)
        {
            exchange(this->type, static_cast<Type>(type));
        }
        inline void setStatus(Status &&status)
        {
            exchange(this->status, static_cast<Status>(status));
        }
    };
}
#endif

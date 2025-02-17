#include "StringRequestCreatorImpl.hpp"
#include"Order.hpp"
#include"Request.hpp"
#include<time.h>
#include<regex>
#include<string>
#include <ctime>
namespace MatchingEngine
{
    StringRequestCreatorImpl::StringRequestCreatorImpl()
    {
    }
    StringRequestCreatorImpl::~StringRequestCreatorImpl() 
    {
    }

    shared_ptr<Request> StringRequestCreatorImpl::create(const string &str)
    {
        	
        // example - 09:00:00.690000	TEST8	2837175	I	BUY	9	9.60
        regex oRegex("\\;");
	vector<string> orderDetails(
					sregex_token_iterator(str.begin(), str.end(), oRegex, -1),
					sregex_token_iterator()
					);

        if(orderDetails.size() == 7)
        {
            regex pRegex("\\.");
	    vector<string> timeDetails(
					sregex_token_iterator(orderDetails[0].begin(), orderDetails[0].end(), pRegex, -1),
					sregex_token_iterator()
					);
            time_t curr_time;
	    curr_time = time(0);
            struct tm *tm = localtime(&curr_time);
            strptime(timeDetails[0].c_str(), "%H:%M:%S", tm);
            tm->tm_isdst = -1;
            int microSeconds = 0;
	    try {
	        if(timeDetails[1].size())
	            stol(timeDetails[1]);
            }
            catch(exception &e)
	    {
	    }
            
            pair<time_t,long> receivedTime = make_pair(mktime(tm), microSeconds);

            bool isMarket = (!orderDetails[6].empty())?0:1;
            bool isBuy = !strcasecmp(orderDetails[4].c_str(),"Buy");
            int requestType = (orderDetails[3] == "I" || orderDetails[3] == "i")?1:
			      (orderDetails[3] == "A" || orderDetails[3] == "a")?2:
			      (orderDetails[3] == "C" || orderDetails[3] == "c")?3:0;
             
            return make_shared<Request>(string(orderDetails[1]), 
		make_shared<Order>((orderDetails[2]), (orderDetails[1]), isMarket?numeric_limits<double>::min():stod(orderDetails[6]), 
					isBuy?1:2, stoi(orderDetails[5]), static_cast<int>(isMarket?Type::Market:Type::Limit), receivedTime, orderDetails[0])
		,static_cast<RequestType>(requestType), isBuy?Side::Buy:Side::Sell); 
        }
        else if(orderDetails.size() == 3)
        {
	    cout<<str<<endl;
            if(!strcasecmp("OrderCounts", orderDetails[0].c_str()))
                return make_shared<Request>((orderDetails[1]), nullptr, RequestType::OrderCount, Side::None);
        }
        else if(orderDetails.size() == 4)
	{
	    cout<<str<<endl;
            shared_ptr<Request> request = nullptr;
            if(!strcasecmp("BestSellAtTime", orderDetails[0].c_str()))
            {
                request =  make_shared<Request>((orderDetails[1]), nullptr, RequestType::BestOrders, Side::Sell);
   		updateTime(request, orderDetails);
            }
            else if(!strcasecmp("BestBuyAtTime", orderDetails[0].c_str()))
            {
                request =  make_shared<Request>((orderDetails[1]), nullptr, RequestType::BestOrders, Side::Buy);
   		updateTime(request, orderDetails);
            }
	    else if(!strcasecmp("BiggestBuyOrders", orderDetails[0].c_str()))
            {
                request = make_shared<Request>((orderDetails[1]), nullptr, RequestType::BigOrders, Side::Buy);
		request->setCount(stoi(orderDetails[2]));
            }
	    else if(!strcasecmp("BiggestSellOrders", orderDetails[0].c_str()))
            {
                request =  make_shared<Request>((orderDetails[1]), nullptr, RequestType::BigOrders, Side::Sell);
		request->setCount(stoi(orderDetails[2]));
            }

            return request; 
	}

        return nullptr;
    }

    void StringRequestCreatorImpl::updateTime(shared_ptr<Request> requestPtr, const vector<string> &orderDetails)
    {
        regex pRegex("\\.");
        vector<string> timeDetails(
                                        sregex_token_iterator(orderDetails[2].begin(), orderDetails[2].end(), pRegex, -1),
                                        sregex_token_iterator()
                                        );
        time_t curr_time;
	curr_time = time(0);
        struct tm *tm = localtime(&curr_time);
        strptime(timeDetails[0].c_str(), "%H:%M:%S", tm);
        tm->tm_isdst = -1;
        int microSeconds = 0;
	try {
	    if(timeDetails[1].size())
	    stol(timeDetails[1]);
        }
        catch(exception &e)
	{
	}
            
        pair<time_t,long> receivedTime = make_pair(mktime(tm), microSeconds);
        requestPtr->setPairTime((receivedTime));
        requestPtr->setQueryTime(string(orderDetails[2]));
    }
}

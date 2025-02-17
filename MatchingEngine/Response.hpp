#ifndef Response_HPP
#define Response_HPP
#include<memory>
#include<map>
#include<utility>
#include<iostream>
#include"Order.hpp"
#include"BookTracker.hpp"
namespace MatchingEngine
{
    using namespace std;
    class Response
    {
        private:
	string msg;

        public:
        Response(string & str):msg(str)
	{
	}
	const string& toString() const
	{
	    return msg;
	}
    };
}
#endif

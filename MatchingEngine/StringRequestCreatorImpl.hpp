#ifndef StringRequestCreatorImpl_HPP
#define StringRequestCreatorImpl_HPP
#include "RequestCreatorImpl.hpp"
#include<memory>
namespace MatchingEngine
{
    using namespace std;
    class Request;
    class StringRequestCreatorImpl : public RequestCreatorImpl
    {
        public:

        StringRequestCreatorImpl();
        virtual ~StringRequestCreatorImpl();

        shared_ptr<Request> create(const string &str);

        // no need to copy 
        StringRequestCreatorImpl(const StringRequestCreatorImpl &other) = delete;
        StringRequestCreatorImpl(StringRequestCreatorImpl &&other) = delete;
        StringRequestCreatorImpl& operator = (const StringRequestCreatorImpl &other) = delete;
        StringRequestCreatorImpl& operator = (StringRequestCreatorImpl &&other) = delete;

        private:
	void updateTime(shared_ptr<Request> requestPtr, const vector<string> &orderDetails);
    };
}
#endif

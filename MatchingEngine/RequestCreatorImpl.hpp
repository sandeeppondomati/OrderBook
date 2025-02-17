#ifndef RequestCreatorImpl_HPP
#define RequestCreatorImpl_HPP
#include<memory>
namespace MatchingEngine
{
    using namespace std;
    class Request;
    class RequestCreatorImpl
    {
        public:

        RequestCreatorImpl();
        virtual ~RequestCreatorImpl();

        virtual shared_ptr<Request> create(const string &str) = 0;

        // no need to copy 
        RequestCreatorImpl(const RequestCreatorImpl &other) = delete;
        RequestCreatorImpl(RequestCreatorImpl &&other) = delete;
        RequestCreatorImpl& operator = (const RequestCreatorImpl &other) = delete;
        RequestCreatorImpl& operator = (RequestCreatorImpl &&other) = delete;

    };
}
#endif

#ifndef RequestCreator_HPP
#define RequestCreator_HPP
#include<memory>
#include<string>
#include "RequestCreatorImpl.hpp"
namespace MatchingEngine
{
    using namespace std;
    class Request;
    class RequestCreator
    {
        public:
        RequestCreator(unique_ptr<RequestCreatorImpl> implPtr);
        ~RequestCreator();

        template<typename T>
        shared_ptr<Request> create(const T &str)
        {
            return implPtr->create(str);
        }

        // no need to copy 
        RequestCreator(const RequestCreator &other) = delete;
        RequestCreator(RequestCreator &&other) = delete;
        RequestCreator& operator = (const RequestCreator &other) = delete;
        RequestCreator& operator = (RequestCreator &&other) = delete;
       
        private:
        unique_ptr<RequestCreatorImpl> implPtr;

    };
}
#endif

#ifndef PublisherImpl_HPP
#define PublisherImpl_HPP
#include<memory>
namespace MatchingEngine
{
    using namespace std;
    class Response;
    class PublisherImpl
    {
        public:

        PublisherImpl();
        virtual ~PublisherImpl();

        virtual bool publish(const shared_ptr<Response> &message) = 0;

        // no need to copy 
        PublisherImpl(const PublisherImpl &other) = delete;
        PublisherImpl(PublisherImpl &&other) = delete;
        PublisherImpl& operator = (const PublisherImpl &other) = delete;
        PublisherImpl& operator = (PublisherImpl &&other) = delete;

    };
}
#endif

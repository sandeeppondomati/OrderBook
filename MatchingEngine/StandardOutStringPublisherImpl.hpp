#ifndef StandardOutStringPublisherImpl_HPP
#define StandardOutStringPublisherImpl_HPP
#include<memory>
#include "PublisherImpl.hpp"
namespace MatchingEngine
{
    using namespace std;
    class Response;
    class StandardOutStringPublisherImpl : public PublisherImpl
    {
        public:

        StandardOutStringPublisherImpl();
        virtual ~StandardOutStringPublisherImpl();

        bool publish(const shared_ptr<Response> &message);

        // no need to copy 
        StandardOutStringPublisherImpl(const StandardOutStringPublisherImpl &other) = delete;
        StandardOutStringPublisherImpl(StandardOutStringPublisherImpl &&other) = delete;
        StandardOutStringPublisherImpl& operator = (const StandardOutStringPublisherImpl &other) = delete;
        StandardOutStringPublisherImpl& operator = (StandardOutStringPublisherImpl &&other) = delete;

    };
}
#endif

#include <detail/Queue.inc>
#include <gtest/gtest.h>
#include <StubListener.hpp>


namespace aggup::detail::testing {

    class QueueTest : public ::testing::Test {
    public:
        void SetUp() override {
            stubListenerOneInteger.listened = 1;
            stubListenerTwoInteger.listened = 2;
        }

        StubListener<int> stubListenerOneInteger;
        StubListener<int> stubListenerTwoInteger;
    };

    TEST_F(QueueTest, testIterationQueueIsFilled) {
        Queue<int> queue(&stubListenerOneInteger, &stubListenerTwoInteger);
        queue.pull();
        auto iterator = queue.createIterator();
        
        int counter = 0;
        while ( iterator->hasNext() ) {
            EXPECT_EQ(++counter, iterator->current());
            iterator->next();
        }
        
        EXPECT_EQ(1, iterator->current() ); 
        iterator->next();
        EXPECT_EQ(2, iterator->current() ); 
    }

    TEST_F(QueueTest, testIterationQueueIsEmpty) {
        Queue<int> queue(&stubListenerOneInteger, &stubListenerTwoInteger);
        auto iterator = queue.createIterator();

        iterator->next();
        EXPECT_THROW(iterator->current(), std::out_of_range);
    }
}

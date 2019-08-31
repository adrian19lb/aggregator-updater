#include <detail/ContainExecutorIterator.inc>
#include <gtest/gtest.h>
#include <detail/StubAggregator.hpp>
#include <detail/FakeIterator.hpp>
#include <detail/CapacityReceiver.inc>

namespace aggup::detail::testing {
    
    TEST(ContainExecutorIteratorTest, testExecute) {
        FakeIterator< std::vector<int> > fakeCounterIterator(3); //return 0, 1, 2
        CapacityReceiver receiver;
        ContainExecutorIterator< std::vector, Aggregator, int > executor(&fakeCounterIterator, &receiver);

        aggup::testing::StubAggregator<int> stubAggregator(2);
        stubAggregator.isContain = true;
        executor.execute(stubAggregator);
        EXPECT_EQ(ContainerCapacity::Full, receiver.capacity);
        
        stubAggregator.isContain = false;
        executor.execute(stubAggregator);
        EXPECT_EQ(ContainerCapacity::Empty, receiver.capacity);
    }

}

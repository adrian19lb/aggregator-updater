#include <AggregatorActivatorImp.hpp>
#include <StubListener.hpp>
#include <gtest/gtest.h>
#include <detail/StubAggregator.hpp>

using aggup::testing::StubAggregator;

namespace aggup::testing {

    
    TEST(AggregatorActivatorImpTest, testIfUpdate) {
        StubListener<int> stubListener;
        AggregatorActivatorImp<std::string, int> activator(&stubListener);
        auto aggregator = std::make_unique< StubAggregator<int> >(1);
        auto aggregatorRawPtr = aggregator.get();
        
        activator.add("test", std::move(aggregator));
        activator.update();

        aggregatorRawPtr->isContain = true; 
        EXPECT_TRUE(activator["test"]);

        aggregatorRawPtr->isContain = false; 
        EXPECT_FALSE(activator["test"]);

        EXPECT_FALSE(activator["testAnother"]);
    }

}

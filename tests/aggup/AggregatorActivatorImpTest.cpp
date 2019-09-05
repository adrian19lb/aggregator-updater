#include <AggregatorActivatorImp.hpp>
#include <StubListener.hpp>
#include <gtest/gtest.h>
#include <detail/StubAggregator.hpp>

using aggup::testing::StubAggregator;

namespace aggup::testing {

    
    TEST(AggregatorActivatorImpTest, testIfUpdate) {
        auto stubListener = std::make_unique< StubListener<int> >();
        AggregatorActivatorImp<std::string, int> activator(std::move(stubListener));
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

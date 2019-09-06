#include <AggregatorActivatorImp.hpp>
#include <StubListener.hpp>
#include <gtest/gtest.h>
#include <detail/StubAggregator.hpp>

using aggup::testing::StubAggregator;

namespace aggup::testing {

    
    TEST(AggregatorActivatorImpTest, testIfUpdate) {
        auto stubListener = std::make_unique< StubListener<int> >();
        AggregatorActivatorImp<std::string, int> activator(std::move(stubListener));
        StubAggregator<int> aggregator(1);
        
        activator.add("test", &aggregator);
        activator.update();

        aggregator.isContain = true; 
        EXPECT_TRUE(activator["test"]);

        aggregator.isContain = false; 
        EXPECT_FALSE(activator["test"]);

        EXPECT_FALSE(activator["testAnother"]);
    }

}

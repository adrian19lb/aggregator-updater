#include <UnorderedAggregator.hpp>
#include <gtest/gtest.h>

namespace aggup::testing {
    
    TEST(UnorderedAggregatorTest, testEqual) {
        UnorderedAggregator<int> aggregator{1,2};
        UnorderedAggregator<int> aggregatorToCompare{1,2};

        EXPECT_EQ(aggregator, aggregatorToCompare);
    }
    
    TEST(UnorderedAggregatorTest, testNotEqual) {
        UnorderedAggregator<int> aggregator{1,2};
        UnorderedAggregator<int> complexAggregator{2,3};
        UnorderedAggregator<int> simpleAggregator{1};

        EXPECT_NE(aggregator, complexAggregator);
        EXPECT_NE(aggregator, simpleAggregator);
    }

    TEST(UnorderedAggregatorTest, testAddition) {
        UnorderedAggregator<int> aggregator{1};
        UnorderedAggregator<int> additiveAggregator{1,2};

        UnorderedAggregator<int> sumUpAggregators = std::move(aggregator + additiveAggregator);

        EXPECT_TRUE(sumUpAggregators.contain(aggregator));
        EXPECT_TRUE(sumUpAggregators.contain(additiveAggregator));
        EXPECT_TRUE(sumUpAggregators.contain(2));
        EXPECT_EQ(2, sumUpAggregators.size());
    }

}

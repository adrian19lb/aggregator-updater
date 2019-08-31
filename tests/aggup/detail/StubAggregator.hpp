#ifndef STUBAGGREGATOR_H
#define STUBAGGREGATOR_H

#include <Aggregator.hpp>

namespace aggup::testing {
    
    template<typename T>
    class StubAggregator : public Aggregator<T> {
    public:
        bool isContain;
        StubAggregator(size_t length)
        : length(length) {
        
        }

        size_t size() const override {
            return length;
        }

        bool contain(T const& item) const override {
            return isContain;
        }

        bool contain(Aggregator<T> const& aggregator) const {
            return isContain;
        }

    private:
        size_t length;
    };

}

#endif /* STUBAGGREGATOR_H */

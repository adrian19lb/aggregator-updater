#ifndef AGGREGATORACTIVATOR_H
#define AGGREGATORACTIVATOR_H

#include <Aggregator.hpp>
#include <memory>

namespace aggup {
    
    template<typename T>
    using AggregatorUPtr = std::unique_ptr< Aggregator<T> >;

    template<typename Identifier, typename T>
    class AggregatorActivator {
    public:
        virtual ~AggregatorActivator() = default;
        virtual bool operator[](Identifier id) = 0;
        virtual void add(Identifier id, Aggregator<T>* aggregator) = 0;
        virtual void update() = 0;
    };

}

#endif /* AGGREGATORACTIVATOR_H */

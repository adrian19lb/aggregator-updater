#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include <cstddef>

namespace aggup {
    
    template<typename T>
    class Aggregator {
    public:
        virtual ~Aggregator() = default;
        virtual bool contain(T const& item) const = 0;
        virtual bool contain(Aggregator<T> const& aggupgregator) const = 0;
        virtual size_t size() const = 0;
    };

}

#endif /* AGGREGATOR_H */

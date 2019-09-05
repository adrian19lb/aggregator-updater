#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <Listener.hpp>
#include <detail/ForwardIterator.inc>
#include <set>
#include <memory>

namespace aggup::detail {
    
    template<typename Container>
    using IteratorUPtr = std::unique_ptr< Iterator<Container> >;
    
    template<typename T>
    class Queue {
    public:
        using iterator = typename std::set<T>::iterator;
        using const_iterator = typename std::set<T>::const_iterator;
        using value_type = typename std::set<T>::value_type;
    public:
        template<typename... Arg> Queue(Arg... args) {
            ( listeners.emplace(std::move(args)),... );
        }

    IteratorUPtr<Queue> createIterator() {
        return std::make_unique< ForwardIterator<Queue> >(items.begin(), items.end() );
    }

    void pull() {
        items.clear();
        pullFromListeners();
    }

    private:
        void pullFromListeners() {
            for (auto&& listener: listeners) {
                auto item = listener->listen();
                items.emplace(item);
            }
        }
    private:
        std::set< std::unique_ptr<Listener<T>> > listeners;
        std::set<T> items;
    };
}

#endif /* ifndef QUEUE_HPP */

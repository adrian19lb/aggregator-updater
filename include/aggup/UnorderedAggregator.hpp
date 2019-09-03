#ifndef AGGREGATORIMP_HPP
#define AGGREGATORIMP_HPP 

#include <Aggregator.hpp>
#include <unordered_set>

namespace aggup {
    
    template<typename T, typename Hasher = std::hash<T>, typename Comperator = std::equal_to<T> > 
    class UnorderedAggregator : public Aggregator<T> {
    private:
        template<typename E> 
        using unorder_set = std::unordered_set<T, Hasher, Comperator>; 
    public:
        using value_type = T;
    private:
        explicit UnorderedAggregator(unorder_set<T> const& items);
        void makeMove(unorder_set<T> const& items);
    public:
        UnorderedAggregator(std::initializer_list<T> items);
        UnorderedAggregator() = default;
        UnorderedAggregator(UnorderedAggregator&& source);
        ~UnorderedAggregator() = default;
        UnorderedAggregator(UnorderedAggregator<T, Hasher, Comperator> const& items) = delete;
        UnorderedAggregator& operator=(UnorderedAggregator const& items) = delete;
        UnorderedAggregator& operator=(UnorderedAggregator&& source);
        template<typename E, typename R, typename U>
        friend bool operator==(UnorderedAggregator<E, R, U> const& lhs, UnorderedAggregator<E, R, U> const& rhs);
        template<typename E, typename R, typename U>
        friend bool operator!=(UnorderedAggregator<E, R, U> const& lhs, UnorderedAggregator<E, R, U> const& rhs);
        UnorderedAggregator<T, Hasher, Comperator> operator+(UnorderedAggregator<T, Hasher, Comperator> const& additive) const;
    public:
        size_t size() const override;
        bool contain(T const& item) const override;
        bool contain(Aggregator<T> const& aggregator) const override;
        void add(T item) override;
    private:
        bool areAllItemsIncludedFrom(UnorderedAggregator const& source) const;
    private:
        unorder_set<T> items;
        Comperator comperator;
    };
}

#include <detail/UnorderedAggregator.inc>

#endif /* ifndef EVENTSAGGREGATORIMP_HPP */

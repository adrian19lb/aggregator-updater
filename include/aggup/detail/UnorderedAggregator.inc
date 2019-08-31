#include <algorithm>

namespace aggup {
    
    template<typename T, typename Hasher, typename Comperator> 
    UnorderedAggregator<T, Hasher, Comperator>::UnorderedAggregator(unorder_set<T> const& items) {
        makeMove(items);
    }

    template<typename T, typename Hasher, typename Comperator> 
    void UnorderedAggregator<T, Hasher, Comperator>::makeMove(unorder_set<T> const& items) {
        this->items.insert( std::make_move_iterator( items.begin() ), 
                            std::make_move_iterator( items.end() ));
    }

    template<typename T, typename Hasher, typename Comperator> 
    UnorderedAggregator<T, Hasher, Comperator>::UnorderedAggregator(std::initializer_list<T> items)
    : items( items.begin(), items.end() ) {
    }

    template<typename T, typename Hasher, typename Comperator> 
    UnorderedAggregator<T, Hasher, Comperator>::UnorderedAggregator(UnorderedAggregator&& source) {
        makeMove(source.items); 
    }

    template<typename T, typename Hasher, typename Comperator>
    UnorderedAggregator<T, Hasher, Comperator>& UnorderedAggregator<T, Hasher, Comperator>::operator=(UnorderedAggregator<T, Hasher, Comperator>&& source) {
        makeMove(source.items);
        return *this;
    }

    template<typename T, typename Hasher, typename Comperator>
    bool operator==(UnorderedAggregator<T, Hasher, Comperator> const& lhs, UnorderedAggregator<T, Hasher, Comperator> const& rhs) {
        return lhs.items.size() == rhs.items.size() && lhs.areAllItemsIncludedFrom(rhs);
    }

    template<typename T, typename Hasher, typename Comperator>
    bool operator!=(UnorderedAggregator<T, Hasher, Comperator> const& lhs, UnorderedAggregator<T, Hasher, Comperator> const& rhs) {
        return !(lhs.items.size() == rhs.items.size() && lhs.areAllItemsIncludedFrom(rhs));    
    }
    
    template<typename T, typename Hasher, typename Comperator>    
    UnorderedAggregator<T, Hasher, Comperator> UnorderedAggregator<T, Hasher, Comperator>::operator+(UnorderedAggregator<T, Hasher, Comperator> const& additive) const {
        unorder_set<T> newItems;
        newItems.insert( items.begin(), items.end() ); 
        newItems.insert( additive.items.begin(), additive.items.end() );

        return std::move( UnorderedAggregator<T>(newItems) );
    }
    
    template<typename T, typename Hasher, typename Comperator>    
    size_t UnorderedAggregator<T, Hasher, Comperator>::size() const {
        return items.size();
    }

    template<typename T, typename Hasher, typename Comperator>    
    bool UnorderedAggregator<T, Hasher, Comperator>::contain(T const& item) const {
        auto found = std::find_if(items.begin(), items.end(), [this, &item](auto itr) {
            return comperator(itr, item);        
        });
            
        return found != items.end();
    }

    template<typename T, typename Hasher, typename Comperator>    
    bool UnorderedAggregator<T, Hasher, Comperator>::contain(Aggregator<T> const& aggregator) const {
        const UnorderedAggregator& source = dynamic_cast<UnorderedAggregator const&>(aggregator);
        return source.size() <= size() && areAllItemsIncludedFrom(source);
    }

    template<typename T, typename Hasher, typename Comperator>    
    bool UnorderedAggregator<T, Hasher, Comperator>::areAllItemsIncludedFrom(UnorderedAggregator const& source) const {
        const auto isIncluded = [this](const auto& itr) { return items.find(itr) != items.end(); };
            
        return std::all_of(source.items.begin(), source.items.end(), isIncluded);
    }

}

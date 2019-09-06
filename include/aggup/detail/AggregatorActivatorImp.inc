namespace aggup {
    template<typename Id, typename T>
    template<typename... Args> 
    AggregatorActivatorImp<Id, T>::AggregatorActivatorImp(Args... listeners)
    : aggregators()
    , elementsQueue( std::forward<Args>(listeners)... )
    , capacityReceiver() {

    }
    
    template<typename Id, typename T> bool AggregatorActivatorImp<Id, T>::operator[](Id id) {
        if ( auto found = aggregators.find(id); found != aggregators.end() ) {
            auto executor = createExecutor();
            executor->execute(*found->second);
            return capacityReceiver.capacity == detail::ContainerCapacity::Full;
        }else {
            return false;
        }
    }

    template<typename Id, typename T>
    std::unique_ptr< detail::ExecutorIterator<detail::Queue, Aggregator, T, detail::ContainerCapacity> > AggregatorActivatorImp<Id, T>::createExecutor() {
        return std::make_unique< detail::ContainExecutorIterator<detail::Queue, Aggregator, T> >( queueIterator.get(), &capacityReceiver );
    }

    template<typename Id, typename T>
    void AggregatorActivatorImp<Id, T>::update() {
        elementsQueue.pull();
        queueIterator = std::move( createIterator() );
    }
    
    template<typename Id, typename T> detail::IteratorUPtr< detail::Queue<T> > AggregatorActivatorImp<Id, T>::createIterator() {
        return elementsQueue.createIterator(); 
    }
    
    template<typename Id, typename T> void AggregatorActivatorImp<Id, T>::add(Id id, Aggregator<T> const* aggregator) {
        aggregators.emplace( std::make_pair(id, aggregator) ); 
    }
}

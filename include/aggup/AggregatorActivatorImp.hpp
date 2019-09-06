#ifndef AGGREGATORACTIVATORIMP_H
#define AGGREGATORACTIVATORIMP_H

#include <Listener.hpp>
#include <AggregatorActivator.hpp>
#include <map>
#include <detail/CapacityReceiver.inc>
#include <detail/ContainExecutorIterator.inc>
#include <detail/Queue.inc>

namespace aggup {
    
    template<typename Id, typename T>
    class AggregatorActivatorImp  : public AggregatorActivator<Id, T> {
    public:
        template<typename... Args> AggregatorActivatorImp(Args... listeners);
        bool operator[](Id id) override;
    protected:
        virtual std::unique_ptr< detail::ExecutorIterator<detail::Queue, Aggregator, T, detail::ContainerCapacity> > createExecutor();
    public:
        void add(Id id, Aggregator<T> const* aggregator) override;
        void update() override;
    protected:
        virtual std::unique_ptr<detail::Iterator< detail::Queue<T> >> createIterator();
    public:
    private:
        std::map< std::string, Aggregator<T> const* > aggregators;
        detail::Queue<T> elementsQueue;
        std::unique_ptr< detail::Iterator< detail::Queue<T> >> queueIterator;
        detail::CapacityReceiver capacityReceiver;
        
    };
}

#include <detail/AggregatorActivatorImp.inc>

#endif /* AGGREGATORACTIVATORIMP_H */

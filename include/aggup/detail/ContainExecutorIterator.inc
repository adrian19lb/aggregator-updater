#ifndef PROCESSEXECUTOR_H
#define PROCESSEXECUTOR_H

#include <detail/ExecutorIterator.inc>
#include <detail/ObserverReceiver.inc>
#include <detail/ContainerCapacity.inc>
#include <stdexcept>

namespace aggup::detail {

    template< template<typename T, typename... Args> class Container, 
              template<typename T> class Executee, 
              typename T, typename... Args>
    class ContainExecutorIterator : public ExecutorIterator< Container, Executee, T, ContainerCapacity, Args...> {
    public:
        using value_type = typename ExecutorIterator< Container, Executee, T, ContainerCapacity, Args... >::value_type;
    public:
        ContainExecutorIterator(Iterator< Container<T, Args...> >* iterator, ObserverReceiver<ContainerCapacity>* receiver)
        : ExecutorIterator<Container, Executee, T, ContainerCapacity, Args...>(iterator)
        , START_VALUE(0)
        , receiver(receiver) {
            counter = START_VALUE;
        }

    private:
         void executeForSingle(Executee<T> const& object, value_type const& value) override {
            if ( counter += object.contain(value); counter == object.size() ) {
                notify(ContainerCapacity::Full);
                throw std::out_of_range("Reached object size");
            }else {
                notify(ContainerCapacity::Empty);
            }
         }

         void tearDownAfterIterate() override {
            counter = START_VALUE;
         }

    private:
         void notify(ContainerCapacity capacity) override {
            receiver->receive(capacity);
         }
    private:
        ObserverReceiver<ContainerCapacity>* receiver;
        int counter;
        const int START_VALUE;
    };
}

#endif /* PROCESSEXECUTOR_H */

#ifndef CONTAINERCAPACITYRECEIVER_H
#define CONTAINERCAPACITYRECEIVER_H

#include <detail/ObserverReceiver.inc>
#include <detail/ContainerCapacity.inc>

namespace aggup::detail {

    class CapacityReceiver : public ObserverReceiver<ContainerCapacity> {
    public:
        CapacityReceiver()
        : capacity{ContainerCapacity::Empty} {
        
        }
    private:
        void receive(ContainerCapacity capacity) override {
            this->capacity = capacity; 
        }

    public:
        ContainerCapacity capacity;

    };

}

#endif /* CONTAINERCAPACITYRECEIVER_H */

#ifndef RECEIVER_H
#define RECEIVER_H

namespace aggup::detail {

    template<typename T, typename... Args>
    class ObserverReceiver {
    public:
        virtual void receive(T item, Args... optional) = 0;    
    };

}

#endif /* RECEIVER_H */

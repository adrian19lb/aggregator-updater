#ifndef STUBLISTENER_H
#define STUBLISTENER_H

#include <Listener.hpp>

namespace  aggup {
    
    template<typename T>
    class StubListener : public Listener<T> {
    public:
        T listened;

        T listen() override {
            return listened;
        }
    };

}

#endif /* STUBLISTENER_H */

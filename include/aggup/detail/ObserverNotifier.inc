#ifndef OBSERVERNOTIFIER_H
#define OBSERVERNOTIFIER_H

namespace aggup::detail {
    
    template<typename T, typename... Args>
    class ObserverNotifier {
    public:
        virtual void notify(T item, Args... optional) = 0;
    };

}

#endif /* OBSERVERNOTIFIER_H */

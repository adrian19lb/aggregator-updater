#ifndef LISTENER_HPP
#define LISTENER_HPP

namespace aggup {

    template<typename T>
    class Listener {
    public:
        virtual ~Listener () = default;
        virtual T listen() = 0;
    };

}

#endif /* ifndef LISTENER_HPP */

#ifndef ITERATOR
#define ITERATOR

namespace aggup::detail {
    
    template<typename Container> 
    class Iterator {
    public:
        virtual ~Iterator() = default;
        virtual void next() = 0;
        virtual bool hasNext() = 0;
        virtual typename Container::value_type current() = 0;
    };
}


#endif /* ifndef ITERATOR */

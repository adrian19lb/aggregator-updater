#ifndef EXECUTORITERATOR_HPP
#define EXECUTORITERATOR_HPP

#include <detail/Iterator.inc>
#include <detail/ObserverNotifier.inc>
#include <iostream>

namespace aggup::detail {

    template< template<typename T, typename... Args> class Container, 
              template<typename T> class Executee, 
              typename T, typename Observable, typename... Args>
    class ExecutorIterator : public ObserverNotifier<Observable> {
    public:
        using value_type = typename Container<T, Args...>::value_type;
    public:
        ExecutorIterator(Iterator< Container<T, Args...> >* iterator)
        :iterator(iterator) {
        
        }

        virtual ~ExecutorIterator() = default;

        void execute(Executee<T>  const& object) {
            iterate(object);
            tearDownAfterIterate();
        }

        virtual void notify(Observable state) = 0;
    private:
        void iterate(Executee<T> const& object) {
            while ( iterator->hasNext() ) {
                try {
                    executeForSingle(object, iterator->current() );
                    iterator->next();
                }catch(std::exception const& except) {
                    std::cerr << except.what() << std::endl;
                    break; 
                }
            }
        }

    protected:
        virtual void executeForSingle(Executee<T> const& object, value_type const& value) = 0;
        virtual void tearDownAfterIterate() = 0;
    private:
        Iterator< Container<T, Args...> >* iterator;
    };

}


#endif /* ifndef EXECUTORITERATOR_HPP */

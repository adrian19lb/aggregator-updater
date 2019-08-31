#ifndef FAKEITERATOR_H
#define FAKEITERATOR_H

#include <detail/Iterator.inc>
#include <cstddef>

namespace aggup::detail::testing {

    template<typename Container>
    class FakeIterator : public Iterator<Container> {
    public:
        FakeIterator(size_t iterationAmount)
        : iterationAmount(iterationAmount)
        , RESET(0)
        , counter(RESET) {
        
        }

        void next() override {
            ++counter;
        }

        typename Container::value_type current() override {
            return counter; 
        }

        bool hasNext() override {
            if (counter <= iterationAmount) {
                return true;
            }else {
                counter = RESET;
                return false;
            }
        }
    private:
        size_t iterationAmount;
        int const RESET;
        int counter;
    };

}

#endif /* FAKEITERATOR_H */

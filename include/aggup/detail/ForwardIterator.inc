#ifndef FORWARDITERATOR_H
#define FORWARDITERATOR_H

#include <detail/Iterator.inc>
#include <iostream>
#include <stdexcept>

namespace aggup::detail {
     
    template<typename Container>
    class ForwardIterator : public Iterator<Container> {
        class PositionTag {
        public:
            enum class Id {
                Between,
                Endness
            };

            PositionTag(Id tag)
            : tag{tag} {
            
            }

            void replace(Id tag) {
                this->tag = tag;
            }

            Id status() const {
               return tag;
            }
        private:
            Id tag;
        };
    private:
        using iterator = typename Container::iterator;
        using const_iterator = typename Container::const_iterator;
        using value_type = typename Container::value_type;
    public:
        ForwardIterator(iterator start, iterator last)
        : indicator(start)
        , start(start)
        , last(last)
        , position(PositionTag::Id::Between) {
            
        }

        ForwardIterator(ForwardIterator&& moveable) {
            moveIterator( std::forward<ForwardIterator>(moveable) ); 
        }

        ForwardIterator& operator=(ForwardIterator&& moveable) {
            moveIterator( std::forward<ForwardIterator>(moveable) ); 
        }

        void moveIterator(ForwardIterator&& moveable) {
            indicator = std::make_move_iterator(moveable.indicator);
            start = std::make_move_iterator(moveable.start);
            last = std::make_move_iterator(moveable.last);
            position = std::move(moveable.position);
        }

        void next() override {
            try {
                incrementIfNotLast();
                position.replace(PositionTag::Id::Between);
                checkEmptinessOrEndness();
            }catch(std::out_of_range const& except) {
                indicator = start;
                position.replace(PositionTag::Id::Endness);
            }
        }

    private:
        void incrementIfNotLast() {
            if (indicator != last)  {
                ++indicator;
            }
        }
        void checkEmptinessOrEndness() {
            if (indicator == last || start == last) {
                throw std::out_of_range("Iterator out of range");
            }
        }
    public: 
        bool hasNext() override {
            if (position.status() == PositionTag::Id::Between) {
                return true;
            }else {
                return false;
            }
        }

        typename Container::value_type current() override {
            checkEmptinessOrEndness();
            
            return *indicator;
        }

    private:
        iterator indicator;
        iterator start;
        iterator last;
        PositionTag position;
    };
}


#endif /* FORWARDITERATOR_H */

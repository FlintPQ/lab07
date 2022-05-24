//
// Created by flint on 18.05.2022.
//

#ifndef LAB07_ULTRACOOLCYCLEDBUFFERALLRIGHTSRESERVED_H
#define LAB07_ULTRACOOLCYCLEDBUFFERALLRIGHTSRESERVED_H

#include <memory>


template<class T>
#define link std::shared_ptr<bNode<T>>
struct bNode {
    link mommy;
    link son;
    T value;
    int node_type; // 0 - common; 1 - floor; 2 - roof

};


template<class T>
class UltraCoolCycledBufferAllRightsReserved {
public:
    class UltraCoolCycledBufferAllRightsReserved_iterator : public std::iterator<std::forward_iterator_tag, T, T, const T*, const T&> {
    public:
        std::shared_ptr<bNode<T>> content;
        int type;
        explicit UltraCoolCycledBufferAllRightsReserved_iterator(std::shared_ptr<bNode<T>> x, int type_): content(x), type(type_) {}
        UltraCoolCycledBufferAllRightsReserved_iterator &operator++() {
            content = content->son;
            if (content->node_type == 1){
                type = -1;
            }
            return *this;
        }

        friend bool operator<(UltraCoolCycledBufferAllRightsReserved_iterator left, UltraCoolCycledBufferAllRightsReserved_iterator& other) {
            while (left != other){
                if (left.content->node_type == 2){
                    return true;
                }

                return false;
            }
        }
        int operator-(UltraCoolCycledBufferAllRightsReserved_iterator other){
            int dur = 0;
            while (*this != other){
                ++dur;
                --other;
            }

            return dur;
        }

        UltraCoolCycledBufferAllRightsReserved_iterator& operator+(int n) {
            for (int i = 0; i < n; ++i){
                ++(*this);
            }

            return *this;
        }

        UltraCoolCycledBufferAllRightsReserved_iterator& operator-(int n) {
            for (int i = 0; i < n; ++i){
                --(*this);
            }

            return *this;
        }

        UltraCoolCycledBufferAllRightsReserved_iterator& operator++(int) {
            UltraCoolCycledBufferAllRightsReserved_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        UltraCoolCycledBufferAllRightsReserved_iterator &operator--() {
            content = content->mommy;
            return *this;
        }

        UltraCoolCycledBufferAllRightsReserved_iterator &operator--(int) {
            UltraCoolCycledBufferAllRightsReserved_iterator tmp = *this;
            --(*this);
            return tmp;
        }


        T& operator*() const { return content->value; }
        friend bool operator== (const UltraCoolCycledBufferAllRightsReserved_iterator& a, const UltraCoolCycledBufferAllRightsReserved_iterator& b) { return a.content->mommy == b.content->mommy && a.type == b.type ; };
        friend bool operator!= (const UltraCoolCycledBufferAllRightsReserved_iterator& a, const UltraCoolCycledBufferAllRightsReserved_iterator& b) { return a.content->mommy != b.content->mommy || a.type != b.type; };
    };

    void push_back(T value){
        push(value, 2);
        ++roof;
    }

    void insert(UltraCoolCycledBufferAllRightsReserved_iterator target, T value){
        if (target == roof){
            push_back(value);
        } else if (target == floor){
            push_forward(value);
        } else{
            std::shared_ptr<bNode<T>> buff = std::make_shared<bNode<T>>(bNode<T>{std::shared_ptr<bNode<T>>{target.content}, std::shared_ptr<bNode<T>>{(++target).content}, value, 0});
            target.content->mommy = buff;
            (--target).content->son = buff;
            ++size;
        }
    }

    void remove(UltraCoolCycledBufferAllRightsReserved_iterator &target){
        --size;
        if (size == 0){
            floor = UltraCoolCycledBufferAllRightsReserved_iterator{nullptr};
            roof = UltraCoolCycledBufferAllRightsReserved_iterator{nullptr};
            target = floor;
        } else{
            auto buff = target.content->mommy->son;
            target.content->mommy->son = target.content->son;
            target.content->son->mommy = buff;
            target = UltraCoolCycledBufferAllRightsReserved_iterator{target.content->mommy};
        }

    }
    void push_forward(T value){
        push(value, 1);
        ++floor;
    }

    int length(){
        return size;
    }

    T top(){
        return *roof;
    }

    T bot(){
        return *floor;
    }

    UltraCoolCycledBufferAllRightsReserved_iterator operator[](int i){
        return begin() + i;
    }

    UltraCoolCycledBufferAllRightsReserved_iterator begin(){
        return floor;
    }

    UltraCoolCycledBufferAllRightsReserved_iterator last(){
        return roof;
    }

    UltraCoolCycledBufferAllRightsReserved_iterator end(){
        return UltraCoolCycledBufferAllRightsReserved_iterator{std::make_shared<bNode<T>>(bNode<T>{roof.content, nullptr, -1}), -1};
    }
private:
    int size = 0;


    void push(T value, int node_type){
        if (size == 0) {
            std::shared_ptr<bNode<T>> buff = std::make_shared<bNode<T>>(bNode<T>{nullptr, nullptr, value, 2});
            buff->son = buff;
            buff->mommy = buff;
            floor = UltraCoolCycledBufferAllRightsReserved_iterator{buff, 1};
            roof = UltraCoolCycledBufferAllRightsReserved_iterator{buff, 2};
            floor.content->node_type = 1;
        } else{
            std::shared_ptr<bNode<T>> buff = std::make_shared<bNode<T>>(bNode<T>{std::shared_ptr<bNode<T>>{roof.content}, std::shared_ptr<bNode<T>>{floor.content}, value, node_type});
            roof.content->son = buff;
            floor.content->mommy = buff;
        }
        ++size;
    }

    UltraCoolCycledBufferAllRightsReserved_iterator floor = UltraCoolCycledBufferAllRightsReserved_iterator{nullptr, 1};
    UltraCoolCycledBufferAllRightsReserved_iterator roof = UltraCoolCycledBufferAllRightsReserved_iterator{nullptr, 2};

};

#endif //LAB07_ULTRACOOLCYCLEDBUFFERALLRIGHTSRESERVED_H

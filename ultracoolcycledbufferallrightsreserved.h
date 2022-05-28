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
struct UltraCoolCycledBufferAllRightsReserved {
public:
    class UltraCoolCycledBufferAllRightsReserved_basic_iterator : public std::iterator<std::random_access_iterator_tag, T, T, const T*, const T&> {
    public:
        std::shared_ptr<bNode<T>> content;
        int type;
        explicit UltraCoolCycledBufferAllRightsReserved_basic_iterator(std::shared_ptr<bNode<T>> x, int type_): content(x), type(type_) {}

        virtual UltraCoolCycledBufferAllRightsReserved_basic_iterator &operator++() {
            content = content->son;
            if (content->node_type == 1){
                type = -1;
            }
            return *this;
        }

        friend bool operator<(UltraCoolCycledBufferAllRightsReserved_basic_iterator left, UltraCoolCycledBufferAllRightsReserved_basic_iterator& other) {
            while (left != other){
                if (left.content->node_type == 2){
                    return true;
                }

                return false;
            }
        }
        

        UltraCoolCycledBufferAllRightsReserved_basic_iterator& operator++(int) {
            UltraCoolCycledBufferAllRightsReserved_basic_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        virtual UltraCoolCycledBufferAllRightsReserved_basic_iterator &operator--() {
            content = content->mommy;
            return *this;
        }

        UltraCoolCycledBufferAllRightsReserved_basic_iterator &operator--(int) {
            UltraCoolCycledBufferAllRightsReserved_basic_iterator tmp = *this;
            --(*this);
            return tmp;
        }


        T& operator*() const { return content->value; }
        friend bool operator== (const UltraCoolCycledBufferAllRightsReserved_basic_iterator& a, const UltraCoolCycledBufferAllRightsReserved_basic_iterator& b) { return a.content->mommy == b.content->mommy && a.type == b.type ; };
        friend bool operator!= (const UltraCoolCycledBufferAllRightsReserved_basic_iterator& a, const UltraCoolCycledBufferAllRightsReserved_basic_iterator& b) { return a.content->mommy != b.content->mommy || a.type != b.type; };
    };


    class UltraCoolCycledBufferAllRightsReserved_iterator : public UltraCoolCycledBufferAllRightsReserved_basic_iterator{
    private:
        std::shared_ptr<bNode<T>> *data;
        int ind;
    public:
        explicit UltraCoolCycledBufferAllRightsReserved_iterator(UltraCoolCycledBufferAllRightsReserved_basic_iterator bb, int struct_size, UltraCoolCycledBufferAllRightsReserved_basic_iterator &enn= nullptr): data(new bNode<T>[struct_size]){
            this->content = enn != nullptr ? enn.content : bb.content;
            ind = enn != nullptr ? struct_size - 1 : 0;
            for (int i = 0; i < struct_size; ++i){
                data[0] = bb.content;
                ++bb;
            }
        }

        UltraCoolCycledBufferAllRightsReserved_basic_iterator &operator+(int i) {
            auto b = *this;
            b.content = data[ind + i];
            return b;
        }

        friend UltraCoolCycledBufferAllRightsReserved_basic_iterator &operator+(int i, UltraCoolCycledBufferAllRightsReserved_basic_iterator & it) {
            auto b = it;
            b.content = it.data[it.ind + i];
            return b;
        }

        UltraCoolCycledBufferAllRightsReserved_basic_iterator &operator-(int i) {
            auto b = *this;
            b.content = data[ind + i];
            return b;
        }

        friend UltraCoolCycledBufferAllRightsReserved_basic_iterator &operator-(int i, UltraCoolCycledBufferAllRightsReserved_basic_iterator & it) {
            auto b = it;
            b.content = it.data[it.ind - i];
            return b;
        }

        UltraCoolCycledBufferAllRightsReserved_iterator &operator++(){
            UltraCoolCycledBufferAllRightsReserved_basic_iterator::operator++(this);
            ++ind;
        }

        UltraCoolCycledBufferAllRightsReserved_iterator &operator--(){
            UltraCoolCycledBufferAllRightsReserved_basic_iterator::operator--(this);
            ++ind;
        }

    };

    void push_back(T value){
        push(value, 2);
        ++roof;
    }

    void insert(UltraCoolCycledBufferAllRightsReserved_basic_iterator target, T value){
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

    void remove(UltraCoolCycledBufferAllRightsReserved_basic_iterator &target){
        --size;
        if (size == 0){
            floor = UltraCoolCycledBufferAllRightsReserved_basic_iterator{nullptr};
            roof = UltraCoolCycledBufferAllRightsReserved_basic_iterator{nullptr};
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
        return ltraCoolCycledBufferAllRightsReserved_iterator(floor, size);
    }

    UltraCoolCycledBufferAllRightsReserved_iterator last(){
        return UltraCoolCycledBufferAllRightsReserved_iterator(floor, size, roof);
    }

    UltraCoolCycledBufferAllRightsReserved_iterator end(){
        return UltraCoolCycledBufferAllRightsReserved_iterator(floor, size, UltraCoolCycledBufferAllRightsReserved_basic_iterator{std::make_shared<bNode<T>>(bNode<T>{roof.content, nullptr, -1}), -1});
    }
private:
    int size = 0;


    void push(T value, int node_type){
        if (size == 0) {
            std::shared_ptr<bNode<T>> buff = std::make_shared<bNode<T>>(bNode<T>{nullptr, nullptr, value, 2});
            buff->son = buff;
            buff->mommy = buff;
            floor = UltraCoolCycledBufferAllRightsReserved_basic_iterator{buff, 1};
            roof = UltraCoolCycledBufferAllRightsReserved_basic_iterator{buff, 2};
            floor.content->node_type = 1;
        } else{
            std::shared_ptr<bNode<T>> buff = std::make_shared<bNode<T>>(bNode<T>{std::shared_ptr<bNode<T>>{roof.content}, std::shared_ptr<bNode<T>>{floor.content}, value, node_type});
            roof.content->son = buff;
            floor.content->mommy = buff;
        }
        ++size;
    }

    UltraCoolCycledBufferAllRightsReserved_basic_iterator floor = UltraCoolCycledBufferAllRightsReserved_basic_iterator{nullptr, 1};
    UltraCoolCycledBufferAllRightsReserved_basic_iterator roof = UltraCoolCycledBufferAllRightsReserved_basic_iterator{nullptr, 2};

};

#endif //LAB07_ULTRACOOLCYCLEDBUFFERALLRIGHTSRESERVED_H

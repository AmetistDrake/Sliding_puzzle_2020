#ifndef POTHAZI_FUNCTOR_HPP
#define POTHAZI_FUNCTOR_HPP

#include "Node.hpp"
#include <sstream>

class Functor {
public:
    bool operator()(const Node *n1, const Node *n2) const {
        return n1->get_cost() < n2->get_cost();
    }
};

class node_pointer_hash {
public:
    size_t operator()(Node* const &s) const {
        size_t hash;
        stringstream ss;
        for (auto &i : s->get_state().get_array()) {
            ss << i;
        }

        ss >> hash;
        // cout << hash << endl;
        return hash;
    }
};

struct node_pointer_equal {
    bool operator () ( Node const * lhs, Node const * rhs ) const {
        for (int i = 0; i < lhs->get_state().get_number_of_rows(); ++i){
            if (lhs->get_state().get_array()[i] != rhs->get_state().get_array()[i])
            {
                return false;
            }
        }
        return true;
    }
};

class node_pointer_compare {
public:
    bool operator()(Node* lhs, Node* rhs) {
        return lhs->get_cost() > rhs->get_cost();
    }
};


#endif//POTHAZI_FUNCTOR_HPP

#ifndef POT_HF_NODE_HPP
#define POT_HF_NODE_HPP
#include "State.hpp"

class Node {
private:
    State state;
    Node* parent;
    int depth{};
    int cost = 0;

public:
    Node(const State& s, Node* p, int d) : state(s), parent(p), depth(d) {
        cost = get_cost1() + get_cost2() + depth;
    }

    int get_cost1() {
        int cost1 = 0;
        const std::vector<int>& s = state.get_array();

        for (size_t i = 0; i < s.size(); ++i) {
            size_t v = s[i];
            if (v == 0) continue;
            if (v != i + 1) cost1++;
        }
        return cost1;
    }
    int get_cost2(){
        int cost2 = 0;
        const std::vector<int>& s = state.get_array();
        int rows_or_cols = state.get_number_of_rows();
        for (unsigned int i = 0; i < s.size(); ++i) {

            int v = s[i];
            if (v == 0) continue;

            // actual index of v should be v-1
            v--;

            int gx = v % rows_or_cols;
            int gy = v / rows_or_cols;

            int x = i % rows_or_cols;
            int y = i / rows_or_cols;

            cost += abs(x - gx) + abs(y - gy);
        }
        return cost2;
    }

    Node* get_parent(){
        return parent;
    }

    [[nodiscard]] const State& get_state() const{
        return state;
    }

    [[nodiscard]] int get_depth() const{
        return depth;
    }
    [[nodiscard]] int get_cost() const {
        return cost;
    }

    void print() const {
//        cout << "depth: " << depth << endl;
        cout << "cost: " << cost << endl;
        state.print();
    }
};

#endif//POT_HF_NODE_HPP

#ifndef POT_HF_SOLVER_HPP
#define POT_HF_SOLVER_HPP
#include "Functor.hpp"
#include "Node.hpp"
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <unordered_set>

using namespace std;

class Solver {
private:
    // vector<Node*> open_list;
    priority_queue<Node*, vector<Node*>, node_pointer_compare> open_list;
    unordered_set<Node*, node_pointer_hash, node_pointer_equal> closed_list;
    // vector<Node*> closed_list;

    const State &start;
    const State &goal;
    bool solved = false;
    std::map<int, std::vector<int>> edges;
    std::vector<Node *> solution;

    [[nodiscard]] bool is_solved(Node *next) {
        if (next->get_state() == goal) {
            return true;
        }
        return false;
    }
    [[nodiscard]] Node *get_next_node() {
        //A functor használatára egy példa

//        auto it(std::min_element(open_list.begin(), open_list.end(), Functor())); // Ez annyiban jobb mint egy priority_queue-s megoldás, hogy elérhetőek az elemek
//        Node * selected = *it;
//        open_list.erase(it);
        Node *selected = open_list.top();
        open_list.pop();
        return selected;
    }

    void expand_node(Node *current) {
        int empty_ind = current->get_state().find_empty();
        for (auto e : edges[empty_ind]) {
            State s(current->get_state());
            s.swap_values(e, empty_ind);
            Node *n = new Node(s, current, current->get_depth() + 1);
            if (closed_list.find(n) == closed_list.end()) { // !is_in_closed_list(s)
                open_list.push(n);
                //open_list.push_back(n);
            }
        }
    }
    bool is_in_closed_list(const State& s){
        for (auto& c : closed_list) {
            if (s == c->get_state()) {
                return true;
            }
        }
        return false;
    }

public:
    ~Solver() {
        for (auto c : closed_list) {
            delete c;
        }
        closed_list.clear();
//        for (auto o : open_list) {
//            delete o;
//        }
//        open_list.clear();
        while (!open_list.empty()) {
            Node *n = open_list.top();
            open_list.pop();
            delete n;
        }
    }

    Solver(const State &from, const State &to) : start(from), goal(to) {
        int N = from.get_number_of_rows();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int pos = i * N + j;
                vector<int> nbs;
                int up = pos - N;
                int down = pos + N;
                int left = pos - 1;
                int right = pos + 1;

                // corner
                if (i == 0 && j == 0) {
                    nbs.push_back(right);
                    nbs.push_back(down);
                } else if (i == 0 && j == N - 1) {
                    nbs.push_back(left);
                    nbs.push_back(down);
                } else if (i == N - 1 && j == 0) {
                    nbs.push_back(up);
                    nbs.push_back(right);
                } else if (i == N - 1 && j == N - 1) {
                    nbs.push_back(up);
                    nbs.push_back(left);
                }
                // edge
                else if (i == 0) {
                    nbs.push_back(left);
                    nbs.push_back(down);
                    nbs.push_back(right);
                } else if (i == N - 1) {
                    nbs.push_back(left);
                    nbs.push_back(up);
                    nbs.push_back(right);
                } else if (j == 0) {
                    nbs.push_back(up);
                    nbs.push_back(right);
                    nbs.push_back(down);
                } else if (j == N - 1) {
                    nbs.push_back(up);
                    nbs.push_back(left);
                    nbs.push_back(down);
                }
                // inner
                else {
                    nbs.push_back(up);
                    nbs.push_back(down);
                    nbs.push_back(left);
                    nbs.push_back(right);
                }
                edges[pos] = nbs;
            }
        }
    }
    static bool is_solvable(const State &state) {
        int inv_count = 0;
        const std::vector<int> &arr = state.get_array();
        for (unsigned int i = 0; i < arr.size() - 1; ++i)
            for (unsigned int j = i + 1; j < arr.size(); ++j)
                if (arr[j] && arr[i] && arr[i] > arr[j])
                    inv_count++;
        if (state.get_number_of_rows() % 2 == 1)// páratlan eset pl 3x3
        {
            return (inv_count % 2 == 0);
        } else {// páros eset 2x2
            return (inv_count % 2 == 1);
        }
    }

    int solve() {
        for (auto c : closed_list) {
            delete c;
        }
        closed_list.clear();
//        for (auto o : open_list) {
//            delete o;
//        }
//        open_list.clear();
        while (!open_list.empty()) {
            Node *n = open_list.top();
            open_list.pop();
            delete n;
        }

        solved = false;
        int result_depth = 0;
        Node *current = new Node(start, nullptr, 0);
        open_list.push(current);
//        open_list.push_back(current);

        if (is_solvable(start)) {
            int i = 0;
//            cout << "START " << endl;
            while (!open_list.empty() && !solved) {
//                cout << "Iteration: " << i << endl;
//                cout << "Open list is: " << endl;
//                priority_queue<Node*, vector<Node*>, Node_pointer_compare> tmp(open_list);
//                while(!tmp.empty()) {
//                    tmp.top()->print();
//                    tmp.pop();
//                }
////                for (auto o : open_list) {
////                    o->print();
////                }
//                cout << "Closed list is: "<< endl;
//                for (auto c : closed_list) {
//                    c->print();
//                }

                current = get_next_node();
//                cout << "Current is: " << endl;
//                current->print();

                if (is_solved(current)) {
                    solved = true;
                    result_depth = current->get_depth();
                } else {
                    //closed_list.push_back(current);
                    closed_list.insert(current);

                    //auto timer_start = chrono::high_resolution_clock::now();
                    expand_node(current);

                    //auto timer_stop = chrono::high_resolution_clock::now();
                    //auto duration = duration_cast<chrono::microseconds>(timer_stop - timer_start);
                    //cout << duration.count() << endl;

                    // closed_list.insert(current->get_state());
//                    Node* tmp = current;
//                    current = nullptr;
//                    delete tmp;
                }
                i++;
            }
        } else {
            return -1;
        }

        if (solved) {
            while (current->get_parent() != nullptr) {
                solution.push_back(current);
                current = current->get_parent();
            }
        }

        return result_depth;
    }
};


#endif//POT_HF_SOLVER_HPP

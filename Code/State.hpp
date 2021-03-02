#ifndef POT_HF_STATE_HPP
#define POT_HF_STATE_HPP
#ifndef POTHAZI_STATE_HPP
#define POTHAZI_STATE_HPP

#include <random>
#include <utility>
#include <vector>
#include <iostream>

using namespace std;

//Ez az osztály a játék adott állapotát mutatja
//Egy egydimenziós vektor reprezentálja az állapotot
//A 0 értékű elem reprezentálja az üres helyet
class State{
private:
    std::vector<int> tiles;
    int N;
public:

    //constructors
    State(int n, std::vector<int>  t) : tiles(std::move(t)), N(n) {};
    //copy constructor
    State(const State& other){
        N = other.N;
        tiles = other.tiles;
    }
    //assignment operator
    State& operator = (const State& other){
        if (*this != other) {
            this->N = other.N;
            this->tiles = other.tiles;
        }
        return *this;
    }
    //Overload =,!= operators
    bool operator ==(const State& other) const{
        if (N != other.N) {
            return false;
        }
        else {
            for (size_t i = 0; i < tiles.size(); i++) {
                if (tiles[i] != other.tiles[i]) {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator !=(const State& other) const{
        return !(*this == other);
    }
    //üres hely megkeresése
    [[nodiscard]] int find_empty() const{
        for (size_t i = 0; i < tiles.size(); i++)
        {
            if (tiles[i] == 0)
            {
                return i;
            }
        }
        return -1;
    }
    //megcseréli az adott indexű elemeket
    void swap_values(int ind1, int ind2){
        int tmp = tiles[ind1];
        tiles[ind1] = tiles[ind2];
        tiles[ind2] = tmp;
    }
    //Getter
    [[nodiscard]] const std::vector<int>&get_array() const{
        return tiles;
    }
    [[nodiscard]] int get_number_of_rows() const{
        return N;
    }

    void print() const {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << tiles[i*N+j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};


#endif//POTHAZI_STATE_HPP
#endif//POT_HF_STATE_HPP

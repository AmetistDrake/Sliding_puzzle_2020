#include "Solver.hpp"

#include "woodpecker.hpp"
#include <chrono>
#include <iostream>

TEST("Constructors, copy assignment",1){
    State state_1(2,std::vector<int>{1,2,3,4});
    State state_2(state_1);
    CHECK_EQ(true,state_2==state_1);
    CHECK_EQ(false,state_1!=state_2);
    State state_3=state_2;
    CHECK_EQ(true, state_2==state_3);
    CHECK_EQ(true, state_1==state_3);
    State state_4(2,std::vector<int>{1,2,4,3});
    CHECK_EQ(true,state_4!=state_1);
    CHECK_EQ(false,state_4==state_1);
}

TEST("Find the empty slot",1){

State goal(3, std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 0 });
CHECK_EQ(goal.find_empty(),8);
}

TEST("Swap with empty",1){
    State goal(3, std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 0 });
    goal.swap_values(2, 8);
    CHECK_EQ(goal.find_empty(),2);
    goal.swap_values(5, 2);
    CHECK_EQ(goal.find_empty(),5);
}

TEST("Solver is solvable",1){
    State goal(3, std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 0 });
    State start0(3, std::vector<int>{ 3, 4, 5, 7, 1, 2, 6, 8, 0});
    State start1(3, std::vector<int>{ 7, 5, 0, 1, 6, 8, 2, 3, 4});
    Solver solver0(start0, goal);

    CHECK_EQ(false,solver0.is_solvable(start0));
    CHECK_EQ(true,solver0.is_solvable(start1));
}

TEST("solve_easy", 1) {
    State goal(2, vector<int>{1, 2, 3, 0});
    State start1(2, vector<int>{0,2,1,3});
    Solver solver0(start1, goal);
    CHECK_EQ(2, solver0.solve());
}


TEST("solve_easy", 1) {
    State goal(3, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 0});
    State start1(3, vector<int>{1, 2, 3, 4, 8, 5, 7, 0, 6});
    Solver solver0(start1, goal);
    CHECK_EQ(3, solver0.solve());
}

TEST("solve_easy", 1) {
    State goal(3, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 0});
    State start1(3, vector<int>{1, 2, 3, 4, 8, 5, 7, 6, 0});
    Solver solver0(start1, goal);
    CHECK_EQ(4, solver0.solve());
}

TEST("solve_easy", 1) {
    State goal(3, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 0});
    State start1(3, vector<int>{1, 2, 3, 4, 8, 0, 7, 6, 5});
    Solver solver0(start1, goal);
    CHECK_EQ(5, solver0.solve());
}

TEST("Solve",1){
    State goal(3, std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 0 });
    State start1(3, std::vector<int>{ 7, 5, 0, 1, 6, 8, 2, 3, 4});
    Solver solver0(start1, goal);
    MEASURE("solving",1.5s) {
        CHECK_EQ(26, solver0.solve());
    }
    State start2(3, std::vector<int>{ 0, 2, 1, 5, 8, 3, 7, 6, 4});
    Solver solver1(start2,goal);
    MEASURE("solving",1.5s) {
        CHECK_EQ(20, solver1.solve());
    }
    State start0(3, std::vector<int>{ 3, 4, 5, 7, 1, 2, 6, 8, 0});
    Solver solver2(start0,goal);
    CHECK_EQ(-1,solver2.solve());
}

WOODPECKER_MAIN(-1, -1)
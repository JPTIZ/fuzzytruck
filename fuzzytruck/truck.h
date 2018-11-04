#ifndef TRUCK_CPP_FUZZYTRUCK_TRUCK_H
#define TRUCK_CPP_FUZZYTRUCK_TRUCK_H

namespace fuzzytruck {

class FunctionBlockTruck {

    public: 
    double direction;
    double x;
    double y;

    double action;

    private: 
    double direction_east;
    double direction_north;
    double direction_northeast;
    double direction_northwest;
    double direction_south;
    double direction_southeast;
    double direction_southwest;
    double direction_west;

    double x_centered;
    double x_too_left;
    double x_too_right;

    double y_close;
    double y_really_close;
    double y_really_far;


    double defuzzify_action[1000];


    public:
    FunctionBlockTruck();
    void calc();
    void print();

    private:
    void defuzzify();
    void fuzzify();
    void reset();
    double membership_action_turn_left(double x);
    double membership_action_turn_none(double x);
    double membership_action_turn_right(double x);
    double membership_direction_east(double x);
    double membership_direction_north(double x);
    double membership_direction_northeast(double x);
    double membership_direction_northwest(double x);
    double membership_direction_south(double x);
    double membership_direction_southeast(double x);
    double membership_direction_southwest(double x);
    double membership_direction_west(double x);
    double membership_x_centered(double x);
    double membership_x_too_left(double x);
    double membership_x_too_right(double x);
    double membership_y_close(double x);
    double membership_y_really_close(double x);
    double membership_y_really_far(double x);
    void calc_truck_rules();

};

}

#endif
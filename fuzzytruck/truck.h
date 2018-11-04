#ifndef TRUCK_CPP_FUZZYTRUCK_TRUCK_H
#define TRUCK_CPP_FUZZYTRUCK_TRUCK_H

namespace fuzzytruck {

class FunctionBlockTruck {

    public: 
    double angle;
    double x;
    double y;

    double action;

    private: 
    double angle_left;
    double angle_right;
    double angle_vertical;

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
    double membership_angle_left(double x);
    double membership_angle_right(double x);
    double membership_angle_vertical(double x);
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
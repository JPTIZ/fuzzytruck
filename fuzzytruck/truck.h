#ifndef TRUCK_CPP_FUZZYTRUCK_TRUCK_H
#define TRUCK_CPP_FUZZYTRUCK_TRUCK_H

namespace fuzzytruck {

class FunctionBlockTruck {

    public: 
    double dir;
    double x;
    double y;

    double action;

    private: 
    double dir_east;
    double dir_north;
    double dir_south;
    double dir_west;

    double x_center;
    double x_left;
    double x_right;

    double y_far;


    double defuzzify_action[1000];


    public:
    FunctionBlockTruck();
    void calc();
    void print();

    private:
    void defuzzify();
    void fuzzify();
    void reset();
    double membership_action_left(double x);
    double membership_action_right(double x);
    double membership_dir_east(double x);
    double membership_dir_north(double x);
    double membership_dir_south(double x);
    double membership_dir_west(double x);
    double membership_x_center(double x);
    double membership_x_left(double x);
    double membership_x_right(double x);
    double membership_y_far(double x);
    void calc_truck_rules();

};

}

#endif
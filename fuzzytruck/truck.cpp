#include <stdio.h>
#include <stdlib.h>
#include "truck.h"

namespace fuzzytruck {


double rule_accumulation_method_max(double defuzzifier_value, double value_to_aggregate) {
    return defuzzifier_value > value_to_aggregate ? defuzzifier_value : value_to_aggregate;
}

double rule_activation_method_min(double degree_of_support, double membership) {
    return degree_of_support < membership ? degree_of_support : membership;
}

double rule_connection_method_and(double antecedent1, double antecedent2) {
    return antecedent1 < antecedent2 ? antecedent1 : antecedent2;
}


FunctionBlockTruck::FunctionBlockTruck() {
    action = 0.0;
}

void FunctionBlockTruck::calc() {
    reset();
    fuzzify();
    calc_truck_rules();
    defuzzify();
}

void FunctionBlockTruck::calc_truck_rules() {
    auto degree_of_support_1 = 1.0 * (rule_connection_method_and(x_left , dir_north));
    if(degree_of_support_1 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_right(x);
            auto y = rule_activation_method_min(degree_of_support_1 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_2 = 1.0 * (rule_connection_method_and(rule_connection_method_and(x_left , y_far) , dir_east));
    if(degree_of_support_2 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_right(x);
            auto y = rule_activation_method_min(degree_of_support_2 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_3 = 1.0 * (rule_connection_method_and(rule_connection_method_and(x_left , y_far) , dir_south));
    if(degree_of_support_3 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_left(x);
            auto y = rule_activation_method_min(degree_of_support_3 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_4 = 1.0 * (rule_connection_method_and(x_center , dir_north));
    if(degree_of_support_4 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_left(x);
            auto y = rule_activation_method_min(degree_of_support_4 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_5 = 1.0 * (rule_connection_method_and(x_center , dir_east));
    if(degree_of_support_5 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_right(x);
            auto y = rule_activation_method_min(degree_of_support_5 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_6 = 1.0 * (rule_connection_method_and(x_center , dir_west));
    if(degree_of_support_6 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_left(x);
            auto y = rule_activation_method_min(degree_of_support_6 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_7 = 1.0 * (rule_connection_method_and(x_right , dir_north));
    if(degree_of_support_7 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_left(x);
            auto y = rule_activation_method_min(degree_of_support_7 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_8 = 1.0 * (rule_connection_method_and(rule_connection_method_and(x_right , y_far) , dir_west));
    if(degree_of_support_8 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_left(x);
            auto y = rule_activation_method_min(degree_of_support_8 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_9 = 1.0 * (rule_connection_method_and(rule_connection_method_and(x_right , y_far) , dir_south));
    if(degree_of_support_9 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_right(x);
            auto y = rule_activation_method_min(degree_of_support_9 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

}

void FunctionBlockTruck::defuzzify() {
    auto sum_action = 0.0;
    auto wsum_action = 0.0;
    for (auto i = 0; i < 1000 ; i++) {
        auto x = -1.0 + i * 0.002;
        sum_action += defuzzify_action[i];
        wsum_action += x * defuzzify_action[i];
    }
    action = wsum_action / sum_action;
}

void FunctionBlockTruck::fuzzify() {
    dir_east = membership_dir_east(dir);
    dir_north = membership_dir_north(dir);
    dir_south = membership_dir_south(dir);
    dir_west = membership_dir_west(dir);
    x_center = membership_x_center(x);
    x_left = membership_x_left(x);
    x_right = membership_x_right(x);
    y_far = membership_y_far(y);
}

double FunctionBlockTruck::membership_action_left(double x) {
    if (x <= 0.0)    return 0.0;
    if (x > 1.0)    return 1.0;
    if (x <= 1.0)    return 0.0 + (1.0 - 0.0) * ((x - 0.0) / (1.0 - 0.0));
}

double FunctionBlockTruck::membership_action_right(double x) {
    if (x <= -1.0)    return 1.0;
    if (x > 0.0)    return 0.0;
    if (x <= 0.0)    return 1.0 + (0.0 - 1.0) * ((x - -1.0) / (0.0 - -1.0));
}

double FunctionBlockTruck::membership_dir_east(double x) {
    if (x <= 90.0)    return 0.0;
    if (x > 270.0)    return 0.0;
    if (x <= 180.0)    return 0.0 + (1.0 - 0.0) * ((x - 90.0) / (180.0 - 90.0));
    if (x <= 270.0)    return 1.0 + (0.0 - 1.0) * ((x - 180.0) / (270.0 - 180.0));
}

double FunctionBlockTruck::membership_dir_north(double x) {
    if (x <= 180.0)    return 0.0;
    if (x > 360.0)    return 0.0;
    if (x <= 270.0)    return 0.0 + (1.0 - 0.0) * ((x - 180.0) / (270.0 - 180.0));
    if (x <= 360.0)    return 1.0 + (0.0 - 1.0) * ((x - 270.0) / (360.0 - 270.0));
}

double FunctionBlockTruck::membership_dir_south(double x) {
    if (x <= 0.0)    return 0.0;
    if (x > 180.0)    return 0.0;
    if (x <= 90.0)    return 0.0 + (1.0 - 0.0) * ((x - 0.0) / (90.0 - 0.0));
    if (x <= 180.0)    return 1.0 + (0.0 - 1.0) * ((x - 90.0) / (180.0 - 90.0));
}

double FunctionBlockTruck::membership_dir_west(double x) {
    if (x <= 0.0)    return 1.0;
    if (x > 360.0)    return 1.0;
    if (x <= 90.0)    return 1.0 + (0.0 - 1.0) * ((x - 0.0) / (90.0 - 0.0));
    if (x <= 270.0)    return 0.0 + (0.0 - 0.0) * ((x - 90.0) / (270.0 - 90.0));
    if (x <= 360.0)    return 0.0 + (1.0 - 0.0) * ((x - 270.0) / (360.0 - 270.0));
}

double FunctionBlockTruck::membership_x_center(double x) {
    if (x <= 0.0)    return 0.0;
    if (x > 1.0)    return 0.0;
    if (x <= 0.5)    return 0.0 + (1.0 - 0.0) * ((x - 0.0) / (0.5 - 0.0));
    if (x <= 1.0)    return 1.0 + (0.0 - 1.0) * ((x - 0.5) / (1.0 - 0.5));
}

double FunctionBlockTruck::membership_x_left(double x) {
    if (x <= 0.0)    return 1.0;
    if (x > 0.5)    return 0.0;
    if (x <= 0.5)    return 1.0 + (0.0 - 1.0) * ((x - 0.0) / (0.5 - 0.0));
}

double FunctionBlockTruck::membership_x_right(double x) {
    if (x <= 0.5)    return 0.0;
    if (x > 1.0)    return 1.0;
    if (x <= 1.0)    return 0.0 + (1.0 - 0.0) * ((x - 0.5) / (1.0 - 0.5));
}

double FunctionBlockTruck::membership_y_far(double x) {
    if (x <= 0.0)    return 0.0;
    if (x > 1.0)    return 1.0;
    if (x <= 1.0)    return 0.0 + (1.0 - 0.0) * ((x - 0.0) / (1.0 - 0.0));
}


void FunctionBlockTruck::print() {
    printf("Function block truck:\n");
    printf("    Output %20s : %f\n", "action" , action);
    printf("    Input  %20s : %f\n", "dir" , dir);
    printf("           %20s : %f\n", "dir_east" , dir_east);
    printf("           %20s : %f\n", "dir_north" , dir_north);
    printf("           %20s : %f\n", "dir_south" , dir_south);
    printf("           %20s : %f\n", "dir_west" , dir_west);
    printf("    Input  %20s : %f\n", "x" , x);
    printf("           %20s : %f\n", "x_center" , x_center);
    printf("           %20s : %f\n", "x_left" , x_left);
    printf("           %20s : %f\n", "x_right" , x_right);
    printf("    Input  %20s : %f\n", "y" , y);
    printf("           %20s : %f\n", "y_far" , y_far);
}

void FunctionBlockTruck::reset() {
    for(int i=0 ; i < 1000 ; i++) {
    defuzzify_action[i] = 0.0;
}
}

}
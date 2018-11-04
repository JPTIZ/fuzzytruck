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
    auto degree_of_support_1 = 1.0 * (rule_connection_method_and(x_too_left , angle_left));
    if(degree_of_support_1 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = 0.0 + i * 0.03;
            auto membership = membership_action_turn_left(x);
            auto y = rule_activation_method_min(degree_of_support_1 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_2 = 1.0 * (rule_connection_method_and(x_centered , angle_vertical));
    if(degree_of_support_2 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = 0.0 + i * 0.03;
            auto membership = membership_action_turn_none(x);
            auto y = rule_activation_method_min(degree_of_support_2 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_3 = 1.0 * (rule_connection_method_and(x_too_right , angle_right));
    if(degree_of_support_3 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = 0.0 + i * 0.03;
            auto membership = membership_action_turn_right(x);
            auto y = rule_activation_method_min(degree_of_support_3 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

}

void FunctionBlockTruck::defuzzify() {
    auto sum_action = 0.0;
    auto wsum_action = 0.0;
    for (auto i = 0; i < 1000 ; i++) {
        auto x = 0.0 + i * 0.03;
        sum_action += defuzzify_action[i];
        wsum_action += x * defuzzify_action[i];
    }
    action = wsum_action / sum_action;
}

void FunctionBlockTruck::fuzzify() {
    angle_left = membership_angle_left(angle);
    angle_right = membership_angle_right(angle);
    angle_vertical = membership_angle_vertical(angle);
    x_centered = membership_x_centered(x);
    x_too_left = membership_x_too_left(x);
    x_too_right = membership_x_too_right(x);
    y_close = membership_y_close(y);
    y_really_close = membership_y_really_close(y);
    y_really_far = membership_y_really_far(y);
}

double FunctionBlockTruck::membership_action_turn_left(double x) {
    if (x <= 0.0)    return 0.0;
    if (x > 10.0)    return 0.0;
    if (x <= 5.0)    return 0.0 + (1.0 - 0.0) * ((x - 0.0) / (5.0 - 0.0));
    if (x <= 10.0)    return 1.0 + (0.0 - 1.0) * ((x - 5.0) / (10.0 - 5.0));
}

double FunctionBlockTruck::membership_action_turn_none(double x) {
    if (x <= 10.0)    return 0.0;
    if (x > 20.0)    return 0.0;
    if (x <= 15.0)    return 0.0 + (1.0 - 0.0) * ((x - 10.0) / (15.0 - 10.0));
    if (x <= 20.0)    return 1.0 + (0.0 - 1.0) * ((x - 15.0) / (20.0 - 15.0));
}

double FunctionBlockTruck::membership_action_turn_right(double x) {
    if (x <= 20.0)    return 0.0;
    if (x > 30.0)    return 0.0;
    if (x <= 25.0)    return 0.0 + (1.0 - 0.0) * ((x - 20.0) / (25.0 - 20.0));
    if (x <= 30.0)    return 1.0 + (0.0 - 1.0) * ((x - 25.0) / (30.0 - 25.0));
}

double FunctionBlockTruck::membership_angle_left(double x) {
    if (x <= 0.0)    return 1.0;
    if (x > 0.5)    return 0.0;
    if (x <= 0.5)    return 1.0 + (0.0 - 1.0) * ((x - 0.0) / (0.5 - 0.0));
}

double FunctionBlockTruck::membership_angle_right(double x) {
    if (x <= 0.5)    return 0.0;
    if (x > 1.0)    return 1.0;
    if (x <= 1.0)    return 0.0 + (1.0 - 0.0) * ((x - 0.5) / (1.0 - 0.5));
}

double FunctionBlockTruck::membership_angle_vertical(double x) {
    if (x <= 0.0)    return 0.0;
    if (x > 1.0)    return 0.0;
    if (x <= 0.5)    return 0.0 + (1.0 - 0.0) * ((x - 0.0) / (0.5 - 0.0));
    if (x <= 1.0)    return 1.0 + (0.0 - 1.0) * ((x - 0.5) / (1.0 - 0.5));
}

double FunctionBlockTruck::membership_x_centered(double x) {
    if (x <= 0.0)    return 0.0;
    if (x > 1.0)    return 0.0;
    if (x <= 0.5)    return 0.0 + (1.0 - 0.0) * ((x - 0.0) / (0.5 - 0.0));
    if (x <= 1.0)    return 1.0 + (0.0 - 1.0) * ((x - 0.5) / (1.0 - 0.5));
}

double FunctionBlockTruck::membership_x_too_left(double x) {
    if (x <= 0.0)    return 1.0;
    if (x > 0.5)    return 0.0;
    if (x <= 0.5)    return 1.0 + (0.0 - 1.0) * ((x - 0.0) / (0.5 - 0.0));
}

double FunctionBlockTruck::membership_x_too_right(double x) {
    if (x <= 0.5)    return 0.0;
    if (x > 1.0)    return 1.0;
    if (x <= 1.0)    return 0.0 + (1.0 - 0.0) * ((x - 0.5) / (1.0 - 0.5));
}

double FunctionBlockTruck::membership_y_close(double x) {
    if (x <= 0.0)    return 0.0;
    if (x > 1.0)    return 0.0;
    if (x <= 0.5)    return 0.0 + (1.0 - 0.0) * ((x - 0.0) / (0.5 - 0.0));
    if (x <= 1.0)    return 1.0 + (0.0 - 1.0) * ((x - 0.5) / (1.0 - 0.5));
}

double FunctionBlockTruck::membership_y_really_close(double x) {
    if (x <= 0.5)    return 0.0;
    if (x > 1.0)    return 1.0;
    if (x <= 1.0)    return 0.0 + (1.0 - 0.0) * ((x - 0.5) / (1.0 - 0.5));
}

double FunctionBlockTruck::membership_y_really_far(double x) {
    if (x <= 0.0)    return 1.0;
    if (x > 0.5)    return 0.0;
    if (x <= 0.5)    return 1.0 + (0.0 - 1.0) * ((x - 0.0) / (0.5 - 0.0));
}


void FunctionBlockTruck::print() {
    printf("Function block truck:\n");
    printf("    Output %20s : %f\n", "action" , action);
    printf("    Input  %20s : %f\n", "angle" , angle);
    printf("           %20s : %f\n", "angle_left" , angle_left);
    printf("           %20s : %f\n", "angle_right" , angle_right);
    printf("           %20s : %f\n", "angle_vertical" , angle_vertical);
    printf("    Input  %20s : %f\n", "x" , x);
    printf("           %20s : %f\n", "x_centered" , x_centered);
    printf("           %20s : %f\n", "x_too_left" , x_too_left);
    printf("           %20s : %f\n", "x_too_right" , x_too_right);
    printf("    Input  %20s : %f\n", "y" , y);
    printf("           %20s : %f\n", "y_close" , y_close);
    printf("           %20s : %f\n", "y_really_close" , y_really_close);
    printf("           %20s : %f\n", "y_really_far" , y_really_far);
}

void FunctionBlockTruck::reset() {
    for(int i=0 ; i < 1000 ; i++) {
    defuzzify_action[i] = 0.0;
}
}

}
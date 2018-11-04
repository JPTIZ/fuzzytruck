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
    auto degree_of_support_1 = 1.0 * (rule_connection_method_and(rule_connection_method_and(x_too_left , direction_southeast) , y_really_close));
    if(degree_of_support_1 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_right(x);
            auto y = rule_activation_method_min(degree_of_support_1 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_2 = 1.0 * (rule_connection_method_and(rule_connection_method_and(x_too_left , direction_southeast) , 1 -y_really_close));
    if(degree_of_support_2 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_none(x);
            auto y = rule_activation_method_min(degree_of_support_2 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_3 = 1.0 * (rule_connection_method_and(x_too_left , direction_south));
    if(degree_of_support_3 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_left(x);
            auto y = rule_activation_method_min(degree_of_support_3 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_4 = 1.0 * (rule_connection_method_and(x_too_left , direction_southwest));
    if(degree_of_support_4 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_left(x);
            auto y = rule_activation_method_min(degree_of_support_4 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_5 = 1.0 * (rule_connection_method_and(x_too_left , direction_west));
    if(degree_of_support_5 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_left(x);
            auto y = rule_activation_method_min(degree_of_support_5 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_6 = 1.0 * (rule_connection_method_and(x_too_left , direction_east));
    if(degree_of_support_6 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_right(x);
            auto y = rule_activation_method_min(degree_of_support_6 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_7 = 1.0 * (rule_connection_method_and(x_too_left , direction_northeast));
    if(degree_of_support_7 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_right(x);
            auto y = rule_activation_method_min(degree_of_support_7 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_8 = 1.0 * (rule_connection_method_and(x_too_left , direction_north));
    if(degree_of_support_8 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_right(x);
            auto y = rule_activation_method_min(degree_of_support_8 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_9 = 1.0 * (rule_connection_method_and(x_too_left , direction_northwest));
    if(degree_of_support_9 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_right(x);
            auto y = rule_activation_method_min(degree_of_support_9 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_10 = 1.0 * (rule_connection_method_and(x_centered , direction_south));
    if(degree_of_support_10 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_none(x);
            auto y = rule_activation_method_min(degree_of_support_10 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_11 = 1.0 * (rule_connection_method_and(x_centered , direction_southeast));
    if(degree_of_support_11 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_right(x);
            auto y = rule_activation_method_min(degree_of_support_11 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_12 = 1.0 * (rule_connection_method_and(x_centered , direction_southwest));
    if(degree_of_support_12 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_left(x);
            auto y = rule_activation_method_min(degree_of_support_12 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_21 = 1.0 * (rule_connection_method_and(x_too_right , direction_southeast));
    if(degree_of_support_21 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_right(x);
            auto y = rule_activation_method_min(degree_of_support_21 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_22 = 1.0 * (rule_connection_method_and(x_too_right , direction_south));
    if(degree_of_support_22 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_right(x);
            auto y = rule_activation_method_min(degree_of_support_22 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_23 = 1.0 * (rule_connection_method_and(rule_connection_method_and(x_too_right , direction_southwest) , y_really_close));
    if(degree_of_support_23 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_left(x);
            auto y = rule_activation_method_min(degree_of_support_23 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_24 = 1.0 * (rule_connection_method_and(rule_connection_method_and(x_too_right , direction_southwest) , 1 -y_really_close));
    if(degree_of_support_24 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_none(x);
            auto y = rule_activation_method_min(degree_of_support_24 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_26 = 1.0 * (rule_connection_method_and(x_too_right , direction_west));
    if(degree_of_support_26 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_right(x);
            auto y = rule_activation_method_min(degree_of_support_26 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_27 = 1.0 * (rule_connection_method_and(x_too_right , direction_east));
    if(degree_of_support_27 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_left(x);
            auto y = rule_activation_method_min(degree_of_support_27 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_28 = 1.0 * (rule_connection_method_and(x_too_right , direction_northeast));
    if(degree_of_support_28 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_left(x);
            auto y = rule_activation_method_min(degree_of_support_28 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_29 = 1.0 * (rule_connection_method_and(x_too_right , direction_north));
    if(degree_of_support_29 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_left(x);
            auto y = rule_activation_method_min(degree_of_support_29 , membership);
            defuzzify_action[i] += rule_accumulation_method_max(defuzzify_action[i], y);
        }
    }

    auto degree_of_support_30 = 1.0 * (rule_connection_method_and(x_too_right , direction_northwest));
    if(degree_of_support_30 > 0) {
        for (auto i = 0 ; i < 1000 ; i++) {
            auto x = -1.0 + i * 0.002;
            auto membership = membership_action_turn_left(x);
            auto y = rule_activation_method_min(degree_of_support_30 , membership);
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
    direction_east = membership_direction_east(direction);
    direction_north = membership_direction_north(direction);
    direction_northeast = membership_direction_northeast(direction);
    direction_northwest = membership_direction_northwest(direction);
    direction_south = membership_direction_south(direction);
    direction_southeast = membership_direction_southeast(direction);
    direction_southwest = membership_direction_southwest(direction);
    direction_west = membership_direction_west(direction);
    x_centered = membership_x_centered(x);
    x_too_left = membership_x_too_left(x);
    x_too_right = membership_x_too_right(x);
    y_close = membership_y_close(y);
    y_really_close = membership_y_really_close(y);
    y_really_far = membership_y_really_far(y);
}

double FunctionBlockTruck::membership_action_turn_left(double x) {
    if (x <= 0.0)    return 0.0;
    if (x > 1.0)    return 1.0;
    if (x <= 1.0)    return 0.0 + (1.0 - 0.0) * ((x - 0.0) / (1.0 - 0.0));
}

double FunctionBlockTruck::membership_action_turn_none(double x) {
    if (x <= -1.0)    return 0.0;
    if (x > 1.0)    return 0.0;
    if (x <= 0.0)    return 0.0 + (1.0 - 0.0) * ((x - -1.0) / (0.0 - -1.0));
    if (x <= 1.0)    return 1.0 + (0.0 - 1.0) * ((x - 0.0) / (1.0 - 0.0));
}

double FunctionBlockTruck::membership_action_turn_right(double x) {
    if (x <= -1.0)    return 1.0;
    if (x > 0.0)    return 0.0;
    if (x <= 0.0)    return 1.0 + (0.0 - 1.0) * ((x - -1.0) / (0.0 - -1.0));
}

double FunctionBlockTruck::membership_direction_east(double x) {
    if (x <= 160.0)    return 0.0;
    if (x > 200.0)    return 0.0;
    if (x <= 180.0)    return 0.0 + (1.0 - 0.0) * ((x - 160.0) / (180.0 - 160.0));
    if (x <= 200.0)    return 1.0 + (0.0 - 1.0) * ((x - 180.0) / (200.0 - 180.0));
}

double FunctionBlockTruck::membership_direction_north(double x) {
    if (x <= 269.0)    return 0.0;
    if (x > 271.0)    return 0.0;
    if (x <= 270.0)    return 0.0 + (1.0 - 0.0) * ((x - 269.0) / (270.0 - 269.0));
    if (x <= 271.0)    return 1.0 + (0.0 - 1.0) * ((x - 270.0) / (271.0 - 270.0));
}

double FunctionBlockTruck::membership_direction_northeast(double x) {
    if (x <= 180.0)    return 0.0;
    if (x > 270.0)    return 0.0;
    if (x <= 181.0)    return 0.0 + (1.0 - 0.0) * ((x - 180.0) / (181.0 - 180.0));
    if (x <= 269.0)    return 1.0 + (1.0 - 1.0) * ((x - 181.0) / (269.0 - 181.0));
    if (x <= 270.0)    return 1.0 + (0.0 - 1.0) * ((x - 269.0) / (270.0 - 269.0));
}

double FunctionBlockTruck::membership_direction_northwest(double x) {
    if (x <= 270.0)    return 0.0;
    if (x > 360.0)    return 0.0;
    if (x <= 271.0)    return 0.0 + (1.0 - 0.0) * ((x - 270.0) / (271.0 - 270.0));
    if (x <= 359.0)    return 1.0 + (1.0 - 1.0) * ((x - 271.0) / (359.0 - 271.0));
    if (x <= 360.0)    return 1.0 + (0.0 - 1.0) * ((x - 359.0) / (360.0 - 359.0));
}

double FunctionBlockTruck::membership_direction_south(double x) {
    if (x <= 89.0)    return 0.0;
    if (x > 91.0)    return 0.0;
    if (x <= 90.0)    return 0.0 + (1.0 - 0.0) * ((x - 89.0) / (90.0 - 89.0));
    if (x <= 91.0)    return 1.0 + (0.0 - 1.0) * ((x - 90.0) / (91.0 - 90.0));
}

double FunctionBlockTruck::membership_direction_southeast(double x) {
    if (x <= 90.0)    return 0.0;
    if (x > 180.0)    return 0.0;
    if (x <= 110.0)    return 0.0 + (1.0 - 0.0) * ((x - 90.0) / (110.0 - 90.0));
    if (x <= 160.0)    return 1.0 + (1.0 - 1.0) * ((x - 110.0) / (160.0 - 110.0));
    if (x <= 180.0)    return 1.0 + (0.0 - 1.0) * ((x - 160.0) / (180.0 - 160.0));
}

double FunctionBlockTruck::membership_direction_southwest(double x) {
    if (x <= 0.0)    return 0.0;
    if (x > 90.0)    return 0.0;
    if (x <= 20.0)    return 0.0 + (1.0 - 0.0) * ((x - 0.0) / (20.0 - 0.0));
    if (x <= 70.0)    return 1.0 + (1.0 - 1.0) * ((x - 20.0) / (70.0 - 20.0));
    if (x <= 90.0)    return 1.0 + (0.0 - 1.0) * ((x - 70.0) / (90.0 - 70.0));
}

double FunctionBlockTruck::membership_direction_west(double x) {
    if (x <= 0.0)    return 1.0;
    if (x > 360.0)    return 1.0;
    if (x <= 20.0)    return 1.0 + (0.0 - 1.0) * ((x - 0.0) / (20.0 - 0.0));
    if (x <= 340.0)    return 0.0 + (0.0 - 0.0) * ((x - 20.0) / (340.0 - 20.0));
    if (x <= 360.0)    return 0.0 + (1.0 - 0.0) * ((x - 340.0) / (360.0 - 340.0));
}

double FunctionBlockTruck::membership_x_centered(double x) {
    if (x <= 0.4)    return 0.0;
    if (x > 0.6)    return 0.0;
    if (x <= 0.5)    return 0.0 + (1.0 - 0.0) * ((x - 0.4) / (0.5 - 0.4));
    if (x <= 0.6)    return 1.0 + (0.0 - 1.0) * ((x - 0.5) / (0.6 - 0.5));
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
    printf("    Input  %20s : %f\n", "direction" , direction);
    printf("           %20s : %f\n", "direction_east" , direction_east);
    printf("           %20s : %f\n", "direction_north" , direction_north);
    printf("           %20s : %f\n", "direction_northeast" , direction_northeast);
    printf("           %20s : %f\n", "direction_northwest" , direction_northwest);
    printf("           %20s : %f\n", "direction_south" , direction_south);
    printf("           %20s : %f\n", "direction_southeast" , direction_southeast);
    printf("           %20s : %f\n", "direction_southwest" , direction_southwest);
    printf("           %20s : %f\n", "direction_west" , direction_west);
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
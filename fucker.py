STUB = '''
function_block truck

var_input
    x: real;
    y: real;
    dir: real;
end_var

var_output
    action: real;
end_var

fuzzify x
    term left   := (0.0, 1) (0.5, 0);
    term center := (0.0, 0) (0.5, 1) (1.0, 0);
    term right  := (0.5, 0) (1, 1);
end_fuzzify

fuzzify y
    term far   := (0.0, 0) (1.00, 1);
    // term not far := (0.33, 0) (1.0, 1);
end_fuzzify

fuzzify dir
    term west      := (  0, 1) ( 90, 0) (270, 0) (360, 1);

    term south     := (  0, 0) ( 90, 1) (180, 0);

    term east      := ( 90, 0) (180, 1) (270, 0);

    term north     := (180, 0) (270, 1) (360, 0);

    // term really_south := ( 80, 0) ( 90, 1) (100, 0);
end_fuzzify

defuzzify action
    term left  := (-1, 1) (0, 0);
    term none  := (-1, 0) (0, 1) (1, 0);
    term right :=         (0, 0) (1, 1);

    method: cog;
    default := 0;
end_defuzzify

ruleblock truck_rules
    and: min;
    act: min;
    accu: max;


'''


THE_END = '''
end_ruleblock

end_function_block
'''


from typing import NamedTuple


class Rule(NamedTuple):
    x: str = None
    y: str = None
    dir: str = None
    action: str = None


if __name__ == '__main__':
    rules = [
        # Rule(x='left',  dir='south',  action='right'),
        # Rule(x='right',   dir='north',  action='right'),

        Rule(x='left',    dir='north',  action='left'),
        Rule(x='right',   dir='north',  action='right'),
        Rule(x='center',  dir='east',   action='left'),
        Rule(x='center',  dir='west',   action='right'),
        Rule(x='center',  dir='north',  action='right'),

        Rule(x='left',    dir='south',  y='far',          action='right'),
        Rule(x='left',    dir='east',   y='far',          action='left'),
        Rule(x='right',   dir='south',  y='far',          action='left'),
        Rule(x='right',   dir='west',   y='far',          action='right'),
    ]

    contents = STUB
    for i, (x, y, dir, action) in enumerate(rules):
        cond = ''
        if x is not None:
            if cond:
                cond += ' and '
            cond += f' x is {x} '
        if y is not None:
            if cond:
                cond += ' and '
            cond += f' y is {y} '
        if dir is not None:
            if cond:
                cond += ' and '
            cond += f' dir is {dir} '
        contents += f'\n    rule {i+1}: if {cond} then action is {action} '
    contents += THE_END
    with open('truck.fcl', 'w') as f:
        f.write(contents)

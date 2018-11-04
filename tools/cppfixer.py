'''
Module for separating .cpp definitions into .h + .cpp and applies some styling.
Not meant to be beautiful, just functional.
'''
import re

from sys import argv


def remove_comments(contents: str, output: str = ''):
    return '\n'.join(
        line for line in contents.split('\n')
        if not re.search('^[ \t]*//', line)
    ).strip()


def uncamel(contents: str, output: str = ''):
    def _uncamel(match):
        a, b = match.group(1), match.group(2)
        return f'{a}_{b.lower()}'

    return re.sub(
        r'([a-z])([A-Z])',
        _uncamel,
        contents
    )


def camel_classes(contents: str, output: str = ''):
    classes = []

    def camelit(match):
        classname = match.group(1)
        camelled = re.sub(
            r'_([a-z])',
            lambda match: match.group(1).upper(),
            classname
        )

        classes.append((classname, camelled))

        return f'class {camelled}'

    contents = re.sub(
        r'class ([\w]+)',
        camelit,
        contents
    )

    for classname, camelled in classes:
        contents = re.sub(f'{classname}', f'{camelled}', contents)

    return contents


def extract_classes(contents: str, output: str = ''):
    classes = []

    # I am sure I have a purpose when declaring these outside a simple for loop
    lines = contents.splitlines()
    i = 0
    start = None
    while i < len(lines):
        line = lines[i]

        if line.startswith('class'):
            start = i
        elif line == '};' and start is not None:
            classes.append('\n'.join(lines[start:i + 1]))
            lines = lines[:start] + lines[i + 1:]
            i, start = start, None

        i += 1

    return (classes, '\n'.join(lines))


def organize_includes(contents: str, output: str):
    includes = []
    lines = contents.splitlines()
    i = 0
    while i < len(lines):
        line = lines[i]

        if line.startswith('#include'):
            includes += [line]
            lines = lines[:i] + lines[i + 1:]

        i += 1

    includes = '\n'.join(includes + [f'#include "{output.split("/")[-1]}.h"'])

    for i, line in enumerate(lines):
        if line.strip():
            lines = lines[i:]
            break

    lines = '\n'.join(lines).strip()

    return f'{includes}\n\n{lines}'


def remove_main(contents: str, output: str = ''):
    lines = contents.splitlines()
    for i, line in enumerate(lines):
        if line.startswith('int main'):
            return '\n'.join(lines[:i])


def fix_spaces(contents: str, output: str = ''):
    replaces = [
        ('\( ', '('),
        (' \)', ')'),
        (r'return \((.+)\);', lambda m: f'return {m.group(1)};'),
        ('\t{ (.+) }',
         lambda m: (
             ' {\n'
             f'    {m.group(1)}'
             '\n}'
         )),
        ('\t', '    '),
    ]

    for pat, replace in replaces:
        contents = re.sub(pat, replace, contents)

    return contents


def use_auto(contents: str, output: str = ''):
    return re.sub(r'\w+ (\w+) = (.*);',
                  lambda m: f'auto {m.group(1)} = {m.group(2)};',
                  contents)


def insert_namespace(contents: str, output: str = ''):
    lines = contents.splitlines()

    for i, line in enumerate(lines):
        if not line.startswith('#include'):
            return '\n'.join(
                lines[:i]
                + ['\nnamespace fuzzytruck {\n']
                + lines[i:]
                + ['\n}']
            )


if __name__ == '__main__':
    try:
        filename = argv[1]
        output = argv[2]
    except IndexError:
        print(f'Usage: {argv[0]} <filename> <output-base>')
        exit(1)

    with open(filename) as f:
        contents = f.read()

    operations = [
        remove_comments,
        organize_includes,
        uncamel,
        camel_classes,
        remove_main,
        fix_spaces,
        use_auto,
        insert_namespace,
    ]

    for operation in operations:
        contents = operation(contents, output)

    classes, contents = extract_classes(contents)

    with open(f'{output}.cpp', 'w') as f:
        f.write(contents)

    with open(f'{output}.h', 'w') as f:
        welp = '\n'.join(classes)
        tag = (
            f'{filename}_{output}_H'
            .upper()
            .replace('.', '_')
            .replace('/', '_')
        )
        f.write(
            f'#ifndef {tag}\n'
            f'#define {tag}\n'
            '\nnamespace fuzzytruck {\n'
            f'\n{welp}\n'
            '\n}\n\n#endif'
        )

import re

from sys import argv


def remove_comments(contents: str):
    return '\n'.join(
        line for line in contents.split('\n')
        if not re.search('^[ \t]*//', line)
    ).strip()


def uncamel(contents: str):
    print('Uncamelling...')

    def _uncamel(match):
        a, b = match.group(1), match.group(2)
        return f'{a}_{b.lower()}'

    return re.sub(
        r'([a-z])([A-Z])',
        _uncamel,
        contents
    )


def camel_classes(contents: str):
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


if __name__ == '__main__':
    try:
        filename = argv[1]
        output = argv[2]
    except IndexError:
        print(f'Usage: {argv[0]} <filename> <output-base>')
        exit(1)

    with open(filename) as f:
        contents = f.read()

    contents = camel_classes(remove_comments(uncamel(contents)))

    with open(f'{output}.cpp', 'w') as f:
        f.write(contents)

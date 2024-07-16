#!/usr/bin/env python3

import argparse
import os
import re
from enum import Enum


class Lang(Enum):
    CPP = 'c++'
    PYTHON = 'python'
    BASH = 'bash'
    JAVA = 'java'
    RAW = ''

COMMENTS = [
    ('/**', ' */'),
    (""", """),
    (''', '''),
]

def get_lang(lang: str) -> Lang:
    lang = lang.lower()
    if lang in ('h', 'c', 'c++', 'cpp', 'cc', 'hpp'):
        return Lang.CPP
    elif lang in ('py'):
        return Lang.PYTHON
    elif lang in ('sh', 'bash'):
        return Lang.BASH
    elif lang in ('java'):
        return Lang.JAVA
    return Lang.RAW

def escape_file_name(file_name: str) -> str:
    file_name = file_name.replace('\\', r'\\')
    file_name = file_name.replace('_', r'\_')
    return file_name

def escape_special_symbols(text: str) -> str:
    text = text.replace('<', r'\ensuremath{<}')
    text = text.replace('>', r'\ensuremath{>}')
    return text

def wrap_big_o_notation(text: str) -> str:
    n = len(text)
    i = 0
    while i < n:
        if text[i] == 'O' and i + 1 < n and text[i + 1] == '(':
            j = i + 1
            balance = 0
            while j < n:
                if text[j] == '(':
                    balance += 1
                elif text[j] == ')':
                    balance -= 1

                if balance == 0:
                    break
                j += 1

            if balance == 0:
                assert j < n and text[j] == ')'
                big_o = r'\mathcal{O}' + text[i + 1:j + 1]
                text = text[:i] + big_o + text[j + 1:]
            i = j
        i += 1

    return text

def process_file(input: str, output: str, lang: Lang) -> None:
    known_categories = [
        'Description', 'Note', 'Usage', 'Time', 'Space', 'Source', 'Status',
        'Tested', 'Author', 'License', 'Date',
    ]
    basename = os.path.basename(input)
    os.makedirs(os.path.dirname(output), exist_ok=True)
    with open(input, 'r', encoding='utf8') as f:
        source = f.readlines()
    source = [line.rstrip() for line in source]
    comment_start = None
    comment_end_str = None
    for comment in COMMENTS:
        for i, line in enumerate(source):
            if line == comment[0] and (comment_start is None or comment_start > i):
                comment_start = i
                comment_end_str = comment[1]
                break

    categories: dict[str, list[str]] = {}
    errors: list[str] = []
    if comment_start is not None:
        idx = comment_start
        prev_category = None
        while idx < len(source):
            line = source[idx]
            if line == comment_end_str:
                idx += 1
                break
            line = re.sub(r'^[*\s]*', '', line)
            colon_idx = line.find(':')
            if colon_idx != -1 and line[0].isupper() and line[:colon_idx].isalpha():
                cat = line[:colon_idx]
                if cat not in known_categories:
                    errors.append(f'Unknown category "{cat}" in {input}')
                prev_category = cat
                value = line[len(cat) + 1:].lstrip()
                categories[cat] = [value]
            else:
                if prev_category is not None:
                    categories[prev_category].append(line)
            idx += 1

        # wrap items (i.e. start with - or +) with list
        for category, lines in categories.items():
            new_lines = []
            i = 0
            while i < len(lines):
                line = lines[i]
                if line.startswith(('-', '+')):
                    items = []
                    items.append(r'\begin{usagelist}')
                    while i < len(lines) and lines[i].startswith(('-', '+')):
                        cur_line = lines[i]
                        cur_line = cur_line[1:].lstrip()
                        items.append(rf'\item {cur_line}')
                        i += 1
                    items.append(r'\end{usagelist}')
                    new_lines.append('\n'.join(items))
                else:
                    new_lines.append(line)
                i += 1

            categories[category] = new_lines

        source = source[idx:]

    if errors:
        output_content = [r'\negzeroerror{%s}' % '. '.join(errors)]
    else:
        output_content = []
        source = strip_empty_lines(source)

        # remove empty string
        for category in categories:
            categories[category] = [line for line in categories[category] if line]

        categories = {k: ' '.join(v) for k, v in categories.items()}

        if 'Description' in categories:
            output_content.append(r'\defdesc{%s}' % escape_special_symbols(categories['Description']))
        if 'Note' in categories:
            output_content.append(r'\defnote{%s}' % escape_special_symbols(categories['Note']))
        if 'Usage' in categories:
            output_content.append(r'\defusage{%s}' % escape_special_symbols(categories['Usage']))
        if 'Time' in categories:
            output_content.append(r'\deftime{%s}' % wrap_big_o_notation(escape_special_symbols(categories['Time'])))
        if 'Space' in categories:
            output_content.append(r'\defspace{%s}' % wrap_big_o_notation(escape_special_symbols(categories['Space'])))
        output_content.append(r'\deffilemetadata{%s, %s lines}' % (escape_file_name(basename), len(source)))
        output_content.append(r'\begin{lstlisting}[caption=%s, language=%s]' % (escape_file_name(basename), lang.value))
        output_content.extend(source)
        output_content.append(r'\end{lstlisting}')
    with open(output, 'w', encoding='utf8') as f:
        f.write('\n'.join(output_content))

def add_opts(parser: argparse.ArgumentParser) -> None:
    parser.add_argument(
        'input',
        help='Path to the input file',
        type=str,
    )
    parser.add_argument(
        '-o',
        '--output',
        help='Path to the output file',
        type=str,
        default='./header.tmp'
    )
    parser.add_argument(
        '-l',
        '--lang',
        help='Language of the input file',
        type=str,
    )

def strip_empty_lines(lines: list[str], strip_left: bool = True, strip_right: bool = True) -> list[str]:
    length = len(lines)
    if length == 0:
        return lines
    if strip_left:
        pos = 0
        while pos < length and lines[pos] == '':
            pos += 1
        lines = lines[pos:]
    if strip_right:
        pos = len(lines) - 1
        while pos >= 0 and lines[pos] == '':
            pos -= 1
        lines = lines[:pos + 1]
    return lines

def main():
    parser = argparse.ArgumentParser(
        description='Preprocess header files before including in .tex file',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    add_opts(parser)
    args = parser.parse_args()

    if not os.path.isfile(args.input):
        raise FileNotFoundError(f'Input file not found: {args.input}')
    if args.lang is None:
        ext = os.path.splitext(args.input)[1]
        ext = ext[1:]
        args.lang = ext
    lang = get_lang(args.lang)
    process_file(args.input, args.output, lang)


if __name__ == '__main__':
    main()

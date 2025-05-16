import os
import re

def extract_define_targets(filepath):
    with open(filepath, 'r') as file:
        lines = file.readlines()

    result = set()

    for line in lines:
        stripped = line.strip()

        match = re.match(r"#define\s+(\w+)\s+(\w+)", stripped)
        if match:
            var, value = match.groups()
            if var in {"OUTPUT0", "OUTPUT1", "OUTPUT2"}:
                result.add(value)
            else:
                result.add(var)

    return sorted(result)

def find_stm8s_includes_with_conditions(codebase_path, interested_vars = set()):
    matched_includes = list()

    # Patterns
    include_pattern = re.compile(r'#include\s+[<"]([^">]*stm8s_[^">]*)[">]')
    ifdef_pattern = re.compile(r'#\s*ifdef\s+(\w+)')
    ifndef_pattern = re.compile(r'#\s*ifndef\s+(\w+)')
    if_pattern = re.compile(r'#\s*(if|elif)\s+(.*)')
    else_pattern = re.compile(r'#\s*else')
    endif_pattern = re.compile(r'#\s*endif')

    def expression_mentions_var(expr, vars_to_check):
        # Remove parentheses and split on logical operators
        tokens = re.split(r'\|\||&&|[() \t]+', expr)
        return any(var in tokens for var in vars_to_check)

    for root, _, files in os.walk(codebase_path):
        for file in files:
            if file.endswith(('.c', '.cpp', '.h', '.hpp')):
                filepath = os.path.join(root, file)
                try:
                    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                        condition_stack = []

                        for i, line in enumerate(f, 1):
                            stripped = line.strip()

                            # Handle #ifdef / #ifndef
                            if (m := ifdef_pattern.match(stripped)):
                                condition_stack.append(('ifdef', m.group(1)))
                                continue
                            if (m := ifndef_pattern.match(stripped)):
                                condition_stack.append(('ifndef', m.group(1)))
                                continue

                            # Handle #if / #elif
                            if (m := if_pattern.match(stripped)):
                                expr = m.group(2)
                                mentions = expression_mentions_var(expr, interested_vars)
                                condition_stack.append(('if', expr if mentions else None))
                                continue

                            # Handle #else
                            if else_pattern.match(stripped):
                                if condition_stack:
                                    kind, val = condition_stack.pop()
                                    flipped = None
                                    if kind in ('ifdef', 'ifndef'):
                                        flipped = ('ifndef' if kind == 'ifdef' else 'ifdef', val)
                                    elif kind == 'if':
                                        flipped = ('if', None if val else None)
                                    if flipped:
                                        condition_stack.append(flipped)
                                continue

                            # Handle #endif
                            if endif_pattern.match(stripped):
                                if condition_stack:
                                    condition_stack.pop()
                                continue

                            # Handle #include "stm8s_..."
                            if (m := include_pattern.search(stripped)):
                                include_entry = (filepath, i, m.group(1))

                                if not condition_stack:
                                    matched_includes.append(include_entry)
                                elif any(
                                    (kind == 'ifdef' and val in interested_vars) or
                                    (kind == 'if' and val is not None)
                                    for kind, val in condition_stack
                                ):
                                    matched_includes.append(include_entry)

                except Exception as e:
                    print(f"Could not read file {filepath}: {e}")
    
    includes = list()

    for filepath, line, include in matched_includes:
        includes.append(str(include))

    return includes

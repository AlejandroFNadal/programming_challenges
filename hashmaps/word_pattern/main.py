def wordPattern(pattern: str, s: str) -> bool:
    """
    Here the goal was to match pattern to a string. For ex:

    abba -> dog cat cat dog
    abba -> dog cat cat fish
    aaaa -> dog cat cat dog : False
    My solution was to use a dict to check that each pattern maps to an unique word. Before doing that, I convert
    the pattern and the string to a set and I can compare lengths. I thought I was being clever by doing this, but
    there was a better solution:
        return (len(set(pattern)) ==
                    len(set(s)) ==
                    len(set(zip_longest(pattern,s))))
        This one was not mine, but it is amazing. zip longest combines the tuples creating a new list, and then if you apply a set,
        you get all the unique ones. If the length is not the same than the amount of elements in the pattern, you have words that
        were repeated Same with counting the elements of the string.
        Anyway, my solution is also N and you dont need 5 minutes to understand it, so I stick with it.
    """
    tokens = s.split(" ")
    src_map = {}
    # hopefully weed out quite a few here
    if len(tokens) != len(pattern):
        return False
    if len(set(tokens)) != len(set(pattern)):
        return False
    i = 0
    for pat in pattern:
        if pat not in src_map:
            src_map[pat] = tokens[i]
        else:
            if tokens[i] != src_map[pat]:
                return False
        i += 1
    return True

def recurs(el: str):
    if el == '+':
        return recurs(tokens.pop()) + recurs(tokens.pop())
    elif el == '-':
        b = recurs(tokens.pop())
        a = recurs(tokens.pop())
        return a - b
    elif el == "*":
        return recurs(tokens.pop()) * recurs(tokens.pop())
    elif el == "/":
        b = recurs(tokens.pop())
        a = recurs(tokens.pop())
        return  round(int(a / b))
    else:
        return int(el)

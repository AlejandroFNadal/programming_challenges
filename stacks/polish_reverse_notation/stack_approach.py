def evalRPN(self, tokens: List[str]) -> int:
        stack = []
        while tokens:
            val = tokens.pop(0)
            if val in ["+", "-", "*", "/"]:
                a = int(stack.pop())
                b = int(stack.pop())
            if val == "+":
                stack.append(a + b)
            elif val == "-":
                stack.append(b - a)
            elif val == "*":
                stack.append(a * b)
            elif val == "/":
                c = int(b/a)
                stack.append(c)
            else:
                stack.append(int(val))
        return stack[0]

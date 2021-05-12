import StackClass


def T_A_C(exp):
    stack = []
    x = 1
    # an instance of the StackClass module
    obj = StackClass.Conversion(len(exp))
    # an instance that converts a given infix notation to post fix
    postfix = obj.infixToPostfix(exp)
    for i in postfix:
        if i in "abcdefghijklmnopqrstuvwxyz" or i in "0123456789":
            stack.append(i)
        elif i == '-':
            op1 = stack.pop()
            print("t(", x, ")", "=", i, op1)
            stack.append("t(%s)" % x)
            x = x + 1
            if stack != []:
                op2 = stack.pop()
                op1 = stack.pop()
                print("t(", x, ")", "=", op1, "+", op2)
                stack.append("t(%s)" % x)
                x = x + 1
        elif i == '=':
            op2 = stack.pop()
            op1 = stack.pop()
            print(op1, i, op2)

        else:
            op1 = stack.pop()
            if stack != []:
                op2 = stack.pop()
                print("t(", x, ")", "=", op2, i, op1)
                stack.append("t(%s)" % x)
                x = x + 1


def Quadruple(exp):
    stack = []
    op = []
    x = 1
    # an instance of the StackClass module
    obj = StackClass.Conversion(len(exp))
    # an instance that converts a given infix notation to post fix
    postfix = obj.infixToPostfix(exp)
    print("{0:^4s} | {1:^4s} | {2:^4s}|{3:4s}".format('op', 'arg1', 'arg2', 'result'))
    for i in postfix:
        if i in "abcdefghijklmnopqrstuvwxyz" or i in "0123456789":
            stack.append(i)
        elif i == '-':
            op1 = stack.pop()
            stack.append("t(%s)" % x)
            print("{0:^4s} | {1:^4s} | {2:^4s}|{3:4s}".format(i, op1, "(-)", " t(%s)" % x))
            x = x + 1
            if stack != []:
                op2 = stack.pop()
                op1 = stack.pop()
                print("{0:^4s} | {1:^4s} | {2:^4s}|{3:4s}".format("+", op1, op2, " t(%s)" % x))
                stack.append("t(%s)" % x)
                x = x + 1
        elif i == '=':
            op2 = stack.pop()
            op1 = stack.pop()
            print("{0:^4s} | {1:^4s} | {2:^4s}|{3:4s}".format(i, op2, "(-)", op1))
        else:
            op1 = stack.pop()
            op2 = stack.pop()
            print("{0:^4s} | {1:^4s} | {2:^4s}|{3:4s}".format(i, op2, op1, " t(%s)" % x))
            stack.append("t(%s)" % x)
            x = x + 1


def Triple(exp):
    stack = []
    op = []
    x = 0
    # an instance of the StackClass module
    obj = StackClass.Conversion(len(exp))
    # an instance that converts a given infix notation to postfix
    postfix = obj.infixToPostfix(exp)
    print("{0:^4s} | {1:^4s} | {2:^4s}".format('op', 'arg1', 'arg2'))
    for i in postfix:
        if i in "abcdefghijklmnopqrstuvwxyz" or i in "0123456789":
            stack.append(i)
        elif i == '-':
            op1 = stack.pop()
            stack.append("(%s)" % x)
            print("{0:^4s} | {1:^4s} | {2:^4s}".format(i, op1, "(-)"))
            x = x + 1
            if stack != []:
                op2 = stack.pop()
                op1 = stack.pop()
                print("{0:^4s} | {1:^4s} | {2:^4s}".format("+", op1, op2))
                stack.append("(%s)" % x)
                x = x + 1
        elif i == '=':
            op2 = stack.pop()
            op1 = stack.pop()
            print("{0:^4s} | {1:^4s} | {2:^4s}".format(i, op1, op2))
        else:
            op1 = stack.pop()
            if stack != []:
                op2 = stack.pop()
                print("{0:^4s} | {1:^4s} | {2:^4s}".format(i, op2, op1))
                stack.append("(%s)" % x)
                x = x + 1


exp = input("Enter a valid infix expression:")
print("Three Address Code")
print("--------------------------")
T_A_C(exp)
print("Quadruple Representation")
print("--------------------------")
Quadruple(exp)
print("Triple Representation")
print("--------------------------")
Triple(exp)

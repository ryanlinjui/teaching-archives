def add(x, y):
    return x + y

def divide(x, y):
    if y == 0:
        raise ValueError("Cannot divide by zero")
    return x / y

# ============================================
# 請在下方區塊新增你們自訂的運算子函數定義
# 例如小組 A 可新增其它運算子：
#   '-': subtract
#   '*': multiply
#   '/': divide
# ============================================

operators = {
    '+': add
    '/':divide
}

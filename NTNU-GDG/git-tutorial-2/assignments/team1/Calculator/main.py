import operator

def main():
    # 顯示目前支援的運算子
    supported_ops = ", ".join(operator.operators.keys())
    print(f"目前支援的運算子：{supported_ops}")
    
    try:
        x = float(input("請輸入第一個數字: "))
        y = float(input("請輸入第二個數字: "))
    except ValueError:
        print("請輸入有效的數字")
        return

    op = input("請輸入運算子： ")
    
    if op in operator.operators:
        result = operator.operators[op](x, y)
        print("結果:", result)
    else:
        print("不支援的運算子！")

if __name__ == "__main__":
    main()

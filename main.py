def add(i1, i2, b):
    bigger = max(i1, i2)
    smaller = min(i1, i2)

    carry = 0
    number = []

    while bigger > 0 :
        digit = bigger % b + smaller % b + carry
        carry = digit // b
        number.append(digit % b)

        bigger = bigger // b
        smaller = smaller // b

    if carry > 0 :
        number.append(carry)

    sum = 0
    i=0

    for digit in number:
        sum += digit*pow(10,i)
        i += 1

    return sum

def split_number(n, k):
    high = n // 10**k
    low = n % 10**k
    return low, high

def multiply(i1, i2, b):

    if i1 < 10 :
        return i1 * i2 # base case
    
    n = max(len(str(i1)), len(str(i2)))
    k = n // 2
    

    a0, a1 = split_number(i1, k) 
    b0, b1 = split_number(i2, k)

    x1 = multiply(a0, b0, b)
    x3 = multiply(a1, b1, b)
    x2 = multiply((a0+a1),(b0+b1), b) - x1 - x3

    return x3 * (pow(b, 2*k)) + x2 * (pow(b,k)) + x1

def divide(i1, i2, b):
    return 0 # im undergrad :)

def decimal_to_base(num, base):
    if num == 0:
        return "0"
    
    digits = "0123456789"
    result = ""

    while num > 0:
        result = digits[num % base] + result
        num = num // base

    return result

def main():
    i1_str, i2_str, b_str = input().split()

    b = int(b_str)
    i1 = int(i1_str, b)
    i2 = int(i2_str, b)

    sum = add(i1, i2, 10)
    product = multiply(i1, i2, 10)
    ratio = divide(i1, i2, 10)

    print(f"{decimal_to_base(sum,b)} {decimal_to_base(product,b)} {ratio}")

if __name__ == "__main__":
    main()
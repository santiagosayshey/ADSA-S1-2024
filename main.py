def main():
    print('Enter three integers: "I1 I2 B" where I1 and I2 are integers (up to 100 digits) and B is the base of the two integers (from 2 to 10)')
    i1, i2, b = input().split()

    addition = add(i1, i2, b)

    print('sum is ', addition)

def add(i1, i2, b):
    bigger = max(int(i1), int(i2))
    smaller = min(int(i1), int(i2))
    b = int(b)

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
        sum += digit*pow(b,i)
        i += 1

    return sum



def multiply(i1, i2, b):
    pass


def divide(i1, i2, b):
    return 0 # im undegrad :)

def pad_number(smaller, larger):
    # Prepend zeros to the smaller number
    return smaller.zfill(len(larger))

if __name__ == "__main__":
    main()
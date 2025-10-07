def Euclides(A,B):
    r = (A % B)
    if r == 0:
        return B
    return Euclides(B, r)
    
def main():
    print("Calcule o mdc de:")
    n1 = int(input("NUMERO 1: "))
    n2 = int(input("NUMERO 2: "))
    if n1 >= n2:
        print(f"O mdc({n1},{n2}): {Euclides(n1,n2)}")
    else:
        print(f"O mdc({n2},{n1}): {Euclides(n2,n1)}")
    
if __name__ == '__main__':
    main()
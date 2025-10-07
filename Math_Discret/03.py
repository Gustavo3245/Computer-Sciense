

def fibonacci2(n):
    fib = [1, 1]
    while len(fib) < n:
        fib.append(fib[-1] + fib[-2])

    return fib[n-1]  

def main():
    n = int(input("Digite o valor da sequencia de fibonacci: "))
    
    for i in range(1,n+1):
        print(f"x:{i}|y:{fibonacci2(i)}")
        
if __name__ == '__main__':
    main()
    
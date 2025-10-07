def input_positivo_nulo(msg):
    n = int(input(msg))
    if n >= 0:
        return n
    while n < 0:
        n = int(input("Não são aceitos numeros negativos. Tente novamente: "))

def exemplo03(n):
    resultado = 0
    for i in range(1,n+1):
        resultado += i**2
    return resultado

def verificar03(n):
    resultado = exemplo03(n)
    if resultado == (n * (n + 1) * ((2 * n) + 1)) / 6:
        return True
    return False

print("Exemplo 03:")
print("Se n é inteiro positivo, então: ")
print("1**2 + 2**2 + ... + n**2 = n(n+1)(2n + 1)/6")
print("---")

print("Caso base:")
print("n = 0")
n = 0
print(f"Caso base: {verificar03(n)}")
print("---")
if verificar03(n):
    print("caso base é verdadeiro")
    print("Agora, pode ser testado para qualquer numero. ")
    n = input_positivo_nulo("Digite o número que deseja testar: ")
    print(f"Caso usuario: {verificar03(n)}")
    
    print("---")
    if verificar03(n):
        print("O caso usuario é verdade.")
        print("Para melhor demonstração, devemos testar o n + 1 | n = caso do usuario. |")
        print(f"O caso de n + 1: {verificar03(n+1)}")
        print("---")
        if verificar03(n+1):
            print("Concluimos que todos os casos são verdadeiros")
        else:
            print("Concluimos que nem para todos os casos são verdadeiros")
    else:
        print("O caso usuario não é verdade.")
else:
    print("O caso base não é verdade.")
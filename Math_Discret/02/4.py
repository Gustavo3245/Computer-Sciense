def input_positivo_nulo(msg):
    n = int(input(msg))
    if n >= 0:
        return n
    while n < 0:
        n = int(input("Não são aceitos numeros negativos. Tente novamente: "))

def exemplo04(n):
    resultado = 0
    for i in range(n+1):
        resultado += 2**i
    return resultado

def verificar04(n):
    resultado = exemplo04(n)
    if resultado == (2**(n+1)) - 1:
        return True
    return False

def main():
    print("Exemplo 04:")
    print("Se n é inteiro positivo, então: ")
    print("SOMATORA 2**i (i = 0 -> i = n) = (2**(n+1))-1")
    print("---")

    print("Caso base:")
    print("n = 0")
    n = 0
    print(f"Caso base: {verificar04(n)}")
    print("---")
    if verificar04(n):
        print("caso base é verdadeiro")
        print("Agora, pode ser testado para qualquer numero. ")
        n = input_positivo_nulo("Digite o número que deseja testar: ")
        print(f"Caso usuario: {verificar04(n)}")
        
        print("---")
        if verificar04(n):
            print("O caso usuario é verdade.")
            print("Para melhor demonstração, devemos testar o n + 1 | n = caso do usuario. |")
            print(f"O caso de n + 1: {verificar04(n+1)}")
            print("---")
            if verificar04(n+1):
                print("Concluimos que todos os casos são verdadeiros")
            else:
                print("Concluimos que nem para todos os casos são verdadeiros")
        else:
            print("O caso usuario não é verdade.")
    else:
        print("O caso base não é verdade.")
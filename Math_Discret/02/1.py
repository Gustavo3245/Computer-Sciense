def input_positivo(msg):
    n = int(input(msg))
    if n > 0:
        return n
    while n <= 0:
        n = int(input("Não são aceitos numeros negativos ou 0. Tente novamente: "))

def exemplo01(n):
    resultado = 0
    for i in range(1,n+1):
        resultado += (2 * i) - 1
    return resultado

def verificar01(n):
    resultado = exemplo01(n)
    if resultado == n**2:
        return True
    return False

def main():
    print("Exemplo 01:")
    print("Se n é inteiro positivo, então: ")
    print("1+3+...+(2n-1) = n ** 2")
    print("---")

    print("Caso base:")
    print("n = 1")
    n = 1
    print(f"Caso base: {verificar01(n)}")
    print("---")
    if verificar01(n):
        print("caso base é verdadeiro")
        print("Agora, pode ser testado para qualquer numero. ")
        n = input_positivo("Digite o número que deseja testar: ")
        print(f"Caso usuario: {verificar01(n)}")
        print("---")
        if verificar01(n):
            print("O caso usuario é verdade.")
            print("Para melhor demonstração, devemos testar o n + 1 | n = caso do usuario. |")
            print(f"O caso de n + 1: {verificar01(n+1)}")
            print("---")
            if verificar01(n+1):
                print("Concluimos que todos os casos são verdadeiros")
            else:
                print("Concluimos que nem para todos os casos são verdadeiros")
        else:
            print("O caso usuario não é verdade.")
    else:
        print("O caso base não é verdade.")
def input_positivo(msg):
    n = int(input(msg))
    if n > 0:
        return n
    while n <= 0:
        n = int(input("Não são aceitos numeros negativos ou 0. Tente novamente: "))

def exemplo02(n):
    resultado = 0
    for i in range(1,n+1):
        resultado += i
    return resultado

def verificar02(n):
    resultado = exemplo02(n)
    if resultado == (n * (n+1)) / 2:
        return True
    return False

def main():
    print("Exemplo 02:")
    print("Se n é inteiro positivo, então: ")
    print("1+2+...+n = n(n+1)/2")
    print("---")

    print("Caso base:")
    print("n = 1")
    n = 1
    print(f"Caso base: {verificar02(n)}")
    print("---")
    if verificar02(n):
        print("caso base é verdadeiro")
        print("Agora, pode ser testado para qualquer numero. ")
        n = input_positivo("Digite o número que deseja testar: ")
        print(f"Caso usuario: {verificar02(n)}")
        print("---")
        if verificar02(n):
            print("O caso usuario é verdade.")
            print("Para melhor demonstração, devemos testar o n + 1 | n = caso do usuario. |")
            print(f"O caso de n + 1: {verificar02(n+1)}")
            print("---")
            if verificar02(n+1):
                print("Concluimos que todos os casos são verdadeiros")
            else:
                print("Concluimos que nem para todos os casos são verdadeiros")
        else:
            print("O caso usuario não é verdade.")
    else:
        print("O caso base não é verdade.")
        
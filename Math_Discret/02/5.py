from math import factorial

def input_maior_que(msg,numero):
    n = int(input(msg))
    if n > numero:
        return n
    while n < numero:
        n = int(input(f"Não são aceitos numeros menores que {numero}. Tente novamente: "))

def exemplo05(n):
    return 2**n

def verificar05(n):
    resultado = exemplo05(n)
    if resultado < factorial(n):
        return True
    return False

def main():
    print("Exemplo 05:")
    print("Se n >= 4, então: ")
    print("2**n < n!")
    print("---")

    print("Caso base:")
    print("n = 4")
    n = 4
    print(f"Caso base: {verificar05(n)}")
    print("---")
    if verificar05(n):
        print("caso base é verdadeiro")
        print("Agora, pode ser testado para qualquer numero. ")
        n = input_maior_que("Digite o número que deseja testar: ",3)
        print(f"Caso usuario: {verificar05(n)}")
        
        print("---")
        if verificar05(n):
            print("O caso usuario é verdade.")
            print("Para melhor demonstração, devemos testar o n + 1 | n = caso do usuario. |")
            print(f"O caso de n + 1: {verificar05(n+1)}")
            print("---")
            if verificar05(n+1):
                print("Concluimos que todos os casos são verdadeiros")
            else:
                print("Concluimos que nem para todos os casos são verdadeiros")
        else:
            print("O caso usuario não é verdade.")
    else:
        print("O caso base não é verdade.")
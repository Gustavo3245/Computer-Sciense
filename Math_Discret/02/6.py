
def exemplo06(n):




def main():
    print("Exemplo 06:")
    print("Se n >= 4, então: ")
    print("2**n < n!")
    print("---")

    print("Caso base:")
    print("n = 4")
    n = 4
    print(f"Caso base: {verificar06(n)}")
    print("---")
    if verificar06(n):
        print("caso base é verdadeiro")
        print("Agora, pode ser testado para qualquer numero. ")
        n = input_maior_que("Digite o número que deseja testar: ",3)
        print(f"Caso usuario: {verificar06(n)}")
        
        print("---")
        if verificar06(n):
            print("O caso usuario é verdade.")
            print("Para melhor demonstração, devemos testar o n + 1 | n = caso do usuario. |")
            print(f"O caso de n + 1: {verificar06(n+1)}")
            print("---")
            if verificar06(n+1):
                print("Concluimos que todos os casos são verdadeiros")
            else:
                print("Concluimos que nem para todos os casos são verdadeiros")
        else:
            print("O caso usuario não é verdade.")
    else:
        print("O caso base não é verdade.")
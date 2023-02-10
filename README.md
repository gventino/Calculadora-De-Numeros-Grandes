# 🤖 **Calculadora de Números Grandes**:
## 🧑‍💻Colaboradores:
  * @Luc4smp - https://github.com/Luc4smp
  * @MariaLuisaGabriel - https://github.com/MariaLuisaGabriel

## Visão Geral:
Trabalho do segundo período do curso *Bacharelado em Ciências da Computação* da **UFU**(Universidade Federal de Uberlândia-MG) na disciplina de *Algoritmos e Estruturas de Dados 1*. O programa implementa uma calculadora de números inteiros de tamanho arbitrário, que é capaz de operar com números maiores do que o valor máximo suportado pelos tipos de dados *int* e *long*. Foi criada uma representação para tais números que explora os benefícios oferecidos pelas estruturas de dados vistas em sala de aula, mais detalhes serão dados nos próximos tópicos.

## Organização das Estruturas Utilizadas:
O programa conta com duas estruturas principais que utilizam de outras estruturas.

### Números:
Os Números são organizados em um **Lista Duplamente Encadeada** com descritor de **Início da Lista**;

### Nós dos Números:
Cada Nó conta com os seguintes Campos:
* Endereço do Próximo Nó;
* Valor armazenado no Nó (Cada Nó armazena um dígito nesse campo);

### Histórico:
O Histórico é uma Fila **LIFO**(*Last In First Out*) encadeada com descritor de **Início da Fila**

### Nós do Histórico:
Cada Nó conta com os seguintes Campos:
* Endereço do Próximo Nó;
* Primeiro Número, Segundo Número e Terceiro Número (Seguindo a estrutura adotada para os Números);
* Operação realizada entre os dois primeiros Números;

### 🤔Por que optamos por essas Estruturas?
Escolhemos usar uma Lista Duplamente Encadeada para os Números em razão dos seguintes fatores:
  * Facilidade em navegar sentido Início->Fim e sentido Fim->Inicio;
  * Estrutura de Dados mais genérica;
  * Fácil de trabalhar, é extremamente conveniente;
   
Escolhemos usar uma Fila para o Histórico em razão dos seguintes fatores:
  * Entendemos que caso fosse necessário retirar uma operação do Histórico para liberar memória o certo seria retirar a operação mais antiga;
  
## Funcionalidades da Calculadora:
A calculadora em seu **Menu Inicial** dispõe de um total de 5 opções:

![image](https://user-images.githubusercontent.com/82289479/218175209-7593dfe4-de3c-45cb-bf88-5b17a4bfe3d6.png)

---

### Opção 🇦 :
Ao escolher essa opção é pedido do usuário o *input* do primeiro Número, a operação que será feita com esse Número e o Segundo Número. Logo após a passagem desses dados a operação escolhida é realizada e o resultado mostrado na tela da seguinte forma:

![image](https://user-images.githubusercontent.com/82289479/218176015-70515c12-a9ea-4a20-9c9d-040a12ea93c0.png)

---

### Opção 🇧 :
Limpa a estrutura de Histórica que é utilizada durante toda a execução do programa.

---

### Opção 🇨 :
Exibe o Histórico no *buffer* de saída da seguinte forma:

![image](https://user-images.githubusercontent.com/82289479/218177266-1c94ab12-3ca5-4341-9757-d72029ce52b4.png)

---

### Opção 🇩 :
Limpa o terminal (sim, simples assim).

---

### Opção 🇽 :
Encerra a aplicação (sim, outro nome autoexplicativo).

---

## Outras Funcionalidades:
A aplicação guarda os erros no arquivo `log.txt` e salva todas as operações do Histórico no arquivo `historico.txt`, observe que se esses arquivo já não estiverem criados eles serão criados ao executar a aplicação.

## 🤔Após clonar o repositório, como eu uso a aplicação ?
  * Caso você use a IDE CodeBlocks é só abrir o arquivo do projeto e executar a opção `build & run` na IDE;
  * Caso contrário, você deve ter a ferramenta `gcc` instalada no seu `cmd` e usar as seguintes linhas de comando:
      * `gcc -o main main.c calculadora.c` e logo em seguida `main.exe`;
 *Para Linux você terá problemas para compilação e execução do problema devido ao uso do `windows.h` na aplicação;
 
 ## *Final Toughts*:
 Por hora, o projeto está dado como finalizado até que encontremos algo para melhorar ou corrigir, aceitamos *feedbacks* e acreditamos que foi um trabalho muito proveitoso e que nos ensinou muito.





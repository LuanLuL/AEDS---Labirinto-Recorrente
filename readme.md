<section>   
    <h1>📢 AEDS: Labirinto Recorrente</h1>   
    <p>
        Criado em Abril de 2023, o projeto <strong>Labirinto Recorrente</strong> foi desenvolvido em virtude de atender as demandas do curso de Algoritimo e Estrutura de Dados, ministrado pelo professor <a href="https://www.linkedin.com/in/michelpiressilva/?originalSubdomain=br" target="_blank">Michel Pires Da Silva</a> no Centro Federal de Educação Tecnológica de Minas Gerais (<a href="https://www.divinopolis.cefetmg.br/" target="_blank">CEFET-MG</a>).
    </p>
</section>
<section>
    <h2>🛠 Problemática</h2>
    <p>
       Após produzir um trabalho de aquecimento que envolvia o caminhamento em matrizes (<a href="https://github.com/LuanLuL/AEDS---Caminho-Guloso">AEDS: Caminho-Guloso</a>), está na hora de incluir nesse processo execuções mais elaboradas, as quais nos permita analisar o custo computacional de todo o processo. Nessa perspectiva, o problema do Labirinto Recorrente consiste em um personagem que se encontra perdido em um labirinto, o qual é composto por várias matrizes quadradas de mesma proporção, cuja posição de sua localização é dada por um elemento (x, y) dentro dessa estrutura.
    </p>
    <p>
        O objetivo principal do personagem é atravessar todas as matrizes que compõem o labirinto até que o seu último caminho se torne zero. Ou seja, todos os elementos percorridos desde o elemento inicial até seu reencontro devem possuir o valor zero. Após isso, é preciso apresentar como resultado final: 
    </p>
    <ol type="a">
        <li>Quantidade de casas que foram percorridas ao todo;</li>
        <li>A soma de itens consumidos pelo caminho completo;</li>
        <li>Quantidade de casas da matriz que ficaram sem serem exploradas;</li>
        <li>Quantidade de perigos enfrentados ao decorrer do percurso.</li>
    </ol>
</section>
<section>
    <h2>🚧 Regras</h2>
    <p>
        Nesse labirinto existem dois elementos que devem ser tratados de formas diferentes. O primeiro elemento especial é a parede (#). As paredes bloqueiam os passos do personagem, fazendo com que a única opção seja desviar e continuar por outro percurso. Já o segundo elemento especial é chamado de armadilha (*). A cada armadilha atravessada pelo personagem, ele levará 1 de dano em um total máximo de 10 vidas. De resto, todos os outros elementos da matriz são considerados como possíveis trajetórias, as quais são valores numéricos positivos.
    </p>
    <p>
        Ao decorrer do percuso, a cada passo correto sob uma estrada, o personagem ganha um item, subtraindo esse do valor que compõe a posição (x, y) e gravando nessa o valor resultante. A cada subtração bem sucedida o item vai para um banco de vida que, quando cheio (a cada 4 itens), regenera 1 de vida para o personagem. Contudo, pode haver partes do caminho com zero itens, esses devem continuar sendo utilizados, porém, sem computar pontuação no banco de itens. 
    </p>
    <p>
        Caso o total de vidas venha a ser zero, o algoritimo deve considerar que o personagem morreu e finalizar o programa apresentando os resultados. Por fim, o personagem deve escolher o trajeto de forma aleatória. Em outras palavras, ele decide um elemento (x, y) arbitrariamente que esteja a sua volta e segue para ele se possível ou descarta caso seja uma parede.
    </p>
    <p>
        De modo geral, a intenção do problema não é encontrar uma saída, mas sim, tentar consumir o máximo possível de itens até zerar o caminho ou morrer tentando.
    </p>
</section>
<section>
    <h2>✅ Solução proposta</h2>
    <p>
        Depois de compreendido a problemática e suas respectivas regras, a estratégia de resolução apresentada se baseia em dividir o problema em partes. Primeiramente, é necessario criar uma estrutura organizada de armazenamento para as matrizes que formam o labirinto, na qual é empregado os conceitos da Orientação a Objetos. Em seguida é preciso estabelecer meios sucintos para efetivar a leitura, atualização e remoção das matrizes; uma classe foi desenvolvida para satisfazer essa demanda. Por último e mais importante, o personagem deve percorrer o labirinto até que uma das condições de parada seja alcançada. 
    </p>
    <div>
        <h3>💍 Engenharia do sistema</h3>
        <p>
            A ferramenta utilizada para construção do sistema é  a linguagem de programação C++. Sendo orientada a objetos (POO), o C++ é usado tanto para comunicação em máquinas quanto para desenvolvimento de softwares acadêmicos e corporativos, jogos e entre outras coisas. Foi escolhida por ser considerada uma das linguagens de programação mais rapidas dos mundo e por possuir as funcionalidades de POO — <a href="https://cplusplus.com/doc/tutorial/" target="_blank">saiba mais</a>.
        </p>
        <p>
            Com o intuito de organizar e decifrar o labirinto, o sistema é composto por sete classes: <i>Lista</i>, <i>No</i>, <i>Numero</i>, <i>Matriz</i>, <i>Person</i>, <i>Bag</i> e <i>Inventario</i>. Observe mais na Figura 1.  
        </p>
        <br>
        <p align="center">
            <img src="img/diagrama_classes.png">
            <br><br><strong>Figura 1:</strong> Diagrama de classes do sistema
        </p>
        <br>
        <p>
            Basicamente, a parte principal do software consiste em uma classe que realiza o gerenciamento de arquivos DATA e dois objetos com a finalidade de representar o personagem e o labirinto. As demais classes auxiliam nos métodos importantes do sistema, guardando e fornecendo informações.
        </p>
    </div>
    <div>
        <h3>📁 Estouro de memória</h3>
        <p>
            Sabe-se que os dados de entrada do labirinto são inseridos através do arquivo DATA <a href="https://github.com/LuanLuL/AEDS---Labirinto-Recorrente/blob/master/dataset/input.data">input.data</a>. Nesse sentido, o usuario tem a possibilidade de inserir matrizes do tamanho que desejar. Contudo, se ao acaso for introduzido matrizes muito grandes, o sistema pode apresentar erros ao tentar carregar um número excessivo de dados simultaneamente.
        </p>
        <p>
           Para solucionar essa dificuldade, a classe <i>Inventario</i> foi criada para gerenciar os arquivos de dados. Durante o processamento do algoritmo, está classe é responsável por separar as matrizes, de forma que apenas uma esteja alocada na memória do sistema por vez. Além disso, essa classe também
           gera o arquivo DATA <a href="https://github.com/LuanLuL/AEDS---Labirinto-Recorrente/blob/master/dataset/output.data">output.data</a>, o qual salva o labirinto após o seu processamento ser finalizado.
        </p>
    </div>
    <div>
        <h3>🎲 Randomização de posições</h3>
        <p>
           Partindo para o segmento que de fato decide qual é o percurso realizado pelo personagem dentro do labirinto, foi-se necessário implementar duas classes: <i>Person</i> e <i>Matriz</i>. Lembrando que as principais regras a serem consideradas são a aleatoriedade e o devido tratamento dos elementos especias. Nesse sentido, ao passo que a <i>Person</i> é responsavel por cuidar das decisões, a <i>Matriz</i> fornece uma posição (x, y) randomicamente entre a prováveis possibilidades.
        </p>
        <p>
            A lógica por traz dessa "escolha" aleatória se da por meio do uso da <a href="https://cplusplus.com/reference/random/">random</a>, uma biblioteca C++ que permite produzir números randomicos usando combinações de geradores e distribuições.  Nesse seguimento, a ideia consiste em gerar dois números (x, y) que entejam adjacentes a posição do personagem, ou seja, o trajeto é continuo quando dentro da matriz. Todavia, esse percurso pode se tornar não-continuo ao cair em um elemento (x, y) que esteja forá dos limites da matriz. Observe na Figura 2.
        </p>
         <pc
            <img src="img/Matrixes_examples.png">
            <br><br><strong>Figura 2:</strong> Possibilidades de randomização na matriz
        </p>
        <p>
            Observando a Figura 2, é possível perceber a forma como a conexão entre as matrizes é feita. De forma explicativa, quando o personagem se encontra dentro da matriz, o proximo elemento do percurso será sempre adjacecnte a ele. Todavia, quando o personagem se encontrar em uma das bordas, existe a possibilidade de, radomicamente, ele sair da matriz; nessa circunstância o personagem é teletransportado para outra matriz do modo exibido na Figura 2.
        </p>
        <p>
            É importante enfatizar que a primeira posição (x, y) acessada pelo personagem ao adentrar qualquer matriz também é escolhida de forma aleatória. Ou seja, o personagem sempre começará em um elemento randomico dentro dos limites e que não seja uma parede da matriz; Não há exeções para esse comportamento.
        </p>
        <p>
            Outra idealização a ser considerada no processo de randomização das posições é a respeito dos portais. Um portal nada mais é que uma parede situada em uma borda. Se acessado, um portal tem por função teletrasnportar o personagem para a matriz mais próxima. Portanto, tendo em mente que a matriz posterior tem prioridade, os portais localizados na borda direita ou inferior conduzem para a matriz seguinte. Já os portais situados na borda esquerda ou superior levam para a matriz anterior. Isso é empregado no sitema para melhorar a conexão entre as matrizes, fazendo com que o software se torne mais sucinto.   
        </p>
    </div>
</section>
<section>
    <h2>🎞 Processamento</h2>
    <p>
        Durante o deselvovimento do algoritimo apresentado nesse repositório, foi-se utilizado de três principais tecnologias: Visual Studio Code e WSL:Ubunto.
    </p>
    <ul>
        <li>    
            <p>
                O Visual Studio Code é um editor de texto multiplataforma disponibilizado pela Microsoft para o desenvolvimento de aplicações, Conhecer essa ferramenta é importante para os desenvolvedores que pretendem trabalhar em ambientes multiplataforma, por exemplo,  podendo operar o desenvolvimento em ambiente Mac e Linux, ao mesmo tempo em que mantém o projeto compatível com Windows. Segue em anexo o link para o site da plataforma — <a href="https://code.visualstudio.com/" target="_blank">Visual Studio Code</a>.
            </p>
        </li>
        <li>
            <p>O WSL é um método para se executar o Sistema Operaciona Linux dentro do Windows de forma muito facil. Essa platoforma se torna essencial para o desenvovimento em ambiente GNU Linux, evitando tarefas como a intalação de maquinas vituais, criação de dual booting no computador pessoal e entre outras coisas. Além disso, existem diversas vantagens como rodar programas em conjunto e compartihamento de localhost. Segue em anexo um  tutorial de download do WSL2 — <a href="https://youtu.be/hd6lxt5iVsg" target="_blank">Tutorial WSL2</a>.</p>
        </li>
    </ul>
    <p>
        Por fim, visando dimuir o tempo de processamento do programa de computador é empregado o arquivo <a href="https://pt.stackoverflow.com/questions/154102/makefile-o-que-%C3%A9-e-qual-a-finalidade">Makefile</a> que realiza todo o procedimento de compilação e execução. Para tanto, segue anexado na Tabela 1, as diretrizes de execução no padrão <code>make</code>:
    </p>
    <div align="center">
        <table>
            <thead>
                <tr>
                    <th>Comando</th>
                    <th>Função</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td><code>make clean</code></td>
                    <td>Apaga a última compilação realizada contida na pasta build</td>
                </tr>
                <tr>
                    <td><code>make</code></td>
                    <td>Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build</td>
                </tr>
                <tr>
                    <td><code>make run</code></td>
                    <td>Executa o programa da pasta build após a realização da compilação</td>
                </tr>
            </tbody>
        </table>
        <p align="center">
            <b>Tabela 1:</b> Comandos úteis para compilar e executar o software
        </p>
    </div>
</section>
<section>
    <h2>🙌 Resultado Final</h2>
    <p>
        Diante do exposto, tem-se que o programa de computador apresentado nesse repositório, é capaz de resolver a problemática do labirinto recorrente. Com uma temática randômica, os métodos princiapais do algoritimo somam em média um custo assintótico de 
        <p align="center">
            <i><strong>K × ( 27 + n )</i> ,</strong>
        </p>
        onde <i>K</i> representa o número de parcelas randomizadas, <i>n</i> simboliza a quantidade de matrizes dadas como entrada no sistema e <i>27</i> é o custo computacional constante das funções utilizadas:
    </p>
    <a href="https://github.com/LuanLuL/AEDS---Labirinto-Recorrente/blob/master/src/Person.cpp">
        <p><code>void Person::move(){...}</code></p>
        <p><code>Person::finishSolveMaze(){...}</code></p>
    </a>
    <a href="https://github.com/LuanLuL/AEDS---Labirinto-Recorrente/blob/master/src/Matriz.cpp">
        <p><code>short int Matriz::randomStreet(){...}</code></p>
        <p><code>void Matriz::randomStart(){...}</code></p>
    </a>
    <p>
        Observe abaixo um possível desfecho atingido com a entrada <a href="https://github.com/LuanLuL/AEDS---Labirinto-Recorrente/blob/master/dataset/input.data">input.data</a>:
        <pre>
    ************* INICIO *************<br>
    Resolvendo o labirinto recorrente ...<br>
    FIM DE JOGO<br>
    O personagem morreu!<br>
    Resultados:<br>
    a) Quantidade de casas percorridas ao todo: 59<br>
    b) Soma de itens consumidos pelo caminho: 36<br>
    c) Quantidade de casas que ficaram sem serem exploradas:<br>
            Matriz 1: 25
            Matriz 2: 30
            Matriz 3: 21<br>
    d) Quantidade de perigos enfrentados ao decorrer do percurso: 19<br>
    ************* FIM *************
        </pre>
    </p>
    <p>
        Conclui-se então que a problemática do labirinto recorrente, na maioria dos casos, não será finalizada, pois o persongem acaba morrendo antes de acatar as condições de parada. Além disso, os resultados finais não possuem um padrão para a mesma entrada de dados. Assim sendo, por possuir características de processamento randômico, a cada excução, o software poderá apresentar uma solução completamente diferente.
    </p>
</section>
<section>
    <hr size="0.5">
    <div>
          <p>
           Feito por <strong>Luan Gonçalves Santos</strong>     
         </p>
         <p align="right">
          <a href="https://www.linkedin.com/in/luan-santos-9bb01920b/" taget="_blank"><img src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white"></a>
        <a href="https://www.instagram.com/luann_gsantos/" taget="_blank"><img src="https://img.shields.io/badge/Instagram-E4405F?style=for-the-badge&logo=instagram&logoColor=white"></a>
        <p>
    </div>
</section>


<!-- 

Organizando a matriz:

* == (-1)
# == (-2)
PORTAL PARA MATRIZ ANTERIOR == (-3) 
PORTAL PARA PROXIMA MATRIZ == (-4)                                          
-->
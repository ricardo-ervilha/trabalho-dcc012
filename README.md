<h1>Estrutura de Dados II(DCC012 - UFJF)</h1>
<h2>Trabalho Prático - Parte 1</h2>

<h3>Professor: Marcelo Caniato Renhe</h3>

<h4><br>Repositório associado ao projeto avaliativo em C++ da disciplina de Estrutura de Dados II(2022.3).</p>

<h3>📌 Features</h3>
<ul type="square">
<li>TAD ProductReview contendo os campos UserID, ProductID, Rating e TimeStamp.</li>
<li>CreateBinary: Função para geração do arquivo binário utilizando buffer de dados.</li>
<li>GetReview: Função para recuperar um review <b>i</b> de dentro do arquivo binário.</li>
<li>Import: Função para importar <b>n</b> registros do arquivo binário. A mesma conta com o auxílio
de uma tabela hash<br>para acelerar na verificação de reviews já sorteados anteriormente.</li>
<li>Ordenação com uso do Merge Sort, Quick Sort e Bucket Sort.</li>
<li>Estatísticas dos métodos de ordenação para diferentes conjuntos de dados.</li>
<li>Tabela hash de ProductID's, a qual imprime os <b>p</b> elementos com maior frequência.</li>
</ul>


<h3>☕ Integrantes da equipe <b>Empty Coffee Cups</b></h3>

<ul>
<li>Kaio De Oliveira e Sousa</li>
<li>Lucas Silva Santana</li>
<li>Pedro de Araújo Bhering Bittencourt</li>
<li>Ricardo Ervilha Silva</li>
</ul>


<h3>📁 Divisão dos arquivos</h3>
<ul>
<li>apps: programa principal</li>
<li>data: arquivos input.dat, e saida.txt</li>
<li>include: arquivos de cabeçalho dos TAD's</li>
<li>src: arquivos de implementação dos TAD's</li>
</ul>


<h3>📗 Passo-a-passo para compilar os arquivos com auxílio do Make</h3>
<ol>
<li>make pre: Gera as pastas obj e bin antecipadamente, as quais conterão os binários dos TAD's e main, respectivamente.</li>
<li>make libed: Compila os TAD's.</li>
<li>make myapps: Compila e gera o executável da main.</li>
<li>make clean: Limpa os arquivos binários gerados nas pastas obj e bin.</li>
</ol>

#### 🧭 Rodando a aplicação pelo terminal

```bash

# Clone este repositório
$ https://github.com/ricardo-ervilha/trabalho-dcc012

# Acesse a pasta do projeto no seu terminal/cmd
$ cd trabalho-dcc012

# Compilar e executar a aplicação
make clean pre libed myapps && ./bin/main
```

<h3>🛈 Fontes usadas para consulta durante o trabalho</h3>
<ul>
<li>https://www.javatpoint.com/how-to-split-strings-in-cpp</li>
<li>https://www.ufjf.br/jairo_souza/ensino/material/ed2/</li>
<li>https://stackoverflow.com/questions/28115724/getting-big-random-numbers-in-c-c </li>
<li>http://www.cse.yorku.ca/~oz/hash.html</li>
<li>https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/</li>
<li>https://www.geeksforgeeks.org/bucket-sort-2/</li>
<li>Algoritmos: teoria e prática Cormen, Thomas Capítulo 8 Seção 8.4</li>
</ul>

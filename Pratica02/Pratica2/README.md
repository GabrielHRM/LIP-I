# Prática 02 — Herança e Polimorfismo

Sistema de lançamento de notas de alunos desenvolvido para a prática de Herança e Polimorfismo.

A superclasse `Aluno` concentra os dados e comportamentos comuns. As subclasses especializam as regras de avaliação, período e prazo de integralização. A criação dos objetos é centralizada em `AlunoFactory`, enquanto `SistemaNotasView` trabalha, em geral, apenas com referências do tipo `Aluno`.

## Identificação

**Nome:** Gabriel Henrique Rocha Melo

**Matrícula:** 20250059916

**Versão do JDK utilizada:** openjdk version "25.0.4.1" 2026-08-18 LTS  

## Como compilar e executar

A partir da pasta onde estão todos os arquivos `.java`:

```bash
javac -d out *.java
java -cp out SistemaNotasView
```

No PowerShell do Windows, os mesmos comandos podem ser usados:

```powershell
javac -d out *.java
java -cp out SistemaNotasView
```

## Arquivos do projeto

- `Aluno.java` — superclasse com os dados e comportamentos comuns.
- `AlunoTecnico.java` — aluno de curso técnico.
- `AlunoGraduacao.java` — aluno de graduação.
- `AlunoPosGraduacao.java` — aluno de pós-graduação.
- `AlunoIntercambio.java` — quarto tipo criado para demonstrar a extensibilidade do projeto.
- `AlunoFactory.java` — responsável por criar a subclasse correspondente ao tipo informado.
- `SistemaNotasView.java` — cliente que monta a turma, lança notas e imprime os relatórios.

## Quarto tipo de aluno criado

Foi criado o tipo `AlunoIntercambio`.

Regras utilizadas:

- tempo de curso contado em meses;
- prazo máximo de 12 meses;
- duas avaliações;
- média das duas avaliações;
- média maior ou igual a 7,0: aprovado;
- média abaixo de 7,0: recuperação.

Além da nova classe `AlunoIntercambio.java`, foram modificados **2 arquivos**:

1. `AlunoFactory.java`, para reconhecer o tipo `INTERCAMBIO`;
2. `SistemaNotasView.java`, para incluir um aluno de intercâmbio nos dados usados no teste.

A estrutura dos métodos de relatório, resumo e controle de prazo não precisou ser alterada para tratar especificamente o novo tipo.

## Por que o cliente consegue tratar todos os alunos do mesmo jeito?

Porque todas as classes específicas herdam de `Aluno`.

O cliente pode manter uma referência do tipo `Aluno` e chamar métodos como `lancarNota()`, `getSituacao()`, `getPeriodoAtual()` e `getPrazo()` independentemente da subclasse concreta.

Quando um desses métodos foi sobrescrito, a implementação executada é a da classe real do objeto armazenado na memória. Isso é polimorfismo por sobrescrita com ligação dinâmica.

## Por que o cliente não precisa de `instanceof` nem de casting?

Porque as operações necessárias ao cliente já estão definidas na superclasse `Aluno`.

Cada subclasse sobrescreve os métodos cuja regra muda conforme o tipo de curso. Dessa forma, o cliente apenas chama o mesmo método através de uma referência `Aluno`, e o Java escolhe em tempo de execução a implementação correspondente ao tipo dinâmico do objeto.

A criação das subclasses também é centralizada em `AlunoFactory`, evitando que o cliente tenha que decidir qual classe concreta instanciar.

## Por que `getMedia()` é `private` nas subclasses e `getNotas()` devolve uma cópia da lista?

`getMedia()` é `private` porque a média é um detalhe interno das subclasses que trabalham com notas numéricas. O cliente não precisa conhecer esse cálculo diretamente; ele utiliza métodos públicos como `getDesempenho()` e `getSituacao()`.

`getNotas()` devolve uma cópia para preservar o encapsulamento. Se a lista interna fosse devolvida diretamente, código externo poderia adicionar ou remover notas sem passar pela validação realizada em `lancarNota()`.

## O que acontece quando uma nota ou conceito ainda não foi lançado?

Na pós-graduação, enquanto nenhum conceito foi lançado, `getConceito()` retorna `"-"` e `getSituacao()` retorna `Nao avaliado`. Essa decisão foi usada porque ainda não existe informação suficiente para classificar o aluno como aprovado, em recuperação ou reprovado.

Nos tipos com notas numéricas, as avaliações ainda não lançadas entram implicitamente como zero no cálculo porque a soma das notas existentes é dividida pelo total previsto de avaliações. Esse comportamento segue o padrão já fornecido em `AlunoTecnico`.

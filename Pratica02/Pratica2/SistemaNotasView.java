import java.util.ArrayList;
import java.util.HashMap;

/**
 * Cliente das classes de aluno: o programa que lança notas e imprime o
 * relatório da turma.
 *
 * Ponto central da prática: esta classe NÃO deve saber se está
 * lidando com um AlunoTecnico, um AlunoGraduacao ou um AlunoPosGraduacao.
 * Ela conversa apenas com o tipo Aluno.
 *
 * ---------------------------------------------------------------------
 * ITENS 5, 6 DA PRÁTICA: complete esta classe.
 * ---------------------------------------------------------------------
 */
public class SistemaNotasView {

    public static void main(String[] args) {
        ArrayList<Aluno> turma = montarTurma();

        imprimirRelatorio(turma);
        imprimirResumoPorSituacao(turma);
        imprimirAlertasDePrazo(turma);
        demonstrarTipoEstaticoEDinamico();
        demonstrarCasosDeBorda();
    }

    private static ArrayList<Aluno> montarTurma() {

        ArrayList<Aluno> turma = new ArrayList<Aluno>();

        String[][] alunos = {
            {"TECNICO",     "2026001", "Albert Einstein",    "03/2026"},
            {"TECNICO",     "2021005", "Emmy Noether",       "03/2021"},
            {"GRADUACAO",   "2026003", "Cecilia Payne",      "03/2026"},
            {"POS",         "2026004", "Dmitri Mendeleev",   "03/2026"},
            {"GRADUACAO",   "2020005", "Ada Lovelace",       "03/2020"},
            {"POS",         "2020006", "Marie Curie",         "03/2020"},
            {"INTERCAMBIO", "2026015", "Rosalind Franklin",  "03/2026"}
        };

        String[][] notas = {
            {"8.0", "7.5", "6.0", "9.0"},
            {"4.0", "3.0", "5.0", "2.0"},
            {"8.0", "7.0", "9.0"},
            {"A"},
            {"5.0", "5.0", "5.0"},
            {"C"},
            {"8.0", "7.0"}
        };

        for (int i = 0; i < alunos.length; i++) {

            Aluno aluno = AlunoFactory.criar(
                alunos[i][0],
                alunos[i][1],
                alunos[i][2]
            );

            if (aluno != null) {

                aluno.setInicioDoCurso(alunos[i][3]);

                lancarNotas(
                    aluno,
                    notas[i]
                );

                turma.add(aluno);
            }
        }

        return turma;
}

    /** Lança várias notas de um aluno qualquer, sem saber o tipo dele. */
    private static void lancarNotas(Aluno aluno, String... valores) {
        for (int i = 0; i < valores.length; i++) {
            aluno.lancarNota(valores[i]);
        }
    }

    /**
     * Item 5 - EXEMPLO JÁ PRONTO de código polimórfico.
     *
     * Nenhum instanceof, nenhum casting, nenhum if por tipo de aluno: o laço
     * abaixo continua funcionando mesmo depois que você criar o quarto tipo
     * de aluno do item 6.
     */
    private static void imprimirRelatorio(ArrayList<Aluno> turma) {
        System.out.println("===== RELATORIO DA TURMA =====");
        System.out.printf(
            "%-10s %-22s %-10s %-22s %s%n",
            "MATRICULA", "NOME", "PERIODO", "DESEMPENHO", "SITUACAO"
        );
        for (Aluno aluno : turma) {
            // imprimirInformacoes() está escrito APENAS na classe Aluno (tipo estático),
            // mas os métodos que ele chama são os da subclasse do objeto (tipo dinâmico).
            aluno.imprimirInformacoes();
        }
        System.out.println();
    }

    /**
     * TODO 5.4: conte quantos alunos estão em cada situação e imprima o resumo.
     * Sugestão: um HashMap<String, Integer> e o vetor de situações abaixo,
     * que usa as constantes de Aluno. Não use instanceof aqui.
     *
     *     String[] situacoes = {Aluno.APROVADO, Aluno.RECUPERACAO,
     *                           Aluno.REPROVADO, Aluno.NAO_AVALIADO};
     */
    private static void imprimirResumoPorSituacao(ArrayList<Aluno> turma) {

        System.out.println("===== RESUMO POR SITUACAO =====");

        HashMap<String, Integer> resumo = new HashMap<String, Integer>();

        resumo.put(Aluno.APROVADO, 0);
        resumo.put(Aluno.RECUPERACAO, 0);
        resumo.put(Aluno.REPROVADO, 0);
        resumo.put(Aluno.NAO_AVALIADO, 0);

        for (Aluno aluno : turma) {

            String situacao = aluno.getSituacao();

            resumo.put(
                situacao,
                resumo.get(situacao) + 1
            );
        }

        System.out.println(
            Aluno.APROVADO + ": "
            + resumo.get(Aluno.APROVADO)
        );

        System.out.println(
            Aluno.RECUPERACAO + ": "
            + resumo.get(Aluno.RECUPERACAO)
        );

        System.out.println(
            Aluno.REPROVADO + ": "
            + resumo.get(Aluno.REPROVADO)
        );

        System.out.println(
            Aluno.NAO_AVALIADO + ": "
            + resumo.get(Aluno.NAO_AVALIADO)
        );

        System.out.println();
}

    /**
     * TODO 5.5: para cada aluno, imprima o nome, o prazo (getPrazo()) e se
     * ele ainda está dentro do prazo de integralização (estaNoPrazo() e
     * getTempoRestante()). Repare que a unidade de tempo muda de um tipo para
     * outro, mas o cédigo aqui é um só. Mostre também getInicioDoCurso(): é a
     * data de onde todos esses números são calculados.
     */
    private static void imprimirAlertasDePrazo(ArrayList<Aluno> turma) {

        System.out.println("===== PRAZO DE INTEGRALIZACAO =====");

        for (Aluno aluno : turma) {

            System.out.println("Aluno: " + aluno.getNome());
            System.out.println(
                "Inicio do curso: "
                + aluno.getInicioDoCurso()
            );

            System.out.println(
                "Prazo: "
                + aluno.getPrazo()
            );

            if (aluno.estaNoPrazo()) {

                System.out.println(
                    "Situacao do prazo: dentro do prazo"
                );

                System.out.println(
                    "Tempo restante: "
                    + aluno.getTempoRestante()
                    + " "
                    + aluno.getUnidadeDePrazo()
                );
            }
            else {

                System.out.println(
                    "Situacao do prazo: prazo excedido"
                );
            }

            System.out.println();
        }
}

    /**
     * TODO 5.6: demonstre tipo estático x tipo dinâmico (Aula 05).
     * Declare uma variável do tipo Aluno, aponte-a para objetos de subclasses
     * diferentes e chame os MESMOS métodos, mostrando que a implementação
     * executada é a da classe do objeto (late binding). Por exemplo:
     *
     *     Aluno a = AlunoFactory.criar("TECNICO", "2026008", "Heinrich Hertz");
     *     a.setInicioDoCurso("03/2025");
     *     a.lancarNota("10.0");
     *     System.out.println(a.getSituacao());
     *
     *     a = AlunoFactory.criar("POS", "2026009", "Isaac Newton");
     *     a.setInicioDoCurso("01/2026");
     *     a.lancarNota("A");
     *     System.out.println(a.getSituacao());
     *
     * Inclua também um objeto criado com "new Aluno(...)" e observe o que
     * acontece: como a superclasse não conhece a regra de nenhum curso, a
     * situação dele sai como "Nao avaliado".
     * Use a.getClass().getSimpleName() para exibir o tipo dinâmico.
     */
    private static void demonstrarTipoEstaticoEDinamico() {

        System.out.println(
            "===== TIPO ESTATICO x TIPO DINAMICO ====="
        );

        Aluno a = AlunoFactory.criar(
            "TECNICO",
            "2026008",
            "Heinrich Hertz"
        );

        a.setInicioDoCurso("03/2025");

        lancarNotas(
            a,
            "10.0", "10.0", "10.0", "10.0"
        );

        System.out.println(
            "Tipo estatico: Aluno"
        );

        System.out.println(
            "Tipo dinamico: "
            + a.getClass().getSimpleName()
        );

        System.out.println(
            "Situacao: "
            + a.getSituacao()
        );

        System.out.println();

        a = AlunoFactory.criar(
            "POS",
            "2026009",
            "Isaac Newton"
        );

        a.setInicioDoCurso("01/2026");
        a.lancarNota("A");

        System.out.println(
            "Tipo estatico: Aluno"
        );

        System.out.println(
            "Tipo dinamico: "
            + a.getClass().getSimpleName()
        );

        System.out.println(
            "Situacao: "
            + a.getSituacao()
        );

        System.out.println();

        a = new Aluno(
            "2026010",
            "Aluno Generico"
        );

        a.lancarNota("10.0");

        System.out.println(
            "Tipo estatico: Aluno"
        );

        System.out.println(
            "Tipo dinamico: "
            + a.getClass().getSimpleName()
        );

        System.out.println(
            "Situacao: "
            + a.getSituacao()
        );

        System.out.println();
}

    /**
     * TODO 5.7: complete os casos de borda (casos de falha/erro).
     * Cada bloco deve imprimir o que aconteceu e o programa deve seguir em frente:
     * - tipo de aluno inexistente na AlunoFactory (cuidado com o null devolvido),
     * - conceito inválido na pós-graduação (ex.: E, F, Z),
     * - nota fora do intervalo [0, 10], texto que não é número,
     * - e notas em excesso.
     */
    private static void demonstrarCasosDeBorda() {

        System.out.println("===== CASOS DE BORDA =====");

        System.out.println(
            "Tipos aceitos pela fabrica: "
            + AlunoFactory.getTiposDisponiveis()
        );

        System.out.println();

        // Tipo inexistente
        Aluno desconhecido = AlunoFactory.criar(
            "MESTRADO",
            "2026011",
            "Katherine Johnson"
        );

        System.out.println(
            "Aluno criado para o tipo MESTRADO: "
            + desconhecido
        );

        System.out.println();

        // Conceito inválido
        Aluno pos = AlunoFactory.criar(
            "POS",
            "2026012",
            "Niels Bohr"
        );

        pos.lancarNota("E");

        System.out.println();

        // Nota acima de 10
        Aluno graduacao = AlunoFactory.criar(
            "GRADUACAO",
            "2026013",
            "Alan Turing"
        );

        graduacao.lancarNota("12");

        // Texto em vez de número
        graduacao.lancarNota("abc");

        System.out.println();

        // Notas em excesso
        Aluno tecnico = AlunoFactory.criar(
            "TECNICO",
            "2026014",
            "Nikola Tesla"
        );

        tecnico.lancarNota("8");
        tecnico.lancarNota("7");
        tecnico.lancarNota("9");
        tecnico.lancarNota("6");

        // Quinta nota: deve ser recusada
        tecnico.lancarNota("10");

        System.out.println();
    }
}

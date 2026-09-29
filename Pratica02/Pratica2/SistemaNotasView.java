import java.util.ArrayList;
import java.util.HashMap;

/**
 * Cliente das classes de aluno: o programa que lança notas e imprime o
 * relatório da turma.
 *
 * Esta classe trabalha com o tipo Aluno e deixa a escolha da subclasse
 * concreta para AlunoFactory.
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
            {"TECNICO",     "2026001", "Albert Einstein",   "03/2026"},
            {"TECNICO",     "2021005", "Emmy Noether",      "03/2021"},
            {"GRADUACAO",   "2026003", "Cecilia Payne",     "03/2026"},
            {"POS",         "2026004", "Dmitri Mendeleev",  "03/2026"},
            {"GRADUACAO",   "2020005", "Ada Lovelace",      "03/2020"},
            {"POS",         "2020006", "Marie Curie",        "03/2020"},
            {"INTERCAMBIO", "2026015", "Rosalind Franklin", "03/2026"}
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
                lancarNotas(aluno, notas[i]);
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

    private static void imprimirRelatorio(ArrayList<Aluno> turma) {
        System.out.println("===== RELATORIO DA TURMA =====");
        System.out.printf(
            "%-10s %-22s %-10s %-22s %s%n",
            "MATRICULA", "NOME", "PERIODO", "DESEMPENHO", "SITUACAO"
        );

        for (Aluno aluno : turma) {
            aluno.imprimirInformacoes();
        }

        System.out.println();
    }

    private static void imprimirResumoPorSituacao(ArrayList<Aluno> turma) {
        System.out.println("===== RESUMO POR SITUACAO =====");

        HashMap<String, Integer> resumo = new HashMap<String, Integer>();

        resumo.put(Aluno.APROVADO, 0);
        resumo.put(Aluno.RECUPERACAO, 0);
        resumo.put(Aluno.REPROVADO, 0);
        resumo.put(Aluno.NAO_AVALIADO, 0);

        for (Aluno aluno : turma) {
            String situacao = aluno.getSituacao();
            resumo.put(situacao, resumo.get(situacao) + 1);
        }

        System.out.println(Aluno.APROVADO + ": " + resumo.get(Aluno.APROVADO));
        System.out.println(Aluno.RECUPERACAO + ": " + resumo.get(Aluno.RECUPERACAO));
        System.out.println(Aluno.REPROVADO + ": " + resumo.get(Aluno.REPROVADO));
        System.out.println(Aluno.NAO_AVALIADO + ": " + resumo.get(Aluno.NAO_AVALIADO));
        System.out.println();
    }

    private static void imprimirAlertasDePrazo(ArrayList<Aluno> turma) {
        System.out.println("===== PRAZO DE INTEGRALIZACAO =====");

        for (Aluno aluno : turma) {
            System.out.println("Aluno: " + aluno.getNome());
            System.out.println("Inicio do curso: " + aluno.getInicioDoCurso());
            System.out.println("Prazo: " + aluno.getPrazo());

            if (aluno.estaNoPrazo()) {
                System.out.println("Situacao do prazo: dentro do prazo");
                System.out.println(
                    "Tempo restante: "
                    + aluno.getTempoRestante()
                    + " "
                    + aluno.getUnidadeDePrazo()
                );
            }
            else {
                System.out.println("Situacao do prazo: prazo excedido");
            }

            System.out.println();
        }
    }

    private static void demonstrarTipoEstaticoEDinamico() {
        System.out.println("===== TIPO ESTATICO x TIPO DINAMICO =====");

        Aluno a = AlunoFactory.criar(
            "TECNICO",
            "2026008",
            "Heinrich Hertz"
        );

        a.setInicioDoCurso("03/2025");
        lancarNotas(a, "10.0", "10.0", "10.0", "10.0");

        System.out.println("Tipo estatico: Aluno");
        System.out.println("Tipo dinamico: " + a.getClass().getSimpleName());
        System.out.println("Situacao: " + a.getSituacao());
        System.out.println();

        a = AlunoFactory.criar(
            "POS",
            "2026009",
            "Isaac Newton"
        );

        a.setInicioDoCurso("01/2026");
        a.lancarNota("A");

        System.out.println("Tipo estatico: Aluno");
        System.out.println("Tipo dinamico: " + a.getClass().getSimpleName());
        System.out.println("Situacao: " + a.getSituacao());
        System.out.println();

        // Exceção intencional à criação pela fábrica: o enunciado pede este objeto
        // para comparar a superclasse genérica com as subclasses.
        a = new Aluno(
            "2026010",
            "Aluno Generico"
        );

        a.lancarNota("10.0");

        System.out.println("Tipo estatico: Aluno");
        System.out.println("Tipo dinamico: " + a.getClass().getSimpleName());
        System.out.println("Situacao: " + a.getSituacao());
        System.out.println();
    }

    private static void demonstrarCasosDeBorda() {
        System.out.println("===== CASOS DE BORDA =====");
        System.out.println(
            "Tipos aceitos pela fabrica: "
            + AlunoFactory.getTiposDisponiveis()
        );
        System.out.println();

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

        Aluno pos = AlunoFactory.criar(
            "POS",
            "2026012",
            "Niels Bohr"
        );
        pos.lancarNota("E");
        System.out.println();

        Aluno graduacao = AlunoFactory.criar(
            "GRADUACAO",
            "2026013",
            "Alan Turing"
        );
        graduacao.lancarNota("12");
        graduacao.lancarNota("abc");
        System.out.println();

        Aluno tecnico = AlunoFactory.criar(
            "TECNICO",
            "2026014",
            "Nikola Tesla"
        );
        tecnico.lancarNota("8");
        tecnico.lancarNota("7");
        tecnico.lancarNota("9");
        tecnico.lancarNota("6");
        tecnico.lancarNota("10");
        System.out.println();
    }
}

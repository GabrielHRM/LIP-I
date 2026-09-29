/**
 * Aluno de pós-graduação (Especialização/Mestrado/Doutorado).
 *
 * Tempo de curso: contado em MESES, no máximo 24 meses para conclusão.
 * Nota final: conceito A, B, C ou D (não há média numérica).
 * Situação: A ou B aprovado; C recuperação; D reprovado direto.
 *
 * ---------------------------------------------------------------------
 * ITEM 3 DA PRÁTICA: complete esta classe.
 *
 * Repare que aqui NÃO existe média nenhuma: o estado e a regra são
 * diferentes dos outros tipos de aluno, e isso é normal. O que precisa
 * continuar igual é o conjunto de métodos herdado de Aluno.
 * ---------------------------------------------------------------------
 */
public class AlunoPosGraduacao extends Aluno {

    public static final int PRAZO_MAXIMO_MESES = 24;

    public AlunoPosGraduacao(String matricula, String nome) {
        super(matricula, nome);
    }

    @Override
    public void lancarNota(String valor) {

        // A pós-graduação aceita apenas um conceito.
        if (getNotas().size() >= 1) {
            System.out.println(
                "[aviso] A pos-graduacao aceita apenas um conceito. "
                + "Conceito ignorado: " + valor
            );
            return;
        }

        if (valor == null) {
            System.out.println(
                "[aviso] Conceito invalido. Use A, B, C ou D."
            );
            return;
        }

        String conceito = valor.trim().toUpperCase();

        if (!conceito.equals("A")
                && !conceito.equals("B")
                && !conceito.equals("C")
                && !conceito.equals("D")) {

            System.out.println(
                "[aviso] Conceito invalido. Use A, B, C ou D. "
                + "Conceito ignorado: " + valor
            );
            return;
        }

        super.lancarNota(conceito);
    }

    /**
     * O conceito lançado, ou "-" enquanto nada foi lançado.
     */
    private String getConceito() {

        if (getNotas().size() == 0) {
            return "-";
        }

        return getNotas().get(0);
    }

    @Override
    public String getSituacao() {

        String conceito = getConceito();

        // Sem conceito lançado, o aluno ainda não foi avaliado.
        if (conceito.equals("-")) {
            return NAO_AVALIADO;
        }

        if (conceito.equals("A") || conceito.equals("B")) {
            return APROVADO;
        }

        if (conceito.equals("C")) {
            return RECUPERACAO;
        }

        return REPROVADO;
    }

    @Override
    public String getDesempenho() {
        return "Conceito: " + getConceito();
    }

    @Override
    public String getPeriodoAtual() {
        return getTempoDecorrido() + "o mes";
    }

    @Override
    public int getTempoDecorrido() {
        return getMesesDecorridos() + 1;
    }

    @Override
    public int getPrazoMaximo() {
        return PRAZO_MAXIMO_MESES;
    }

    @Override
    public String getUnidadeDePrazo() {
        return "mes(es)";
    }
}
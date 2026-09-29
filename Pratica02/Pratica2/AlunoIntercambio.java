/**
 * Aluno de intercambio.
 *
 * Tempo de curso: contado em MESES, com prazo máximo de 12 meses.
 * Nota final: média de 2 avaliações.
 * Situação: média >= 7,0 aprovado; abaixo de 7,0 recuperação.
 *
 * A regra de recuperação abaixo de 7,0 foi adotada para completar a regra
 * do novo tipo, pois o enunciado fornece apenas o critério de aprovação.
 */
public class AlunoIntercambio extends Aluno {

    public static final int TOTAL_AVALIACOES = 2;
    public static final int PRAZO_MAXIMO_MESES = 12;
    public static final double MEDIA_APROVACAO = 7.0;

    public AlunoIntercambio(String matricula, String nome) {
        super(matricula, nome);
    }

    @Override
    public void lancarNota(String valor) {
        if (getNotas().size() >= TOTAL_AVALIACOES) {
            System.out.println(
                "[aviso] O intercambio tem apenas " + TOTAL_AVALIACOES
                + " avaliacoes. Nota ignorada: " + valor
            );
            return;
        }

        if (!ehNotaNumericaValida(valor)) {
            System.out.println(
                "[aviso] Nota invalida (use um numero de 0 a 10). Nota ignorada: " + valor
            );
            return;
        }

        super.lancarNota(valor);
    }

    private double getMedia() {
        double soma = 0.0;

        for (String nota : getNotas()) {
            soma += converterParaNumero(nota);
        }

        return soma / TOTAL_AVALIACOES;
    }

    @Override
    public String getSituacao() {
        if (getMedia() >= MEDIA_APROVACAO) {
            return APROVADO;
        }

        return RECUPERACAO;
    }

    @Override
    public String getDesempenho() {
        return String.format("Media: %.2f", getMedia());
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

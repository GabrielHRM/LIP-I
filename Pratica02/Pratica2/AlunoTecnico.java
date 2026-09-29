/**
 * Aluno de curso técnico.
 *
 * Tempo de curso: contado em ANOS (1o ano, 2o ano, ...), no máximo 5 anos.
 * Nota final: soma das 4 notas bimestrais dividida por 4.
 * Situação: média >= 6,0 aprovado; caso contrario, recuperação.
 *
 * A classe AlunoTecnico JÁ ESTÁ PRONTA e serve de EXEMPLO para as
 * outras subclasses.
 */
public class AlunoTecnico extends Aluno {

    public static final int TOTAL_BIMESTRES = 4;
    public static final int PRAZO_MAXIMO_ANOS = 5;
    public static final double MEDIA_APROVACAO = 6.0;

    public AlunoTecnico(String matricula, String nome) {
        super(matricula, nome);
    }

    @Override
    public void lancarNota(String valor) {
        if (getNotas().size() >= TOTAL_BIMESTRES) {
            System.out.println(
                "[aviso] O curso tecnico tem apenas " + TOTAL_BIMESTRES
                + " bimestres. Nota ignorada: " + valor
            );
            return;
        }
        if (!ehNotaNumericaValida(valor)) {
            System.out.println(
                "[aviso] Nota invalida (use um numero de 0 a 10). Nota ignorada: " + valor
            );
            return;
        }
        super.lancarNota(valor); // a superclasse guarda a nota na lista
    }

    /**
     * Média do curso técnico. É private porque só interessa aqui dentro: para
     * o cliente, quem responde é getDesempenho(). Um getMedia() público na
     * subclasse só serviria a quem fizesse casting - justamente o que este
     * projeto evita.
     */
    private double getMedia() {
        double soma = 0.0;
        for (String nota : getNotas()) {
            soma += converterParaNumero(nota);
        }
        // Divide sempre por 4: bimestre sem nota lançada conta como zero.
        return soma / TOTAL_BIMESTRES;
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
        return getTempoDecorrido() + "o ano";
    }

    /**
     * O técnico conta o tempo de curso em ANOS: cada 12 meses decorridos é um
     * ano completo, e quem acabou de entrar já está no 1o ano - por isso o + 1.
     * Repare que este é o único lugar da classe que sabe fazer essa conta: o
     * período, o prazo e o alerta de integralização saem todos daqui.
     */
    @Override
    public int getTempoDecorrido() {
        return getMesesDecorridos() / 12 + 1;
    }

    @Override
    public int getPrazoMaximo() {
        return PRAZO_MAXIMO_ANOS;
    }

    @Override
    public String getUnidadeDePrazo() {
        return "ano(s)";
    }
}

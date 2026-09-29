import java.util.ArrayList;

/**
 * Superclasse de todos os alunos do sistema.
 *
 * Aqui fica o que qualquer aluno tem (matrícula, nome e a lista de notas),
 * e o que qualquer aluno sabe responder (situação, desempenho, período, prazo).
 * Os métodos que dependem do tipo de curso têm, nesta classe, uma
 * resposta neutra: quem sabe responder de verdade é cada subclasse, que
 * SOBRESCREVE o método.
 *
 * A classe Aluno JÁ ESTA PRONTA: não precisa ser alterada.
 */
public class Aluno {

    // Situações possíveis na disciplina. São constantes da superclasse, então
    // as subclasses podem usar APROVADO, RECUPERACAO, ... diretamente.
    public static final String APROVADO = "Aprovado";
    public static final String RECUPERACAO = "Em recuperacao";
    public static final String REPROVADO = "Reprovado";
    public static final String NAO_AVALIADO = "Nao avaliado";

    // Data de referência do sistema: o "hoje" usado para saber quanto tempo de
    // curso já passou. É uma constante (e não a data da máquina) para o
    // relatório sair igual em qualquer computador e em qualquer dia.
    public static final int ANO_ATUAL = 2026;
    public static final int MES_ATUAL = 3;

    private String matricula;
    private String nome;
    private ArrayList<String> notas;

    // Início do curso: a ÚNICA informação de tempo guardada pelo sistema.
    // Todo o resto (ano, semestre, mês, prazo) é CALCULADO a partir daqui, e
    // cada subclasse calcula do jeito do seu curso.
    private int anoInicio;
    private int mesInicio;

    public Aluno(String matricula, String nome) {
        notas = new ArrayList<String>();
        this.matricula = matricula;
        this.nome = nome;
        // Quem acabou de ser criado é um calouro: começou o curso agora.
        this.anoInicio = ANO_ATUAL;
        this.mesInicio = MES_ATUAL;
    }

    public String getMatricula() {
        return matricula;
    }

    public String getNome() {
        return nome;
    }

    /**
     * As notas lançadas. Devolve uma CÓPIA da lista: se devolvesse a lista de
     * dentro do objeto, qualquer um poderia acrescentar nota por fora e driblar
     * a validação de lancarNota().
     */
    public ArrayList<String> getNotas() {
        return new ArrayList<String>(notas);
    }

    // Só as subclasses precisam do ano e do mês separados - é delas o trabalho
    // de converter a data em ano, semestre ou mês. Por isso protected, e não
    // public: o cliente pergunta getPeriodoAtual() ou getInicioDoCurso().
    protected int getAnoInicio() {
        return anoInicio;
    }

    protected int getMesInicio() {
        return mesInicio;
    }

    /** O início do curso no formato mes/ano (ex.: "03/2020"). */
    public String getInicioDoCurso() {
        return String.format("%02d/%d", mesInicio, anoInicio);
    }

    // ------------------------------------------------------------------
    // Métodos que cada subclasse SOBRESCREVE. A resposta abaixo é a de um
    // aluno generico, sem regra de curso definida: e por isso que um objeto
    // criado com "new Aluno(...)" aparece como "Nao avaliado" no relatorio.
    // ------------------------------------------------------------------

    /**
     * Guarda mais um lançamento de nota. As subclasses sobrescrevem este
     * metodo para validar o valor à sua maneira (número para técnico e
     * graduação, conceito para pós-graduação) e só então chamam
     * super.lancarNota(valor), que executa o codigo abaixo.
     */
    public void lancarNota(String valor) {
        if (valor == null || valor.trim().length() == 0) {
            System.out.println("[aviso] Nota vazia ignorada.");
            return;
        }
        notas.add(valor.trim());
    }

    public String getSituacao() {
        return NAO_AVALIADO;
    }

    public String getDesempenho() {
        return "Sem regra de avaliacao";
    }

    public String getPeriodoAtual() {
        return "-";
    }

    public int getTempoDecorrido() {
        return 0;
    }

    public int getPrazoMaximo() {
        return 0;
    }

    public String getUnidadeDePrazo() {
        return "periodo(s)";
    }

    // ------------------------------------------------------------------
    // Metodos escritos APENAS UMA VEZ aqui e que funcionam para qualquer
    // subclasse, porque se apoiam nos métodos acima. Quando uma subclasse
    // sobrescreve getTempoDecorrido(), é a versão dela que roda aqui dentro
    // graças ao polimorfismo.
    // ------------------------------------------------------------------

    /**
     * Define quando o aluno entrou no curso, a partir de um texto no formato
     * mes/ano (ex.: "03/2020") - do jeito que a informação chegaria de um
     * formulário ou de um banco de dados. Está escrito UMA única vez aqui e
     * serve para qualquer tipo de aluno: o que muda de um curso para outro não
     * é a data de entrada, é como cada um conta o tempo a partir dela.
     */
    public void setInicioDoCurso(String inicio) {
        if (inicio == null || !inicio.trim().matches("\\d{1,2}/\\d{4}")) {
            System.out.println(
                "[aviso] Inicio de curso invalido (use mes/ano, ex.: 03/2020). Ignorado: " + inicio
            );
            return;
        }

        String[] partes = inicio.trim().split("/");
        int mes = Integer.parseInt(partes[0]);
        int ano = Integer.parseInt(partes[1]);

        if (mes < 1 || mes > 12) {
            System.out.println("[aviso] Mes invalido em " + inicio + ". Inicio de curso ignorado.");
            return;
        }

        this.mesInicio = mes;
        this.anoInicio = ano;
    }

    public boolean estaNoPrazo() {
        return getTempoDecorrido() <= getPrazoMaximo();
    }

    public int getTempoRestante() {
        return Math.max(0, getPrazoMaximo() - getTempoDecorrido());
    }

    public String getPrazo() {
        return getTempoDecorrido() + "/" + getPrazoMaximo() + " " + getUnidadeDePrazo();
    }

    public void imprimirInformacoes() {
        System.out.printf(
            "%-10s %-22s %-10s %-22s %s%n",
            getMatricula(),
            getNome(),
            getPeriodoAtual(),
            getDesempenho(),
            getSituacao()
        );
    }

    // ------------------------------------------------------------------
    // Métodos úteis para as subclasses que trabalham com notas numéricas.
    // ------------------------------------------------------------------

    /**
     * Quantos meses completos se passaram entre o início do curso e a data de
     * referência. É a partir deste número que cada subclasse conta os ANOS, os
     * SEMESTRES ou os MESES do seu curso.
     */
    protected int getMesesDecorridos() {
        int meses = (ANO_ATUAL - anoInicio) * 12 + (MES_ATUAL - mesInicio);
        if (meses < 0) {
            return 0; // início de curso no futuro: o aluno ainda não começou.
        }
        return meses;
    }

    /** O texto representa um número entre 0 e 10? Aceita "8", "8.5" e "8,5". */
    protected boolean ehNotaNumericaValida(String valor) {
        if (valor == null)
            return false;

        String limpo = valor.trim().replace(',', '.');
        if (!limpo.matches("\\d+(\\.\\d+)?"))
            return false;

        double nota = Double.parseDouble(limpo);
        return nota >= 0.0 && nota <= 10.0;
    }

    /** Converte "8,5" ou "8.5" no numero 8.5. */
    protected double converterParaNumero(String valor) {
        return Double.parseDouble(valor.trim().replace(',', '.'));
    }
}

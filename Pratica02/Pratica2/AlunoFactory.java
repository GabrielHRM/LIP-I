/**
 * Fábrica de alunos.
 *
 * O cliente informa apenas o tipo; este é o único lugar do sistema que
 * decide qual subclasse deve ser instanciada.
 */
public class AlunoFactory {

    public static Aluno criar(String tipo, String matricula, String nome) {
        if (tipo == null) {
            System.out.println("[aviso] Tipo de aluno nao informado.");
            return null;
        }

        String chave = tipo.trim().toUpperCase();

        if (chave.equals("TECNICO")) {
            return new AlunoTecnico(matricula, nome);
        }

        if (chave.equals("GRADUACAO")) {
            return new AlunoGraduacao(matricula, nome);
        }

        if (chave.equals("POS")) {
            return new AlunoPosGraduacao(matricula, nome);
        }

        if (chave.equals("INTERCAMBIO")) {
            return new AlunoIntercambio(matricula, nome);
        }

        System.out.println(
            "[aviso] Tipo de aluno desconhecido. Tipos validos: "
            + getTiposDisponiveis()
        );
        return null;
    }

    public static String getTiposDisponiveis() {
        return "TECNICO, GRADUACAO, POS, INTERCAMBIO";
    }
}

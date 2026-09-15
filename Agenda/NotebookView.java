public class NotebookView {
    public static void main(String[] args){
        Notebook meuNotebook = new Notebook();

        System.out.println("========TESTE DE ADICIONAR 3 NOTAS=========");

        //Adicionando 3 notas ao array
        meuNotebook.storeNote("Estudar para a prova!");
        meuNotebook.storeNote("Java eh bao dmais!!!");
        meuNotebook.storeNote("244456789");

        meuNotebook.listNotes();

        System.out.println("==========TESTE DE ADICIONAR UMA NOTA JÁ EXISTENTE===========");

        meuNotebook.storeNote("244456789");

        System.out.println("==========TESTE DO NUMERO DE NOTAS NA AGENDA===========");

        //Tamanho atual: 3
        //Indices: 0-2
        System.out.println("Total de notas atuais da agenda: "+ meuNotebook.numberOfNotes());

        System.out.println("==========TESTE DE REMOVER NOTAS NA AGENDA===========");

        int indiceNota = 2;
        meuNotebook.removeNote(indiceNota);
        meuNotebook.removeNote(indiceNota);
        //Tamanho atual: 2
        //Indice: 0-1
        System.out.println("Total de notas atuais da agenda: " + meuNotebook.numberOfNotes());

        System.out.println("==========TESTE DE MOSTRAR NOTA ESPECIFICA===========");

        int i1 = 0, i2 = 1, i3 = 4, i4 = -1;

        meuNotebook.showNote(i1);
        meuNotebook.showNote(i2);
        meuNotebook.showNote(i3);
        meuNotebook.showNote(i4);

        System.out.println("==========TESTE DE LISTAR NOTAS===========");

        meuNotebook.listNotes();
    }
}

import java.util.ArrayList;

public class Notebook{
    private ArrayList<String> notes;

    public Notebook(){
        notes = new ArrayList<String>();
    }

    //Prefiro ter notas distintas para uma agenda
    //Ter a mesma mensagem duplicada polui a visualização de algo que tem como objetivo lembrar pendencias
    public void storeNote(String note){
        if(notes.contains(note)){
            System.out.println("Nota |" + note + "| já adicionada! Inserção cancelada.");
        }else{
            notes.add(note);
        }
    }

    public int numberOfNotes(){
        return notes.size();
    }
    
    public void removeNote(String note){
        if(notes.contains(note)){
            notes.remove(note);
        }else{
            System.out.println("Erro: A nota nao existe, ou ja foi removido, na agenda.");
        }
    }

    public void showNote(int noteNumber){
        if(noteNumber < 0){
            System.out.println("Valor inválido");
        }else if(noteNumber < numberOfNotes()){
            System.out.println(notes.get(noteNumber));
        }else{
            System.out.println("Valor inválido");
        }
    }
    /*for(Type element: collection){
        
    } */
    public void listNotes(){
        for(String note : notes){
            System.out.println(note);
        }
    }
}
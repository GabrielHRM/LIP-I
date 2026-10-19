package game.world.gobjects;
public class Player extends GameObject {
    public Player(int x, int y) { super(x, y); }
    public void moveTo(int newX, int newY) { setPosition(newX, newY); }
    @Override
    public char getSymbol() { return '@'; }
}

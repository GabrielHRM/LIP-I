package game.world.gobjects;
public abstract class GameObject {
    private int x;
    private int y;
    protected GameObject(int x, int y) { this.x = x; this.y = y; }
    public int getX() { return x; }
    public int getY() { return y; }
    protected void setPosition(int x, int y) { this.x = x; this.y = y; }
    public boolean isAt(int x, int y) { return this.x == x && this.y == y; }
    public abstract char getSymbol();
}

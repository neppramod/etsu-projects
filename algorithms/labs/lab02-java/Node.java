public class Node {
    private int x;
    public Node parent;

    public Node(int x)
    {
	this.x = x;
	this.parent = this;
    }

    public int getX()
    {
	return x;
    }
}

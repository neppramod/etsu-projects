public class Node {
    private int x;

    public Node parent;
    public int rank;

    public Node(int x)
    {
	this.x = x;
	this.parent = this;
	this.rank = 0;
    }

    public int getX()
    {
	return x;
    }
}

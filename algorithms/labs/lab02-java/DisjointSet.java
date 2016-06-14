import java.util.*;

public class DisjointSet {
    private HashMap<Integer, Node> nodeMap;

    public DisjointSet()
    {
	nodeMap = new HashMap<Integer, Node>();
    }

    public void MakeSet(int x)
    {
	//nodeMap[x] = new Node(x);
	nodeMap.put(x, new Node(x));
    }

    Node Find(int x)
    {
	Node node = null;

	if (nodeMap.containsKey(x))
	    node = nodeMap.get(x);

	if (node != null)
	    node = findRoot(node);

	return node;
    }

    Node findRoot(Node node)
    {
	if (node.parent == node)
	    return node;
	else
	    return findRoot(node.parent);
    }

    void Union(int x, int y)
    {
	Node xRoot = Find(x);
	Node yRoot = Find(y);

	// TODO: Merge based on rank
	if (xRoot != null && yRoot != null)
	    yRoot.parent = xRoot;
    }
    
    void printNodeMap()
    {
	for (int key : nodeMap.keySet()) {
	    Node node = nodeMap.get(key);
	    while (node.parent != node) {
		System.out.print(node.getX() + " ");
		node = node.parent;
	    }
	}
	
	System.out.println();
    }
}

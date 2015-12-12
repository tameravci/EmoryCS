      /*
      THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
      CODE WRITTEN BY OTHER STUDENTS. TAMER AVCI
      */
public class BSTIndex {
	private Node root;
	private class Node {
		private String key;
		private MovieInfo val;
		private Node left, right;
		public Node(String key, MovieInfo val) {
			this.key = key;
			this.val = val;
		}
	}

	public BSTIndex() {
		root = null;
	}

	public void insert(MovieInfo data) {
		root = insert(root, data.shortName, data);
	}

	private Node insert(Node x, String key, MovieInfo data) {
		if ( x == null )
			return new Node (data.shortName, data);
		int cmp = key.compareToIgnoreCase(x.key);
		if (cmp < 0)
			x.left = insert(x.left, key, data);
		else if (cmp > 0)
			x.right = insert(x.right, key, data);
		else
			x.val = data;
		return x;
	}

	public MovieInfo findExact(String key) {
		Node x = root;
		while ( x != null) {
			int cmp = key.compareToIgnoreCase(x.key);
			if (cmp < 0)
				x = x.left;
			else if (cmp > 0)
				x = x.right;
			else
				return x.val;
		}
		return null;
	}

	public MovieInfo findPrefix (String prefix) { 
		Node x = root;
		prefix = prefix.substring(0, prefix.length()-1);
		while (x != null) {
			if (startsWithIgnoreCase(x.key, prefix))
				return x.val;		
			int cmp = prefix.compareToIgnoreCase(x.key);			
			if (cmp < 0)
				x = x.left;
			else if (cmp > 0)
				x = x.right;
			else
				return x.val;
		}
		return null;
	}

	private boolean startsWithIgnoreCase(String str, String prefix) {
		str = str.toLowerCase();
		prefix = prefix.toLowerCase();
		return str.startsWith(prefix);
	}
}

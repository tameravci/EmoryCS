/*
THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR MATERIALS OTHER THAN THIS SEMESTER'S COURSE MATERIALS. TAMER AVCI
*/

class BookStore{
	
	private Book[] bookshelf;
        private Purchase[] shoppingcart;
        private int counterBook;
	private int counterPurchase;

	BookStore(int maxBookCount, int maxPurchaseCount) {
		bookshelf = new Book[maxBookCount];
       		shoppingcart = new Purchase[maxPurchaseCount];
		counterBook = 0;
		counterPurchase = 0;
	}
 
	public void addBook(String title, String author, double price, int availableCount) {		
		Book newBook = new Book(title, author, price,availableCount);	
		for (int i = 0; i < counterBook; i++) {
			if (bookshelf[i].equals(newBook)) {
				while (availableCount>0)  {
					bookshelf[i].increaseAvailableCount();
					availableCount--;
				}	
				return;
        	       }
		}
		if (bookshelf[bookshelf.length-1]!=null) {
			System.out.println("Sorry, the Book Store is full");
			return;
		}
		bookshelf[counterBook] = newBook;
		counterBook++;
	} 
	
	public void removeBook(int index) {
		bookshelf[index] = null;
		for (int i = index; i<bookshelf.length-1; i++) {
			bookshelf[i] = bookshelf[i+1];
		}
		counterBook--;
	}
	
	public void printBookStore() {
		System.out.println("--------");
		System.out.println("Book Store at Emory");
		System.out.println("These are the books still available:");
		for (int i = 0; i < counterBook; i++) {
			System.out.println(bookshelf[i].toString());
		}
		System.out.println("--------");
		System.out.println("These are the purchases made:");
		for (int i = 0; i < counterPurchase; i++) {
			System.out.println(shoppingcart[i].toString());	
		}
		System.out.println("--------");
	}

	public void buy(String name, String title, String author, double max_price) {
		for (int i = 0; i < counterBook; i++) {
			if (title.equals(bookshelf[i].getTitle()) && author.equals(bookshelf[i].getAuthor()) && max_price >= bookshelf[i].getPrice()) {
				if (counterPurchase >= shoppingcart.length) {
					System.out.println("Sorry, you've reached the maximum Purchase count");	
				}			
				else {				
					shoppingcart[counterPurchase] = new Purchase(name, bookshelf[i]);
					bookshelf[i].decreaseAvailableCount();
					if (!bookshelf[i].isAvailable())
						removeBook(i);
					System.out.println("Purchase completed!");
					System.out.println(shoppingcart[counterPurchase].toString());
					counterPurchase++;
					return;
				}
			}
		}
		System.out.println("Sorry " + name + "! Your purchase cannot be completed at this time!");
        }
}

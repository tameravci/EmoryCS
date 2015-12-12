class Purchase{

	private String customerName;
	private Book book;

	public Purchase(String customerName, Book book){
		this.customerName = customerName;
		this.book = book;
	}
		
	public String getCustomerName(){
		return customerName;
	}
	
	public Book getBook(){
		return this.book;
	}
	
	/**
	This method returns a String describing this purchase object
	*/		
	public String toString(){
		String str = "Customer's Name: " + customerName + 
					 "\nPurchased Book: " + book.toString();
		return str;
	
	}
		
}

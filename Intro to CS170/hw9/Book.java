class Book{

	private String title;
	private String author;
	private double price;
	private int availableCount;
	
	Book(){
		title = "";
		author = "";
		price = 0.0;
		availableCount = 0;
	
	}

	Book(String title, String author, double price, int availableCount){
		this.title = title;
		this.author = author;
		this.price = price;
		this.availableCount = availableCount;
		
	}
	
	Book(Book other){
	
		this.title = other.title;
		this.author = other.author;
		this.price = other.price;
	}
		
	public void setTitle(String title){ 
		this.title = title;
	}
	
	public void setAuthor(String author){
		this.author = author;
	}
	
	public void setPrice (double price){
		this.price = price;
	}
	
	public String getTitle(){
		return this.title;
	}
	
	
	public String getAuthor(){
		return this.author;
	}
	
	public double getPrice(){
		return this.price;
	}
	
	public int getAvailableCount(){
		return availableCount;
	}
	
	public boolean isAvailable(){
		return (availableCount > 0);
	}
	
	public void decreaseAvailableCount(){
		availableCount--;
	}
	
	public void increaseAvailableCount(){
		availableCount++;
	}
	
	
	
	/**
	This method checks if a given book object is equal to this object
	*/
	public boolean equals(Book other){
		return (this.title.equals(other.title) && this.author.equals(other.author) && this.price == other.price);	
	}
	
	/**
	This method returns a String describing this book object
	*/
	public String toString(){
		return "Title: "+ this.title + "\tAuthor: "+this.author + "\tPrice: "+ this.price + "\tAvailable: " + this.availableCount;
	
	}
	
	
}

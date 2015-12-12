/*
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
A TUTOR OR CODE WRITTEN BY OTHER STUDENTS.
Nicholas Cuccia & Tamer Avci
Collaboration Statement: Nicholas worked mostly on the FaceSpace Class, Tamer Worked mostly on the BSTFaceSpace Class, we both created the Profile Class
*/
import java.util.InputMismatchException;
import java.util.Scanner;


public class FaceSpace {

	public static void main( String [ ] args )
	{
		BSTFaceSpace t = new BSTFaceSpace( );		
		System.out.println("Welcome to FaceSpace! Here are the current options!");
		System.out.println("");

		Scanner input = new Scanner(System.in);
		
		while(true){ //Menu system that allows user to choose a command
		    System.out.println("\n List of Commands:");
		    System.out.println("\t a) Add Account");
		    System.out.println("\t b) Update Account");
		    System.out.println("\t c) Add Friend to a user");
		    System.out.println("\t d) Remove Friend from a user");
		    System.out.println("\t e) Search for a user");
		    System.out.println("\t f) Find the Shortest Path Between 2 Users");
		    System.out.println("\t g) Remove a User Profile");
		    System.out.println("\t h) Quit");
		    System.out.println("Please enter the letter corresponding with the command you would like to perform");
			String choice = input.nextLine().trim().toLowerCase();

//------------------------------Choice a-Add Account---------------------------------------			
			if(choice.equals("a)")||choice.equals("a")) { //done
			    String name, location;
			    int age=0;
			    System.out.println("Please enter the name of the account you would like to make: " );
			    name = input.nextLine().trim();
			    
			    Profile temp = t.search(name);
			    boolean quit = false;
			    while(temp!= null) { //Checks if the name already exists
			        System.out.println("The account name you are trying to create already exists!");
			        System.out.println("Please enter a new account name, or enter q to return to the main menu.");
			        name = input.nextLine().trim();
			        if (name.toLowerCase().equals("q")) { //Allows user to quit to main menu at any time
			            quit = true;
			            break;
			        }
			        temp = t.search(name);
			    }
			    while (quit==false) {
    			    System.out.println("Please enter the age of the person you are creating an account for: ");
    			    while(!input.hasNextInt()) { //Makes user enter an Integer
    			    	System.out.println("This is not an int, please input an int.");
    			    	input.next();
    			    }
    			    age = input.nextInt();	    			    
    			    System.out.println("Please enter the location of the person you are creating and account for: ");
    			    input.nextLine();
    			    location = input.nextLine().trim(); 
    			    t.insert(new Profile(name, age, location)); //Creates a new account
    			    System.out.println(name+" has been added to the system!");
    			    System.out.println("The Account has been created! Press any key to continue");
    		        input.nextLine();
    			    break;
			    }
			}
//------------------------------Choice b-Update-------------------------------------------
			if(choice.equals("b)")||choice.equals("b")) { //done
			    boolean quit = false;
			    String name, location, tempName, tempChoice,relationship;
			    int age;
			    System.out.println("Please input the name of the profile you would like to update.");
			    name = input.nextLine().trim();
			    Profile temp;
			    temp = t.search(name);  //Pulls up the account from the BST
			    while(temp==null){ //If account doesn't exist, forces user to enter a new account
			        System.out.println("The profile you have entered does not exist!");
			        System.out.println("Please enter an existing profile, or press q to return to the main menu");
			        name=input.nextLine().trim();
			        if (name.toLowerCase().equals("q")){
			            quit = true;
			            break;
			        }
			        temp = t.search(name);
			    }
			   
			    while(quit == false) { //done
			       System.out.println("\n List of Commands:");
		           System.out.println("\t a) Change name of Profile");
		           System.out.println("\t b) Change Age of User");
		           System.out.println("\t c) Change Location of User");
		           System.out.println("\t d) Change relaionship Status of User");
		           System.out.println("Please enter the letter corresponding with the command you would like to perform");
		           tempChoice=input.nextLine().trim().toLowerCase();
		           //------------------------------Choice a-Name---------------------------------------------
		           		if(tempChoice.equals("a)")||tempChoice.equals("a")) {
			                System.out.println("What is the new name for the account?");
			                tempName = input.nextLine().trim();
			                temp=t.search(tempName);
			                while(temp!= null) {//Checks if the name is already taken
			                    System.out.println("The account name you are trying to create already exists!");
			                    System.out.println("Please enter a new account name, or enter q to return to the main menu.");
			                    tempName = input.nextLine().trim();
			                    if (tempName.toLowerCase().equals("q")) {
			                        quit = true;
			                        break;
			                    }
			                    temp=t.search(tempName);
			                }
			                if (quit == false) {  //Otherwise, 'updates' the BST using the updateName method
			                	t.updateName(name,tempName);
			                	System.out.println("Name Updated: Press any key to continue");
			                }
			                else System.out.println("Name not Updated: Press any key to continue");
    		        		input.nextLine();
		            	}
		            //------------------------------Choice b-Age----------------------------------------------	
		           		if(tempChoice.equals("b)")||tempChoice.equals("b")) {
			                System.out.println("What is the new age?");
		    			    while(!input.hasNextInt()) {  //Makes sure the the information entered is an integer
		    			    	System.out.println("This is not an int, please input an int.");
		    			    	input.next();
		    			    }
			                age = input.nextInt();
			                t.updateAge(name, age); //Updates age
			                input.nextLine();
			                System.out.println("Age Updated: Press any key to continue");
    		        		input.nextLine();
		            	}
		            //------------------------------Choice c-Location-------------------------------------------	
		           		if(tempChoice.equals("c)")||tempChoice.equals("c")) {
			                System.out.println("What is the new location of the user?");
			                location = input.nextLine().trim();
			                t.updateLocation(name, location);  //Updates location
			                System.out.println("Location Updated: Press any key to continue");
    		        		input.nextLine();
		            	}
		            //------------------------------Choice d-Relationship-------------------------------------------	
		           		if(tempChoice.equals("d)")||tempChoice.equals("d")) {
			                System.out.println("Please choose from the following options:");
			                System.out.println("\t a) Add/Update Relationship (Will end previously existing relationship)");
			                System.out.println("\t b) Remove Relationship");
			                tempChoice= input.nextLine().trim().toLowerCase();
			                //------------------------------Choice a-Update-------------------------------------------
    		           		if(tempChoice.equals("a)")||tempChoice.equals("a")) {
    			                System.out.println("With whom would you like "+name+" to be in a relationship with?");
    			                relationship = input.nextLine().trim();
    			                temp=t.search(relationship);
    			                while(temp== null) { //Checks if acount exists
    			                    System.out.println("The account name you are trying to find does not exist");
    			                    System.out.println("Please enter a new account name, or enter q to return to the main menu.");
    			                    relationship = input.nextLine().trim();
    			                    if (relationship.toLowerCase().equals("q")) {
    			                        quit = true;
    			                        break;
    			                    }
    			                    temp = t.search(name);
    			                }
    			                boolean prev=false;
    			               	if ((temp.relationship!=null)&&(quit!=true)) prev = true;
    			                while(prev==true) { //Checks if the person chosen is already in a relationship
    			                    System.out.println(relationship+" is already in a relationship!");
    			                    System.out.println("Please enter a new account name, or enter q to return to the main menu.");
    			                    relationship = input.nextLine().trim();
    			                    if (relationship.toLowerCase().equals("q")) {
    			                        quit = true;
    			                        break;
    			                    }
    			                    temp = t.search(name);
    			                }
    			                if (quit == false) {
    			                	t.relationship(name, relationship);  //Updates the relationship status of both individuals
    			                	System.out.println(name +" is now in a relationship with "+relationship);
    			                	System.out.println("Press any key to continue");
    		        				input.nextLine();
    			                }

    		            	}
    		            	//------------------------------Choice b-Remove-------------------------------------------
    		           		if(tempChoice.equals("b)")||tempChoice.equals("b")) {
    		           			temp = t.search(name);
    		           			if (temp.relationship==null) { //Responds in a snappy fashion if user doesn't have a relationship
    		           				System.out.println("What relationship are you talking about.  You don't have one currently.");
    		           				System.out.println("Press any key to continue");
    		           				input.nextLine();
    		           			}
    		           			else { //Otherwise performs desired operation
    		           				System.out.println("Sorry about your breakup");
    		           				t.removeRelationship(name);
    		           				System.out.println("Press any key to continue");
    		           				input.nextLine();
    		           			}
    		            	}
		            	}
		           		break;
			    }
			    
			}
//------------------------------Choice c-Add Friend----------------------------------------
			if(choice.equals("c)")||choice.equals("c")) { //done
			    String firstUser, secondUser;
			    Profile temp;
			    boolean quit =false;
			    
				System.out.println("Please input the name of the name of the profile you want to add a friend to!");
			    firstUser=input.nextLine().trim();
			    temp=t.search(firstUser);
			    
                while(temp== null) {  //Checks if account exists
                    System.out.println("This account does not exist!");
                    System.out.println("Please enter a new account name, or enter q to return to the main menu.");
                    firstUser = input.nextLine().trim();
                    if (firstUser.toLowerCase().equals("q")) {
                        quit = true;
                        break;
                    }
                    temp = t.search(firstUser);
                }

                while(quit==false){
				    System.out.println("Please input the name of the person who should be his/her friend!");
				    secondUser=input.nextLine().trim();
				    
				    temp=t.search(secondUser);
				    if (firstUser.equals(secondUser)){  //If you try to add yourself as a friend, prevents you from doing that
				    	System.out.println("You can't be friends with yourself. That is just sad.");
				    	while(firstUser.equals(secondUser)) {
		                    System.out.println("Please enter a new account name for your friend, or enter q to return to the main menu.");
		                    secondUser = input.nextLine().trim();
		                    if (secondUser.toLowerCase().equals("q")) {
		                        quit = true;
		                        break;
		                    }
		                    temp = t.search(secondUser);
		                }
				    	if (quit) break;
				    	
				    }
	                while(temp== null) {
	                    System.out.println("This account does not exist");
	                    System.out.println("Please enter a new account name, or enter q to return to the main menu.");
	                    secondUser = input.nextLine().trim();
	                    if (secondUser.toLowerCase().equals("q")) {
	                        quit = true;
	                        break;
	                    }
	                    temp = t.search(secondUser);
	                }
	                if (quit == true) break;
	                t.addFriend(firstUser, secondUser); //Adds users to each other friends list (unless already friends)
	                System.out.println(firstUser+" and "+secondUser +" are friends!");
	                System.out.println("Press any key to continue");
    		        input.nextLine();
	                break;
                }
                
			    
			}
//------------------------------Choice d-Remove Friend--------------------------------------
			if(choice.equals("d)")||choice.equals("d")) { //done
			    System.out.println("So you want to remove a friend?  First enter the name of your profile: ");
			    String firstUser, secondUser;
			    Profile temp;
			    boolean quit =false;
			    firstUser=input.nextLine().trim();
			    temp=t.search(firstUser);
			    
                while(temp== null) {  //Checks if account exists
                    System.out.println("This account does not exist!");
                    System.out.println("Please enter a new account name, or enter q to return to the main menu.");
                    firstUser = input.nextLine().trim();
                    if (firstUser.toLowerCase().equals("q")) {
                        quit = true;
                        break;
                    }
                    temp = t.search(firstUser);
                }
                while(quit==false){
				    System.out.println("Please input the name of the person who you will no longer be friends with!");
				    secondUser=input.nextLine().trim();
				    
				    temp=t.search(secondUser);
				    if (firstUser.equals(secondUser)){ //Prevents a user from trying to remove themself from their friendlist
				    	System.out.println("You can remove yourself as a friend. You will alwyas love yourself!");
				    	while(firstUser.equals(secondUser)) {
		                    System.out.println("Please enter a new account name for your friend you would like to remove, or enter q to return to the main menu.");
		                    secondUser = input.nextLine().trim();
		                    if (secondUser.toLowerCase().equals("q")) {
		                        quit = true;
		                        break;
		                    }
		                    temp = t.search(secondUser);
		                }
				    	if (quit) break;
				    	
				    }
	                while(temp== null) { //Checks if account exists
	                    System.out.println("This account does not exist");
	                    System.out.println("Please enter a friend to remove that does exist, or enter q to return to the main menu.");
	                    secondUser = input.nextLine().trim();
	                    if (secondUser.toLowerCase().equals("q")) {
	                        quit = true;
	                        break;
	                    }
	                    temp = t.search(secondUser);
	                }
	                if (quit == true) break;
	                t.removeFriend(firstUser, secondUser); //Removes friend
	                System.out.println("Press any key to continue");
    		        input.nextLine();
	                break;
                }
			    
			    
			}
//------------------------------Choice e-Search--------------------------------------------
			if(choice.equals("e)")||choice.equals("e")) { //done
			    String key;
			    Profile temp;
			    System.out.println("Please enter the name of the profile you would like to find.");
			    key = input.nextLine().trim();
			    temp = t.search(key);  //Looks for the account
			    System.out.println();
			    System.out.println("-------------------------------------");
			    if (temp == null) System.out.println("Account does not exist.");
			    else temp.becomeString();
			   	System.out.println("Press any key to continue");
    		    input.nextLine();
			}
//------------------------------Choice f-Degree--------------------------------------------
			if(choice.equals("f)")||choice.equals("f")) { //done
			    String firstUser, secondUser;
			    boolean quit = false;
			    Profile temp;
				System.out.println("Please input the first user: ");
				firstUser=input.nextLine().trim();
				temp = t.search(firstUser);
                while(temp== null) { //Checks if account exists
                    System.out.println("This account does not exist!");
                    System.out.println("Please enter a new account name, or enter q to return to the main menu.");
                    firstUser = input.nextLine().trim();
                    if (firstUser.toLowerCase().equals("q")) {
                        quit = true;
                        break;
                    }
                    temp = t.search(firstUser);
                }
                if(!quit){
					System.out.println("Please input the second user: ");
					secondUser=input.nextLine().trim();
					System.out.println();
			    	while(firstUser.equals(secondUser)) {  //Checks if person is yourself
	                    System.out.println("Please enter an account name that is not yourself, or enter q to return to the main menu.");
	                    secondUser = input.nextLine().trim();
	                    if (secondUser.toLowerCase().equals("q")) {
	                        quit = true;
	                        break;
	                    }
	                    temp = t.search(secondUser);
	                }
			    	if(!quit) {
			    		temp = t.search(secondUser);
			    		while(temp== null) {
		                    System.out.println("This account does not exist!");
		                    System.out.println("Please enter a new account name, or enter q to return to the main menu.");
		                    secondUser = input.nextLine().trim();
		                    if (secondUser.toLowerCase().equals("q")) {
		                        quit = true;
		                        break;
		                    }
		                    temp = t.search(secondUser);
			    		}
		                if (!quit){
							int deg = t.degreeSeperation(firstUser,secondUser);  //Finds how far apart the users are (via shortest path)
							System.out.println();
							
							if (deg<0) System.out.println("Users are not connected by friends.");
							else if (deg == 1) System.out.println("These users are currently friends, so they have no degree of seperation.");
							else System.out.println("The users are sepereated by "+ (deg-1)+" friends.");
		                }
			    	}
                }
                System.out.println("Press any key to continue");
    		    input.nextLine();
			}
//------------------------------Choice g-Delete-------------------------------------------
			if(choice.equals("g)")||choice.equals("g")) { //done
			    String removeUser;
			    boolean quit = false;
			    Profile temp;
				System.out.println("Please input the name of the profile you would like to delete: ");
				removeUser=input.nextLine().trim();
				temp = t.search(removeUser);
                while(temp== null) {  //Checks if user exists
                    System.out.println("This account does not exist!");
                    System.out.println("Please enter an existing account to delete, or enter q to return to the main menu.");
                    removeUser = input.nextLine().trim();
                    if (removeUser.toLowerCase().equals("q")) {
                        quit = true;
                        break;
                    }
                    temp = t.search(removeUser);
                }
                if(!quit){  //If they exist, remove the account
			    	t.removeProfile(removeUser);
			    	System.out.println(removeUser+" has been removed. ");
                }
                System.out.println("Press any key to continue");
    		    input.nextLine();
			}
//------------------------------Choice h-Quit---------------------------------------------
			if(choice.equals("h)")||choice.equals("h")) { //done
			    break;
			}
		}
		
		
	}
}
	

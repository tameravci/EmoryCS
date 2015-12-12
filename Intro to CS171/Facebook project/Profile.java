/*
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
A TUTOR OR CODE WRITTEN BY OTHER STUDENTS.
Nicholas Cuccia & Tamer Avci
Collaboration Statement: Nicholas worked mostly on the FaceSpace Class, Tamer Worked mostly on the BSTFaceSpace Class, we both created the Profile Class
*/
import java.util.ArrayList;


public class Profile { // Profile class
	String fullName;
	int age;
	String location;
	String relationship;	
	ArrayList<Profile> friends = new ArrayList<Profile> ();
	Profile parent;
	
	public Profile(Profile user1, Profile user2) { // constructor to find the degree separation
	    fullName = user1.fullName;
	    friends=user1.friends;
	    parent = user2;
	}
	public Profile(String name, int a, String loc) { // constructor
		fullName = name;
		age = a;
		location = loc;
	}
    
    public void becomeString() { // for printing purposes
        System.out.println("Profile Name: "+ fullName);
        System.out.println("Age: "+age);
        System.out.println("Location: "+location);
        if (relationship==null) System.out.println("Relationship Status: Single");
        else System.out.println("Currently in a relationship with " + relationship);
        ArrayList<String> names = new ArrayList<String> ();
        for (int i = 0 ; i< friends.size();i++) {
            names.add(friends.get(i).fullName);
        }
        System.out.println("Friends List: "+names.toString());
    }


}

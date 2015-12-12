/*
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
A TUTOR OR CODE WRITTEN BY OTHER STUDENTS.
Nicholas Cuccia & Tamer Avci
Collaboration Statement: Nicholas worked mostly on the FaceSpace Class, Tamer worked mostly on the BSTFaceSpace Class, we both created the Profile Class
*/
import java.util.ArrayDeque;
import java.util.ArrayList;
public class BSTFaceSpace {

    private Node root; //The root of the BST

    private class Node { // node class

        private String key;  //The name of the account

        private Profile val;  //The Profile of the account

        private Node left, right;

        public Node(String key, Profile val) { // value is profile, key is name

            this.key = key;

            this.val = val;

        }

    }

    ArrayList<Profile> delete = new ArrayList<Profile> (); // this arraylist helps us remove a user from the system

    public BSTFaceSpace() { // constructor

        root = null;

    }

    public void insert(Profile data) { // adding a user to the system
        if(search(data.fullName)==null)
            delete.add(data); //Adds to the arrayList (meant to keep track of users for deletion purposes)
        root = insert(root, data.fullName, data); //Inserts Node onto BST
    }

    private Node insert(Node x, String key, Profile data) { // adding a user to the system

        if ( x == null ) return new Node (data.fullName, data);  //If no nodes exists, creates a new root node

        int cmp = key.compareToIgnoreCase(x.key);  //Determines if key is greater than or less then current node

        if (cmp < 0)

            x.left = insert(x.left, key, data);

        else if (cmp > 0)

            x.right = insert(x.right, key, data);

        else

            x.val = data;

        return x;

    }

    public Profile search(String key) { // searching a user

        Node x = root;

        while ( x != null) {

            int cmp = key.compareToIgnoreCase(x.key);

            if (cmp < 0) //if the current node is greater than the key, go to the left node

                x = x.left;

            else if (cmp > 0) //If the current node is less than the key, go to the right node

                x = x.right;

            else  //If the current node is the key, return the node

                return x.val;

        }

        return null;

    }


    public void addFriend(String user1, String user2) { // adding a friend to one user's profile
        for(int i=0; i<search(user1).friends.size(); i++) {
            if(search(user1).friends.get(i)==search(user2)) { //Checks that the users aren't already friends
                System.out.println("The user is already friends with the person.");
                return;
            }
        }
        search(user1).friends.add(search(user2));
        search(user2).friends.add(search(user1)); // adding them both to each other
    }
    
    public void removeFriend(String user1, String user2) { // removing a friend from a user's profile
        for(int i=0; i<search(user1).friends.size(); i++) {
            if(search(user1).friends.get(i)==search(user2)) {  //Attempts to find both users in the adj list and remove them
                search(user1).friends.remove(search(user2));
                search(user2).friends.remove(search(user1));
                System.out.println(user1+" and "+user2+" are no longer friends.");
                return;
            }
        }
        System.out.println("The user does not have them in their friends list.");            
    }
    
    public void updateName(String oldname, String newname) { // changing the name of a user: requires to re-construct the binary search tree using the delete ArrayList because key changes
        String relation;
        relation = search(oldname).relationship;
        if (relation != null) search(relation).relationship = newname; 
        search(oldname).fullName = newname;
        root = new Node(delete.get(0).fullName,delete.get(0));
        for (int i=1; i<delete.size(); i++)
            insert(delete.get(i));
    }
    
    public void updateAge(String name, int newAge) { // changing the age of a user
        search(name).age = newAge;
    }
    
    public void updateLocation(String name, String newLoc) { // changing the location of a user
        search(name).location = newLoc;
    }
    
    public void relationship(String user1, String user2) { // adding a relationship to a user profile
        if (search(user1).relationship != null) search(search(user1).relationship).relationship=null;
        search(user1).relationship = user2;
        search(user2).relationship = user1;
    }
    
    public void removeRelationship(String user1) { // removing a relationship from a user profile
            String user2 = search(user1).relationship;
            search(user1).relationship = null;
            search(user2).relationship = null;        
    }
    
    
    public int degreeSeperation(String user1, String user2) {  // finding the amount of separation using a BFS
        int counter = 0;
        ArrayList<Profile> path = new ArrayList<Profile> ();
        ArrayDeque<Profile> queue = new ArrayDeque<Profile> ();
        ArrayDeque<String> names = new ArrayDeque<String> ();
        queue.add(search(user1));
        path.add(search(user1));
        while(!queue.isEmpty()) { // using a queue to execute BFS
             Profile initial = queue.remove();
             if(initial.fullName == search(user2).fullName) {
            	 Profile x;
                 for (x=initial; x.parent!=null; x=x.parent) {
                    names.push(x.fullName);
                     counter++;
                 }
                 names.push(x.fullName);
                 System.out.println("The path we took to connect the two users is: ");
                 while(!names.isEmpty()) {
                    System.out.print(names.pop());
                    if (!names.isEmpty()) System.out.print(" to ");
                 }
                 return counter;
             }
             else {
             boolean existence = false;
                 for(int i=0; i<initial.friends.size(); i++) {
                	 existence = false; // resetting
                         for(int a=0; a<path.size(); a++) {
                             if(initial.friends.get(i).fullName.equals(path.get(a).fullName))
                                 existence = true;
                         }
                         if (!existence){
                             queue.add(new Profile(initial.friends.get(i), initial));
                             path.add(new Profile(initial.friends.get(i), initial));
                         }
                 }
             }
        }
        return -1;
    }
    
    public void removeProfile(String user1) { // removing a profile: requires to re-construct the binary search tree using the delete ArrayList
        delete.remove(search(user1));  //Removes the user1 profile fro the delete ArrayList
        while(search(user1).friends.size()!=0)  //Removes user1 from his friend's adj list
            removeFriend(search(user1).fullName,search(user1).friends.get(0).fullName);
        if (search(user1).relationship!=null) removeRelationship(user1); //If user1 has a relationship, removes it
        if (delete.size()!=0) root = new Node(delete.get(0).fullName, delete.get(0));  //If other users exist, re-compiles BST using them
        else root = null; //If no other users exist, root becomes null
        for (int i=0; i<delete.size(); i++)  //Places all the other users into the BST
            insert(delete.get(i));
        }
    }
    

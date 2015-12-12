/*
THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR MATERIALS OTHER THAN THIS SEMESTER'S COURSE MATERIALS. TAMER_AVCI
*/

import java.util.*;
public class GooseGame {
    public static int roll() { // a method to roll the dice
        int a  = (int) (1+ (Math.random() * 6) ); // first dice 1-6
        int b  = (int) (1+ (Math.random() * 6) ); // second dice 1-6
        int rollSum = a + b;
        return rollSum;
    }

    public static boolean isGeese(int[] a, int[] b) { // a method to determine if a player arrived to a goose square
        for (int i = 0; i < a.length; i++) { // changing the player
            for (int c=0; c < b.length; c++) { // keeping the player constant looking for Goose squares
                if ( a[i] == b[c]){ 
                    return true;
                }
            }
        }
        return false;
    }
    
    public static int nextGoose(int[] a, int[] b) { // a method that returns the next Goose square
        for (int i=0; i<a.length; i++) { // finding which player landed on a goose square
            for (int x=0; x<b.length; x++) { // finding which goose square is occupied
                if (a[i]==b[x]) { 
                    if (b[x]==63) // this if-statement is to prevent crossing the Geese array boundaries and hence an Exception error
                        return b[x];
                    else
                        return b[++x];  // returning the next goose square
                }
            }
        }
        return a[0]; // this is irrelevant in the main method line: 47 under the if isGoose condition, this will never be returned anyway
    }              

    public static void printGame(int[] a, int [] b) {  // a method to print the player's number, what s/he rolled and her/his new position
                                                       // this method also includes who's next & determines if anybody has won (no separate methods)
        outerloop:
            for (int y=0; y < a.length; y++) {   // this loop will determine who's next and enable players to play in correct order
                int x = roll(); // rolling the dice and assigning it to an integer
                System.out.println("Player " + y + " rolled " + x + " and now is in position " + (a[y]+ x)); // will print what's happened so far
                a[y] += x; // we have to save the player's new location
                while (isGeese(a, b)) { // checking if the new location is a Goose square (this must be while not if!!)
                    System.out.println("From Goose to Goose, I roll the dice because it's my turn!"); // yes!
                    a[y] = nextGoose(a,b); // we must go to the next Goose square
                    System.out.println("Player " + y + " will now teleport to " + a[y]); // printing the location (not necessary)
                    if (a[y]>=63) { // in case the player already passed the 63
                        System.out.println("Player " + y + " has won!!");
                        break outerloop; // we must exit the game
                    }
                    int e = roll(); // if the player has not passed the 63 yet, s/he must roll the dice again (note thatwe're still under the if (isGeese) condition
                    System.out.println("Player " + y + " rolled " + e + " and now is in position " + (a[y]+ e)); // new location
                    a[y] += e; // we have to save the player's final location
                }
                if (a[y]>=63) { // checking if the final location is equal or greater than 63
                    System.out.println("****  Player " + y + " has won!! ****");
                    break outerloop; // if yes, we must exit the game
                }
            } 
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.println("*** Welcome to Goose Game. How many players? ***"); // asking for number of players
        int playerNum = input.nextInt();
        while (playerNum < 2) { // complaining if there are less than 2 players
            System.out.println("This game can only be played by two or more players. How many players?");
            playerNum = input.nextInt();
        }
        int[] playerList = new int[playerNum]; // declaring an array of integers for players
        System.out.println(playerNum + " players are playing the Goose Game, good luck everybody!");
        int[] geese = {5,9,14,18,23,27,32,36,41,45,50,54,63}; // declaring and initializing an array for the locations of geese
        for (int i=0; i < playerNum; i++) { // initializing every player's initial location to 0
           playerList[i] = 0;
        }
        boolean b=true; 
        outerloop: // this crucial magic loop will actually make the computer play the game as long as players did not reach 63. 
                   // without this, the game would run from player 0 to player n and then would stop
            while (b) {
                for (int i=0; i<playerList.length; i++) { 
                    if (playerList[i]>=63)  { // constantly checking whether any player passed 63
                        b = false; // if yes, the boolean will set to false and the printGame method will not be processed again
                        break outerloop; 
                    }
                    else
                    b = true;  
                }
                printGame(playerList, geese); // running the method until someone reaches 63
            }
    }
}

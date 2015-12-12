Read Me File:
	Instructions:
	Once the program is launched you will be brought to the main menu.  Here you have 8 options.
		 a) Add Account
		 	Allows you to create a new account.  Will ask you for the name you want to make the account, along with the age and location of the person in the account.
		 b) Update Account
			 a) Change name of Profile
			 	Allows you to change the name of an already existing account.  This is an extra feature that we decide to create.  We found that once we had a delete method for an account, a name change method was easy.
			 b) Change Age of User
			 	Allows you to update the Age of an exisiting account
			 c) Change Location of User
			 	Allows you to update the location of a current account
			 d) Change relaionship Status of User
			        a) Add/Update Relationship (Will end previously existing relationship)
			        	Allows you to create a realtionship between 2 existing accounts.
         			b) Remove Relationship
         				Allows you to end a relationship that exists between 2 accounts.
		 c) Add Friend to a user
		 	Allows you to add a friend to an account (Will also add you as a friend to their account)
		 d) Remove Friend from a user
		 	Allows you to remove a friend from an account (Will also remove you as a friend from their account)
		 e) Search for a user
		 	Allows you to search for a user profile.  If the profile is found, all information about the profile is printed.
		 f) Find the Shortest Path Between 2 Users
		 	Allows you to find how far apart 2 profiles are seperated.  If the profiles are friends it will print "These accounts are already friends."  If they are not friends it will print "These profile are seperated by n friends".  If they are not connected it will print "These profiles are not connceted".
		 g) Remove a User Profile
		 	Allows you to delete an existing profile.  This also remove the profile from anyones friend list, and end and relationship that exists with the profile.
		 h) Quit
		 	Allows you to quit the program.
		 	
	What we have learned:
		Throughout this program we have mostly learned about the complexity of something like Facebook.  We had never before relized how complicated it could be to just update a name of a profile, or delete and account.  The biggest issue we faced when making this program was changing the name of the account.  Because our Binary Search tree used the Names of the account as the key, changing the name of the account meant we had to delete a node on the BST and add a new one.  This was the hardest accomplishment that we have had. The second issue we faced was error handeling.
	
	Unique Parts of our Program:
		We have a delete account option!
		We have the ability to update the name of an account!
		We have a relationship option!
	

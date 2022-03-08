#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
/**
 *
 * A password strength meter and a default password generator, 
 * as defined in the CS221 course website for Project 1.
 *
 */

bool compare(const char *password, const char *username)
{
    while (*password != '\0' && *username != '\0')// loops through username and password to see it the username is in the pw
    {
        if (*password != *username) {//if the chain of common letters is broken return false becuase that means the username is not in the password
            return false;
        }

        password++;//helps loop through pw array
        username++;//heklps loop through username array
    }

    return true;//else return ture meaning that the username is in the password
}

//looks for a common char
bool UserInPass(const char* password, const char* username) // loops through pw until there is a letter that is in both username and password
{
    while (*password != '\0')
    {
        if ((*password == *username) && compare(password, username)) { // if there is a letter in the password that is also in the username call compare to see if the whole username is in the password
            return true;//return true if compare returns true because that means the username is in the passowrd
        }
        password++;
    }

    return false;
}

bool isStrongPassword(const char * username, const char * password) {
	//TODO: your code goes here.
    int size = 0;//makes sure size requirement for pw is met
    int hasUpper = 0; //makes sure pw has an upper case letter
    int hasLower = 0;//makes sure pw has a lower case letter
    int hasNum = 0;//makes sure pw has a num
    int letterCombo = 0;//makes sure pw has at leasdt 4 letters in a row
    int consecLetter = 0;//makes sure pw has at leasdt 4 letters in a row
    int nonLetterOrNum = 0;//makes sure the pw only contains numbers and letters
    
    bool x = UserInPass(password,username);

    while(*password != '\0') //loop thorugh the pw string till it ends
    {
        if(*password >= 'A' && *password <= 'Z')//makes sure pw has an upper case letter
        {
            hasUpper++;
            letterCombo++;
        }
        else if (*password >= 'a' && *password <= 'z')//makes sure pw has a lower case letter
        {
            hasLower++;
            letterCombo++;
            
        }
        else if(*password >= '0' && *password <= '9')//makes sure pw has a number
        {
            hasNum++;
            letterCombo = 0;
        }
        else//makes sure pw only contains letters and numbers
        {
            
            nonLetterOrNum++;
        }
        if(letterCombo >= 4)//makes sure there are at least 4 letters in a row in the pw
        {
            consecLetter++;
        }

        size++;
        password++;
        
    }

        if((size >= 8) && (hasLower > 0) && (hasUpper > 0) && (consecLetter >= 1) && (nonLetterOrNum == 0) && x == false && hasNum >= 1) // if all constraints are met return true because password is strong
        {
            return true;
        }

    
	return false;
}

/** 
 * Example: isStrongDefaultPassword("vahab", "Taher3h") returns false
 */
bool isStrongDefaultPassword(const char* username, const char* password) {//same as is function above but without the consecutive char check (no need to comment)
	 int size = 0;
    int hasUpper = 0;
    int hasLower = 0;
    int hasNum = 0;
    int letterCombo = 0;
    int consecLetter = 0;
    int nonLetterOrNum = 0;
    bool x = UserInPass(password,username);

    while(*password != '\0')
    {
        if(*password >= 'A' && *password <= 'Z')
        {
            hasUpper++;
            letterCombo++;
        }
        else if (*password >= 'a' && *password <= 'z')
        {
            hasLower++;
            letterCombo++;
            
        }
        else if(*password >= '0' && *password <= '9')
        {
            hasNum++;
            letterCombo = 0;
        }
        else
        {
            
            nonLetterOrNum++;
        }
        size++;
        password++;
        
    }

        if((size >= 8) && (hasLower > 0) && (hasUpper > 0) && (nonLetterOrNum == 0) && x == false && hasNum >=1 )
        {
            return true;
        }

   
	return false;
}

/** 
 * This function may *not* call isStrongPassword(). 
 * This function must call isStrongDefaultPassword().
 */
void generateDefaultPassword(char* default_password, const char * username) {
	//TODO: your code goes here.
    int upper = 15;// highest password length
    int lower = 8;//lowest password length
    int randomCat = 0; //To choose a random char catagorie
    int passwordSize = 0;//Store the random password size.

    //Array of numbers to choose (Catagorie 0)
    char numbers[11] = "0123456789";

    //Array of lowercase letter to choose from (Catagorie 1)
    char lowercase[27] = "abcdefghijklmnoqprstuvwyzx";

    //Array of capital letters to choose from (catagorie 2)
    char capital[27] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";

    //Keeps the random generated password. (Must be no longer than 15 chars)
    char randomPass[16] = "";

    //From the 3 catagories Lowercase, Captial and number generate a random num 0-2 to select a char for the password
    randomCat = rand() %3;
    passwordSize = rand() %(upper-lower+1)+lower;

    //Loop until the random passwrod size is reached
    
    while(isStrongDefaultPassword(username, randomPass) == false){
        for (int i=0; i <= passwordSize; i++)
        {
            if (randomCat == 0)
            {
                randomPass[i]= numbers[rand() % 10];// pick a random char from that catagorie
                randomCat = rand() % 3; //choose a new random catagorie
            }
            else if (randomCat == 1)
            {
                randomPass[i]= lowercase[rand() % 26];// pick a random char from that catagorie
                randomCat = rand() % 3; //choose a new random catagorie
            }
            else
            {
                randomPass[i]= capital[rand() % 26];// pick a random char from that catagorie
                randomCat = rand() % 3; //choose a new random catagorie
            }

        
        }
        
    }
    strcpy(default_password,randomPass);
    
    //
    
    //*default_password = *randomPass;
    //if the user wants to replace their current password with the random one do so.


}

int main(void) 
{
    char username[50]="";//create astring array to store username
    char password[50]="";//create a string array to store pw
    char default_pw[50]= "";//store default pw
    int x = 0;
    printf("Enter a username: \n");//ask for user and input for username
    scanf("%s",username);
    printf("Enter a password: \n");//^^^same but with pw
    scanf("%s",password);

    while(isStrongPassword(username,password) == false)//Keeping asking for a pasword until it is considered strong
    {
	    printf("Your password is weak. Try again\n");
	    printf("Enter a password: \n");
	    scanf("%s",password);
	    isStrongPassword(username,password);
    }
    printf("Strong Password");
    printf("\nGenerating a default password...\n");
    generateDefaultPassword(default_pw,username);
    printf("Generated default password: %s\n",default_pw);
    
    
    

	return 0;
}


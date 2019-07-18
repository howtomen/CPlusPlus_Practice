#include <iostream> //duh
#include <string> // string for the name
#include <time.h> //needed in random number generation



using namespace std;

int health[3] = {150,200,250}; // made array so that the health levels are always defined.
int crit[3] = {5,10,15}; // same thing^^ but with critical damage %

struct Gladiator { //this is how structs work you do Struct NameofThing
    string name; 
    int maxHealth, currentHealth, minDamage, DamageRange, evasion, critDam; //this is everything stored in one instance of the struct same with name
}; //dont forget that this needs ;


void showstats(Gladiator one) // simple function to print out the gladiators stats. no need to print both at once just pass each one into function
{
    cout << "These are " << one.name << "'s stats: " << endl;
    cout << "Health: " << one.currentHealth << endl;
    cout << "Evasion %: " << one.evasion << endl;
    cout << "Critical %: " << one.critDam << endl; 
    cout << "Damage: range: " << one.minDamage << "-" << one.minDamage+one.DamageRange << endl;
    
}


void generateGlad( Gladiator &one ) //passed by reference (&) is needed so that the program remembers the values assigned otherwise you get a bunch of 0's for every value
{
    int temp3, temp4; // i made all these random temps because I was getting errors but they are not necesarry. if u want to be more efficient you can reuse one temp to save memory
    char choice; //^^ i fixed the error above and just decided to leave temp variables bc im lazy
    cout << "Enter a Gladiator name: "; cin >> one.name; // notice how i write to struct. one is the name of the gladiator value in main and then "." then value inside struct;
    do{
    srand (time(NULL));
    int temp = rand ()% 3+ 1;
    one.maxHealth = health[temp-1]; // gives random health from the array used -1 to include 0-2 
    one.currentHealth = health[temp-1];
    int temp1 = rand ()% 3+ 1;
    one.critDam = crit[temp1-1]; // gets random crit from the array
    int temp2 = rand ()% 3+ 1;
    one.evasion = crit[temp2-1];
    do
    {
        temp3 = rand ()% 14+ 1; // generates random number from 1-14 
        one.minDamage = temp3;

    } while (temp3 < 8); // use a do while loop to make sure that the value stays within the range of 8-14. anything under 8 gets reseeded 
    do
    {
        temp4 = rand ()% 16+ 1;
        one.DamageRange = temp4;
        
    } while (temp4 < 16); //once again ignore anything under 16

    showstats(one);
    cout << "do you want to keep these stats(y/n)? "; cin >> choice;
    }while (choice != 'y'); //keeps going until the char y is found;
}


int taketurns(Gladiator &one, Gladiator &two, int turn)
{
    int temp, damage;
    int miss = 0; //this is to account for attacks that miss 
    if (turn == 0)
    {
        temp = rand() % 100 + 1; //generate number 1-100
        if ( temp < two.evasion ) // if the number is lower than two.evasion then gladiator 2 dodges attack
            miss = 1;
        if (miss == 1){
            cout << two.name << " has evaded the attack\n";
            return 0;
        }
        if (miss == 0) // this accounts for attacks that are successful. could also be else but whateverr
        {
            do{
                damage = rand() % one.minDamage+one.DamageRange; // this randomly picks damage from 1 - minDamage + damage range
            }while (damage < one.minDamage); // ignores values lower than min damage
            
            int temp2 = rand() % 100 + 1;
            if (temp2 < one.critDam) //if number is less than critical damage % then double the damage
                damage = damage *2;
            two.currentHealth = two.currentHealth - damage; // reduce health of opponent.
            cout << one.name << " has inflicted " << damage << " points of damage to " << two.name << endl; //print attack details
            cout << two.name << " has " << two.currentHealth << " health points remaining.\n";
            if (two.currentHealth < 1) //determine if the fight goes on. anything less than 1 means the fighter is ded af
                return 1; // end fight
            else
                return 0; //continue
        }
    }
    if (turn == 1) //exact same as above but for the other fighter
    { //  ^^ also remember '==' is needed in all these if statements otherwise they are broken and it took me like 20 min to remember that
        temp = rand() % 100 + 1;
        if ( temp < one.evasion )
            miss = 1;
        if (miss == 1){
            cout << one.name << " has evaded the attack\n";
            return 0;
        }
        if (miss == 0)
        {
            do{
                damage = rand() % two.minDamage+two.DamageRange;
            }while (damage < two.minDamage);
            int temp3 = rand() % 100 + 1;
            if (temp3 < two.critDam)
                damage = damage *2;
            one.currentHealth = one.currentHealth - damage;
            cout << two.name << " has inflicted " << damage << " points of damage to " << one.name << endl;
            cout << one.name << " has " << one.currentHealth << " health points remaining.\n";      
                if (one.currentHealth < 1)
                return 1;
            else
                return 0;
        }
    }

}


void LetsFight(Gladiator &one, Gladiator &two) //made this function simply because it makes it easier to implement the rematch
{
    int fight, turn; //your professor required a return variable i set it to fight
    int roundcount = 1; // this is just to keep track of how many rounds are fought in each fight
    do
    {
        turn = 0; //needed bc otherwise turn would never go back to 0
        cout << "\n\nRound " << roundcount << endl; //print round count and \n is just an endl shortcut
        fight = taketurns(one, two, turn);
        if (fight == 0) //only continue if fight is 0, if fight == 1 then the fight is over.
        {
            turn++; //makes it so that its the other players turn, gets reset above
            fight = taketurns(one, two, turn);
        }
        roundcount++; //next round
    } while (fight == 0); //keeps going until someone dies af
    if (turn == 0)//determine winner by seeing what turn it was
        cout << endl << one.name << " won the match" << endl;  
    else //could be if turn == 1 but thats more typing so nah
        cout << endl << two.name << " won the match" << endl;
}

int main() 
{
    Gladiator one, two; // you decalre structs in the same way you declare any other variable. except your struct name is now a type.
    int anothertemp = 0; //this temp variable is simply to loop the rematch option. rename this if u want
    cout << "You are gonna be hosting a fight between two gladiators!" << endl;
    char rematchsame, rematch; //for when deciding if you want to rematch and what kind of rematch 
    generateGlad(one); //lets make two gladiators
    generateGlad(two);
    LetsFight(one, two); //lets have them fight for the first time
    do{ // allows as many rematches as your heart desires.
    cout << "Would you like to rematch with the same fighters?(y/n) ";
    cin >> rematchsame;
    if (rematchsame == 'y')
    {
        one.currentHealth = one.maxHealth; //this resets the health so that the rematch doesnt end right away
        two.currentHealth = two.maxHealth;
        LetsFight(one,two); //rematchhhhhhh
    }
    else //if u dont want the same fighters try new ones? 
    {
        cout << "would you like to rematch with new fighters?(y/n) "; 
        cin >> rematch;
        if (rematch == 'y')
        {
            generateGlad(one); //lets make new fighters 
            generateGlad(two);
            LetsFight(one, two); // rematch af
        }
        else
            anothertemp++; // if u dont wanna rematch lets get out of this loop
    }
    }while (anothertemp == 0); //stays in loop until 2 nos are given  

    cout << "\n\nThanks for playing!\n\n";
    system("pause"); 
    return 0;

}
//Code of: Grace Peltan and Madeline Carlson


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//struct holding the attributes of each individual card
typedef struct card_s {
    char color[7];
    int value;
    char action[15];
    struct card_s *pt;
} card;

//struct holding the pointers values in order to create player's hands through a linked list
typedef struct hand_s{
    card* head;
    int* sizeptr;
    card* tail;
    int fourOkay;
} hand;

//struct to store each player
typedef struct player_s {
    int position;
    hand playerhand;
    char name[30];
} player;

//function to add a card to a players hand through a linked list
/*function takes the nextCard, which is the card on top of the available pile, as well as the hand of the player, and returns an updated linked list of the players hand with the nextCard added*/
void addtoHand(card nextCard, hand s) {
    card *current = s.head;
    
    
    while(current->pt != NULL){
        current = current->pt;
    }
    current->pt = malloc(sizeof(card));
    strncpy(current->pt->color, nextCard.color, 7);
    current->pt->value = nextCard.value;
    strncpy(current->pt->action, nextCard.action, 7);
    
    current->pt->pt = NULL;

}

//function to read in the user's file of cards, and return an array of the deck of cards
//takes in a file, as well as an empty array of typre card, and inserts these cards wihtin the empty array
void arrayMaker(FILE* inp, card* deck) {

    for (int i = 0; i < 108; i++) {
        fscanf(inp, "%s", deck[i].color);
        fscanf(inp, "%d", &deck[i].value);
        fscanf(inp, "%s", deck[i].action);
    }
}

//function to shuffle the array of the deck that has been created from the user file
//takes in deck array of cards, and returns shuffled deck
void shuffle(card* deck) {
    card temp;
    int card1;
    int card2;

    for (int i = 0; i < 500; i++) {
        card1 = (rand() % 108);
        card2 = (rand() % 108);
        temp = deck[card1];
        deck[card1] = deck[card2];
        deck[card2] = temp;
    }
}

//function to print individual cards as a graphic, based upon there attributes within their struct
//takes in any card, and prints it
void printCard(card display){
    char colour = ' ';
    if (strcmp(display.color, "RED") == 0) {
            colour = 'R';
        }
        else if (strcmp(display.color, "YELLOW") == 0) {
            colour = 'Y';
        }
        else if (strcmp(display.color, "GREEN") == 0) {
            colour = 'G';
        }
        else {
            colour = 'B';
        }

    if (strcmp(display.action, "NULL") == 0) {
        printf(" ____\n");
        printf("|%d   |\n", display.value);
        printf("|  %c |\n", colour);
        printf("|  %c |\n", colour);
        printf("|___%d|\n", display.value);
    }
    else if (strcmp(display.action, "WILD") == 0){
        printf(" _____\n");
        printf("|  🔴 |\n");
        printf("| 🟡  |\n");
        printf("|  🟢 |\n");
        printf("|_🔵__|\n");
        printf("WILD!\n");
    }
    else if (strcmp(display.action, "REVERSE") == 0){
        printf(" ____\n");
        printf("|    |\n");
        printf("| 🔃 |\n");
        printf("|  %c |\n", colour);
        printf("|____|\n");
        printf("REVERSE!\n");
    }
    else if (strcmp(display.action, "+2") == 0) {
         printf(" ____\n");
        printf("|+2  |\n");
        printf("|  %c |\n", colour);
        printf("|  %c |\n", colour);
        printf("|__+2|\n");
    }
    else if (strcmp(display.action, "+4") == 0) {
        printf(" _____\n");
        printf("|+4🔴 |\n");
        printf("| 🟡  |\n");
        printf("|  🟢 |\n");
        printf("|_🔵+4|\n");
    }
    else if (strcmp(display.action, "SKIP") == 0) {
        printf(" ____\n");
        printf("|  %c |\n", colour);
        printf("| 🚫 |\n");
        printf("|  %c |\n",colour);
        printf("|____|\n");
    }
    
    printf("%s, %d, %s\n", display.color, display.value, display.action);
}


/*function to print a players entire hand through each turn, by utilizing the linked list as well as the printCard function*/
//takes in a hand, and sends indiviudual cards to printCard to print the entrie hand
void printHand(card *cp) {
    
    while(cp != NULL){
        
        printCard(*cp);
        cp = cp->pt;
    }
    
}


//function to check individual card's validity to be played against the display card or "activeCard"
/*takes in the "activeCrad" which is the card the player has to match, as well as the player's choice of card, and returns a bool value*/
int checkCard(card activeCard, card playerCard) {

    if ((strcmp(playerCard.action, "WILD") == 0) || (strcmp(playerCard.action, "+4") == 0)) {
        return true;
    }
    
    else if(((strcmp(playerCard.action, "SKIP")) == 0) && (strcmp(activeCard.action, "SKIP")) == 0) {
        return true;
    }
        
    else if (strcmp(activeCard.color, playerCard.color) == 0) {
        return true;
    }
        
    else if(activeCard.value == playerCard.value){
        return true;
            
    }
    
    else {
        return false;
    }

}

/*different than "checkCard" in the way that the player can only play a +4 card if they have no other matches of color*/
/*takes in players entire hand, the card it needs to match, and the player's choice of card, return a bool determining whether or not they can place a +4*/
int checkMove(hand playerhand, card activeCard, card playerCard) {
    
    if ((strcmp(playerCard.action, "+4") == 0) && (playerhand.fourOkay == 0)){
        return false;
        
    }
    else{
        if ((strcmp(playerCard.action, "WILD") == 0) || (strcmp(playerCard.action, "+4") == 0)) {

            return true;
            
        }
        
        if(((strcmp(playerCard.action, "SKIP")) == 0) && (strcmp(activeCard.action, "SKIP")) == 0) {

            return true;
        }
        
        if (strcmp(activeCard.color, playerCard.color) == 0) {

            return true;
            
        }
        
        if(activeCard.value == playerCard.value){

            return true;
            
            
        }
    
        else {

            return false;
            
        }
    }
}

//function to return the card that the player has chosen for the linked list, in order to check this card
/*takes in player's entire hand, and the address choice for the card they want to place, and returns a card of that address in the player's hand*/
card getCard (hand playerhand, int playerChoice) {
    
    
    for(int i = 0; i < playerChoice; i++){
        playerhand.head = playerhand.head->pt;
    }
    
    printf("%s, %d, %s", playerhand.head->color, playerhand.head->value, playerhand.head->action);
    return *playerhand.head;
}

/*once the card the player has chosen has gone through the validity check, this function removes this card from the linked list of the player's hand*/
/*takes in a double and single pointer to the head node of the player's hand linked list, as well as the address chosen, returns the updated linked list without the card of the address*/
void cardhandfree(card** head, card* head2, int choice){
    card* current = *head;
    card* previous = *head;
    card* temp;
    
    current = malloc(sizeof(card*));
    previous = malloc(sizeof(card*));
    temp = malloc(sizeof(card*));
    
    if (choice == 0) {
        temp = head2;
        head2 = head2->pt;
        free(temp);
    }
    if(choice == 1) {
        *head = current->pt;
        free(current);
        current = NULL;
    }
    else {
        while((choice > 1)&&(current->pt !=NULL)){
            previous = current;
            current = current->pt;
            choice--;
        if(current->pt == NULL){
            previous->pt = NULL;
            free(current);
            current = NULL;
        }
        else{
            previous->pt = current->pt;
            free(current);
            current = NULL;
        }
        }
    }
    
}


//function to put the chosen card back into the deck array at the "activeCard" or display position
/*takes in the players hand, the address choice, the entire deck array of cards, and the address of the activeCard (or top of discard pile), and places card given by player on top of the discard pile*/
void placeCard(hand playerhand, int numchoice, card deck[108], int activeCard) {
    card playerCard = getCard(playerhand, numchoice);
    char colorChoice[7];
    
    if ((strcmp(playerCard.action, "WILD") == 0) || (strcmp(playerCard.action, "+4") == 0)) {
        printf("Choose a card from: RED, YELLOW, GREEN, or BLUE.\n");
        scanf("%s", colorChoice);
        strncpy(playerCard.color, colorChoice, 7);
    }

    strncpy(deck[activeCard].color, playerCard.color, 7);
    deck[activeCard].value = playerCard.value;
    strncpy(deck[activeCard].action, playerCard.action, 7);
    cardhandfree(&playerhand.head, playerhand.head, numchoice);
    
}

/*function to check a player's entire hand, in order to see if they contain any valid choices, or if they need to draw a card*/
//takes in the players entire hand, the head node of the player's linked list, the top of discard pile, and the integter for the game over validiation check, and returns bool as to whether or not the player has any valid moves, as well as the integer pointer which indicates both UNO and game over.*/
bool checkHand(hand playerhand, card *playerHead, card activeCard, int* gamewon) {
    int valid = 0;
    int colormatch = 0;
    int plusfour = 0;
    int count = 0;
    while(playerHead != NULL){
        if ((strcmp(playerHead->action, "+4") == 0)) {
            plusfour ++;
        }
        if (strcmp(activeCard.color, playerHead->color) == 0) {
            colormatch ++;
        }
        
        if(checkCard( activeCard, *playerHead)) {
            valid++;
        }
        
        playerHead = playerHead->pt;
        count++;
    }
    if (count ==0){
        printf("GAME WON!");
        *gamewon = 1;
    }
    if (count == 1){
        printf("UNO!");
    }
    if (colormatch<=plusfour){
        playerhand.fourOkay = 0;
    }
    else{
        playerhand.fourOkay = 1;
    }
   
        if (valid != 0) {
            return true;
        }
        else{
            return false;
        }
        
    }




int main (void) {
    card deck[108]; //entire card deck array
    FILE* inp = NULL; //user input file being read in
    char fileName[30]; //filename being read in from user
    int shuffleChoice = 1; //user's choice of whether or not to shuffle the deck array
    int numPlayers = 0; //amount of players from user input (from 2 - 10)
    int activeCard = 0; //top card on discard pile, or the "display" card
    int nextCard = 0; //this is the next card that is available to be drawn from the deck
    int* gamewon = 0; //utilized in the while loop containing each turn, so that the game can terminate if game = 1
    int activePlayer = 0; //stores the player who's turn it is
    int nextplayer = 1; // stores int location of the next player in player array
    int turn = 1; /*indicates the direction in which the array of players is iterated (array of players is below the user input for the number of players*/
    int skip = 0; //indicates whether the array of the players needs to skip one if a skip card is placed
    int playerChoice; //holds the address of the players choice for a card within their hand for each turn
    card choice; //holds the card that is associated with the player's address choice
    
    //user enters file name, and this name is checked for
    while (inp == NULL) {
        printf("Enter the file name for the deck of cards.\n");
        scanf("%s", fileName);
        inp = fopen(fileName, "r");
        if (inp == NULL) {
            printf("File name does not exist. Try again.\n");
        }
    }
    
    /*once the file name is valid and has been successfully read in, the array is created through the arrayMaker function*/
    arrayMaker(inp, deck);

    //while loop in order for the player's to shuffle as many times as they like
    while (shuffleChoice != 2) {
        printf("Press 1 to shuffle, or 2 to play:\n");
        scanf("%d", &shuffleChoice);
        if (shuffleChoice == 1){
            shuffle(deck);
            //run shuffle function
        }
    }
    
    //asks the user for the number of players
    printf("Enter the number of players from 2 - 10:\n");
    scanf("%d", &numPlayers);
    
    //checking to see if the number entered is within a vlaid range of players
    while(numPlayers < 2 || numPlayers > 10) {
        printf("Not a valid number of players.\n");
        scanf("%d", &numPlayers);
    }
   
    //creating an array of players based upon the number entered by the user
    player team[numPlayers]; //
    
    //player's are allowed to enter each of their names, which are stored within the array as well as the player struct//
    for (int i = 0; i < numPlayers; i++) {
        printf("Enter Player number %d's name:\n", (i + 1));
        scanf("%s", team[i].name);
    }
    
    //activeCard and nextCard are initialzed to be the last two elements of the array
    activeCard = 107;
    nextCard = 106;

    //the head node for the player's linked lists are dynamically allocated
    for (int i = 0; i < numPlayers; i++) {
        
        team[i].playerhand.head = NULL;
        team[i].playerhand.head = malloc(sizeof(card));
        
        strncpy(team[i].playerhand.head->color, deck[nextCard].color, 7);
        team[i].playerhand.head->value = deck[nextCard].value;
        strncpy(team[i].playerhand.head->action, deck[nextCard].action, 7);
        
        team[i].playerhand.head->pt = NULL;
        nextCard --;
        
        team[i].playerhand.fourOkay = 0;
        
    }
        
    //the tail node for the player's linked lists are dynamically allocated
    for (int i = 0; i < numPlayers; i++) {
        
        team[i].playerhand.tail = malloc(sizeof(card));
        
        strncpy(team[i].playerhand.tail->color, deck[nextCard].color, 7);
        team[i].playerhand.tail->value = deck[nextCard].value;
        strncpy(team[i].playerhand.tail->action, deck[nextCard].action, 7);
        
        team[i].playerhand.head->pt = team[i].playerhand.tail;
        
        nextCard --;
        
    }
    
    //the rest of the linked lists for player's hands are created throught he addtoHand function
    //the nested for loops allow for alternate dealing
    for(int j = 0; j < 5; j++) {
        for (int i = 0; i < numPlayers; i++) {
            addtoHand(deck[nextCard], team[i].playerhand);
            nextCard--;
        }
    }
    
    //indicating that the player's hands have been successfully dealt
    printf("\n\nAll player's hands have been drawn.\n");
    
    //while loop for turns, runs until a player has no carsds
    while (gamewon == 0){
        
        //checking activePlayer's hand in order to see if they have valid moves, or need to draw a card
        //if no valid moves, a card is automatically drawn for them until a valid card exists
        while((!checkHand(team[activePlayer].playerhand, team[activePlayer].playerhand.head, deck[activeCard], gamewon)) && (activeCard >=0)){
            printf("%s, it's your turn, but you have no moves. Drawing a card.\n", team[activePlayer].name);
            addtoHand(deck[nextCard], team[activePlayer].playerhand);
            nextCard--;
        }
        
        /*tell's the users who's turn it is, as well as printing their hand so they can see which card they would like to choose*/
        printf("It is %s's turn! Here's your hand of cards:\n", team[activePlayer].name);
        printHand(team[activePlayer].playerhand.head);
        //indicates and prints the active card, so that the user is able to choose a valid index
        printf("\n\n\n\n Active card:\n");
        printCard(deck[activeCard]);
        
        //asks the player for the address within their linked list to choose from
        printf("%s, choose a card to place, starting at 0.\n", team[activePlayer].name);
        scanf("%d", &playerChoice);
        /*this address is put into the getCrad function, in order ot return the actual card associated with the address*/
        
        choice = getCard(team[activePlayer].playerhand, playerChoice);
        //while loop checks this card, and if it is not valid, asks player for another address
        //note this loop only runs once the player has at least one valid move
        while (!checkMove(team[activePlayer].playerhand, deck[activeCard], choice)) {
            printf("\nNOT VALID MOVE\n");
            printf("\n%s, choose a card to place.\n", team[activePlayer].name);
            scanf("%d", &playerChoice);
            choice = getCard(team[activePlayer].playerhand, playerChoice);
        }
        
        //shows the player that the chosen address and card was valid against the activeCard
        printf("\nValid move.\n");
        
        
        //turn reverses direction that the array is traveled through if the action attribute of the card is "REVERSE"
        if(strcmp(choice.action, "REVERSE") == 0){
            turn = -turn;
        }
        //temporarily increments the iteration through the array of players in order to skip the next turn
        if(strcmp(choice.action, "SKIP") == 0){
            skip = turn;
        }
        
  
        
        
        //adds four cards to the next player's hand if the action attribute is "+4"
        if(strcmp(choice.action, "+4") == 0){
            printf("+4 for next player\n");
            for(int i = 0;i<4; ++i){
                addtoHand(deck[nextCard],  team[nextplayer].playerhand);
                --nextCard;
            }
        }
        //adds two cards to the next player's hand if the action attribute is "+2"
        if(strcmp(choice.action, "+2") == 0){
            printf("+2 for next player\n");
            for(int i = 0;i<2; ++i){
                addtoHand(deck[nextCard],  team[nextplayer].playerhand);
                --nextCard;
            }
            
        }
        
        //activeCard is decremented in order for the player's choice to be placed into the next spot in the array
        activeCard --;
        placeCard(team[activePlayer].playerhand, playerChoice, deck, activeCard);
        
        
        //displays the card just placed as the next card to be matched with
        printf("\n\n\n Active card:\n");
        printCard(deck[activeCard]);
        
        
        /*running through checkHand, which iterates thrrough the linked list in while loop, and returns the value of pointer unoCheck, which not only checks if the player has UNO, but also if the player has won the game*/
        checkHand(team[activePlayer].playerhand, team[activePlayer].playerhand.head, deck[activeCard], gamewon);
        
        
        //updates activePlayer based upon turn direction and whether or not a skip was played
        activePlayer = activePlayer + turn + skip;
        nextplayer = activePlayer + turn;
        
        //keeps player iteration within bounds of array
        if (activePlayer <0 || activePlayer > numPlayers-1){
            if (turn == -1){
                activePlayer = numPlayers-1;
                nextplayer = activePlayer - 1;
            }
            else{
                activePlayer = 0;
                nextplayer = 1;
            }
        }
        
        if (nextplayer <0 || nextplayer > numPlayers-1){
            if (turn == -1){
                nextplayer = numPlayers - 2;
            }
            else{
                nextplayer = 0;
            }
        }
        
        
        skip =0;
    
        
    }
    
    printf("GAME OVER\n");
    
    return 0;
}


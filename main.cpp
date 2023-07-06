//sources code
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include<thread>
#include<chrono>
#include<unistd.h>
#include<time.h>
#include <set>
#include <cctype>
#include <stdexcept>

#include "util.h"
#include "guesser.h"
#include "draw.h"


using namespace std;

#define MAX_GUESSES 7

const int MAX_BAD_GUESSES = 7;

vector <string> WORD_LIST;
/*const string WORD_LIST[]={
"whale","dog","cat","lion","tiger","fish","bat","rat","mouse","jellyfish",
"chimpanzee","bear","seal","giraffe",
"leopard","cheetah","monkey","snake","cobra","shark","crocodile","polarbear","bird",
"parrot","eagal","anaconda","ant","pig","chicken","cow","buffalo",
"butterfly","dolphin","goat","sheep","crow",
"duck","goose","pigeon","falcon","elephant","octopus"
};
const string lol[]={

};*/
const string GAMEOVER[] ={
" -------------        \n"
" |           /        \n"
" |          O         \n"
" |         /|\\       \n"
" |         / \\        \n"
" |     \n"
" ----- \n",
" -------------        \n"
" |           |        \n"
" |           O        \n"
" |          /|\\      \n"
" |          / \\      \n"
" |     \n"
" ----- \n",
" -------------        \n"
" |            \       \n"
" |             O      \n"
" |            /|\\   \n"
" |            / \\   \n"
" |     \n"
" ----- \n",
" -------------        \n"
" |           |        \n"
" |           O        \n"
" |          /|\\      \n"
" |          / \\      \n"
" |     \n"
" ----- \n",
" -------------         \n"
" |           /         \n"
" |          O          \n"
" |         /|\\        \n"
" |         / \\        \n"
" |     \n"
" ----- \n",
" -------------        \n"
" |           |        \n"
" |           O        \n"
" |          /|\\      \n"
" |          / \\      \n"
" |     \n"
" ----- \n",
" -------------        \n"
" |            \       \n"
" |             O      \n"
" |            /|\\   \n"
" |            / \\   \n"
" |                    \n"
" ----- \n",
" -------------        \n"
" |           |        \n"
" |           O        \n"
" |          /|\\      \n"
" |          / \\      \n"
" |     \n"
" ----- \n",
" -------------        \n"
" |           //        \n"
" |          O         \n"
" |         /|\\        \n"
" |         / \\        \n"
" |     \n",
" -------------        \n"
" |           |        \n"
" |           O        \n"
" |          /|\\      \n"
" |          / \\      \n"
" |     \n"
" ----- \n",
" -------------        \n"
" |            \\       \n"
" |             O      \n"
" |            /|\\   \n"
" |            / \\   \n"
" |     \n"
" ----- \n",
" -------------        \n"
" |           |        \n"
" |           O        \n"
" |          /|\\      \n"
" |          / \\      \n"
" |     \n"
" ----- \n",
};
static string figure[] = {
" O \n"
" /|\\ \n"
" | | \n",
" O \n"
" /|\\ \n"
" / \\ \n",
" \O //\n"
"  | \n"
" / \\ \n",
" \\O/ \n"
"  | \n"
" / \\ \n",
" O \n"
" /|\ \n"
" / \\ \n",
"   O \n"
" /|\\ \n"
" / \\ \n" ,
" O \n"
" /|\\ \n"
" / \\ \n" ,
"   O \n"
" /|\\ \n"
" / \\ \n" ,
" O \n"
" /|\\ \n"
" / \\ \n" ,
"   O \n"
" /|\\ \n"
" / \\ \n" ,
};
const string FIGURE[] = {
" -------------    \n"
" |                \n"
" |                \n"
" |                \n"
" |                \n"
" |     \n"
" ----- \n",
" -------------    \n"
" |           |    \n"
" |                \n"
" |                \n"
" |                \n"
" |     \n"
" ----- \n",
" -------------    \n"
" |           |    \n"
" |           O    \n"
" |                \n"
" |                \n"
" |     \n"
" ----- \n",
" -------------    \n"
" |           |    \n"
" |           O    \n"
" |           |    \n"
" |                \n"
" |     \n"
" ----- \n",
"--------------    \n"
" |           |    \n"
" |           O    \n"
" |          /|    \n"
" |                \n"
" |     \n"
" ----- \n",
" -------------    \n"
" |           |    \n"
" |           O    \n"
" |          /|\\  \n"
" |                \n"
" |     \n"
" ----- \n",
" -------------    \n"
" |           |    \n"
" |           O    \n"
" |          /|\\  \n"
" |          /     \n"
" |     \n"
" ----- \n",
" -------------    \n"
" |           |    \n"
" |           O    \n"
" |          /|\\  \n"
" |          / \\  \n"
" |     \n"
" ----- \n",
};






string chooseWord();
void renderGame(string guessedWord, int badGuessCount , vector <char> WrongGuessed);
char readAGuess();
bool contains(string word, char guess);
string update(string guessedWord, string word, char guess);
int Picktopick();
int ChooseLevel();
void displayFinalResult(bool won , bool time , const string& word, int &sum , double time_use){
if(won&&time){
        int i=0;sum=sum+10;
    while(i<10){
            system("cls");
           // for (int i = 0; i < 30; i++) cout << endl;
            cout << "Congratulations! You win! "<<"the word is "<<word<<endl;
             cout << "Your Point : "<<sum<<endl;
             cout<<"Time Wasted :"<<time_use<<endl;
               cout<<figure[i];
               i++;
            this_thread::sleep_for(chrono::milliseconds(500));
		}
}
if(!time){
    int i=0; sum=sum-10;
		while(i<12){
                system("cls");
          // for (int i = 0; i < 30; i++) cout << endl;
        cout << "Sorry time is up. You lost the game "<<endl;
        cout << "Your Point : "<<sum<<endl;
        cout<<"Time Wasted :"<<time_use<<endl;
               cout<<GAMEOVER[i];

               i++;
            this_thread::sleep_for(chrono::milliseconds(500));
		}
}

	if(!won||!time){
		int i=0; sum=sum-10;
		while(i<12){
                system("cls");
          // for (int i = 0; i < 30; i++) cout << endl;
        cout << "You lost. The correct word is " << word<<endl;
        cout << "Your Point : "<<sum<<endl;
        cout<<"Time Wasted :"<<time_use<<endl;
               cout<<GAMEOVER[i];

               i++;
            this_thread::sleep_for(chrono::milliseconds(500));
		}
	}
}
bool checkExist(char a , vector <char> s){

for(int i=0;i<s.size();i++)if(a==s[i])return true;
return false;
}
string NameInput(){
string a;
cout<<"Enter your name please! : ";
cin>>a;
cout<<"Hello! "<<a<<" Welcome to Hangman! I hope you win"<<endl;
return a;
}


int main()
{
    int sum=100;
    vector <string> Namelist;
    vector <char> WrongGuessed;
    vector <double> TimeRank;
    vector <int> Point;
    char x;

for(int i=0;i<10;i++){
        string name = NameInput();
        Namelist.push_back(name);

	string word = chooseWord();
	string guessedWord = string(word.length(), '-');
	int badGuessCount = 0;
            vector <char> t;
            for(int i=0;i<word.length();i++)t.push_back(word[i]);
            srand(time(NULL));
           int helpIndex= rand() % t.size();
           char help = t[helpIndex];
           vector <char> alphabet;
           for(int i=0;i<word.length();i++){
                alphabet.push_back(word[i]-1);
                alphabet.push_back(word[i]+1);
                alphabet.push_back(word[i]-2);
                alphabet.push_back(word[i]+2);
           }
            clock_t start, ends;
        double time_use;
    start = clock();
	do {

		renderGame(guessedWord, badGuessCount,WrongGuessed);
		char guess = readAGuess();
		cout<<time_use;
if(guess=='1'){
    system("pause");
}
		if(guess=='0'){
                sum= sum-5;
            cout << "Your help : "<<t[helpIndex]<<endl;
             cout << "Your Point : "<<sum<<endl;
            system("pause");
		}
		if(contains(word, guess)==false && checkExist(guess , alphabet)==true){
            cout<<"Almost Right"<<endl;
           system("pause");
		}

		 if (contains(word, guess))
			guessedWord = update(guessedWord, word, guess);

if(!contains(word, guess)&&guess!='0'&&guess!='1'){

    badGuessCount++;

        WrongGuessed.push_back(guess);
}





	} while (badGuessCount < MAX_BAD_GUESSES && word != guessedWord);
	 ends = clock();
    time_use = (double)(ends - start) / CLOCKS_PER_SEC;
TimeRank.push_back(time_use);
Point.push_back(sum);

displayFinalResult(badGuessCount < MAX_BAD_GUESSES,time_use < 60 , word , sum , time_use);
cout<<"Do you want to continue"<<endl<<" Press n to exit / Press y to continue"<<endl;
cin>>x;
if(x=='y'){
    WrongGuessed.clear();
        continue;
}
if(x=='n'){
for(int i=0;i<Namelist.size();i++){
    cout<<Namelist[i]<<'\t'<<Point[i]<<'\t'<<TimeRank[i]<<endl;
}
break;
}

sum=100;

}
	return 0;
}

void chuanhoa(string &s){
for(int i=0;i<s.length();i++){
    if(s[i]>='A'&&s[i]<='Z')s[i]=char(s[i]+32);
}
}
int Picktopick(){
    int n;
    cout<<"Press 1 : Animal"<<endl;
    cout<<"Press 2 : Fruit"<<endl;
    cout<<"Press 3 : Job"<<endl;
    cout<<"Press 4 : Lol"<<endl;
    cin>>n;
    return n;
}
int ChooseLevel(){
   int n;
   cout<<"Press 1 : Easy"<<endl;
    cout<<"Press 2 : Normal"<<endl;
    cout<<"Press 3 : Hard"<<endl;
    cin>>n;
   return n;
}

string chooseWord()
{
     int k = Picktopick  ()  ;
    string path ;
if(k==1)path="animal.txt";
if(k==2)path="job.txt";
if(k==3)path="fruit.txt";
if(k==4)path="lol.txt";
    ifstream file(path);
string line;
    if (file.is_open()) {
while ( getline (file,line) ) {
WORD_LIST.push_back(line);
}
file.close();
}
else cout << "Unable to open file";
 int z = ChooseLevel () ;
 if(z==1){
srand(time(NULL));
int RandomIndex= rand() % WORD_LIST.size();
while(WORD_LIST[RandomIndex].length()>3){
        srand(time(NULL));
 RandomIndex= rand() % WORD_LIST.size();
}
chuanhoa(WORD_LIST[RandomIndex]);

	return WORD_LIST[RandomIndex];
 }
 if(z==2){
srand(time(NULL));
int RandomIndex= rand() % WORD_LIST.size();
while(WORD_LIST[RandomIndex].length()>4||WORD_LIST[RandomIndex].length()<=3){
        srand(time(NULL));
 RandomIndex= rand() % WORD_LIST.size();
}
chuanhoa(WORD_LIST[RandomIndex]);

	return WORD_LIST[RandomIndex];
 }
 if(z==3){
srand(time(NULL));
int RandomIndex= rand() % WORD_LIST.size();
while(WORD_LIST[RandomIndex].length()<5){
        srand(time(NULL));
 RandomIndex= rand() % WORD_LIST.size();
}
chuanhoa(WORD_LIST[RandomIndex]);

	return WORD_LIST[RandomIndex];
 }


}
void clock(int hour , int minute , int second){
while(true){

    cout<<" "<<hour<<" :"<<minute<<" :"<<second<<endl;
    second++;
    if(second==60){
            minute++;
    second=0;
 }
    if(minute==60){
        hour++;
        minute=0;
    }
    if(hour==60)hour=0;
    sleep(1);
 }
}
void renderGame(string guessedWord , int badGuessCount , vector <char> WrongGuessed)
{
   system("cls");
	cout<<FIGURE[badGuessCount]<<endl;
	cout << guessedWord << endl;
	cout<<"Wrong Guessed: ";
	for(int i=0;i<WrongGuessed.size();i++)cout<<WrongGuessed[i]<<" ";
	cout<<endl;
	cout << "Number of wrong guesses: " << badGuessCount << endl;
}

char readAGuess()
{
	char input;
	cout<<"Press 1 if you want to pause this game "<<endl;
	cout << "Press 0 if you need help       "<<endl;
	cout << "Your guess: ";
	cin >> input;
    return input;
}

bool contains(string word, char c)
{
	return (word.find_first_of(c) != string::npos);
}

string update(string guessedWord, const string word, char guess)
{
	for (int i = word.length() - 1; i >= 0; i--) {
        if (word[i] == guess) {
            guessedWord[i] = guess;
        }
    }
   return guessedWord;
}


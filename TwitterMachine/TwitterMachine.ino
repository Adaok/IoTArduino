/*

Tweet Machine with One Sheeld
This sketch receive voice message and tweet it.
The user is notify.

*/

#define CUSTOM_SETTINGS
#define INCLUDE_TEXT_TO_SPEECH_SHIELD
#define INCLUDE_NOTIFICATION_SHIELD
#define INCLUDE_VOICE_RECOGNIZER_SHIELD
#define INCLUDE_TWITTER_SHIELD

/* Include 1Sheeld library and other. */
#include <OneSheeld.h>
#include <LiquidCrystal.h>


bool asSpeaked = false;
char *MyTweet;
char Hashtag[]= "#With1Sheeld";

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int inputButtonSend = 8;
int inputButtonCancel = 9;

int valSend = 0;
int valCancel = 0;


void setup()
{
  /* Start communication. */
  OneSheeld.begin();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Tweet Machine !");
  pinMode(inputButtonSend, INPUT);
  pinMode(inputButtonCancel, INPUT);
}

void loop()
{
  valSend = digitalRead(inputButtonSend);  // read input value
  valCancel = digitalRead(inputButtonCancel);
       
  if(VoiceRecognition.isNewCommandReceived()){
    MyTweet = VoiceRecognition.getLastCommand();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(MyTweet);
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(Hashtag);
  }

  int lengthTweet = strlen(MyTweet);
  
  if(valSend != 0 && lengthTweet != 0){
    strcat(MyTweet, " ");
    strcat(MyTweet, Hashtag);
    Twitter.tweet(MyTweet);
      TextToSpeech.say("Tweet send !");
      Notification.notifyPhone("Tweet envoyé");
      lcd.setCursor(0, 1);
      // print the number of seconds since reset:
      lcd.print("Tweet send !");
      strcpy(MyTweet, "");

      delay(2000);
      lcd.clear();
      lcd.print("Tweet Machine !");
  }

  if(valCancel != 0 && lengthTweet != 0){
     strcpy(MyTweet, "");
     lcd.clear();
     lcd.print("Tweet abort");

     delay(2000);
     lcd.clear();
     lcd.print("Tweet Machine !");
  }
}

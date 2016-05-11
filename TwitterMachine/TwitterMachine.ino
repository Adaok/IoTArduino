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



/* Include 1Sheeld library. */
#include <OneSheeld.h>
#include <LiquidCrystal.h>


bool asSpeaked = false;
char *MyTweet;
char Hashtag[]= "#With1Sheeld";

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup()
{
  /* Start communication. */
  OneSheeld.begin();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  
}

void loop()
{
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
  if(VoiceRecognition.isNewCommandReceived()){

    MyTweet = VoiceRecognition.getLastCommand();
    strcat(MyTweet, " ");
    strcat(MyTweet, Hashtag);
    int lengthTweet = strlen(MyTweet);

    if(lengthTweet != 0){
      Twitter.tweet(MyTweet);
      TextToSpeech.say("Tweet send !");
      Notification.notifyPhone("Tweet envoyé");
      strcpy(MyTweet, "");
    } 
  }
}

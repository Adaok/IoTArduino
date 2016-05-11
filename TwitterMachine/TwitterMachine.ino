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

bool asSpeaked = false;
char *MyTweet;
char Hashtag[]= "#With1Sheeld";

void setup()
{
  /* Start communication. */
  OneSheeld.begin();
  /* Set the LED pin as output. */
}

void loop()
{
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

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
const int lcd_rs = 7, lcd_e = 8, lcd_db4 = 9, lcd_db5 = 10, lcd_db6 = 11, lcd_db7 = 12;
LiquidCrystal lcd(lcd_rs, lcd_e, lcd_db4, lcd_db5, lcd_db6, lcd_db7);

// defines the notes given their frequencies: https://nickfever.com/music/note-frequencies
#define Rest 0
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_Bb4 466
#define NOTE_B4 494
#define NOTE_A4 440
#define NOTE_C5 523
#define NOTE_Db5 554
#define NOTE_D5 587
#define NOTE_Eb5 624
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_Gb5 740
#define NOTE_G5 784
#define NOTE_Ab5 831
#define NOTE_A5 880
#define NOTE_Bb5 932
#define NOTE_B5 988
#define NOTE_C6 1047

int piezoPin = 6;

/* Melody made by me while singing to my girlfriend,
thinking about singing a new fairytale to our cats
... kinda weird because the song is about learning
how to count. kitties gotta count the biscuits they make
*/

// notes in melody
int melody[] = {
  Rest, Rest,
  Rest, NOTE_C5,
  NOTE_F5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5,
  NOTE_D5, NOTE_E5, NOTE_D5, NOTE_Db5, NOTE_D5, NOTE_C5,
  NOTE_F5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5,
  NOTE_D5, NOTE_E5, NOTE_D5, NOTE_Db5, NOTE_D5, NOTE_F5,
  NOTE_G5, NOTE_A5, NOTE_G5, NOTE_E5, Rest,
  NOTE_C5, NOTE_D5, NOTE_C5, NOTE_A4, Rest,
  NOTE_G5, NOTE_A5, NOTE_G5, NOTE_E5, Rest,
  NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4,
  NOTE_Bb4, NOTE_D5,
  NOTE_E5, NOTE_C5,
  NOTE_F5, NOTE_C5,
  NOTE_Bb4, NOTE_A4,
  NOTE_G4, NOTE_D5,
  NOTE_E5, NOTE_C5,
  NOTE_F5, NOTE_F5, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_F5, Rest, NOTE_F4, Rest
};

// 0.5 - half note
// 1 - quarter note
// 2 - triplet eigth note
// 4 - triplet quarter note

float noteDurations[] = {
  0.5, 0.5, 
  1, 0.5,
  2, 4, 2, 4, 2, 4, 2, 4,
  2, 4, 2, 4, 1, 1,
  2, 4, 2, 4, 2, 4, 2, 4,
  2, 4, 2, 4, 1, 1,
  1, 1, 2, 4, 1,
  1, 1, 2, 4, 1,
  1, 1, 2, 4, 1,
  1, 1, 1, 1,
  0.5, 0.5,
  0.5, 0.5,
  0.5, 0.5,
  0.5, 0.5,
  0.5, 0.5,
  0.5, 0.5,
  2, 4, 2, 4, 1, 1,
  1, 1, 1, 1
};

int bpm = 90;

void setup() {
  
  // setup 16 columns by 2 rows of text
  lcd.begin(16, 2);
  lcd.print("Journey by Jaidi");
  
  // goes to second line
  lcd.setCursor(0, 1);
  lcd.print("n Playing Melody");
  
  bpm = bpm * 2;
  
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {
    int noteDuration;
    if (noteDurations[thisNote] == 2) {
      // Quarter note triplet
      noteDuration = (60000 / bpm) * 2 / 3;
    } else if (noteDurations[thisNote] == 4) {
      // Eighth note triplet
      noteDuration = (60000 / bpm) * 1 / 3;
    } else if (noteDurations[thisNote] == 1) {
      // Regular quarter note
      noteDuration = 60000 / bpm;
    } else if (noteDurations[thisNote] == 8) {
      // Regular eighth note
      noteDuration = (60000 / bpm) / 2;
    } else if (noteDurations[thisNote] == 16) {
      // Regular sixteenth note
      noteDuration = (60000 / bpm) / 4;
    } else if (noteDurations[thisNote] == 0.5) {
      // Regular half note
      noteDuration = (60000 / bpm) * 2;
    }
    
    tone(piezoPin, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the piezo
    noTone(piezoPin);
  }
  
  // goes to beginning second line
  lcd.setCursor(0, 1);
  lcd.print("n Melody Ended  ");
}

void loop() {
  // no need to repeat the melody.
}

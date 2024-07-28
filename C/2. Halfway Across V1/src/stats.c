#include "halfway_across.h"
#define LOW_STAT_THRESHOLD 20
#define MEDIUM_STAT_THRESHOLD 50
#define HIGH_STAT_THRESHOLD 70

struct worldStats world = {1, 32, "clear"};

struct playerStats player = {100, 1, 100, 100, 50, 50};


// Gives player vague indication of stats if they select "Reflect" option
void warnings() {
  clearScreen();
  if (player.warmth < LOW_STAT_THRESHOLD) {
    printf("I won't survive this cold much longer.\n");
  } else if (LOW_STAT_THRESHOLD <= player.warmth &&
             player.warmth < MEDIUM_STAT_THRESHOLD) {
    printf("The cold is becoming unbearable.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= player.warmth &&
             player.warmth < HIGH_STAT_THRESHOLD) {
    printf("The cold is starting to get to me.\n");
  }

  if (player.health < LOW_STAT_THRESHOLD) {
    printf("My health is quickly deteriorating.\n");
  } else if (LOW_STAT_THRESHOLD <= player.health &&
             player.health < MEDIUM_STAT_THRESHOLD) {
    printf("I feel very ill.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= player.health &&
             player.health < HIGH_STAT_THRESHOLD) {
    printf("I feel a little under the currentWeather.\n");
  }

  if (player.hunger < LOW_STAT_THRESHOLD) {
    printf("I am starving.\n");
  } else if (LOW_STAT_THRESHOLD <= player.hunger &&
             player.hunger < MEDIUM_STAT_THRESHOLD) {
    printf("I need to eat something soon.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= player.hunger &&
             player.hunger < HIGH_STAT_THRESHOLD) {
    printf("I am starting to get hungry.\n");
  }

  if (player.thirst < LOW_STAT_THRESHOLD) {
    printf("My throat is very dry.\n");
  } else if (LOW_STAT_THRESHOLD <= player.thirst &&
             player.thirst < MEDIUM_STAT_THRESHOLD) {
    printf("I need to drink something soon.\n");
  } else if (MEDIUM_STAT_THRESHOLD <= player.thirst &&
             player.thirst < HIGH_STAT_THRESHOLD) {
    printf("I am starting to get thirsty.\n");
  }
  printf("\nI will persist...");
  clearStdin();
}

// A given day's temperature has an effect on
// how high the temperature stat must be to avoid losing health
int generateTemperature() {
  int currentTemperature = rand() % (30 + 1);
  return currentTemperature;
}

// A given day's currentWeather currentWeather have an effect on
// what actions the player can do and how likely they are to succeed at those
// they can
char *generateWeather() {
  float blizzardProb = 5;
  float snowyProb = 20;
  float cloudyProb = 50;
  static char currentWeather[20];

  int prob = rand() % 100;
  if (prob <= blizzardProb) {
    strcpy(currentWeather, "snowed heavily");
  } else if (prob > blizzardProb && prob <= snowyProb) {
    strcpy(currentWeather, "snowed");
  } else if (prob > snowyProb && prob <= cloudyProb) {
    strcpy(currentWeather, "cloudy");
  } else if (prob > cloudyProb) {
    strcpy(currentWeather, "clear");
  } else {
    printf("There was an issue generating currentWeather currentWeather");
    return NULL;
  }
  return currentWeather;
}

void advanceDay() {
  if (player.health <= 0) {
    clearScreen();
    printf("This is my last entry, my health is failing me. Whoever finds "
           "this journal is welcome to whatever is left in my camp...");
    clearStdin();
    clearScreen();
    return;
  }
  player.energy = 1;
  world.day = world.day + 1;
  world.currentTemperature = generateTemperature();
  memset(world.currentWeather, 0, sizeof(world.currentWeather));
  strcpy(world.currentWeather, generateWeather());
  return;
}

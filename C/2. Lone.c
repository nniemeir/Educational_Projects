#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define FOOD_ITEMS 18
#define CLOTHING_ITEMS 15
#define TOOLS_ITEMS 3
#define RESOURCES_ITEMS 3
#define PELTS_ITEMS 6

struct playerStats {
  int health;
  int energy;
  int hunger;
  int thirst;
  int temperature;
  int charm;
  int quickness;
  int day;
};

struct item {
  char name[50];
  int amount;
  bool equipped;
  int effects;
};

struct playerInventory {
  // Food
  struct item food[FOOD_ITEMS];
  struct item clothing[CLOTHING_ITEMS];
  struct item tools[TOOLS_ITEMS];
  struct item resources[RESOURCES_ITEMS];
  struct item pelts[PELTS_ITEMS];
};

struct playerStats player = {100, 50, 100, 100, 50, 50, 20, 1};

struct playerInventory inventory = {
    .food =
        {
            {"Badger Meat", 0, false, 20},
            {"Bear Meat", 0, false, 100},
            {"Deer Meat", 0, false, 40},
            {"Fox Meat", 0, false, 20},
            {"Rabbit Meat", 0, false, 10},
            {"Squirrel Meat", 0, false, 10},
            {"Barberry", 0, false, 2},
            {"Bindweed", 0, false, -2},
            {"Buckthorn", 0, false, -5},
            {"Chokecherry", 0, false, 3},
            {"Common Burdock", 0, false, 5},
            {"Dandelion", 0, false, 5},
            {"Mountain Deathcamas", 0, false, -100},
            {"Oregon Grape", 0, false, 2},
            {"Purslane", 0, false, 2},
            {"Stinging Nettle", 0, false, 10},
            {"Wild Onion", 0, false, 2},
            {"Wild Strawberry", 0, false, 2},
        },
    .clothing =
        {
            {"Bearskin Cloak", 0, false, 50},
            {"Fox Skin Gloves", 0, false, 7},
            {"Leather Gloves", 1, true, 5},
            {"Rabbit Skin Gloves", 0, false, 8},
            {"Badger Hat", 0, false, 7},
            {"Felt Hat", 1, true, 5},
            {"Fox Hat", 0, false, 8},
            {"Raccoon Hat", 0, false, 7},
            {"Heavy Cotton Shirt", 1, true, 10},
            {"Heavy Cotton Trousers", 1, true, 20},
            {"Heavy Wool Vest", 0, false, 20},
            {"Moccasins", 1, true, 10},
            {"Bearskin Boots", 0, false, 30},
            {"Dearskin Boots", 0, false, 20},
            {"Rabbit Boots", 0, false, 15},
        },
    .tools =
        {
            {"Axe", 0, false, 0},
            {"Kettle", 0, false, 0},
            {"Knife", 0, false, 0},
        },
    .resources =
        {
            {"Purified Water", 0, false, 50},
            {"River Water", 0, false, 25},
            {"Wood", 0, false, 0},
        },
    .pelts = {
        {"Badger", 0, false, 0},
        {"Bear", 0, false, 0},
        {"Deer", 0, false, 0},
        {"Fox", 0, false, 0},
        {"Rabbit", 0, false, 0},
        {"Squirrel", 0, false, 0},
    }};

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void invalidInputMessage() {
  clearScreen();
  printf("My memory is failing me at the moment...\n");
  while (getchar() != '\n')
    ;
  clearScreen();
}

void listStats() {
  clearScreen();
  printf("Health: %d\n", player.health);
  printf("Energy: %d\n", player.energy);
  printf("Hunger: %d\n", player.hunger);
  printf("Thirst: %d\n", player.thirst);
  printf("Temperature: %d\n", player.temperature);
  printf("Charm: %d\n", player.charm);
  printf("Quickness: %d\n", player.quickness);
}

void warnings() {
  clearScreen();
  if (player.temperature < 20) {
    printf("I won't survive this cold much longer.\n");
  } else if (20 <= player.temperature && player.temperature < 50) {
    printf("The cold is becoming unbearable.\n");
  } else if (50 <= player.temperature && player.temperature < 70) {
    printf("The cold is starting to get to me.\n");
  }

  if (player.health < 20) {
    printf("My health is quickly deteriorating.\n");
  } else if (20 <= player.health && player.health < 50) {
    printf("I feel very ill.\n");
  } else if (50 <= player.health && player.health < 70) {
    printf("I feel a little under the weather.\n");
  }

  if (player.hunger < 20) {
    printf("I am starving.\n");
  } else if (20 <= player.hunger && player.hunger < 50) {
    printf("I need to eat something soon.\n");
  } else if (50 <= player.hunger && player.hunger < 70) {
    printf("I am starting to get hungry.\n");
  }

  if (player.thirst < 20) {
    printf("My throat is very dry.\n");
  } else if (20 <= player.thirst && player.thirst < 50) {
    printf("I need to drink something soon.\n");
  } else if (50 <= player.thirst && player.thirst < 70) {
    printf("I am starting to get thirsty.\n");
  }
  printf("I will persist...");
  while (getchar() != '\n')
    ;
}

int generateTemperature() {
  int dailyTemperature = rand() % (30 + 1);
  return dailyTemperature;
}

void travelMenu() {
  int validDestination = 0;
  while (!validDestination) {
    clearScreen();
    char destination[4];
    printf("I walked to...\n\n1. The Lake\n2. The Valley\n\n> ");
    fgets(destination, sizeof(destination), stdin);
    int destinationInt = atoi(destination);
    switch (destinationInt) {
    case 1:
      printf("Traveling to the lake...\n");
      validDestination = 1;
      break;
    case 2:
      printf("Traveling to the valley...\n");
      validDestination = 1;
      break;
    default:
      invalidInputMessage();
    }
  }
}

void displayInventory() {
  clearScreen();
  int clothingIncrement;
  printf("\n~~~ Clothing ~~~\n");
  for (clothingIncrement = 0; clothingIncrement < CLOTHING_ITEMS;
       clothingIncrement++) {
    if (inventory.clothing[clothingIncrement].amount != 0) {
      printf("%s: %d\n", inventory.clothing[clothingIncrement].name,
             inventory.clothing[clothingIncrement].amount);
    }
  }
  int foodIncrement;
  printf("\n~~~ Food ~~~\n");
  for (foodIncrement = 0; foodIncrement < FOOD_ITEMS; foodIncrement++) {
    if (inventory.food[foodIncrement].amount != 0) {

      printf("%s: %d\n", inventory.food[foodIncrement].name,
             inventory.food[foodIncrement].amount);
    }
  }
  int toolsIncrement;
  printf("\n~~~ Tools ~~~\n");
  for (toolsIncrement = 0; toolsIncrement < TOOLS_ITEMS; toolsIncrement++) {
    if (inventory.tools[toolsIncrement].amount != 0) {

      printf("%s: %d\n", inventory.tools[toolsIncrement].name,
             inventory.tools[toolsIncrement].amount);
    }
  }
  int resourcesIncrement;
  printf("\n~~~ Resources ~~~\n");
  for (resourcesIncrement = 0; resourcesIncrement < RESOURCES_ITEMS;
       resourcesIncrement++) {
    if (inventory.resources[resourcesIncrement].amount != 0) {

      printf("%s: %d\n", inventory.resources[resourcesIncrement].name,
             inventory.resources[resourcesIncrement].amount);
    }
  }
  int peltsIncrement;
  printf("\n~~~ Pelts ~~~\n");
  for (peltsIncrement = 0; peltsIncrement < PELTS_ITEMS; peltsIncrement++) {
    if (inventory.pelts[peltsIncrement].amount != 0) {

      printf("%s: %d\n", inventory.pelts[peltsIncrement].name,
             inventory.pelts[peltsIncrement].amount);
    }
  }
}

// Calculate whether to lower player's stats at end of day
void advanceDay() {
  player.day = player.day + 1;
}

int homeMenu() {
  char homeSelection[3];
  char conditions[20] = "snowed";
  int leftHome = 0;
  int dailyTemperature = 30;
  while (!leftHome) {
    clearScreen();
    printf("Day %d\n\n", player.day);
    printf("It was %d degrees and %s today.\n", dailyTemperature, conditions);
    printf("I decided to...\n\n");
    printf("1. Leave Camp\n2. Examine My Belongings\n3. Reflect\n4. List Stats"
           "(Debug)\n5. Sleep\n\n> ");
    fgets(homeSelection, sizeof(homeSelection), stdin);
    homeSelection[strcspn(homeSelection, "\n")] = '\0';
    if (strcmp(homeSelection, "1") == 0) {
      travelMenu();
      int leftHome = 1;
    } else if (strcmp(homeSelection, "2") == 0) {
      displayInventory();
      while (getchar() != '\n')
        ;
    } else if (strcmp(homeSelection, "3") == 0) {
      warnings();
    } else if (strcmp(homeSelection, "4") == 0) {
      listStats();
      while (getchar() != '\n')
        ;
    } else if (strcmp(homeSelection, "5") == 0) {
      advanceDay();
      dailyTemperature = generateTemperature();
      if (player.health <= 0) {
        clearScreen();
        printf("This is my last entry, my health is failing me. Whoever finds "
               "this journal is welcome to whatever is left in my camp...");
        while (getchar() != '\n')
          ;
        leftHome = 1;
      }
    } else {
      invalidInputMessage();
    }
  }
  return 0;
}

void preface() {
  clearScreen();
  printf("Someday you'll find yourself compelled to disrupt a patch of dirt, "
         "thinking you'll dig up a better tomorrow.\n\n");
  sleep(2);
  printf("You'll dig until your hands are masses of blisters and you're as "
         "stiff as a board. Another hour and I'll certainly be there, you'll "
         "think to yourself.\n\n");
  sleep(2);
  printf("The sun might try to boil your skin, but you'll persist.\n\n");
  sleep(2);
  printf("The truth is, some holes don't want to be dug.\n\n");
  sleep(2);
  printf("Eventually there comes a time where you just have to put down the "
         "shovel and be on your way, or that hole will be your grave...\n\n");
  while (getchar() != '\n')
    ;
  clearScreen();
}

void gameplay() { homeMenu(); }

void mainMenu() {
  clearScreen();
  char mainSelection[4];
  char prefaceSelection[4];
  int validSelection = 0;
  int validPrefaceSelection = 0;
  while (!validSelection) {
    printf("1. New Journal\n2. Continue Journal\n3. Go Home\n\n> ");
    fgets(mainSelection, sizeof(mainSelection), stdin);
    mainSelection[strcspn(mainSelection, "\n")] = '\0';
    if (strcmp(mainSelection, "1") == 0) {
      while (!validPrefaceSelection) {
        clearScreen();
        printf("1. Read Preface\n2. Skip Preface\n\n> ");
        fgets(prefaceSelection, sizeof(prefaceSelection), stdin);
        prefaceSelection[strcspn(prefaceSelection, "\n")] = '\0';
        if (strcmp(prefaceSelection, "1") == 0) {
          validPrefaceSelection = 1;
          preface();
          gameplay();
          return;
        } else if (strcmp(prefaceSelection, "2") == 0) {
          validPrefaceSelection = 1;
          gameplay();
          return;
        } else {
          invalidInputMessage();
        }
      }
    } else if (strcmp(mainSelection, "2") == 0) {
      clearScreen();
      printf("Saving not yet implemented...\n");
      while (getchar() != '\n')
        ;
      clearScreen();
    } else if (strcmp(mainSelection, "3") == 0) {
      return;
    } else {
      invalidInputMessage();
    }
  }
}

int main() {
  srand(time(NULL));
  mainMenu();
  return EXIT_SUCCESS;
}
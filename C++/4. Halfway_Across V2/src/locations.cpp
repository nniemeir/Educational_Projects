#include "../include/locations.h"
#include "QDebug"

Location::Location(const QString &name, const QString &description,
                   const QString &image, const std::vector<item> &inventory)
    : name(name), description(description), image(image), inventory(inventory) {
}

Location camp("camp",
              "You wake up sore, that familiar ache of winter mornings felt "
              "once again.\n\nExit: North",
              ":/images/camp.png", {{"FISHING ROD", 1, 0, 0, "tools"}});

Location
    campPath("campPath",
             "You move through a break in the trees for a while before "
             "reaching a fork in the road.\n\nExits: North, South, East, West",
             ":/images/campPath.png", {{"ROCK", 1, 0, 0, "tools"}});

Location caveEntrance("caveEntrance",
                      "You happen upon a cave, it might not be a good idea to "
                      "find out what it contains.\n\nExits: West, East",
                      ":/images/caveEntrance.png",
                      {{"ROCK", 1, 0, 0, "tools"}});

Location cave("cave",
              "Entering the cave, you see nothing but darkness.\n\nExits:West",
              ":/images/cave.png", {{"ROCK", 1, 0, 0, "tools"}});

Location intro("intro", "HALFWAY ACROSS\n\nType BEGIN to continue.\n",
               ":/images/intro.png", {{"MOTIVATION", 1, 0, 0, "Resources"}});

Location lake("lake", "You reach a lake after an hour's journey.\n\nExit: East",
              ":/images/lake.png", {{"CHISEL", 1, 0, 0, "tools"}});

Location valley("valley",
                "You reach a clearing. This could be a good spot for "
                "hunting.\n\nExit: South",
                ":/images/valley.png", {{"STICK", 1, 0, 0, "tools"}});

QString Location::getName() const { return name; }
QString Location::getDescription() const { return description; }
QString Location::getImage() const { return image; }

int Location::searchInventory(const QString &itemName) const {
  auto it = std::find_if(inventory.begin(), inventory.end(),
                         [&](const item &i) { return i.name == itemName.toUpper(); });
  if (it != inventory.end()) {
    int index = std::distance(inventory.begin(), it);
    return index;
  } else {
    return -1;
  }
}

QString Location::locInventory() const{
  QString inventoryText;
  inventoryText.append("You see:\n");
  for (const auto &item : inventory) {
    inventoryText.append(QString("%1\n").arg(item.name));
  }
  return inventoryText;
}

const item &Location::getInventoryItem(int index) const {
  return inventory[index];
}

void Location::addItem(const item &itemToAdd) { inventory.push_back(itemToAdd); }

void Location::removeItem(int index) {
  inventory.erase(inventory.begin() + index);
}

QString Location::getItemName(int index) const { return inventory[index].name; }

int Location::getItemEquipped(int index) const {
  return inventory[index].active;
}

void Location::setItemEquipped(int index, int value) {
  inventory[index].active = value;
}

int Location::getItemQuantity(int index) const {
  return inventory[index].amount;
}

void Location::setItemQuantity(int index, int value) {
  inventory[index].amount = value;
}

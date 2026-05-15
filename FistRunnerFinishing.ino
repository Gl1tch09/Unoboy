#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE); // OLED initialization

// 'MainCharacter', 40x20px (forward)
const unsigned char MainCharacterForward[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc7, 0x03, 0x00, 0x00, 
	0x60, 0x28, 0x0c, 0x00, 0x00, 0x18, 0xab, 0x31, 0x00, 0x00, 0xc4, 0x44, 0x44, 0x00, 0x00, 0x32, 
	0x82, 0x99, 0x00, 0x00, 0x95, 0x1d, 0x92, 0x00, 0x00, 0x5d, 0x22, 0xba, 0x00, 0x80, 0x5c, 0xdd, 
	0x3b, 0x01, 0x80, 0x1e, 0x3e, 0x68, 0x01, 0x80, 0xfe, 0xb6, 0x7f, 0x01, 0x80, 0xfe, 0xbe, 0x3b, 
	0x01, 0x80, 0x76, 0xdd, 0xbd, 0x00, 0x00, 0xbd, 0xe3, 0x5a, 0x00, 0x00, 0xe2, 0xff, 0x23, 0x00, 
	0x00, 0x1c, 0x00, 0x1c, 0x00, 0x00, 0xe0, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00
};

// 'MainCharacter', 40x20px (down)
const unsigned char MainCharacterDown[] PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x07, 0x00, 0x00, 
	0x38, 0x00, 0x38, 0x00, 0x00, 0xc4, 0xff, 0x47, 0x00, 0x00, 0x5a, 0xc7, 0xbd, 0x00, 0x00, 0xbd, 
	0xbb, 0x6e, 0x01, 0x80, 0xdc, 0x7d, 0x7f, 0x01, 0x80, 0xfe, 0x6d, 0x7f, 0x01, 0x80, 0x16, 0x7c, 
	0x78, 0x01, 0x80, 0xdc, 0xbb, 0x3a, 0x01, 0x00, 0x5d, 0x44, 0xba, 0x00, 0x00, 0x49, 0xb8, 0xa9, 
	0x00, 0x00, 0x99, 0x41, 0x4c, 0x00, 0x00, 0x22, 0x22, 0x23, 0x00, 0x00, 0x8c, 0xd5, 0x18, 0x00, 
	0x00, 0x30, 0x14, 0x06, 0x00, 0x00, 0xc0, 0xe3, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00 
};

// Enemy sprite facing up (40x20px)
const unsigned char EnemyUp[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 
	0xff, 0x07, 0x00, 0x00, 0x38, 0x00, 0x38, 0x00, 0x00, 0x04, 0x38, 0x40, 0x00, 0x00, 0x02, 0x44, 
	0x80, 0x00, 0x00, 0x03, 0x82, 0x80, 0x00, 0x00, 0x01, 0x82, 0x80, 0x00, 0x00, 0xe1, 0x83, 0x87, 
	0x00, 0x00, 0x23, 0x44, 0xc4, 0x00, 0x00, 0x22, 0x38, 0x44, 0x00, 0x00, 0x22, 0x00, 0x46, 0x00, 
	0x00, 0x66, 0x80, 0x33, 0x00, 0x00, 0x9c, 0xc1, 0x1c, 0x00, 0x00, 0x70, 0x22, 0x07, 0x00, 0x00, 
	0xc0, 0xe3, 0x01, 0x00 
};

// Enemy sprite facing down (40x20px)
const unsigned char EnemyDown[] PROGMEM = {
  0x00, 0x80, 0xc7, 0x03, 0x00, 0x00, 0xe0, 0x44, 0x0e, 0x00, 0x00, 0x38, 0x83, 0x39, 0x00, 0x00, 
	0xcc, 0x01, 0x66, 0x00, 0x00, 0x62, 0x00, 0x44, 0x00, 0x00, 0x22, 0x1c, 0x44, 0x00, 0x00, 0x23, 
	0x22, 0xc4, 0x00, 0x00, 0xe1, 0xc1, 0x87, 0x00, 0x00, 0x01, 0x41, 0x80, 0x00, 0x00, 0x01, 0x41, 
	0xc0, 0x00, 0x00, 0x01, 0x22, 0x40, 0x00, 0x00, 0x02, 0x1c, 0x20, 0x00, 0x00, 0x1c, 0x00, 0x1c, 
	0x00, 0x00, 0xe0, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00
};

// 'MainCharacterPunchStart', 40x20px (punching start)
const unsigned char MainCharacterPunchStartUp[] PROGMEM = {
    // Add the pixel data for the punch start frame here
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x00, 
	0x60, 0x08, 0x0f, 0x00, 0x00, 0x18, 0x8b, 0x30, 0x00, 0x00, 0xc4, 0x84, 0x46, 0x00, 0x00, 0x32, 
	0x02, 0x99, 0x00, 0x00, 0x95, 0x1d, 0xb3, 0x00, 0x00, 0xdd, 0x22, 0x92, 0x00, 0x80, 0xdc, 0xdd, 
	0x3b, 0x01, 0x80, 0x1e, 0x3e, 0x6c, 0x01, 0x80, 0xfe, 0xb6, 0x6f, 0x01, 0x80, 0xfe, 0xbe, 0x2b, 
	0x01, 0x80, 0x76, 0xdd, 0xbd, 0x00, 0x00, 0xbd, 0xe3, 0x5a, 0x00, 0x00, 0xe2, 0xff, 0x23, 0x00, 
	0x00, 0x1c, 0x00, 0x1c, 0x00, 0x00, 0xe0, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00
};



// 'MainCharacterPunchEndUp', 40x20px (punching end)
const unsigned char MainCharacterPunchEndUp[] PROGMEM = {
    // Add the pixel data for the punch end frame here
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x80, 0x17, 0x02, 0x00, 0x00, 
	0x60, 0xd8, 0x0c, 0x00, 0x00, 0x18, 0xab, 0x33, 0x00, 0x00, 0xc4, 0x44, 0x46, 0x00, 0x00, 0x32, 
	0x82, 0x99, 0x00, 0x00, 0x95, 0x1d, 0x92, 0x00, 0x00, 0x5d, 0x22, 0xbc, 0x00, 0x80, 0x5c, 0xdd, 
	0x3e, 0x01, 0x80, 0x1e, 0x3e, 0x6f, 0x01, 0x80, 0xfe, 0xb6, 0x7f, 0x01, 0x80, 0xfe, 0xbe, 0x3b, 
	0x01, 0x80, 0x76, 0xdd, 0xbd, 0x00, 0x00, 0xbd, 0xe3, 0x5a, 0x00, 0x00, 0xe2, 0xff, 0x23, 0x00, 
	0x00, 0x1c, 0x00, 0x1c, 0x00, 0x00, 0xe0, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00
};

// 'MainCharacterPunchStartDown', 40x20px (punching start)
const unsigned char MainCharacterPunchStartDown[] PROGMEM = {
    // Add the pixel data for the punch start frame here
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x07, 0x00, 0x00, 
	0x38, 0x00, 0x38, 0x00, 0x00, 0xc4, 0xff, 0x47, 0x00, 0x00, 0x5a, 0xc7, 0xbd, 0x00, 0x00, 0xbd, 
	0xbb, 0x6e, 0x01, 0x80, 0xd4, 0x7d, 0x7f, 0x01, 0x80, 0xf6, 0x6d, 0x7f, 0x01, 0x80, 0x36, 0x7c, 
	0x78, 0x01, 0x80, 0xdc, 0xbb, 0x3b, 0x01, 0x00, 0x49, 0x44, 0xbb, 0x00, 0x00, 0xcd, 0xb8, 0xa9, 
	0x00, 0x00, 0x99, 0x40, 0x4c, 0x00, 0x00, 0x62, 0x21, 0x23, 0x00, 0x00, 0x0c, 0xd1, 0x18, 0x00, 
	0x00, 0xf0, 0x10, 0x06, 0x00, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00
};



// 'MainCharacterPunchEndDown', 40x20px (punching end)
const unsigned char MainCharacterPunchEndDown[] PROGMEM = {
    // Add the pixel data for the punch end frame here
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x07, 0x00, 0x00, 
	0x38, 0x00, 0x38, 0x00, 0x00, 0xc4, 0xff, 0x47, 0x00, 0x00, 0x5a, 0xc7, 0xbd, 0x00, 0x00, 0xbd, 
	0xbb, 0x6e, 0x01, 0x80, 0xdc, 0x7d, 0x7f, 0x01, 0x80, 0xfe, 0x6d, 0x7f, 0x01, 0x80, 0xf6, 0x7c, 
	0x78, 0x01, 0x80, 0x7c, 0xbb, 0x3a, 0x01, 0x00, 0x3d, 0x44, 0xba, 0x00, 0x00, 0x49, 0xb8, 0xa9, 
	0x00, 0x00, 0x99, 0x41, 0x4c, 0x00, 0x00, 0x62, 0x22, 0x23, 0x00, 0x00, 0xcc, 0xd5, 0x18, 0x00, 
	0x00, 0x30, 0x1b, 0x06, 0x00, 0x00, 0x40, 0xe8, 0x01, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00
};

int punchAnimationFrame = 0; // 0: No punch, 1: Punch start, 2: Punch middle, 3: Punch end
unsigned long lastPunchTime = 0;  // Time to control punch animation speed
const unsigned long punchDuration = 100; // How long each frame of the punch animation lasts (milliseconds)



// Buttons pins for movement
const int Up = 2;
const int Down = 3;
const int Right = 4;
const int Left = 5;

// Button pins for actions
const int Punch = 6;
const int Sprint = 7;

// Character dimensions and position
const int characterWidth = 40;
const int characterHeight = 20;

int killCounter = 0;  // Variable to track the number of kills

// Screen offset variables
int screenOffsetX = 0;
int screenOffsetY = 0;

// Enemy positions and directions
const int MAX_ENEMIES = 5;
int enemies[MAX_ENEMIES][3]; // [x, y, direction]

// World dimensions
const int WORLD_WIDTH = 350;
const int WORLD_HEIGHT = 350;
const int BORDER_OFFSET_X = 20;
const int BORDER_OFFSET_Y = 20;

// Direction tracking
int direction = 0;  // 0: forward, 180: down

// Sprint mechanic variables
bool isSprinting = false;  // Sprint state
unsigned long sprintCooldown = 0;  // Sprint cooldown time
const unsigned long sprintCooldownDuration = 3000;  // Cooldown duration in milliseconds
const int sprintSpeed = 4;  // Speed during sprint
const int normalSpeed = 2;  // Normal speed

// Health variables
const int maxHealth = 20;
int playerHealth = 20;

bool isPunching = false;
const uint8_t* spriteToDraw = nullptr;
void drawHealthBar() {
    int barWidth = 50;  // Width of the health bar
    int barHeight = 5;  // Height of the health bar
    int barX = 5;       // Bottom-left corner of the screen
    int barY = 64 - barHeight - 5; // 5 pixels above the bottom edge

    // Draw the outline of the health bar
    u8g2.drawFrame(barX, barY, barWidth, barHeight);

    // Calculate the current health bar width
    int currentWidth = map(playerHealth, 0, maxHealth, 0, barWidth);

    // Draw the filled portion of the health bar
    u8g2.drawBox(barX, barY, currentWidth, barHeight);

    // Draw the health as text beside the bar
    u8g2.setFont(u8g2_font_6x10_tf); // Adjust font size if needed
    u8g2.setCursor(barX + barWidth + 5, barY + barHeight - 1);
    u8g2.print(playerHealth);
    u8g2.print("/");
    u8g2.print(maxHealth);
}

// Add an array for enemy health
int enemyHealth[MAX_ENEMIES];

// Update setup function to initialize enemy health
void setup() {
    u8g2.begin();
    pinMode(Up, INPUT);
    pinMode(Down, INPUT);
    pinMode(Right, INPUT);
    pinMode(Left, INPUT);
    pinMode(Punch, INPUT);  // Punch button setup
    pinMode(Sprint, INPUT); // Sprint button setup

    // Set player starting position to the center of the world
    screenOffsetX = (WORLD_WIDTH / 2) - (128 / 2); // Center horizontally
    screenOffsetY = (WORLD_HEIGHT / 2) - (64 / 2); // Center vertically

    // Randomly place enemies
    randomSeed(analogRead(0));
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i][0] = random(0, WORLD_WIDTH);  // x position
        enemies[i][1] = random(0, WORLD_HEIGHT); // y position
        enemies[i][2] = random(0, 2) * 180;     // direction: 0 or 180 (up or down)
        enemyHealth[i] = 4;  // Set initial health for each enemy
    }
}

void drawKillCounter() {
  u8g2.setFont(u8g2_font_ncenB08_tr);  // Set a font for displaying text
  u8g2.setCursor(45, 10);               // Set cursor position on the screen
  u8g2.print("KnockOuts: ");                // Print "KnockOuts: "
  u8g2.print(killCounter);              // Print the kill counter value
}


unsigned long lastHitTime[MAX_ENEMIES] = {0};

void moveEnemiesTowardsPlayer() {
    int playerX = screenOffsetX + 64 - characterWidth / 2;
    int playerY = screenOffsetY + 32 - characterHeight / 2;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        // Check for collision
        if (checkCollision(enemies[i][0], enemies[i][1], playerX, playerY)) {
            // Check if enough time has passed since the last hit
            if (millis() - lastHitTime[i] >= 2500) {
                playerHealth = max(0, playerHealth - 1); // Reduce health
                lastHitTime[i] = millis(); // Update the hit timestamp
            }
            continue;
        }

        // Move enemy towards player
        if (enemies[i][0] < playerX) enemies[i][0]++;
        else if (enemies[i][0] > playerX) enemies[i][0]--;

        if (enemies[i][1] < playerY) enemies[i][1]++;
        else if (enemies[i][1] > playerY) enemies[i][1]--;
    }
}

// Function to check collision between player and enemies
bool checkCollision(int enemyX, int enemyY, int playerX, int playerY) {
    return !(enemyX + 40 <= playerX || // Enemy is to the left of the player
             enemyX >= playerX + characterWidth || // Enemy is to the right of the player
             enemyY + 20 <= playerY || // Enemy is above the player
             enemyY >= playerY + characterHeight); // Enemy is below the player
}

void drawBorders() {
     // Top border
    u8g2.drawHLine(0 - screenOffsetX + BORDER_OFFSET_X, 0 - screenOffsetY + BORDER_OFFSET_Y, WORLD_WIDTH - 2 * BORDER_OFFSET_X);

    // Bottom border
    u8g2.drawHLine(0 - screenOffsetX + BORDER_OFFSET_X, WORLD_HEIGHT - 1 - screenOffsetY - BORDER_OFFSET_Y, WORLD_WIDTH - 2 * BORDER_OFFSET_X);

    // Left border
    u8g2.drawVLine(0 - screenOffsetX + BORDER_OFFSET_X, 0 - screenOffsetY + BORDER_OFFSET_Y, WORLD_HEIGHT - 2 * BORDER_OFFSET_Y);

    // Right border
    u8g2.drawVLine(WORLD_WIDTH - 1 - screenOffsetX - BORDER_OFFSET_X, 0 - screenOffsetY + BORDER_OFFSET_Y, WORLD_HEIGHT - 2 * BORDER_OFFSET_Y);
}

// Function to handle punching logic
// Function to handle punching logic
void handlePunch() {
    int playerX = screenOffsetX + 64 - characterWidth / 2;
    int playerY = screenOffsetY + 32 - characterHeight / 2;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        // Check if the enemy is within a larger punching range (e.g., within a 30-pixel radius)
        if (abs(enemies[i][0] - playerX) <= 40 && abs(enemies[i][1] - playerY) <= 25) {
            // Deal 1 damage to the enemy if it's still alive
            if (enemyHealth[i] > 0) {
                enemyHealth[i] = max(0, enemyHealth[i] - 1);  // Reduce enemy health

                // If the enemy's health is 0, reset the enemy's position and health
                if (enemyHealth[i] == 0) {
                    enemies[i][0] = random(0, WORLD_WIDTH);  // Reset enemy position
                    enemies[i][1] = random(0, WORLD_HEIGHT);
                    killCounter++;  // Increment kill counter by 1
                    enemyHealth[i] = 4;  // Reset enemy health to 4
                }
            }
        }
    }
   if (!digitalRead(Punch) && millis() - lastPunchTime > punchDuration) {
        punchAnimationFrame = (punchAnimationFrame + 1) % 3; // Cycle between 0, 1, and 2
        lastPunchTime = millis();
    }

    // Select sprite based on direction and punch state
    

    if (direction == 0) { // Forward direction
        if (punchAnimationFrame == 1) {
            spriteToDraw = MainCharacterPunchStartUp;
        } else if (punchAnimationFrame == 2) {
            spriteToDraw = MainCharacterPunchEndUp;
        } else {
            spriteToDraw = MainCharacterForward;
        }
    } else { // Downward direction (180 degrees)
        if (punchAnimationFrame == 1) {
            spriteToDraw = MainCharacterPunchStartDown;
        } else if (punchAnimationFrame == 2) {
            spriteToDraw = MainCharacterPunchEndDown;
        } else {
            spriteToDraw = MainCharacterDown;
        }
    }

}

// In the draw loop:


void loop() {
    u8g2.clearBuffer();


 // Handle sprint mechanic
    if (digitalRead(Sprint) == LOW && millis() - sprintCooldown >= sprintCooldownDuration) {
        isSprinting = true;
        sprintCooldown = millis();  // Update the cooldown
    } else {
        isSprinting = false;
    }

    //int moveSpeed = isSprinting ? sprintSpeed : normalSpeed;  // Use sprint speed if sprinting
    int moveSpeed = digitalRead(Sprint) == LOW ? 4 : 2;  // Sprinting speed is 4, normal is 2

    // Movement logic with sprint speed adjustment
    if (digitalRead(Up) == LOW) {
        screenOffsetY = max(0, screenOffsetY - moveSpeed);  // Adjust speed based on sprint
        direction = 0;  // Moving forward
    }
    if (digitalRead(Down) == LOW) {
        screenOffsetY = min(WORLD_HEIGHT - 64, screenOffsetY + moveSpeed);  // Adjust speed based on sprint
        direction = 180;  // Moving down
    }
    if (digitalRead(Left) == LOW) {
        screenOffsetX = max(0, screenOffsetX - moveSpeed);  // Adjust speed based on sprint
    }
    if (digitalRead(Right) == LOW) {
        screenOffsetX = min(WORLD_WIDTH - 128, screenOffsetX + moveSpeed);  // Adjust speed based on sprint
    }


    // Handle punching logic
    if (digitalRead(Punch) == LOW) {
        handlePunch();
    }

    // Move enemies
    moveEnemiesTowardsPlayer();

    int playerX = screenOffsetX + 64 - characterWidth / 2;
    int playerY = screenOffsetY + 32 - characterHeight / 2;

    // Draw the world borders
    drawBorders();


    // Draw the enemies with adjusted direction
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i][1] < playerY) {
            enemies[i][2] = 0;  // Enemy facing up
        } else {
            enemies[i][2] = 180;  // Enemy facing down
        }

        // Render the enemy sprite based on direction
        if (enemies[i][2] == 0) {  // Up direction
            u8g2.drawXBMP(enemies[i][0] - screenOffsetX, enemies[i][1] - screenOffsetY, characterWidth, characterHeight, EnemyUp);
        } else {  // Down direction
            u8g2.drawXBMP(enemies[i][0] - screenOffsetX, enemies[i][1] - screenOffsetY, characterWidth, characterHeight, EnemyDown);
        }
    }

    

    // Check punch animation first (priority over direction)
    if (punchAnimationFrame == 0) {  // If not punching
    // Draw the player's regular sprite (forward or down)
    if (direction == 0) {
        spriteToDraw = MainCharacterForward;
    } else if (direction == 180) {
        spriteToDraw = MainCharacterDown;
    }
}


    // Draw the determined sprite if any
    if (spriteToDraw) {
        u8g2.drawXBMP(64 - characterWidth / 2, 32 - characterHeight / 2, characterWidth, characterHeight, spriteToDraw);
    }
    drawHealthBar(); 
drawKillCounter();
    u8g2.sendBuffer();
    delay(50);  
}
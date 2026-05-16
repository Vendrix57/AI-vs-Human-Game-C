# Player vs. AI: Battle Engine (C)

A sophisticated command-line combat simulator where a player faces off against a strategic AI. The project demonstrates advanced C concepts including heuristic-based decision making, custom UI elements, and real-time game loops.

## 🧠 Strategic AI Engine

Unlike simple games that use random numbers for enemy actions, this project features a custom **AI Decision Engine**. The AI calculates a "utility score" for every possible move based on:
* **Self-Preservation:** The AI is more likely to heal when its HP drops below 30.
* **Aggression Tracking:** If the player attacks frequently, the AI increases its own attack priority.
* **Special Move Optimization:** The AI "holds" its powerful special attack until the player's health is low enough for a potential finishing blow.



## 🎮 Features

* **Dynamic Visuals:** Includes a custom-built `hpBar` function that renders visual health bars using ASCII characters.
* **Combat Mechanics:** * **Attack:** Reliable 20 damage.
    * **Heal:** Restore 15 HP (capped at 100).
    * **Special Attack:** High-risk, high-reward move (35-50 damage) available only once per match.
* **Immersive UI:** Utilizes system delays (`sleep`) and screen clearing (`cls`) to create a polished, "animated" feel in the console.

## 🛠️ Technical Implementation

* **Heuristics:** Uses a scoring algorithm (`ai_decision`) to simulate intelligent behavior.
* **Randomization:** Employs `srand(time(NULL))` to ensure varied damage for special attacks.
* **Input Handling:** Robust turn validation ensures players cannot use their special move more than once or enter invalid commands.

## 📋 How to Run

1.  **Compile the code:**
    ```bash
    gcc battle.c -o battle
    ```
2.  **Run the executable:**
    ```bash
    ./battle
    ```

## 🕹️ Gameplay Preview

```text
=====================================
          ROUND 04
=====================================

Player HP:  85 [########--]
AI     HP:  60 [######----]

-------------------------------------
Actions:
 a -> Attack (20 dmg)
 h -> Heal (15 HP)
 b -> Special Attack (35-50 dmg, once)
-------------------------------------
Your choice: a

You attacked and dealt 20 damage!

AI is thinking...
AI chose *** SPECIAL ATTACK ***!
AI dealt 42 damage!

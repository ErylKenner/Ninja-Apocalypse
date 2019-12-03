# Ninja-Apocalypse
## Gameplay
Stylized top-down survival shooter. Survive increasingly stronger waves of ninjas using guns found throughout the map. Each gun starts with a limited amount of ammo. When a gun runs out of ammo it cannot be used anymore, however it can be thrown at an emeny for a 1-shot as its final attack.

If the player survives enough waves, they will be transported to a boss arena where a powerful boss will try to defeat them. If they manage to survive the terrible monster, they will teleport to the final map. The game is then infinite as the player tries to survive as long for as possible.

## Game Engine
Written in C++ using a custom game engine built off of the Ogre graphics engine. I implemented a rigid-body collision system which handles collisions and queues callback functions. Rectangle and circle colliders are implemented currently. I also added static terrain path-planning so enemies can navigate arbitrary maps. This makes adding additional maps simple.

## Controls
| Button  | Action |
| ------------- | ------------- |
| W  | Forward  |
| S  | Backward  |
| A  | Left |
| D  | Right  |
| Move Mouse  | Aim  |
| Left Mouse  | Shoot  |
| Right Mouse  | Throw Gun  |

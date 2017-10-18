# 4_Krazy_Karts
(ref: KK_UEM)

### 1 Creating A Go-Kart Pawn ###

+ Create the project.
+ Create a pawn.
+ Setup GameMode Spawning.
+ Setup Camera.
+ Attach throttle controls.

### 2 Understanding Forces And Movement ###

+ Revision of forces in physics.
+ Calculating movement from force.
+ Providing the driving force.

### 3 Blocking Movement Without Physics ###

+ Setting up collision volumes.
+ Sweeping with `AddActorWorldOffset`.
+ Resetting velocity on collision.
+ Refactoring the `Tick` function.

### 4 Rotations With Quaternions ###

+ Angle axis rotations with FQuat.
+ Adding rotations actors.
+ Rotating our velocity.

### 5 Simulating Air Resistance ###

+ Understanding air resistance.
+ Getting the "speed".
+ Calculating force due to air resistance.

### 6 Simulating Rolling Resistance ###

+ What is rolling resistance?
+ Finding the gravity in Unreal.
+ Implementing rolling resistance.
+ Example rolling resistance coeffients. 

### 7 Steering And Turning Circles ###

+ Why we get turning circles.
+ Calculating our rotation geometry.
+ Correcting steering behaviour.

### 8 Server Functions & Cheat Protection ###

+ How to change state from the client.
+ Introduction to RPC server functions.
+ What is validation?
+ Implementing validation for input.
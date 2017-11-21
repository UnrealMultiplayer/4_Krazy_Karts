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

### 9 AutonomousProxy vs SimulatedProxy ###

+ What are Actor roles?
+ Investigating the network roles.
+ Updating the `AutonomousProxy`.

### 10 Sources Of Simulation Error ###

+ How simulation error effect our game.
+ Overview the different sources of error.
+ Investigate approaches to eliminating them.

### 11 Replicating Variables From The Server ###

+ Overview of property replication.
+ Replicating the actor position.
+ Setting and reading the property.
+ Replicating the actor rotation.

### 12 Triggering Code On Replication ###

+ Deep dive on property replication.
+ Setting the network update interval.
+ Notify on replicate.
+ Simulate between updates.

### 13 Smooth Simulated Proxies ###

+ Replicating velocity.
+ Why is movement jerky?
+ Replicating control input to SimulatedProxy.

### 14 Simulating Lag And Packet Loss ###

+ What is lag?
+ Simulating lag and packet loss.
+ Why does lag cause glitching?

### 15 Replay Autonomous Moves ###

+ Why do we reset when accelerating?
+ Keeping AutonomousProxy ahead of the Server.
+ What information needs to be sent to the server.
+ Compare our different simulation approaches.

### 16 Planning Client-Side Prediction ###

+ Pseudocode for client prediction.
+ Adding structs for synchronisation.

### 17 Replicating Structs ###

+ What do we have already?
+ Replicating state via a struct.
+ Sending the `Move` struct via RPC.

### 18 Simulating A Move ###

+ The `SimulateMove` signature.
+ Updating the canonical state.
+ Implement `SimulateMove`.

### 19 Unacknowledged Move Queue ###

+ `TArray` for the Move queue.
+ Tidying the move creation code.
+ Printing the queue length.
+ Removing acknowledged moves.

### 20 Simulating Unacknowledged Moves ###

+ Simulate all moves.
+ Testing for smoothness.
+ How can we still make it glitch?
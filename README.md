## Movement

> Used to move around the world.
> * **"north"** or **"n"**: go to the north.
> * **"east"** or **"e"**: go to the east.
> * **"south"** or **"s"**: go to the south.
> * **"west"** or **"w"**: go to the west.
> * "go north", "go east", "go south" and "go west" achieve the same.
	
## Look
> Used to get information out of objects in the world (items, rooms, exits, creatures)
> * **"look"**: info about the room the player is in
> * **"look me"** or **"look myself"**: info about the player
> * **"look"** + nameOfObject: info about the object with the name nameOfObject

## Open
> Used to open items to see if they have extra items inside. Descriptions give hints of which objects can be opened.
> * **"open"** + nameOfObject
> Some objects require a key to be opened. 
> * **"open"** + nameOfObject + **"with"** + nameOfKey
	
## Take
> Used to take items into inventory. Not all items can be taken.
> * **"take"** + nameOfObject
	
## Drop
> Used to drop items in a room.
> * **"drop"** + nameOfObject 
> The items can also be dropped or placed inside other items. 
> * **"drop"** + nameOfObjectToDrop + **"in"** or **"into"** + nameOfContainer
	
## Unlock
> Used to unlock exits.
> * **"unlock"** + direction (north, east, south, or west) + **"with"** + nameOfKey
	
## Touch
> Used to interact with creatures in the world.
> * **"touch"** + nameOfCreature

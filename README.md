# OnPlayerLookAtObject
Script that checks whether the player is aiming at any object

## Installation
- Download incliude from *link*
- Add include to your gamemode using
```pawn
#include <s_aimobject>
```

## Callbacks
```pawn
OnPlayerAimAtObject(playerid, objectid)
```
- playerid - ID of the player who aimed at the object
+ objectid - ID of the object the player aimed at
  + INVALID_OBJECT_ID if the player stops aiming at any objects

```pawn
OnPlayerAimAtDynamicObject(playerid, objectid)
```
- playerid - ID of the player who aimed at the dynamic object
+ objectid - ID of the dynamic object the player aimed at
  + 0 if the player stops aiming at any dynamic objects

## Example of using
```pawn
public OnPlayerAimAtObject(playerid, objectid)
{
	if(objectid == 65535) return SendClientMessage(playerid, -1, "You stopped aiming at the object");

	new chatStr[30];
	format(chatStr, sizeof(chatStr), "You aimed at the object %i", objectid);
	SendClientMessage(playerid, -1, chatStr);
	return 1;
}

public OnPlayerAimAtDynamicObject(playerid, objectid)
{
	if(objectid == 0) return SendClientMessage(playerid, -1, "You stopped aiming at the dynamic object");

	new chatStr[38];
	format(chatStr, sizeof(chatStr), "You aimed at the dynamic object %i", objectid);
	SendClientMessage(playerid, -1, chatStr);
	return 1;
}
```

/*
*								s_aimobject include
*							by #Samurai aka Un[x]pected
*/

/********************* Defines *********************/
#if !defined PRESSED
    #define PRESSED(%0) 		(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#endif
#if !defined RELEASED
	#define RELEASED(%0)		(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
#endif
#if !defined KEY_AIM
    #define KEY_AIM				(128)
#endif

#define TARGET_TIMER_INTERVAL	(200)

/********************* Callbacks *********************/
forward OnPlayerAimAtObject(playerid, objectid);
forward OnPlayerAimAtDynamicObject(playerid, objectid);

/********************* Variables *********************/
static targetTimer[MAX_PLAYERS],
	lastTargetObj[MAX_PLAYERS],
	lastDynTargetObj[MAX_PLAYERS];

/********************* Hooks *********************/
public OnPlayerConnect(playerid)
{
	lastTargetObj[playerid] = INVALID_OBJECT_ID;
	lastDynTargetObj[playerid] = 0;

	#if defined ExOnPlayerConnect	
		return ExOnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect ExOnPlayerConnect

#if defined ExOnPlayerConnect
	forward ExOnPlayerConnect(playerid);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_AIM))
    {
    	targetTimer[playerid] = SetTimerEx("TargetObjectTimer", TARGET_TIMER_INTERVAL, true, "i", playerid);
    	EnablePlayerCameraTarget(playerid, true);
    }
    if(RELEASED(KEY_AIM))
    {
		if(lastTargetObj[playerid] != INVALID_OBJECT_ID)
		{
    		lastTargetObj[playerid] = INVALID_OBJECT_ID;
    		OnPlayerAimAtObject(playerid, INVALID_OBJECT_ID);
		}
		if(lastDynTargetObj[playerid] != 0)
		{
    		lastDynTargetObj[playerid] = 0;
    		OnPlayerAimAtDynamicObject(playerid, 0);
		}

    	KillTimer(targetTimer[playerid]);
    	EnablePlayerCameraTarget(playerid, false);
    }
	#if defined ExOnPlayerKeyStateChange	
		return ExOnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange ExOnPlayerKeyStateChange

#if defined ExOnPlayerKeyStateChange
	forward ExOnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

/********************* Timers *********************/
forward TargetObjectTimer(playerid);
public TargetObjectTimer(playerid)
{
	new objectid;

	objectid = GetPlayerCameraTargetObject(playerid);
    if(lastTargetObj[playerid] != objectid)
	{
		lastTargetObj[playerid] = objectid;
		OnPlayerAimAtObject(playerid, objectid);
	}

	// For use with a streamer include
	#if defined _streamer_included
	objectid = GetPlayerCameraTargetDynObject(playerid);
    if(lastDynTargetObj[playerid] != objectid)
	{
		lastDynTargetObj[playerid] = objectid;
		OnPlayerAimAtDynamicObject(playerid, objectid);
	}
	#endif
}

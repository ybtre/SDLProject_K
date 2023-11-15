
typedef enum
{
    DOOR_LEFT,
    DOOR_RIGHT,
    DOOR_TOP,
    DOOR_BOT,

    NUM_DOORS,
} DoorSide;

typedef struct Room
{
    int         id;
    //index 0 - left, 1 - right, 2 - top, 3 - bot
    int         doors[NUM_DOORS];
    int         neighbours[NUM_DOORS]; // id of connected door at DOOR side
    int         neighbours_count;

    int         x;
    int         y;
    SDL_Rect    dest;
    SDL_Rect    dest_doors[NUM_DOORS];
} Room;

Room starting_room = {};
#define ROOMS_TO_GEN            9
Room all_rooms[ROOMS_TO_GEN];

Room create_room(int ID, int PREV_R_ID, int PREV_DOOR, int X, int Y)
{
    Room r;

    for(int i = 0; i < NUM_DOORS; i++)
    {
        r.doors[i]          = rand() % 2;
        r.neighbours[i]     = -1;
    }
    
    r.id     = ID;
    r.x      = X;
    r.y      = Y;

    if(PREV_R_ID != -1)
    {
        r.neighbours_count++;

        if(PREV_DOOR == DOOR_LEFT)
        {
            r.neighbours[DOOR_RIGHT]     = PREV_R_ID;
            r.doors[DOOR_RIGHT]          = 1;
        }
        elif(PREV_DOOR == DOOR_RIGHT)
        {
            r.neighbours[DOOR_LEFT]      = PREV_R_ID;
            r.doors[DOOR_LEFT]           = 1;
        }
        elif(PREV_DOOR == DOOR_TOP)
        {
            r.neighbours[DOOR_BOT]       = PREV_R_ID;
            r.doors[DOOR_BOT]            = 1;
        }
        elif(PREV_DOOR == DOOR_BOT)
        {
            r.neighbours[DOOR_TOP]       = PREV_R_ID;
            r.doors[DOOR_TOP]            = 1;
        }
    }

    r.dest.w = 16 * SCREEN_SCALE;
    r.dest.h = 16 * SCREEN_SCALE;
    r.dest.x = r.x - (r.dest.w / 2);
    r.dest.y = r.y - (r.dest.h / 2);

    r.dest_doors[DOOR_LEFT].w = 2 * SCREEN_SCALE;
    r.dest_doors[DOOR_LEFT].h = 4 * SCREEN_SCALE;
    r.dest_doors[DOOR_LEFT].x = (r.dest.x - (r.dest_doors[DOOR_LEFT].w / 2));
    r.dest_doors[DOOR_LEFT].y = (r.dest.y - (r.dest_doors[DOOR_LEFT].h / 2)) + r.dest.h /2;

    r.dest_doors[DOOR_RIGHT].w = 2 * SCREEN_SCALE;
    r.dest_doors[DOOR_RIGHT].h = 4 * SCREEN_SCALE;
    r.dest_doors[DOOR_RIGHT].x = (r.dest.x - (r.dest_doors[DOOR_LEFT].w / 2) + (r.dest.h ));
    r.dest_doors[DOOR_RIGHT].y = (r.dest.y - (r.dest_doors[DOOR_LEFT].h / 2)) + r.dest.h /2;

    r.dest_doors[DOOR_TOP].w = 4 * SCREEN_SCALE;
    r.dest_doors[DOOR_TOP].h = 2 * SCREEN_SCALE;
    r.dest_doors[DOOR_TOP].x = (r.dest.x - (r.dest_doors[DOOR_TOP].w / 2)) + r.dest.w /2;
    r.dest_doors[DOOR_TOP].y = (r.dest.y - (r.dest_doors[DOOR_LEFT].h / 2)) + r.dest_doors[DOOR_TOP].h / 2;

    r.dest_doors[DOOR_BOT].w = 4 * SCREEN_SCALE;
    r.dest_doors[DOOR_BOT].h = 2 * SCREEN_SCALE;
    r.dest_doors[DOOR_BOT].x = (r.dest.x - (r.dest_doors[DOOR_BOT].w / 2)) + r.dest.w /2;
    r.dest_doors[DOOR_BOT].y = (r.dest.y - (r.dest_doors[DOOR_BOT].h / 2)) + r.dest.h;

    return(r);
}

void generate_floor(int SEED)
{
    SDL_Rect bounds = 
    {
        32 * SCREEN_SCALE, 32 * SCREEN_SCALE, 256 * SCREEN_SCALE, 128 * SCREEN_SCALE
    };


    //41good 42 breaks 43good
    srand(43);

    starting_room = create_room( 0, -1, -1, SCR_W/2, SCR_H/2);

    all_rooms[0] = starting_room;

    SDL_Log("Starting room doors: %i %i %i %i", starting_room.doors[0], starting_room.doors[1],starting_room.doors[2],starting_room.doors[3]);
   
    Room prev_r;
    Room r;
    for(int i = 1; i < ROOMS_TO_GEN; i++)
    {
        r = all_rooms[i];
        prev_r = all_rooms[i-1];

        int margin = 5 * SCREEN_SCALE;
        int new_room_door = rand() % 4;
        int cycles = 0;
        int doors_count = 0;
        do
        {
            SDL_Log("new room: %i; new door: %i, state: %i", i, new_room_door, prev_r.doors[new_room_door]);

            if(prev_r.doors[new_room_door] == 1)
            {
                //make new room here
                if(new_room_door == DOOR_LEFT)
                {
                    SDL_Log("Prev ID: %i, New ID: %i", prev_r.neighbours[DOOR_RIGHT], i);
                    if(prev_r.neighbours[DOOR_RIGHT]== i)
                        continue;

                    r = create_room(i, prev_r.id, DOOR_LEFT, prev_r.x - prev_r.dest.w - margin, prev_r.y);

                    all_rooms[i] = r;
                    doors_count = 0;
                }
                elif(new_room_door == DOOR_RIGHT)
                {
                    SDL_Log("Prev ID: %i, New ID: %i", prev_r.neighbours[DOOR_LEFT], i);
                    if(prev_r.neighbours[DOOR_LEFT]== i)
                        continue;

                    r = create_room(i, prev_r.id, DOOR_RIGHT, prev_r.x + prev_r.dest.w + margin, prev_r.y);

                    all_rooms[i] = r;
                    doors_count = 0;
                }
                elif(new_room_door == DOOR_TOP)
                {
                    SDL_Log("Prev ID: %i, New ID: %i", prev_r.neighbours[DOOR_BOT], i);
                    if(prev_r.neighbours[DOOR_BOT]== i)
                        continue;

                    r = create_room(i, prev_r.id, DOOR_TOP, prev_r.x, prev_r.y - prev_r.dest.h - margin);

                    all_rooms[i] = r;
                    doors_count = 0;
                }
                elif(new_room_door == DOOR_BOT)
                {
                    SDL_Log("Prev ID: %i, New ID: %i", prev_r.neighbours[DOOR_TOP], i);
                    if(prev_r.neighbours[DOOR_TOP]== i)
                        continue;

                    r = create_room(i, prev_r.id, DOOR_BOT, prev_r.x, prev_r.y + prev_r.dest.h + margin);

                    all_rooms[i] = r;
                    doors_count = 0;
                }
            }
            else
            {
                doors_count++;
                new_room_door = rand() % 4;
                cycles++;

                if(doors_count >= 4)
                {
                    i--;
                    
                    if(i < 0)
                    {
                        //TODO:
                        SDL_Log("ERROR, COULD NOT GENERATE FLOOR");
                        i = 999;
                        cycles = 999;
                        break;
                    }
                }
            }

        }
        while(prev_r.doors[new_room_door] != 1 AND cycles < 100);

    }
    SDL_Log("Floor Gen Done.");
}

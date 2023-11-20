
#define ROOMS_TO_GEN            9
Room all_rooms[ROOMS_TO_GEN];

Room get_room_at_pos(int X, int Y);
void find_neighbours();

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
        //TODO: somehow this gets insanely high?????????
        r.neighbours_count++;
    
        // need better solution to connect neighbours
        if(PREV_DOOR == DOOR_LEFT)
        {
            r.neighbours[DOOR_RIGHT]                    = PREV_R_ID;
            r.doors[DOOR_RIGHT]                         = 1;
            all_rooms[PREV_R_ID].neighbours[DOOR_LEFT]  = r.id;
        }
        elif(PREV_DOOR == DOOR_RIGHT)
        {
            r.neighbours[DOOR_LEFT]                     = PREV_R_ID;
            r.doors[DOOR_LEFT]                          = 1;
            all_rooms[PREV_R_ID].neighbours[DOOR_RIGHT] = r.id;
        }
        elif(PREV_DOOR == DOOR_TOP)
        {
            r.neighbours[DOOR_BOT]                      = PREV_R_ID;
            r.doors[DOOR_BOT]                           = 1;
            all_rooms[PREV_R_ID].neighbours[DOOR_TOP]   = r.id;
        }
        elif(PREV_DOOR == DOOR_BOT)
        {
            r.neighbours[DOOR_TOP]                      = PREV_R_ID;
            r.doors[DOOR_TOP]                           = 1;
            all_rooms[PREV_R_ID].neighbours[DOOR_BOT]   = r.id;
        }
    }

    r.dest.w = 6 * SCREEN_SCALE;
    r.dest.h = 6 * SCREEN_SCALE;
    r.dest.x = r.x - (r.dest.w / 2);
    r.dest.y = r.y - (r.dest.h / 2);

    r.dest_doors[DOOR_LEFT].w = 1 * SCREEN_SCALE;
    r.dest_doors[DOOR_LEFT].h = 1 * SCREEN_SCALE;
    r.dest_doors[DOOR_LEFT].x = (r.dest.x - (r.dest_doors[DOOR_LEFT].w / 2));
    r.dest_doors[DOOR_LEFT].y = (r.dest.y - (r.dest_doors[DOOR_LEFT].h / 2)) + r.dest.h /2;

    r.dest_doors[DOOR_RIGHT].w = 1 * SCREEN_SCALE;
    r.dest_doors[DOOR_RIGHT].h = 1 * SCREEN_SCALE;
    r.dest_doors[DOOR_RIGHT].x = (r.dest.x - (r.dest_doors[DOOR_LEFT].w / 2) + (r.dest.h ));
    r.dest_doors[DOOR_RIGHT].y = (r.dest.y - (r.dest_doors[DOOR_LEFT].h / 2)) + r.dest.h /2;

    r.dest_doors[DOOR_TOP].w = 1 * SCREEN_SCALE;
    r.dest_doors[DOOR_TOP].h = 1 * SCREEN_SCALE;
    r.dest_doors[DOOR_TOP].x = (r.dest.x - (r.dest_doors[DOOR_TOP].w / 2)) + r.dest.w /2;
    r.dest_doors[DOOR_TOP].y = (r.dest.y - (r.dest_doors[DOOR_LEFT].h / 2)) + r.dest_doors[DOOR_TOP].h / 2;

    r.dest_doors[DOOR_BOT].w = 1 * SCREEN_SCALE;
    r.dest_doors[DOOR_BOT].h = 1 * SCREEN_SCALE;
    r.dest_doors[DOOR_BOT].x = (r.dest.x - (r.dest_doors[DOOR_BOT].w / 2)) + r.dest.w /2;
    r.dest_doors[DOOR_BOT].y = (r.dest.y - (r.dest_doors[DOOR_BOT].h / 2)) + r.dest.h;

    return(r);
}

char check(int X, int Y)
{
    char neigh_id = -1;

    Room tmp = create_room(-2, -1, -1, X, Y);

    for(int i = 0; i < ROOMS_TO_GEN; i++)
    {
        Room t = all_rooms[i];

        if(t.x == tmp.x 
            AND t.y == tmp.y)
        {
            SDL_Log("Found neighbour %i %i at %i %i NEIGH ID %i", t.x, t.y, tmp.x, tmp.y, t.id);
            neigh_id = t.id;
            break;
        }
    }

    return(neigh_id);
}

void find_neighbours(Room *ROOM)
{
    int x, y, count, margin, res_id;
    count = 0;
    margin = 2 * SCREEN_SCALE;
    Room *neigh;

    x = ROOM->x - ROOM->dest.w - margin;
    y = ROOM->y;
    res_id = check(x, y);
    if(res_id != -1)
    {
        count++;
        SDL_Log("LEFT NEIGH");
        neigh = &all_rooms[res_id];
        ROOM->neighbours[DOOR_LEFT]     = res_id;
        ROOM->doors[DOOR_LEFT]          = 1;
        neigh->neighbours[DOOR_RIGHT]   = ROOM->id;
        neigh->doors[DOOR_RIGHT]        = 1;
    };
    x = ROOM->x + ROOM->dest.w + margin;
    y = ROOM->y;
    res_id = check(x, y);
    if(res_id != -1)
    {
        count++;
        SDL_Log("RIGHT NEIGH");
        neigh = &all_rooms[res_id];
        ROOM->neighbours[DOOR_RIGHT]     = res_id;
        ROOM->doors[DOOR_RIGHT]          = 1;
        neigh->neighbours[DOOR_LEFT]     = ROOM->id;
        neigh->doors[DOOR_LEFT]          = 1;
    };
    x = ROOM->x;
    y = ROOM->y - ROOM->dest.h - margin;
    res_id = check(x, y);
    if(res_id != -1)
    {
        count++;
        SDL_Log("TOP NEIGH");
        neigh = &all_rooms[res_id];
        ROOM->neighbours[DOOR_TOP]      = res_id;
        ROOM->doors[DOOR_TOP]           = 1;
        neigh->neighbours[DOOR_BOT]     = ROOM->id;
        neigh->doors[DOOR_BOT]          = 1;
    };
    x = ROOM->x;
    y = ROOM->y + ROOM->dest.h + margin;
    res_id = check(x, y);
    if(res_id != -1)
    {
        count++;
        SDL_Log("BOT NEIGH");
        neigh = &all_rooms[res_id];
        ROOM->neighbours[DOOR_BOT]      = res_id;
        ROOM->doors[DOOR_BOT]           = 1;
        neigh->neighbours[DOOR_TOP]     = ROOM->id;
        neigh->doors[DOOR_TOP]          = 1;
    };

}

char check_neighboor(Room ROOM, int DIRECTION_TO_CHECK)
{
    char result = false;

    int x, y, margin;
    margin = 2 * SCREEN_SCALE;

    if(DIRECTION_TO_CHECK == DOOR_LEFT)
    {
        x = ROOM.x - ROOM.dest.w - margin;
        y = ROOM.y;
    }
    elif(DIRECTION_TO_CHECK == DOOR_RIGHT)
    {
        x = ROOM.x + ROOM.dest.w + margin;
        y = ROOM.y;
    }
    elif(DIRECTION_TO_CHECK == DOOR_TOP)
    {
        x = ROOM.x;
        y = ROOM.y - ROOM.dest.h - margin;
    }
    elif(DIRECTION_TO_CHECK == DOOR_BOT)
    {
        x = ROOM.x;
        y = ROOM.y + ROOM.dest.h + margin;
    }

    Room tmp = create_room(-2, -1, -1, x, y);

    for(int i = 0; i < ROOMS_TO_GEN; i++)
    {
        Room t = all_rooms[i];

        if(t.x == tmp.x 
            AND t.y == tmp.y)
        {
            SDL_Log("CANT create room here: %i %i %i %i", t.x, t.y, tmp.x, tmp.y);
            result = false;
            break;
        }
        else
        {
            //SDL_Log("CAN create room here: %i %i %i %i", t.x, t.y, tmp.x, tmp.y);
            result = true;
        }
    }

    return(result);
}

void generate_floor(int SEED)
{
    SDL_Rect bounds = 
    {
        32 * SCREEN_SCALE, 32 * SCREEN_SCALE, 256 * SCREEN_SCALE, 128 * SCREEN_SCALE
    };

    //41good 42 breaks 43good
    //srand(42);
    int cycles = 0;

retry_generation_from_start:

    Room starting_room = create_room( 0, -1, -1, ((18 * 16) * SCREEN_SCALE), ((1 * 16) * SCREEN_SCALE));
    starting_room.type = ROOM_TYPE_STARTING;
    starting_room.state = ROOM_STATE_ACTIVE;

    all_rooms[0] = starting_room;

    Room cur_r;
    Room new_r;
    const int max_cycles = 1000;
    for(int i = 1; i < ROOMS_TO_GEN; i++)
    {
        new_r = all_rooms[i];
        cur_r = all_rooms[i-1];

        int doors_count = 0;

        if(i == 2)
        {
            SDL_Log("Break:");
        }
        pick_new_door:
        if(cycles >= max_cycles)
        {
            SDL_Log("ERROR, TOO MANY CYCLES");
            goto break_generation;
        };

        int margin = 2 * SCREEN_SCALE;
        int new_room_door = rand() % 4;
        SDL_Log("Picking new door: %i", new_room_door);
        {
            cycles++;
            SDL_Log("Current Room ID: %i", cur_r.id);
            if(cur_r.id >= 0)
            {
                if(cur_r.doors[new_room_door] == 1)
                {
                    //make new room here
                    if(new_room_door == DOOR_LEFT)
                    {
                        SDL_Log("Making Room on the Left");
                        SDL_Log("Current Room LEFT neigh ID: %i", cur_r.neighbours[DOOR_LEFT]);
                        char can_create_room = check_neighboor(cur_r, DOOR_LEFT);
                        if(can_create_room)
                        {
                            //connect starting room to first created room
                            if(i == 1)
                            {
                                all_rooms[0].neighbours[DOOR_LEFT] = i;
                            }
                            new_r = create_room(i, cur_r.id, DOOR_LEFT, cur_r.x - cur_r.dest.w - margin, cur_r.y);

                            new_r.type = ROOM_TYPE_COMBAT;
                            new_r.state = ROOM_STATE_UNCLEARED;
                            if(i == 8)
                            {
                                new_r.type = ROOM_TYPE_BOSS;
                            }
                            all_rooms[i] = new_r;
                            doors_count = 0;
                        }
                        else
                        {
                            SDL_Log("Room Exists!");
                            goto pick_new_door;
                        }
                    }
                    elif(new_room_door == DOOR_RIGHT)
                    {
                        SDL_Log("Making Room on the Right");
                        SDL_Log("Current Room RIGHT neigh ID: %i", cur_r.neighbours[DOOR_RIGHT]);
                        char can_create_room = check_neighboor(cur_r, DOOR_RIGHT);
                        if(can_create_room)
                        {
                            //connect starting room to first created room
                            if(i == 1)
                            {
                                all_rooms[0].neighbours[DOOR_RIGHT] = i;
                            }
                            new_r = create_room(i, cur_r.id, DOOR_RIGHT, cur_r.x + cur_r.dest.w + margin, cur_r.y);

                            new_r.type = ROOM_TYPE_COMBAT;
                            new_r.state = ROOM_STATE_UNCLEARED;
                            if(i == 8)
                            {
                                new_r.type = ROOM_TYPE_BOSS;
                            }
                            all_rooms[i] = new_r;
                            doors_count = 0;
                        }
                        else
                        {
                            SDL_Log("Room Exists!");
                            goto pick_new_door;
                        }
                    }
                    elif(new_room_door == DOOR_TOP)
                    {
                        SDL_Log("Making Room on the Top");
                        SDL_Log("Current Room TOP neigh ID: %i", cur_r.neighbours[DOOR_TOP]);
                        char can_create_room = check_neighboor(cur_r, DOOR_TOP);
                        if(can_create_room)
                        {
                            //connect starting room to first created room
                            if(i == 1)
                            {
                                all_rooms[0].neighbours[DOOR_TOP] = i;
                            }
                            new_r = create_room(i, cur_r.id, DOOR_TOP, cur_r.x, cur_r.y - cur_r.dest.h - margin);

                            new_r.type = ROOM_TYPE_COMBAT;
                            new_r.state = ROOM_STATE_UNCLEARED;
                            if(i == 8)
                            {
                                new_r.type = ROOM_TYPE_BOSS;
                            }
                            all_rooms[i] = new_r;
                            doors_count = 0;
                        }
                        else
                        {
                            SDL_Log("Room Exists!");
                            goto pick_new_door;
                        }
                    }
                    elif(new_room_door == DOOR_BOT)
                    {
                        SDL_Log("Making Room on the Bot");
                        SDL_Log("Current Room BOT neigh ID: %i", cur_r.neighbours[DOOR_BOT]);

                        char can_create_room = check_neighboor(cur_r, DOOR_BOT);
                        if(can_create_room)
                        {
                            //connect starting room to first created room
                            if(i == 1)
                            {
                                all_rooms[0].neighbours[DOOR_BOT] = i;
                            }
                            new_r = create_room(i, cur_r.id, DOOR_BOT, cur_r.x, cur_r.y + cur_r.dest.h + margin);

                            new_r.type = ROOM_TYPE_COMBAT;
                            new_r.state = ROOM_STATE_UNCLEARED;
                            if(i == 8)
                            {
                                new_r.type = ROOM_TYPE_BOSS;
                            }
                            all_rooms[i] = new_r;
                            doors_count = 0;
                        }
                        else
                        {
                            SDL_Log("Room Exists!");
                            goto pick_new_door;
                        }
                    }
                }
                else
                {
                    SDL_Log("Door is locked. Pick new Door");
                    doors_count++;
                    cycles++;
                    
                    if(doors_count < 4)
                    {
                        goto pick_new_door;
                    }
                    elif(doors_count >= 4)
                    {
                        SDL_Log("Go Back a room");
                        i-=2;
                        new_r = all_rooms[i];
                        cur_r = all_rooms[i-1];
                        
                        if(i < 0)
                        {
                            //TODO:
                            SDL_Log("ERROR, COULD NOT GENERATE FLOOR");
                            i = 999;
                            goto retry_generation_from_start;
                            break;
                        }
                    }
                }
            }
        }

        if(cur_r.doors[new_room_door] != 1 AND cycles < max_cycles)
        {
            goto pick_new_door;
        }
    }

break_generation:

    SDL_Log("Floor Gen Done. Took %i cycles", cycles);
    //SDL_Log("Neigh states %i %i %i %i", all_rooms[1].neighbours[0], all_rooms[1].neighbours[1],all_rooms[1].neighbours[2],all_rooms[1].neighbours[3]);
    for(int i = 0; i < ROOMS_TO_GEN; i++)
    {
        SDL_Log("------------------------------------------------");
        Room *r = &all_rooms[i];
        for(int j = 0; j < NUM_DOORS; j++)
        {
            r->doors[j] = 0;
        }
        SDL_Log("--------------------ID:%i------------------------", r->id);
        find_neighbours(r);
    }
}

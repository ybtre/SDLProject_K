
SDL_Rect gen_floor_btn;

void transition_to_room(void);

void init_playing(void)
{
    gen_floor_btn.x = SCR_W / 10;
    gen_floor_btn.y = 50;

    gen_floor_btn.w = 100;
    gen_floor_btn.h = 50;

    //srand is seeded with 42
    generate_floor(rand());

    stage.current_room_id = all_rooms[0].id;
    stage.interacted_with_door = -1;

    init_player();
    init_entities();
}

void update_playing(void)
{
    if(SDL_HasIntersection(&game.mouse_rect, &gen_floor_btn))
    {
        if(game.mouse.button[SDL_BUTTON_LEFT])
        {
            generate_floor(rand());

            game.mouse.button[SDL_BUTTON_LEFT] = 0;
        }
    }

    update_entities();

    if(stage.interacted_with_door != -1)
    {
        transition_to_room();
        stage.interacted_with_door = -1;
    }
}

void render_playing(void)
{

    draw_entities();

    debug_draw_door_state();

    draw_floor_map();

    {// button for regenerating dungeon
        SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 255);
        SDL_RenderFillRect(game.renderer, &gen_floor_btn);
    }

    gen_floor_btn.x = SCR_W / 10;
    gen_floor_btn.y = 50;

    Room curr = all_rooms[stage.current_room_id];
    SDL_Rect dest = { SCR_W / 10, 20, 0, 0};

    char buff[64];
    sprintf(buff, "Room state: %i, Room type: %i", curr.state, curr.type);
    render_text(buff, dest, 1.f);
}

void transition_to_room(void)
{
    Room current = all_rooms[stage.current_room_id];
    //SDL_Log("Interacted with door %i", stage.interacted_with_door);
    int next_room_id = current.neighbours[stage.interacted_with_door];
    //SDL_Log("Next room id %i", next_room_id);

    if(stage.interacted_with_door == DOOR_LEFT)
    {
        Entity door = get_entity(ENT_DOOR_RIGHT);
        stage.player->rect.x    = (door.rect.x + door.rect.w /2) - stage.player->rect.w *2;
        stage.player->rect.y    = (door.rect.y + door.rect.h /2) - stage.player->rect.h /2;
    }
    elif(stage.interacted_with_door == DOOR_RIGHT)
    {
        Entity door = get_entity(ENT_DOOR_LEFT);
        stage.player->rect.x    = (door.rect.x + door.rect.w /2) + stage.player->rect.w;
        stage.player->rect.y    = (door.rect.y + door.rect.h /2) - stage.player->rect.h /2;
    }
    elif(stage.interacted_with_door == DOOR_TOP)
    {
        Entity door = get_entity(ENT_DOOR_BOT);
        stage.player->rect.x    = (door.rect.x + door.rect.w /2) - stage.player->rect.w/2;
        stage.player->rect.y    = (door.rect.y + door.rect.h /2) - stage.player->rect.h * 2;
    }
    elif(stage.interacted_with_door == DOOR_BOT)
    {
        Entity door = get_entity(ENT_DOOR_TOP);
        stage.player->rect.x    = (door.rect.x + door.rect.w /2) - stage.player->rect.w/2;
        stage.player->rect.y    = (door.rect.y + door.rect.h /2) + stage.player->rect.h;
    }
    /*
    stage.player->rect.x        = SCR_W/2 - stage.player->rect.w/2; // center
    stage.player->rect.y        = SCR_H/2 - stage.player->rect.h/2; // center
                                                                    // */
                                          
    //TODO: Should be set to cleared whenever fighting ends in given room, not on transition
    current.state       = ROOM_STATE_CLEARED;

    stage.current_room_id = next_room_id; 

    SDL_Log("New Current room id %i", stage.current_room_id);
    current = all_rooms[stage.current_room_id];
    // set new current room as active room
    current.state       = ROOM_STATE_ACTIVE;
    //SDL_Log("Door states %i %i %i %i", all_rooms[stage.current_room_id].doors[0], all_rooms[stage.current_room_id].doors[1],all_rooms[stage.current_room_id].doors[2],all_rooms[stage.current_room_id].doors[3]);

    //SDL_Log("Neigh states %i %i %i %i", all_rooms[stage.current_room_id].neighbours[0], all_rooms[stage.current_room_id].neighbours[1],all_rooms[stage.current_room_id].neighbours[2],all_rooms[stage.current_room_id].neighbours[3]);
}


















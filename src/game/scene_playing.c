
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
}

void transition_to_room(void)
{
    Room current = all_rooms[stage.current_room_id];
    //SDL_Log("Interacted with door %i", stage.interacted_with_door);
    int next_room_id = current.neighbours[stage.interacted_with_door];
    //SDL_Log("Next room id %i", next_room_id);

    stage.player->rect.x        = SCR_W/2 - stage.player->rect.w/2; // center
    stage.player->rect.y        = SCR_H/2 - stage.player->rect.h/2; // center
                                            //
    stage.current_room_id = next_room_id; 
    SDL_Log("New Current room id %i", stage.current_room_id);
    SDL_Log("Door states %i %i %i %i", all_rooms[stage.current_room_id].doors[0], all_rooms[stage.current_room_id].doors[1],all_rooms[stage.current_room_id].doors[2],all_rooms[stage.current_room_id].doors[3]);

    SDL_Log("Neigh states %i %i %i %i", all_rooms[stage.current_room_id].neighbours[0], all_rooms[stage.current_room_id].neighbours[1],all_rooms[stage.current_room_id].neighbours[2],all_rooms[stage.current_room_id].neighbours[3]);
}


















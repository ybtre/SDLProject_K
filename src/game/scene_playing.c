
SDL_Rect gen_floor_btn;

SDL_Rect floor_bounds;
PlayerData p_data;
void init_player(void);

void update_entities(void);

void draw_entities(void);
void draw_entity(Entity_Type TYPE, char DEBUG);
void draw_debug_rect(Entity *E);

void draw_current_room();
void draw_floor_map(void);

void init_playing(void)
{
    gen_floor_btn.x = SCR_W / 10;
    gen_floor_btn.y = 50;

    gen_floor_btn.w = 100;
    gen_floor_btn.h = 50;

    //srand is seeded with 42
    generate_floor(rand());

    stage.current_room_id = all_rooms[0].id;

    init_player();
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
}

void render_playing(void)
{

    draw_entities();
    draw_current_room();
    draw_floor_map();

    {// button for regenerating dungeon
        SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 255);
        SDL_RenderFillRect(game.renderer, &gen_floor_btn);
    }
}

void init_player(void)
{
    p_data.is_moving = false;

    Entity p;

    p.id            = 0;
    p.active        = true;

    p.type          = ENT_PLAYER;

    p.rect.w        = 8 * SCREEN_SCALE;
    p.rect.h        = 8 * SCREEN_SCALE;
    p.rect.x        = SCR_W/2 - p.rect.w/2; // center
    p.rect.y        = SCR_H/2 - p.rect.h/2; // center

    p.vel.x         = 0;
    p.vel.y         = 0;

    p.hitbox.x      = p.rect.x;
    p.hitbox.y      = p.rect.y;
    p.hitbox.w      = p.rect.w;
    p.hitbox.h      = p.rect.h;

    p.sprite.tex    = game.spritesheet;
    p.sprite.src.x  = 0;
    p.sprite.src.y  = 0;
    p.sprite.src.w  = 8;
    p.sprite.src.h  = 8;

    stage.entity_pool[0] = p;
    stage.entity_count++;

    stage.player = stage.entity_pool[0];
}

void update_entities(void)
{
    Entity *e;
    Entity *player = &stage.entity_pool[0];

    for(int i = 0; i < stage.entity_count; i++)
    {
        e = &stage.entity_pool[i];

        switch(e->type)
        {
            case ENT_PLAYER:
            {
                if(e->active == true)
                {
                    e->vel.x = e->vel.y = 0;

                    p_data.is_moving = false;    

                    if(game.keyboard[SDL_SCANCODE_A])
                    {
                        e->vel.x = -PLAYER_VELOCITY;
                        p_data.is_moving = true;
                    }
                    if(game.keyboard[SDL_SCANCODE_D])
                    {
                        e->vel.x = PLAYER_VELOCITY;
                        p_data.is_moving = true;
                    }
                    if(game.keyboard[SDL_SCANCODE_W])
                    {
                        e->vel.y = -PLAYER_VELOCITY;
                        p_data.is_moving = true;
                    }
                    if(game.keyboard[SDL_SCANCODE_S])
                    {
                        e->vel.y = PLAYER_VELOCITY;
                        p_data.is_moving = true;
                    }

                    /*
                    if(player_data.is_moving)
                    {
                        anim_advance(e);
                    }
                    else
                    {
                        //NOTE: frame 1 is idle
                        e->anim.cur_frame = 1;
                        e->anim.frame_timer = 0;
                    }
                    */

                    e->rect.x += e->vel.x * game.dt;
                    e->rect.y += e->vel.y * game.dt;

                    if(e->rect.x < floor_bounds.x)
                    {
                        e->rect.x = floor_bounds.x;
                    }
                    elif(e->rect.x > ((floor_bounds.x + floor_bounds.w) - e->rect.w))
                    {
                        e->rect.x = ((floor_bounds.x + floor_bounds.w) - e->rect.w);
                    }
                    elif(e->rect.y < floor_bounds.y)
                    {
                        e->rect.y = floor_bounds.y;
                    }
                    elif(e->rect.y > ((floor_bounds.y + floor_bounds.h) - e->rect.h))
                    {
                        e->rect.y = ((floor_bounds.y + floor_bounds.h) - e->rect.h);
                    }
                }
                break;
            }
        }
    }
}

void draw_current_room()
{
    SDL_Rect room_bounds = 
    {
        16 * SCREEN_SCALE, 32 * SCREEN_SCALE, 288 * SCREEN_SCALE, 144 * SCREEN_SCALE
    };

    SDL_SetRenderDrawColor(game.renderer, 100, 0, 0, 255);
    SDL_RenderDrawRect(game.renderer, &room_bounds);


    floor_bounds.x = 32 * SCREEN_SCALE;
    floor_bounds.y = 48 * SCREEN_SCALE;
    floor_bounds.w = 256 * SCREEN_SCALE;
    floor_bounds.h = 112 * SCREEN_SCALE;

    SDL_SetRenderDrawColor(game.renderer, 100, 75, 0, 255);
    SDL_RenderDrawRect(game.renderer, &floor_bounds);

    /////////////////
    SDL_Rect left_door_bounds = 
    {
        16 * SCREEN_SCALE, 89 * SCREEN_SCALE, 16 * SCREEN_SCALE, 30 * SCREEN_SCALE
    };

    if(all_rooms[stage.current_room_id].doors[DOOR_LEFT] == 1
            AND all_rooms[stage.current_room_id].neighbours[DOOR_LEFT] != -1)
    {
        SDL_SetRenderDrawColor(game.renderer, 0, 245, 0, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(game.renderer, 245, 0, 0, 255);
    }
    SDL_RenderDrawRect(game.renderer, &left_door_bounds);

    /////////////////
    SDL_Rect right_door_bounds = 
    {
        288 * SCREEN_SCALE, 89 * SCREEN_SCALE, 16 * SCREEN_SCALE, 30 * SCREEN_SCALE
    };

    if(all_rooms[stage.current_room_id].doors[DOOR_RIGHT] == 1
            AND all_rooms[stage.current_room_id].neighbours[DOOR_RIGHT] != -1)
    {
        SDL_SetRenderDrawColor(game.renderer, 0, 245, 0, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(game.renderer, 245, 0, 0, 255);
    }
    SDL_RenderDrawRect(game.renderer, &right_door_bounds);

    //////////////
    SDL_Rect top_door_bounds = 
    {
        144 * SCREEN_SCALE, 32 * SCREEN_SCALE, 30 * SCREEN_SCALE, 16 * SCREEN_SCALE
    };

    if(all_rooms[stage.current_room_id].doors[DOOR_TOP] == 1
            AND all_rooms[stage.current_room_id].neighbours[DOOR_TOP] != -1)
    {
        SDL_SetRenderDrawColor(game.renderer, 0, 245, 0, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(game.renderer, 245, 0, 0, 255);
    }
    SDL_RenderDrawRect(game.renderer, &top_door_bounds);

    /////////////////
    SDL_Rect bot_door_bounds = 
    {
        144 * SCREEN_SCALE, 160 * SCREEN_SCALE, 30 * SCREEN_SCALE, 16 * SCREEN_SCALE
    };

    //SDL_Log("Bot state: %i, Bot ID: %i", all_rooms[stage.current_room_id].doors[DOOR_BOT], all_rooms[stage.current_room_id].neighbours[DOOR_BOT]);
    if(all_rooms[stage.current_room_id].doors[DOOR_BOT] == 1
            AND all_rooms[stage.current_room_id].neighbours[DOOR_BOT] != -1)
    {
        SDL_SetRenderDrawColor(game.renderer, 0, 245, 0, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(game.renderer, 245, 0, 0, 255);
    }
    SDL_RenderDrawRect(game.renderer, &bot_door_bounds);
}

void draw_entities(void)
{
    //TODO: switch to drawing based on layer, not based on type
    draw_entity(ENT_PLAYER, true);
}

void draw_entity(Entity_Type TYPE, char DEBUG)
{
    Entity *e;
    int i = 0;
    for(i = 0; i < stage.entity_count; i++)
    {
        e = &stage.entity_pool[i];
       
        if(e->active == false)
            continue;

        if(e->type == TYPE)
        {
            blit_from_sheet(game.spritesheet, e->rect, e->sprite.src, 0, SCREEN_SCALE, false);

            if(DEBUG == true)
            {
                draw_debug_rect(e);
            }
        }
    }
}

void draw_debug_rect(Entity *E)
{
    SDL_Rect drect;
    drect = E->rect;
    //drect.w *= SCREEN_SCALE;
    //drect.h *= SCREEN_SCALE;
    //drect.x -= (drect.w / 2);
    //drect.y -= (drect.h / 2);
    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 255);
    SDL_RenderDrawRect(game.renderer, &drect);
}

void draw_floor_map(void)
{
    {// SCREEN CENTER?
        SDL_RenderDrawRect(game.renderer, &(SDL_Rect){SCR_W/2 - SCREEN_SCALE, SCR_H/2 - SCREEN_SCALE, SCREEN_SCALE, SCREEN_SCALE});
    }
    
    for(int i = 0; i < ROOMS_TO_GEN; i++)
    {
        Room r = all_rooms[i];

        SDL_SetRenderDrawColor(game.renderer, 0, 0, 220, 255);

        if(stage.current_room_id == r.id)
        {
            SDL_RenderFillRect(game.renderer, &r.dest);
        }
        else
        {
            SDL_RenderDrawRect(game.renderer, &r.dest);
        }

        SDL_SetRenderDrawColor(game.renderer, 100, 0, 0, 255);

        for(int j = 0; j < NUM_DOORS; j++)
        {
            if(r.doors[j] == 1)
            {
                SDL_SetRenderDrawColor(game.renderer, 0, 100, 0, 255);
            }
            elif(r.doors[j] == 0)
            {
                SDL_SetRenderDrawColor(game.renderer, 100, 0, 0, 255);
            }

            SDL_RenderFillRect(game.renderer, &r.dest_doors[j]);
        }

        char buff[48];
        sprintf(buff, "%i", r.id);

        SDL_Rect dest = {r.x, r.y - r.dest.w/5, 0, 0};
        render_text(buff, dest, 0.6f);
    }
}

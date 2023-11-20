
PlayerData p_data;
void init_player(void);

void init_entities(void);

void update_entities(void);

void draw_entities(void);
void draw_entity(Entity_Type TYPE, char DEBUG, char DRAW_SPRITE);
Entity get_entity(Entity_Type TYPE);

void draw_floor_map(void);

void debug_draw_rect(Entity *E);
void debug_draw_door_state();

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
    p.rect.y        = SCR_H/2 - p.rect.h/2 + 10 * SCREEN_SCALE; // center

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

    stage.player = &stage.entity_pool[0];
}

void init_entities(void)
{
    Entity e;

    {// Floor
        e.id            = stage.entity_count;
        e.active        = true;

        e.type          = ENT_FLOOR;

        e.rect.x        = 32 * SCREEN_SCALE;
        e.rect.y        = 48 * SCREEN_SCALE;
        e.rect.w        = 256 * SCREEN_SCALE;
        e.rect.h        = 112 * SCREEN_SCALE;

        e.vel.x         = 0;
        e.vel.y         = 0;

        e.hitbox.x      = e.rect.x;
        e.hitbox.y      = e.rect.y;
        e.hitbox.w      = e.rect.w;
        e.hitbox.h      = e.rect.h;

        e.sprite.tex    = game.spritesheet;
        e.sprite.src.x  = 0;
        e.sprite.src.y  = 400;
        e.sprite.src.w  = 256;
        e.sprite.src.h  = 112;

        stage.entity_pool[stage.entity_count] = e;
        stage.entity_count++;
    }
    {//Doors
        {// Left Door
            e.id            = stage.entity_count;
            e.active        = true;

            e.type          = ENT_DOOR_LEFT;

            e.rect.x        = 16 * SCREEN_SCALE;
            e.rect.y        = 89 * SCREEN_SCALE;
            e.rect.w        = 16 * SCREEN_SCALE;
            e.rect.h        = 30 * SCREEN_SCALE;

            e.vel.x         = 0;
            e.vel.y         = 0;

            e.hitbox.x      = e.rect.x;
            e.hitbox.y      = e.rect.y;
            e.hitbox.w      = e.rect.w;
            e.hitbox.h      = e.rect.h;

            e.sprite.tex    = game.spritesheet;
            e.sprite.src.x  = 0;
            e.sprite.src.y  = 32;
            e.sprite.src.w  = 16;
            e.sprite.src.h  = 30;

            stage.entity_pool[stage.entity_count] = e;
            stage.entity_count++;
        }
        {// Right Door
            e.id            = stage.entity_count;
            e.active        = true;

            e.type          = ENT_DOOR_RIGHT;

            e.rect.x        = 288 * SCREEN_SCALE;
            e.rect.y        = 89 * SCREEN_SCALE;
            e.rect.w        = 16 * SCREEN_SCALE;
            e.rect.h        = 30 * SCREEN_SCALE;

            e.vel.x         = 0;
            e.vel.y         = 0;

            e.hitbox.x      = e.rect.x;
            e.hitbox.y      = e.rect.y;
            e.hitbox.w      = e.rect.w;
            e.hitbox.h      = e.rect.h;

            e.sprite.tex    = game.spritesheet;
            e.sprite.src.x  = 0;
            e.sprite.src.y  = 63;
            e.sprite.src.w  = 16;
            e.sprite.src.h  = 30;

            stage.entity_pool[stage.entity_count] = e;
            stage.entity_count++;
        }
        {// Top Door
            e.id            = stage.entity_count;
            e.active        = true;

            e.type          = ENT_DOOR_TOP;

            e.rect.x        = 144 * SCREEN_SCALE;
            e.rect.y        = 32 * SCREEN_SCALE;
            e.rect.w        = 30 * SCREEN_SCALE;
            e.rect.h        = 16 * SCREEN_SCALE;

            e.vel.x         = 0;
            e.vel.y         = 0;

            e.hitbox.x      = e.rect.x;
            e.hitbox.y      = e.rect.y;
            e.hitbox.w      = e.rect.w;
            e.hitbox.h      = e.rect.h;

            e.sprite.tex    = game.spritesheet;
            e.sprite.src.x  = 0;
            e.sprite.src.y  = 96;
            e.sprite.src.w  = 30;
            e.sprite.src.h  = 16;

            stage.entity_pool[stage.entity_count] = e;
            stage.entity_count++;
        }
        {// Bot Door
            e.id            = stage.entity_count;
            e.active        = true;

            e.type          = ENT_DOOR_BOT;

            e.rect.x        = 144 * SCREEN_SCALE;
            e.rect.y        = 160 * SCREEN_SCALE;
            e.rect.w        = 30 * SCREEN_SCALE;
            e.rect.h        = 16 * SCREEN_SCALE;

            e.vel.x         = 0;
            e.vel.y         = 0;

            e.hitbox.x      = e.rect.x;
            e.hitbox.y      = e.rect.y;
            e.hitbox.w      = e.rect.w;
            e.hitbox.h      = e.rect.h;

            e.sprite.tex    = game.spritesheet;
            e.sprite.src.x  = 0;
            e.sprite.src.y  = 113;
            e.sprite.src.w  = 30;
            e.sprite.src.h  = 16;

            stage.entity_pool[stage.entity_count] = e;
            stage.entity_count++;
        }
    }
    {// Walls
        e.id            = stage.entity_count;
        e.active        = true;

        e.type          = ENT_WALLS;

        e.rect.x        = 16 * SCREEN_SCALE;
        e.rect.y        = 32 * SCREEN_SCALE;
        e.rect.w        = 288 * SCREEN_SCALE;
        e.rect.h        = 144 * SCREEN_SCALE;

        e.vel.x         = 0;
        e.vel.y         = 0;

        e.hitbox.x      = e.rect.x;
        e.hitbox.y      = e.rect.y;
        e.hitbox.w      = e.rect.w;
        e.hitbox.h      = e.rect.h;

        e.sprite.tex    = game.spritesheet;
        e.sprite.src.x  = 0;
        e.sprite.src.y  = 256;
        e.sprite.src.w  = 288;
        e.sprite.src.h  = 144;

        stage.entity_pool[stage.entity_count] = e;
        stage.entity_count++;
    }
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
                    
                    Entity floor = stage.entity_pool[1];
                    if(e->rect.x < floor.rect.x - e->rect.w)
                    {
                        e->rect.x = floor.rect.x - e->rect.w;
                    }
                    if(e->rect.x > (floor.rect.x + floor.rect.w))
                    {
                        e->rect.x = (floor.rect.x + floor.rect.w);
                    }
                    if(e->rect.y < floor.rect.y - e->rect.w)
                    {
                        e->rect.y = floor.rect.y - e->rect.w;
                    }
                    if(e->rect.y > (floor.rect.y + floor.rect.h))
                    {
                        e->rect.y = (floor.rect.y + floor.rect.h);
                    }
                }
                break;
            }
            
            case ENT_DOOR_LEFT:
            {
                if(e->active)
                {
                    if(SDL_HasIntersection(&stage.player->rect, &e->rect))
                    {
                        if(game.keyboard[SDL_SCANCODE_E])
                        {
                            stage.interacted_with_door = DOOR_LEFT;

                            game.keyboard[SDL_SCANCODE_E] = 0;
                        }
                    }
                }

                break;
            }
            
            case ENT_DOOR_RIGHT:
            {
                if(e->active)
                {
                    if(SDL_HasIntersection(&stage.player->rect, &e->rect))
                    {
                        if(game.keyboard[SDL_SCANCODE_E])
                        {
                            stage.interacted_with_door = DOOR_RIGHT;

                            game.keyboard[SDL_SCANCODE_E] = 0;
                        }
                    }
                }

                break;
            }
            
            case ENT_DOOR_TOP:
            {
                if(e->active)
                {
                    if(SDL_HasIntersection(&stage.player->rect, &e->rect))
                    {
                        if(game.keyboard[SDL_SCANCODE_E])
                        {
                            stage.interacted_with_door = DOOR_TOP;

                            game.keyboard[SDL_SCANCODE_E] = 0;
                        }
                    }
                }

                break;
            }
            
            case ENT_DOOR_BOT:
            {
                if(e->active)
                {
                    if(SDL_HasIntersection(&stage.player->rect, &e->rect))
                    {
                        if(game.keyboard[SDL_SCANCODE_E])
                        {
                            stage.interacted_with_door = DOOR_BOT;

                            game.keyboard[SDL_SCANCODE_E] = 0;
                        }
                    }
                }

                break;
            }
        }
    }
}

void draw_entities(void)
{
    //TODO: switch to drawing based on layer, not based on type
    draw_entity(ENT_FLOOR, true, true);
    draw_entity(ENT_WALLS, false, true);


    draw_entity(ENT_DOOR_LEFT, false, true);
    draw_entity(ENT_DOOR_RIGHT, false, true);
    draw_entity(ENT_DOOR_TOP, false, true);
    draw_entity(ENT_DOOR_BOT, false, true);

    draw_entity(ENT_PLAYER, true, true);
}

void draw_entity(Entity_Type TYPE, char DEBUG, char DRAW_SPRITE)
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
            if(DRAW_SPRITE == true)
            {
                blit_from_sheet(game.spritesheet, e->rect, e->sprite.src, 0, SCREEN_SCALE, false);
            }

            if(DEBUG == true)
            {
                debug_draw_rect(e);
            }
        }
    }
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

Entity get_entity(Entity_Type TYPE)
{
    Entity e;

    for(int i = 0; i < stage.entity_count; i++)
    {
        e = stage.entity_pool[i];
       
        if(e.active == false)
            continue;

        if(e.type == TYPE)
        {
            return(e);
        }
    }

    return(e);
}

void debug_draw_rect(Entity *E)
{
    SDL_Rect drect;
    drect = E->rect;

    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 255);
    SDL_RenderDrawRect(game.renderer, &drect);
}

void debug_draw_door_state()
{
    //
    SDL_Rect r = get_entity(ENT_FLOOR).rect;
    SDL_SetRenderDrawColor(game.renderer, 100, 0, 0, 255);
    SDL_RenderDrawRect(game.renderer, &r);


    /////////////////
    if(all_rooms[stage.current_room_id].doors[DOOR_LEFT] == 1
            AND all_rooms[stage.current_room_id].neighbours[DOOR_LEFT] != -1)
    {
        SDL_SetRenderDrawColor(game.renderer, 0, 245, 0, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(game.renderer, 245, 0, 0, 255);
    }
    r = get_entity(ENT_DOOR_LEFT).rect;
    SDL_RenderDrawRect(game.renderer, &r);

    /////////////////
    if(all_rooms[stage.current_room_id].doors[DOOR_RIGHT] == 1
            AND all_rooms[stage.current_room_id].neighbours[DOOR_RIGHT] != -1)
    {
        SDL_SetRenderDrawColor(game.renderer, 0, 245, 0, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(game.renderer, 245, 0, 0, 255);
    }
    r = get_entity(ENT_DOOR_RIGHT).rect;
    SDL_RenderDrawRect(game.renderer, &r);

    //////////////
    if(all_rooms[stage.current_room_id].doors[DOOR_TOP] == 1
            AND all_rooms[stage.current_room_id].neighbours[DOOR_TOP] != -1)
    {
        SDL_SetRenderDrawColor(game.renderer, 0, 245, 0, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(game.renderer, 245, 0, 0, 255);
    }
    r = get_entity(ENT_DOOR_TOP).rect;
    SDL_RenderDrawRect(game.renderer, &r);

    /////////////////
    if(all_rooms[stage.current_room_id].doors[DOOR_BOT] == 1
            AND all_rooms[stage.current_room_id].neighbours[DOOR_BOT] != -1)
    {
        SDL_SetRenderDrawColor(game.renderer, 0, 245, 0, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(game.renderer, 245, 0, 0, 255);
    }
    r = get_entity(ENT_DOOR_BOT).rect;
    SDL_RenderDrawRect(game.renderer, &r);
}

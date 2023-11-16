
SDL_Rect gen_floor_btn;

PlayerData p_data;
void init_player(void);

void update_entities(void);

void draw_entities(void);
void draw_entity(Entity_Type TYPE, char DEBUG);
void draw_debug_rect(Entity *E);

void draw_floor_map(void);

void init_playing(void)
{
    gen_floor_btn.x = SCR_W / 10;
    gen_floor_btn.y = 50;

    gen_floor_btn.w = 100;
    gen_floor_btn.h = 50;

    //srand is seeded with 42
    generate_floor(rand());

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
    {// floor for debugging visualization
        SDL_Rect floor = 
        {
            32 * SCREEN_SCALE, 32 * SCREEN_SCALE, 256 * SCREEN_SCALE, 128 * SCREEN_SCALE
        };

        SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 255);
        SDL_RenderDrawRect(game.renderer, &floor);
    }


    draw_entities();
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
                    }
                    break;
                }
        }
    }
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

        SDL_SetRenderDrawColor(game.renderer, 0, 0, 200, 255);
        SDL_RenderDrawRect(game.renderer, &r.dest);

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

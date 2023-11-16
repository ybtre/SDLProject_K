
SDL_Rect gen_floor_btn;

void init_playing(void)
{
    gen_floor_btn.x = SCR_W - SCR_W / 8;
    gen_floor_btn.y = 50;

    gen_floor_btn.w = 100;
    gen_floor_btn.h = 50;

    //srand is seeded with 42
    generate_floor(rand());
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
}

void render_playing(void)
{
    SDL_Rect floor = 
    {
        32 * SCREEN_SCALE, 32 * SCREEN_SCALE, 256 * SCREEN_SCALE, 128 * SCREEN_SCALE
    };

    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 255);
    SDL_RenderDrawRect(game.renderer, &floor);

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

        SDL_Rect dest = {r.x, r.y, 0, 0};
        render_text(buff, dest, 0.6f);
    }

    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 255);
    SDL_RenderFillRect(game.renderer, &gen_floor_btn);
}

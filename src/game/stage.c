

void update(void);
void render(void);

SDL_Texture *cursor_texture;

void reset_game(void);

void init_stage(void)
{
    game.delegate.logic = update;
    game.delegate.draw = render;

    memset(&stage, 0, sizeof(Stage));

    cursor_texture = load_texture("assets/cursor.png");
    //game.spritesheet = load_texture("assets/spritesheet.png"); 

    game_state = PLAYING;

    init_playing();
}

inline void update(void)
{
    switch(game_state)
    {
        case MAIN_MENU:
             {
                 if(game.keyboard[SDL_SCANCODE_SPACE])
                 {
                     game_state = PLAYING;
                 }
             }
             break;
        
        case PLAYING:
            {
                //TODO:
                update_playing();
            }
            break;

        case GAME_OVER:
            {
                if(game.keyboard[SDL_SCANCODE_SPACE])
                {
                    game_state = PLAYING;
                }
            }
            break;

    }
    if(game.keyboard[SDL_SCANCODE_ESCAPE])
    {
        exit(1);
    }
}

inline void render(void)
{
    switch(game_state)
    {
        case MAIN_MENU:
            {
                char buff[48];
                sprintf(buff, "MAIN MENU");
                

                SDL_Rect dest = {SCR_W / 4 - 200, SCR_H  / 2 - 80, 0, 0};
                render_text(buff, dest, 2.f);
            }
            break;
        
        case PLAYING:
            {
                //TODO:
                render_playing(); 
                char buff[48];
                sprintf(buff, "PLAYING");

                SDL_Rect dest = {SCR_W / 4 - 200, SCR_H  / 2 - 80, 0, 0};
                render_text(buff, dest, 2.f);
            }
            break;

        case GAME_OVER:
            {
                char buff[48];
                sprintf(buff, "GAME OVER");

                SDL_Rect dest = {SCR_W / 4 - 200, SCR_H  / 2 - 80, 0, 0};
                render_text(buff, dest, 2.f);
            }
            break;
    }

    blit(cursor_texture, game.mouse.x, game.mouse.y, 1.f, 1);
}


inline void reset_game(void)
{
}


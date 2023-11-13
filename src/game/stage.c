

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

    game_state = MAIN_MENU;

    stage.turn = TURN_NOONE;
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
            }
            break;
        
        case PLAYING:
            {
            }
            break;

        case GAME_OVER:
            {
            }
            break;
    }

    blit(cursor_texture, game.mouse.x, game.mouse.y, 1.f, 1);
}


inline void reset_game(void)
{
}


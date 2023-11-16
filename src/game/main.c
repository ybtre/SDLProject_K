
Game game;

int main(int argc, char *argv[])
{
    srand(42);

    memset(&game, 0, sizeof(Game));

    init_SDL();

    atexit(game_close);

    init_game();

    init_stage();

    float last_tick_time = 0;
    float delta = 0;;
    char running = 1;
    while(running == 1)
    {
        float tick_time = SDL_GetTicks();
        delta = tick_time - last_tick_time;
        last_tick_time = tick_time;

        game.dt = delta;

        prepare_scene();

        handle_input();

        game.delegate.logic();
        game.delegate.draw();

        render_scene();
    }

    return(0);
}

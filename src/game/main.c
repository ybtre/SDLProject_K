
Game game;

int main(int argc, char *argv[])
{
    srand(42);

    memset(&game, 0, sizeof(Game));

    init_SDL();

    atexit(game_close);

    init_game();

    init_stage();

    char running = 1;
    uint32_t total_frame_ticks = 0;
    uint32_t total_frames = 0;
    while(running == 1)
    {
        total_frames++;

        prepare_scene();

        handle_input();

        game.delegate.logic();
        game.delegate.draw();

        render_scene();
    }

    return(0);
}

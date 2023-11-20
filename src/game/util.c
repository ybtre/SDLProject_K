
uint64_t total_malloc    = 0;
uint64_t total_free      = 0;
void* mmalloc(uint64_t SIZE)
{
    void* mem_ptr;

    mem_ptr = malloc(SIZE);

    total_malloc += sizeof(mem_ptr);

#ifdef MEMORY_DEBUG
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Total Malloc: %i", total_malloc);
#endif

    return(mem_ptr);
}

void mfree(void* MEM_TO_FREE)
{
    total_malloc -= sizeof(MEM_TO_FREE);
    total_free += sizeof(MEM_TO_FREE);

#ifdef MEMORY_DEBUG
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Total Free: %i", total_free);

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Difference: %i", total_malloc - total_free);
#endif

    free(MEM_TO_FREE);
}

void render_text(char* text, SDL_Rect dest, float SCALE) {
	SDL_Color fg = { 255, 255, 255, 255 };
	SDL_Surface* surf = TTF_RenderText_Solid(game.font, text, fg);

	dest.w = surf->w * SCALE;
	dest.h = surf->h * SCALE;

	SDL_Texture* tex = SDL_CreateTextureFromSurface(game.renderer, surf);

	SDL_RenderCopy(game.renderer, tex, NULL, &dest);
	SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}

float get_angle(int X1, int Y1, int X2, int Y2)
{
    float angle = -90 + atan2(Y1 - Y2, X1 - X2) * (180 / PI);

    return angle >= 0 ? angle : 360 + angle;
}

Vec2i get_scr_scaled(void)
{
    return((Vec2i){ SCREEN_WIDTH * SCREEN_SCALE, SCREEN_HEIGHT * SCREEN_SCALE});
}

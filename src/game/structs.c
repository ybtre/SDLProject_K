
typedef struct
{
    void (*logic)(void);
    void (*draw)(void);
} Delegate;

typedef struct Texture
{
    char            active;

    char            name[MAX_NAME_LENGTH];
    SDL_Texture*    texture;
} Texture;

typedef struct
{
    int x;
    int y;
    int button[MAX_MOUSE_BUTTONS];
    int wheel;
} Mouse;

#define TEXTURE_CACHE_MAX   16
typedef struct
{
	SDL_Renderer*   renderer;
	SDL_Window*     window;
    Delegate        delegate;

    Mouse           mouse;

    int             keyboard[MAX_KEYBOARD_KEYS];

    TTF_Font        *font;

    SDL_Texture     *spritesheet;

    Texture         texture_cache[TEXTURE_CACHE_MAX];
} Game;
Game game;

typedef enum Game_State
{
    MAIN_MENU,
    PLAYING,
    GAME_OVER,
} Game_State;
Game_State game_state;

typedef enum Layers
{
    BG_0,
    BG_1,
    BG_2,
    GAMEPLAY,
    FG,
    UI,

    NUM_LAYERS,
} Layers;

enum Flags 
{
    GAME_PAUSED         = 1 << 0,
};

// |= flag      : set flag
// &= !()flag   : unset flag
// ^= flag      : flip flag
typedef struct Game_Flags
{
    uint64_t flags;

} Game_Flags;
Game_Flags game_flags;

typedef struct
{
    char            active;

    SDL_Rect        src;
    SDL_Rect        dest;

    SDL_Texture     *tex;
} Sprite;

typedef enum Entity_Type
{
    GRID_TILE   = 0,
    GRID_LARGE  = 1,
    GRID_SMALL  = 2,
} Entity_Type;

typedef enum Grid_Color
{
    R = 0,
    G = 1,
    B = 2,
} Grid_Color;

typedef struct
{
    char            active;
    Entity_Type     ent_type;

    int             x;      //world x
    int             y;      //world y
    int             idx;    //grid id x
    int             idy;    //grid id y

    SDL_Rect        hitbox;
    SDL_Rect        dest;

    Grid_Color      color;
    Sprite          *sprite;
    //Layers          layer;
} Entity;
Entity grid_large[GRID_X][GRID_Y];

typedef struct
{
    int         x;
    int         y;
    int         idx;
    int         idy;

    SDL_Rect    dest;
} Common_Ent_Data;

typedef enum
{
    TILE_DEAD,
    TILE_ALIVE,
} Tile_State;

typedef struct
{
    Tile_State          state;

    Common_Ent_Data     data;
} Tile;

typedef struct
{
    Grid_Color          color;

    char                winner;

    Tile                tiles[GRID_X][GRID_Y];

    Common_Ent_Data     data;
} Board;

typedef enum
{
    TURN_NOONE        = 0,
    TURN_GREEN        = 1,
    TURN_ORANGE       = 2,
} Turn;

typedef struct
{
    //Entity 0 is always player
    Turn            turn;
    Turn            prev_turn;

    Board           *current_board;

    char            game_winner;

    int             entity_count;
    Entity          entities_pool[ENTITIES_MAX];
}Stage;
Stage stage;


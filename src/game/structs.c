
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

typedef struct Vec2i
{
    int x;
    int y;
} Vec2i;

typedef struct Vec2
{
    float x;
    float y;
} Vec2;

#define TEXTURE_CACHE_MAX   36
typedef struct
{
	SDL_Renderer*   renderer;
	SDL_Window*     window;
    Delegate        delegate;

    Mouse           mouse;
    SDL_Rect        mouse_rect;

    int             keyboard[MAX_KEYBOARD_KEYS];

    TTF_Font        *font;

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
    L_BG,
    L_FLOOR,
    L_WALLS,
    L_DOORS,
    L_GAMEPLAY,
    L_UI,

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


typedef enum Entity_Type
{
    ENT_PLAYER,
    ENT_PLAYER_BULLET,

    ENT_UI_P_HEALTH,

    ENT_ENEMY,
    ENT_ENEMY_BULLET,

    ENT_BACKGROUND,

    ENT_DOOR,

    ENT_WALL,


    NUM_ENTITIES
} Entity_Type;

typedef struct
{
    SDL_Rect        src;

    SDL_Texture     *tex;
} Sprite;

typedef struct
{
    char            loop;
    int             frames_num;
    int             frames_cur;
    float           frames_rate;
    float           frames_timer;
} AnimData;

typedef struct
{
    int             id;
    char            active;
    Entity_Type     type;

    /*
    int             hp;
    int             base_hp;
    int             dmg;
    int             base_dmg;

    char            facing_right;
    char            hit_this_frame;
    int             hit_frame_timer;
    int             hit_frame_length;
    */

    SDL_Rect        rect; //x, y for position, w, h for constructing dest rect
    Vec2            vel;

    SDL_Rect        hitbox;

    Sprite          sprite;
    //AnimData        anim;
    //Layers          layer;

} Entity;

typedef struct
{
    char            is_moving;

    float           reload_rate;
    float           reload_timer;

    int             score;

    char            take_dmg;
    float           take_dmg_rate;
    float           take_dmg_timer;
    
} PlayerData;

typedef struct
{
    Entity          player;
    int             entity_count;
    Entity          entities_pool[ENTITIES_MAX];

    char            freeze_frame;
    float           freeze_frame_duration;
    float           freeze_frame_timer;
}Stage;
Stage stage;


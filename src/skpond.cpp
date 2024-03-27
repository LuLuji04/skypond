#include<skypond.h>
#include <stdarg.h>
#include <macro.h>

#define FPS 60

static SDL_Window *main_window = nullptr;
static SDL_Renderer *main_renderer = nullptr;

static bool need_redraw = true;
void set_redraw() { need_redraw = true; }


void skypond_update() {

  static uint64_t last = 0;
  static int cpf = 1; // count per frame
  static int cnt = 0;
  if (unlikely((-- cnt) < 0)) {
    uint64_t now = nvboard_get_time();
    uint64_t diff = now - last;
    if (diff == 0) return;
    int cpf_new = ((uint64_t)cpf * 1000000) / ((uint64_t)diff * FPS); // adjust cpf
    cnt += cpf_new - cpf;
    cpf = cpf_new;
    if (diff > 1000000 / FPS) {
      last = now;
      cnt = cpf;

      void read_event();
      read_event();
      update_components(main_renderer);
      if (need_redraw) {
        SDL_RenderPresent(main_renderer);
        need_redraw = false;
      }
    }
  }
}

void skypond_init(int vga_clk_cycle) {
    // init SDL and SDL_image
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG);

    main_window = SDL_CreateWindow("Skpond " VERSION_STR, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    main_renderer = SDL_CreateRenderer(main_window, -1, 
    #ifdef VSYNC
        SDL_RENDERER_PRESENTVSYNC |
    #endif
    #ifdef HARDWARE_ACC
        SDL_RENDERER_ACCELERATED |
    #else
        SDL_RENDERER_SOFTWARE |
    #endif
        0
    );
    SDL_SetRenderDrawColor(main_renderer, 0xff, 0xff, 0xff, 0);
    SDL_RenderFillRect(main_renderer, NULL);

    void init_font(SDL_Renderer *renderer);
    init_font(main_renderer);
    init_render(main_renderer);
    init_components(main_renderer);
    init_gui(main_renderer);

    void init_nvboard_timer();
    init_nvboard_timer();

    update_components(main_renderer);

}

void nvboard_quit(){
    delete_components();
    SDL_DestroyWindow(main_window);
    SDL_DestroyRenderer(main_renderer);
    IMG_Quit();
    SDL_Quit();
}

#ifndef __NVBOARD_H__
#define __NVBOARD_H__

#include <font.h>
#include <render.h>
#include <component.h>
#include <configs.h>
#include <string>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#define VERSION_STR "v1.0 (2024.01.10)"

void set_redraw();
uint64_t nvboard_get_time();

void init_render(SDL_Renderer *renderer);
SDL_Texture* load_pic_texture(SDL_Renderer *renderer, std::string path);
SDL_Texture* new_texture(SDL_Renderer *renderer, int w, int h, int r, int g, int b);

#endif

void skypond_init();
void skypond_update();
void skypond_quit();
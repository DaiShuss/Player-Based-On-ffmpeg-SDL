#include <iostream>
extern "C"
{
#include "SDL2/SDL.h"
};
using namespace std;

const int bpp = 12;

int screen_w = 400, screen_h = 400;

const int pixel_w = 640, pixel_h = 360;

unsigned char buffer[pixel_w * pixel_h * bpp / 8];

int main() {
    if(SDL_Init(SDL_INIT_EVERYTHING)) {
        printf( "Could not initialize SDL - %s\n", SDL_GetError());
        return -1;
    }

    // 新建窗口
    SDL_Window *window = SDL_CreateWindow("Simplest Video Play SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          screen_w, screen_h,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    if(!window) {
        printf("SDL: could not create window - exiting:%s\n",SDL_GetError());
        return -1;
    }

    // 创建render并与window绑定
    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, -1, 0);

    Uint32 pixformat = 0;
    //IYUV: Y + U + V  (3 planes)
    //YV12: Y + V + U  (3 planes)
    pixformat = SDL_PIXELFORMAT_IYUV;

    // 创建texture并与render绑定
    SDL_Texture* sdlTexture = SDL_CreateTexture(sdlRenderer,
            pixformat,
            SDL_TEXTUREACCESS_STREAMING,
            pixel_w,
            pixel_h);

    FILE *fp=NULL;
    fp=fopen("sintel_640_360.yuv","rb+");

    if(fp==NULL){
        printf("cannot open this file\n");
        return -1;
    }

    SDL_Rect sdlRect;

    SDL_Event windowEvent;

    while(1){
        // 从fp中读数据到buffer
        if (fread(buffer, 1, pixel_w * pixel_h * bpp / 8, fp) != pixel_w * pixel_h * bpp / 8) {
            // Loop
            fseek(fp, 0, SEEK_SET);
            fread(buffer, 1, pixel_w * pixel_h * bpp / 8, fp);
        }

        // buffer中给数据到texture
        SDL_UpdateTexture(sdlTexture, NULL, buffer, pixel_w); // 设置纹理的数据

        sdlRect.x = 0;
        sdlRect.y = 0;
        sdlRect.w = screen_w;
        sdlRect.h = screen_h;

        // 把texture数据给到render，展示
        SDL_RenderClear( sdlRenderer );
        SDL_RenderCopy( sdlRenderer, sdlTexture, NULL, &sdlRect);  // 将纹理数据拷贝给渲染器
        SDL_RenderPresent( sdlRenderer );  // 显示
        //Delay 40ms
        if (SDL_PollEvent(&windowEvent)) { // 对当前待处理事件进行轮询。
            if (SDL_QUIT == windowEvent.type) { // 如果事件为推出SDL，结束循环。
                cout << "SDL quit!!" << endl;
                break;
            }
        }
        //SDL_Delay(50);
    }
    SDL_Quit();
    return 0;
}
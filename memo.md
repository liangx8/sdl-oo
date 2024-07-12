# \<filesystem>
  文件操作的C++库

# SDL_Surface
  1. 用SDL_GetWindowSurface()从SDL_Window对象中获取目标surface
  2. 建立要画的源图案surface，可IMG_Load()建立
  1. SDL_ConvertSurface()把源surface转换成目标的surface
  1. 用SDL_BlitSurface(),把源surface拷贝到目标surface
  1. SDL_UpdateWindowSurface()

# SDL_Renderer

# 显示文字
  1. TTF_OpenFont()
  1. TTF_RenderText_Solid() 建立一个Surface(其实到了这步利用SDL_Surface显示的方法就能显示文本)
  1. SDL_CreateTextureFromSurface()　由前面的surface再建一Texture
  1. SDL_RenderCopyEx() 把texture 渲染到　renderer上
  1. 最后用SDL_RenderPresent()

# SDL_Texture
  在SDL2中替代Surface
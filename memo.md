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

# Ｃ＋＋知识
  1. 在函数中返回引用(Return reference in a function)

  直接返回函数中的本地变量实体，这是错误的做法，编译器会有警告。因为本地变量是堆栈变量，会在函数返回后被回收

  返回一个已经存在的全局或者中内存堆中的实体，这种做法会执行一个拷贝构造(copy construction)
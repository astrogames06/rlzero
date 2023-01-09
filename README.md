# raylib zero
A simple to use game framework build on raylib.

Raylib zero is a simple to use single header only game framework made with raylib.

## DISCLAIMER:

This is not intended to replace raylib. Infact you can use raylib zero in raylib and vice versa.

## What is raylib?

<img align="left" src="https://github.com/raysan5/raylib/blob/master/logo/raylib_logo_animation.gif" width="288px">

**raylib is a simple and easy-to-use library to enjoy videogames programming.**

raylib is highly inspired by Borland BGI graphics lib and by XNA framework and it's specially well suited for prototyping, tooling, graphical applications, embedded systems and education.

*NOTE for ADVENTURERS: raylib is a programming library to enjoy videogames programming; no fancy interface, no visual helpers, no debug button... just coding in the most pure spartan-programmers way.*

Ready to learn? Jump to [code examples!](https://www.raylib.com/examples.html)

---

##
##

## Why use raylib zero?

🤔 Begineer Friendly:
Raylib zero is made for the purpose of making video game programming easy.

😎 Open Source:
Raylib zeros source code is online which lets people change it and make it better.

🎈 Light Weight:
Raylib zeros source code only comes out to be under 10kb.

---

## Easy to use api

Basic window program

``` c
#include <rlzero.h>

void Update(void) {}

void Draw(void)
{
  fill(0, 0, 0);
}

int main()
{
  Init(840, 640, "Window! :)");
  // init varibles
  
  BeginGame();
}
```

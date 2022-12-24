/*
RAYLIB ZERO LICENSE

MIT License

Copyright (c) 2022 Marshroom

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef RAYLIBZERO_H
#define RAYLIBZERO_H

// includes
#include <stdint.h>
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <iostream>
#include <algorithm>


#define PHYSAC_IMPLEMENTATION
#if _WIN32 || _WIN64

#include "physac.hpp"

#elif __linux__

#include "physac.h"

#endif

// Scene

int WIDTH;
int HEIGHT;

bool IsRun = false;

struct TransformComponent
{
public:
    Vector2 position;
    float rotation;
};

// Actors

typedef struct Actor
{
public:
    TransformComponent transform;
    std::string path;
    Texture2D texture;
    bool killed;

    void Move(float x, float y)
    {
        this->transform.position.x += x * GetFrameTime();
        this->transform.position.y += y * GetFrameTime();
    }

    void Rotate(float angle)
    {
        this->transform.rotation += angle;
    }

    void SetPos(float x, float y)
    {
        this->transform.position.x = x;
        this->transform.position.y = y;
    }

    Vector2 GetPos()
    {
        return this->transform.position;
    }

    float GetX()
    {
        return this->transform.position.x;
    }
    void SetX(float x)
    {
        this->transform.position.x = x;
    }

    float GetY()
    {
        return this->transform.position.y;
    }
    void SetY(float y)
    {
        this->transform.position.y = y;
    }

    Vector2 GetSize()
    {
        return Vector2{ (float)this->texture.width, (float)this->texture.height };
    }
    void SetSize(int width, int height)
    {
        this->texture.width = width;
        this->texture.height = height;
    }
    void AddSize(int width, int height)
    {
        this->texture.width += width;
        this->texture.height += height;
    }

    float GetWidth()
    {
        return this->texture.width;
    }
    float GetHeight()
    {
        return this->texture.height;
    }
} Actor;

std::vector<Actor*> actors;

Actor InitActor(const std::string& path, float x, float y, float rotation = 0.f)
{
    if (IsRun)
    {
        TransformComponent transform = TransformComponent{Vector2{x,y}, rotation};
        Actor new_actor = Actor{ transform, 
            path, 
            LoadTexture(path.c_str()), 
            false
        };
        actors.push_back(&new_actor);

        return new_actor;
    }
    std::cerr << "Actor was created before Run() function!\n";
    return Actor{0, 0, 0, 0};
}

// physics

struct PhysicsBodyLite
{
    PhysicsBody body;
    Vector2 size;
    Color color;
};

std::vector<PhysicsBodyLite*> PhysicsBodies;

PhysicsBodyLite InitBodyRect(float x, float y, float width, float height, Color color, bool can_rotate)
{
    PhysicsBody body = CreatePhysicsBodyRectangle(Vector2{x, y}, width, height, 10);
    PhysicsBodyLite LiteBody = PhysicsBodyLite{body, Vector2{width, height}, color};

    PhysicsBodies.push_back(&LiteBody);

    return LiteBody;
}

void CreateBodyRect(float x, float y, float width, float height, Color color, bool can_rotate)
{
    PhysicsBody body = CreatePhysicsBodyRectangle(Vector2{x, y}, width, height, 10);
    PhysicsBodyLite LiteBody = PhysicsBodyLite{body, Vector2{width, height}, color};

    PhysicsBodies.push_back(&LiteBody);
}

// Game loop functions

void Input(void);
void Update(void);
void Draw(void);

void Init(int width, int height, const char* title)
{
    InitWindow(width, height, title);
    InitPhysics();
    IsRun = true;

    WIDTH = width;
    HEIGHT = height;
}

void BeginGame(void)
{
    while (!WindowShouldClose())
    {
        UpdatePhysics();
        Input();
        Update();

        BeginDrawing();

        // for (PhysicsBodyLite* body : PhysicsBodies)
        // {
        //     std::vector<PhysicsBodyLite*>::iterator itr = std::find(PhysicsBodies.begin(), PhysicsBodies.end(), body);
	    //     int index = std::distance(PhysicsBodies.begin(), itr);

        //     int vertexCount = GetPhysicsShapeVerticesCount(index);
        //     if (body[index].body.v)
        // }

        for (int i = 0; i < (int)PhysicsBodies.size(); i++)
        {
            int vertexCount = GetPhysicsShapeVerticesCount(i);
            if (vertexCount == 4)
            {
                DrawRectanglePro(Rectangle{PhysicsBodies[i]->body->position.x, 
                    PhysicsBodies[i]->body->position.y, 
                    PhysicsBodies[i]->size.x, 
                    PhysicsBodies[i]->size.y
                },
                    Vector2{PhysicsBodies[i]->size.x/2, PhysicsBodies[i]->size.y/2},
                    PhysicsBodies[i]->body->orient, PhysicsBodies[i]->color
                );
            }
        }

        Draw();

        EndDrawing();
    }

    CloseWindow();
    ClosePhysics();

    for (Actor* actor : actors)
    {
        UnloadTexture(actor->texture);
        delete actor;
    }
    delete &actors;
}

// Drawing functions

void fill(Color color)
{
    ClearBackground(color);
}

void rect(float x, float y, float width, float height, float rotation, Color color)
{
    DrawRectanglePro(Rectangle{x, y, width, height},
        Vector2{width/2, height/2},
        rotation, color
    );
}

void circle(float x, float y, float radius, Color color, bool fill)
{
    if (fill)
        DrawCircle(x, y, radius, color);
    else
        DrawCircleLines(x, y, radius, color);
}

void line(float startX, float startY, float endX, float endY, Color color)
{
    DrawLine(startX, startY, endX, endY, color);
}

void DrawActor(const Actor& actor)
{
    DrawTexturePro(actor.texture,
        Rectangle{0, 0, (float)actor.texture.width, (float)actor.texture.height},
        Rectangle{ actor.transform.position.x, actor.transform.position.y, (float)actor.texture.width, (float)actor.texture.height },
        Vector2 { (float)actor.texture.width/2, (float)actor.texture.height/2 },
        actor.transform.rotation,
        WHITE
    );
}

Color NewColor(uint32_t r, uint32_t g, uint32_t b)
{
    return Color { (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };
}

#endif
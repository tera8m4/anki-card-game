/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "Card.h"
#include "models/CardModel.h"
#include "ModelsRegistry.h"
#include "controllers/CardsMatchController.h"
#include "ResourceManager.h"

#include <iostream>
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    ResourceManager::getInstance().loadFont("noto", "assets/NotoSansJP-Regular.ttf");

    auto model1 = std::make_shared<CardModel>("私", "key1", "key2");
    auto model2 = std::make_shared<CardModel>("I", "key2", "key1");

    ModelsRegistry::getInstance().addCardModel(model1);
    ModelsRegistry::getInstance().addCardModel(model2);

	auto c = std::make_shared<Card>();
    c->setPosition({ 0.0f, 0.0f });

    auto c2 = std::make_shared<Card>();
    c2->setPosition({ 150.0f, 0.0f });

    CardsMatchController cardsController;    
    cardsController.addCard(c);
    cardsController.addCard(c2);
    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        c->update();
        c2->update();
        cardsController.update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

            c->draw();
            c2->draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

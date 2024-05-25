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
#include "transport/Transport.h"
#include <iostream>
#include <ranges>
#include <spdlog/spdlog.h>
#include "utils.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    utils::enableUTF8();
    //SetConsoleCodePage(CP_UTF8);
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    ResourceManager::getInstance().loadFont("noto", "assets/NotoSansJP-Regular.ttf");
    spdlog::info("よこそ");

    auto allDueCards = Transport::getInstance().findDueCards();
    auto tmpView = std::ranges::take_view(allDueCards, 6);
    std::vector<unsigned long long> dueCards(tmpView.begin(), tmpView.end());


    std::cout << std::endl;

    auto words = Transport::getInstance().getWords(dueCards);
    const auto& cardInfos = Transport::getInstance().getCardInfo(words);
    ModelsRegistry::getInstance().createFromCardInfos(cardInfos);


    std::vector<std::shared_ptr<Card>> cards;
    CardsMatchController cardsController;

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 2; ++j) {
            cards.emplace_back(std::make_shared<Card>());
            cards.back()->setPosition({ 210.0f * i + 10, j * 310.0f + 10 });
            cardsController.addCard(cards.back());
        }
    }



    //Transport::getInstance().init();


    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        for (auto& x : cards) {
            x->update();
        }

        cardsController.update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            for (auto& x : cards) {
                x->draw();
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

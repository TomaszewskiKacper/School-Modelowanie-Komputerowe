#include <SFML/Window.hpp>
#include <glad/glad.h>
#include "ShaderProgram.h"
#include "Board.h"
#include <iostream>



int main() {
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.sRgbCapable = false;
    contextSettings.minorVersion = 3;
    contextSettings.majorVersion = 3;

    sf::Window window(sf::VideoMode(1000, 1000), "OpenGL", sf::Style::Default, contextSettings);
    window.setActive(true);

    gladLoadGL();
    glViewport(0, 0, static_cast<GLsizei>(window.getSize().x), static_cast<GLsizei>(window.getSize().y));

    //Initialize Shader
    ShaderProgram shader;

    //Initialize Board
    Board board(200, 200);
    board.Generate();


    //Clock
    sf::Clock clock;
    float last_step = 0;

    // Main loop
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Rendering
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        board.Draw(shader);

        //timing
        float dt = clock.restart().asSeconds();
        //std::cout << 1.0f / dt << " FPS" << std::endl;
        last_step += dt;
        if (last_step > 0.10f) { //next step every x seconds
            board.Next_step();
            last_step -= 0.10f;
        }

        window.display();
    }



    return 0;
}

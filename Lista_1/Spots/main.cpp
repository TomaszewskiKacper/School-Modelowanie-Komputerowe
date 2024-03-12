#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <glad/glad.h>
#include "ShaderProgram.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>



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
    Board board(300, 300);
    board.Generate();

    sf::Texture pic;
    pic.create(window.getSize().x, window.getSize().y);

    //Clock
    int steps = 30000;
    sf::Clock clock;
    float last_step = 0.0f;
    float step_timing = 0.01f;

    //File
    std::ofstream file("../Spots_graphing/Spots_Density.txt");

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
        if (last_step > step_timing) { //next step every x seconds
            board.Next_step();
            last_step -= step_timing;
            if (steps) {
                //Write to File
                if (file.is_open()) {
                    file << board.Density() << " ";	//pass board density into file
                }
                //grab screen shot every x steps
                if (false) {          
                    pic.update(window);
                    std::string filename = "im_";
                    filename += std::to_string(steps);
                    filename += ".png";
                    pic.copyToImage().saveToFile(filename);
                }
                steps--;
                system("cls");
                std::cout << steps << std::endl << "density: " << board.Density();
            }

        }

        window.display();
    }

    file.close();


    return 0;
}

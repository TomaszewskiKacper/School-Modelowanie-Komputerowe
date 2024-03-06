#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glad/glad.h>
#include "ShaderProgram.h"
#include "Cube.h"
#include "Camera.h"
#include "Chunk.h"
#include "CubePalette.h"

int main()
{
    //SETTINGS
    const int WIDTH = 32;
    const int HEIGHT = 32;
    const int DEPTH = 32;
    const float UPDATE_RATE = 0.85f;    //how often next step is calculated
    const int UPDATE_VERSION = 2;   //1 - only 6 neighbours, 2 - all 26 neighbours
    ///////////////////////////////


    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.sRgbCapable = false;
    contextSettings.minorVersion = 3;
    contextSettings.majorVersion = 3;

    sf::Window window(sf::VideoMode(1000, 800), "OpenGL", sf::Style::Default, contextSettings);
    window.setActive(true);

    gladLoadGL();
    glViewport(0, 0, static_cast<GLsizei>(window.getSize().x), static_cast<GLsizei>(window.getSize().y));

 
    // ShaderProgram
    ShaderProgram shaderProgram;
    
    //Chunk
    CubePalette cubePalette;
    Chunk<WIDTH, HEIGHT, DEPTH>chunk(glm::vec2(0.0f, 0.0f), cubePalette);
    chunk.First();


 

    sf::Clock clock;
    sf::Clock clock_refresh;

    float dt_r = 0.0f;

    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    Camera camera(glm::vec3(0.0f, HEIGHT, 2.0f), glm::vec3(0.0f, 0.0f, -1.0f), 0.0f, 0.0f);

    // run the program as long as the window is open
    glEnable(GL_DEPTH_TEST);
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

        const sf::Vector2i newMousePosition = sf::Mouse::getPosition();
        camera.Rotate(newMousePosition - mousePosition);
        mousePosition = newMousePosition;

        dt_r += clock_refresh.restart().asSeconds();
        float dt = clock.restart().asSeconds();
        dt *= 10;

        //Inputs
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            camera.MoveForward(dt);
            //std::cout << "W";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            camera.MoveBackward(dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            camera.MoveLeft(dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            camera.MoveRight(dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            camera.MoveUp(dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            camera.MoveDown(dt);
        }



        

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Use();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        shaderProgram.SetMat4("mvp", projection * camera.View());
        

        //refresh chunk every x sec
        if (dt_r > UPDATE_RATE) {
            dt_r -= UPDATE_RATE;
            if (UPDATE_VERSION == 1)
                chunk.Update();

            else if (UPDATE_VERSION == 2)
                chunk.Update_v2();
        }

        //Draw chunk
        chunk.Draw(shaderProgram, camera.View());




        window.display();
    }


    return 0;
}
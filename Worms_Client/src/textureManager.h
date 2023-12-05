#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
using namespace sf;

class TextureManager
{
public:
    GLuint LoadTexture(sf::String name);
    void drawSkybox(std::vector<GLuint> skybox, float size);
    void drawBox(GLuint skybox, float size);
    std::vector<GLuint> createSkybox();
    GLuint createBox();
    GLuint createWorm();
    GLuint createSand();
    void addName(std::string& text, const Font& font, const Vector2f& position, RenderWindow& window, float fontSize);
    void convertWorldToWindowCoordinates(float worldX, float worldY, float worldZ, Vector2f& windowCoords, const RenderWindow& window);

};
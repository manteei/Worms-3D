#include "textureManager.h"

#define GL_CLAMP_TO_EDGE 0x812F

GLuint TextureManager::LoadTexture(sf::String name)
{
    sf::Image image;
    if (!image.loadFromFile(name))
        return EXIT_FAILURE;

    image.flipVertically();

    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return texture;
}

void TextureManager::drawSkybox(std::vector<GLuint> skybox, float size)
{
    glBindTexture(GL_TEXTURE_2D, skybox[0]);
    glBegin(GL_QUADS);
    //front
    glTexCoord2f(0, 0);   glVertex3f(-size, -size, -size);
    glTexCoord2f(1, 0);   glVertex3f(size, -size, -size);
    glTexCoord2f(1, 1);   glVertex3f(size, size, -size);
    glTexCoord2f(0, 1);   glVertex3f(-size, size, -size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox[1]);
    glBegin(GL_QUADS);
    //back
    glTexCoord2f(0, 0); glVertex3f(size, -size, size);
    glTexCoord2f(1, 0); glVertex3f(-size, -size, size);
    glTexCoord2f(1, 1); glVertex3f(-size, size, size);
    glTexCoord2f(0, 1); glVertex3f(size, size, size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox[2]);
    glBegin(GL_QUADS);
    //left
    glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
    glTexCoord2f(1, 0); glVertex3f(-size, -size, -size);
    glTexCoord2f(1, 1); glVertex3f(-size, size, -size);
    glTexCoord2f(0, 1); glVertex3f(-size, size, size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox[3]);
    glBegin(GL_QUADS);
    //right
    glTexCoord2f(0, 0); glVertex3f(size, -size, -size);
    glTexCoord2f(1, 0); glVertex3f(size, -size, size);
    glTexCoord2f(1, 1); glVertex3f(size, size, size);
    glTexCoord2f(0, 1); glVertex3f(size, size, -size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox[4]);
    glBegin(GL_QUADS);
    //bottom
    glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
    glTexCoord2f(1, 0); glVertex3f(size, -size, size);
    glTexCoord2f(1, 1); glVertex3f(size, -size, -size);
    glTexCoord2f(0, 1); glVertex3f(-size, -size, -size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox[5]);
    glBegin(GL_QUADS);
    //top  		
    glTexCoord2f(0, 0); glVertex3f(-size, size, -size);
    glTexCoord2f(1, 0); glVertex3f(size, size, -size);
    glTexCoord2f(1, 1); glVertex3f(size, size, size);
    glTexCoord2f(0, 1); glVertex3f(-size, size, size);
    glEnd();
}



void TextureManager::drawBox(GLuint skybox, float size)
{
    glBindTexture(GL_TEXTURE_2D, skybox);
    glBegin(GL_QUADS);
    //front
    glTexCoord2f(0, 0);   glVertex3f(-size, -size, -size);
    glTexCoord2f(1, 0);   glVertex3f(size, -size, -size);
    glTexCoord2f(1, 1);   glVertex3f(size, size, -size);
    glTexCoord2f(0, 1);   glVertex3f(-size, size, -size);

    //back
    glTexCoord2f(0, 0); glVertex3f(size, -size, size);
    glTexCoord2f(1, 0); glVertex3f(-size, -size, size);
    glTexCoord2f(1, 1); glVertex3f(-size, size, size);
    glTexCoord2f(0, 1); glVertex3f(size, size, size);

    //left
    glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
    glTexCoord2f(1, 0); glVertex3f(-size, -size, -size);
    glTexCoord2f(1, 1); glVertex3f(-size, size, -size);
    glTexCoord2f(0, 1); glVertex3f(-size, size, size);

    //right
    glTexCoord2f(0, 0); glVertex3f(size, -size, -size);
    glTexCoord2f(1, 0); glVertex3f(size, -size, size);
    glTexCoord2f(1, 1); glVertex3f(size, size, size);
    glTexCoord2f(0, 1); glVertex3f(size, size, -size);

    //bottom
    glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
    glTexCoord2f(1, 0); glVertex3f(size, -size, size);
    glTexCoord2f(1, 1); glVertex3f(size, -size, -size);
    glTexCoord2f(0, 1); glVertex3f(-size, -size, -size);

    //top  		
    glTexCoord2f(0, 0); glVertex3f(-size, size, -size);
    glTexCoord2f(1, 0); glVertex3f(size, size, -size);
    glTexCoord2f(1, 1); glVertex3f(size, size, size);
    glTexCoord2f(0, 1); glVertex3f(-size, size, size);
    glEnd();
}

void TextureManager::addName(std::string& text, const sf::Font& font, const sf::Vector2f& position, RenderWindow& window, float fontSize) {
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(fontSize);
    sfText.setFillColor(sf::Color::Black);
    sfText.setPosition(position);

    window.draw(sfText);
}

std::vector<GLuint> TextureManager::createSkybox() {
    std::vector<GLuint> skybox(6);

    skybox[0] = LoadTexture("resources/skybox/front.png");
    skybox[1] = LoadTexture("resources/skybox/back.png");
    skybox[2] = LoadTexture("resources/skybox/left.png");
    skybox[3] = LoadTexture("resources/skybox/right.png");
    skybox[4] = LoadTexture("resources/skybox/bottom.png");
    skybox[5] = LoadTexture("resources/skybox/top.png");

    return skybox;
}


void TextureManager::convertWorldToWindowCoordinates(float worldX, float worldY, float worldZ, Vector2f& windowCoords, const RenderWindow& window)
{
    GLdouble modelview[16];
    GLdouble projection[16];
    GLint viewport[4];

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLdouble winX, winY, winZ;
    gluProject(worldX, worldY, worldZ, modelview, projection, viewport, &winX, &winY, &winZ);

    windowCoords.x = static_cast<float>(winX);

    windowCoords.y = static_cast<float>(window.getSize().y - winY);

}

GLuint TextureManager::createBox() {
    return LoadTexture("resources/textures/grass.jpg");
}

GLuint TextureManager::createSand() {
    return LoadTexture("resources/textures/sand.jpg");
}

GLuint TextureManager::TextureManager::createWorm() {
    return LoadTexture("resources/textures/pink.png");
}
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Complexe.h"

struct Features {
    const sf::Vector2i sizeWindow{ 1024, 1024 };
    const double size{ double(sizeWindow.x) };
    std::vector<std::vector<Complexe>> tabCom{};
    std::vector<std::vector<unsigned int>> tabDiv;
    std::pair<double, double> posVal;
    std::pair<double, double> sizeVal;
    unsigned int iteration{ 0 };
};

struct MouseData {
    bool pressed{};
    sf::Vector2f ptPressed{};
    sf::RectangleShape rec{};
};

struct Engine {
    bool process{ false };
    bool display{ true };
    int scaleColor{ 5 };
    unsigned int d{ 1 };
    sf::Image screenShot;
    sf::Sprite spriteScreen;
    sf::Font font;
    sf::String preTextIteration{ "Iteration: " };
    sf::String preTextResolution{ "Qualite: " };
    sf::String preTextNbFractale{ "Periode aff: " };
    sf::String preTextRe{ "G/D: " };
    sf::String preTextIm{ "H/B: " };
    sf::Text textIteration;
    sf::Text textResolution;
    sf::Text textNbFractale;
    sf::Text textRe;
    sf::Text textIm;
};

Complexe f(Complexe z, Complexe c, unsigned int d);
void reset(Features& features);
sf::Color getColorIteration(unsigned int iteration, int scaleColor);

int main()
{
    Engine engine{};
    Features features{};
    MouseData mouseData{};


    const std::pair<double, double> centerValue{ 0, 0 };
    const std::pair<double, double> sizeValue{ 5, 5 };

    features.sizeVal = sizeValue;
    features.posVal = { centerValue.first - sizeValue.first / 2., centerValue.second - sizeValue.second / 2. };

    engine.font.loadFromFile("JAi_____.ttf");

    engine.textIteration.setFont(engine.font);
    engine.textNbFractale.setFont(engine.font);
    engine.textRe.setFont(engine.font);
    engine.textIm.setFont(engine.font);

    engine.textIteration.setOutlineThickness(2);
    engine.textNbFractale.setOutlineThickness(2);
    engine.textRe.setOutlineThickness(2);
    engine.textIm.setOutlineThickness(2);

    engine.textIteration.setOutlineColor(sf::Color::White);
    engine.textResolution.setOutlineColor(sf::Color::White);
    engine.textNbFractale.setOutlineColor(sf::Color::White);
    engine.textRe.setOutlineColor(sf::Color::White);
    engine.textIm.setOutlineColor(sf::Color::White);

    engine.textIteration.setCharacterSize(20);
    engine.textNbFractale.setCharacterSize(20);
    engine.textRe.setCharacterSize(20);
    engine.textIm.setCharacterSize(20);

    engine.textIteration.setFillColor(sf::Color::Black);
    engine.textNbFractale.setFillColor(sf::Color::Black);
    engine.textRe.setFillColor(sf::Color::Black);
    engine.textIm.setFillColor(sf::Color::Black);

    engine.textIteration.setPosition(sf::Vector2f(0, 0));
    engine.textNbFractale.setPosition(sf::Vector2f(0, 25));
    engine.textRe.setPosition(sf::Vector2f(0, 50));
    engine.textIm.setPosition(sf::Vector2f(0, 75));

    engine.textIteration.setString(engine.preTextIteration);
    engine.textNbFractale.setString(engine.preTextNbFractale + std::to_string(engine.d));
    engine.textRe.setString(engine.preTextRe + std::to_string(features.posVal.first) + ", " + std::to_string(features.posVal.first + features.sizeVal.first));
    engine.textIm.setString(engine.preTextIm + std::to_string(features.posVal.second) + ", " + std::to_string(features.posVal.second + features.sizeVal.second));


    mouseData.rec.setFillColor(sf::Color::Transparent);
    mouseData.rec.setOutlineThickness(4);
    mouseData.rec.setOutlineColor(sf::Color::White);

    sf::RenderWindow window(sf::VideoMode(features.sizeWindow.x, features.sizeWindow.y), "Mandelbrot set v2");

    reset(features);

    engine.screenShot.create(features.sizeWindow.x, features.sizeWindow.y, sf::Color::Black);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Left) {
                    mouseData.pressed = true;
                    mouseData.ptPressed = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                }
                else if (event.key.code == sf::Mouse::Right) {
                    features.sizeVal = sizeValue;
                    features.posVal = std::make_pair(centerValue.first - sizeValue.first / 2., centerValue.second - sizeValue.second / 2.);

                    reset(features);
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.key.code == sf::Mouse::Left) {
                    mouseData.pressed = false;

                    sf::FloatRect scaleFloatRect = mouseData.rec.getGlobalBounds();

                    if (scaleFloatRect.width > 0) {
                        scaleFloatRect.top /= features.sizeWindow.y;
                        scaleFloatRect.left /= features.sizeWindow.x;
                        scaleFloatRect.width /= features.sizeWindow.x;
                        scaleFloatRect.height /= features.sizeWindow.y;


                        features.posVal.first = features.posVal.first + scaleFloatRect.left * features.sizeVal.first;
                        features.posVal.second = features.posVal.second + scaleFloatRect.top * features.sizeVal.second;
                        features.sizeVal.first *= scaleFloatRect.width;
                        features.sizeVal.second *= scaleFloatRect.height;

                        reset(features);

                        engine.textRe.setString(engine.preTextRe + std::to_string(features.posVal.first) + ", " + std::to_string(features.posVal.first + features.sizeVal.first));
                        engine.textIm.setString(engine.preTextIm + std::to_string(features.posVal.second) + ", " + std::to_string(features.posVal.second + features.sizeVal.second));

                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    engine.process = !engine.process;
                }
                else if (event.key.code == sf::Keyboard::D) {
                    engine.display = !engine.display;
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    engine.scaleColor++;
                    if (engine.scaleColor > 10)
                        engine.scaleColor = 10;
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    engine.scaleColor--;
                    if (engine.scaleColor < -10)
                        engine.scaleColor = -10;
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    engine.d--;
                    if (engine.d < 1)
                        engine.d = 1;

                    reset(features);

                    engine.textNbFractale.setString(engine.preTextNbFractale + std::to_string(engine.d));
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    engine.d++;
                    if (engine.d > 100)
                        engine.d = 100;

                    reset(features);

                    engine.textNbFractale.setString(engine.preTextNbFractale + std::to_string(engine.d));
                }
            }
        }

        if (mouseData.pressed) {
            mouseData.rec.setPosition(mouseData.ptPressed);
            mouseData.rec.setSize(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)) - mouseData.ptPressed));
            
            if (mouseData.rec.getSize().x > mouseData.rec.getSize().y)
                mouseData.rec.setSize(sf::Vector2f(mouseData.rec.getSize().x, mouseData.rec.getSize().x));
            else 
                mouseData.rec.setSize(sf::Vector2f(mouseData.rec.getSize().y, mouseData.rec.getSize().y));
        }

        if (engine.process && !mouseData.pressed) {
            bool allBlack{ true };
            while (allBlack) {
                for (double i{ 0 }; i < features.size; i++) {
                    for (double j{ 0 }; j < features.size; j++) {
                        if (std::isfinite(features.tabCom[i][j].getModule()))
                            features.tabCom[i][j] = f(features.tabCom[i][j], Complexe(features.posVal.first + i * features.sizeVal.first / features.size, features.posVal.second + j * features.sizeVal.second / features.size), engine.d);
                        else
                            allBlack = false;
                    }
                }
                engine.textIteration.setString(engine.preTextIteration + std::to_string(features.iteration));
                features.iteration++;
            }
        }

        for (int i{ 0 }; i < features.size; i++)
            for (int j{ 0 }; j < features.size; j++)
                if (!std::isfinite(features.tabCom[i][j].getModule()) && features.tabDiv[i][j] == 0)
                    features.tabDiv[i][j] = features.iteration;

        if (engine.display) {
            window.clear(sf::Color::Black);

            for (int i{ 0 }; i < features.size; i++) {
                for (int j{ 0 }; j < features.size; j++) {
                    if (!std::isfinite(features.tabCom[i][j].getModule()))
                        engine.screenShot.setPixel(i, j, getColorIteration(features.tabDiv[i][j], engine.scaleColor));
                    else
                        engine.screenShot.setPixel(i, j, sf::Color::Black);
                }
            }

            sf::Texture texture;
            texture.loadFromImage(engine.screenShot);
            engine.spriteScreen.setTexture(texture);
            window.draw(engine.spriteScreen);

            if (mouseData.pressed)
                window.draw(mouseData.rec);
            window.draw(engine.textIteration);
            window.draw(engine.textResolution);
            window.draw(engine.textNbFractale);
            window.draw(engine.textRe);
            window.draw(engine.textIm);
            window.display();
        }
    }

    return 0;
}


Complexe f(Complexe z, Complexe c, unsigned int d) {
    Complexe zn{ z };

    for (unsigned int i{ 0 }; i < d; i++)
        zn = zn * z;

    return zn + c;
}

void reset(Features& features)
{
    features.tabCom.clear();
    features.tabDiv.clear();
    
    std::vector<unsigned int> lineZ{};
    for (int i{ 0 }; i < features.size; i++)
        lineZ.push_back(0);
    for (int i{ 0 }; i < features.size; i++)
        features.tabDiv.push_back(lineZ);

    std::vector<Complexe> lineC{};
    for (int i{ 0 }; i < features.size; i++)
        lineC.push_back(Complexe(0, 0));
    for (int i{ 0 }; i < features.size; i++)
        features.tabCom.push_back(lineC);

    features.iteration = 0;
}

sf::Color getColorIteration(unsigned int iteration, int scaleColor)
{
    iteration *= scaleColor;
    sf::Uint8 r{ 0 };
    sf::Uint8 g{ 0 };
    sf::Uint8 b{ 0 };

    iteration %= 6 * 255;

    if (iteration <= 255) {
        r = iteration;
        g = 0;
        b = 255;
    }
    else if (iteration < 2 * 255) {
        iteration %= 255;

        r = 255;
        g = 0;
        b = 255 - iteration;
    }
    else if (iteration < 3 * 255) {
        iteration %= 255;

        r = 255;
        g = iteration;
        b = 0;
    }
    else if (iteration < 4 * 255) {
        iteration %= 255;

        r = 255 - iteration;
        g = 255;
        b = 0;
    }
    else if (iteration < 5 * 255) {
        iteration %= 255;

        r = 0;
        g = 255;
        b = iteration;
    }
    else if (iteration < 6 * 255) {
        iteration %= 255;

        r = 0;
        g = 255 - iteration;
        b = 255;
    }

    return sf::Color(r, g, b);
}
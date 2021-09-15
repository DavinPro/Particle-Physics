#include <SFML/Graphics.hpp>

#include <vector>
#include <array>
#include <iostream>
#include <random>

#include "particle.h"
#include "rectangle.hpp"
#include "quadtree.hpp"


// Window Settings
const uint32_t WINDOW_WIDTH = 1000;
const uint32_t WINDOW_HEIGHT = 1000;
const uint16_t FPS_LIMIT = 60;
const Rectangle<float> windowBound(0.0, 0.0, WINDOW_WIDTH, WINDOW_HEIGHT);

// Particle Settings
const unsigned int NUM_PARTS = 10;
const float MIN_PART_RADIUS = 1.0f;
const float MAX_PART_RADIUS = 15.0f;
const float MIN_MASS = 4.0f;
const float MAX_MASS = 255.0f;
const float MIN_VELOCITY = -200.0f;
const float MAX_VELOCITY = 200.0f;

// Render Settings
bool drawQuadrants = false;

// Particle containers
std::vector<Particle> particles;
QuadTree<Particle> tree;

// Fixed timestep for updates
const double DT = 1.0 / FPS_LIMIT;

void handleEvents(sf::RenderWindow& window);
void createParticle(float x = 0.0f, float y = 0.0f);
void render(sf::RenderWindow& window);
void drawQuadTree(const QuadTree<Particle>& tree, sf::RenderWindow& window);
void drawRectangle(const Rectangle<float>& rect, sf::RectangleShape& outline, sf::RenderWindow& window);
void update(double dt);
void updateFPS(sf::Time dt);

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hello SFML", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setFramerateLimit(FPS_LIMIT);

    sf::Clock clock;

    for (int i = 0; i < NUM_PARTS; i++)
        createParticle();

    while (window.isOpen()) {
        sf::Time start = clock.getElapsedTime();

        handleEvents(window);

        // QuadTree must be recreated every frame
        // potential optimization to update rather than recreate
        tree = QuadTree<Particle>(windowBound);

        update(DT);

        // Render
        render(window);
        window.display();

        updateFPS(clock.restart() - start);
    }

    return 0;
}

void handleEvents(sf::RenderWindow& window) {
    static sf::Event event;

    while (window.pollEvent(event)) {
        switch (event.type) {

        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                window.close();
                break;
            case sf::Keyboard::Q:
                drawQuadrants = !drawQuadrants;
                break;
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
                createParticle(event.mouseButton.x, event.mouseButton.y);
            break;
        }
    }
}

void createParticle(float x, float y) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> posDistr(MAX_PART_RADIUS, WINDOW_WIDTH - MAX_PART_RADIUS);
    static std::uniform_real_distribution<float> radDistr(MIN_PART_RADIUS, MAX_PART_RADIUS);
    static std::uniform_real_distribution<float> velDistr(MIN_VELOCITY, MAX_VELOCITY);
    static std::uniform_real_distribution<float> massDistr(MIN_MASS, MAX_MASS);

    // To avoid creating another random number generator for populating
    // the particles in main, x and y are defaulted to 0.0, allowing
    // access to the generators here. A particle created by clicking the 
    // mouse can't be placed at a coordinate of 0.0, and so if x = 0.0 it is
    // known that the position should be randomly generated.
    if (x == 0.0) {
        x = posDistr(gen);
        y = posDistr(gen);
    }

    Particle p(Vec2<float>(x, y), radDistr(gen), Vec2<float>(velDistr(gen), velDistr(gen)),
        windowBound, massDistr(gen));
    particles.push_back(p);
}

void render(sf::RenderWindow& window) {
    window.clear();

    if (drawQuadrants)
        drawQuadTree(tree, window);

    for (auto& p : particles)
        window.draw(p.shape);
}

void drawQuadTree(const QuadTree<Particle>& tree, sf::RenderWindow& window) {
    std::vector<Rectangle<float>> boundBoxes;
    tree.getBoundBoxes(boundBoxes);

    sf::RectangleShape outline;
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color::White);
    outline.setOutlineThickness(1);

    for (auto& box : boundBoxes)
        drawRectangle(box, outline, window);
}

void drawRectangle(const Rectangle<float>& rect, sf::RectangleShape& outline, sf::RenderWindow& window) {
    outline.setSize(sf::Vector2f(rect.width, rect.height));
    outline.setPosition(rect.left, rect.top);

    window.draw(outline);
}

void update(double dt) {
    static Rectangle<float> searchRect(0.0f, 0.0f, 0.0f, 0.0f);
    static std::vector<Particle*> nearParts;

    for (auto& p : particles) {
        p.update(dt);
        tree.insert(p);
    }

    for (auto& p : particles) {
        searchRect = Rectangle<float>(p.pos.x - p.radius * 2, p.pos.y - p.radius * 2, p.radius * 4, p.radius * 4);
        tree.query(nearParts, searchRect);

        for (auto& np : nearParts) {
            if (np != &p && p.intersects(*np)) {
                p.collide(*np);
                break;
            }
        }
        nearParts.clear();
    }
}

void updateFPS(sf::Time dt) {
    static uint16_t frames = 0;
    static double accTime = 0.0;

    frames++;
    accTime += dt.asSeconds();
    if (accTime > 1.0) {
        std::cout << "fps: " << floor(frames / accTime) << std::endl;

        frames = 0;
        accTime = 0.0;
    }
}
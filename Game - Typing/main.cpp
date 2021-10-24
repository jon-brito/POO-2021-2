//g++ main.cpp -o sfml-app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system && ./sfml-app
#include <iostream>
#include <vector>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
using namespace std;

#define WINDOW_W 1024
#define WINDOW_H 768
#define FPS 60
#define SPEED 10

struct Pencil {
    sf::Font font;
    sf::Text text;
    sf::RenderWindow& window;

    Pencil(sf::RenderWindow& window) : window {window} {
        if (!font.loadFromFile("./assets/Roboto-Regular.ttf"))
            std::cout << "\nFont load error!\n";
        text.setFont(font);
    }

    void write(string str, int x, int y, int size, sf::Color color = sf::Color::White) {
        this->text.setFillColor(color);
        this->text.setString(str);
        this->text.setPosition(x, y);
        this->text.setCharacterSize(size);
        window.draw(text);
    }


};

struct Bubble {
    int x;
    int y;
    int speed;
    char letter;
    bool alive {true};

    static const int radius {20};   

    Bubble(int x, int y, char letter, int speed) {
        this->x = x;
        this->y = y;
        this->letter = letter;
        this->speed = speed;
    }

    void update() {
        this->y += this->speed;
    }

    void draw(sf::RenderWindow& window) {
        sf::CircleShape circle(Bubble::radius);
        circle.setPosition(x,y);
        circle.setFillColor(sf::Color::White);
        window.draw(circle);

        static Pencil pencil(window);
        pencil.write(string(1,this->letter), this->x + 0.5 * Bubble::radius, y, Bubble::radius * 1.5, sf::Color::Black);
    }

};

struct Board {
    sf::RenderWindow& window;
    Pencil pencil;
    vector<Bubble> bubbles;

    int hits {0};
    int misses {0};

    Board(sf::RenderWindow& window) : window(window), pencil(window) {
    }

    void update() {
        if (this->checkNewBubble())
            this->addNewBubble();


        for (Bubble& bubble : bubbles) {
            bubble.update();
        }

        this->countOutsideBubbles();
        this->removeBubbles();
    }

    void countHits(char letter) {
        for (auto& bubble : bubbles) {
            if (bubble.letter == letter) {
                this->hits++;
                bubble.alive = false;
                break;
            }
        }
    }

    void addNewBubble() {
        int x = rand() % ((int) this->window.getSize().x - (2 * Bubble::radius));
        int y = -2 * Bubble::radius;
        int speed = rand() % SPEED + 1; 
        int letter = rand() % 26 + 'A';
        bubbles.push_back(Bubble(x, y, letter, speed));
    }

    bool checkNewBubble() {
        static const int new_bubble_timeout {25};
        static int new_bubble_timer {0};

        new_bubble_timer--;
        if (new_bubble_timer <= 0) {
            new_bubble_timer = new_bubble_timeout;
            return true;
        }
        return false;
    }

    void countOutsideBubbles() {
        for (auto& bubble : bubbles) {
            if (bubble.y + 2 * Bubble::radius > this->window.getSize().y) {
                if (bubble.alive) {
                    bubble.alive = false;
                    this->misses++;
                }
            }
        }
    }

    void removeBubbles() {
        vector<Bubble> alive {};
        for (auto& bubble : bubbles)
            if (bubble.alive)
                alive.push_back(bubble);

        this->bubbles = alive;
    }

    void draw() {
        pencil.write("Hits: " + to_string(this->hits) + "    Misses: " + to_string(this->misses), 10, 10, 30);
        pencil.write("Alive Bubbles: " + to_string(this->bubbles.size()), 10, 40, 30);
        for (Bubble& bubble : bubbles) {
            bubble.draw(window);
        }
    }
};

struct Game {
    sf::RenderWindow window;
    function<void()> on_uptade;
    Board board;

    Game() : window (sf::VideoMode(WINDOW_W, WINDOW_H), "Game"), board(window) {
        on_uptade = [&] {
            this->gameplay();
        };
        
        window.setFramerateLimit(FPS);
    }

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                char code = static_cast<char>(event.text.unicode);
                code = toupper(code);
                board.countHits(code);
            }
        }
    }

    void gameplay() {
        board.update();

        if (board.misses == 10) {
            on_uptade = [&] {
                this->gameover();
            };
        }

        window.clear();
        board.draw();
        window.display();
    }

    void gameover() {
        window.clear(sf::Color::Red);
        static Pencil pencil(window);
        pencil.write("GAME OVER", window.getSize().x / 4, window.getSize().y / 2 - 80, 100, sf::Color::Black);
        pencil.write("HITS: " + to_string(board.hits), window.getSize().x / 2 - 170, window.getSize().y / 2 + 50, 100, sf::Color::Black);
        window.display();

        sf::sleep(sf::Time(sf::seconds(5)));
        window.close();
    }

    void mainLoop() {
        while (window.isOpen()) {
            processEvents();
            on_uptade(); 
        }
    }
};  

int main() {
    srand(time(NULL));

    Game game;
    game.mainLoop();

    return 0;
}
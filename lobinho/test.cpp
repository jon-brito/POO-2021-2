//g++ test.cpp -o sfml-app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system && ./sfml-app
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define STEP 100
#define W_WINDOW 900
#define H_WINDOW 700

void setSize(sf::Sprite& sprite, int width, int height) {
    auto rect = sprite.getLocalBounds();
    sprite.setScale((float) width / rect.width, (float) height / rect.height);
}

struct Entity {
    int x {0};
    int y {0};
    int step {0};
    int score {0};
    sf::Sound sound;
    sf::Sprite sprite;

    Entity(int x, int y, int step, sf::Texture& texture, sf::SoundBuffer& buffer) {
        this->x = x;
        this->y = y;
        this->step = step;
        this->sprite.setTexture(texture);
        this->sound.setBuffer(buffer);
    }

    void draw(sf::RenderWindow& window) {
        this->sprite.setPosition(x * step, y * step);
        setSize(this->sprite, step, step);
        window.draw(this->sprite);
    }

    void upScore() {
        this->score++;
        sound.play();
    }
};

struct Coin {
    int x {0};
    int y {0};
    int step{0};
    sf::Sprite sprite;

    Coin(int step, sf::Texture& texture) {
        int rangeW = std::rand() % 9;
        int rangeH = std::rand() % 7;

        this->x = rangeW;
        this->y = rangeH;

        this->step = step;
        this->sprite.setTexture(texture);
        setSize(this->sprite, step, step);
    }

    void draw(sf::RenderWindow& window) {
        this->sprite.setPosition(x * step, y * step);
        window.draw(this->sprite);
    }

    void randPos() {
        this->x = std::rand() % W_WINDOW / STEP;
        this->y = std::rand() % H_WINDOW / STEP;
    }    
};

struct Board {
    int nc {0};
    int nl {0};
    int step {0};
    sf::Sprite sprite;

    Board(int nc, int nl, int step, sf::Texture& texture) {
        this->nc = nc;
        this->nl = nl;
        this->step = step;
        this->sprite.setTexture(texture);
        setSize(this->sprite, W_WINDOW, H_WINDOW);
        this->sprite.setPosition(0, 0);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(this->sprite);
    }
};

sf::Texture loadTexture(std::string path) {
    sf::Texture texture;
    texture.loadFromFile(path);
    return texture;
}

void moveEntity(sf::Keyboard::Key key, Entity& entity, std::vector<sf::Keyboard::Key> move) {
    if (key == move[0] && entity.x > 0) {
        entity.x--;
    } else if (key == move[1] && entity.y > 0) {
        entity.y--;
    } else if (key == move[2] && entity.x < (W_WINDOW / STEP) - 1) {
        entity.x++;
    } else if (key == move[3] && entity.y < (H_WINDOW / STEP) - 1) {
        entity.y++;
    }
}


int main() {
    srand(time(NULL));

    sf::Texture gold_coin_text(loadTexture("./assets/gold_coin2.png"));
    sf::Texture background_text(loadTexture("./assets/background.png"));
    sf::Texture runner_text(loadTexture("./assets/runner.png"));

    sf::Font font;
    if (!font.loadFromFile("./assets/Minecraft.ttf")) {
        std::cout << "FONT ERROR\n";
        exit(1);
    }

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("./assets/goodCoin.wav")) {
        std::cout << "AUDIO ERROR\n";
        exit(1);
    }

    Entity runner(3, 2, STEP, runner_text, buffer);
    Coin goldcoin(STEP, gold_coin_text);
    Board board(H_WINDOW / STEP, W_WINDOW / STEP, STEP, background_text);

    sf::Text text;
    text.setFont(font);
    text.setString("Score: 0");
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    sf::RenderWindow window(sf::VideoMode(W_WINDOW, H_WINDOW), "Game");
    while (window.isOpen()) {        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                moveEntity(event.key.code, runner, {sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Down});
            }
        }   
       
        window.clear();

        if (runner.x == goldcoin.x && runner.y == goldcoin.y) {
            runner.upScore(); 
            text.setString("Score: " + std::to_string(runner.score));
            if (runner.score < 10) {
                goldcoin.randPos();
            } else {
                goldcoin.x = -100;
            }           
        }

        board.draw(window);
        goldcoin.draw(window);
        runner.draw(window);
        window.draw(text);

        window.display();

        if (runner.score == 10) {
            sf::sleep(sf::Time(sf::seconds(1)));
            window.close();
        }        
    }

    return 0;
}
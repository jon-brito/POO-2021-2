//g++ coin.cpp -o sfml-app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system && ./sfml-app
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include <functional>
#include <iostream>
#include <cstdlib>
#include <list>
#include <ctime>

#define STEP 100
#define W_WINDOW 1000
#define H_WINDOW 700

void setSize(sf::Sprite& sprite, int width, int height) {
    auto rect = sprite.getLocalBounds();
    sprite.setScale((float) width / rect.width, (float) height / rect.height);
}

sf::Texture loadTexture(std::string path) {
    sf::Texture text;
    if (!text.loadFromFile(path)) {
        std::cout << path << " error\n";
        exit(1);
    } else {
        return text;
    }
}

sf::SoundBuffer setAudio(std::string path) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(path)) {
        std::cout << path << " error";
        exit(1);
    } else {
        return buffer;
    }
}

struct Speaker {
    sf::Sound goodSound;
    sf::Sound badSound;
    sf::Sound winSound;
    sf::Sound loseSound;

    sf::SoundBuffer buffer;
    sf::SoundBuffer buffer2;
    sf::SoundBuffer buffer3;
    sf::SoundBuffer buffer4;

    Speaker() {
        buffer = setAudio("./assets/goodCoin.wav");
        goodSound.setBuffer(buffer);

        buffer2 = setAudio("./assets/badCoin.wav");
        badSound.setBuffer(buffer2);

        buffer3 = setAudio("./assets/win.wav");
        winSound.setBuffer(buffer3);

        buffer4 = setAudio("./assets/lose.wav");
        loseSound.setBuffer(buffer4);
    }

    void playCoin(bool is_gold) {
        if (is_gold) goodSound.play();
        else badSound.play();
    }

    void playFinal(bool you_win) {
        if (you_win) winSound.play();
        else loseSound.play();
    }
};

struct Pencil {
    sf::Font font;
    sf::Text text;

    Pencil() {
        if (!font.loadFromFile("./assets/Minecraft.ttf")) {
            std::cout << "FONT ERROR\n";
            exit(1);
        }

        text.setFont(font);
    }

    void writeScore(sf::RenderWindow& window, int score) {
        text.setString("Score: " + std::to_string(score));
        text.setOutlineThickness(2.5);
        text.setCharacterSize(50);
        window.draw(text);
    }

    void write(sf::RenderWindow& window, std::string str, int x, int y, int size, sf::Color color) {
        text.setString(str);
        text.setOutlineThickness(2);
        text.setCharacterSize(size);
        text.setPosition(x,y);
        text.setFillColor(color);
        window.draw(text);
    }

    void changeColor(int score) {
        if (score == 0) text.setFillColor(sf::Color::White);
        else if (score > 0) text.setFillColor(sf::Color::Green);
        else text.setFillColor(sf::Color::Red);
    }

};

struct Player {
    int x;
    int y;
    int score;
    sf::Texture player_text;
    sf::Sprite player_spr;
    bool is_left;

    Player() : y {5}, x {5}, score {0} {
        player_text = loadTexture("./assets/runnerL.png");
        player_spr.setTexture(player_text);

        player_spr.setPosition(0, 0);
        setSize(player_spr, STEP, STEP);
        is_left = true;
    }

    void draw(sf::RenderWindow& window) {
        player_spr.setPosition(x * STEP, y * STEP);
        window.draw(this->player_spr);
    }

    bool spinPlayer(sf::Keyboard::Key key) {
        if (key == sf::Keyboard::Key::A && !is_left) {
            this->player_text = loadTexture("./assets/runnerL.png");
            this->player_spr.setTexture(player_text);
            is_left = true;
            return true;
        } else if (key == sf::Keyboard::Key::D && is_left) {
            this->player_text = loadTexture("./assets/runnerR.png");
            this->player_spr.setTexture(player_text);        
            is_left = false;
            return true;
        }

        return false;
    }

    void move(sf::Keyboard::Key key) {
        if (key == sf::Keyboard::A && x > 0) {
            if (!spinPlayer(key)) this->x--;  
        } else if (key == sf::Keyboard::W && y > 0) { 
            this->y--; 
        } else if (key == sf::Keyboard::D && x < (W_WINDOW / STEP) - 1) { 
           if (!spinPlayer(key)) this->x++;
        } else if (key == sf::Keyboard::S && y < (H_WINDOW / STEP) - 1) {
            this->y++;
        }
    }

    void checkScore(bool is_gold) {
        if (is_gold) this->score++;
        else this->score -= 2;
    }

};

struct Coin {
    int x {};
    int y {};
    sf::Texture coin_text;
    sf::Sprite coin_spr;
    bool is_gold;

    Coin(int x, int y) {
        int randColor {std::rand() % 2};

        if (randColor == 0) {
            coin_text = loadTexture("./assets/gold_coin.png");
            is_gold = true;
        } else {
            coin_text = loadTexture("./assets/red_coin.png");
            is_gold = false;
        }

        this->x = x;
        this->y = y;

        coin_spr.setTexture(coin_text);
        coin_spr.setPosition(x * STEP, y * STEP);
        setSize(coin_spr, STEP, STEP);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(coin_spr);
    }
};

struct Board {
    sf::Texture board_text;
    sf::Sprite board_spr;

    sf::RenderWindow& window;
    Player player;
    std::list<Coin> coins {};
    Pencil pencil;
    Speaker speaker;

    int num_coins {};
    int num_coins_max {(W_WINDOW/STEP) * (H_WINDOW/STEP) - 1};
    

    Board(sf::RenderWindow& window) : window {window} {
        board_text = loadTexture("./assets/background.png");
        board_spr.setTexture(board_text);
        board_spr.setPosition(0, 0);
        setSize(board_spr, W_WINDOW, H_WINDOW);

        int x = {std::rand() % (W_WINDOW/STEP)};
        int y = {std::rand() % (H_WINDOW/STEP)};

        coins.emplace_back(x,y);
        num_coins = 1;
    }

    bool onTop() {
        for (auto i = coins.begin(); i != coins.end(); i++) {
            if (player.x == i->x && player.y == i->y) {
                coins.erase(i);
                this->num_coins--;

                player.checkScore(i->is_gold);
                speaker.playCoin(i->is_gold);
                return true;
            }
        }
        return false;
    }

    bool exist(const std::list<Coin>& coins, int x, int y) {
        for (auto i = coins.begin(); i != coins.end(); i++) {
            if ((i->x == x && i->y == y) || (player.x == x && player.y == y)) return true;
        }   

        return false;
    }

    void addCoin() {
        if (onTop()) {
            for (int i = 1; i <= 2; i++) {
                if (this->num_coins < this->num_coins_max) {
                    int x = {std::rand() % (W_WINDOW/STEP)};
                    int y = {std::rand() % (H_WINDOW/STEP)};

                    if (exist(coins, x, y)) {
                        i--;
                    } else {
                        coins.emplace_back(x,y);
                        this->num_coins++;
                    }
                }
            }
        }
    }

    void draw() {
        addCoin();

        window.clear();

        window.draw(board_spr);
        player.draw(window);
        for (auto& coin : coins) {
            coin.draw(window);
        }

        pencil.changeColor(player.score);
        pencil.writeScore(window, player.score);

        window.display();
    }

};

struct Game {
    sf::RenderWindow window;
    Board board;
    std::function<void()> screen;
    bool you_win;

    Game() : window{sf::VideoMode(W_WINDOW, H_WINDOW), "Super Coin Rush"}, board {window} {
        screen = [&] {
            this->gameplay();
        };

        you_win = false;
    }

    void gameOver() {
        window.clear(sf::Color::Red);
        board.pencil.write(window, "YOU LOSE", 230, 300, 100, sf::Color::Black);
        board.speaker.playFinal(you_win);
        window.display();


        sf::sleep(sf::Time(sf::seconds(3)));
        board.speaker.playFinal(you_win);
        window.close();
    }

    void youWin() {
        window.clear(sf::Color::Green);
        board.pencil.write(window, "YOU WIN", 270, 300, 100, sf::Color::Black);
        window.display();

        board.speaker.playFinal(you_win);
        sf::sleep(sf::Time(sf::seconds(3)));
        window.close();
    }

    void gameplay() {
        board.draw();
    }

    void checkWin() {
        if (board.player.score <= -30 || board.num_coins == board.num_coins_max) {
            you_win = false;
            screen = [&] {
                this->gameOver();
            };
        }

        if (board.player.score >= 30) {
            you_win = true;
            screen = [&] {
                this->youWin();
            };
        }
    }

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                board.player.move(event.key.code);
            }
        } 
    }

    void mainLoop() {
        while(this->window.isOpen()) {
            processEvents();
            checkWin();
            screen();
        }
    }
};

int main() {
    std::srand(std::time(NULL));
    Game game;
    game.mainLoop();

    return 0;
}
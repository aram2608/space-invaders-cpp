#include "game/game.hpp"

#include "game.hpp"

#include <fstream>
#include <iostream>

// Constructor - Game
Game::Game() : keys{KEY_LEFT, KEY_RIGHT, KEY_SPACE} {
    // Game assets
    music = LoadMusicStream("audio/bgm_loud.ogg");
    explosion_sound = LoadSound("audio/explosion.ogg");
    game_over_sound = LoadSound("audio/game_over.ogg");
    ship_hit_sound = LoadSound("audio/ship_hit.ogg");
    aliens_sound = LoadSound("audio/alien_step.ogg");

    // Textures for UI
    ship_image = LoadTexture("assets/spaceship.png");
    font = LoadFontEx("font/monogram.ttf", 64, 0, 0);

    // Hard coded values for UI
    screen_center = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    grey = {29, 29, 27, 255};
    yellow = {243, 216, 63, 255};

    // Initialize starting screen/keybinds
    title();
    bind_inputs();
    bind_states();
}

// Destructor - Game
Game::~Game() {
    Alien::unload_images();
    UnloadMusicStream(music);
    UnloadSound(explosion_sound);
    UnloadSound(game_over_sound);
    UnloadSound(ship_hit_sound);
    UnloadSound(aliens_sound);
    UnloadTexture(ship_image);
    UnloadFont(font);
}

// Function to initalize the title screen
void Game::title() {
    // Starting game state
    state = GameState::Title;
    high_score = load_score_file();
}

// Method to bind our keys to the keymap
void Game::bind_inputs() {
    // We bind a lambda function that take a referecne to our ship and the delta time
    keymap[KEY_LEFT] = [](SpaceShip &ship, float delta) { ship.move_left(delta); };
    keymap[KEY_RIGHT] = [](SpaceShip &ship, float delta) { ship.move_right(delta); };
    keymap[KEY_SPACE] = [](SpaceShip &ship, float delta) { ship.fire_laser(); };
}

// Function to initialize game parameters
void Game::init() {
    // Player params
    lives = 3;
    score = 0;
    level = 1;
    // Assets/aliens
    obstacles = make_obs();
    aliens = create_fleet();
    alien_dir = 1;
    // Mystery Ship params
    last_al_laser_time = 0.0;
    lst_myst_spwn = 0.0;
    myst_ship_intv = GetRandomValue(10, 20);
}

// Function to reset game after game over
void Game::reset() {
    // We rest the ships position
    ship.reset();
    // We clear the vectors for all game objects
    aliens.clear();
    al_lasers.clear();
    obstacles.clear();
}

// Function to handle IO logic for game events
void Game::handle_input(float delta) {
    // We loop over the vector of keys
    for (auto key : keys) {
        // If one is press we dispatch the bound function
        if (IsKeyDown(key)) {
            dispatch(key, delta);
        }
    }
}

// Function to dispatch the bound methods
void Game::dispatch(int key, float delta) {
    // We do a quick check to see if the method is bound to the keymap
    // as an assurance
    if (auto it = keymap.find(key); it != keymap.end())
        it->second(ship, delta);
}

// Function to update the events on screen
void Game::update_simulation() {
    // We get the delta time
    float delta = GetFrameTime();
    // We handle keyboard inputs
    handle_input(delta);

    // We spawn the mystery ship
    spawn_mystery_ship();

    // Iterate over vector of lasers and update positions
    for (auto &laser : ship.lasers) {
        laser.update(delta);
    }

    // Alien movement and logic
    move_aliens(delta);
    aliens_shoot();

    // Update alien laser positions
    for (auto &laser : al_lasers) {
        laser.update(delta);
    }

    // Clean up lasers that fly off screen
    delete_laser();
    mystery_ship.update(delta);

    // Collision handling logic
    check_collisions();

    // Checks and advances level
    check_level();
}

// Method to bind the state tables at the start of the game
void Game::bind_states() {
    // We need to initialize all the state containers at once
    // Each lambda stores the underlying logic needed to run each state
    // We are not list initializing inside the array itself
    // since that was incredibly unreadable
    StateTable TITLE = {
        .enter = {[](Game &game) { /* nothing */ }},
        .update = {[](Game &game) {
            if (IsKeyPressed(KEY_ENTER)) {
                game.reset();
                game.init();
                game.set_state(GameState::Playing);
            }
        }},
    };
    StateTable PLAYING = {
        .enter = {[](Game &game) { PlayMusicStream(game.music); }},
        .update = {[](Game &game) {
            if (IsKeyPressed(KEY_P)) {
                game.set_state(GameState::Paused);
                return;
            }
            game.update_simulation();
            if (game.lives <= 0) {
                game.set_state(GameState::GameOver);
            }
        }},
    };
    StateTable PAUSE = {
        .enter = {[](Game &game) { PauseMusicStream(game.music); }},
        .update = {[](Game &game) {
            if (IsKeyPressed(KEY_ENTER)) {
                game.set_state(GameState::Playing);
            }
        }},
    };
    StateTable GAMEOVER = {
        .enter = {[](Game &game) {
            PauseMusicStream(game.music);
            PlaySound(game.game_over_sound);
        }},
        .update = {[](Game &game) {
            if (IsKeyPressed(KEY_ENTER)) {
                game.reset();
                game.init();
                game.set_state(GameState::Playing);
            } else if (IsKeyPressed(KEY_T)) {
                game.reset();
                game.set_state(GameState::Title);
            }
        }},
    };
    STATES = {TITLE, PLAYING, PAUSE, GAMEOVER};
}

// Method to set the set during run time
void Game::set_state(GameState next) {
    // If the current state matches what we want to move to we simply return
    // this is a littler sanity check but a bit redundant
    if (state == next) {
        return;
    }
    // We switch states
    state = next;
    // Now we can index the states array and pass a reference to the current
    // game class to run all the underlying logic used to enter a new state
    STATES[static_cast<size_t>(state)].enter(*this);
}

// Method to update the loop given the current state
void Game::update_loop() { STATES[static_cast<size_t>(state)].update(*this); }

// Function to draw events onto game window
void Game::draw() {
    ship.draw();
    mystery_ship.draw();

    // Iterate over vector of lasers and draw to screen
    for (auto &laser : ship.lasers) {
        laser.draw();
    }

    // Iterate over vector of obstacles and draw to screen
    for (auto &obs : obstacles) {
        obs.draw();
    }

    // Iterate over a vector of aliens and draw to screen
    for (auto &alien : aliens) {
        alien.draw();
    }

    // Iterate over a vector of alien lasers and draw to screen
    for (auto &laser : al_lasers) {
        laser.draw();
    }
}

// Main logic to draw to screen
void Game::draw_loop() {
    // I switched to a dispatch table since its much cleaner than a giant if/else

    // We first typdef or declare an alias for a pointer to a non static member
    // function in the game class that takes no parameters and returns a void
    // Seems a bit like magic and i dont fully understand it but it works pretty
    // well
    using DrawFn = void (Game::*)();

    // We then create an array of pointers to the methods we want to dispatch
    static constexpr DrawFn table[] = {&Game::draw_title,     // Title
                                       &Game::draw_playing,   // Playing
                                       &Game::draw_paused,    // Paused
                                       &Game::draw_gameover}; // Gameover
    // We can now cast the current state to its size in order to index our table
    // we then point at the index and dereference the function so we can call it
    (this->*table[static_cast<std::size_t>(state)])();
}

// Function to draw the title screen
void Game::draw_title() {
    // Hard coded UI components
    high_scr_title_size = MeasureTextEx(font, "HIGH SCORE", 34, 2);
    title_size = MeasureTextEx(font, "SPACE INVADERS", 80, 2);
    start_text_size = MeasureTextEx(font, "RETURN TO START GAME", 34, 2);

    // Draw UI Components
    ClearBackground(grey);
    DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);

    // Title screen text
    DrawTextEx(font, "SPACE INVADERS",
               {screen_center.x - title_size.x / 2, (screen_center.y - title_size.y / 2) - 50}, 80,
               2, yellow);
    DrawTextEx(
        font, "RETURN TO START GAME",
        {screen_center.x - start_text_size.x / 2, (screen_center.y - start_text_size.y / 2) + 20},
        34, 2, yellow);
    DrawTextEx(font, "HIGH SCORE",
               {screen_center.x - high_scr_title_size.x / 2,
                (screen_center.y - high_scr_title_size.y / 2) + 200},
               34, 2, yellow);
    // Formatting for high score loaded from file
    std::string high_scr_txt = format_trail_zeros(high_score, 5);
    Vector2 scr_txt_size = MeasureTextEx(font, high_scr_txt.c_str(), 34, 2);
    DrawTextEx(font, high_scr_txt.c_str(),
               {screen_center.x - scr_txt_size.x / 2, (screen_center.y - scr_txt_size.y / 2) + 230},
               34, 2, yellow);
}

// Function to draw the paused screen
void Game::draw_paused() {
    // Hard coded UI components
    paused_txt = MeasureTextEx(font, "PAUSED", 80, 2);
    start_text_size = MeasureTextEx(font, "RETURN TO START GAME", 34, 2);

    // Draw UI Components
    ClearBackground(grey);
    DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
    DrawLineEx({25, 730}, {775, 730}, 3, yellow);
    std::string level_num = format_level(level);
    std::string level_s = level_display + " " + level_num;
    DrawTextEx(font, level_s.c_str(), {565, 740}, 34, 2, yellow);

    // Paused title
    DrawTextEx(font, "PAUSED",
               {screen_center.x - paused_txt.x / 2, (screen_center.y - paused_txt.y / 2) - 50}, 80,
               2, yellow);
    DrawTextEx(
        font, "RETURN TO START GAME",
        {screen_center.x - start_text_size.x / 2, (screen_center.y - start_text_size.y / 2) + 20},
        34, 2, yellow);

    // Lives remaining
    float x = 50.0;
    for (int i = 0; i < lives; i++) {
        DrawTextureV(ship_image, {x, 745}, WHITE);
        x += 50;
    }

    // Scoreboard
    DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
    std::string score_txt = format_trail_zeros(score, 5);
    DrawTextEx(font, score_txt.c_str(), {50, 40}, 34, 2, yellow);

    DrawTextEx(font, "HIGH SCORE", {570, 15}, 34, 2, yellow);
    std::string high_scr_txt = format_trail_zeros(high_score, 5);
    DrawTextEx(font, high_scr_txt.c_str(), {655, 40}, 34, 2, yellow);
}

// Function to draw the game over screen
void Game::draw_gameover() {
    // Hard coded UI components
    game_over_title_size = MeasureTextEx(font, "GAME OVER", 80, 2);
    retry_text_size = MeasureTextEx(font, "RETURN TO TRY AGAIN", 34, 2);

    // Draw UI Components
    ClearBackground(grey);
    DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);

    // Game over screen text
    DrawTextEx(font, "GAME OVER",
               {screen_center.x - game_over_title_size.x / 2,
                (screen_center.y - game_over_title_size.y / 2) - 50},
               80, 2, yellow);
    DrawTextEx(
        font, "RETURN TO TRY AGAIN",
        {screen_center.x - retry_text_size.x / 2, (screen_center.y - retry_text_size.y / 2) + 20},
        34, 2, yellow);

    // Scoreboard
    DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
    std::string score_txt = format_trail_zeros(score, 5);
    DrawTextEx(font, score_txt.c_str(), {50, 40}, 34, 2, yellow);
}

// Function to draw the playing screen
void Game::draw_playing() {
    // Hard coded UI components
    level_display = "LEVEL";

    // Draw UI Components
    ClearBackground(grey);
    DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
    DrawLineEx({25, 730}, {775, 730}, 3, yellow);
    std::string level_num = format_level(level);
    std::string level_s = level_display + " " + level_num;
    DrawTextEx(font, level_s.c_str(), {565, 740}, 34, 2, yellow);

    // Lives remaining
    float x = 50.0;
    for (int i = 0; i < lives; i++) {
        DrawTextureV(ship_image, {x, 745}, WHITE);
        x += 50;
    }
    // Scoreboard
    DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
    std::string score_txt = format_trail_zeros(score, 5);
    DrawTextEx(font, score_txt.c_str(), {50, 40}, 34, 2, yellow);

    DrawTextEx(font, "HIGH SCORE", {570, 15}, 34, 2, yellow);
    std::string high_scr_txt = format_trail_zeros(high_score, 5);
    DrawTextEx(font, high_scr_txt.c_str(), {655, 40}, 34, 2, yellow);

    // Draw game assets
    draw();
}

// Function to delete lasers to protect memory resources
void Game::delete_laser() {
    // Iterator to loop through the vector and remove any inactive ship lasers
    for (auto it = ship.lasers.begin(); it != ship.lasers.end();) {
        if (!it->active) {
            it = ship.lasers.erase(it);
        } else {
            ++it;
        }
    }

    // Iterator to loop through the vector and remove any inactive alien lasers
    for (auto it = al_lasers.begin(); it != al_lasers.end();) {
        if (!it->active) {
            it = al_lasers.erase(it);
        } else {
            ++it;
        }
    }
}

// Function to return a vector of obstacles for the game window
std::vector<Obstacle> Game::make_obs() {
    // Declare our vector
    std::vector<Obstacle> out;

    // Calculate obstacle width and gaps between obstacles
    int obs_w = Obstacle::grid[0].size() * 3;
    float obs_gap = (GetScreenWidth() - (4 * obs_w)) / 5;

    // Iterate over the number of obstacles we want to make (4)
    for (int i = 0; i < 4; i++) {
        float off_x = (i + 1) * obs_gap + i * obs_w;
        // Appends a new element to the end of the container by constructing it in-place
        // Apparently more efficient than pushback
        out.emplace_back(Vector2{off_x, float(GetScreenHeight() - 200)});
    }
    return out;
}

// Function to handle mystery ship spawning logic
void Game::spawn_mystery_ship() {
    // Logic to handling spawn time of mystery ship
    double curr_t = GetTime();
    if (curr_t - lst_myst_spwn > myst_ship_intv) {
        mystery_ship.spawn();
        lst_myst_spwn = GetTime();
        myst_ship_intv = GetRandomValue(10, 20);
    }
}

// Function to create a vector of aliens to spawn a fleet into game window
std::vector<Alien> Game::create_fleet() {
    std::vector<Alien> out;
    // Iterate over a 5 row x 11 column grid to create a fleet of 55 aliens
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 11; column++) {

            // Calculates alien type from row number
            int alien_t;
            if (row == 0) {
                alien_t = 3;
            } else if (row == 1 || row == 2) {
                alien_t = 2;
            } else {
                alien_t = 1;
            }

            // Calculate x and y by an arbitrary cell_size of 55
            float x = 75 + column * 55;
            float y = 100 + row * 55;
            // Construct Alien in place and add to vector
            out.emplace_back(alien_t, Vector2{x, y});
        }
    }
    return out;
}

// Function to shift fleet position on game window
void Game::move_aliens(float delta) {
    // Calculate screen position to make sure the aliens stay on screen
    // Move aliens down once the edge of screen is met
    for (auto &alien : aliens) {
        // Right side of screen
        if (alien.position.x + alien.alien_images[alien.type - 1].width > GetScreenWidth() - 25) {
            alien_dir = -1 * 100.0f * delta;
            aliens_down(4);
            PlaySound(aliens_sound);
        }
        // Left side of screen
        if (alien.position.x < 25) {
            alien_dir = 1 * 100.0f * delta;
            aliens_down(4);
            PlaySound(aliens_sound);
        }
        // Update movement
        alien.update(alien_dir);
    }
}

// Function to move entire fleet of aliens down the y direction
void Game::aliens_down(int distance) {
    // Iterate over vector of aliens and update y_coord for each alien
    for (auto &alien : aliens) {
        alien.position.y += distance;
    }
}

// Function handle firing logic for alien fleet
void Game::aliens_shoot() {
    // Get time and if current time is greq to interval and aliens are on screen fire
    double curr_time = GetTime();
    if (curr_time - last_al_laser_time >= al_shot_intv && !aliens.empty()) {

        // Pick a random alien and have it fire a laser
        int rand_idx = GetRandomValue(0, aliens.size() - 1);
        Alien &alien = aliens[rand_idx];

        // Vector {x_coord, y_coord} calculations with a laser speed of 300.0f
        al_lasers.emplace_back(
            Vector2{alien.position.x + alien.alien_images[alien.type - 1].width / 2,
                    alien.position.y + alien.alien_images[alien.type - 1].height},
            300.0f);

        // Update last fire time given completion of previous code
        last_al_laser_time = GetTime();
    }
}

// Function to handle collisions
void Game::check_collisions() {
    // Spaceship Lasers
    for (auto &laser : ship.lasers) {
        // Iterate over aliens in alien vector and check for collisions
        auto it = aliens.begin();
        while (it != aliens.end()) {
            if (CheckCollisionRecs(it->get_rect(), laser.get_rect())) {
                PlaySound(explosion_sound);
                // Scoring for alien types
                if (it->type == 1) {
                    score += 100;
                } else if (it->type == 2) {
                    score += 200;
                } else if (it->type == 3) {
                    score += 300;
                }
                score_check();
                it = aliens.erase(it);
                laser.active = false;
            } else {
                ++it;
            }
        }
        // Iterate over obstacles vector to check for collisions
        for (auto &obs : obstacles) {
            auto it = obs.blocks.begin();
            while (it != obs.blocks.end()) {
                if (CheckCollisionRecs(it->get_rect(), laser.get_rect())) {
                    it = obs.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }
        // Check laser/mystery ship collisions
        if (CheckCollisionRecs(laser.get_rect(), mystery_ship.get_rect())) {
            PlaySound(explosion_sound);
            laser.active = false;
            mystery_ship.alive = false;
            score += 500;
            score_check();
        }
    }
    // Alien lasers
    for (auto &laser : al_lasers) {
        // Check for ship/laser collisions
        if (CheckCollisionRecs(laser.get_rect(), ship.get_rect())) {
            laser.active = false;
            PlaySound(ship_hit_sound);
            --lives;
        }
        // Iterate over obstacles vector to check for collisions
        for (auto &obs : obstacles) {
            auto it = obs.blocks.begin();
            while (it != obs.blocks.end()) {
                if (CheckCollisionRecs(it->get_rect(), laser.get_rect())) {
                    it = obs.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }
    }
    // Alien collisions
    for (auto &alien : aliens) {
        // Alien/obstacle collisions
        for (auto &obs : obstacles) {
            auto it = obs.blocks.begin();
            while (it != obs.blocks.end()) {
                if (CheckCollisionRecs(it->get_rect(), alien.get_rect())) {
                    it = obs.blocks.erase(it);
                } else {
                    it++;
                }
            }
        }
        // Alien/ship collision
        if (CheckCollisionRecs(alien.get_rect(), ship.get_rect())) {
            PlaySound(ship_hit_sound);
            --lives;
            ship.reset();
        }
    }
    // Obstacle/ship collision
    for (auto &obs : obstacles) {
        auto it = obs.blocks.begin();
        while (it != obs.blocks.end()) {
            if (CheckCollisionRecs(it->get_rect(), ship.get_rect())) {
                it = obs.blocks.erase(it);
                PlaySound(ship_hit_sound);
                --lives;
                ship.reset();
            } else {
                it++;
            }
        }
    }
}

// Function to update high score
void Game::score_check() {
    if (score > high_score) {
        high_score = score;
        save_high_scr(high_score);
    }
}

// Function to save high score to a text file
void Game::save_high_scr(int high_scr) {
    std::ofstream high_scr_file("score/highscore.txt");
    if (high_scr_file.is_open()) {
        high_scr_file << high_scr;
        high_scr_file.close();
    } else {
        std::cerr << "Failed to save highscore to file" << std::endl;
    }
}

// Function to load a high score at start of game from text file
int Game::load_score_file() {
    int loaded_high_scr = 0;
    std::ifstream high_scr_file("score/highscore.txt");
    if (high_scr_file.is_open()) {
        high_scr_file >> loaded_high_scr;
    } else {
        std::cerr << "Failed to load highscore from file" << std::endl;
    }
    return loaded_high_scr;
}

// Function to progress to new level
// check in the update function
void Game::check_level() {
    // We check if the vector is empty
    if (aliens.empty()) {
        ++level;
        aliens = create_fleet();
    }
}

// Function to format the scores
std::string Game::format_trail_zeros(int number, int width) {
    std::string num_text = std::to_string(number);
    int trailing_zeros = width - num_text.length();
    return num_text = std::string(trailing_zeros, '0') + num_text;
}

// Function to reformat level displayed on UI
std::string Game::format_level(int number) {
    if (number < 10) {
        std::string num_text = std::to_string(number);
        return num_text = '0' + num_text;
    } else {
        std::string num_text = std::to_string(number);
        return num_text;
    }
}
#pragma once

#include "sdl_includes.h"
#include <string>
#include <vector>
#include <map>
#include "Resources.h"
#include "ClientConnection.h"

using namespace std;

class SDLGame {
public:
	const static int _MAX_PLAYERS_ = 10;

	SDLGame(std::string windowTitle_, int width, int height);
	virtual ~SDLGame();

	SDL_Window* getWindow() const; // returns a pointer to the SDL window
	SDL_Renderer* getRenderer() const; // returns a pointer to the SDL renderer
	int getWindowWidth() const; // returns the window width
	int getWindowHeight() const; // returns the window height
	const Resources* getResources() const; // returns a pointer to the resources

	// for SDLNet games
	Uint8 getClientId() const;
	bool isMasterClient() const;
	ClientConnection& getConnection();

	// some general properties mechanism, simply implemented with a map
	void   setProp(string key, string value);
	string getProp(string key);

	// abstract methods to be implemented by subclasses
	virtual void start() = 0; // start the game
	virtual void stop() = 0;  // stop the game

private:
	void initSDL(); // initialize SDL (ttf, mixer, image, create window and renderer, etc)
	void closeSDL(); // close all SDL resources
	void initResources(); // initialize the SDLResources object with the data at the top of this file
	void closeResources(); // close the  SDLResources object (frees all memory)

protected:
	SDL_Window* window_; // the window
	SDL_Renderer* renderer_;  // the renderer
	Resources* resources_; // resource (textures, font, music, etc)

	std::string windowTitle_; // window title
	int width_; // window width
	int height_; // window height
	Uint8 client_id;
	ClientConnection conn_;

	map<string,string> properties_;
};


#include "Game.h"
#include "Forest.h"

Game::Game(CL_DisplayWindow& window) : window(window), quit(false), pause(false)
{
	// Eventhandler anlegen
	slotQuit = window.sig_window_close().connect(this, &Game::onWindowClose);
	slotKeyDown = window.get_ic().get_keyboard().sig_key_down().connect(this, &Game::onKeyDown);

	components.push_back(new Forest(*this, 256, 0.0000001f, 0.01f));
}


// main loop
void Game::run()
{
	// Spielkomponenten initialisieren
	init();

	while (!quit)
	{
		// Spielkomponenten aktualisieren
		update();

		// Spielkomponenten zeichnen
		draw();

		window.flip(1);
		CL_KeepAlive::process();
	}
}


// Initialisieren der Spielkomponenten
void Game::init()
{	
	for (std::list<GameComponent*>::iterator it = components.begin(); it != components.end(); ++it)
		(*it)->init();
}


// Updaten der Spielkomponenten
void Game::update()
{	
	float elapsed = getElapsedTime();

	if (pause)
		return;

	for (std::list<GameComponent*>::iterator it = components.begin(); it != components.end(); ++it)
		(*it)->update(elapsed);
}


// Zeichnen der Spielkomponenten
void Game::draw()
{
	float elapsed = getElapsedTime();

	CL_Draw::fill(window.get_gc(), window.get_viewport(), CL_Colorf::black);

	for(std::list<GameComponent*>::iterator it = components.begin(); it != components.end(); ++it)
		(*it)->draw(elapsed);
}


// Event für Beenden des Windows
void Game::onWindowClose()
{
	quit = true;
}


// Event für Tastendruck
void Game::onKeyDown(const CL_InputEvent &key, const CL_InputState &state)
{
	switch (key.id)
	{
		case CL_KEY_ESCAPE: quit = true; break;
		case CL_KEY_SPACE: pause = !pause; break;
	}
}


// liefert das aktuelle DisplayWindow
CL_DisplayWindow& Game::getDisplayWindow() const
{
	return window;
}


// liefert die vergangene Zeit seit dem letzten Aufruf
float Game::getElapsedTime() const
{
	static unsigned int lastTime = 0;

	unsigned int newTime = CL_System::get_time();

	if (lastTime == 0)
		lastTime = newTime;

	int deltaTime = newTime - lastTime;

	lastTime = newTime;

	return deltaTime * 0.001f;
}
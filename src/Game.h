#pragma once

#include "EventManager.h"
#include "FadeInOut.h"
#include "Game/Level.h"
#include "LoadingScreen.h"
#include <memory>
#include "Menu.h"
#include "Parser/ParseVariable.h"
#include "Queryable.h"
#include "ResourceManager.h"
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Variable.h"
#include <vector>

class Game : public sf::NonCopyable, public Queryable
{
private:
	sf::RenderWindow window;
	sf::RenderTexture windowTex;
	sf::Sprite windowSprite;

	sf::Vector2u refSize;
	sf::Vector2u minSize;
	sf::Vector2u oldSize;
	sf::Vector2u size;
	sf::Vector2u windowTexSize;
	unsigned framerate{ 0 };
	bool smoothScreen{ false };
	bool stretchToFit{ false };
	bool keepAR{ true };
	bool enableInput{ true };
	bool pauseOnFocusLoss{ false };
	bool paused{ false };

	sf::Vector2i mousePositioni;
	sf::Vector2f mousePositionf;

	sf::Event::MouseButtonEvent mousePressEvt;
	sf::Event::MouseButtonEvent mouseReleaseEvt;
	sf::Event::MouseMoveEvent mouseMoveEvt;
	sf::Event::MouseWheelScrollEvent mouseScrollEvt;
	sf::Event::KeyEvent keyPressEvt;
	sf::Event::TextEvent textEnteredEvt;
	sf::Event::TouchEvent touchBeganEvt;
	sf::Event::TouchEvent touchMovedEvt;
	sf::Event::TouchEvent touchEndedEvt;
	bool mousePressed{ false };
	bool mouseReleased{ false };
	bool mouseMoved{ false };
	bool mouseScrolled{ false };
	bool keyPressed{ false };
	bool textEntered{ false };
	bool touchBegan{ false };
	bool touchMoved{ false };
	bool touchEnded{ false };

	unsigned musicVolume{ 100 };
	unsigned soundVolume{ 100 };

	sf::Time elapsedTime;

	std::string path;
	std::string title;
	std::string version;

	ResourceManager resourceManager;
	EventManager eventManager;

	std::map<std::string, Variable> variables;

	std::unique_ptr<LoadingScreen> loadingScreen;
	std::unique_ptr<FadeInOut> fadeInOut;

	void processEvents();
	void onClosed();
	void onResized(const sf::Event::SizeEvent& evt);
	void onLostFocus();
	void onGainedFocus();

	void onTextEntered(const sf::Event::TextEvent& evt);
	void onKeyPressed(const sf::Event::KeyEvent& evt);
	void onMouseWheelScrolled(const sf::Event::MouseWheelScrollEvent& evt);
	void onMouseButtonPressed(const sf::Event::MouseButtonEvent& evt);
	void onMouseButtonReleased(const sf::Event::MouseButtonEvent& evt);
	void onMouseMoved(const sf::Event::MouseMoveEvent& evt);
	void onTouchBegan(const sf::Event::TouchEvent& evt);
	void onTouchMoved(const sf::Event::TouchEvent& evt);
	void onTouchEnded(const sf::Event::TouchEvent& evt);

	void updateMouse(const sf::Vector2i mousePos);
	void updateEvents();
	void drawCursor();
	void drawAndUpdate();
	void drawFadeEffect();
	void drawWindow();

	void updateSize();
	void updateWindowTex();

	std::map<std::string, Variable>::const_iterator findVariable(const std::string& key) const;

public:
	Game() : refSize(640, 480), minSize(640, 480), size(640, 480) {}
	~Game();

	void init();

	const sf::Vector2u& OldWindowSize() const { return oldSize; }
	const sf::Vector2u& WindowSize() const { return size; }
	const sf::Vector2u& WindowTexSize() const { return windowTexSize; }
	sf::Vector2f WindowTexSizef() const
	{
		return sf::Vector2f((float)windowTexSize.x, (float)windowTexSize.y);
	}
	void WindowSize(const sf::Vector2u& size_)
	{
		if (size_.x >= minSize.x && size_.y >= minSize.y)
		{
			if (window.isOpen() == true)
			{
				window.setSize(size_);
			}
			else
			{
				size = size_;
			}
		}
	}
	const sf::Vector2u& RefSize() const { return refSize; }
	void RefSize(const sf::Vector2u& size_)
	{
		if (window.isOpen() == false &&
			size_.x > minSize.x &&
			size_.y > minSize.y)
		{
			refSize = size_;
		}
	}
	const sf::Vector2u& MinSize() const { return minSize; }
	void MinSize(const sf::Vector2u& size_)
	{
		if (window.isOpen() == true)
		{
			return;
		}
		minSize = size_;
		if (size.x < minSize.x && size.y < minSize.y)
		{
			size = minSize;
		}
	}
	unsigned Framerate() const { return framerate; }
	bool SmoothScreen() const { return smoothScreen; }
	bool StretchToFit() const { return stretchToFit; }
	bool KeepAR() const { return keepAR; }

	const sf::Vector2i& MousePositioni() const { return mousePositioni; }
	const sf::Vector2f& MousePositionf() const { return mousePositionf; }

	const sf::Event::MouseButtonEvent& MousePress() { return mousePressEvt; }
	const sf::Event::MouseButtonEvent& MouseRelease() { return mouseReleaseEvt; }
	const sf::Event::MouseMoveEvent& MouseMove() { return mouseMoveEvt; }
	const sf::Event::MouseWheelScrollEvent& MouseScroll() { return mouseScrollEvt; }
	const sf::Event::KeyEvent& KeyPress() { return keyPressEvt; }
	const sf::Event::TextEvent& TextEntered() { return textEnteredEvt; }
	const sf::Event::TouchEvent& TouchBegan() { return touchBeganEvt; }
	const sf::Event::TouchEvent& TouchMoved() { return touchMovedEvt; }
	const sf::Event::TouchEvent& TouchEnded() { return touchEndedEvt; }

	bool wasMousePressed() { return mousePressed; }
	bool wasMouseReleased() { return mouseReleased; }
	bool wasMouseMoved() { return mouseMoved; }
	bool wasMouseScrolled() { return mouseScrolled; }
	bool wasKeyPressed() { return keyPressed; }
	bool wasTextEntered() { return textEntered; }
	bool hasTouchBegan() { return touchBegan; }
	bool hasTouchMoved() { return touchMoved; }
	bool hasTouchEnded() { return touchEnded; }

	void clearMousePressed() { mousePressed = false; }
	void clearMouseReleased() { mouseReleased = false; }
	void clearMouseMoved() { mouseMoved = false; }
	void clearMouseScrolled() { mouseScrolled = false; }
	void clearKeyPressed() { keyPressed = false; }
	void clearTextEntered() { textEntered = false; }
	void clearTouchBegan() { touchBegan = false; }
	void clearTouchMoved() { touchMoved = false; }
	void clearTouchEnded() { touchEnded = false; }

	void clearInputEvents()
	{
		mousePressed = false;
		mouseReleased = false;
		mouseMoved = false;
		mouseScrolled = false;
		keyPressed = false;
		textEntered = false;
		touchBegan = false;
		touchMoved = false;
		touchEnded = false;
	}

	void MinWidth(unsigned width_) { size.x = width_; }
	void MinHeight(unsigned height_) { size.y = height_; }
	void Framerate(unsigned framerate_)
	{
		if (framerate_ > 0)
		{
			framerate = std::min(std::max(framerate_, 30u), 60u);
		}
		else
		{
			framerate = 0;
		}
		if (window.isOpen() == true)
		{
			window.setFramerateLimit(framerate);
		}
	}
	void SmoothScreen(bool smooth_);
	void StretchToFit(bool stretchToFit_);
	void KeepAR(bool keepAR_);
	void PauseOnFocusLoss(bool pause_) { pauseOnFocusLoss = pause_; }

	unsigned MusicVolume() const { return musicVolume; }
	void MusicVolume(unsigned volume)
	{
		musicVolume <= 100 ? musicVolume = volume : musicVolume = 100;
	}
	unsigned SoundVolume() const { return soundVolume; }
	void SoundVolume(unsigned volume)
	{
		soundVolume <= 100 ? soundVolume = volume : soundVolume = 100;
	}

	void addPlayingSound(const sf::SoundBuffer& obj);
	void addPlayingSound(const sf::SoundBuffer* obj);

	const sf::Time& getElapsedTime() const { return elapsedTime; }

	const std::string& getPath() const { return path; }
	const std::string& getTitle() const { return title; }
	const std::string& getVersion() const { return version; }

	bool isInputEnabled() { return enableInput; }
	void EnableInput(bool enable) { enableInput = enable; }

	sf::RenderWindow& Window() { return window; }
	const sf::RenderWindow& Window() const { return window; }

	const sf::RenderTexture& WindowTex() const { return windowTex; }

	ResourceManager& Resources() { return resourceManager; }
	const ResourceManager& Resources() const { return resourceManager; }
	EventManager& Events() { return eventManager; }

	void setPath(const std::string& path_) { path = path_; }
	void setTitle(const std::string& title_)
	{
		title = title_;
		if (window.isOpen() == true)
		{
			window.setTitle(title);
		}
	}
	void setVersion(const std::string& version_) { version = version_; }

	LoadingScreen* getLoadingScreen() { return loadingScreen.get(); }
	void setLoadingScreen(std::unique_ptr<LoadingScreen> loadingScreen_) { loadingScreen = std::move(loadingScreen_); }

	bool drawLoadingScreen();

	FadeInOut* getFadeInOut() const { return fadeInOut.get(); }
	void setFadeInOut(std::unique_ptr<FadeInOut> fadeInOut_) { fadeInOut = std::move(fadeInOut_); }

	void updateMouse();
	void updateCursorPosition();

	void play();

	const std::map<std::string, Variable>& getVariables() { return variables; }

	bool getVariableNoPercentage(const std::string& key, Variable& var) const;
	bool getVariable(const std::string& key, Variable& var) const;

	template <class T, class U>
	U getVarOrProp(const Variable& var, U defVal = U())
	{
		if (var.is<T>() == true)
		{
			return (U)var.get<T>();
		}
		else if (var.is<std::string>() == true)
		{
			Variable var2;
			if (getVarOrProp(var.get<std::string>(), var2) == true)
			{
				if (var2.is<T>() == true)
				{
					return (U)var2.get<T>();
				}
			}
		}
		return defVal;
	}

	bool getVarOrProp(const std::string& key, Variable& var) const;
	Variable getVarOrProp(const Variable& var) const;
	bool getVarOrPropBool(const std::string& key) const;
	bool getVarOrPropBool(const Variable& var) const;
	double getVarOrPropDouble(const std::string& key) const;
	double getVarOrPropDouble(const Variable& var) const;
	int64_t getVarOrPropLong(const std::string& key) const;
	int64_t getVarOrPropLong(const Variable& var) const;
	std::string getVarOrPropString(const std::string& key) const;
	std::string getVarOrPropString(const Variable& var) const;

	void clearVariable(const std::string& key);

	void setVariable(const std::string& key, const Variable& value);

	void saveVariables(const std::string& filePath, const std::vector<std::string>& varNames) const;

	virtual bool getProperty(const std::string& prop, Variable& var) const;
	void setProperty(const std::string& prop, const Variable& val);

	virtual const Queryable* getQueryable(const std::string& prop) const;
};

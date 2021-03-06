#include "Text2.h"
#include "Game.h"
#include "GameUtils.h"
#include "TextUtils.h"
#include "Utils.h"

std::shared_ptr<Action> Text2::getAction(uint16_t nameHash16)
{
	switch (nameHash16)
	{
	case str2int16("change"):
		return changeAction;
	default:
		return nullptr;
	}
}

void Text2::setAction(uint16_t nameHash16, const std::shared_ptr<Action>& action)
{
	switch (nameHash16)
	{
	case str2int16("change"):
		changeAction = action;
		return;
	}
}

void Text2::setBinding(const std::string& binding)
{
	bindings.clear();
	bindings.push_back(binding);
}

void Text2::setBinding(const std::vector<std::string>& bindings_)
{
	bindings = bindings_;
}

void Text2::update(Game& game)
{
	if (text->Visible() == false)
	{
		return;
	}
	if (bindings.size() > 0)
	{
		triggerOnChange = text->setText(TextUtils::getFormatString(game, format, bindings));
	}
	if (triggerOnChange == true)
	{
		triggerOnChange = false;
		if (changeAction != nullptr)
		{
			changeAction->execute(game);
		}
	}
}

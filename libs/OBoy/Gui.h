#pragma once

/*#include "GuiEvent.h"
#include "GuiEventArgs.h"*/
#include <string>

namespace oboy
{
  //class GuiWindow;

	class Gui
	{
	public:

		Gui();
		virtual ~Gui();

    /*virtual void setEnabled(bool enabled);
		virtual bool isEnabled();

		virtual void setConnected(bool connected);
		virtual bool isConnected();*/

    virtual void injectTimePulse(float dt) = 0;
    virtual void setResourceGroupDirectory(const std::string& resourceGroup, const std::string& directory) = 0;

    virtual void setDefaultImagesetResourceGroup(const std::string& resourceGroup) = 0;
    virtual void setDefaultFontResourceGroup(const std::string& resourceGroup) = 0;
    virtual void setDefaultSchemeResourceGroup(const std::string& resourceGroup) = 0;
    virtual void setDefaultWidgetLookManagerResourceGroup(const std::string& resourceGroup) = 0;
    virtual void setDefaultWindowManagerResourceGroup(const std::string& resourceGroup) = 0;

    virtual void setDefaultFont(const std::string& fontName) = 0;
    virtual void setDefaultMouseCursor(const std::string& imageset, const std::string& imageName) = 0;

    virtual void loadSkin(const std::string& fileName) = 0;
    virtual void loadFont(const std::string& fontName, const float pointSize, const bool antiAliased, const std::string& fontFileName) = 0;

    virtual void draw() = 0;

    /*virtual void destroyAllWindows() = 0;
    virtual GuiWindow* createWindow(const std::string& name) = 0;
    virtual GuiWindow* loadWindowLayout(const std::string& fileName) = 0;
    virtual GuiWindow* getWindow(const std::string& name) = 0;
    virtual void setGUISheet(GuiWindow* window) = 0;*/

	/*private:

		bool mIsEnabled;
		bool mIsConnected;*/

	};
}


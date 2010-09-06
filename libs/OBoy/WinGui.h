#pragma once

#include "Gui.h"

namespace OBoy
{
	class WinGui : public Gui
	{
	public:

		WinGui();
		virtual ~WinGui();

    virtual void injectTimePulse(float dt);
    virtual void setResourceGroupDirectory(const std::string& resourceGroup, const std::string& directory);

    virtual void setDefaultImagesetResourceGroup(const std::string& resourceGroup);
    virtual void setDefaultFontResourceGroup(const std::string& resourceGroup);
    virtual void setDefaultSchemeResourceGroup(const std::string& resourceGroup);
    virtual void setDefaultWidgetLookManagerResourceGroup(const std::string& resourceGroup);
    virtual void setDefaultWindowManagerResourceGroup(const std::string& resourceGroup);

    virtual void setDefaultFont(const std::string& fontName);
    virtual void setDefaultMouseCursor(const std::string& imageset, const std::string& imageName);

    virtual void loadSkin(const std::string& fileName);
    virtual void loadFont(const std::string& fontName, const float pointSize, const bool antiAliased, const std::string& fontFileName);

    virtual void draw();

    /*virtual void destroyAllWindows();
    
    virtual GuiWindow* createWindow(const std::string& name);
    virtual GuiWindow* loadWindowLayout(const std::string& fileName);
    virtual GuiWindow* getWindow(const std::string& name);
    virtual void setGUISheet(GuiWindow* window);*/
	};
}

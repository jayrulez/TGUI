/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2015 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Loading/Theme.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/EditBox.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::map<std::string, std::function<Widget::Ptr()>> BaseTheme::m_constructors =
        {
            {toLower("Button"), std::make_shared<Button>},
            {toLower("EditBox"), std::make_shared<EditBox>}
        };

    std::shared_ptr<BaseThemeLoader> BaseTheme::m_themeLoader = std::make_shared<DefaultThemeLoader>();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BaseTheme::widgetAttached(Widget* widget)
    {
        widget->attachTheme(shared_from_this());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BaseTheme::widgetDetached(Widget*)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BaseTheme::setConstructFunction(const std::string& type, const std::function<Widget::Ptr()>& constructor)
    {
        m_constructors[toLower(type)] = constructor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BaseTheme::setThemeLoader(const std::shared_ptr<BaseThemeLoader>& themeLoader)
    {
        m_themeLoader = themeLoader;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BaseTheme::widgetReload(Widget* widget, const std::string& primary, const std::string& secondary, bool force)
    {
        widget->reload(primary, secondary, force);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Theme::Theme(const std::string& filename) :
        m_filename(filename)
    {
        std::string::size_type slashPos = m_filename.find_last_of("/\\");
        if (slashPos != std::string::npos)
            m_resourcePath = m_filename.substr(0, slashPos+1);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<Theme> Theme::create(const std::string& filename)
    {
        return std::make_shared<Theme>(filename);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    WidgetConverter Theme::load(std::string className)
    {
        className = toLower(className);

        std::string widgetType;
        if (m_filename != "")
        {
            if (m_widgetTypes.find(className) != m_widgetTypes.end())
                widgetType = m_widgetTypes[className];
            else
                widgetType = toLower(m_themeLoader->load(m_filename, className, m_widgetProperties[className]));
        }
        else // Load the white theme
        {
            widgetType = className;
        }

        auto constructor = m_constructors[widgetType];
        if (constructor)
        {
            Widget::Ptr widget = constructor();
            m_widgets[widget.get()] = className;
            m_widgetTypes[className] = widgetType;

            widgetAttached(widget.get());
            widgetReload(widget.get(), m_filename, className, true);

            return WidgetConverter{widget};
        }
        else
            throw Exception{"Failed to load widget of type '" + widgetType + "'. No constructor function was set for that type."};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Theme::reload(const std::string& filename)
    {
        m_filename = filename;

        m_resourcePath = "";
        std::string::size_type slashPos = m_filename.find_last_of("/\\");
        if (slashPos != std::string::npos)
            m_resourcePath = m_filename.substr(0, slashPos+1);

        m_widgetTypes.clear();
        m_widgetProperties.clear();

        for (auto& widget : m_widgets)
        {
            if (m_filename != "")
            {
                if (m_widgetTypes.find(widget.second) == m_widgetTypes.end())
                {
                    std::string widgetType = toLower(m_themeLoader->load(m_filename, widget.second, m_widgetProperties[widget.second]));
                }
            }

            widgetReload(widget.first, filename, widget.second);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Theme::reload(std::string oldClassName, std::string newClassName)
    {
        oldClassName = toLower(oldClassName);
        newClassName = toLower(newClassName);

        // If we don't have the new class name in the cache then check if the theme loader has it
        if (m_filename != "")
        {
            if (m_widgetTypes.find(newClassName) == m_widgetTypes.end())
                m_themeLoader->load(m_filename, newClassName, m_widgetProperties[newClassName]);
        }

        // Reload all the widget that match the old class name
        for (auto& widget : m_widgets)
        {
            if (widget.second == oldClassName)
            {
                widget.second = newClassName;
                widgetReload(widget.first, m_filename, newClassName);
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Theme::reload(Widget::Ptr widget, std::string className)
    {
        className = toLower(className);

        // If we don't have the class name in the cache then check if the theme loader has it
        std::string widgetType;
        if (m_filename != "")
        {
            if (m_widgetTypes.find(className) != m_widgetTypes.end())
                widgetType = m_widgetTypes[className];
            else
                widgetType = toLower(m_themeLoader->load(m_filename, className, m_widgetProperties[className]));
        }
        else // Load the white theme
        {
            widgetType = className;
            if (!m_constructors[widgetType])
                throw Exception{"Failed to reload widget of type '" + widgetType + "'. No constructor function was set for that type."};
        }

        widgetAttached(widget.get());
        widgetReload(widget.get(), m_filename, className);
        m_widgets[widget.get()] = className;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Theme::widgetDetached(Widget* widget)
    {
        auto it = m_widgets.find(widget);
        if (it != m_widgets.end())
            m_widgets.erase(it);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Theme::initWidget(Widget* widget, std::string filename, std::string className)
    {
        if (filename != m_filename)
            throw Exception{"Theme tried to init widget which gave a wrong filename."};

        // Temporarily change the resource path to load relative from the theme file
        std::string oldResourcePath = getResourcePath();
        setResourcePath(oldResourcePath + m_resourcePath);

        try
        {
            for (auto& property : m_widgetProperties[className])
                widget->getRenderer()->setProperty(property.first, property.second);
        }
        catch (Exception& e)
        {
            // Restore the resource path before throwing
            setResourcePath(oldResourcePath);
            throw e;
        }

        // Restore the resource path
        setResourcePath(oldResourcePath);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
    void Theme::setLoader(const std::string& type, const LoaderFuncType& loader)
    {
        m_loaders[toLower(type)] = loader;
    }
*/
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
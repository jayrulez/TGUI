/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2014 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_TAB_HPP
#define TGUI_TAB_HPP


#include <TGUI/Widget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API Tab : public Widget
    {
    public:

        typedef std::shared_ptr<Tab> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Tab();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Tab() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the tab
        ///
        /// @param configFileFilename  Filename of the config file.
        ///
        /// @throw Exception when the config file couldn't be opened.
        /// @throw Exception when the config file didn't contain a "Tab" section with the needed information.
        /// @throw Exception when one of the images, described in the config file, couldn't be loaded.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Tab::Ptr create(const std::string& configFileFilename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another tab
        ///
        /// @param tab  The other tab
        ///
        /// @return The new tab
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Tab::Ptr copy(const Tab::Ptr& tab)
        {
            return std::make_shared<Tab>(*tab);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the filename of the config file that was used to load the widget.
        ///
        /// @return Filename of loaded config file.
        ///         Empty string when no config file was loaded yet.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::string& getLoadedConfigFile() const
        {
            return m_loadedConfigFile;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the position of the widget
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// @param position  New position
        ///
        /// @see move, getPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPosition(const Layout& position) override;
        using Transformable::setPosition;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function currently does nothing.
        ///
        /// @param size  Currently ignored
        ///
        /// It is not yet possible to change the size directly.
        ///
        /// @see setTabHeight
        /// @see setDistanceToSide
        /// @see setMaximumTabWidth
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(const Layout& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the size of the tabs.
        ///
        /// @return Size of the tabs
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getSize() const override
        {
            return {m_width, m_textureNormal.getSize().y};
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new tab.
        ///
        /// @param name    The name of the tab (this is the text that will be drawn on top of the tab).
        /// @param select  Do you want the new tab to be selected immediately?
        ///
        /// @return  The index of the tab in the list.
        ///
        /// @warning The index returned by this function may no longer be correct when a tab is removed.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int add(const sf::String& name, bool select = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Selects the tab with a given name.
        ///
        /// @param name  The name of the tab to select.
        ///
        /// When the name doen't match any tab then nothing will be changed.
        /// If there are multiple tabs with the same name then the first one will be selected.
        ///
        /// @see select(int)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void select(const sf::String& name);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Selects the tab with a given index.
        ///
        /// @param index  The index of the tab to select.
        ///
        /// When the index is too high then nothing will happen.
        ///
        /// @see select(sf::String)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void select(unsigned int index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Deselects the selected tab.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deselect();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a tab with a given name.
        ///
        /// @param name  The name of the tab to remove.
        ///
        /// When multiple tabs have the same name, only the first will be removed.
        ///
        /// @see remove(unsigned int)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void remove(const sf::String& name);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a tab with a given index.
        ///
        /// @param index  The index of the tab to remove.
        ///
        /// When the index is too high then nothing will happen.
        ///
        /// @see remove(sf::String)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void remove(unsigned int index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all tabs.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAll();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Get the name of the currently selected tab.
        ///
        /// @return The name of the tab.
        ///         When no tab is selected then this function returns an empty string.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getSelected() const
        {
            return (m_selectedTab >= 0) ? m_tabNames[m_selectedTab] : "";
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Get the index of the currently selected tab.
        ///
        /// @return The index of the tab.
        ///         When no tab is selected then this function returns -1.
        ///
        /// @warning The index returned by this function may no longer be correct when a tab is removed.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getSelectedIndex() const
        {
            return m_selectedTab;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the font of the tabs.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed with the setGlobalFont function from the parent.
        ///
        /// @param font  The new font.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(const sf::Font& font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the font of the tabs.
        ///
        /// @return  Pointer to the font that is currently being used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Font* getTextFont() const
        {
            return m_text.getFont();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the text color that will be used inside the tabs.
        ///
        /// @param color  The new text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(const sf::Color& color)
        {
            m_textColor = color;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Get the text color that is currently being used inside the tabs.
        ///
        /// @return The text color that is currently being used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getTextColor() const
        {
            return m_textColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the text color that will be used for the selected tab.
        ///
        /// @param color  The new text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedTextColor(const sf::Color& color)
        {
            m_selectedTextColor = color;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Get the text color that is currently being used for the selected tab.
        ///
        /// @return The text color that is currently being used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getSelectedTextColor() const
        {
            return m_selectedTextColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the character size of the text.
        ///
        /// @param size  The new size of the text.
        ///              If the size is 0 (default) then the text will be scaled to fit in the tab.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the character size of the text.
        ///
        /// @return The text size.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const
        {
            return m_text.getCharacterSize();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the height of the tabs.
        ///
        /// @param height  Height of the tabs
        ///
        /// By default, it is the height of the tab image that is loaded with the load function.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTabHeight(float height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the height of the tabs.
        ///
        /// @return Tab height
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float getTabHeight() const
        {
            return m_textureNormal.getSize().y;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the maximum tab width of the tabs.
        ///
        /// @param maximumWidth  Maximum width of a single tab
        ///
        /// If the text on the tab is longer than this width then it will be cropped to fit inside the tab.
        /// By default, the maximum width is 0 which means that there is no limitation.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumTabWidth(unsigned int maximumWidth);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum tab width of the tabs.
        ///
        /// @return Maximum tab width
        ///
        /// If the text on the tab is longer than this width then it will be cropped to fit inside the tab.
        /// By default, the maximum width is 0 which means that there is no limitation.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getMaximumTabWidth() const
        {
            return m_maximumTabWidth;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the distance between the text and the side of the tab.
        ///
        /// @param distanceToSide  distance between the text and the side of the tab
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setDistanceToSide(unsigned int distanceToSide);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the distance between the text and the side of the tab.
        ///
        /// @return distance between the text and the side of the tab
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getDistanceToSide() const
        {
            return m_distanceToSide;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the transparency of the widget.
        ///
        /// @param transparency  The transparency of the widget.
        ///                      0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /// Note that this will only change the transparency of the images. The parts of the widgets that use a color will not
        /// be changed. You must change them yourself by setting the alpha channel of the color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTransparency(unsigned char transparency) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y) override;

/**
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        // This function is a (slow) way to set properties on the widget, no matter what type it is.
        // When the requested property doesn't exist in the widget then the functions will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setProperty(std::string property, const std::string& value) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        // This function is a (slow) way to get properties of the widget, no matter what type it is.
        // When the requested property doesn't exist in the widget then the functions will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void getProperty(std::string property, std::string& value) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        // Returns a list of all properties that can be used in setProperty and getProperty.
        // The second value in the pair is the type of the property (e.g. int, uint, string, ...).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::list< std::pair<std::string, std::string> > getPropertyList() const override;
*/

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculates the size of each tab image.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculateTabsWidth();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const container) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() override
        {
            return std::make_shared<Tab>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Defines specific triggers to Tab.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum TabCallbacks
        {
            TabChanged = WidgetCallbacksCount * 1,          ///< Current Tab changed
            AllTabCallbacks = WidgetCallbacksCount * 2 - 1, ///< All triggers defined in Tab and its base classes
            TabCallbacksCount = WidgetCallbacksCount * 2
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        std::string   m_loadedConfigFile;

        bool          m_separateSelectedImage = true;

        unsigned int  m_textSize = 0;

        sf::Color     m_textColor;
        sf::Color     m_selectedTextColor;

        unsigned int  m_maximumTabWidth = 0;

        float         m_width = 0;

        // The distance between the side of the tab and the text that is drawn on top of the tab.
        unsigned int m_distanceToSide = 5;

        int  m_selectedTab = -1;

        std::vector<sf::String> m_tabNames;

        Texture             m_textureNormal;
        Texture             m_textureSelected;
        std::list<Texture>  m_texturesNormal;
        std::list<Texture>  m_texturesSelected;

        sf::Text m_text;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TAB_HPP

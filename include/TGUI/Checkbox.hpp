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


#ifndef TGUI_CHECKBOX_HPP
#define TGUI_CHECKBOX_HPP


#include <TGUI/RadioButton.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API Checkbox : public RadioButton
    {
      public:

        typedef std::shared_ptr<Checkbox> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Checkbox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Checkbox() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates the chackbox
        ///
        /// @param configFileFilename  Filename of the config file.
        ///
        /// @throw Exception when the config file couldn't be opened.
        /// @throw Exception when the config file didn't contain a "Checkbox" section with the needed information.
        /// @throw Exception when one of the images, described in the config file, couldn't be loaded.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Checkbox::Ptr create(const std::string& configFileFilename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another checkbox
        ///
        /// @param checkbox  The other checkbox
        ///
        /// @return The new checkbox
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Checkbox::Ptr copy(const Checkbox::Ptr& checkbox)
        {
            return std::make_shared<Checkbox>(*checkbox);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks the checkbox.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void check() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Unchecks the checkbox.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void uncheck() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void keyPressed(const sf::Event::KeyEvent& event) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() override
        {
            return std::make_shared<Checkbox>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Defines specific triggers to Checkbox.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum CheckboxCallbacks
        {
            AllCheckboxCallbacks = RadioButtonCallbacksCount - 1, ///< All triggers defined in RadioButton and its base classes
            CheckboxCallbacksCount = RadioButtonCallbacksCount
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_CHECKBOX_HPP

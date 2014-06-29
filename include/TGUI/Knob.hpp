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


#ifndef TGUI_KNOB_HPP
#define TGUI_KNOB_HPP


#include <TGUI/Widget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API Knob : public Widget
    {
      public:

        typedef std::shared_ptr<Knob> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Knob();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Knob() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the knob
        ///
        /// @param configFileFilename  Filename of the config file.
        ///
        /// @throw Exception when the config file couldn't be opened.
        /// @throw Exception when the config file didn't contain a "Knob" section with the needed information.
        /// @throw Exception when one of the images, described in the config file, couldn't be loaded.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Knob::Ptr create(const std::string& configFileFilename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another knob
        ///
        /// @param knob  The other knob
        ///
        /// @return The new knob
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Knob::Ptr copy(const Knob::Ptr& knob)
        {
            return std::make_shared<Knob>(*knob);
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
        /// @brief Set the position of the knob
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// @param position  Coordinate of the new position
        ///
        /// @see move, getPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPosition(const Layout& position) override;
        using Transformable::setPosition;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the knob.
        ///
        /// @param size  The new size of the knob
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(const Layout& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the start rotation, which is the place where the value should be minimal.
        ///
        /// @param startRotation  New start rotation.
        ///
        /// The rotation is a number in the interval [0,360[, for which 0 to to the right and the rotation goes counter-clockwise.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setStartRotation(float startRotation);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the end rotation, which is the place where the value should be maximal.
        ///
        /// @param endRotation  New end rotation.
        ///
        /// The rotation is a number in the interval [0,360[, for which 0 to to the right and the rotation goes counter-clockwise.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setEndRotation(float endRotation);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the value for when the knob would be rotated in the direction of StartRotation.
        ///
        /// @param minimum  The new minimum value
        ///
        /// The knob will be rotated to keep representing the value correctly.
        ///
        /// When the value is too small then it will be changed to this minimum.
        /// When the maximum value is lower than the new minimum then it will be changed to this new minimum value.
        /// The default minimum value is 0.
        ///
        /// @see setStartRotation
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setMinimum(int minimum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the value for when the knob would be rotated in the direction of EndRotation.
        ///
        /// @param maximum  The new maximum value
        ///
        /// The knob will be rotated to keep representing the value correctly.
        ///
        /// When the value is too big then it will be changed to this maximum.
        /// When the minimum value is higher than the new maximum then it will be changed to this new maximum value.
        /// The default maximum value is 360.
        ///
        /// @see setEndRotation
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setMaximum(int maximum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the current value.
        ///
        /// @param value  The new value
        ///
        /// The knob will be rotated to correctly represent this new value.
        ///
        /// The value can't be smaller than the minimum or bigger than the maximum.
        /// The default value is 0.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setValue(int value);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the value when the knob would be rotated in the direction of StartRotation.
        ///
        /// @return The current minimum value
        ///
        /// The default minimum value is 0.
        ///
        /// @see getStartRotation
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getMinimum() const
        {
            return m_minimum;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the value when the knob would be rotated in the direction of EndRotation.
        ///
        /// @return The current maximum value
        ///
        /// The default maximum value is 360.
        ///
        /// @see getEndRotation
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getMaximum() const
        {
            return m_maximum;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current value.
        ///
        /// @return The current value, determined by the Minimum, Maximum, StartRotation and EndRotation
        ///
        /// The default value is 0.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getValue() const
        {
            return m_value;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Should the value increase when turning the knob clockwise?
        ///
        /// @param clockwise  Does the value increase when turning clockwise?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setClockwiseTurning(bool clockwise);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the value increases when turning the knob clockwise?
        ///
        /// @return Does the value increase when turning clockwise?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getClockwiseTurning()
        {
            return m_clockwiseTurning;
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

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetFocused() override;

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
        // Recalculates the rotation of the knob.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculateRotation();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() override
        {
            return std::make_shared<Knob>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Defines specific triggers to Knob.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum KnobCallbacks
        {
            ValueChanged       = WidgetCallbacksCount * 1,     ///< Value changed (knob turned)
            AllKnobCallbacks   = WidgetCallbacksCount * 2 - 1, ///< All triggers defined in Knob and its base classes
            KnobCallbacksCount = WidgetCallbacksCount * 2
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        std::string m_loadedConfigFile;

        Texture m_backgroundTexture;
        Texture m_foregroundTexture;

        bool m_clockwiseTurning = true; // Does rotating clockwise increment the value?
        float m_imageRotation = 0;
        float m_startRotation = 90;
        float m_endRotation = 90;

        int m_minimum = 0;
        int m_value = 0;
        int m_maximum = 360;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_KNOB_HPP


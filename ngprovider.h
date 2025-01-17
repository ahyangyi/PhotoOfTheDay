/*
 *   Copyright (C) 2007 Tobias Koenig <tokoe@kde.org>
 *   Copyright  2008 by Anne-Marie Mahfouf <annma@kde.org>
 *   Copyright  2008 by Georges Toth <gtoth@trypill.org>
 *
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License as published by  
 *   the Free Software Foundation; either version 2 of the License, or     
 *   (at your option) any later version.   
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef FLICKRPROVIDER_H
#define FLICKRPROVIDER_H

#include "potdprovider.h"

/**
* This class grabs a random image from the flickr
* interestingness stream of pictures, for the given date.
* Should there be no image for the current date, it tries
* to grab one from the day before yesterday.
 */
class NGProvider : public PotdProvider
{
    Q_OBJECT

    public:
        /**
         * Creates a new flickr provider.
         *
         * @param date The date for which the image shall be fetched.
         * @param parent The parent object.
         */
        NGProvider( QObject *parent, const QVariantList &args );

        /**
         * Destroys the flickr provider.
         */
        ~NGProvider();

        /**
         * Returns the requested image.
         *
         * Note: This method returns only a valid image after the
         *       finished() signal has been emitted.
         */
        virtual QImage image() const;

        /**
         * Returns the identifier of the picture request (name + date).
         */
        virtual QString identifier() const;

    private:
      class Private;
      Private* const d;

      Q_PRIVATE_SLOT( d, void pageRequestFinished( KJob* ) )
      Q_PRIVATE_SLOT( d, void imageRequestFinished( KJob* ) )
};

#endif

/*
 *   Copyright  2011 by Yi Yang <ahyangyi@gmail.com>
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

#include "ngprovider.h"

#include <QtCore/QDate>
#include <QtCore/QRegExp>
#include <QtGui/QImage>

#include <KDebug>
#include <kio/job.h>

POTDPROVIDER_EXPORT_PLUGIN( NGProvider, "NGProvider", "" )

class NGProvider::Private
{
    public:
    Private( NGProvider *parent )
        : mParent( parent )
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    }

    void pageRequestFinished( KJob* );
    void imageRequestFinished( KJob* );
    void parsePage();

    NGProvider *mParent;
    QByteArray mPage;
    QDate mDate;
    QImage mImage;
};

void NGProvider::Private::pageRequestFinished( KJob *_job )
{
    KIO::StoredTransferJob *job = static_cast<KIO::StoredTransferJob *>(_job);
    if ( job->error() ) {
        emit mParent->error( mParent );
        return;
    }

    const QString data = QString::fromUtf8( job->data() );

    int pos = data.indexOf("download_link");
    int pos1, pos2;

    if (pos != -1)
    {
        pos1 = data.indexOf("href=", pos) + 6;
        pos2 = data.indexOf("\"", pos1);
    }
    else
    {
        pos = data.indexOf("primary_photo");

        if (pos == -1)
        {
            emit mParent->error( mParent );
            kDebug() << "page doesn't contain valid photos";
            return;
        }

        pos1 = data.indexOf("img src=", pos) + 9;
        pos2 = data.indexOf("\"", pos1);
    }

    const QString sub = data.mid( pos1, pos2 - pos1);

    KUrl url( sub  );
//    KIO::StoredTransferJob *imageJob = KIO::storedGet( url, KIO::NoReload, KIO::HideProgressInfo);
    KIO::StoredTransferJob *imageJob = KIO::storedGet( url );
    mParent -> connect(imageJob, SIGNAL( finished( KJob* )), SLOT( imageRequestFinished( KJob* ) ) ); 
}

void NGProvider::Private::imageRequestFinished( KJob *_job )
{
    KIO::StoredTransferJob *job = static_cast<KIO::StoredTransferJob *>( _job );
    if ( job->error() ) {
        emit mParent->error( mParent );
        return;
    }

    mImage = QImage::fromData( job->data() );
    emit mParent->finished( mParent );
}

    NGProvider::NGProvider( QObject *parent, const QVariantList &args )
: PotdProvider( parent, args ), d( new Private( this ) )
{
    const QString type = args[ 0 ].toString();
    if ( type == QLatin1String( "Date" ) ) {
        d->mDate = args[ 1 ].toDate();
    } else {
        Q_ASSERT( false && "Invalid type passed to potd provider" );
    }

    KUrl url(QLatin1String( "http://photography.nationalgeographic.com/photography/photo-of-the-day/" ) );
    KIO::StoredTransferJob *job = KIO::storedGet( url );
    connect( job, SIGNAL( finished( KJob* ) ), SLOT( pageRequestFinished( KJob* ) ) );
}

NGProvider::~NGProvider()
{
    delete d;
}

QImage NGProvider::image() const
{
    return d->mImage;
}

QString NGProvider::identifier() const
{
    return QString( QLatin1String( "ng:%1" ) ).arg( d->mDate.toString( Qt::ISODate ));
}

#include "ngprovider.moc"

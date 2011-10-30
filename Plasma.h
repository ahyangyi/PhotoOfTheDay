#ifndef PhotoOfTheDay_HEADER
#define PhotoOfTheDay_HEADER

#include <KIcon>
 
#include <Plasma/Applet>
#include <Plasma/Svg>
 
class QSizeF;
 
// Define our plasma Applet
class PhotoOfTheDay : public Plasma::Applet
{
    Q_OBJECT
    public:
        // Basic Create/Destroy
        PhotoOfTheDay(QObject *parent, const QVariantList &args);
        ~PhotoOfTheDay();
 
        // The paintInterface procedure paints the applet to screen
        void paintInterface(QPainter *p,
                const QStyleOptionGraphicsItem *option,
                const QRect& contentsRect);
    void init();
 
    private:
        Plasma::Svg m_svg;
        KIcon m_icon;
};
 
#endif
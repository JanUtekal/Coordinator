#include <QObject>
#include <QGeoPositionInfoSource>
using namespace QtMobility;

class LocationWatcher : public QObject
{
    Q_OBJECT

public:
    LocationWatcher(QObject *parent = 0);
    void enable();
    void disable();

signals:
    void updateMyLocation(double lon, double lat);
private slots:
    void positionUpdated(const QGeoPositionInfo &info);

private:
    QGeoPositionInfoSource *source;
};

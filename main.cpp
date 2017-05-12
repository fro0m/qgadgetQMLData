#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QDebug>

class SuperItem {
    Q_GADGET
    Q_PROPERTY(int x MEMBER m_x)
    Q_PROPERTY(int y MEMBER m_y)
public:
    bool operator==(const SuperItem & t_right) {
        if (t_right.m_x == this->m_x && t_right.m_y == this->m_y) {
            return true;
        }
        return false;
    }
public:
    int m_y;
    int m_x;

};
QML_DECLARE_TYPE(SuperItem)

class SuperModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(SuperItem superItem READ superItem WRITE setSuperItem NOTIFY SuperItemChanged)
    Q_PROPERTY(SuperItem * superItemP READ superItemP WRITE setSuperItemP NOTIFY superItemPChanged)
public:
    explicit SuperModel(QObject * parent = nullptr)
        : QObject(parent) {
        m_superItem.m_x = 111;
        m_superItem.m_y = 222;
    }

    SuperItem* superItemP() /*const*/
    {
        return &m_superItem;
    }

    SuperItem superItem() const
    {
        return m_superItem;
    }

    Q_INVOKABLE int getSuperItemXFromC() const {
        return m_superItem.m_x;
    }

public slots:
    void setSuperItemP(SuperItem * superItem)
    {
        qDebug() << "tracking @ " << Q_FUNC_INFO;
        m_superItem.m_x = superItem->m_x;
        m_superItem.m_y = superItem->m_y;

        emit superItemPChanged(superItem);
    }

    void setSuperItem(SuperItem superItem)
    {
        if (m_superItem == superItem)
            return;

        m_superItem = superItem;
        emit SuperItemChanged(superItem);
    }

signals:
    void superItemPChanged(SuperItem * superItem);

    void SuperItemChanged(SuperItem superItem);

private:
    SuperItem m_superItem;
};

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qRegisterMetaType<SuperItem>();
    qRegisterMetaType<SuperItem *>();

    qmlRegisterType<SuperModel>("qgadgettest", 1, 0, "SuperModel");

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}

#include "main.moc"


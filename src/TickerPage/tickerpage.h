#ifndef TICKERPAGE_H
#define TICKERPAGE_H

#include <QWidget>
#include <QStaticText>
#include <QTimer>

namespace Ui {
class TickerPage;
}

class TickerPage : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QString separator READ separator WRITE setSeparator)

public:
    TickerPage(QWidget *parent = nullptr, QString text = "");
    virtual ~TickerPage();

public slots:
    QString text() const;
    void setText(QString text);

    void setField(QString key, QString val);

    QString separator() const;
    void setSeparator(QString separator);

protected:
    void paintEvent(QPaintEvent *);

private:
    void updateText();
    QMap<QString, QString> fields;
    QString _text;
    QString _separator;
    QStaticText staticText;
    int singleTextWidth;
    QSize wholeTextSize;
    int leftMargin;
    int scrollPos;
    QImage buffer;
    QTimer* timer;

private slots:
    virtual void timeout();
};
#endif // TICKERPAGE_H

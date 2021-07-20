#ifndef USAGEWIDGET_H
#define USAGEWIDGET_H
#include <QWidget>
#include <QPixmap>
#include <QColor>
#include <QQueue>
#include <QResizeEvent>
constexpr int QUEUE_MAX = 60;

class UsageWidget:public QWidget
{
public:
    explicit UsageWidget(QWidget* parent):QWidget(parent),m_viewh(0),m_viewv(0),
        m_base(1),m_currentpt(0),m_ptnum(0),m_incbase(0),m_graphx(0.0)
    {
        Init();
    }
    ~UsageWidget(){}

private:

    void paintEvent(QPaintEvent *e);

    void resizeEvent(QResizeEvent* e)
    {
        Q_UNUSED(e);
        m_viewh = height();
        m_viewv = width();

        m_backgroundpixmap = QPixmap(m_viewv - m_base * 2, m_viewh - m_base * 2);
        m_backgroundpixmap.fill(Qt::white);
        m_incbase = (m_viewv - m_base * 2) / 60.0;
    }

private:

    void Init();

public:

    void AddUsageData(const double & usage);

private:

    int m_viewh;
    int m_viewv;
    int m_base;


    QPixmap m_backgroundpixmap;


    int m_currentpt;
    int m_ptnum;

    QColor m_mashcolor,m_linecolor,m_bodercolor;

    double m_incbase;

    QQueue<double> m_ptbuffer;

    double m_graphx;
};
#endif // USAGEWIDGET_H

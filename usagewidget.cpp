#include "usagewidget.h"
#include <QPainter>
#include <QPen>
#include <QLineF>
#include <QPainterPath>
#include <QPolygonF>


void UsageWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    painter.drawPixmap(m_base,m_base,m_backgroundpixmap);

    int col_ymax = m_backgroundpixmap.height();
    int row_xmax = m_backgroundpixmap.width();

    double colspac = row_xmax / 20.0f;
    double rowspac = col_ymax / 10.0f;

    QPen borderpen(m_bodercolor);
    borderpen.setWidthF(1.2);
    painter.setPen(borderpen);
    painter.drawRect(m_base,m_base,row_xmax,col_ymax);

    if(m_viewh > 130 || m_viewv > 285)
    {
        painter.setPen(m_mashcolor);

        for(double beginy = m_base; beginy < m_base + col_ymax; beginy += rowspac)
        {
            painter.drawLine(QLineF(m_base, beginy, m_base + row_xmax, beginy));
        }

        if(!m_graphx)
        {
            m_graphx += colspac;
        }

        for(double beginx = m_base + m_graphx; beginx < row_xmax + m_base; beginx += colspac)
        {
            painter.drawLine(QLineF(beginx, m_base, beginx, m_base + col_ymax));
        }
    }

    int ptnum = m_ptbuffer.size();
    QPen linepen(m_linecolor);
    linepen.setWidthF(1.2);
    painter.setPen(linepen);


    QPolygonF poly;
    int i = 1, j = ptnum;
    for(; i < ptnum; i++ , --j)
    {
        //painter.drawLine(QLineF(perx, (1 - m_ptbuffer[i - 1] / 100.0f) * col_ymax,
                //seccx, (1 - m_ptbuffer[i] / 100.0f) * col_ymax));
        //生成多边形
        poly.append(QPointF(m_base + row_xmax - (j - 1) * m_incbase
                            , (1 - m_ptbuffer[i - 1] / 100.0f) * col_ymax));
        poly.append(QPointF(m_base + row_xmax - (j - 2) * m_incbase
                            , (1 - m_ptbuffer[i] / 100.0f) * col_ymax));
    }
    //添加最后两个点
    poly.append(QPointF(m_base + row_xmax, m_base + col_ymax));
    if(ptnum >= QUEUE_MAX)
    {
        poly.append(QPointF(m_base, m_base + col_ymax));
    }
    QBrush oldBrush;
    QBrush brush(QColor(241,246,250,140));
    oldBrush = painter.brush();
    painter.setBrush(brush);
    painter.drawPolygon(poly);
    painter.setBrush(oldBrush);

    if(m_ptnum != m_currentpt)
    {
        m_currentpt = m_ptnum;
        m_graphx -= m_incbase;
    }
}

void UsageWidget::Init()
{ 
    m_backgroundpixmap = QPixmap(m_viewv - m_base * 2, m_viewh - m_base * 2);
    m_backgroundpixmap.fill(Qt::white);

    m_mashcolor = QColor(206,226,248);
    m_linecolor = QColor(17,125,187);
    m_bodercolor = QColor(17,125,187);
    m_ptbuffer.append(0.0f);
}

void UsageWidget::AddUsageData(const double & usage)
{
    int tusage;

    usage > 100.0 ? tusage = 100 : tusage = usage;
    usage < 0.0 ? tusage = 0 : tusage = usage;

    m_ptnum++;
    m_ptbuffer.push_back(tusage);
    size_t currentsize = m_ptbuffer.size();
    if(currentsize > (QUEUE_MAX + 1))
    {
       m_ptbuffer.pop_front();
    }
    update();
}

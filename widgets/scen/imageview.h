#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>

#include "drawshape/shapeswidget.h"
#include "utils/baseutils.h"

class QWheelEvent;
class QPaintEvent;
class QFile;

class ImageView : public QGraphicsView
{
    Q_OBJECT

public:
    enum RendererType { Native, OpenGL, Image };

    ImageView(QWidget *parent = 0);

    void setImage(const QString  &path);
    void setRenderer(RendererType type = Native);
    void drawBackground(QPainter *p, const QRectF &rect);

    QRect calculateImageScaledGeometry();

public slots:
    void setHighQualityAntialiasing(bool highQualityAntialiasing);
    void setViewBackground(bool enable);
    void setViewOutline(bool enable);

    void initShapesWidget(QString shape);
    void updateShapesColor(DrawStatus drawstatus, QColor color);
    void updateShapesLineWidth(int linewidth);
    void updateLineShapes(QString lineShape);
    void updateTextFontsize(int fontsize);
    void updateBlurLinewidth(int linewidth);

    void rotateImage(const QString &path, int degree);
    void generateBlurEffect(const QString &type);
    void mirroredImage(bool horizontal = false, bool vertical = true) /*const*/;

protected:
    void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    RendererType m_renderer;

    QGraphicsItem *m_svgItem;
    QGraphicsItem *m_pixmapItem;
    QGraphicsRectItem *m_backgroundItem;
    QGraphicsRectItem *m_outlineItem;

    QImage m_image;
    QString m_currentPath;

    QRectF m_imageRect;
    QRect m_originRect;
    qreal m_sx;
    qreal m_sy;

    bool m_imageLoaded;
    bool m_shapesWidgetExist;
    ShapesWidget* m_shapesWidget;
};
#endif // IMAGEVIEW_H

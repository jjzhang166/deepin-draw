﻿#ifndef BASEUTILS_H
#define BASEUTILS_H

#include <QCursor>
#include <QFont>
#include <QLayout>
#include <QFontMetrics>
#include <QPainter>

enum ResizeDirection {
    Rotate,
    Moving,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    Top,
    Bottom,
    Left,
    Right,
    Outting,
};

enum DrawStatus {
    Fill,
    Stroke,
};

QCursor setCursorShape(QString cursorName, int colorIndex = 0);
int stringWidth(const QFont &f, const QString &str);
QString     getFileContent(const QString &file);
QColor       colorIndexOf(int index);
int                colorIndex(QColor color);
bool          isValidFormat(QString suffix);
bool          isCommandExist(QString command);
void  paintSelectedPoint(QPainter &painter, QPoint pos,
                                              QPixmap pointImg);
QVariantList cachePixmap(const QString &path);
QString DetectImageFormat(const QString &filepath);
#endif // BASEUTILS_H

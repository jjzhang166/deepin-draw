#include "colorpanel.h"

#include <QPainter>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QButtonGroup>
#include <QDebug>

#include "utils/baseutils.h"
#include "utils/global.h"
#include "colorlabel.h"
#include "colorslider.h"
#include "pickcolorwidget.h"

ColorButton::ColorButton(const QColor &color, QWidget *parent)
    : QPushButton(parent), m_disable(false) {
    m_color = color;
    setFixedSize(20, 20);
    setCheckable(true);

    connect(this, &ColorButton::clicked, this, [=]{
        qDebug() << "ColorButton:" << m_color;
        if (m_disable) {
            emit colorButtonClicked(Qt::transparent);
        } else {
            emit colorButtonClicked(m_color);
        }
    });
}

void ColorButton::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(m_color);

    if (m_disable) {
        painter.drawPixmap(QRect(3, 3, this->width() - 6, this->height() - 6),
            QPixmap(":/theme/light/images/draw/color_disable_active.png"));
        if (isChecked()) {
            painter.setBrush(QBrush());
            QPen borderPen;
            borderPen.setWidth(1);
            borderPen.setColor("#01bdff");
            painter.setPen(borderPen);
            painter.drawRoundedRect(this->rect(), 4, 4);
        }
        return;
    }

    painter.setBrush(QBrush(m_color));

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(0, 0, 0, 51));
    painter.setPen(pen);
    painter.drawRoundedRect(QRect(2, 2, this->width() - 4, this->height() - 4), 4, 4);

    if (isChecked()) {
        painter.setBrush(QBrush());
        QPen borderPen;
        borderPen.setWidth(1);
        borderPen.setColor("#01bdff");
        painter.setPen(borderPen);
        painter.drawRoundedRect(this->rect(), 4, 4);
    }
}

void ColorButton::setDisableColor(bool disable) {
    m_disable = disable;
}

ColorButton::~ColorButton() {}

ColorPanel::ColorPanel(QWidget *parent)
    : QWidget(parent) {
    DRAW_THEME_INIT_WIDGET("ColorPanel");
    setFixedSize(232, 416);

    QStringList colList;
    colList << QString("") << QString("#ff0c0c") << QString("#fe3c3b") << QString("#fd6867") << QString("#fd9694")
            << QString("#fcc4c1") << QString("#f8e0d6") << QString("#e4c299") << QString("#f2aa46")
            << QString("#fd9d0f") << QString("#f6b443") << QString("#eecb77") << QString("#f0ee4e")
            << QString("#f4fb00") << QString("#f6f96d") << QString("#f4f6a6") << QString("f3f3d6")
            << QString("#e9eedc") << QString("#dde8cb") << QString("#ccdfb0") << QString("#9cd972")
            << QString("#4ec918") << QString("#5cc850") << QString("#6bc989") << QString("#53ac6d")
            << QString("#72b88e") << QString("#7cc8cd") << QString("#97d1d4") << QString("#c9e1e1")
            << QString("#c1dee7") << QString("#93ceed") << QString("#76c3f1") << QString("#49b2f6")
            << QString("#119fff") << QString("#0192ea") << QString("#3d7ddd") << QString("#92cdfb")
            << QString("#99cffa") << QString("#ececf8") << QString("#ccc9f9") << QString("#b2acf9")
            << QString("#958ef9") << QString("#7c6ffa") << QString("#8a47fb") << QString("#6b1aef")
            << QString("#952dfd") << QString("#af39e4") << QString("#c174da") << QString("#c587d9")
            << QString("#dbb4c1") << QString("#cf8c86") << QString("#b45f51") << QString("#865e4f")
            << QString("#694d48") << QString("#ffffff") << QString("#d4d4d4") << QString("#919191")
            << QString("#626262") << QString("#404040") << QString("#000000");

    QList<ColorButton*> cButtonList;
    QButtonGroup* colorsButtonGroup = new QButtonGroup(this);
    colorsButtonGroup->setExclusive(true);

    QGridLayout* gLayout = new QGridLayout;
    gLayout->setVerticalSpacing(3);
    gLayout->setHorizontalSpacing(3);

    for(int i = 0; i < colList.length(); i++) {
        ColorButton* cb = new ColorButton(QColor(colList[i]), this);
        if (i == 0)
            cb->setDisableColor(true);
        cButtonList.append(cb);
        gLayout->addWidget(cb, i/10, i%10);
        colorsButtonGroup->addButton(cb);
        qDebug() << "~~~" << i/10 << i%10;
        connect(cb, &ColorButton::colorButtonClicked, this, &ColorPanel::colorChanged);
    }

    m_sliderLabel = new SliderLabel("Alpha", this);
    m_sliderLabel->setFixedHeight(25);

    m_editLabel = new EditLabel(this);
    m_editLabel->setTitle(tr("Color"));
    m_editLabel->setEditText("#FF0000");


    m_colorfulBtn = new PushButton(this);
    m_colorfulBtn->setObjectName("ColorFulButton");

    QHBoxLayout* colorLayout = new QHBoxLayout;
    colorLayout->setMargin(0);
    colorLayout->setSpacing(0);
    colorLayout->addWidget(m_editLabel);
    colorLayout->addWidget(m_colorfulBtn);

    PickColorWidget* pickColWidget = new PickColorWidget(this);

    connect(pickColWidget, &PickColorWidget::pickedColor, this, [=](QColor color){
        m_editLabel->setEditText(color.name());
    });

    connect(pickColWidget, &PickColorWidget::pickedColor, this, &ColorPanel::colorChanged);

    QVBoxLayout* mLayout = new QVBoxLayout(this);
    mLayout->setContentsMargins(4, 4, 4, 4);
    mLayout->setSpacing(0);
    mLayout->addLayout(gLayout);
    mLayout->addWidget(m_sliderLabel);
    mLayout->addSpacing(2);
    mLayout->addLayout(colorLayout);
    mLayout->addSpacing(5);
    mLayout->addWidget(pickColWidget);

    setLayout(mLayout);
}

ColorPanel::~ColorPanel() {}

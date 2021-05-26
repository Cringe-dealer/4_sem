#include <iostream>
#include <QPointF>
#include <QApplication>
#include <QPen>
#include <QBrush>
#include "canvas.hpp"

canvas::canvas(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
}

canvas::~canvas()
{
}

void canvas::cut()
{
    _cutter.cut();
    this->update();
}

void canvas::set_bg(const QColor &color)
{
    bg = color;
}

void canvas::set_cut_col(const QColor &color)
{
    _cutter.set_cut_col(color);
    this->update();
}

void canvas::set_seg_col(const QColor &color)
{
    _cutter.set_seg_col(color);
    this->update();
}

void canvas::set_vis_col(const QColor &color)
{
    _cutter.set_vis_col(color);
    this->update();
}

void canvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.setBrush(bg);
    painter.setPen(QColor(0, 0, 0));
    painter.drawRect(0, 0, this->width(), this->height());

    _cutter.draw(painter);
}

void canvas::mousePressEvent(QMouseEvent *event)
{
    process = not process;
    Qt::KeyboardModifiers key = QApplication::queryKeyboardModifiers();
    bool is_hor = false, is_vert = false;
    if (key == Qt::ShiftModifier)
        is_hor = true;
    if (key == Qt::ControlModifier)
        is_vert = true;
    _cutter.add_point(event->pos().x(), event->pos().y(), is_hor, is_vert);
    this->update();
}

void canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (!process)
        return;

    Qt::KeyboardModifiers key = QApplication::queryKeyboardModifiers();
    bool is_hor = false, is_vert = false;
    if (key == Qt::ShiftModifier)
        is_hor = true;
    if (key == Qt::ControlModifier)
        is_vert = true;
    _cutter.render_point(event->pos().x(), event->pos().y(), is_hor, is_vert);
    this->update();
}

void canvas::clear()
{
    _cutter.clear();

    this->update();
}

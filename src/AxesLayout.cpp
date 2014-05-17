/*!
  \file AxesLayout.cpp
  \brief file contains the implementation of the class AxesLayout.

  \author Geghetsik Dabaghyan 
 */

//! Headers from standard libraries
#include <QtGui>
#include <iostream>

//! Headers from current project
#include <AttributeAxis.hpp>
#include <AxesPairLink.hpp>
#include <AxesLayout.hpp>
#include <DataComponent.hpp>
#include <DataEntry.hpp>
#include <PointOnAxis.hpp>
#include <PointsOnAxisLink.hpp>
#include <Task.hpp>

AxesLayout::AxesLayout (QString granularity, QString nature, 
						QObject* parent)
	: QGraphicsScene(parent)
{
	_task = new Task(granularity, nature, this);

	_selectionAreaRect = new QGraphicsRectItem();
	_selectionAreaRect->setVisible(false);
	_selectionAreaRect->setPen(QPen(Qt::darkBlue));
	_selectionAreaRect->setBrush(Qt::darkCyan);
	_selectionAreaRect->setOpacity(0.25);
	addItem(_selectionAreaRect);
}

void AxesLayout::addAttributeAxis(AttributeAxis* axis)
{
	addItem(axis);
	_axes.push_back(axis);
}

void AxesLayout::addAttributeAxes(std::vector<AttributeAxis*> axes)
{
	for (uint i = 0; i < axes.size(); ++i) {
		addItem(axes[i]);
		_axes.push_back(axes[i]);
		axes[i]->setAxesLayout(this);
	}
	arrangeAxes();
	createLinkedAxesPairs();
}


void AxesLayout::arrangeAxes()
{
	if (_axes.empty()) {
		std::cout << "Axes layout is empty" << std::endl;
		return;
	}
	int size = _axes.size();
	qreal length = 98 * height() / 100;
	qreal axisPosY = 99 * height() / 100;
//	qreal axisY2 = height() / 10;
	qreal offset = width() / (size + 1);
	std::cout << "ARRANGE AXES =============== " << offset << std::endl;
	for (int i = 0; i  < size; ++i) {
		AttributeAxis* axis = _axes[i];
		qreal axisPosX = (i + 1) * offset;
		axis->setPos(axisPosX, axisPosY);
		axis->setRotation(-180);
		axis->setLine(0, 0, 0, length);
	}
}

void AxesLayout::remapDataPoints()
{
	if (_axes.empty()) {
		std::cout << "Axes layout is empty" << std::endl;
		return;
	}
	for (int i = 0; i  < _axes.size(); ++i) {
		_axes[i]->remapDataPoints();
	}
	for (int i = 0; i < _linkedAxesPairs.size(); ++i) {
		_linkedAxesPairs.at(i)->updateDataLinks();
	}

}

void AxesLayout::createLinkedAxesPairs()
{
	for (int i = 0; (i + 1) < _axes.size(); ++i) {
		std::cout << "AXES pair: " << i << _axes.size() << std::endl;
		AttributeAxis* axis1 = _axes[i];
		AttributeAxis* axis2 = _axes[i+1];
		AxesPairLink* axesPair = new AxesPairLink(axis1, axis2);
		_linkedAxesPairs.append(axesPair);

		// add links of axesPair to scene/layout
		QMap<DataEntry*, PointsOnAxisLink*>& map = axesPair->getDataLinks();
		QMap<DataEntry*, PointsOnAxisLink*>::iterator it;
		for (it = map.begin(); it != map.end(); ++it) {
			PointsOnAxisLink* link = map[it.key()];
			addItem(link);
		}
	}
}


void AxesLayout::updateLinks(AttributeAxis* axis)
{
	for (int i = 0; i < _linkedAxesPairs.size(); ++i) {
		if (_linkedAxesPairs.at(i)->axesPairContains(axis)) {
			_linkedAxesPairs.at(i)->updateDataLinks();
		}
	}
}

void AxesLayout::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mousePressEvent(event);
	if (event->modifiers() == 0 || event->modifiers() == Qt::CTRL) {
		_selectionAreaRect->setRect(event->scenePos().x(), 
				event->scenePos().y(), 0, 0);
		_selectionAreaRect->setVisible(true);
		std::cout<< "LAYOUT clicked" << std::endl;
	}
}

void AxesLayout::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseMoveEvent(event);
	if (event->modifiers() == 0 || event->modifiers() == Qt::CTRL) {
		if (QLineF(event->screenPos(), 
				event->buttonDownScreenPos(Qt::LeftButton)).length() 
				< QApplication::startDragDistance()) {
			return;
		}
	
		QRectF rect = QRectF(event->buttonDownScenePos(Qt::LeftButton), 
				event->scenePos()).normalized();
		_selectionAreaRect->setRect(rect);
		QPainterPath path;
		path.addRect(rect);
		setSelectionArea(path);
	}

}

void AxesLayout::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseReleaseEvent(event);
	if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
			.length() < QApplication::startDragDistance()) {
		return;
	}
	if (!selectedItems().isEmpty()) {
		if (event->modifiers() == Qt::CTRL) {
			_task->addToLastPattern(selectedItems());
			_task->perform();
		} else if (event->modifiers() == 0) {
			_task->addNewPattern(selectedItems());
			_task->perform();
		}
		clearSelection();
	}
	_selectionAreaRect->setVisible(false);
	_selectionAreaRect->update();
}

QList<DataEntry*>* AxesLayout::getData ()
{
	return _data;
}

void AxesLayout::setData (QList<DataEntry*>* data)
{
	_data = data;
}

QList<AttributeAxis*>& AxesLayout::getAxes()
{
	return _axes;
}

void AxesLayout::updateAllLinks()
{
	for (int i = 0; i < _linkedAxesPairs.size(); ++i) {
		_linkedAxesPairs.at(i)->updateDataLinks();
	}
}

void AxesLayout::setTaskToDefault()
{
	delete _task;
	_task = new Task(tr("Elementary"), tr("Comparison"), this);
}

void AxesLayout::setTaskGranularuty(QString granularity)
{
	_task->setGranularity(granularity);
}

void AxesLayout::setTaskNature(QString nature)
{
	_task->setNature(nature);
}

void AxesLayout::taskPerform()
{
	_task->perform();
}

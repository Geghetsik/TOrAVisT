/*!
  @file Toravist.hpp
  @brief file contains the definaion of the class Toravist.

  @author Geghetsik Dabaghyan 
 */

#pragma once

//! Headers from standard libraries
#include <QMainWindow>
#include <list>

//! Headers from current project

//! Forward declarations
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QRadioButton;
class QGroupBox;

class Task;
class AxesLayout;
class DataEntry;
class QGraphicsView;

/*!
  \class Toravist Toravist.hpp "include/Toravist.hpp"
  \brief Main class of the application

  This is the main class of the application.
 */
class Toravist : public QMainWindow
{
	Q_OBJECT

	public:
		Toravist();
		~Toravist();

	protected:

		private slots:
			void loadData();
			void about();

	private:
		void createActions();
		void createMenus();

		QMenu*	_fileMenu;
		QMenu*	_taskMenu;
		QMenu*	_helpMenu;

		QAction*	_loadDataAct;
		QAction*	_exitAct;
		QAction*	_aboutAct;
		QAction*	_newTask;
		QAction*	_undo;
		QAction*	_redo;

/*
		std::list<Task*> 			_taskHistory;
		std::list<Task*>::iterator 	_currentTaskIndex;		
		Task* 						_currentTask;
*/		

		QGroupBox*	_taskGranularityGroup;
		QGroupBox*	_taskNatureGroup;

		QRadioButton*	_elementaryTaskRadioBtn;
		QRadioButton*	_synopticTaskRadioBtn;
		QRadioButton*	_lookupTaskRadioBtn;
		QRadioButton*	_comparisonTaskRadioBtn;

		AxesLayout* 				_axesLayout;
		std::list<DataEntry*>		_data;

		QGraphicsView*				_view;

	private:
		void createTaskGroup();
		void createGranularityGroup();
		void createNatureGroup();

};


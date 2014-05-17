/*!
  @file Toravist.hpp
  @brief file contains the definaion of the class Toravist.

  @author Geghetsik Dabaghyan 
 */

#pragma once

//! Headers from standard libraries
#include <QMainWindow>
#include <QToolBar>
#include <list>

//! Headers from current project

//! Forward declarations
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QRadioButton;
class QPushButton;
class QGroupBox;
class QComboBox;
//class QToolBar;

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
			void taskGranularityChanged(QString newValue);
			void taskNatureChanged(QString newValue);
			void setTaskDefault();
			void about();

	private:
		void createToolBox();
		void createTaskToolbar();
		void createViewToolBar();
		void createActions();
		void createMenus();

		QMenu*	_fileMenu;
		QMenu*	_taskMenu;
		QMenu*	_viewMenu;
		QMenu*	_helpMenu;

		QAction*	_loadDataAct;
		QAction*	_exitAct;
		QAction*	_aboutAct;
		QAction*	_defaultViewAct;
		QAction*	_undoAct;
		QAction*	_redoAct;

/*
		std::list<Task*> 			_taskHistory;
		std::list<Task*>::iterator 	_currentTaskIndex;		
		Task* 						_currentTask;
*/		

		QComboBox*		_taskGranularityCombo;
		QComboBox*		_taskNatureCombo;
		QComboBox*		_viewScaleCombo;
		QPushButton* 	_defaultViewBtn;

		QToolBar*		_taskToolBar;

		AxesLayout* 				_axesLayout;
		QGraphicsView*				_view;

		QList<DataEntry*>			_data;



};


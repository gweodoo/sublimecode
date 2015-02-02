/***************************************************************************/
/*                                                                         */
/* This file is part of Sublime Code.                                      */
/*                                                                         */
/* Sublime Code is free software: you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by    */
/* the Free Software Foundation, either version 3 of the License, or       */
/* (at your option) any later version.                                     */
/*                                                                         */
/* Sublime Code is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
/* GNU General Public License for more details.                            */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with Sublime Code.  If not, see <http://www.gnu.org/licenses/>.   */
/*                                                                         */
/***************************************************************************/

#ifndef UI_MAINWINDOW1_H
#define UI_MAINWINDOW1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QDesktopWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QComboBox>
#include <QLabel>
#include <QMovie>

QT_BEGIN_NAMESPACE

/**
* Ui mainwindow is the displayer (window maker) for the project selection view
*/
class UI_MainWindow1
{
private: 
	QWidget *centralWidget;                      ///< main widget 
	QWidget *directoryWidget;                    ///< directory widget
	QWidget *vcsWidget;                          ///< vcs widget
	QWidget *archiveWidget;                      ///< archive widget
	QGroupBox *sourcesGroupBox;                  ///< sources group box
	QGroupBox *destinationGroupBox;              ///< destination group box
	QTabWidget *tabs;                            ///< tab widget
	QPushButton *browseSource;                   ///< browse local sources button 
	QPushButton *browseDest;                     ///< browse destination button
	QPushButton *browseArchive;                  ///< browse archive button
	QPushButton *Finish;                         ///< finish button
	QLineEdit *lineEditSource;                   ///< local file sources line edit
	QLineEdit *lineEditDest;                     ///< destination line edit
	QLineEdit *lineEditVcs;                      ///< vcs line edit
	QLineEdit *lineEditArchive;                  ///< archive line edit
	QLineEdit * lineEditBranch;                  ///< branch vcs line edit 
	QLabel *labelBranch;                         ///< branch label
	QLabel *labelBrowseSource;                   ///< local sources label
	QLabel *labelBrowseDest;                     ///< destination label
	int width;                                   ///< window width 
	int height;                                  ///< window height
	QComboBox *comboBoxVcs;                      ///< vcs combo box
	QComboBox *comboBoxArchive;                  ///< archive combo box
	QLabel *waitingLabel;                        ///< waiting spinner label
	QMovie *waitingMovie;                        ///< waiting spinner movie
	static const char * const vcsTypes[];        ///< char* array of vcs types
	static const char * const archiveTypes[];    ///< char* array of archive types

public:
	///default destructor
	explicit UI_MainWindow1();
	///default destructor
	~UI_MainWindow1();
	/**
	* graphical initializer
	* \param[in] MainWindow the base class MainWindow, our container
	*/
	void setupUi(QMainWindow *MainWindow);
	/**
	 * Translate buttons according to system language.
	 * \param[in] MainWindow the base class MainWindow, our container
	 */
	void retranslateUi(QMainWindow *MainWindow);
	/**
	 * Local source file line edit qt object getter
	 * \return class member as pointer
	 */
	QLineEdit *getLineEditSource();
	/**
	 * Archive branch line edit qt object getter
	 * \return class member as pointer
	 */
	QLineEdit *getLineEditBranch();
	/**
	 * Destination line edit qt object getter
	 * \return class member as pointer
	 */
	QLineEdit *getLineEditDest();
	/**
	 * Archive line edit qt object getter
	 * \return class member as pointer
	 */
	QLineEdit *getLineEditArchive();
	/**
	 * Vcs line edit qt object getter
	 * \return class member as pointer
	 */
	QLineEdit *getLineEditVcs();
	/**
	 * Browse local sources file button qt object getter
	 * \return class member as pointer
	 */
	QPushButton *getButtonBrowseSource();
	/**
	 * Browse local destination file button qt object getter
	 * \return class member as pointer
	 */
	QPushButton *getButtonBrowseDest();
	/**
	 * Browse local archive file button qt object getter
	 * \return class member as pointer
	 */
	QPushButton *getButtonBrowseArchive();
	/**
	 * Finish button qt object getter
	 * \return class member as pointer
	 */
	QPushButton *getFinish();
	/**
	 * Tabs widget qt object getter
	 * \return class member as pointer
	 */
	QTabWidget *getQTabWidget();
	/**
	 * Vcs combo box qt object getter
	 * \return class member as pointer
	 */
	QComboBox *getComboBoxVcs();
	/**
	 * Archive combo box qt object getter
	 * \return class member as pointer
	 */
	QComboBox *getComboBoxArchive();
	/**
	 * Waiting spinner movie qt object getter
	 * \return class member as pointer
	 */
	QMovie *getWaitingMovie();
	/**
	 * Main widget qt object getter
	 * \return class member as pointer
	 */
	QWidget *getCentralWidget();
	/**
	 * Waiting spinner label qt object getter
	 * \return class member as pointer
	 */
	QLabel *getWaitingLabel();
};

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

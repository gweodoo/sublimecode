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

#ifndef HANDLETHREAD_H
#define HANDLETHREAD_H

#include "handler/Handler.h"
#include <QThread>

/**
 * Threaded handler process 
 */
class HandlerThread : public QThread
{
	Q_OBJECT
	
public:
	/**
	 * Default constructor
	 * \param[in] parent Upstream accessor
	 */
	HandlerThread(QObject *parent = 0);
	
	/**
	 * Default Destructor
	 */
	~HandlerThread();
	
	/**
	 * Launch the handler process that try to get the project from a vcs
	 */
	void run();
	
	/**
	 * Sets handler with the configured handler
	 * \param[in] handler The configured handler
	 */
	void setHandler(Handler *handler);
	
private:
	Handler *handler; ///< The configured handler
	
signals:
	/**
	 * Signal when the handler process has finished
	 * \param[in] isDone Boolean that indicates the process ended successfully
	 */
	void handlerChanged(bool isDone);
};

#endif // HANDLETHREAD_H

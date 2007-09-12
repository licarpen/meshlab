#ifndef __RMXMLPARSER_H__
#define __RMXMLPARSER_H__

#include <QString>
#include <QFile>
#include <QDomDocument>
#include <qDebug>
#include <QList>

#include "RmEffect.h"
#include "RmPass.h"
#include "UniformVar.h"
#include "GlState.h"


/*
 * This is the main class for RenderMonkey file (.rfx) Xml Parser.
 * A RenderMonkey file can contain any number of RmOpenGLEffect, each of which can
 * contain any number of RmGLPass. Not all the pass have a fragment or vertex
 * program, so we ignore the one that do not have them 
 * It works on a file corresponding to the given file name and the parsing
 * is invoked by calling parse(). On success, this is the tree of class
 * collected by the parser:
 *
 *		RmXmlParser:
 *			- List< RmEffect >, each RmEffect has:
 *				- List< RmPass >, each RmPass has:
 *					- the fragment program source code
 *					- the vertex program source code
 *					- the uniform variable used in the fragment program
 *					- the uniform variable used in the vertex program
 *					- other infos such as openGL state and model reference
 * 
 * Any class that is a container of List< other class > has these three methods:
 *		- int size()					to know the list size
 *		- T & at(int idx)				to get the idx-th element of the list
 *		- T & operator[] (int idx)		as above
 *
 * 
*/
class RmXmlParser
{
	QString error;
	QString filename;
	QDomDocument doc;

	QList<RmEffect> effects;

	public:
		RmXmlParser( ) {}
		RmXmlParser( QString filename ) { setFileName(filename); }
		virtual ~RmXmlParser( ){}

		// * start the parsing
		// * return true on success
		// * return false on failing, then use getError() 
		bool parse( QString filename = QString() );


		QString & getFileName() { return filename; }
		QString & errorString() { return error; }
		void setFileName( QString _filename ) { filename = _filename; }


		// * These are to manipulate the list of effects
		int size() { return effects.size(); }
		RmEffect & at(int idx) { return effects[idx]; }
		RmEffect & operator[] (int idx) { return effects[idx]; }

		// * debug purpose
		void VarDump( bool extendedDump = false );


		static QDomElement getDomElement( QDomElement & root, QString tagname, QString name );
};



#endif


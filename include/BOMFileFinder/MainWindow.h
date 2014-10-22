//
// MainWindow.h
//

#ifndef H__BOMFILEFINDER_MAINWINDOW__H
#define H__BOMFILEFINDER_MAINWINDOW__H

#define NOMINMAX

#include <QMainWindow>
#include <QTreeWidget>
#include <QLineEdit>

namespace BOMFileFinder {

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
public Q_SLOTS:
	void selectDir();
	void load();
	void itemDoubleClicked(QTreeWidgetItem * item, int column);
private:
	QLineEdit *_directory;
	QTreeWidget *_list;
};

} // namespace BOMFileFinder

#endif // H__BOMFILEFINDER_MAINWINDOW__H

#include "BOMFileFinder/MainWindow.h"
#include "BOMFileFinder/BOMDetector.h"

#include <QDirIterator>
#include <QTimer>
#include <QDebug>

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QUrl>
#include <QPushButton>
#include <QFileDialog>
#include <QSettings>

namespace BOMFileFinder {

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	setWindowTitle("BOM File Finder");
	setWindowIcon(QIcon(":/edge.png"));

	QWidget *central = new QWidget(this);
	_directory = new QLineEdit(this);
	QPushButton *seldirBtn = new QPushButton("Select directory", this);
	connect(seldirBtn, SIGNAL(clicked()), this, SLOT(selectDir()));
	QPushButton *loadBtn = new QPushButton("Reload", this);
	connect(loadBtn, SIGNAL(clicked()), this, SLOT(load()));
	_list = new QTreeWidget(this);
	connect(_list, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem *, int)));
	_list->setColumnCount(2);
	QStringList listheader;
	listheader.append("BOM");
	listheader.append("Filename");
	_list->setHeaderLabels(listheader);


	QVBoxLayout *clayout = new QVBoxLayout;
	central->setLayout(clayout);

	QHBoxLayout *dirlayout = new QHBoxLayout;
	clayout->addLayout(dirlayout);
	dirlayout->addWidget(new QLabel("Directory: ", this));
	dirlayout->addWidget(_directory);
	dirlayout->addWidget(seldirBtn);
	dirlayout->addWidget(loadBtn);

	clayout->addWidget(_list);

	setCentralWidget(central);

	QSettings settings;
	_directory->setText(settings.value("directory", "").toString());
}

void MainWindow::load()
{
	_list->clear();

	if (_directory->text().isEmpty())
		return;

	QDirIterator diri(_directory->text(), QDirIterator::Subdirectories);
	while (diri.hasNext())
	{
		diri.next();

		if (diri.fileInfo().isFile())
		{
			BOMDetector::bom_t bomres = BOMDetector::detect(diri.filePath());
			if (bomres != BOMDetector::BT_NONE)
			{
				//qDebug() << diri.filePath() << " ::: " << BOMDetector::bomTitle(bomres);

				QStringList data;
				data.append(BOMDetector::bomTitle(bomres));
				data.append(diri.filePath());
				_list->addTopLevelItem(new QTreeWidgetItem((QTreeWidget*)0, data));
			}
		}

	}
}

void MainWindow::itemDoubleClicked(QTreeWidgetItem * item, int column)
{
	if (item != NULL)
	{
		QDesktopServices::openUrl(QUrl(item->text(1)));
	}
}

void MainWindow::selectDir()
{
	QString dir(_directory->text());
	dir = QFileDialog::getExistingDirectory(this, "Select directory", dir);

	if (dir != _directory->text())
	{
		QSettings settings;
		settings.setValue("directory", dir);

		_directory->setText(dir);
		load();
	}
}

} // namespace AppStatsD
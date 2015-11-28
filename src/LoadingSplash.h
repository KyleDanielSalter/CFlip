#ifndef LOADINGSPLASH_H
#define LOADINGSPLASH_H

#include <QWidget>

namespace Ui {
	class LoadingSplash;
}

class LoadingSplash : public QWidget
{
	Q_OBJECT

public:
	explicit LoadingSplash(QWidget *parent = 0);
	~LoadingSplash();

private:
	Ui::LoadingSplash *ui;
};

#endif // LOADINGSPLASH_H

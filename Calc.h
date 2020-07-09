#ifndef CALC_H
#define CALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calc; }
QT_END_NAMESPACE

class Calc : public QMainWindow
{
    Q_OBJECT

public:
	explicit Calc(QWidget *parent = nullptr);
    ~Calc() override;

private:
    Ui::Calc *ui;

private slots:
	void numButtonPressed();
	void commaButtonPressed();
	void mathButtonPressed();

	QString performOperation();

	void equalButtonPressed();
	void percentButtonPressed();

	void squareButtonPressed();
	void sqrtButtonPressed();

	void clearButtonPressed();
	void signButtonPressed();

	void memButtonPressed();
	void memAddButtonPressed();
	void memSubButtonPressed();

	static void offButtonPressed();
};
#endif // CALC_H

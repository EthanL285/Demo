#ifndef CHORDS_H
#define CHORDS_H

#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

//////////////////// Toggle Switch Class ////////////////////

class ToggleSwitch : public QWidget {
    Q_OBJECT

public:
    ToggleSwitch(QColor background, QWidget *parent = nullptr);
    bool isToggled();
    void toggle();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void clicked();

private:
    QColor background;
    QWidget *handle;
    bool toggled = false;

public slots:
    void animateHandle();
};

//////////////////// Chords Class /////////////////////

class Chords : public QWidget
{
    Q_OBJECT
public:
    explicit Chords(QWidget *parent = nullptr);
    void toggleContent();
    void animateAccordion(QWidget *widget);
    void toggleMode();

private slots:
    void addChord();
    void changeWindow();

private:
    QWidget *content;
    QWidget *header;
    QLineEdit *searchField;
    QPushButton *button;
    QPushButton *trash;
    QPushButton *back;
    QLabel *barPlacement;
    QComboBox *barDropdown;
    bool contentToggled = false;
    QIcon expandIcon;
    QIcon collapseIcon;
    QScrollArea *scrollArea;
    QStackedWidget *stackedWidget;
    QWidget *chordWindow = nullptr;
    QWidget *chordDiagram;
    ToggleSwitch *placeSwitch;
    ToggleSwitch *dragSwitch;
    ToggleSwitch *deleteSwitch;
};

//////////////////// Chord Diagram Class ////////////////////

class ChordDiagram : public QWidget {
    Q_OBJECT

public:
    ChordDiagram(QWidget *parent = nullptr);
    QPointF snapToGrid(const QPointF &pos);
    bool onSameString(QPointF point);
    int getCircleNum(QPointF point);
    int getNextCircleNum();
    int getCircleIndex(QPointF point);
    int getStringCircleIndex(QPointF point);
    int getStringNum(QPointF point);
    bool circleHover(QPointF point);
    void closeString(int stringNum);
    void openString(int stringNum);
    void drawCircle(QPainter &painter, QPointF center, int circleNum);
    void resetDiagram();
    friend class Chords;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Chords *chords;
    int cellHeight;
    int cellWidth;
    bool isHoveringWidget = false;
    bool isHoveringCircle = false;
    bool placeMode = false;
    bool dragMode = false;
    bool deleteMode = false;
    bool limitReached = false;
    bool snap = false;
    bool isPressed = false;
    bool circlePositionsFound = false;
    QVector<QPointF> circlePositions;
    QVector<QPair<QPointF, int>> placedCircles;
    QPointF grabbedCircle = QPointF(-1,-1);
    QPointF currCirclePos = QPointF(-1,-1);
    QVector<QPushButton*> stringButtons;
};

//////////////////// Field Class ////////////////////

class Field : public QLineEdit {
    Q_OBJECT

public:
    Field(QString text, bool dark, int width = 0, QWidget *parent = nullptr);
};

//////////////////// Label Class ////////////////////

class Label : public QLabel {
    Q_OBJECT

public:
    Label(QString text, QWidget *parent = nullptr);
};

#endif // CHORDS_H

#ifndef CHECKBOXPERSO_H
#define CHECKBOXPERSO_H

#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <dialog.h>

class CheckBoxPerso : public QWidget {
    Q_OBJECT
public:
    QCheckBox *checkBox;
    QPushButton *button;

    CheckBoxPerso(QWidget *parent = nullptr) : QWidget(parent) {
        QHBoxLayout *layout = new QHBoxLayout(this);
        checkBox = new QCheckBox("Tarea", this);
        button = new QPushButton("...", this); // Botón adicional

        layout->addWidget(checkBox);
        layout->addStretch();
        layout->addWidget(button);

        connect(checkBox, &QCheckBox::stateChanged, this, &CheckBoxPerso::onCheckboxChanged);
        connect(button, &QPushButton::clicked, this, &CheckBoxPerso::onButtonClicked);
    }

    void editarTarea(std::string &tareaActual);

signals:
    void checkboxToggled(bool checked);
    void buttonEditClicked();
    void editWithData(std::string &tareaAntigua, std::string &tareaActual);

private slots:
    void onCheckboxChanged(int state) {
        emit checkboxToggled(state == Qt::Checked);
    }

    void onButtonClicked();

private:
};

#endif // CHECKBOXPERSO_H

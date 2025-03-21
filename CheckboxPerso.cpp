#include <CheckboxPerso.h>
#include <QMessageBox>

void CheckBoxPerso::onButtonClicked(){
    Dialog *uiDialog = new Dialog(this);
    connect(uiDialog, &Dialog::acceptedWithData, this, &CheckBoxPerso::editarTarea);
    uiDialog->exec();
}

void CheckBoxPerso::editarTarea(std::string &tareaActual){
    std::string tareaAntigua = checkBox->text().toStdString();
    emit editWithData(tareaAntigua, tareaActual);
}

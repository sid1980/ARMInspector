/** To change this license header, coose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/****************************************************************************
 ** 
 **             ВЫВОД СПИСКА ПОЛЬЗОВАТЕЛЕЙ
 **             Класс окна вывода списка пользователя -Dialog.
 **             Используются для вывода данных о пользователе списком
 **             Модель эземпляра из списка - UserView.
 **
 ****************************************************************************/

/*
 * File:   dialog.cpp
 * Author: kazun
 *
 * Created on 29 марта 2021 г., 20:44
 */

//Форма вывода списка пользователей



#include "dialog.h"
#include "User/User.h"
#include "User/UserView.h"
#include <QButtonGroup>
#include <QRadioButton>
#include <QDebug>
#include <QComboBox>
#include <QPalette>
#include <QColor>
#include <QString>
#include <string>

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

Dialog::Dialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::dialog) {
    ui->setupUi(this);
    usrFrm_ = new userForm(this);
    pwdFrm_ = new pwdFrm(this);
    usrEdtFrm_ = new userEditFrm(this);
    userview_ = new UserView();
    listusers_ = new ModelList<UserView>();
    proxyModel_ = new QSortFilterProxyModel(listusers_);
    const QColor hlClr = Qt::red; // highlight color to set
    const QColor txtClr = Qt::white; // highlighted text color to set

    QPalette p = palette();
    p.setColor(QPalette::Highlight, hlClr);
    p.setColor(QPalette::HighlightedText, txtClr);
    setPalette(p);
    QMessageBoxEx::setCustomTextForButton(QMessageBox::Yes, "Да");
    QMessageBoxEx::setCustomTextForButton(QMessageBox::No, "Нет");
}

///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

Dialog::~Dialog() {
    delete ui;
    delete usrFrm_;
    delete pwdFrm_;
    delete usrEdtFrm_;
    delete userview_;
    delete listusers_;
    delete proxyModel_;
}

Ui::dialog* Dialog::getUI() {
    return ui;
}

///-----------------------------------------------------------------------------
///
///         Инициализация ссылки на контроллер клиента.
///          
///-----------------------------------------------------------------------------

void Dialog::initClient(ClientController *clientController) {
    m_pClientController = clientController;
    // Сигнально-слотовое соединение, сигнализирующее, что   контроллер комманд
    // готов вернуть  результат  выполнения запроса к серверу.
    connect(this, SIGNAL(ready()), m_pClientController, SLOT(formReady()));
    ///выполнить команду на сервере
    connect(this, SIGNAL(runServerCmd(const QString&)), m_pClientController, SLOT(runServerCmd(const QString&)));
    //установить модель TableView после получения списка моделей (в данном случае пользователей)
    connect(m_pClientController, SIGNAL(listUserReady(const QList<UserView>&)), this, SLOT(setModel(const QList<UserView>&)));
    //установить модель TableView после получения списка моделей (в данном случае пользователей)
    connect(m_pClientController, SIGNAL(listInspectionsReady(const QList<Inspection>&)), this, SLOT(setListInspections(const QList<Inspection>&)));
    //Показать новую запись после ответа сервера
    connect(m_pClientController, SIGNAL(responseServer(const QString&)), this, SLOT(showNewUserData(const QString&)));
    //// Сигнально-слотовое соединение  ожидания ответа от сервера.
    connect(this, SIGNAL(waitReady()), m_pClientController, SLOT(waitReady()));
};



///-----------------------------------------------------------------------------
///
///         показать данные о новом пользователе в  окне списка пользователей
///          
///-----------------------------------------------------------------------------

void Dialog::showNewUserData(const QString& asUser) {
    User user;
    JsonSerializer::parse(asUser, user);
    //table2->selectRow(current.row());
    userview_->setId(user.getId());
    userview_->setFio(user.getFio());
    userview_->setName(user.getName());
    userview_->setInspection(usrFrm_->getInspections()[user.getInspection() - 1].getName());
    listusers_->addModel(*userview_);
    this->getUI()->tableView->selectRow(listusers_->rowCount() - 1);
    this->getUI()->tableView->scrollToBottom();
}


///-----------------------------------------------------------------------------
///
///              показать отредактированные данные о  пользователе в 
///              окне списка пользователей
///          
///-----------------------------------------------------------------------------

void Dialog::showEditUserData(const User& user) {
    userview_->setId(user.getId());
    userview_->setFio(user.getFio());
    userview_->setName(user.getName());
    userview_->setInspection(usrFrm_->getInspections()[user.getInspection() - 1].getName());
    QItemSelectionModel *select = this->getUI()->tableView->selectionModel();
    int rowidx = select->currentIndex().row();
    this->getUI()->tableView->scrollTo(select->currentIndex());
    select->model()->setData(select->model()->index(rowidx, 0), userview_->getId(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 1), userview_->getFio(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 2), userview_->getInspection(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 3), userview_->getName(), Qt::EditRole);
    emit ready();
}




///-----------------------------------------------------------------------------
///
///         заполнить форму редактирования пользователя
///          
///-----------------------------------------------------------------------------

void Dialog::fillUserEditFrm(const User& user) {
    usrEdtFrm_->getWidget()->lineEditFio->setText(user.getFio());
    for (int i = 0; i < usrEdtFrm_->getInspections().size(); i++) {
        if (usrEdtFrm_->getInspections()[i].getId() == user.getInspection()) {
            usrEdtFrm_->getWidget()->comboBoxInspection->setCurrentIndex(i);
            break;
        }
    }
    usrEdtFrm_->getWidget()->lineEditName->setText(user.getName());
    QList<QRadioButton *> allButtons;
    allButtons = usrEdtFrm_->getWidget()->groupBoxStatus->findChildren<QRadioButton *>();
    for (int i = 1; i <= allButtons.size(); ++i) {
        if (i == user.getStatus()) {
            allButtons[i - 1]->setChecked(true);
        }
    }
    allButtons = usrEdtFrm_->getWidget()->groupBoxRole->findChildren<QRadioButton *>();
    for (int i = 1; i <= allButtons.size(); ++i) {
        if (i == user.getRole()) {
            allButtons[i - 1]->setChecked(true);
        }
    }
}


///-----------------------------------------------------------------------------
///
///         Инициализировать список инспекций  в окнах ввода и 
///         редактированиядля пользователя  
///          
///-----------------------------------------------------------------------------

void Dialog::setListInspections(const QList<Inspection>& inspections) {
    //QMessageBox::information(0, "Information Box", inspections[1].getName());
    usrFrm_->setInspections(inspections);
    usrEdtFrm_->setInspections(inspections);
    emit ready();
};

///-----------------------------------------------------------------------------
///
///         определить модель вывода данных
///          
///-----------------------------------------------------------------------------

void Dialog::setModel(const QList<UserView>& users) {
    listusers_->setListModel(users);
    proxyModel_->setSourceModel(listusers_);
    this->getUI()->tableView->setSortingEnabled(true); // enable sortingEnabled
    this->getUI()->tableView->setModel(proxyModel_);
    emit ready();
    //this->getUI()->tableView->setSpan(0,1,2,2);
}

///-----------------------------------------------------------------------------
///
///         вывести на экран  окно списка пользователей
///          
///-----------------------------------------------------------------------------

void Dialog::showBox() {
    this->getUI()->tableView->setColumnHidden(0, true);
    this->getUI()->tableView->resizeColumnsToContents();
    this->getUI()->tableView->resizeRowsToContents();
    //emit getInspections();
    this->exec();
}

///-----------------------------------------------------------------------------
///
///         обработчик кнопки добавления пользователя
///          
///-----------------------------------------------------------------------------

///Обработка нажатия кнопки добавления  пользователя.
///Данные считываются из формы данных пользователя,
///добавляются в Модель отображения данных на экране и
///и в Модель передачи данных на сервер.

void Dialog::on_pushButton_addUser_clicked() {
    this->getUI()->tableView->model()->sort(-1);
    usrFrm_->getWidget()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Сохранить"));
    usrFrm_->getWidget()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
    if (usrFrm_->exec() == QDialog::Accepted) {

        User* user = new User();
        user->setFio(usrFrm_->getWidget()->lineEditFio->text());
        user->setInspection(usrFrm_->getInspections()[usrFrm_->getWidget()->comboBoxInspection->currentIndex()].getId());

        user->setName(usrFrm_->getWidget()->lineEditName->text());
        user->setPassword(usrFrm_->getWidget()->lineEditPassword->text());

        ///Получить значение RadioBox
        QButtonGroup group;
        QList<QRadioButton *> allButtons;
        allButtons = usrFrm_->getWidget()->groupBoxStatus->findChildren<QRadioButton *>();
        for (int i = 1; i <= allButtons.size(); ++i) {
            group.addButton(allButtons[i - 1], i);
        }
        user->setStatus(group.checkedId());

        allButtons = usrFrm_->getWidget()->groupBoxRole->findChildren<QRadioButton *>();
        for (int i = 1; i < allButtons.size(); ++i) {
            group.addButton(allButtons[i - 1], i);
        }
        user->setRole(group.checkedId());
        //QMessageBox::information(this, "Добавление нового пользовтеля",
        //        QString::number(user->getInspection()));
        //proxyModel_->setSourceModel(listusers_);
        //createAddUserQuery(*user);
        emit runServerCmd(Functor<User>::produce(ModelWrapper::ADD_NEW_USER, *user));
        //emit addUser(*user);
        emit waitReady();
        delete user;
    }
}

///-----------------------------------------------------------------------------
///
///         Обработчик кнопки редактирования пользователя
///          
///-----------------------------------------------------------------------------

void Dialog::on_pushButton_editUser_clicked() {

    int rowidx = proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()).row();
    if (rowidx >= 0) {
        UserView userV = listusers_->getModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
        auto id = userV.getId();
        QJsonObject param;
        param.insert("ID", id);
        emit runServerCmd(Functor<User>::producePrm(ModelWrapper::GET_MODEL, param));
        emit waitReady();
        usrEdtFrm_->getWidget()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Сохранить"));
        usrEdtFrm_->getWidget()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
        if (usrEdtFrm_->exec() == QDialog::Accepted) {
            User* user = new User();
            user->setId(id);
            user->setFio(usrEdtFrm_->getWidget()->lineEditFio->text());
            user->setInspection(usrEdtFrm_->getInspections()[usrEdtFrm_->getWidget()->comboBoxInspection->currentIndex()].getId());
            user->setName(usrEdtFrm_->getWidget()->lineEditName->text());

            ///Получить значение RadioBox
            QList<QRadioButton *> buttons;
            buttons = usrEdtFrm_->getWidget()->groupBoxStatus->findChildren<QRadioButton *>();
            for (int i = 1; i <= buttons.size(); ++i) {
                if (buttons[i - 1]->isChecked()) {
                    user->setStatus(i);
                }
            }
            buttons = usrEdtFrm_->getWidget()->groupBoxRole->findChildren<QRadioButton *>();
            for (int i = 1; i <= buttons.size(); ++i) {
                if (buttons[i - 1]->isChecked()) {
                    user->setRole(i);
                }
            }
            //emit updateUser(*user);
            emit runServerCmd(Functor<User>::produce(ModelWrapper::EDIT_USER, *user));
            emit waitReady();
            delete user;

        }
    }
}
///-----------------------------------------------------------------------------
///
///         обработчик кнопки удаления  пользователя
///          
///-----------------------------------------------------------------------------

void Dialog::on_pushButton_deleteUser_clicked() {
    //Question MessageBox
    int rowidx = proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()).row();
    if (rowidx >= 0) {
        UserView user = listusers_->getModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
        auto id = user.getId();
        QMessageBoxEx::StandardButton reply;
        reply = QMessageBoxEx::question(this, "Удаление пользователя",
                "Вы действительно хотите удалить пользователя <br><br><a style='font-size:14px;color:red;'> " +
                user.getFio() + "</a> ?<br>",
                QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qDebug() << "Yes was clicked";
            QJsonObject param;
            param.insert("ID", id);
            //emit deleteUser(id);
            emit runServerCmd(Functor<User>::producePrm(ModelWrapper::DEL_MODEL, param));
            emit waitReady();
            listusers_->delModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
        } else {
            qDebug() << "Yes was *not* clicked";
        }
    }
}


///-----------------------------------------------------------------------------
///
///         обработчик кнопки редактирования пароля
///          
///-----------------------------------------------------------------------------

void Dialog::on_pushButton_changePassword_clicked() {
    int rowidx = proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()).row();
    if (rowidx >= 0) {
        UserView userV = listusers_->getModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
        pwdFrm_->getWidget()->labelUser->setText(userV.getFio());
        pwdFrm_->getWidget()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Сохранить"));
        pwdFrm_->getWidget()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));

        if (pwdFrm_->exec() == QDialog::Accepted) {
            QString pwd1 = pwdFrm_->getWidget()->lineEditPwd->text().trimmed();
            QString pwd2 = pwdFrm_->getWidget()->lineEditPwd2->text().trimmed();
            if (pwd1.isEmpty() || pwd2.isEmpty()) {
                QMessageBox::information(0, "Изменение пароля пользовтеля", "Пароль не может быть пустым");
                return;
            }
            if (pwd1.compare(pwd2, Qt::CaseSensitive) != 0) {
                QMessageBox::information(0, "Изменение пароля пользовтеля", "Пароли не совпадают");
                return;
            }
            qDebug() << "pwdFrm Yes was clicked";
            User* user = new User();
            user->setId(userV.getId());
            user->setFio(userV.getFio());
            user->setName(userV.getName());
            user->setPassword(pwdFrm_->getWidget()->lineEditPwd->text());
            emit runServerCmd(Functor<User>::produce(ModelWrapper::CHANGE_PASSWORD, *user));
            //emit setPwd(*user);
            emit waitReady();
            delete user;
        }
    }

    //pwdFrm * frm=new pwdFrm(this);
    //frm->show();
    //QMessageBox::information(0, "Редактирование пользовтеля","");
    //pwdFrm_->show() ;
}


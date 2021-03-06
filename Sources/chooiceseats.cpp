#include "Headers/chooiceseats.h"
#include "ui_chooiceseats.h"
#include <stdlib.h>



chooiceSeats::chooiceSeats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooiceSeats)
{
    ui->setupUi(this);

}

void chooiceSeats::setText(QString text)
{
    txt = text;
}

void chooiceSeats::setHallID(int hall)
{
    hallID = hall;
}

void chooiceSeats::setShowID(int showId)
{
    showID = showId;
}

void chooiceSeats::setNameAndSurname(QString nameVal, QString surnameVal)
{
    name = nameVal + " ";
    surname = surnameVal;
}

void chooiceSeats::setSeatsCount(int count)
{
    tickets = count;
    ui->counterLabel->setText(QString::number(count));
    qDebug() << tickets << " count " << count;
}

void chooiceSeats::setDbPointer(Database base)
{
    dB = &base;
}

void chooiceSeats::generateSeats(int &seats, QList<int> &refList)
{

    qDebug() << "w sali nr. " << refHall << " jest miejsc: " << seats;

    int rows = seats / 10;


    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < 10; col++) {

            QCheckBox* check = new QCheckBox();
            ui->gridL->addWidget(check, row, col);
            connect(check, SIGNAL(clicked(bool)), this, SLOT(check(bool)));

        }
    }

    foreach (int var, refList) {
        QCheckBox *box = qobject_cast<QCheckBox*>(ui->gridL->itemAt(var)->widget());
        box->setChecked(true);
        box->setEnabled(false);

    }

}

bool chooiceSeats::getIsSeatsReserved()
{
    return isSeatsReserved;

}

void chooiceSeats::setSeatsEnabled(bool state)
{
    for (int var = 0; var < ui->gridL->count() ; var++) {
        QCheckBox *box = qobject_cast<QCheckBox*>(ui->gridL->itemAt(var)->widget());
        if(!(box->isChecked()))
        {
            box->setEnabled(state);
        }
        else
        {
            qDebug() << "zaznaczono " << var;
            qDebug() << "rzad " << var/10 + 1;
            qDebug() << "miejsce " << var % 10 + 1;
        }
    }
}

QString chooiceSeats::rezervationSeats()
{
    QString seats = "";
    for(int var = 0; var < ui->gridL->count(); var++)
    {
        QCheckBox *box = qobject_cast<QCheckBox*>(ui->gridL->itemAt(var)->widget());
        if(box->isChecked() && box->isEnabled())
        {
            seats += QString::number(var) + ";";
        }
    }
    return seats;
}

void chooiceSeats::setIsModifyRezerv(bool isModif)
{
    isModifyRezerv = isModif;
}

void chooiceSeats::setRezervId(int &ref)
{
    rezervId = ref;
}



void chooiceSeats::check(bool state)
{
    int counter = ui->counterLabel->text().toInt();
    if(!state)
    {
        if(counter == 0)
        {
            setSeatsEnabled(true);
        }
        counter++;
        ui->counterLabel->setText(QString::number(counter));
    }
    else
    {
        counter--;
        ui->counterLabel->setText(QString::number(counter));
        if(counter == 0)
        {
            setSeatsEnabled(false);
        }
    }
}


chooiceSeats::~chooiceSeats()
{
    delete ui;
}


void chooiceSeats::on_pushButton_clicked()
{
    if(ui->counterLabel->text().toInt() == 0)
    {
        int id;
        if(!isModifyRezerv) id = dB->newRezervationId();
        QString seats = rezervationSeats();
        qDebug() << seats;

        QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "Potwierdzenie","Czy dane sa poprawne?\n" +
                                       name + surname + "\n"+ txt,
                                       QMessageBox::Yes|QMessageBox::No);
         if(reply == QMessageBox::Yes)
         {
             QString content = "con";

             if(isModifyRezerv)
             {
                dB->modifyRezervation(refRezervId, showID, hallID, seats);
                content = "Modifykacja rezerwacji przebiegla pomyslnie";
             }
             else
             {
                 QString pass = QString::number(id) + QString::number(rand() % 100 + 10);
                 qDebug() << id;
                 dB->addRezervation(id, showID, hallID, name, surname, seats, pass.toInt());
                 content = "Pomyslnie zarejestrowano rezerwacje\nTwoj kod to: " + pass;
             }
             QByteArray ba = content.toLatin1();
             const char*c = ba.data();

             QMessageBox::information(this, tr("Sukces"), tr(c));
             isSeatsReserved = true;
             this->close();
         }
    }
    else
    {
        QMessageBox::warning(this, tr("Błąd!"), tr("Nie wybrano wszystkich zadeklarowanych miejsc!"));
    }
}



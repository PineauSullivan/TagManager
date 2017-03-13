#include "Headers/Style.h"

void Style::setStyle(QPushButton* button, int version){
    switch(version){
        case 1:
            button->setCursor(Qt::PointingHandCursor);// vert clair normal
            button->setStyleSheet("border-radius: 10px; color: #ffffff; background: #5afa5a; border: solid black 1px;");
            break;
        case 2:
            button->setCursor(Qt::OpenHandCursor); //vert Foncé, aucun tag
            button->setStyleSheet("border-radius: 10px; color: #ffffff; background: #93bd96;");
            break;
        case 3:
            button->setCursor(Qt::PointingHandCursor); // bleu
            button->setStyleSheet("border-radius: 10px; color: #ffffff; background: #468af0; border: solid black 1px;");
            break;
        case 4:
            button->setCursor(Qt::PointingHandCursor); // orange
            button->setStyleSheet("border-radius: 10px; color: #ffffff; background: #ff9829; border: solid black 1px;");
            break;
        default:
            break;
    }
}

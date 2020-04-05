#include "lightconfig.h"
#include "ui_lightconfig.h"

LightConfig::LightConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LightConfig)
{
    ui->setupUi(this);
}

LightConfig::~LightConfig()
{
    delete ui;
}

QString LightConfig::getRoomName(){
    return ui->lineEditRoom->text();
}
QString LightConfig::getSwitchPri(){
    return ui->lineEditPrimary->text();
}

QString LightConfig::getSwitchSec(){
    return ui->lineEditSecondary->text();
}
int     LightConfig::getConfigSet(){
    if(nameSet && PrimarySet){
        return 1;
    }
    return 0;
}


void LightConfig::on_lineEditRoom_textChanged(const QString &arg1)
{
    nameSet = 1;
    emit configChanged();
}

void LightConfig::on_lineEditPrimary_textChanged(const QString &arg1)
{
    PrimarySet = 1;
    emit configChanged();
}

void LightConfig::on_lineEditSecondary_textChanged(const QString &arg1)
{
    SecondarySet = 1;
    emit configChanged();
}

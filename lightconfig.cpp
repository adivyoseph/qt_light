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
QString LightConfig::getLightName(){
    return ui->lineEditLight->text();
}



void LightConfig::on_lineEditRoom_textChanged(const QString &arg1)
{
    nameSet = 1;
    emit configChanged();
}

void LightConfig::on_lineEditLight_textChanged(const QString &arg1)
{
    LightSet = 1;
    emit configChanged();
}


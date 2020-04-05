#ifndef LIGHTCONFIG_H
#define LIGHTCONFIG_H

#include <QDialog>

namespace Ui {
class LightConfig;
}

class LightConfig : public QDialog
{
    Q_OBJECT

public:
    explicit LightConfig(QWidget *parent = nullptr);
    ~LightConfig();
    QString getRoomName();
    QString getSwitchPri();
    QString getSwitchSec();
    int     getConfigSet();

signals:
    void configChanged(void);

private slots:
    void on_lineEditRoom_textChanged(const QString &arg1);

    void on_lineEditPrimary_textChanged(const QString &arg1);

    void on_lineEditSecondary_textChanged(const QString &arg1);

private:
    Ui::LightConfig *ui;
    int nameSet;
    int PrimarySet;
    int SecondarySet;
};

#endif // LIGHTCONFIG_H

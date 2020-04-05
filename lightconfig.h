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
    QString getLightName();
    int     getConfigSet();

signals:
    void configChanged(void);

private slots:
    void on_lineEditRoom_textChanged(const QString &arg1);

    void on_lineEditLight_textChanged(const QString &arg1);


private:
    Ui::LightConfig *ui;
    int nameSet;
    int LightSet;

};

#endif // LIGHTCONFIG_H

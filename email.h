/*#ifndef EMAIL_H
#define EMAIL_H


#include <QDialog>

namespace Ui
{
class email;
}

class Email
{
    Q_OBJECT

    public:
        explicit Email(QWidget *parent = nullptr);
        ~Email();
    private slots:
        void sendMail();
        void mailSent(QString);
    private:
        Ui::email *ui;
};

#endif // EMAIL_H

*/

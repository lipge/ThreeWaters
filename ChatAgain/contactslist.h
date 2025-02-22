#ifndef CONTACTSLIST_H
#define CONTACTSLIST_H

#include <QListWidget>

class ContactsList : public QListWidget
{
    Q_OBJECT
public:
    ContactsList(QWidget* parent = nullptr);
    void showRedDot(bool show = true);
    void updateContactsList(const QString& name, const QString& headshort);
protected:
    void wheelEvent(QWheelEvent *e) override;
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event)override;
private:
    void addContacts();

private slots:
    void slot_item_clicked(QListWidgetItem* item);

signals:
    void sig_loading_contacts();
    void sig_switch_newfriend();

};

#endif // CONTACTSLIST_H
